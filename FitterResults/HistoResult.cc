#include "HistoResult.hh"

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

  setupParameters();
  
  setupInputHistos();

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
  TH1* sumOfTemplates = dynamic_cast<TH1*>(m_inputHistos[0]->Clone("sumOfTemplates")); 
  sumOfTemplates->Reset("MICE");
  sumOfTemplates->ResetStats();

  for (int i = 0; i < m_numOfParameters; ++i)
  {
    newStack.Add(m_inputHistos[i]);
    sumOfTemplates->Add(m_inputHistos[i]);
  }

  //---------------- Make a modified Pearsons Chi2 Test ---------------- 
  sumOfTemplates->Chi2Test(m_dataHisto,"WUP");


  TCanvas myC(m_filename.c_str(),"",2400,1200);
  myC.Clear();
  myC.Draw();
  myC.Divide(m_numOfParameters,2);

  //---------------- DATA and fitted MC histos ---------------- 
  myC.cd(1);
  newStack.SetMaximum(1.5*newStack.GetMaximum());
  newStack.Draw("BAR");
  m_dataHisto->SetMarkerSize(1.5*m_dataHisto->GetMarkerSize());
  m_dataHisto->SetMarkerStyle(8);
  m_dataHisto->SetStats(0);
  m_dataHisto->Draw("e1same");
  TLegend leg(0.6,0.7,0.92,0.92);
  leg.AddEntry(m_dataHisto,"data","lep");
  for (int i = 0; i < m_numOfParameters; ++i)
  {
    leg.AddEntry(m_inputHistos[i],getMinimizer()->VariableName(i).c_str(),"lep");
  }
  leg.SetFillColor(kWhite);
  leg.SetLineColor(kWhite);
  leg.Draw();

  //---------------- RESUTLS ---------------- 
  myC.cd(2);
  TPaveText mtext(0.2,0.2,.9,.9,"ARC");
  for (int i = 0; i < m_numOfParameters; ++i)
  {
    mtext.AddText(getParameterResult(i,1.).c_str());
  }
  mtext.Draw();
  // myC.cd(3);
  // m_dataHisto->Draw();

  //---------------- TEMPLATES USED ---------------- 
  int CanvasTot = m_numOfParameters*2;
  int CanvasIdx = CanvasTot-m_numOfParameters+1;
  for (int i = 0; i < (m_numOfParameters); ++i,CanvasIdx++)
  {
    myC.cd(CanvasIdx);
    m_inputHistos[i]->Scale(1/m_inputHistos[i]->Integral());
    m_inputHistos[i]->Draw();
  }
    
  myC.Update();
  myC.Print(".eps");

  newFile->Write();
  newFile->Close();
}

std::string FitterResults::HistoResult::getParameterResult(const int& _idx, double _norm=1.){
  std::ostringstream _text;
  double centralValue = 0.;
  if(_idx>=getFunction()->getNumberOfParameters()){
    _text << ">> variable unknown <<";

  }
  else{
    centralValue = _norm*getMinimizer()->X()[_idx];
    _text << getMinimizer()->VariableName(_idx) << " : (";
    _text << centralValue;

    double Up=0;
    double Down=0;
    double rUp=0;
    double rDown=0;

    double Error=getMinimizer()->Errors()[_idx];
    double relError = Error/centralValue;
    int minosStatus = 0;
    getMinosResultsForIndex(_idx,minosStatus,Up,Down);
    if(minosStatus<0){
      _text << " +/- " << centralValue*relError << ")";
     }
     else{
       rUp = Up/centralValue;
       rDown = Down/centralValue;

       _text << "^{" << centralValue*rUp << "}_{"<< centralValue*rDown << "})";
     }
  }
    
  return _text.str();
    
}
