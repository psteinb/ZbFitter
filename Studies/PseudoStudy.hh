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
#include "FitterResults/AbsResult.hh"
#include "functions/SimpleMaxLLH.hh"

#include "TRandom3.h"
#include "TMath.h"
#include "TH1D.h"

template<
  class ProtoCreator,
  class InputT=FitterInputs::NormedTH1,
  class FitterT=functions::SimpleMaxLLH
  >
class PseudoStudy{

  InputT m_input;
  FitterT m_fitter;
  ProtoCreator m_creator;

  std::string m_fitEngine       ;
  std::string m_fitMode         ;

  std::vector<TH1*> m_templateTH1s;
  TH1D* m_total;
  std::vector<TH1*> m_resultTH1s;

  int m_threads;
  int m_iterations;
  TRandom3 m_TRand3;

  std::vector<TH1D> m_pulls;
  std::vector<TH1D> m_means;
  std::vector<TH1D> m_sigmas;
  
  std::vector<double> m_expectedValues   ;
  std::vector<double> m_expectedErrors      ;
  double              m_dataIntegral	;

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

  // void setupIntegrals(){
  //   double integral=0.;
  //   double error=0.;
  //   for (int i = 0; i <m_templateTH1s.size() ; ++i)
  //   {
  //     integral = m_templateTH1s.at(i)->IntegralAndError(m_templateTH1s.at(i)->GetXaxis()->GetXmin(),
  //                                                       m_templateTH1s.at(i)->GetXaxis()->GetXmax(),
  //                                                       error);
  //     m_templateTH1sIntegrals[i] = integral;
  //     m_templateTH1sErrors[i] = error;
  //   }
    
  // };

  std::string addIntToText(const std::string& _text, const int& _anInt){
    std::string value = _text;
    _text+=_anInt;
    return _text;
  }


  void setupResults(const int& _size){
    
    double expMeanDown = 0.;
    double expMeanUp = 0.;

    double expSigmaDown = 0.;
    double expSigmaUp = 0.;

    for (int i = 0; i < _size; ++i)
    {
      expMeanDown = 0.5*(m_expectedValues.at(i));
      expMeanUp = 1.5*(m_expectedValues.at(i));
      expSigmaDown = 0.5*(m_expectedErrors.at(i));
      expSigmaUp = 1.5*(m_expectedErrors.at(i));

      m_pulls[i] = TH1D(addIntToText("pull_par",i).c_str(),"pull",50,-5,5);
      m_means[i] = TH1D(addIntToText("mean_par",i).c_str(),"mean fitted",50,expMeanDown,expMeanUp);
      m_sigmas[i] = TH1D(addIntToText("sigma_par",i).c_str(),"sigma fitted",50,expSigmaDown,expSigmaUp);
    }


  }

  void setupTotalTemplates(){

    m_total = dynamic_cast<TH1D*>(m_templateTH1s.front()->Clone("total"));
    m_total->Reset("MICE");
    m_total->ResetStats();
    
    ProtoCreator creator;
    creator(m_total,m_templateTH1s);
    
  };  

  void prepareData(TH1D* _data=0){
    _data = (TH1D*)m_templateTH1s[0]->Clone("data");
    _data->Reset("MICE");
    _data->ResetStats();
  };
  
public:
  
  PseudoStudy(const std::vector<TH1*>& _templates,
              const std::vector<double>& _expected,
              const std::vector<double>& _expectedErrors,
              const double& _dataIntegral,
              const int& _thr=1,
              const int& _iters=5000
              ):
    m_input(),
    m_fitter(),
    m_creator(),
    m_fitEngine("Minuit"),       
    m_fitMode  ("Migrad"),       
    m_templateTH1s(_templates.size(),0),
    m_total(0),
    m_resultTH1s(),
    m_threads(_thr),
    m_iterations(_iters),
    m_TRand3(),
    m_pulls(_templates.size()),
    m_means(_templates.size()),
    m_sigmas(_templates.size()),
    m_expectedValues    (_expected),   
    m_expectedErrors    (_expectedErrors),   
    m_dataIntegral      (_dataIntegral),   
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


    setupTotalTemplates();
    setupInput(m_total,m_templateTH1s);
    setupResults(_templates.size());
  };

  //setter
  void setFitEngine( const std::string& _engine){m_fitEngine = _engine;};
  void setFitMode( const std::string& _mode){m_fitMode = _mode;};
  
  //getters
  void getResultsOfParameter(const int& _idx,std::vector<TH1*>& _results){

    _results.clear();
    
    if(!(_idx<m_templateTH1s.size()))
      return;

    _results.resize(3);
    
    try{
      _results[0] = &(m_means.at(_idx));
    }
    catch(std::exception& exc){
      std::cerr << __FILE__ <<":"<< __LINE__ <<"\t unable to return m_means item at "<< _idx <<" due to \n\t"<< exc.what()<<std::endl;
      _results[0] = 0;
    }

    try{
      _results[1] = &(m_sigmas.at(_idx));
    }
    catch(std::exception& exc){
      std::cerr << __FILE__ <<":"<< __LINE__ <<"\t unable to return m_sigmas item at "
                << _idx <<" due to \n\t"<< exc.what()<<std::endl;
      _results[1] = 0;
    }

    
    try{
      _results[2] = &(m_pulls.at(_idx));
    }
    catch(std::exception& exc){
      std::cerr << __FILE__ <<":"<< __LINE__ <<"\t unable to return m_pulls item at "<< _idx<<" due to \n\t"<< exc.what()<<std::endl;
      _results[2] = 0;
    }
    
    return;
  };

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
  
  void createScaledData(TH1D* _data=0,
                        const double& _integral=1.){

    if(!_data){
      std::cerr << __FILE__ << ":"<< __LINE__ <<"\t inline TH1 pointer vector empty or data histo nil\n";
      return;}


    _data->Reset("MICE");
    _data->ResetStats();
    _data->FillRandom(m_total,_integral);

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
      createScaledData(m_data,m_TRand3.Poisson(m_dataIntegral));

      //feed m_input
      setupInput(m_data,m_templateTH1s);

      //init the fitter
      core::FitCore<FitterT,InputT,FitterResults::AbsResult> fitter(&m_input);
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
  

      if(m_fitValues[0]>m_expectedValues[0])
        bPull = (m_expectedValues[0]-m_fitValues[0])/TMath::Sqrt((m_fitErrorsDown[0]*m_fitErrorsDown[0])+(m_expectedErrors[0]*m_expectedErrors[0]));
      else
        bPull = (m_expectedValues[0]-m_fitValues[0])/TMath::Sqrt((m_fitErrorsUp[0]*m_fitErrorsUp[0])+(m_expectedErrors[0]*m_expectedErrors[0]));

      if(m_fitValues[1]>m_expectedValues[1])
        cPull = (m_expectedValues[1]-m_fitValues[1])/TMath::Sqrt((m_fitErrorsDown[1]*m_fitErrorsDown[1])+(m_expectedErrors[1]*m_expectedErrors[1]));
      else
        cPull = (m_expectedValues[1]-m_fitValues[1])/TMath::Sqrt((m_fitErrorsUp[1]*m_fitErrorsUp[1])+(m_expectedErrors[1]*m_expectedErrors[1]));

      if(m_fitValues[2]>m_expectedValues[2])
        lPull = (m_expectedValues[2]-m_fitValues[2])/TMath::Sqrt((m_fitErrorsDown[2]*m_fitErrorsDown[2])+(m_expectedErrors[2]*m_expectedErrors[2]));
      else
        lPull = (m_expectedValues[2]-m_fitValues[2])/TMath::Sqrt((m_fitErrorsUp[2]*m_fitErrorsUp[2])+(m_expectedErrors[2]*m_expectedErrors[2]));

      /////////////////////////////////////////
      /// FIXME: the following should be done better by a utility method
      /////////////////////////////////////////

      m_pulls[0].Fill(bPull);
      m_pulls[1].Fill(cPull);
      m_pulls[2].Fill(lPull);

      m_means[0].Fill(m_fitValues[0]);
      m_means[1].Fill(m_fitValues[1]);
      m_means[2].Fill(m_fitValues[2]);

      m_sigmas[0].Fill(std::min(m_fitErrorsDown[0],m_fitErrorsUp[0]));
      m_sigmas[1].Fill(std::min(m_fitErrorsDown[1],m_fitErrorsUp[1]));
      m_sigmas[2].Fill(std::min(m_fitErrorsDown[2],m_fitErrorsUp[2]));

      //clean-up data
      m_data->Reset("MICE");
      m_data->ResetStats(); 
    
    }

  };
  
};

#endif
