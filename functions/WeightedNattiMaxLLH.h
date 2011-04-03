
#ifndef WEIGHTEDNATTIMAXLLH_H
#define WEIGHTEDNATTIMAXLLH_H
#include "functions/AbsFittingFunction.h"

#include <string>

namespace functions {


/**
  * class WeightedNattiMaxLLH
  * Likelihood as discussed in arXiv:0803.2711
  */

class WeightedNattiMaxLLH : virtual public AbsFittingFunction
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  WeightedNattiMaxLLH ( );

  /**
   * Empty Destructor
   */
  virtual ~WeightedNattiMaxLLH ( );

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * @param  _values
   */
  void operator_ (double* _values = 0 )
  {
  }


  /**
   * @param  _data
   */
  void setData (std::vector<double> _data )
  {
  }


  /**
   * @param  _parameters
   */
  void setParameters (std::vector<double> _parameters )
  {
  }


  /**
   * @return double
   */
  double up ( )
  {
    {}
  }

protected:

  // Static Protected attributes
  //  

  // Protected attributes
  //  

public:


  // Protected attribute accessor methods
  //  

protected:

public:


  // Protected attribute accessor methods
  //  

protected:


private:

  // Static Private attributes
  //  

  // Private attributes
  //  

  std::vector<double> m_parameters;
  std::vector<double> m_data;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of m_parameters
   * @param new_var the new value of m_parameters
   */
  void setM_parameters ( std::vector<double> new_var )   {
      m_parameters = new_var;
  }

  /**
   * Get the value of m_parameters
   * @return the value of m_parameters
   */
  std::vector<double> getM_parameters ( )   {
    return m_parameters;
  }

  /**
   * Set the value of m_data
   * @param new_var the new value of m_data
   */
  void setM_data ( std::vector<double> new_var )   {
      m_data = new_var;
  }

  /**
   * Get the value of m_data
   * @return the value of m_data
   */
  std::vector<double> getM_data ( )   {
    return m_data;
  }
private:


  void initAttributes ( ) ;

};
}; // end of package namespace

#endif // WEIGHTEDNATTIMAXLLH_H
