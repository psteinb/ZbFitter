
#ifndef FITRUNNER_H
#define FITRUNNER_H

#include <string>

namespace core {


/**
  * class FitRunner
  * responsibilities:
  * * load resources from given AbsHisto
  * * create a ROOT::Math::Minimizer as illustrated here:
  * http://root.cern.ch/drupal/content/numerical-minimization
  * * conduct fit
  * * produce results
  */

class FitRunner
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  FitRunner ( );

  /**
   * Empty Destructor
   */
  virtual ~FitRunner ( );

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * @param  _fileName
   */
  void configureFromFile (std::string _fileName = "" )
  {
  }


  /**
   * @param  _verbosity
   */
  void fit (bool _verbosity )
  {
  }


  /**
   * @param  _function
   */
  void setFittingFunction (functions::AbsFittingFunction _function )
  {
  }


  /**
   * @return bool
   * @param  _name
   */
  bool isConfigured (std::string _name )
  {
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

  // containing data and templates accessible through interface
  FitterInputs::AbsHisto m_resources;
  // objet to store formatted results into if necessary
  core::AbsResult m_result;
  functions::AbsFittingFunction m_fcn;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of m_resources
   * containing data and templates accessible through interface
   * @param new_var the new value of m_resources
   */
  void setM_resources ( FitterInputs::AbsHisto new_var )   {
      m_resources = new_var;
  }

  /**
   * Get the value of m_resources
   * containing data and templates accessible through interface
   * @return the value of m_resources
   */
  FitterInputs::AbsHisto getM_resources ( )   {
    return m_resources;
  }

  /**
   * Set the value of m_result
   * objet to store formatted results into if necessary
   * @param new_var the new value of m_result
   */
  void setM_result ( core::AbsResult new_var )   {
      m_result = new_var;
  }

  /**
   * Get the value of m_result
   * objet to store formatted results into if necessary
   * @return the value of m_result
   */
  core::AbsResult getM_result ( )   {
    return m_result;
  }

  /**
   * Set the value of m_fcn
   * @param new_var the new value of m_fcn
   */
  void setM_fcn ( functions::AbsFittingFunction new_var )   {
      m_fcn = new_var;
  }

  /**
   * Get the value of m_fcn
   * @return the value of m_fcn
   */
  functions::AbsFittingFunction getM_fcn ( )   {
    return m_fcn;
  }
private:



  /**
   */
  void printConfig ( )
  {
  }

  void initAttributes ( ) ;

};
}; // end of package namespace

#endif // FITRUNNER_H
