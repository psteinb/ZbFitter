#define __RUNLINEARTEST_CC__
//available for ROOT version 5.26 or higher
//#include "TTreePerfStats.h"
#include "run/RunLinearTest.hh"
#include "run/ConfLinearTest.hh"
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <exception>

#include "core/FitCore.hh"
#include "FitterInputs/NormedTH1.hh"
#include "FitterInputs/NormalisationFunctors.hh"
#include "FitterResults/HistoResult.hh"
#include "functions/BinnedEML.hh"

//TBB
#include "tbb/parallel_for.h"

//ROOT
#include "TROOT.h"
#include "TString.h"
#include "TRegexp.h"
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

  std::vector<double> steps(numCalls);
  std::generate(steps.begin(),steps.end(),StepValueGenerator(conf.p_stepsize));

  int grainsize = numCalls/conf.p_threads;
  
  tbb::parallel_for(tbb::blocked_range<double>(conf.p_stepsize,2.,conf.p_stepsize),
                    ExperimentPerformer()
                    );

  return 0; 
   

}
 
