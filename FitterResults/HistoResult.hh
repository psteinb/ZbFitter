#pragma once
#ifndef HISTORESULT_H
#define HISTORESULT_H
#include "AbsResult.hh"
#include "functions/AbsFittingFunction.hh"
#include "TH1.h"
#include "TFile.h"
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
  std::vector<TH1*> m_inputHistos;
  TH1* m_dataHisto;
  const double* m_results;
  const double* m_resultsSymErrors;
  int m_numOfParameters;

  void cleanUp(){
    // for (int i = 0; i < m_inputHistos.size(); ++i)
    // {
    //   if(m_inputHistos[i])
    //     delete m_inputHistos[i];
    // }
    m_inputHistos.clear();
    delete m_dataHisto;m_dataHisto=0;
  }

  void setupParameters(){
    m_numOfParameters = std::max(getMinimizer()->NDim(),getMinimizer()->NFree());
    cleanUp();
    m_inputHistos.reserve(m_numOfParameters);
    m_results = getMinimizer()->X();
    m_resultsSymErrors = getMinimizer()->Errors();
  };

  void setupInputHistos(){
    TH1* meta = 0;
    for (int i = 0; i < m_numOfParameters; ++i)
    {
      meta = dynamic_cast<TH1*>(getFunction()->getTemplate(i)->getHisto()->Clone(appendToNameString<int>(i).c_str()));
      meta->SetDirectory(0);
      m_inputHistos.push_back(meta);
    }
    m_dataHisto = dynamic_cast<TH1*>(getFunction()->getData()->getHisto()->Clone(appendToNameString<std::string>("_data").c_str()));
    m_dataHisto->SetDirectory(0);
  }

  void treatInputHistosForResult(){
    int color = 2;
    for (int i = 0; i < m_numOfParameters; ++i,color++)
    {
      m_inputHistos[i]->Scale(m_results[i]/m_inputHistos[i]->Integral());
      m_inputHistos[i]->SetFillColor(color);
      m_inputHistos[i]->SetLineColor(color);
      m_inputHistos[i]->SetMarkerColor(color);
    }
  }

  void joinHistosToFile(TFile* _file=0){
    if(_file && !(_file->IsZombie())){
      for (int i = 0; i < m_numOfParameters; ++i)
      {
        m_inputHistos[i]->SetDirectory(_file->GetDirectory("/"));
      }
    }
    else
      std::cerr << __FILE__ << ":" << __LINE__ << "\t file does not exist\n";
  }
  
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
    m_inputHistos(),
    m_dataHisto(0),
    m_results(0),
    m_resultsSymErrors(0),
    m_numOfParameters(0)
  {
    TH1::AddDirectory(kFALSE);
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
