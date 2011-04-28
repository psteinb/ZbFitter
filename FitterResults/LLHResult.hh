#pragma once
#ifndef LLHHISTO_H
#define LLHHISTO_H
#include "AbsResult.hh"
#include "TObject.h"
#include <string>

class TGraph;

namespace FitterResults {


/**
  * class LLHResult
  * 
  */

class LLHResult : public AbsResult
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
  LLHResult (ROOT::Math::Minimizer* _min=0 , 
               const int& _verb=1,
               const std::string& _text="LLHResult.root"):
    AbsResult(_min),
    m_verbosity(_verb),
    m_filename(_text)
  {};

  /**
   * Empty Destructor
   */
  virtual ~LLHResult ( ){};

  

  virtual void print ( );

  void setFileName(const std::string& _text="LLHResult.root"){m_filename=_text;};
  
  void printTGraphVector(const std::vector<TGraph*>&);
};
}; // end of package namespace

#endif // LLHHISTO_H
