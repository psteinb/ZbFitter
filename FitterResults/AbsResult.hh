
#ifndef ABSRESULT_H
#define ABSRESULT_H
#include "Math/Minimizer.h"

class TObject;

namespace functions{
  
  class AbsFittingFunction;

};

namespace FitterResults {


class AbsResult
{
  ROOT::Math::Minimizer* m_minimizer;
  functions::AbsFittingFunction* m_function;
  std::vector<double> m_minosUp;
  std::vector<double> m_minosDown;
  std::vector<int>    m_minosStatus;

protected:
  
public:

  //hand the minimizer over to the result, so that all results can be printed nicely
  AbsResult( ROOT::Math::Minimizer* _min=0) : 
    m_minimizer(_min),
    m_function(0),
    m_minosUp(),    
    m_minosDown(),  
    m_minosStatus()
  {};

  //we don't take owner ship, we just want to read values
  ~AbsResult(){};

  //getter/setter for minimizer
  void setMinimizer( ROOT::Math::Minimizer* _min=0){m_minimizer = _min;};
   ROOT::Math::Minimizer* getMinimizer(){ return m_minimizer;};

  //getter/setter for function
  void setFunction( functions::AbsFittingFunction* _min=0){m_function = _min;};
   functions::AbsFittingFunction* getFunction(){ return m_function;};

  /**
     print method to save all results to disc / print them to the screen / ...
   */
  virtual void print ( ) = 0;
  
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
};
}; // end of package namespace

#endif // ABSRESULT_H
