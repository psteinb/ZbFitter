#pragma once
#ifndef __RUNLINTEST__HH__
#define __RUNLINTEST__HH__

#include <iostream>
#include "TROOT.h"

#include "TH1.h"

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

#endif
