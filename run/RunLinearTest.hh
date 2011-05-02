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

public:
  ExperimentPerformer(){};
  ExperimentPerformer( const ExperimentPerformer& ){};
  virtual ~ExperimentPerformer(){};

  void operator()(const tbb::blocked_range<double>& ) const {};

};

#endif
