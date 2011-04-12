#pragma once
#ifndef HISTORESULT_H
#define HISTORESULT_H
#include "AbsResult.hh"
#include "TObject.h"
#include <string>


namespace FitterResults {


/**
  * class HistoResult
  * 
  */

class HistoResult : public AbsResult
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
  HistoResult (ROOT::Math::Minimizer* _min=0 , 
               const int& _verb=1,
               const std::string& _text="histoResult.root"):
    AbsResult(_min),
    m_verbosity(_verb),
    m_filename(_text)
  {};

  /**
   * Empty Destructor
   */
  virtual ~HistoResult ( ){};

  

  virtual void print ( );


};
}; // end of package namespace

#endif // HISTORESULT_H
