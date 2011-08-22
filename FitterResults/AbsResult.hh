
#ifndef ABSRESULT_H
#define ABSRESULT_H
#include "Math/Minimizer.h"
#include "functions/AbsFittingFunction.hh"
#include "TColor.h"
#include "TH1.h"
#include "TROOT.h"


class TObject;

namespace functions{
  
  class AbsFittingFunction;

};

namespace FitterResults {


class AbsResult
{
  ROOT::Math::Minimizer* m_minimizer;
   functions::AbsFittingFunction* m_function;

  bool m_doFractions;
  int m_numOfParameters;
  std::vector<std::string>      m_parameterNames	;
  std::vector<double> 		m_fitResults		;
  std::vector<double> 		m_fitSymmErrors		;
  std::vector<double> 		m_minosUp		;
  std::vector<double> 		m_minosDown		;
  std::vector<int>    		m_minosStatus		;
  std::vector<TH1*>    		m_templatesScaled	;

  std::vector<int>    		m_colors		;

protected:
  
public:

  //hand the minimizer over to the result, so that all results can be printed nicely
  AbsResult( ROOT::Math::Minimizer* _min=0) : 
    m_minimizer(_min),
    m_function(0),
    m_doFractions(false),
    m_numOfParameters(0),
    m_parameterNames(),        
    m_fitResults(),            
    m_fitSymmErrors(),         
    m_minosUp(),    
    m_minosDown(),  
    m_minosStatus(),
    m_templatesScaled(),
    m_colors()
  {
    
    int colors[] = {kRed,kGreen,kWhite,TColor::GetColor(255,255,153),
                    kPink,kTeal,kMagenta,kSpring,
                    kViolet,kYellow,kBlue,kOrange};
    m_colors.clear();
    m_colors.resize(16);
    m_colors.assign(colors,colors+16);

  };

  //we don't take owner ship, we just want to read values
  ~AbsResult(){};

  /**
     print method to save all results to disc / print them to the screen / ...
   */
  virtual void print ( ) = 0;

  /**
     utility method to scale all templates to the fitted values
   */
  virtual void setupHistos();

  /////////////////////////////////////////
  /// getter/setters

  //setter for minimizer
  void setMinimizer( ROOT::Math::Minimizer* _min=0){m_minimizer = _min;};
  //getter for minimizer
  ROOT::Math::Minimizer* getMinimizer(){ return m_minimizer;};

  //setter for function
  void setFunction( functions::AbsFittingFunction* _new=0){m_function = _new;};
  //getter for function
  functions::AbsFittingFunction* getFunction(){ return m_function;};


  void setResults(const std::vector<double>& _new){
    m_fitResults = _new;
    m_numOfParameters = m_fitResults.size();
  }

  void setSymmErrors(const std::vector<double>& _new){
    m_fitSymmErrors = _new;
  }

  void setParameterNames(const std::vector<std::string>& _new){
    m_parameterNames = _new;
  }

  const std::vector<double>* getResults() const {
    return &m_fitResults;
  }

  const std::vector<double>* getSymmErrors() const {
    return &m_fitSymmErrors;
  }

  const std::vector<std::string>* getParameterNames() const {
    return &m_parameterNames;
  }
  
  const std::vector<TH1*>* getScaledTemplateHistograms() const {
    return &m_templatesScaled;
  }

  int getNumberOfParameters() const {
    return m_numOfParameters;
  }

  void doFractions(const bool& _value=true){m_doFractions = _value;};
  bool isFractionFit() const {return m_doFractions;};
  
  void setMinosResults(const std::vector<int>& _status,
                  const std::vector<double>& _up,
                  const std::vector<double>& _down){
    m_minosStatus = _status;
    m_minosUp     = _up;
    m_minosDown   = _down;
  }

  void getMinosResults(std::vector<int>& _status,
                  std::vector<double>& _up,
                  std::vector<double>& _down){
    _status  =     m_minosStatus	;
    _up      =     m_minosUp    ;
    _down    =     m_minosDown  ;
  }
  
  void getMinosResultsForIndex(const int& _idx,
                               int& _status,
                               double& _up,
                               double& _down                               ){
    if(_idx<m_minosStatus.size()){
      _status  =     m_minosStatus.at(_idx)	;
      _up      =     m_minosUp    .at(_idx);
      _down    =     m_minosDown  .at(_idx);
    }
    else{
      _status  =     -500	;
      _up      =     -500;
      _down    =     -500;
    }
      

   
  };

   int getColor(const int& _index){
      int value = 0;
      try{
        value = m_colors.at(_index);
      }
      catch(std::exception& _exc){
        value = kAzure;
      }
      return value;
   };

};
}; // end of package namespace

#endif // ABSRESULT_H
