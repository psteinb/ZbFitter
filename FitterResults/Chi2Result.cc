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

  setupParameters();
  
  setupInputHistos();

  const double *xs = getMinimizer()->X();
  const double *xErrors = getMinimizer()->Errors();
  

  //real work starts here [REFACTOR!]
  //goal: calculate a chi2 over the bins fitted
  //as a first approach, I add up errors
  m_chi2 = 0;
  double data = 0;
  double exp = 0;
  double uncert = 0;
  int emptyBins = 0;
  bool allTemplatesZero = false;
  for (int i = 1; i < m_dataHisto->GetNbinsX(); ++i)
  {
    data = m_dataHisto->GetBinContent(i);
    exp = 0.;
    uncert = 0.;
    allTemplatesZero = true;
    for (int p = 0; i < m_numOfParameters; ++i)
    {
      exp += xs[p]*m_inputHistos[p]->GetBinContent(i);
      uncert += (xErrors[p]*xErrors[p])*(m_inputHistos[p]->GetBinContent(i)*m_inputHistos[p]->GetBinContent(i));
      uncert += (xs[p]*xs[p])*(m_inputHistos[p]->GetBinError(i)*m_inputHistos[p]->GetBinError(i));
    }
    allTemplatesZero = exp;
    
    if(exp){
      m_chi2+= ((data-exp)*(data-exp))/(exp);
      
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

