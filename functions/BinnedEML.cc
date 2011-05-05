#define BINNEDEML__CC
#include "functions/BinnedEML.hh"
#include <cmath>
#include "TMath.h"
#include <numeric>
#include <iterator>


// Constructors/Destructors
//  

functions::BinnedEML::BinnedEML ( ) :
  functions::AbsFittingFunction()
{
  
}

functions::BinnedEML::~BinnedEML( ) { }

double functions::BinnedEML::getLogTerm(const short& _bin){

  double binWidth = m_templates.at(0).getHisto()->GetBinWidth(1);
  double value =0;  

  for (short i=0; i < this->getNumberOfParameters(); ++i)
  {

    value+=((getParameterValue(i))*(m_templates.at(i).getContent()->at(_bin)));

  }

  //value*=binWidth;
  if(value)
    return std::log(value);
  else
    return 0.;
}

double functions::BinnedEML::operator()(const double* _values ){

  

  
  setParameters(_values);
  

  double sumOfParameters = std::accumulate(getParameters()->begin(), 
					   getParameters()->end(),
					   0.);
  
  //the likelihood function
  double logLHValue = sumOfParameters;
  
  
  
  std::vector<double>::const_iterator dataItr = m_data.getContent()->begin();
  std::vector<double>::const_iterator dataEnd = m_data.getContent()->end();
  
  double sumOverAllBins = 0.;
  for (short bin = 0; dataItr!=dataEnd; ++dataItr,++bin)
  {
    sumOverAllBins += ((*dataItr)*this->getLogTerm(bin));
  }
  
  logLHValue += (-1.*(sumOverAllBins));

  //Roots interface seem not to pick up the predefined up function returning .5
  //according to the TMinuit2 manual, one may instead double the LLH to get correct errors
  logLHValue *= 2;
  
  std::cout << "for parameters: \t";
  std::copy(getParameters()->begin(),
            getParameters()->end(),
            std::ostream_iterator<double>(std::cout,", "));
  std::cout << " == " << sumOverAllBins
            <<"\n\tLLH:\t\t" << logLHValue 
            << std::endl;

  return (logLHValue);
}


