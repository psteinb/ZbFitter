#pragma once
#ifndef LLHPVALUE_H
#define LLHPVALUE_H
#include "AbsResult.hh"
#include "TObject.h"
#include <string>

class TGraph;

namespace FitterResults {


/**
  * class LLHPValue
  * 
  */

class LLHPValue : public AbsResult
{
private:

  int m_verbosity;
  std::string m_filename;
  std::string m_resource;
  TFile m_rscFile;
  TH1* m_maxLLH;
  double m_llh;

public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  LLHPValue (ROOT::Math::Minimizer* _min=0 , 
               const int& _verb=1,
	     const std::string& _text="LLHPValue.root",
	     const std::string& _rsc="maxLLH.root"
	     ):
    AbsResult(_min),
    m_verbosity(_verb),
    m_filename(_text),
    m_resource(_rsc),
    m_rscFile(TFile(_rsc.c_str())),
    m_maxLLH(0),
    m_llh(0.)
  {
    m_maxLLH = dynamic_cast<TH1*>(m_rscFile.Get("maxllh")) ;  
  };

  /**
   * Empty Destructor
   */
  virtual ~LLHPValue ( ){};

  

  virtual void print ( );

  void setFileName(const std::string& _text="LLHPValue.root"){m_filename=_text;};
  void setResourceFileName(const std::string& _rsc="LLHPValue.root"){
    m_resource=_rsc;
    if(!m_rscFile.IsZombie())
      m_rscFile.Close();
    m_rscFile = TFile(_rsc.c_str());
    m_maxLLH = dynamic_cast<TH1*>(m_rscFile.Get("maxllh")) ;  
  };
  
  void setLLH(const double& _value=0.){m_llh=_value;};
  // void printTGraphVector(const std::vector<TGraph*>&);
};
}; // end of package namespace

#endif // LLHPVALUE_H
