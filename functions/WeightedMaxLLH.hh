
#ifndef WEIGHTEDMAXLLH_H
#define WEIGHTEDMAXLLH_H
#include "functions/AbsFittingFunction.hh"

#include <string>

namespace functions {


/**
  * class WeightedMaxLLH
  * simple Likelihood presented in ATL-COM-PHYS-2011-108 including correction for
  * weights as in Froedesen
  */

class WeightedMaxLLH : virtual public AbsFittingFunction
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  WeightedMaxLLH ( );

  /**
   * Empty Destructor
   */
  virtual ~WeightedMaxLLH ( );

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * @return double
   * @param  _values
   */
  double operator_ (double* _values = 0 )
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

#endif // WEIGHTEDMAXLLH_H
