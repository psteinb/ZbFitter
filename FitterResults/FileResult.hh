#pragma once
#ifndef FILERESULT_H
#define FILERESULT_H
#include "AbsResult.hh"
#include "functions/AbsFittingFunction.hh"
#include "TH1.h"
#include "TNamed.h"
#include "TFile.h"
#include <string>
#include <sstream>

namespace FitterResults {


/**
  * class FileResult
  * 
  */

class FileResult : public AbsResult
{
private:

  int m_verbosity;
  std::string m_filename;
  std::string m_filenameCore;
  
  std::vector<TNamed*> fileContent;

  // void setDirectoryOfContentTo(TFile* _file=0);
  void addCovarianceFromMinimizer();
  void addCorrelationFromMinimizer();

public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  FileResult (ROOT::Math::Minimizer* _min=0 , 
               const int& _verb=1,
               const std::string& _text="fileResult.root"):
    AbsResult(_min),
    m_verbosity(_verb),
    m_filename(_text),
    fileContent()
  {
    TH1::AddDirectory(kFALSE);
    fileContent.reserve(3);
  };

  /**
   * Empty Destructor
   */
  virtual ~FileResult ( ){
    for (int i = 0; i < fileContent.size(); ++i)
    {
      delete fileContent[i];fileContent[i]=0;
    }
    fileContent.clear();
  };

  virtual void print ( );

  template<typename T>
  std::string appendToNameString(const T& _value){
    std::ostringstream text;
    text.str(m_filename);
    text << _value;
    return text.str();
  }

  // std::string getParameterResult(const int& _idx,const double& _norm=1.);
  //transferring ownership
  void addObjectToSave(TNamed* _object){
    if(!(fileContent.size()<fileContent.capacity()))
      fileContent.reserve(fileContent.capacity()+1);
    
    
    fileContent.push_back(_object);
    
  }
  

  void setFileName(const std::string& _name){
    m_filename = _name;
  }
};
}; // end of package namespace

#endif // FILERESULT_H
