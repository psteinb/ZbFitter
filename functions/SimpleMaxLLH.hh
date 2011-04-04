#ifndef SIMPLEMAXLLH_H
#define SIMPLEMAXLLH_H
#include "functions/AbsFittingFunction.hh"


namespace functions {


/**
  * class SimpleMaxLLH
  * Let's try the simple Likelihood presented in ATL-COM-PHYS-2011-108
  */

class SimpleMaxLLH : virtual public AbsFittingFunction
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
  double operator() (double* _values = 0 )
  {
  }


  /**
   * @param  _data
   */
  void setData (const std::vector<double>& _data )
  {
    m_data = _data;
  }


  /**
   * @param  _parameters
   */
  void setTemplates (const std::vector<std::vector<double> >& _templates ){
    m_templates = _templates;
  }

  /**
   * @param  _weights function to set the weights
   */
  virtual void setWeights (const std::vector<std::vector<double> >& _weights ){
    m_weights = _weights;
  };

  /**
   * @return double
   */
  double up ( )
  {
  }

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

#endif // SIMPLEMAXLLH_H
