
#ifndef FITCORE_H
#define FITCORE_H
#include <iomanip>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <stdexcept>

#include "Math/Factory.h"
#include "Math/Functor.h"
#include "Math/Minimizer.h"

#include "TStopwatch.h"
#include "TEnv.h"
#include "THashList.h"



namespace core {
  

  /**
   * class FitCore
   * responsibilities:
   * * load resources from given AbsHisto
   * * create a ROOT::Math::Minimizer as illustrated here:
   * http://root.cern.ch/drupal/content/numerical-minimization
   * * conduct fit
   * * produce results
   */


  template <class Fcn, class Scr, class Res>
  class FitCore
  {
    
  private:
    
    // containing data and templates accessible through interface
    Scr* m_resources;

    // objet to store formatted results into if necessary
    Res* m_result;

    //function to minimize
    Fcn m_fcn;
    
    //configuration map
    std::map<std::string,std::string> m_config;

    //minimizer to use
    ROOT::Math::Minimizer* m_minimizer;

    //config file
    std::string m_configFile;
    TEnv        m_environment;
    /**
     */
    void printConfig ( )
    {
      std::map<std::string,std::string>::const_iterator cfgItr = m_config.begin();
      std::map<std::string,std::string>::const_iterator cfgEnd = m_config.end();
      std::cout << "FitCore:\tusing the following configurations\n";
      for (;cfgItr!=cfgEnd;++cfgEnd)
      {
        std::cout << std::setw(20) << cfgItr->first << "\t"<< std::setw(30) << cfgItr->second << std::endl;
      }
    }

    void loadDataToFunction(){
      std::vector<double> metaData;
      m_resources->getData(metaData);
      m_fcn.setData(metaData);
    };

    void loadTemplatesToFunction(){
      std::vector<std::vector<double> > metaTemplates;
      std::vector<std::vector<double> > metaWeights;
      m_resources->getTemplatesWithWeights(metaTemplates,metaWeights);
      m_fcn.setTemplates(metaTemplates);
      m_fcn.setWeights(metaWeights);
    };

  public:


    /**
     * Empty Constructor
     */
    FitCore (Scr* _sources=0,Res* _results=0 ):
      m_resources(_sources),
      m_result(_results),
      m_fcn(),
      m_config(),
      m_minimizer(0),
      m_configFile(""),
      m_environment()
    {};
    /**
     * Empty Destructor
     */
    virtual ~FitCore ( ){
        //the only ownership we have is on m_minimizer
      delete m_minimizer;m_minimizer=0;
    };

    
    /**
       Stub for later
       * @param  _fileName
       */
    void configureFromFile (const std::string& _fileName = "" ){
      m_configFile = _fileName;
      if(m_environment.ReadFile(_fileName.c_str(),kEnvLocal)<0)
        throw std::invalid_argument(_fileName);
      
      THashList* envTable = m_environment.GetTable();
      TEnvRec* currentEntry=0;
      for (int i = 0; i < envTable->GetEntries(); ++i)
      {
        currentEntry = dynamic_cast<TEnvRec*>(envTable->At(i));
        configureKeyWithValue(currentEntry->GetName(),currentEntry->GetValue());
      }
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
    void setFittingFunction (const Fcn& _function )
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
    void setM_resources ( Scr* new_var )   {
      m_resources = new_var;
    }

    /**
     * Get the value of m_resources
     * containing data and templates accessible through interface
     * @return the value of m_resources
     */
    Scr* getM_resources ( )   {
      return m_resources;
    }

    /**
     * Set the value of m_result
     * objet to store formatted results into if necessary
     * @param new_var the new value of m_result
     */
    void setM_result ( Res* new_var )   {
      m_result = new_var;
    }

    /**
     * Get the value of m_result
     * objet to store formatted results into if necessary
     * @return the value of m_result
     */
    Res* getM_result ( )   {
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

#include "core/FitCore.icc"
#endif // FITCORE_H
