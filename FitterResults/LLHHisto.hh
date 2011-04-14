#pragma once
#ifndef LLHHISTO_H
#define LLHHISTO_H
#include "AbsResult.hh"
#include "TObject.h"
#include <string>


namespace FitterResults {


/**
  * class LLHHisto
  * 
  */

class LLHHisto : public AbsResult
{
private:

  int m_verbosity;
  std::string m_filename;

public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  LLHHisto (ROOT::Math::Minimizer* _min=0 , 
               const int& _verb=1,
               const std::string& _text="LLHHisto.root"):
    AbsResult(_min),
    m_verbosity(_verb),
    m_filename(_text)
  {};

  /**
   * Empty Destructor
   */
  virtual ~LLHHisto ( ){};

  

  virtual void print ( );


};
}; // end of package namespace

#endif // LLHHISTO_H
