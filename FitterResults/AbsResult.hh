
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
protected:
  
public:

  //hand the minimizer over to the result, so that all results can be printed nicely
  AbsResult( ROOT::Math::Minimizer* _min=0) : 
    m_minimizer(_min),
    m_function(0)
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

};
}; // end of package namespace

#endif // ABSRESULT_H
