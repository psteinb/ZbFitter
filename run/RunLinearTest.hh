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

struct scaleMCValue0
{
  double m_scale;

public:
  scaleMCValue0(const double& _scale=1.):
    m_scale(_scale){};

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

public:
  std::vector<double> m_means;
  std::vector<double> m_sigmas;

  ExperimentPerformer( const ConfLinearTest& _configuration, const double& _scale=1.):
    m_means(),
    m_sigmas(),
    m_configuration(_configuration),
    m_scale(_scale)
  {
  };

  ExperimentPerformer( const ExperimentPerformer& _other):
    m_means(_other.m_means),
    m_sigmas(_other.m_sigmas),
    m_configuration(_other.m_configuration),
    m_scale(_other.m_scale)
  {};
  virtual ~ExperimentPerformer(){};

  void experiment()  ;

};

#endif
