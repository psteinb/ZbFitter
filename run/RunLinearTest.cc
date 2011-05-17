#define __RUNLINEARTEST_CC__
//available for ROOT version 5.26 or higher
//#include "TTreePerfStats.h"
//#include "run/RunLinearTest.hh"

#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <exception>
#include <cmath>
#include <algorithm>



//TBB
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"

//ROOT
#include "TROOT.h"
#include "TString.h"
#include "TLine.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "AtlasStyle.h"

//implement the runner configuration
#include "run/ExperimentPerformer.hh"
#include "run/FractionExperimentPerformer.hh"
#include "run/LinearTestFunctors.hh"


class Conductor{

  std::vector<BasePerformer*>* m_workers;

public:

  Conductor(const Conductor& _rhs):
    m_workers(_rhs.m_workers)
  {}

  Conductor(std::vector<BasePerformer*>* _workers):
    m_workers(_workers)
  {}

  // void operator()(const BasePerformer& _performer){
    
  //   _performer.experiment();

  // }

  void operator()(const tbb::blocked_range<size_t>& _range) const {

    std::vector<BasePerformer*>* metaWorkers = m_workers;

    for (size_t i = _range.begin(); i < _range.end(); ++i)
    {
      std::cout << ">>>"<< __FILE__ << ":" << __LINE__ << "\t do work "<< i <<"\n";
      try{
        metaWorkers->at(i)->experiment();
      }
      catch(std::exception& exc)
      {
        std::cout << "## index " << i << " worker does not exist\n ";
      }
    }
    
  }

};

void setupResults(std::vector<TGraphErrors*>& _results, const ConfLinearTest& _config, const int& _size){
  
  TString templates = _config.p_tempTitle.c_str();
  TObjArray* templateItems = templates.Tokenize(",");
  
  _results.reserve(templateItems->GetEntries());
  TGraphErrors* meta = 0;
  for (int i = 0; i < _results.capacity(); ++i)
  {
    TString Name =  dynamic_cast<TObjString*>(templateItems->At(i))->GetString();
    Name.Append("_lin");
    TString Title =  dynamic_cast<TObjString*>(templateItems->At(i))->GetString();
    Title.Append(";scale to vary b with;fitted ");
    Title.Append(dynamic_cast<TObjString*>(templateItems->At(i))->GetString().Data());
    meta = new TGraphErrors(_size);

    meta->SetName(Name.Data());
    meta->SetTitle(Title.Data());
    _results.push_back(meta);
  }
  delete templateItems;
}

void printResults(const std::vector<TGraphErrors*>& _results, const ConfLinearTest& _config, const std::string _name){

  TString Canvas = _config.p_outputfile.c_str();
  Canvas.Append(_name.c_str());
  TCanvas aCanvas(Canvas.Data(),"linear tests",3000,1000);
  aCanvas.Clear();
  aCanvas.Draw();
  aCanvas.Divide(_results.size(),1);

  TF1* fitline = new TF1("line","[0]*x+[1]",_results[0]->GetXaxis()->GetXmin(),_results[0]->GetXaxis()->GetXmax());
  fitline->SetParName(0,"a");
  fitline->SetParName(1,"b");
  TLine aLine;
  
  for (int i = 1; i < _results.size()+1; ++i)
  {
    aCanvas.cd(i);
    gStyle->SetOptFit(1112);
    
    if(_name.find("rel")!=std::string::npos){
      std::string name = _results[i-1]->GetYaxis()->GetTitle();
      name+="/b(nominal)";
      _results[i-1]->GetYaxis()->SetTitle(name.c_str());
    }
    
    if(_results[i-1]->GetMaximum()>0)
      _results[i-1]->SetMaximum(1.75*(_results[i-1]->GetMaximum()));
    _results[i-1]->GetXaxis()->SetRangeUser(_config.p_scaleRange.first-_config.p_stepsize,_config.p_scaleRange.second+_config.p_stepsize);
    _results[i-1]->Draw("AP+");
    _results[i-1]->Fit(fitline,"R");

  }
  aCanvas.Update();
  aCanvas.Print(".eps");
  
}

int main(int argc, char* argv[])
{
  TStyle* aStyle =  AtlasStyle();
  aStyle->SetOptStat(220002211);
  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();

  //set root message level
  //gErrorIgnoreLevel = 2001;
  //
  ConfLinearTest conf(argc,argv);
  if(conf.p_giveHelp)
    return -1;
  else
    if(conf.p_msgLevel)
      conf.printConf();

  double LengthOfRange = conf.p_scaleRange.second - conf.p_scaleRange.first;
  int numCalls = std::ceil(LengthOfRange/conf.p_stepsize) + 1;

  //setup steps
  std::vector<double> steps(numCalls);
  StepValueGenerator generator(conf.p_stepsize,conf.p_scaleRange.first);
  std::generate(steps.begin(),steps.end(),generator);
  if(!std::count(steps.begin(),steps.end(),1.)){
    //steps.reserve(steps.capacity()+1);
    steps.push_back(1.);
    std::sort(steps.begin(),steps.end());
  }
  

  //setup workers
  std::vector<BasePerformer*> workers;
  workers.reserve(steps.size());
  BasePerformer* meta =0;
  std::vector<double> unscaledValue;
  for (int i = 0; i < steps.size(); ++i)
  {
    if(conf.p_doFractions)
      meta = new FractionExperimentPerformer(conf,steps.at(i));
    else
      meta = new ExperimentPerformer(conf,steps.at(i));

    meta->prepare();
    workers.push_back(meta);
    if(!(steps.at(i)!=1.)){
      unscaledValue.assign(meta->getExpected()->begin(),meta->getExpected()->end());
    }
  }

  //do parallel job
  int grainsize = numCalls/conf.p_threads;
  tbb::blocked_range<size_t> runRange(0,steps.size(),grainsize);
  tbb::parallel_for(runRange,
                    Conductor(&workers)
                    );

  
  std::vector<TGraphErrors*> results;
  setupResults(results,conf,numCalls);

  std::vector<TGraphErrors*> resultsNormedY;
  setupResults(resultsNormedY,conf,numCalls);

  std::vector<BasePerformer*>::const_iterator rItr = workers.begin();
  std::vector<BasePerformer*>::const_iterator rEnd = workers.end();
  

  for (short idx = 0;rItr!=rEnd; ++rItr,idx++)
  {
    (*rItr)->print();
    try{
      for (int i = 0; i < results.size(); ++i)
      {
        results.at(i)->SetPoint(idx+1,steps.at(idx),(*rItr)->getMeans()->at(i));
        resultsNormedY.at(i)->SetPoint(idx+1,steps.at(idx),(*rItr)->getMeans()->at(i));
      }
    }
    catch(std::exception& ex){
      std::cerr << __FILE__ <<":" << __LINE__ << "\t"<<idx << " does not exist in aPerformer.m_means\n";
    }
    
    try{
      for (int i = 0; i < results.size(); ++i)
      {
        results.at(i)->SetPointError(idx+1,conf.p_stepsize/2.,(*rItr)->getSigmas()->at(i));
        resultsNormedY.at(i)->SetPointError(idx+1,conf.p_stepsize/2.,(*rItr)->getSigmas()->at(i));
      }
    }
    catch(std::exception& ex){
      std::cerr << __FILE__ <<":" << __LINE__ << "\t"<<idx << " does not exist in aPerformer.m_means\n";
    }
  }



   for (short idx = 0;idx<resultsNormedY.size();idx++)
   {
     double xValue = 0;
     double yValue = 0;
     double yError = 0;
     double yValueRel = 0;
     double yErrorRel = 0;
     double maxY = 0;
     for (int i = 1; i < (resultsNormedY[idx]->GetN()); ++i)
     {
       resultsNormedY[idx]->GetPoint(i,xValue,yValue);
       yError = resultsNormedY[idx]->GetErrorY(i);
       yValueRel = yValue/float(unscaledValue[idx]);
       yErrorRel = yError/float(unscaledValue[idx]);
       std::cout << i << "\t" << resultsNormedY[idx]->GetName() << "\t" 
                 << xValue << ": "<<yValue<<"("<<unscaledValue[idx] << " => "<< yValueRel <<")\n";

       resultsNormedY[idx]->SetPoint(i,xValue,yValueRel);
       resultsNormedY[idx]->SetPointError(i,resultsNormedY[idx]->GetErrorX(i),yErrorRel);
       maxY = std::max(yValueRel,maxY);
     }
     resultsNormedY[idx]->SetMaximum(maxY);
   }

   printResults(resultsNormedY,conf,"_relLinear");
   printResults(results,conf,"_absLinear");
  
  return 0; 
   

}
 
