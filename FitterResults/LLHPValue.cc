#define LLHRESULT_CC
#include <sstream>

#include "FitterResults/LLHPValue.hh"
#include "functions/AbsFittingFunction.hh"

#include "TCanvas.h"
#include "TPaveText.h"
#include "TMath.h"
#include "TAxis.h"
#include "TFile.h"

TH1* FitterResults::LLHPValue::createIntegralOverlay(const int& _start){
  
  TH1* value = dynamic_cast<TH1*>(m_maxLLH->Clone("overlay"));
  value->Reset("MICE");
  value->ResetStats();
  value->SetDirectory(0);

  for (int i = 1; i < m_maxLLH->GetNbinsX(); ++i)
  {
    if(i>(_start-1))
      value->SetBinContent(i, m_maxLLH->GetBinContent(i));
  }

  return value;
}

void FitterResults::LLHPValue::calculate(){

  if(!getMinimizer()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no minimizer given!\n";
    return;
  }

  if(!getFunction()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no function given!\n";
    return;
  }

  
  double minValue = getMinimizer()->MinValue();
  
  double IntErr = 0;
  double Int = m_maxLLH->IntegralAndError(m_maxLLH->FindBin(minValue),m_maxLLH->GetXaxis()->GetLast(),IntErr);

  m_pValue = Int/m_maxLLH->Integral();
  m_pValueError = IntErr/m_maxLLH->Integral();

  TH1* overlay = createIntegralOverlay();
  std::string name = m_filename;
  name+="_pValue";
  TCanvas aCanvas(name.c_str(),"",800,600);
  aCanvas.Clear();
  aCanvas.Draw();
  m_maxLLH->Draw();
  overlay->SetFillColor(kBlue);
  overlay->Draw("HISTSAME");

  TPaveText aPave(0.5,0.7,.9,.9,"ARC");
  std::ostringstream pValueString;
  pValueString.str("");
  pValueString << "P(LLH #geq " << minValue <<") = " << Int << " +/- " << IntErr;
  aPave.AddText(pValueString.str().c_str());
  aPave.Draw();
    
  aCanvas.Update();
  aCanvas.Print(".eps");

}


void FitterResults::LLHPValue::print(){

  if(!getMinimizer()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no minimizer given!\n";
    return;
  }

  if(!getFunction()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no function given!\n";
    return;
  }

  this->calculate();

  std::cout << "pValue Analysis\n\tp: "<<m_pValue << " +/- " << m_pValueError << std::endl;

}

