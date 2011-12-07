
#ifndef FITCORE_H
#define FITCORE_H
#include <iomanip>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <stdexcept>
#include <numeric>

#include "Math/Factory.h"
#include "Math/Functor.h"
#include "Math/Minimizer.h"
#include "Minuit2/Minuit2Minimizer.h"
#include "TMath.h"


#include "TStopwatch.h"
#include "TEnv.h"
#include "THashList.h"

#include "core/MinimizerConfiguration.hh"
#include "functions/AbsFittingFunction.hh"



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
    std::map<std::string,std::string> m_configMap;
    MinimizerConfiguration m_paramConfiguration;
    
    //minimizer to use
    ROOT::Math::Minimizer* m_minimizer;

    //config file
    std::string m_configFile;
    TEnv        m_environment;
    
    //minos errors
    std::vector<int>    m_minosStatus		;
    std::vector<double> m_fitResults		;
    std::vector<double> m_fitSymmErrors		;
    std::vector<double> m_minosUp		;
    std::vector<double> m_minosDown		;


    void printConfig ( )
    {
      std::map<std::string,std::string>::const_iterator cfgItr = m_configMap.begin();
      std::map<std::string,std::string>::const_iterator cfgEnd = m_configMap.end();
      std::cout << "FitCore:\tusing the following configurations\n";
      for (;cfgItr!=cfgEnd;++cfgEnd)
      {
        std::cout << std::setw(20) << cfgItr->first << "\t"<< std::setw(30) << cfgItr->second << std::endl;
      }
    }

    void print() const;


    void loadDataToFunction(){
      m_fcn.setupFromInput(m_resources);
      m_fcn.setNumberOfFixedParameters(m_paramConfiguration.getNumberOfParametersFixed());
    };

    void runMinos();

    void calculateOmittedParameters();

    void collectResults(){
      m_fitResults.clear();
      m_fitResults.resize(m_paramConfiguration.getNumberOfParameters(),0.);

      m_fitSymmErrors.clear();
      m_fitSymmErrors.resize(m_paramConfiguration.getNumberOfParameters(),0.);

      std::copy(m_minimizer->X(),
                m_minimizer->X()+m_paramConfiguration.getNumberOfParametersConfigured(),
                m_fitResults.begin());
      
      std::copy(m_minimizer->Errors(),
                m_minimizer->Errors()+m_paramConfiguration.getNumberOfParametersConfigured(),
                m_fitSymmErrors.begin());

    };

  public:


    /**
     * Empty Constructor
     */
    FitCore (Scr* _sources=0,Res* _results=0 ):
      m_resources(_sources),
      m_result(_results),
      m_fcn(),
      m_configMap(),
      m_paramConfiguration(),
      m_minimizer(0),
      m_configFile(""),
      m_environment(),
      m_minosStatus(),
      m_fitResults(),
      m_fitSymmErrors(),
      m_minosUp(),
      m_minosDown()
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
    int fit (const bool& );
    
    void printTo(Res*);
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
      std::map<std::string,std::string>::const_iterator cfgItr = m_configMap.find(_name);
      if(cfgItr!=m_configMap.end())
        return true;
      else
        return false;
    }

    std::string getConfigured (const std::string& _name ) const
    {
      std::map<std::string,std::string>::const_iterator cfgItr = m_configMap.find(_name);
      if(cfgItr!=m_configMap.end())
        return (cfgItr->second);
      else
        return "";
    }

    /**
     * set the configuration directly
     * @return bool
     * @param  _name
     */
    bool configureKeyWithValue (const std::string& _key, const std::string& _value )
    {
      m_configMap[_key] = _value;
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
    const Fcn* getFunction() const {return &m_fcn;}

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


    int getMinosError(const int& _idx, double& _Down, double& _Up){
      _Down = m_minosDown.at(_idx);
      _Up   = m_minosUp.at(_idx);
      return m_minosStatus.at(_idx);
    }
    
    void getMinosErrorSet(std::vector<int>& _Status, 
                          std::vector<double>& _Down, 
                          std::vector<double>& _Up){

      _Down.clear();_Down.reserve(m_minosDown.size());
      _Up.clear();_Up.reserve(m_minosUp.size());
      _Status.clear();_Status.reserve(m_minosStatus.size());

      _Down.assign(m_minosDown.begin(),m_minosDown.end());
      _Up.assign(m_minosUp.begin(),m_minosUp.end());
      _Status.assign(m_minosStatus.begin(),m_minosStatus.end());
      


    }

    const std::vector<double>* getFitResults() const{
      return &m_fitResults;
    }

    const std::vector<double>* getFitSymmetricErrors() const{
      return &m_fitSymmErrors;
    }

    const std::vector<std::string>* getParameterNames() const{
      return m_paramConfiguration.getConfiguredNames();
    }

    MinimizerConfiguration* getConfiguration() {
      return &m_paramConfiguration;
    }

  };
}; // end of package namespace

#include "core/FitCore.icc"
#endif // FITCORE_H
