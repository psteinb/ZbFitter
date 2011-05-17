#pragma once
#ifndef CHI2RESULT_H
#define CHI2RESULT_H
#include "AbsResult.hh"
#include "TObject.h"
#include <string>
#include <sstream>
#include "TH1D.h"
#include "functions/AbsFittingFunction.hh"
namespace FitterResults {


/**
  * class Chi2Result
  * 
  */

class Chi2Result : public AbsResult
{
private:

  int m_verbosity;
  std::string m_filename;
  std::string m_filenameCore;

  const TH1* m_dataHisto;

  double m_chi2;
  int m_ndf;
  double m_chi2prob;

  
  
  // template<typename T>
  // std::string appendToNameString(const T& _value){
  //   std::ostringstream text;
  //   text.str(m_filename);
  //   text << _value;
  //   return text.str();
  // }

public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Chi2Result (ROOT::Math::Minimizer* _min=0 , 
               const int& _verb=1,
               const std::string& _text="chi2Result.root"):
    AbsResult(_min),
    m_verbosity(_verb),
    m_filename(_text),
    m_filenameCore()
  {
    if(m_filename.find_last_of(".")!=std::string::npos)
      m_filenameCore = m_filename.substr(0,m_filename.find_last_of("."));
    else
      m_filenameCore = m_filename;
    TH1::AddDirectory(kFALSE);
  };

  /**
   * Empty Destructor
   */
  virtual ~Chi2Result ( ){};

  virtual void print ( );
  
  virtual void calculate( );

  void setFileName(const std::string& _name){
    m_filename = _name;
    if(m_filename.find_last_of(".")!=std::string::npos)
      m_filenameCore = m_filename.substr(0,m_filename.find_last_of("."));
    else
      m_filenameCore = m_filename;
  }

  void getResult(double& _chi2,double& _ndf,double& _prob){
    _chi2 = m_chi2;
    _ndf = m_ndf;
    _prob = m_chi2prob;
  };
};
}; // end of package namespace

#endif // CHI2RESULT_H
