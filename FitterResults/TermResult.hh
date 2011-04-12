#pragma once
#ifndef TERMRESULT_H
#define TERMRESULT_H
#include "AbsResult.hh"
#include "TObject.h"


namespace FitterResults {


/**
  * class TermResult
  * 
  */

class TermResult : public AbsResult
{
private:

  int m_verbosity;

public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  TermResult (ROOT::Math::Minimizer* _min=0 , const int& _verb=1):
    AbsResult(_min),
    m_verbosity(_verb)
  {};

  /**
   * Empty Destructor
   */
  virtual ~TermResult ( ){};



  virtual void print ( );


};
}; // end of package namespace

#endif // TERMRESULT_H
