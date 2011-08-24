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



//small class

#endif
