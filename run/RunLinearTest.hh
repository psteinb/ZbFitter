#pragma once
#ifndef __RUNLINTEST__HH__
#define __RUNLINTEST__HH__

#include <iostream>
#include <exception>
#include "TROOT.h"
//available for ROOT version 5.26 or higher
//#include "TTreePerfStats.h"

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <sstream>

// #include "stdio.h"
// #include "unistd.h"

// #include "core/FitCore.hh"
// #include "FitterInputs/NormedTH1.hh"
// #include "FitterResults/HistoResult.hh"
// #include "functions/SimpleMaxLLH.hh"

#include "tbb/blocked_range.h"

#include "TH1.h"
// #include "TRegexp.h"
// #include "TGraphErrors.h"
// #include "AtlasStyle.h"
// #include "TCanvas.h"

#include "run/ConfLinearTest.hh"
#include "core/FitCore.hh"
#include "FitterInputs/NormedTH1.hh"
#include "functions/BinnedEML.hh"
#include "Studies/PseudoStudy.hh"
#include "FitterInputs/NormalisationFunctors.hh"
#include "FitterResults/HistoResult.hh"

struct StepValueGenerator
{
  double stepsize;
  double value ;
  
  
public:
  StepValueGenerator(const double& _step):
    stepsize(_step),
    value(stepsize){}

  double operator()() {
    double meta = value;
    value+=stepsize;
    return meta;
  }
    
};

struct scaleMCByValue
{
  double m_scale;

public:
  scaleMCByValue(const double& _scale=1.):
    m_scale(_scale){};
  
  scaleMCByValue(const scaleMCByValue& _rhs):
    m_scale(_rhs.m_scale){};


  void operator()(TH1* _total, const std::vector<TH1*>& _input){

    if(_total->GetEntries()!=0){
      _total->Reset("MICE");
      _total->ResetStats();}
    

    for (int i = 0; i < _input.size(); ++i)
    {
      if(i<1)
        _total->Add(_input[i],m_scale);
      else
        _total->Add(_input[i]);
    }
    
  };

  //private:

};


//small class

class ExperimentPerformer
{
  ConfLinearTest m_configuration;
  double m_scale;
  std::string m_outname;
  std::vector<TH1*> m_templates;
  TH1* m_data;
  PseudoStudy<scaleMCByValue,FitterInputs::NormedTH1<FitterInputs::Norm2Unity>, functions::BinnedEML>*  m_PseudoStudy;


public:
  std::vector<double> m_means;
  std::vector<double> m_sigmas;
  std::vector<double> m_expected      ;

  ExperimentPerformer( const ConfLinearTest& _configuration, 
                       const double& _scale=1.
                       ):
    m_means(),
    m_sigmas(),
    m_configuration(_configuration),
    m_scale(_scale),
    m_outname(),
    m_templates(),
    m_data(0),
    m_expected (),
    m_PseudoStudy(0)
  {
    std::ostringstream name(_configuration.p_outputfile);
    name << "_step"<<_scale;
    m_outname = name.str();
  };

  ExperimentPerformer( const ExperimentPerformer& _other):
    m_means(_other.m_means),
    m_sigmas(_other.m_sigmas),
    m_configuration(_other.m_configuration),
    m_scale(_other.m_scale),
    m_outname(_other.m_outname),
    m_templates(_other.m_templates),
    m_data(_other.m_data),
    m_expected(_other.m_expected)
  {
    std::cout << _other.m_outname << "COPIED\n";
  };

  virtual ~ExperimentPerformer(){

    delete m_data;
    for (int i = 0; i < m_templates.size(); ++i)
    {
      delete m_templates[i];
    }
    m_templates.clear();

  };

  void experiment()  ;
  
  void print() const{
    std::cout << "ExperimentPerformer at "<<m_scale
              << "\n\tfound means: " << m_means.size()
              << "\n\tfound sigmas: " << m_sigmas.size() << "\n";
  };

  void prepare();
};

#endif
