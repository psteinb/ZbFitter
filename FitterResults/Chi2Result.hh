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
  std::vector<TH1*> m_inputHistos;
  TH1* m_dataHisto;
  int m_numOfParameters;
  double m_chi2;
  int m_ndf;
  double m_chi2prob;


  void cleanUp(){
    // for (int i = 0; i < m_inputHistos.size(); ++i)
    // {
    //   if(m_inputHistos[i])
    //     delete m_inputHistos[i];
    // }
    m_inputHistos.clear();
    //    delete m_dataHisto;m_dataHisto=0;
  }

  void setupParameters(){
    m_numOfParameters = std::max(getMinimizer()->NDim(),getMinimizer()->NFree());
    cleanUp();
    m_inputHistos.reserve(m_numOfParameters);
  }
  
  void setupInputHistos(){
    TH1* metaTemplate = 0;
    for (int i = 0; i < m_numOfParameters; ++i)
    {
      metaTemplate = dynamic_cast<TH1*>(getFunction()->getTemplate(i)->getHisto()->Clone(appendToNameString<int>(i).c_str()));
      metaTemplate->SetDirectory(0);
      metaTemplate->Scale(1./metaTemplate->Integral());
      m_inputHistos.push_back(metaTemplate);
    }
    m_dataHisto = dynamic_cast<TH1*>(getFunction()->getData()->getHisto()->Clone(appendToNameString<std::string>("_data").c_str()));
    m_dataHisto->SetDirectory(0);
  }
  
  template<typename T>
  std::string appendToNameString(const T& _value){
    std::ostringstream text;
    text.str(m_filename);
    text << _value;
    return text.str();
  }

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
