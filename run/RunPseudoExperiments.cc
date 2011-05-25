#include <iostream>
#include "TROOT.h"

#include <vector>
#include <algorithm>
#include <sstream>

#include "run/ConfPseudoExperiment.hh"

#include "core/FitCore.hh"
#include "FitterInputs/NormalisationFunctors.hh"
#include "FitterInputs/NormedTH1.hh"
#include "FitterResults/HistoResult.hh"
#include "functions/BinnedEML.hh"
#include "Studies/PseudoStudy.hh"
#include "Studies/ProtoCreators.hh"


#include "TString.h"
#include "TRegexp.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TRandom3.h"
#include "TMath.h"
#include "TArrow.h"
#include "TPad.h"
#include "TPaveStats.h"
#include "TSystem.h"
#include "TF1.h"

#include "AtlasStyle.h"





void createExpectedValuesFromTemplates(const std::vector<TH1*>& _templates,
                                       std::vector<double>& _expected,
                                       std::vector<double>& _errors,
                                       const double& _dataIntegral){

  _expected.clear();
  _expected.resize(_templates.size(),0.);
  _errors.clear();
  _errors.resize(_templates.size(),0.);
  

  
  std::vector<double> integrals(_templates.size(),0.);
  std::vector<double> errors(_templates.size(),0.);
  double total = 0.;
  for (int i = 0; i < _templates.size(); ++i)
  {
    integrals[i] = _templates[i]->IntegralAndError(_templates[i]->GetXaxis()->GetFirst(),
                                                   _templates[i]->GetXaxis()->GetLast(),
                                                   errors[i]
                                                   );
    total += integrals[i];
  }


  for (int i = 0; i < _templates.size(); ++i)
  {
    _expected[i] = (integrals[i]/total)*_dataIntegral;
    _errors[i] = (errors[i]/total)*_expected[i];
    std::cout << "expected value ["<<i <<"]\t"<<_expected[i]<<" +/- "<<_errors[i] <<std::endl;
  }

}

// void addVerticalArrowToPad(TVirtualPad* _thisPad, TArrow* _arrow,const double& _value=0.){
  
//   if(!(_value!=0.))
//     return;

//   double xpos = _thisPad->XtoPad(_value);
//   double yStart = _thisPad->GetUymin();
//   double yEnd = _thisPad->GetUymax();
//   _arrow->DrawArrow(xpos,yStart,
//                     xpos,yEnd,
//                     0.03,"<");

// }

int main(int argc, char* argv[])
{
  TStyle* aStyle =  AtlasStyle();
  aStyle->SetStatY(1.);
  aStyle->SetStatX(.95);
  aStyle->SetStatW(.8);
  aStyle->SetStatH(0.15);
  aStyle->SetStatBorderSize(0.);
  aStyle->SetPadTopMargin(0.22);
  //aStyle->SetHistTopMargin(0.3);
  aStyle->SetOptStat(2210);
  aStyle->SetPalette(1);
  //  aStyle->SetOptFit(1);
  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();

  //set root message level
  //gErrorIgnoreLevel = 2001;
  //
  ConfPseudoExperiment conf(argc,argv);
  if(conf.p_giveHelp)
    return -1;
  else
    if(conf.p_msgLevel)
      conf.printConf();

   // ----- INPUT ----- 
  FitterInputs::NormedTH1<FitterInputs::Norm2Unity>* input = new FitterInputs::NormedTH1<FitterInputs::Norm2Unity>();
  input->loadData(conf.p_datadir.c_str(),conf.p_dataTitle.c_str(),conf.p_rebin);
  input->loadTemplates(conf.p_datadir.c_str(),conf.p_tempTitle.c_str(),conf.p_rebin);

  std::vector<TH1*> m_templates;
  input->getTemplatesDeepCopy(m_templates);
  TH1* m_data =  input->getDataDeepCopy();

   // ----- EXPECTED VALUES ----- 
  std::vector<double> expected          ;
  std::vector<double> expectedErrors    ;
  createExpectedValuesFromTemplates(m_templates,
                                    expected,          
                                    expectedErrors,
                                    m_data->Integral()*TMath::Abs(conf.p_dataScale));

   // ----- PSEUDO EXPERIMENTS ----- 
  double scaleExpectation = TMath::Abs(conf.p_dataScale);
  PseudoStudy<FitterInputs::NormedTH1<FitterInputs::Norm2Unity>, functions::BinnedEML>  
    aPseudoStudy(m_templates,
                 expected,
                 expectedErrors,
                 conf.p_dataScale*(m_data->Integral()),
                 conf.p_threads,
                 conf.p_nIter
                 );

  aPseudoStudy.setInput(input);
  defaultMCValues aCreator;
  aPseudoStudy.setProtoCreator(&aCreator);
  aPseudoStudy.setFitterConfigFile(conf.p_configFile);
  aPseudoStudy.setFitEngine(conf.p_fitEngine);
  aPseudoStudy.setFitMode(conf.p_fitMode);
  aPseudoStudy.setVerbosity(conf.p_msgLevel);
  aPseudoStudy.setBaseName(conf.p_outputfile);
  if(conf.p_msgLevel<3)
    aPseudoStudy.setPanicPrint(true);
  aPseudoStudy.experiment();
  
  

   // ----- COLLECT RESULTS ----- 
  std::vector<std::vector<TH1*> > m_results(m_templates.size());
  for (int i = 0; i < m_templates.size(); ++i)
  {
    aPseudoStudy.getResultsOfParameter(i,m_results[i]);
  }
  
  std::vector<std::vector<TH2*> > m_correlations(m_templates.size());
  aPseudoStudy.getCorrelationResults(m_correlations);


  // ----- DRAW RESULTS IN ONE PAD ----- 
  TCanvas myResults(conf.p_outputfile.c_str(),"",3000,2000);
  myResults.Clear();
  myResults.Draw();
  myResults.Divide(3,m_templates.size());
  int padSize = 3*m_templates.size();
  TLine anLine;
  anLine.SetLineColor(kBlue);
  anLine.SetLineWidth(2);
  int currentPad=0;
  int padStart=1;
  std::ostringstream expValueString;
  TPaveText expValue;
  expValue.SetTextColor(kBlue);
  expValue.SetBorderSize(0.1);
  expValue.SetFillColor(kWhite);

  TVirtualPad* currentPadPtr = 0;
  double ArrowXNDC = 0.;
  for (int i = 0; i < m_results.size(); ++i,padStart+=3)
  {
    expValueString.str("");
    expValueString <</* "expected:\t"<<*/ (expected[i]) << " #pm " << (expectedErrors[i]);
    for (int pad = 0; pad < 3; ++pad)
    {
      currentPad= pad + padStart;
      currentPadPtr = myResults.cd(currentPad);
      expValue.Clear();
      m_results[i][pad]->SetMaximum(1.4*m_results[i][pad]->GetMaximum());
      m_results[i][pad]->Draw("");
      if(pad<1){
        myResults.Update();
        ArrowXNDC = (gPad->XtoPad(expected[i]) - gPad->GetUxmin())/(gPad->GetUxmax() - gPad->GetUxmin());
        if(ArrowXNDC<.5)
          expValue.SetX1NDC(.5);
        else
          expValue.SetX1NDC(.17);

        expValue.SetY1NDC(1-aStyle->GetStatH()-.17);
        expValue.SetX2NDC(expValue.GetX1NDC()+.33);
        expValue.SetY2NDC(expValue.GetY1NDC()+.1);


        expValue.AddText(expValueString.str().c_str());
        expValue.DrawClone();
        
        anLine.DrawLine(gPad->XtoPad(expected[i]),gPad->GetUymin(),
                        gPad->XtoPad(expected[i]),gPad->GetUymax()/*,0.03,"<|"*/);
      }
    }
  }
  myResults.Update();
  myResults.Print(".eps");

    // ----- DRAW MEAN RESULTS IN ONE PAD ----- 
  std::string name = conf.p_outputfile;
  name += "_means";
  TCanvas MeanCanvas(name.c_str(),"",3000,1000);
  MeanCanvas.Clear();
  MeanCanvas.Draw();
  MeanCanvas.Divide(m_templates.size(),1);
  int pad=1;
  for (int i = 0; i < m_results.size(); ++i,pad++)
  {
    MeanCanvas.cd(pad);
    expValue.Clear();
    expValueString.str("");
    expValueString <</* "expected:\t"<<*/ (expected[i]) << " #pm " << (expectedErrors[i]);
    m_results[i][0]->Draw();
    MeanCanvas.Update();
    ArrowXNDC = (gPad->XtoPad(expected[i]) - gPad->GetUxmin())/(gPad->GetUxmax() - gPad->GetUxmin());
    if(ArrowXNDC<.5)
      expValue.SetX1NDC(.5);
    else
      expValue.SetX1NDC(.17);
    
    expValue.SetY1NDC(1-aStyle->GetStatH()-.17);
    expValue.SetX2NDC(expValue.GetX1NDC()+.33);
    expValue.SetY2NDC(expValue.GetY1NDC()+.1);


    expValue.AddText(expValueString.str().c_str());

    expValue.DrawClone();
    anLine.DrawLine(gPad->XtoPad(expected[i]),gPad->GetUymin(),
                    gPad->XtoPad(expected[i]),gPad->GetUymax()/*,0.03,"<|"*/);
    // }
    
    
  }
  MeanCanvas.Update();
  MeanCanvas.Print(".eps");

    // ----- DRAW PULL RESULTS IN ONE PAD ----- 
  name = conf.p_outputfile;
  name += "_pulls";
  TCanvas PullCanvas(name.c_str(),"",3000,1500);
  PullCanvas.Clear();
  PullCanvas.Draw();
  PullCanvas.Divide(m_templates.size(),1);
  pad=1;
  TF1* gaus = new TF1("MyGaus","gaus(0)",m_results[0][2]->GetXaxis()->GetXmin(),m_results[0][2]->GetXaxis()->GetXmax());
  gaus->SetParameter(0,m_results[0][2]->GetEntries());
  gaus->SetParameter(1,0.);
  gaus->SetParameter(2,1.);
  TPaveText fitValues;
  fitValues.SetTextColor(kBlue);
  fitValues.SetBorderSize(0.1);
  fitValues.SetFillColor(kWhite);
  std::ostringstream stream;
  for (int i = 0; i < m_results.size(); ++i,pad++)
  {
    stream.str("");
    fitValues.Clear();
    PullCanvas.cd(pad);

    gPad->SetTopMargin(.2);
    m_results[i][2]->SetStats(false);
    m_results[i][2]->Draw("e0");
    if(m_results[i][2]->GetEntries()>0){
    m_results[i][2]->Fit(gaus,"VR+");
    stream << "#mu :\t" << gaus->GetParameter(1) << " #pm " << gaus->GetParError(1);
    fitValues.AddText(stream.str().c_str());
    stream.str("");
    stream << "#sigma :\t" << gaus->GetParameter(2) << " #pm " << gaus->GetParError(2);
    fitValues.AddText(stream.str().c_str());
    stream.str("");
    stream << "chi2/NDF :\t" << gaus->GetChisquare() << " / " << gaus->GetNDF();
    fitValues.AddText(stream.str().c_str());
    fitValues.SetX1NDC(.15);
    fitValues.SetX2NDC(.85);
    fitValues.SetY1NDC(.82);
    fitValues.SetY2NDC(.98);
    fitValues.DrawClone();
    }
    PullCanvas.Update();
  }
  PullCanvas.Update();
  PullCanvas.Print(".eps");


  name = conf.p_outputfile;
  name += "_maxLLH";

  TCanvas PseudoMaxLLH(name.c_str(),"",800,600);
  PseudoMaxLLH.Clear();
  PseudoMaxLLH.Draw();
  PseudoMaxLLH.cd(0);
  // aPseudoStudy.getMaxLLHDistribution()->Print("all");
  aPseudoStudy.getMaxLLHDistribution()->Draw();
  PseudoMaxLLH.Update();
  PseudoMaxLLH.Print(".eps");

  std::vector<std::vector<TH2*> > m_correlations(m_templates.size());
  aPseudoStudy.getCorrelationResults(m_correlations);
  int ysize = 0;
  int xsize = 0;
  if(m_correlations.size() && m_correlations[0].size()){
    xsize = m_correlations.size();
    ysize = m_correlations[0].size();

    name = conf.p_outputfile;
    name += "_correlations";

    TCanvas PseudoCorrelation(name.c_str(),"",xsize*800,ysize*600);

    PseudoCorrelation.Clear();
    PseudoCorrelation.Draw();
    PseudoCorrelation.Divide(xsize,ysize);
    
    int padId = 0;
    std::ostringstream correlationText;
    for (int col = 0; col < m_correlations.size(); ++col)
    {
      for (int row = 0; row < m_correlations[0].size(); ++row)
      {
        padId = (m_correlations.size()*row)+1+col;
        PseudoCorrelation.cd(padId);
        m_correlations[col][row]->SetStats(false);
        m_correlations[col][row]->Draw("colz");

        correlationText.str("");
        correlationText<< "correlation: " << m_correlations[col][row]->GetCorrelationFactor();
        correlationText<< ", int: ";
        correlationText << m_correlations[col][row]->Integral();
        TPaveText aPave;
        aPave.AddText(correlationText.str().c_str());
        aPave.SetX1NDC(.1);
        aPave.SetX2NDC(.9);
        aPave.SetY1NDC(.85);
        aPave.SetY2NDC(1.);
        
        aPave.DrawClone();
        PseudoCorrelation.Update();
      }
    }
    
    PseudoCorrelation.Print(".eps");

  }

  aPseudoStudy.printResults();
  return 0; 
   

}
 
