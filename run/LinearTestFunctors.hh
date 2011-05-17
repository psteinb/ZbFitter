#pragma once
#ifndef __LINEARTESTFUNCTORS__HH__
#define __LINEARTESTFUNCTORS__HH__

#include <iostream>
#include "TROOT.h"
#include "TH1.h"

class StepValueGenerator
{
  double stepsize;
  double value ;
  double start;
  bool passedOne;
public:
  
  StepValueGenerator(const double& _step,const double& _start=0.):
    stepsize(_step),
    start(_start),
    value(_start),
    passedOne(false)
  {}

  double operator()() {
    double meta = value;
    if(!(meta!=1.))
      passedOne=true;
    value+=stepsize;
    return meta;
  }
    
  bool didPassOne() const {return passedOne;}
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
