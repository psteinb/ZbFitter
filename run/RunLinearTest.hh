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

#include "core/FitCore.hh"
#include "FitterInputs/NormedTH1.hh"
#include "FitterResults/HistoResult.hh"
#include "functions/SimpleMaxLLH.hh"

#include "tbb/blocked_range.h"

#include "TString.h"
#include "TRegexp.h"
#include "TGraphErrors.h"
#include "AtlasStyle.h"
#include "TCanvas.h"

//small class

class ExperimentPerformer
{

public:
  ExperimentPerformer();
  ExperimentPerformer( const ExperimentPerformer& );
  virtual ~ExperimentPerformer(){};

  void operator()(const tbb::blocked_range<double>& );

};

#endif
