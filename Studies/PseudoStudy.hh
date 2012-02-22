#pragma once
#ifndef __PSEUDOSTUDY_HH__
#define __PSEUDOSTUDY_HH__

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

#include "core/FitCore.hh"
#include "core/MinimizerConfiguration.hh"
#include "FitterInputs/NormedTH1.hh"
#include "FitterResults/HistoResult.hh"
#include "FitterResults/LLHResult.hh"
#include "functions/SimpleMaxLLH.hh"
#include "ProtoCreators.hh"


#include "TRandom3.h"
#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TString.h"
#include "Math/Minimizer.h"

template<
  class InputT,
  class FunctionT=functions::SimpleMaxLLH
  >
class PseudoStudy{

  InputT* m_input;
  FunctionT m_fitter;
  const BaseProtoCreator* m_creator;
  
  std::string m_fitConfigFile       ;
  std::string m_fitEngine       ;
  std::string m_fitMode         ;
  std::string m_baseName;

  std::vector<TH1*> m_templateTH1s;
  TH1* m_total;
  std::vector<TH1*> m_resultTH1s;
  TH1D* m_maxLLH;

  int m_threads;
  int m_iterations;

  TRandom3 m_TRand3;

  std::vector<TH1D> m_pulls;
  std::vector<TH1D> m_bias;
  std::vector<TH1D> m_MigradPulls;
  std::vector<TH1D> m_means;
  std::vector<TH1D> m_sigmas;
  std::vector<std::vector<TH2D> > m_correlations;
  
  std::vector<double> m_expectedValues   ;
  std::vector<double> m_expectedErrors      ;
  double              m_dataIntegral	;

  std::vector<double> m_fitValues;
  std::vector<double> m_fitErrorsUp;
  std::vector<double> m_fitErrorsDown;
  std::vector<int>    m_fitErrorsStatus;
  std::vector<TCanvas*>    m_resultCanvas;
  

  bool m_doPanicPrint;
  int m_verbosity;

  void setupCorrelationResults(const int& _size);

  void treatCorrelationResults(const std::vector<std::string>* _names){

    int _size = _names->size();

    for (int col = 0; col < _size; ++col)
    {
      for (int row = 0; row < _size; ++row)
      {
        m_correlations[col][row].GetXaxis()->SetTitle(_names->at(col).c_str());
        m_correlations[col][row].GetYaxis()->SetTitle(_names->at(row).c_str());
      }
    }
    
  }
  
  void fillCorrelations(){

    int _size = m_fitValues.size();
    for (int col = 0; col < _size; ++col)
    {
      for (int row = 0; row < _size; ++row)
      {
        m_correlations[col][row].Fill(m_fitValues.at(col),m_fitValues.at(row));
      }
    }
    
  }


  //setups
  void setupData(TH1* _data){
    m_input->setDataHisto(_data);
    //m_input->setTemplateHistos(_templates);
    m_input->initData();
  }
  

  void setupInput(TH1* _data, const std::vector<TH1*> _templates){
    m_input->setDataHisto(_data);
    m_input->setTemplateHistos(_templates);
    m_input->init();
  }


  template<typename T>
  std::string addItemToText(const std::string& _text, const T& _aT){
    std::ostringstream value;
    value<< _text.c_str() << _aT;
    return value.str();
  }


  void setupResults(const int& _size);

  void preparePlots(const std::string& _baseName, FitterResults::HistoResult* _histo= 0, FitterResults::LLHResult* _llh = 0){
             
    std::string cName = _baseName;
    cName += "_fit";
    cName += ".root";
    std::string llhName = _baseName;
    llhName += "_LLH";
    llhName += ".root";
    _histo->setFileName(cName.c_str());
    _llh->setFileName(llhName.c_str());
    
  }

  void setupTotalTemplates(){

    m_total = dynamic_cast<TH1*>(m_templateTH1s.front()->Clone("total"));
    m_total->SetDirectory(0);
    m_total->Reset("MICE");
    m_total->ResetStats();
    
    //ProtoCreator creator;
    m_creator->operator()(m_total,m_templateTH1s);
    
  };  

  void prepareData(TH1*& _data){
    _data = (TH1*)m_templateTH1s[0]->Clone("data");
    _data->SetDirectory(0);
    _data->Reset("MICE");
    _data->ResetStats();
  };
  
  void treatFitterConfiguration(core::MinimizerConfiguration* _config){
    for (int i = 0; i < m_expectedValues.size(); ++i)
    {
      _config->getItem(i)->setItem("start",TString::Format("%.2f",m_expectedValues[i]).Data());
    }
  }

  void treatResultsFromMinimizer(const std::vector<std::string>* _names);


  void createScaledData(TH1* _data=0,
                        const double& _integral=1.){

    if(!_data){
      std::cerr << __FILE__ << ":"<< __LINE__ <<"\t data histo pointer nil\n";
      return ;}

    _data->Reset("MICE");
    _data->ResetStats();
    _data->FillRandom(m_total,_integral);
    
    return ;
  }

public:
  
  PseudoStudy(const std::vector<TH1*>& _templates,
              const std::vector<double>& _expected,
              const std::vector<double>& _expectedErrors,
              const double& _dataIntegral,
              const int& _thr=1,
              const int& _iters=5000
              );

   ~PseudoStudy(){
     delete m_input;
   }

  //setter
  void setFitEngine( const std::string& _engine){m_fitEngine = _engine;};
  void setFitMode( const std::string& _mode){m_fitMode = _mode;};
  void setProtoCreator(const BaseProtoCreator* _creator){m_creator = _creator;};
  void setFitterConfigFile(const std::string& _file){m_fitConfigFile = _file;};
  void setInput(InputT* _input=0){
    if(m_input){
      delete m_input;
      m_input = 0;
    }
      
    m_input = _input;
  };
  void setPanicPrint(const bool& _value=false){m_doPanicPrint = _value;};
  void setVerbosity(const int& _value=3){m_verbosity = _value;};
  void setBaseName(const std::string& _value){m_baseName = _value;};

  //getters
  void getResultsOfParameter(const int& _idx,std::vector<TH1*>& _results);
  TH1D* getMaxLLHDistribution(){return m_maxLLH;};
  //utilities

  void printResults();
  
  void getCorrelationResults(std::vector<std::vector<TH2*> >& _results){

    _results.clear();
    
    _results.resize(m_correlations.size(),std::vector<TH2*>(m_correlations[0].size()));
    
    for (int col = 0; col < m_correlations.size(); ++col)
    {
      for (int row = 0; row < m_correlations[0].size(); ++row)
      {
        _results[col][row] = &(m_correlations[col][row]);
      }
    }

  };


  void experiment();


  
};

#include "PseudoStudy.icc"

#endif
