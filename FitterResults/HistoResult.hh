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
    m_filename(_text),
    m_filenameCore()
  {
    if(m_filename.find_last_of(".")!=std::string::npos)
      m_filenameCore = m_filename.substr(0,m_filename.find_last_of("."));
    else
      m_filenameCore = m_filename;

  };

  /**
   * Empty Destructor
   */
  virtual ~HistoResult ( ){};

  

  virtual void print ( );

  template<typename T>
  std::string appendToNameString(const T& _value){
    std::ostringstream text;
    text.str(m_filenameCore);
    text << _value;
    return text.str();
  }

  std::string getParameterResult(const int&);
  


  void setFileName(const std::string& _name){
    m_filename = _name;
    if(m_filename.find_last_of(".")!=std::string::npos)
      m_filenameCore = m_filename.substr(0,m_filename.find_last_of("."));
    else
      m_filenameCore = m_filename;
  }
};
}; // end of package namespace

#endif // HISTORESULT_H
