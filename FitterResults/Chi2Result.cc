#include "Chi2Result.hh"


#include "TMath.h"






void FitterResults::Chi2Result::calculate(){

  
  if(!getMinimizer()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no minimizer given!\n";
    return;
  }



  if(!getFunction()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no function given!\n";
    return;
  }
  m_dataHisto = getFunction()->getData()->getHisto();
  
  
  setupHistos();


  //real work starts here [REFACTOR!]
  //goal: calculate a chi2 over the bins fitted
  //as a first approach, I add up errors
  m_chi2 = 0;
  double data = 0;
  double exp = 0;
  double uncert = 0;
  int emptyBins = 0;

  double fitted =0;
  double fittedSymmError =0;
  double scaledSymmError =0;

  double dataIntegral = m_dataHisto->Integral();

  for (int i = 1; i < m_dataHisto->GetNbinsX(); ++i)
  {
    data = m_dataHisto->GetBinContent(i);
    exp = 0.;
    uncert = 0.;

    for (int p = 0; i < getNumberOfParameters(); ++i)
    {
      fitted = getResults()->at(p);
      fittedSymmError = getSymmErrors()->at(p);
      scaledSymmError = (fittedSymmError/fitted)*getScaledTemplateHistograms()->at(p)->GetBinContent(i);
      exp += getScaledTemplateHistograms()->at(p)->GetBinContent(i);

      if(isFractionFit()){
        uncert += scaledSymmError*scaledSymmError*dataIntegral*dataIntegral;
      }
      else{
        uncert += scaledSymmError*scaledSymmError;
      }


    }

    
    if(exp){
      m_chi2+= ((data-exp)*(data-exp))/(uncert);
      
    }
    else
    {
      emptyBins++;
    }

  }
  
  m_ndf = m_dataHisto->GetNbinsX() - getMinimizer()->NFree() - emptyBins;
  m_chi2prob = TMath::Prob(m_chi2,m_ndf);

}


void FitterResults::Chi2Result::print(){
    
  this->calculate();
    
  std::cout << "chi2 of LLH fitted bins\n";
  std::cout << "chi2 = "<< m_chi2<<"\n";
  std::cout << "ndf = "<<m_ndf <<"\n";
  std::cout << "chi2/ndf = "<< m_chi2/m_ndf <<" (N(bins)-N(Parameters)-N(bins w/ 0 in data & expectations)\n";
  std::cout << "chi2 prob = "<< m_chi2prob <<"\n";
}

