#ifndef SIMPLEMAXLLH_H
#define SIMPLEMAXLLH_H
#include "functions/AbsFittingFunction.hh"


namespace functions {


  /**
   * class SimpleMaxLLH
   * Let's try the simple Likelihood presented in ATL-COM-PHYS-2011-108 without constrains for the moment which is in principle using Poisson statistics ber bin and adding a total normalisation for the data following the extended LLH approach
   */

  class SimpleMaxLLH : public AbsFittingFunction
  {
  
    
  public:

    SimpleMaxLLH ( );

    /**
     * Empty Destructor
     */
    virtual ~SimpleMaxLLH ( );


    /**
     * @return double
     * @param  _values
     */
    double operator()(const double* _values = 0 );
    


    /**
     * @return double
     */
    double up ( )
    {
      //this is a log likelihood function
      return 0.5;
    }
  

    inline double getTotalMCFractionPerBin(const short& _bin){
      double value =0;
      
      for (short i=0; i < this->getNumberOfParameters(); ++i)
      {
        value+=((getParameterValue(i))*(getTemplate(i)->at(_bin)));
      }
      
      return value;
    };



  };
}; // end of package namespace

#endif // SIMPLEMAXLLH_H
