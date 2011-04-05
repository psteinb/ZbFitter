#include "SimpleMaxLLH.hh"
#include <cmath>
#include "TMath.h"
#include <numeric>
#include <functional>



// Constructors/Destructors
//  

functions::SimpleMaxLLH::SimpleMaxLLH ( ) :
  AbsFittingFunction()
{
  
}

functions::SimpleMaxLLH::~SimpleMaxLLH ( ) { }

double functions::SimpleMaxLLH::operator()(double* _values ){

  //_values include all fit parameters
  //[0]: b-fraction
  //[1]: c-fraction
  //[2]: l-fraction
  setParameters(_values);

  double sumData = std::accumulate(getData()->begin(), getData()->end(),0.,std::plus<double>());
  double sumTemp = 0.;
  for (short tidx = 0; tidx < getData()->size(); ++tidx)
  {
    sumTemp += this->getTotalMCFractionPerBin(tidx);
  }

  //the likelihood function
  double value = - (sumData*(std::log(sumTemp))) + sumTemp;
  
  short bin = 0;
  std::vector<double>::const_iterator dataItr = getData()->begin();
  std::vector<double>::const_iterator dataEnd = getData()->end();
  double mcPredictionPerBin = 0.;
  double firstTerm = 0.;
  double secondTerm = 0.;
  for (; dataItr!=dataEnd; ++dataItr,++bin)
  {
    mcPredictionPerBin = this->getTotalMCFractionPerBin(bin);

    firstTerm = (mcPredictionPerBin)*(std::log(mcPredictionPerBin));
    secondTerm = std::log(TMath::Factorial(*dataItr));

    value += (((*dataItr)*firstTerm) + secondTerm);
  }

  return value;
}
