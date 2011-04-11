#define SIMPLEMAXLLH__CC
#include "functions/SimpleMaxLLH.hh"
#include <cmath>
#include "TMath.h"
#include <numeric>
//#include <functional>
//#include <utility>
//#include <algorithm>




// Constructors/Destructors
//  

functions::SimpleMaxLLH::SimpleMaxLLH ( ) :
  functions::AbsFittingFunction()
{
  
}

functions::SimpleMaxLLH::~SimpleMaxLLH( ) { }

double functions::SimpleMaxLLH::operator()(const double* _values ){

  //_values include all fit parameters
  //[0]: b-fraction
  //[1]: c-fraction
  //[2]: l-fraction
  setParameters(_values);

  double sumData = std::accumulate(
                                   m_data.getContent()->begin(), 
                                   m_data.getContent()->end(),
                                   0.,std::plus<double>());
  double sumTemp = 0.;
  for (short tidx = 0; tidx < m_data.getContent()->size(); ++tidx)
  {
    sumTemp += this->getTotalMCFractionPerBin(tidx);
  }

  //the likelihood function
  double value = - (sumData*(std::log(sumTemp))) + sumTemp;
  
  short bin = 0;
  std::vector<double>::const_iterator dataItr = m_data.getContent()->begin();
  std::vector<double>::const_iterator dataEnd = m_data.getContent()->end();
  double mcPredictionPerBin = 0.;

  //  double dataTerm = 0.;
  double binSum =0;
  for (; dataItr!=dataEnd; ++dataItr,++bin)
  {
    mcPredictionPerBin = this->getTotalMCFractionPerBin(bin);

    if(!mcPredictionPerBin)
      continue;

    //    dataTerm = std::log(TMath::Factorial(*dataItr));

    //the dataTerm does not depend on beta, so we may drop it
    binSum += (/*dataTerm +*/ mcPredictionPerBin - ((*dataItr)*std::log(mcPredictionPerBin)));
               
  }

  return (value + binSum);
}


