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
#include "run/Utilities.hh"


//#include "TString.h"
//#include "TRegexp.h"
//#include "TGraphErrors.h"
//#include "TCanvas.h"
//#include "TRandom3.h"
//#include "TMath.h"
//#include "TArrow.h"
//#include "TPad.h"
//#include "TPaveStats.h"
//#include "TSystem.h"
//#include "TF1.h"

#include "AtlasStyle.h"

// void printAll(const std::vector<std::vector<TH1*> >& _results,const std::vector<double>& _expected,const std::vector<double>& _expectedErrors, TStyle* _aStyle, const std::string& _file=""){


//   TCanvas myResults(_file.c_str(),"",3000,2000);
//   myResults.Clear();
//   myResults.Draw();
//   myResults.Divide(3,_results.size());
//   int padSize = 3*_results.size();
//   TLine anLine;
//   anLine.SetLineColor(kBlue);
//   anLine.SetLineWidth(2);
//   int currentPad=0;
//   int padStart=1;
//   std::ostringstream expValueString;
//   TPaveText expValue;
//   expValue.SetTextColor(kBlue);
//   expValue.SetBorderSize(0.1);
//   expValue.SetFillColor(kWhite);

//   TVirtualPad* currentPadPtr = 0;
//   double ArrowXNDC = 0.;
//   for (int i = 0; i < _results.size(); ++i,padStart+=3)
//   {
//     expValueString.str("");
//     expValueString <</* "expected:\t"<<*/ (_expected[i]) << " #pm " << (_expectedErrors[i]);
//     for (int pad = 0; pad < 3; ++pad)
//     {
//       currentPad= pad + padStart;
//       currentPadPtr = myResults.cd(currentPad);
//       expValue.Clear();
//       _results[i][pad]->SetMaximum(1.4*_results[i][pad]->GetMaximum());
//       _results[i][pad]->Draw("");
//       if(pad<1){
//         myResults.Update();
//         ArrowXNDC = (gPad->XtoPad(_expected[i]) - gPad->GetUxmin())/(gPad->GetUxmax() - gPad->GetUxmin());
//         if(ArrowXNDC<.5)
//           expValue.SetX1NDC(.5);
//         else
//           expValue.SetX1NDC(.17);

//         expValue.SetY1NDC(1-_aStyle->GetStatH()-.17);
//         expValue.SetX2NDC(expValue.GetX1NDC()+.33);
//         expValue.SetY2NDC(expValue.GetY1NDC()+.1);


//         expValue.AddText(expValueString.str().c_str());
//         expValue.DrawClone();
        
//         anLine.DrawLine(gPad->XtoPad(_expected[i]),gPad->GetUymin(),
//                         gPad->XtoPad(_expected[i]),gPad->GetUymax()/*,0.03,"<|"*/);
//       }
//     }
//   }
//   myResults.Update();
//   myResults.Print(".eps");


// }

// void printMeans(const std::vector<std::vector<TH1*> >& _results, const std::vector<double>& _expected,const std::string& _file="", ConfPseudoExperiment* _conf=0){

//   TCanvas MeanCanvas(_file.c_str(),"",3000,1000);
//   MeanCanvas.Clear();
//   MeanCanvas.Draw();
//   int width = _results.size();
//   TString templateNames = _conf->p_tempTitle.c_str();
//   templateNames.ToLower();

//   if(templateNames.Contains("background"))
//     width-=1;

//   if(templateNames.Contains("ttbar") || templateNames.Contains("top"))
//     width-=1;

//   if(templateNames.Contains("qcd"))
//     width-=1;
  
//   MeanCanvas.Divide(width,1);
//   int pad=1;
//   double ArrowXNDC = 0.;
//   TLine anLine;
//   anLine.SetLineColor(kBlue);
//   anLine.SetLineWidth(2);
//   TString title = "";
//   for (int i = 0; i < _results.size(); ++i,pad++)
//   {
//     title = _results[i][0]->GetXaxis()->GetTitle();
//     title.ToLower();
//     if(title.Contains("ttbar") || title.Contains("top") 
//        || title.Contains("qcd") || title.Contains("background")){
//       continue;}

//     MeanCanvas.cd(pad);

//     _results[i][0]->Draw();
//     MeanCanvas.Update();
//     ArrowXNDC = (gPad->XtoPad(_expected[i]) - gPad->GetUxmin())/(gPad->GetUxmax() - gPad->GetUxmin());
//     anLine.DrawLine(gPad->XtoPad(_expected[i]),gPad->GetUymin(),
//                     gPad->XtoPad(_expected[i]),gPad->GetUymax()/*,0.03,"<|"*/);
//     // }

//   }
//   MeanCanvas.Update();
//   MeanCanvas.Print(".eps");

// }

// void printPulls(const std::vector<std::vector<TH1*> >& _results, const std::string& _file="", ConfPseudoExperiment* _conf=0){

//   TCanvas PullCanvas(_file.c_str(),"",3000,1500);
//   PullCanvas.Clear();
//   PullCanvas.Draw();

//   int width = _results.size();
//   TString templateNames = _conf->p_tempTitle.c_str();
//   templateNames.ToLower();

//   if(templateNames.Contains("ttbar") || templateNames.Contains("top"))
//     width-=1;

//   if(templateNames.Contains("qcd"))
//     width-=1;

//   PullCanvas.Divide(width,1);
//   int pad=1;
//   TF1* gaus = new TF1("MyGaus","gaus(0)",_results[0][2]->GetXaxis()->GetXmin(),_results[0][2]->GetXaxis()->GetXmax());
//   gaus->SetParameter(0,_results[0][2]->GetEntries());
//   gaus->SetParameter(1,0.);
//   gaus->SetParameter(2,1.);
//   TPaveText fitValues;
//   fitValues.SetTextColor(kBlue);
//   fitValues.SetBorderSize(0.1);
//   fitValues.SetFillColor(kWhite);
//   std::ostringstream stream;
//   TString title = "";
//   for (int i = 0; i < _results.size(); ++i,pad++)
//   {
//     stream.str("");
//     fitValues.Clear();
//     title = _results[i][2]->GetXaxis()->GetTitle();
//     title.ToLower();
//     if(title.Contains("ttbar") || title.Contains("top") || 
//        title.Contains("qcd") || title.Contains("background"))
//       continue;
//     PullCanvas.cd(pad);

//     gPad->SetTopMargin(.2);
//     _results[i][2]->SetStats(false);
//     _results[i][2]->Draw("e0");
//     if(_results[i][2]->GetEntries()>0){
//     _results[i][2]->Fit(gaus,"VR+");
//     stream << "#mu :\t" << gaus->GetParameter(1) << " #pm " << gaus->GetParError(1);
//     fitValues.AddText(stream.str().c_str());
//     stream.str("");
//     stream << "#sigma :\t" << gaus->GetParameter(2) << " #pm " << gaus->GetParError(2);
//     fitValues.AddText(stream.str().c_str());
//     stream.str("");
//     stream << "chi2/NDF :\t" << gaus->GetChisquare() << " / " << gaus->GetNDF();
//     fitValues.AddText(stream.str().c_str());
//     fitValues.SetX1NDC(.15);
//     fitValues.SetX2NDC(.85);
//     fitValues.SetY1NDC(.82);
//     fitValues.SetY2NDC(.98);
//     fitValues.DrawClone();
//     }
//     PullCanvas.Update();
//   }
//   PullCanvas.Update();
//   PullCanvas.Print(".eps");

// }

// void printCorrelations(const std::vector<std::vector<TH2*> >& _results, const std::string& _file=""){

//   int ysize = 0;
//   int xsize = 0;
//   if(_results.size() && _results[0].size()){
//     xsize = _results.size();
//     ysize = _results[0].size();


//     TCanvas PseudoCorrelation(_file.c_str(),"",xsize*800,ysize*600);

//     PseudoCorrelation.Clear();
//     PseudoCorrelation.Draw();
//     PseudoCorrelation.Divide(xsize,ysize);
    
//     int padId = 0;
//     std::ostringstream correlationText;
//     for (int col = 0; col < _results.size(); ++col)
//     {
//       for (int row = 0; row < _results[0].size(); ++row)
//       {
//         padId = (_results.size()*row)+1+col;
//         PseudoCorrelation.cd(padId);
//         _results[col][row]->SetStats(false);
//         _results[col][row]->Draw("colz");

//         correlationText.str("");
//         correlationText<< "correlation: " << _results[col][row]->GetCorrelationFactor();
//         TPaveText aPave;
//         aPave.SetFillColor(kWhite);
//         aPave.SetBorderSize(0.1);
//         aPave.AddText(correlationText.str().c_str());
//         aPave.SetX1NDC(.1);
//         aPave.SetX2NDC(.9);
//         aPave.SetY1NDC(.85);
//         aPave.SetY2NDC(1.);
        
//         aPave.DrawClone();
//         PseudoCorrelation.Update();
//       }
//     }
    
//     PseudoCorrelation.Print(".eps");

//   }


// }

// void printMaxLLH(TH1* _maxLLH, const std::string& _file=""){

//  TCanvas PseudoMaxLLH(_file.c_str(),"",800,600);
//   PseudoMaxLLH.Clear();
//   PseudoMaxLLH.Draw();
//   PseudoMaxLLH.cd(0);
//   _maxLLH->Draw();
//   PseudoMaxLLH.Update();
//   PseudoMaxLLH.Print(".eps");

// }


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

    std::cout << "expected value ["<<i <<"]\t ("<<integrals[i] <<") --> "<<_expected[i]<<" +/- "<<_errors[i] <<std::endl;
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
  MCValues aProtoMaker(conf.p_datadir.c_str(),conf.p_protoTitle,conf.p_rebin);
  std::vector<TH1*> m_protoFunctions(aProtoMaker.getProtoFunctions()->begin(),
                                     aProtoMaker.getProtoFunctions()->end());


  std::vector<double> expected          ;
  std::vector<double> expectedErrors    ;
  if(conf.p_protoTitle.empty())
    createExpectedValuesFromTemplates(m_templates,
                                      expected,          
                                      expectedErrors,
                                      m_data->Integral()*TMath::Abs(conf.p_dataScale));
  else
    createExpectedValuesFromTemplates(m_protoFunctions,
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
  
  aPseudoStudy.setProtoCreator(&aProtoMaker);
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

  // ----- DRAW RESULTS IN ONE CANVAS -----   
  printAll(m_results,expected,expectedErrors,aStyle,conf.p_outputfile);

  // ----- DRAW ONLY MEAN RESULTS ----- 
  std::string name = conf.p_outputfile;
  name += "_means";
  printMeans(m_results,expected,name,&conf);

  // ----- DRAW ONLY PULL RESULTS  ----- 
  name = conf.p_outputfile;
  name += "_pulls";
  printPulls(m_results,name,&conf);

// ----- DRAW ONLY PULL RESULTS  ----- 
  name = conf.p_outputfile;
  name += "_bias";
  printBias(m_results,name,&conf);


  // ----- DRAW maxLLH RESULTS  ----- 
  name = conf.p_outputfile;
  name += "_maxLLH";

  printMaxLLH(aPseudoStudy.getMaxLLHDistribution(),name);

  // ----- RETRIEVE Correlations RESULTS  ----- 
  std::vector<std::vector<TH2*> > m_correlations(m_templates.size());
  aPseudoStudy.getCorrelationResults(m_correlations);
  
  // ----- DRAW Correlations RESULTS  ----- 
  name = conf.p_outputfile;
  name += "_correlations";
  printCorrelations(m_correlations,name);


  aPseudoStudy.printResults();
  return 0; 
   

}
 
