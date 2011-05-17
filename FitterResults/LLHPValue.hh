#pragma once
#ifndef LLHPVALUE_H
#define LLHPVALUE_H
#include "AbsResult.hh"
#include "TObject.h"
#include <string>
#include "TFile.h"
#include "TH1D.h"

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
  TFile* m_rscFile;
  TH1* m_maxLLH;
  double m_pValue       ;
  double m_pValueError  ;

  TH1* createIntegralOverlay(const int& _start=1);

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
    m_rscFile(TFile::Open(_rsc.c_str())),
    m_maxLLH(0),
    m_pValue(0.),       
    m_pValueError(0.)  
  {
    if(!m_rscFile->IsZombie()){
      m_maxLLH = dynamic_cast<TH1*>(m_rscFile->Get("maxLLH")) ;  
    
    }
  };

  /**
   * Empty Destructor
   */
  virtual ~LLHPValue ( ){
    m_rscFile->Close();
    delete m_rscFile;m_rscFile=0;
  };

  

  virtual void print ( );

  void setFileName(const std::string& _text="LLHPValue.root"){m_filename=_text;};
  void setResourceFileName(const std::string& _rsc="LLHPValue.root"){
    m_resource=_rsc;
    if(!m_rscFile->IsZombie())
      m_rscFile->Close();
    m_rscFile = TFile::Open(_rsc.c_str());
    if(!m_rscFile->IsZombie()){
      m_maxLLH = dynamic_cast<TH1*>(m_rscFile->Get("maxllh")) ;  
      m_maxLLH->Sumw2();
      //m_maxLLH -> Scale(1/m_maxLLH->Integral());
    }
  };

  void calculate();

  void getResult(double& _value, double& _error){
    _value = m_pValue;
    _value = m_pValueError;
  };

};
}; // end of package namespace

#endif // LLHPVALUE_H
