#include "HistoResult.hh"
#include "functions/AbsFittingFunction.hh"
#include "TH1D.h"
#include "TFile.h"
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

  TFile* newFile=0;
  newFile = new TFile(m_filename.c_str(),"RECREATE");

  THStack newStack(appendToNameString<std::string>("_stack").c_str(),"");

  TH1D* fitterData = (TH1D*)getFunction()->getData()->getHisto()->Clone(appendToNameString<std::string>("_data").c_str());
  
  TH1D* fitterT0 = (TH1D*)getFunction()->getTemplate(0)->getHisto()->Clone(appendToNameString<int>(0).c_str());
  TH1D* fitterT1 = (TH1D*)getFunction()->getTemplate(1)->getHisto()->Clone(appendToNameString<int>(1).c_str());
  TH1D* fitterT2 = (TH1D*)getFunction()->getTemplate(2)->getHisto()->Clone(appendToNameString<int>(2).c_str());
  
  const double *xs = getMinimizer()->X();
  const double *xErrors = getMinimizer()->Errors();
  

  std::string mode = getMinimizer()->Options().MinimizerAlgorithm();
  fitterT0->Scale(xs[0]);fitterT0->SetFillColor(kRed);
  fitterT1->Scale(xs[1]);fitterT1->SetFillColor(kViolet);
  fitterT2->Scale(xs[2]);fitterT2->SetFillColor(kAzure); 
  fitterT0->SetLineColor(kRed);   
  fitterT1->SetLineColor(kViolet);
  fitterT2->SetLineColor(kAzure); 
  fitterT0->SetMarkerColor(kRed);   
  fitterT1->SetMarkerColor(kViolet);
  fitterT2->SetMarkerColor(kAzure); 
  fitterT0->SetDrawOption("");   
  fitterT1->SetDrawOption("");
  fitterT2->SetDrawOption(""); 


  newStack.Add(fitterT0);
  newStack.Add(fitterT1);
  newStack.Add(fitterT2);

  TCanvas myC(m_filenameCore.c_str(),"",2400,1200);
  myC.Clear();
  myC.Draw();
  myC.Divide(2,1);
  myC.cd(1);
  newStack.Draw("BAR");
  newStack.SetMaximum(1.5*newStack.GetMaximum());
  fitterData->SetMarkerSize(1.5*fitterData->GetMarkerSize());
  fitterData->SetMarkerStyle(8);
  fitterData->Draw("e1same");
  TLegend leg(0.6,0.7,0.92,0.92);
  leg.AddEntry(fitterData,"data","lep");
  leg.AddEntry(fitterT0,"N_{b}","f");
  leg.AddEntry(fitterT1,"N_{c}","f");
  leg.AddEntry(fitterT2,"N_{l}","f");
  leg.SetFillColor(kWhite);
  leg.SetLineColor(kWhite);
  leg.Draw();

  myC.cd(2);
  TPaveText mtext(0,0,1,1,"ARC");

  mtext.AddText(getParameterResult(0,fitterT0->Integral()).c_str());
  mtext.AddText(getParameterResult(1,fitterT1->Integral()).c_str());
  mtext.AddText(getParameterResult(2,fitterT2->Integral()).c_str());
  mtext.Draw();

  myC.Update();
  myC.Print(".eps");

  newFile->Write();
  newFile->Close();
}

std::string FitterResults::HistoResult::getParameterResult(const int& _idx, double _norm=1.){
  std::ostringstream _text;
  if(_idx>=getFunction()->getNumberOfParameters()){
    _text << ">> variable unknown <<";

  }
  else{
    _text << getMinimizer()->VariableName(_idx) << " :\t(";
    _text << _norm*getMinimizer()->X()[_idx];
    double Up=0;
    double Down=0;

    bool minosStatus = getMinimizer()->GetMinosError(_idx,Up,Down);
    if(!minosStatus)
      _text << "\t+/-\t" << _norm*getMinimizer()->Errors()[_idx] << ")";
    else{
      _text << "\t+ " << _norm*Up << "\t- "<<_norm*Down << ")";
    }
  }
    
  return _text.str();
    
}
