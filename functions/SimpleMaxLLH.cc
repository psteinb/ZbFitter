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

double functions::SimpleMaxLLH::getMCPredictionOfBin(const short& _bin){

  //total MC prediction for this bin
  double total = 0;
  for (short i=0; i < this->getNumberOfParameters(); ++i)
  {
    total += (m_templates.at(i).getHisto()->GetBinContent(_bin+1));
  }

  double value =0;  
  for (short i=0; i < this->getNumberOfParameters(); ++i)
  {
    value+=((getParameterValue(i))*(m_templates.at(i).getContent()->at(_bin)))*total;
    //value+=(getParameterValue(i))*total;
  }
  
  return value;
}

double functions::SimpleMaxLLH::operator()(const double* _values ){

  //_values include all fit parameters
  //[0]: b-fraction
  //[1]: c-fraction
  //[2]: l-fraction
  setParameters(_values);
  
  //I set this by hand for testing, the following is the Lumi normalisation factor
  // for NNLO Z+jets at 7TeV for 35.484pb-1 of data 

  
  //total number of events found in data
  double sumData = std::accumulate(m_data.getContent()->begin(), 
                                   m_data.getContent()->end(),
                                   0.,
                                   std::plus<double>()
                                   );
  
  //the expected number of events
  double sumTemp = 0.;
  for (short tidx = 0; tidx < m_data.getContent()->size(); ++tidx)
  {
    sumTemp += (this->getMCPredictionOfBin(tidx));
  }

  //the likelihood function
  double logLHValue = - (sumData*(std::log(sumTemp))) + sumTemp;
  
  short bin = 0;
  std::vector<double>::const_iterator dataItr = m_data.getContent()->begin();
  std::vector<double>::const_iterator dataEnd = m_data.getContent()->end();
  double mcPredictionPerBin = 0.;

  double binSum =0;
  for (; dataItr!=dataEnd; ++dataItr,++bin)
  {
    
    mcPredictionPerBin = this->getMCPredictionOfBin(bin);
    

    if(!(mcPredictionPerBin!=0))
      continue;

    //the dataTerm does not depend on beta, so we may drop it
    binSum += (mcPredictionPerBin - ((*dataItr)*std::log(mcPredictionPerBin)));
               
  }
  
  logLHValue += binSum;
  //std::cout << "LLH: "<< logLHValue << std::endl;
  return (logLHValue);
}


