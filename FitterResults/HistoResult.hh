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
  TH1* m_dataHisto;


  void treatInputHistosForResult(){

    for (int i = 0; i < getNumberOfParameters(); ++i)
    {
      getScaledTemplateHistograms()->at(i)->SetFillColor(this->getColor(i));
      getScaledTemplateHistograms()->at(i)->SetLineColor(kBlack);
      //getScaledTemplateHistograms()->at(i)->SetMarkerColor(this->getColor(i));
      getScaledTemplateHistograms()->at(i)->SetDrawOption("HIST");
    }
  }

  void joinHistosToFile(TFile* _file=0){
    if(_file && !(_file->IsZombie())){
      TH1* meta=0;
      std::string dirname;
      for (int i = 0; i < getNumberOfParameters(); ++i)
      {
        if(getScaledTemplateHistograms()->at(i)->GetDirectory())
         dirname = getScaledTemplateHistograms()->at(i)->GetDirectory()->GetPath();
        else
          dirname = "";

        if(dirname.empty())
          getScaledTemplateHistograms()->at(i)->SetDirectory(_file->GetDirectory("/"));
        else{
          std::cout << __FILE__ << ":" << __LINE__ << "histo named ("<<getScaledTemplateHistograms()->at(i)->GetName() << ") already has a file, cloning it!\n" ;
          std::string newname = getScaledTemplateHistograms()->at(i)->GetName();
          newname += "_Result";
          
          meta = dynamic_cast<TH1*>(getScaledTemplateHistograms()->at(i)->Clone("newname"));
          meta->SetDirectory(_file->GetDirectory("/"));
        }
      }
      if(m_dataHisto)
        m_dataHisto->SetDirectory(_file->GetDirectory("/"));
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
    m_dataHisto(0)
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

  std::string getParameterResult(const int& _idx,const double& _norm=1.);
  


  void setFileName(const std::string& _name){
    m_filename = _name;
  }
};
}; // end of package namespace

#endif // HISTORESULT_H
