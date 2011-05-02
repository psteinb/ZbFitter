#define BINNEDEMLFRACTION__CC
#include "functions/BinnedEMLFraction.hh"
#include <cmath>
#include "TMath.h"
#include <numeric>


// Constructors/Destructors
//  

functions::BinnedEMLFraction::BinnedEMLFraction ( ) :
  functions::AbsFittingFunction()
{
  
}

functions::BinnedEMLFraction::~BinnedEMLFraction( ) { }

double functions::BinnedEMLFraction::getLogTerm(const short& _bin, const double& _sumData){

  double binWidth = m_templates.at(0).getHisto()->GetBinWidth(1);
  double value =0;  
  int lastButOneIndex = (this->getNumberOfParameters()-1);
  double sumAllParamsButLast = std::accumulate(getParameters()->begin(), 
                                               getParameters()->begin()+lastButOneIndex,
                                               0.,
                                               std::plus<double>()
                                               );

  for (short i=0; i < this->getNumberOfParameters(); ++i)
  {
    if(i<(this->getNumberOfParameters()-1))
      value+=((getParameterValue(i))*(m_templates.at(i).getContent()->at(_bin)));
    else
      value+=((1 - sumAllParamsButLast)*(m_templates.at(i).getContent()->at(_bin)));

  }

  value*=binWidth;
  if(value)
    return std::log(value);
  else
    return 0.;
}

double functions::BinnedEMLFraction::operator()(const double* _values ){

  

  
  setParameters(_values);
  

  double sumOfData = std::accumulate(m_data.getContent()->begin(), 
                                     m_data.getContent()->end(),
                                     0.,
                                     std::plus<double>()
                                     );
  
  
  
  //the likelihood function
  double logLHValue = sumOfData;
  
  
  
  std::vector<double>::const_iterator dataItr = m_data.getContent()->begin();
  std::vector<double>::const_iterator dataEnd = m_data.getContent()->end();
  
  double sumOverAllBins = 0.;
  for (short bin = 0; dataItr!=dataEnd; ++dataItr,++bin)
  {
    sumOverAllBins += ((*dataItr)*this->getLogTerm(bin,sumOfData));
  }
  
  logLHValue += -1.*(sumOverAllBins);

  return (logLHValue);
}


