#define BINNEDEMLFRACTION__CC
#include "functions/BinnedEMLFraction.hh"
#include <cmath>
#include "TMath.h"
#include <numeric>
#include <iterator>


// Constructors/Destructors
//  

functions::BinnedEMLFraction::BinnedEMLFraction ( ) :
  functions::AbsFittingFunction()
{
  
}

functions::BinnedEMLFraction::~BinnedEMLFraction( ) { }

double functions::BinnedEMLFraction::getLogTerm(const short& _bin,const double& _totalExpect){

  //double binWidth = m_templates.at(0).getHisto()->GetBinWidth(1);
  double value =0;  

  for (short i=0; i < this->getNumberOfParameters()-1; ++i)
  {

    value+=((getParameterValue(i))*(m_templates.at(i).getContent()->at(_bin))*_totalExpect);

  }

  double last = std::accumulate(getParameters()->begin(), 
                                getParameters()->begin()+this->getNumberOfParameters()-1,
                                1.,
                                std::minus<double>());

  value+=((last)*(m_templates.at(this->getNumberOfParameters()-1).getContent()->at(_bin))*_totalExpect);

  if(value)
    return std::log(value);
  else
    return 0.;
}

double functions::BinnedEMLFraction::operator()(const double* _values ){

  

  
  setParameters(_values);
  

  double sumOfParameters = std::accumulate(getParameters()->begin(), 
					   getParameters()->end(),
					   0.);

  double totPrediction = 0;
  for (int i = 0; i < m_templates.size(); ++i)
  {
    totPrediction += std::accumulate(m_templates.at(i).getContent()->begin(), 
                                    m_templates.at(i).getContent()->end(),
                                    0.);
  }
  

  
  //the likelihood function
  double logLHValue = totPrediction;
  
  
  
  std::vector<double>::const_iterator dataItr = m_data.getContent()->begin();
  std::vector<double>::const_iterator dataEnd = m_data.getContent()->end();
  
  double sumOverAllBins = 0.;
  for (short bin = 0; dataItr!=dataEnd; ++dataItr,++bin)
  {
    sumOverAllBins += ((*dataItr)*this->getLogTerm(bin,totPrediction));
  }
  
  logLHValue += (-1.*(sumOverAllBins));

  //Roots interface seem not to pick up the predefined up function returning .5
  //according to the TMinuit2 manual, one may instead double the LLH to get correct errors
  logLHValue *= 2;

#ifdef __DEBUG_EML__  
  std::cout << "for parameters: \t";
  std::copy(getParameters()->begin(),
            getParameters()->end(),
            std::ostream_iterator<double>(std::cout,", "));
  std::cout << " == " << sumOverAllBins
            <<"\n\tLLH:\t\t" << logLHValue 
            << std::endl;
#endif

  return (logLHValue);
}


