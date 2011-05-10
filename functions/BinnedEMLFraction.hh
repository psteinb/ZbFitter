#ifndef BINNEDEMLFRACTION_H
#define BINNEDEMLFRACTION_H
#include "functions/AbsFittingFunction.hh"


namespace functions {


  /**
   * class BinnedEMLFraction
   * this class adapts the defintion of a binned Likelihood adapted from Cowan 'Statistical Data Analysis' (1998), p.89
   * the joint PDF is split into a linear sum of all flavor contributions each normalizd to unity
   */

  class BinnedEMLFraction : public AbsFittingFunction
  {
    
    
  public:

    BinnedEMLFraction ( );

    /**
     * Empty Destructor
     */
    virtual ~BinnedEMLFraction ( );


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

  

    double getLogTerm(const short& _bin,const double& _totalExpect );



  };
}; // end of package namespace

#endif // BINNEDEML_H
