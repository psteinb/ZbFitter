#pragma once
#ifndef __PSEUDOSTUDY_HH__
#define __PSEUDOSTUDY_HH__
#include "TCanvas.h"
#include "AtlasStyle.h"


#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

#include "core/FitCore.hh"
#include "FitterInputs/NormedTH1.hh"
#include "FitterResults/HistoResult.hh"
#include "functions/SimpleMaxLLH.hh"

#include "TRandom3.h"
#include "TMath.h"
#include "TH1D.h"

template<
  class InputT=FitterInputs::NormedTH1,
  class FitterT=functions::SimpleMaxLLH,
  class ResultT=FitterResults::HistoResult
  >
class PseudoStudy{

  InputT m_input;
  FitterT m_fitter;
  ResultT m_result;

  std::string m_fitEngine       ;
  std::string m_fitMode         ;

  std::vector<TH1*> m_templateTH1s;
  std::vector<TH1*> m_dataTH1s;
  std::vector<TH1*> m_resultTH1s;

  int m_threads;
  int m_iterations;
  TRandom3 m_TRand3;

  TH1D pull_fb;
  TH1D pull_fc;
  TH1D pull_fl;
  
  std::vector<double> m_templateTH1sIntegrals   ;
  std::vector<double> m_templateTH1sErrors      ;
  double              m_dataTH1sIntegrals	;
  double              m_dataTH1sErrors   	;


  std::vector<double> m_fitValues;
  std::vector<double> m_fitErrorsUp;
  std::vector<double> m_fitErrorsDown;
  std::vector<int>    m_fitErrorsStatus;

  //setups
  void setupInput(TH1* _data, const std::vector<TH1*> _templates){
    m_input.setDataHisto(_data);
    m_input.setTemplateHistos(_templates);
    m_input.init();
  }

  void setupIntegrals(){
    double integral=0.;
    double error=0.;
    for (int i = 0; i <m_templateTH1s.size() ; ++i)
    {
      integral = m_templateTH1s.at(i)->IntegralAndError(m_templateTH1s.at(i)->GetXaxis()->GetXmin(),
                                                        m_templateTH1s.at(i)->GetXaxis()->GetXmax(),
                                                        error);
      m_templateTH1sIntegrals[i] = integral;
      m_templateTH1sErrors[i] = error;
    }
    
    m_dataTH1sIntegrals = m_dataTH1s.at(0)->IntegralAndError(m_dataTH1s.at(0)->GetXaxis()->GetXmin(),
                                                             m_dataTH1s.at(0)->GetXaxis()->GetXmax(),
                                                             m_dataTH1sErrors);
    
  };

  void prepareData(TH1D* _data=0){
    _data = (TH1D*)m_templateTH1s[0]->Clone("data");
    _data->Reset("MICE");
    _data->ResetStats();
  };
  
public:
  
  PseudoStudy(const std::vector<TH1*>& _templates,
              const std::vector<TH1*>& _data,
              const int& _thr=1,
              const int& _iters=1000
              ):
    m_input(),
    m_fitter(),
    m_result(0,2,"PseudoStudy"),
    m_fitEngine("Minuit"),       
    m_fitMode  ("Migrad"),       
    m_templateTH1s(_templates.size(),0),
    m_dataTH1s(_data.size(),0),
    m_resultTH1s(),
    m_threads(_thr),
    m_iterations(_iters),
    m_TRand3(),
    pull_fb("fb",";pull fb;N",50,-5.,5.),
    pull_fc("fc",";pull fc;N",50,-5.,5.),
    pull_fl("fl",";pull fl;N",50,-5.,5.),
    m_templateTH1sIntegrals(_templates.size(),0.),   
    m_templateTH1sErrors   (_templates.size(),0.),   
    m_dataTH1sIntegrals    (0.),   
    m_dataTH1sErrors       (0.),  
    m_fitValues(_templates.size(),0.),
    m_fitErrorsUp(_templates.size(),0.),
    m_fitErrorsDown(_templates.size(),0.),
    m_fitErrorsStatus(_templates.size(),0.)
  {
    //create deep copies!
    for (int i = 0; i < _templates.size(); ++i)
    {
      std::string name = _templates.at(i)->GetName();
      name += "_pseudo";
      m_templateTH1s[i] = dynamic_cast<TH1*>(_templates.at(i)->Clone(name.c_str()));
    }

    //create deep copies!
    for (int i = 0; i < _data.size(); ++i)
    {
      std::string name = _data.at(i)->GetName();
      name += "_pseudo";
      m_dataTH1s[i] = (TH1*)_data.at(i)->Clone(name.c_str());
    }

    setupInput(m_dataTH1s[0],m_templateTH1s);
    setupIntegrals();
  };

  //setter
  void setFitEngine( const std::string& _engine){m_fitEngine = _engine;};
  void setFitMode( const std::string& _mode){m_fitMode = _mode;};
  
  //getter

  //utilities

  void createOutput(const std::string& _name,TH1* _fb=0,TH1* _fc=0,TH1* _fl=0){
  
    m_resultTH1s.resize(3,0);
    if(_fb){
      _fb->Draw();
      m_resultTH1s[0] = _fb;
    }

    if(_fc){
      _fc->Draw();
      m_resultTH1s[1] = _fc;
    }

    if(_fl){
      _fl->Draw();
      m_resultTH1s[2] = _fl;
    }
  

  };
  
  void createScaledData(const std::vector<TH1*>& _vector,
                      const std::vector<double>& _scales,
                      TH1D* _data,
                      const int& _integral){

  if(_vector.empty() || !_data){
    std::cerr << __FILE__ << ":"<< __LINE__ <<"\t inline TH1 pointer vector empty or data histo nil\n";
    return;}

  if(_vector.size()!=_scales.size())
    {
    std::cerr << __FILE__ << ":"<< __LINE__ <<"\t inline TH1 pointer vector mismatching scale factor vector\n";
    return;}

  TH1D* total = dynamic_cast<TH1D*>(_vector.front()->Clone("total"));
  total->Reset("MICE");
  total->ResetStats();

  for (int i = 0; i < _vector.size(); ++i)
  {
    total->Add(_vector.at(i),_scales.at(i));
  }

  _data->FillRandom(total,_integral);

  }

  void experiment(){
    double bPull=0;
    double cPull=0;
    double lPull=0;

    TH1D* m_data=0;
    prepareData(m_data);

    for (int i = 0; i < (m_iterations); ++i)
    {
      
    
      if(i % 500 == 0)
        std::cout << " iteration " << i << "/" << m_iterations << std::endl;

      //scale b content and
      // add all MC histos according to the just fitted fractions to give pseudo data
      createScaledData(m_templateTH1s,m_templateTH1sIntegrals,m_data,m_TRand3.Poisson(m_dataTH1sIntegrals));

      //feed m_input
      setupInput(m_data,m_templateTH1s);

      //init the fitter
      core::FitCore<FitterT,InputT,ResultT> fitter(&m_input);
      fitter.configureKeyWithValue("Engine",m_fitEngine);
      fitter.configureKeyWithValue("Mode",m_fitMode);
      fitter.setupMachinery();

      //run the fitter on data from the input file
      fitter.fit(false);

      //collect the results
      fitter.getMinosErrorSet(m_fitErrorsStatus,m_fitErrorsDown,m_fitErrorsUp);
      for (int i = 0; i < m_templateTH1s.size(); ++i)
      {
        m_fitValues[i] = fitter.getMinimizer()->X()[i];
      }
  

      if(m_fitValues[0]>m_templateTH1sIntegrals[0])
        bPull = (m_templateTH1sIntegrals[0]-m_fitValues[0])/TMath::Sqrt((m_fitErrorsDown[0]*m_fitErrorsDown[0])+(m_templateTH1sErrors[0]*m_templateTH1sErrors[0]));
      else
        bPull = (m_templateTH1sIntegrals[0]-m_fitValues[0])/TMath::Sqrt((m_fitErrorsUp[0]*m_fitErrorsUp[0])+(m_templateTH1sErrors[0]*m_templateTH1sErrors[0]));

      if(m_fitValues[1]>m_templateTH1sIntegrals[1])
        cPull = (m_templateTH1sIntegrals[1]-m_fitValues[1])/TMath::Sqrt((m_fitErrorsDown[1]*m_fitErrorsDown[1])+(m_templateTH1sErrors[1]*m_templateTH1sErrors[1]));
      else
        cPull = (m_templateTH1sIntegrals[1]-m_fitValues[1])/TMath::Sqrt((m_fitErrorsUp[1]*m_fitErrorsUp[1])+(m_templateTH1sErrors[1]*m_templateTH1sErrors[1]));

      if(m_fitValues[2]>m_templateTH1sIntegrals[2])
        lPull = (m_templateTH1sIntegrals[2]-m_fitValues[2])/TMath::Sqrt((m_fitErrorsDown[2]*m_fitErrorsDown[2])+(m_templateTH1sErrors[2]*m_templateTH1sErrors[2]));
      else
        lPull = (m_templateTH1sIntegrals[2]-m_fitValues[2])/TMath::Sqrt((m_fitErrorsUp[2]*m_fitErrorsUp[2])+(m_templateTH1sErrors[2]*m_templateTH1sErrors[2]));
      //}

      pull_fb.Fill(bPull);

      pull_fc.Fill(cPull);

      pull_fl.Fill(lPull);


      // ///////////////////////////////////////////
      // // panic print
      // //
    
      // if(TMath::Abs(bPull)>2.5 || TMath::Abs(cPull)>2.5 || TMath::Abs(cPull)>2.5){
      //   std::ostringstream Name;
      //   Name << "pseudoExperiment_";
      //   Name << i << ".root";
      //   result->setFileName(Name.str().c_str());
      //   if(conf.p_msgLevel>4)
      //     fitter.printTo(result);
      // }

      //clean-up data
      m_data->Reset("MICE");
      m_data->ResetStats(); 
    
    }

  };
  
};

#endif
