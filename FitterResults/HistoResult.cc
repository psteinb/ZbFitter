#include "HistoResult.hh"
#include <sstream>

#include "TH1D.h"
#include "TMath.h"
#include "TAxis.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TPaveText.h"
#include "TLegend.h"

void FitterResults::HistoResult::print(){

  
  if(!getMinimizer()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no minimizer given!\n";
    return;
  }



  if(!getFunction()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no function given!\n";
    return;
  }

  m_dataHisto = dynamic_cast<TH1*>(getFunction()->getData()->getHisto()->Clone("Data"));
  m_dataHisto->SetDirectory(0);

  setupHistos();

  TFile* newFile=0;
  std::string name = m_filename;
  if(!(m_filename.find(".root")!=std::string::npos))
    name += ".root";
  newFile = new TFile(name.c_str(),"RECREATE");
  
  //set directory for all TObjects
  joinHistosToFile(newFile);
  
  //scale the input files
  treatInputHistosForResult();
  
  THStack newStack(appendToNameString<std::string>("_stack").c_str(),"");
  TH1* addedTemplates = (TH1*)getScaledTemplateHistograms()->front()->Clone("added");
  addedTemplates->SetDirectory(0);
  addedTemplates->Reset("MICE");
  addedTemplates->ResetStats();

  for (int i = 0; i < getNumberOfParameters(); ++i)
  {
    newStack.Add(getScaledTemplateHistograms()->at(i));
    addedTemplates->Add(getScaledTemplateHistograms()->at(i));
  }

  //---------------- KOLMOGOROV ---------------- 
  double ksProb = m_dataHisto->KolmogorovTest(addedTemplates,"D");
  std::cout << "KOLMOGOROV prob = " << ksProb << std::endl;


  //---------------- PLOTS ---------------- 
  TCanvas fitCanvas(m_filename.c_str(),"",800,600);
  fitCanvas.Clear();
  fitCanvas.Draw();
  fitCanvas.cd(0);

  //---------------- DATA and fitted MC histos ---------------- 

  double highest = std::max(newStack.GetMaximum(),m_dataHisto->GetMaximum());
  newStack.SetMaximum(1.5*highest);
  newStack.Draw("HIST");
  //  newStack.GetXaxis()->SetTitle("m_{SV} [GeV]");
  newStack.GetYaxis()->SetTitle("N / 0.5 GeV");
  m_dataHisto->SetMarkerSize(1.5*m_dataHisto->GetMarkerSize());
  m_dataHisto->SetMarkerStyle(8);
  m_dataHisto->SetStats(0);
  //m_dataHisto->GetXaxis()->SetTitle("m_{SV} [GeV]");
  m_dataHisto->GetYaxis()->SetTitle("N / 0.5 GeV");
  m_dataHisto->Draw("e1same");
  TLegend leg(0.6,0.7,0.92,0.92);
  leg.AddEntry(m_dataHisto,"data","lep");
  for (int i = 0; i < getNumberOfParameters(); ++i)
  {
    leg.AddEntry(getScaledTemplateHistograms()->at(i),getParameterNames()->at(i).c_str(),"f");
  }
  leg.SetFillColor(kWhite);
  leg.SetLineColor(kWhite);
  leg.Draw();
  fitCanvas.Update();
  fitCanvas.Print(".eps");

  

  //---------------- RESUTLS ---------------- 
  TString valName = m_filename.c_str();
  valName.ReplaceAll("_fit","_values");

  int NColumns = (isFractionFit()) ? 2 : 1;

  TCanvas valCanvas(valName.Data(),"",NColumns*800,600);
  valCanvas.Clear();
  valCanvas.Draw();
  
  valCanvas.Divide(/*getNumberOfParameters()*/NColumns,1);
  valCanvas.cd(1);
  TPaveText mtext(0.2,0.2,.9,.9,"ARC");
  for (int i = 0; i < getNumberOfParameters(); ++i)
  {
    mtext.AddText(getParameterResult(i).c_str());
  }
  mtext.Draw();
  TPaveText abstext(0.2,0.2,.9,.9,"ARC");
  if(isFractionFit()){
    //---------------- RESULTS ON FRACTIONS ---------------- 
    valCanvas.cd(2);
    
    std::ostringstream label;
    label.str("");
    label << "data: " << m_dataHisto->Integral();
    abstext.SetLabel(label.str().c_str());
    for (int i = 0; i < getNumberOfParameters(); ++i)
    {
      abstext.AddText(getParameterResult(i,m_dataHisto->Integral()).c_str());
    }
    abstext.Draw();
  }
      
  valCanvas.Update();
  valCanvas.Print(".eps");

  newFile->Write();
  newFile->Close();
}

std::string FitterResults::HistoResult::getParameterResult(const int& _idx, const double& _norm){
  std::ostringstream _text;
  double centralValue = 0.;
  if(_idx>=getNumberOfParameters()){
    _text << ">> variable unknown <<";

  }
  else{
    centralValue = (getResults()->at(_idx));
    _text << getParameterNames()->at(_idx) << " : (";
    _text << centralValue*_norm;

    double Up=0;
    double Down=0;

    double Error=getSymmErrors()->at(_idx);
    double normError = TMath::Sqrt(_norm);

    double symmError = Error;
    if(_norm!=1.)
      symmError = TMath::Sqrt((Error*Error*_norm) + (normError*normError*centralValue));

    int minosStatus = 0;
    getMinosResultsForIndex(_idx,minosStatus,Up,Down);
    double minosDown = Down;
    double minosUp = Up;
    if(_norm!=1.){
      minosDown = TMath::Sqrt((Down*Down*_norm*_norm) + (normError*normError*centralValue*centralValue));
      minosUp = TMath::Sqrt((Up*Up*_norm*_norm) + (normError*normError*centralValue*centralValue));
    }

    if(minosStatus<0 || !(minosUp!=minosDown)){
      _text << " +/- " << symmError << ")";
     }
     else{

       _text << "^{ " << minosUp << "}_{ "<< minosDown << "} )";
     }
  }
    
  return _text.str();
    
}
