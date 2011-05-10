#define LLHRESULT_CC
#include <sstream>

#include "FitterResults/LLHPValue.hh"
#include "functions/AbsFittingFunction.hh"

//#include "TCanvas.h"
#include "TMath.h"
#include "TAxis.h"
#include "TFile.h"

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
  int lowBound =0;int highBound =0;
  integrationBoundsForMaxLLH(minValue,lowBound,highBound);
  
  double lowIntErr = 0;
  double lowInt = m_maxLLH->IntegralAndError(m_maxLLH->GetXaxis()->GetFirst(),lowBound,lowIntErr);
  
  double highIntErr = 0;
  double highInt = m_maxLLH->IntegralAndError(highBound,m_maxLLH->GetXaxis()->GetLast(),highIntErr);

  m_pValue = (highInt + lowInt)/m_maxLLH->Integral();
  m_pValueError = TMath::Sqrt((lowIntErr*lowIntErr) + (highIntErr*highIntErr))/m_maxLLH->Integral();

  //std::cout << "pValue Analysis\n\tp: "<<m_pValue << " +/- " << m_pValueError << std::endl;
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

