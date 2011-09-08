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

double functions::BinnedEMLFraction::getLogTerm(const short& _bin,const double& _total){

  //double binWidth = m_templates.at(0).getHisto()->GetBinWidth(1);
  double value =0;  

  //-1 for the parameter omitted needs to be the last one
  int parameterRange = this->getNumberOfParameters()/*-1*/;

  for (short i=0; i < (parameterRange); ++i)
  {

    value+=((getParameterValue(i))*(m_templates.at(i).getContent()->at(_bin))*_total);

  }

  
  

  //value+=((last)*(m_templates.back().getContent()->at(_bin))*_total);
  
  if(value>0.)
    return std::log(value);
  else
    return 0.;
}

double functions::BinnedEMLFraction::operator()(const double* _values ){

  

  

  setParameters(_values);

  /////////////////////////////////////////
  /// FIXME: this section would need to optimised for I assume (hard-coded) that the last parameter is in "omitted" state
  /////////////////////////////////////////

  int parameterRange = this->getNumberOfParameters()-1;
  double last = std::accumulate(getParameters()->begin(), 
                                getParameters()->begin()+parameterRange,
                                1.,
                                std::minus<double>());

  
  setParameterValue(parameterRange,std::fabs(last));
  
  double sumOfParameters = std::accumulate(getParameters()->begin(), 
                                           getParameters()->end(),
                                           0.);
  
  /////////////////////////////////////////
  /// FIXME: safe-guard against the minimization to violate unitarity of all fractions
  /////////////////////////////////////////

  // if(last<0 || sumOfParameters>1)
  //   return 0.;
  /////////////////////////////////////////
  /// start the computation of the LLH

  double totalData = std::accumulate(m_data.getContent()->begin(), 
                                     m_data.getContent()->end(),
                                     0.);

  //the likelihood function
  double logLHValue = 0.;
  
  
  
  std::vector<double>::const_iterator dataItr = m_data.getContent()->begin();
  std::vector<double>::const_iterator dataEnd = m_data.getContent()->end();
  
  double sumOverAllBins = 0.;
  for (short bin = 0; dataItr!=dataEnd; ++dataItr,++bin)
  {
    sumOverAllBins += ((*dataItr)*this->getLogTerm(bin,totalData));
  }
  
  logLHValue += (-1.*(sumOverAllBins));

  //Roots interface seem not to pick up the predefined up function returning .5
  //according to the TMinuit2 manual, one may instead double the LLH to get correct errors
  logLHValue *= 2;

#ifdef __DEBUG_EML___  
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


