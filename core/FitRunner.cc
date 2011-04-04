#include "FitRunner.hh"
#include <stdexcept>
#include "TStopWatch.h"

// Constructors/Destructors
//  

FitRunner::FitRunner ( ):
  m_resources(0),
  m_result(0),
  m_fcn(),
  m_config(),
  m_minimizer(0),
  m_configFile("")
{

}

FitRunner::~FitRunner ( ) {

  //the only ownership we have is on m_minimizer
  delete m_minimizer;m_minimizer=0;

}

void FitRunner::setupMachinery{
  
  if(isConfigured("Engine") && isConfigured("Mode"))
    m_minimizer = ROOT::Math::Factory::CreateMinimizer(m_config["Engine"], m_config["Mode"]);
  else{
    throw std::runtime_error("FitRunner::setupMachinery for neither engine nor mode was configured");
  }

  if(isConfigured("MaxFunCalls"))
    m_minimizer = getIntFromString(m_config["MaxFunCalls"]);

  if(isConfigured("MaxIterations"))
    m_minimizer = getIntFromString(m_config["MaxIterations"]);

  if(isConfigured("Tolerance"))
    m_minimizer = getDoubleFromString(m_config["Tolerance"]);

  //the rest is set by hand for now
  double stepSize[3] = {0.1,0.1,0.1};
  double variableStart[3] = { .2,.2,.2};
  
  // Set the free variables to be minimized!
  min->SetVariable(0,"b",variableStart[0], stepSize[0]);
  min->SetVariable(1,"c",variableStart[1], stepSize[1]);
  min->SetVariable(2,"l",variableStart[2], stepSize[2]);

  
}

void FitRunner::fit(const bool& _verbose){

  
  ROOT::Math::Functor f(m_fcn,3);

  TStopwatch watch;
  watch.Start();

  min->Minimize(); 
  watch.Stop();
  
  if(_verbose){
    const double *xs = min->X();
    std::cout << "Minimum: f(b = " << xs[0] << ", c = " << xs[1] << ", l = "<< xs[2]<< " ): " 
       << m_fcn(xs) << endl;
  }

  std::cout << "FitRunner::fit \t  CpuTime = \t"<< std::setw(10) << std::setprecision(4)<< watch.CpuTime() << "\n";
  std::cout << "FitRunner::fit \t  RealTime = \t"<< std::setw(10) << std::setprecision(4)<< watch.RealTime() << "\n";

}
//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  


