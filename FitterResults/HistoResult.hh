#pragma once
#ifndef HISTORESULT_H
#define HISTORESULT_H
#include "AbsResult.hh"
#include "TObject.h"
#include <string>
#include <sstream>

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
  std::string m_filenameCore;



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
  {

  };

  /**
   * Empty Destructor
   */
  virtual ~HistoResult ( ){};

  

  virtual void print ( );

  template<typename T>
  std::string appendToNameString(const T& _value){
    std::ostringstream text;
    text.str(m_filename);
    text << _value;
    return text.str();
  }

  std::string getParameterResult(const int&,double);
  


  void setFileName(const std::string& _name){
    m_filename = _name;
  }
};
}; // end of package namespace

#endif // HISTORESULT_H
