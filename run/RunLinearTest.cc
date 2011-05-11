#define __RUNLINEARTEST_CC__
//available for ROOT version 5.26 or higher
//#include "TTreePerfStats.h"
#include "run/RunLinearTest.hh"

#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <exception>



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

// void createScaledData(const std::vector<TH1*>& _vector,double _scale,TH1D* _data){

//   if(_vector.empty() || !_data){
//     std::cerr << __FILE__ << ":"<< __LINE__ <<"\t inline TH1 pointer vector empty or data histo nil\n";
//     return;}

//   std::cout << ">>> old content " << _data->GetEntries() << ", "<< _data->GetNbinsX() <<"\n";
//   TString name;
//   for (int i = 0; i < _vector.size(); ++i)
//   {
//     name = _vector.at(i)->GetName();
//     name.ToLower();
//     if(name.Contains(TRegexp(".*mcb.*")) || name.Contains(TRegexp(".*trueb.*"))){
//       std::cout << ">>> scaled " << name.Data() << " by " << _scale << " from "<< _vector.at(i)->Integral();
//       _data->Add(_vector.at(i),_scale);

//     }
//     else{
//       _data->Add(_vector.at(i),1.);
//       std::cout << ">>> added "<<_vector.at(i)->GetEntries() << "\n";
//     }
//   }

//   std::cout << ">>> new content " << _data->GetEntries() << ", "<< _data->GetNbinsX() << "\n";

// }

// std::string stripRootString(const std::string& _filename){
  
//   size_t pos = _filename.find(".root");
//   if(pos!=std::string::npos)
//     return _filename.substr(0,pos);
//   else
//     return _filename;

// }

// void cloneTH1VectorFromTo(const std::vector<TH1*>& _reference, std::vector<TH1*>& _target){
  
//   _target.clear();
//   _target.resize(_reference.size(),0);
//   std::string newName;
//   for (int i = 0; i < _reference.size(); ++i)
//   {
//     newName = _reference.at(i)->GetName();
//     newName += "_cloned";
//     _target[i] = dynamic_cast<TH1*>(_reference.at(i)->Clone(newName.c_str()));
//   }

// }

// void deleteTH1InVector(std::vector<TH1*>& _vec){
  

//   for (int i = 0; i < _vec.size(); ++i)
//   {
//     delete _vec[i];
//     _vec[i]=0;
//   }

//   _vec.clear();
// }

// void ExperimentPerformer::operator()(const tbb::blocked_range<double>& _range){

//    // ----- INPUT ----- 
//   FitterInputs::NormedTH1<FitterInputs::Norm2Unity>* input = new FitterInputs::NormedTH1<FitterInputs::Norm2Unity>();
//   input->loadData(conf.p_datadir.c_str(),conf.p_dataTitle.c_str(),conf.p_rebin);
//   input->loadTemplates(conf.p_datadir.c_str(),conf.p_tempTitle.c_str(),conf.p_rebin);

//   std::vector<TH1*> m_templates;
//   input->getTemplatesDeepCopy(m_templates);
//   TH1* m_data =  input->getDataDeepCopy();

//    // ----- EXPECTED VALUES ----- 
//   std::vector<double> expected          ;
//   std::vector<double> expectedErrors    ;
//   createExpectedValuesFromTemplates(m_templates,
//                                     expected,          
//                                     expectedErrors,
//                                     m_data);

//    // ----- PSEUDO EXPERIMENTS ----- 
//   PseudoStudy<defaultMCValues,FitterInputs::NormedTH1<FitterInputs::Norm2Unity>, functions::BinnedEML>  
//     aPseudoStudy(m_templates,
//                  expected,
//                  expectedErrors,
//                  m_data->Integral(),
//                  conf.p_threads,
//                  conf.p_nIter
//                  );

//   aPseudoStudy.setInput(input);
//   aPseudoStudy.setFitterConfigFile(conf.p_configFile);
//   aPseudoStudy.setFitEngine(conf.p_fitEngine);
//   aPseudoStudy.setFitMode(conf.p_fitMode);
//   aPseudoStudy.setVerbosity(conf.p_msgLevel);
//   aPseudoStudy.setBaseName(conf.p_outputfile);
//   if(conf.p_msgLevel<3)
//     aPseudoStudy.setPanicPrint(true);
//   aPseudoStudy.experiment();

// }
// void ExperimentPerformer::operator()(const tbb::blocked_range<double>& _range )  {
  
//   tbb::blocked_range<double>::const_iterator rItr = _range.begin();
//   tbb::blocked_range<double>::const_iterator rEnd = _range.end();

  
//   for (;rItr!=rEnd; ++rItr)
//   {
//     operator()(rItr);
//   }

// }
void ExperimentPerformer::createExpectedValuesFromTemplates(){

  m_expected.clear();
  m_expected.resize(m_templates.size(),0.);

  std::vector<double> integrals(m_templates.size(),0.);
  std::vector<double> errors(m_templates.size(),0.);
  double total = 0.;
  for (int i = 0; i < m_templates.size(); ++i)
  {
    integrals[i] = m_templates[i]->IntegralAndError(m_templates[i]->GetXaxis()->GetFirst(),
                                                   m_templates[i]->GetXaxis()->GetLast(),
                                                   errors[i]
                                                   );
    total += integrals[i];
  }

  double dataIntegral = m_data->Integral();

  for (int i = 0; i < m_templates.size(); ++i)
  {
    if(i<1)
      m_expected[i] = (integrals[i]/total)*dataIntegral*m_scale;
    else
      m_expected[i] = (integrals[i]/total)*dataIntegral;
    std::cout << m_scale<< "x, expected value ["<<i <<"]\t"<<m_expected[i] <<std::endl;
  }

}

void ExperimentPerformer::prepare( )  {
  // ----- INPUT ----- 
  FitterInputs::NormedTH1<FitterInputs::Norm2Unity>* input = new FitterInputs::NormedTH1<FitterInputs::Norm2Unity>();
  input->loadData(m_configuration.p_datadir.c_str(),m_configuration.p_dataTitle.c_str(),m_configuration.p_rebin);
  input->loadTemplates(m_configuration.p_datadir.c_str(),m_configuration.p_tempTitle.c_str(),m_configuration.p_rebin);

  input->getTemplatesDeepCopy(m_templates);
  m_data =  input->getDataDeepCopy();

  this->createExpectedValuesFromTemplates();

  scaleMCByValue aScaler(m_scale);
  // dummy values here for they are only important for the pulls
  std::vector<double> expectedErrors    (m_templates.size(),1.);
  
  m_PseudoStudy = new PseudoStudy<scaleMCByValue,FitterInputs::NormedTH1<FitterInputs::Norm2Unity>, functions::BinnedEML>(
                                                                                                                          m_templates,m_expected,expectedErrors,
                                                                                                                          (m_data->Integral()),m_configuration.p_threads,
                                                                                                                          m_configuration.p_nIter
                                                                                                                          );

   m_PseudoStudy->setProtoCreator(aScaler);
   //m_PseudoStudy->setInput(input);
   m_PseudoStudy->setFitterConfigFile(m_configuration.p_configFile);
   m_PseudoStudy->setFitEngine(m_configuration.p_fitEngine);
   m_PseudoStudy->setFitMode(m_configuration.p_fitMode);
   m_PseudoStudy->setVerbosity(m_configuration.p_msgLevel);
   m_PseudoStudy->setBaseName(this->m_outname);

   delete input;
}

void ExperimentPerformer::experiment( )  {
  
  // ----- PSEUDO EXPERIMENTS ----- 
  m_PseudoStudy->experiment();

  std::vector<std::vector<TH1*> > m_results(m_templates.size());
  m_means.reserve(m_templates.size());
  m_sigmas.reserve(m_templates.size());
  for (int i = 0; i < m_templates.size(); ++i)
  {
    m_PseudoStudy->getResultsOfParameter(i,m_results[i]);
    this->m_means.push_back(m_results[i][0]->GetMean());
    this->m_sigmas.push_back(m_results[i][1]->GetMean());
  }

 
}

class Conductor{

  std::vector<ExperimentPerformer*>* m_workers;

public:

  Conductor(const Conductor& _rhs):
    m_workers(_rhs.m_workers)
  {}

  Conductor(std::vector<ExperimentPerformer*>* _workers):
    m_workers(_workers)
  {}

  // void operator()(const ExperimentPerformer& _performer){
    
  //   _performer.experiment();

  // }

  void operator()(const tbb::blocked_range<size_t>& _range) const {

    std::vector<ExperimentPerformer*>* metaWorkers = m_workers;

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
    Title.Append(";scale;fitted ");
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

  TLine aLine;
  
  for (int i = 1; i < _results.size()+1; ++i)
  {
    aCanvas.cd(i);
    gStyle->SetOptFit(1112);
    _results[i-1]->SetMaximum(1.75*(_results[i-1]->GetMaximum()));
    _results[i-1]->Draw("AP+");
    _results[i-1]->Fit(fitline,"R");
    // aCanvas.Update();
    // aLine.DrawLine(gPad->GetUxmin(),gPad->GetUymin(),
    //                gPad->GetUxmax(),gPad->GetUymax());
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

  int numCalls = int(2./conf.p_stepsize)-1;

  //setup steps
  std::vector<double> steps(numCalls);
  std::generate(steps.begin(),steps.end(),StepValueGenerator(conf.p_stepsize));

  //setup workers
  std::vector<ExperimentPerformer*> workers;
  workers.reserve(steps.size());
  ExperimentPerformer* meta =0;
  std::vector<double> unscaledValue;
  for (int i = 0; i < steps.size(); ++i)
  {
    meta = new ExperimentPerformer(conf,steps.at(i));
    meta->prepare();
    workers.push_back(meta);
    if(!(steps.at(i)!=1.)){
      unscaledValue.assign(meta->m_expected.begin(),meta->m_expected.end());
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

  // TGraphErrors bGraph(numCalls);
  // TGraphErrors cGraph(numCalls);
  // TGraphErrors lGraph(numCalls);
  std::vector<ExperimentPerformer*>::const_iterator rItr = workers.begin();
  std::vector<ExperimentPerformer*>::const_iterator rEnd = workers.end();
  

  for (short idx = 0;rItr!=rEnd; ++rItr,idx++)
  {
    (*rItr)->print();
    try{
      for (int i = 0; i < results.size(); ++i)
      {
        results.at(i)->SetPoint(idx+1,steps.at(idx),(*rItr)->m_means.at(i));
        resultsNormedY.at(i)->SetPoint(idx+1,steps.at(idx),(*rItr)->m_means.at(i));
        // if(!(steps.at(idx)!=1.))
        //   unscaledValue[i] = (*rItr)->m_means.at(i);
      }
    }
    catch(std::exception& ex){
      std::cerr << __FILE__ <<":" << __LINE__ << "\t"<<idx << " does not exist in aPerformer.m_means\n";
    }
    
    try{
      for (int i = 0; i < results.size(); ++i)
      {
        results.at(i)->SetPointError(idx+1,conf.p_stepsize/2.,(*rItr)->m_sigmas.at(i));
        resultsNormedY.at(i)->SetPointError(idx+1,conf.p_stepsize/2.,(*rItr)->m_sigmas.at(i));
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
 
