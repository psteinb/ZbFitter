#ifndef BINNEDEML_H
#define BINNEDEML_H
#include "functions/AbsFittingFunction.hh"


namespace functions {


  /**
   * class BinnedEML
   * this class adapts the defintion of a binned Likelihood adapted from Cowan 'Statistical Data Analysis' (1998), p.89
   * the joint PDF is split into a linear sum of all flavor contributions each normalizd to unity
   */

  class BinnedEML : public AbsFittingFunction
  {
    
    
  public:

    BinnedEML ( );

    /**
     * Empty Destructor
     */
    virtual ~BinnedEML ( );


    /**
     * @return double
     * @param  _values
     */
    double operator()(const double* _values = 0 );
    

    

    /**
     * @return double
     */
    double up() 
    {
      //this is a log likelihood function
      return double(.5);
    }

  

    double getLogTerm(const short& _bin);



  };
}; // end of package namespace

#endif // BINNEDEML_H
