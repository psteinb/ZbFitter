
#ifndef FITRUNNER_H
#define FITRUNNER_H
#include <iomanip>
#include <string>
#include <sstream>
#include <map>
#include <vector>

#include "Math/Minimizer.h"


namespace FitterResults{

  class AbsResult;

};
namespace FitterInputs{

  class AbsHisto;

};

namespace functions{

  class AbsFittingFunction;

};

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

  private:

    // containing data and templates accessible through interface
    FitterInputs::AbsHisto* m_resources;

    // objet to store formatted results into if necessary
    FitterResults::AbsResult* m_result;

    //function to minimize
    functions::AbsFittingFunction m_fcn;
    
    //configuration map
    std::map<std::string,std::string> m_config;

    //minimizer to use
    ROOT::Math::Minimizer* m_minimizer;

    //config file
    std::string m_configFile;

    /**
     */
    void printConfig ( )
    {
      std::map<std::string,std::string>::const_iterator cfgItr = m_config.begin();
      std::map<std::string,std::string>::const_iterator cfgEnd = m_config.end();
      std::cout << "FitRunner:\tusing the following configurations\n";
      for (;cfgItr!=cfgEnd;++cfgEnd)
      {
        std::cout << std::setw(20) << cfgItr->first << "\t"<< std::setw(30) << cfgItr->second << std::endl;
      }
    }


  public:


    /**
     * Empty Constructor
     */
    FitRunner ( );

    /**
     * Empty Destructor
     */
    virtual ~FitRunner ( );

    
    /**
       Stub for later
       * @param  _fileName
       */
    void configureFromFile (const std::string& _fileName = "" ){
      m_configFile = _fileName;
    };

    /**
     * apply the available configuration to all attributes necessary
     * 
     */
    void setupMachinery();

    /**
     * @param  _verbosity
     */
    void fit (const bool& );


    /**
     * @param  _function
     */
    void setFittingFunction (const functions::AbsFittingFunction& _function )
    {
      m_fcn = _function;
    }


    /**
     * @return bool
     * @param  _name
     */
    bool isConfigured (const std::string& _name ) const
    {
      std::map<std::string,std::string>::const_iterator cfgItr = m_config.find(_name);
      if(cfgItr!=m_config.end())
        return true;
      else
        return false;
    }

    /**
     * set the configuration directly
     * @return bool
     * @param  _name
     */
    bool configureKeyWithValue (const std::string& _key, const std::string& _value )
    {
      m_config[_key] = _value;
    }
    

    /**
     * Set the value of m_resources
     * containing data and templates accessible through interface
     * @param new_var the new value of m_resources
     */
    void setM_resources ( FitterInputs::AbsHisto* new_var )   {
      m_resources = new_var;
    }

    /**
     * Get the value of m_resources
     * containing data and templates accessible through interface
     * @return the value of m_resources
     */
    FitterInputs::AbsHisto* getM_resources ( )   {
      return m_resources;
    }

    /**
     * Set the value of m_result
     * objet to store formatted results into if necessary
     * @param new_var the new value of m_result
     */
    void setM_result ( FitterResults::AbsResult* new_var )   {
      m_result = new_var;
    }

    /**
     * Get the value of m_result
     * objet to store formatted results into if necessary
     * @return the value of m_result
     */
    FitterResults::AbsResult getM_result ( )   {
      return m_result;
    }

    ROOT::Math::Minimizer* getMinimizer(){return m_minimizer;}

    int getIntFromString(const std::string& _text){
      int value =0;
      std::istringstream inNumber;inNumber.str(_text);
      if(!(inNumber>>value) ){
        std::cerr << "couldn't convert "<<_text<<" to int\n";
        return 0;
      }
      else
        return value;
    }
    
    double getDoubleFromString(const std::string& _text){
      double value =0;
      std::istringstream inNumber;inNumber.str(_text);
      if(!(inNumber>>value) ){
        std::cerr << "couldn't convert "<<_text<<" to double\n";
        return 0;
      }
      else
        return value;
    }

  };
}; // end of package namespace

#endif // FITRUNNER_H
