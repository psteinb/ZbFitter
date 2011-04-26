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
#include "stdio.h"
#include "unistd.h"

#include "core/FitCore.hh"
#include "FitterInputs/NormedTH1.hh"
#include "FitterResults/HistoResult.hh"
#include "functions/SimpleMaxLLH.hh"

#include "TString.h"
#include "TRegexp.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "AtlasStyle.h"
#include "TRandom3.h"
#include "TMath.h"

//small class
class RunnerConfig {

private:
  int m_argc;
  char** m_argv;
  
public:
  
  std::string p_datadir;
  std::string p_outputfile;
  std::string p_configFile;
  std::string p_fitEngine;
  std::string p_fitMode  ;

  std::string p_dataTitle  ;
  std::string p_tempTitle  ;

  int         p_msgLevel;
  int         p_threads;
  int         p_nIter;
  int         p_rebin;
  bool        p_giveHelp;

  
  RunnerConfig();
  RunnerConfig(int , char**);
  void printHelp();
  void printConf();
  void setOpt(int , char** );
  void parse();

};

//default constructor
RunnerConfig::RunnerConfig():
  m_argc(0),m_argv(0),
  p_datadir("/some/path/"),
  p_outputfile("pseudo.eps"),
  p_configFile(""),
  p_fitEngine("Minuit2"),
  p_fitMode  ("Scan"),
  p_dataTitle("data"),
  p_tempTitle("mcb,mcc,mcl"),
  p_msgLevel(3),
  p_threads(1),
  p_giveHelp(false),
  p_nIter(10000),
  p_rebin(1)
{}

//constructor with initialisation
RunnerConfig::RunnerConfig(int inArgc, char** inArgv):
  m_argc(inArgc),m_argv(inArgv),
  p_datadir("/some/path/"),
  p_outputfile("pseudo.eps"),
  p_configFile(""),
  p_fitEngine("Minuit2"),
  p_fitMode  ("Scan"),
  p_dataTitle("data"),
  p_tempTitle("mcb,mcc,mcl"),
  p_msgLevel(3),
  p_threads(1),
  p_giveHelp(false),
  p_nIter(10000.),
  p_rebin(1)
{

  parse();

}

void RunnerConfig::parse(){


  int opt = 0;
  while( (opt = getopt(m_argc, m_argv, "d:o:c:m:t:E:M:D:T:i:r:h" ))!=-1 ){
    std::istringstream instream;
    std::ostringstream outstream;
    size_t found;
    int meta=0;
    double dmeta=0;
    switch(opt){
    case 'd':
      p_datadir = std::string(optarg);
      break;
    case 'D':
      p_dataTitle = std::string(optarg);
      break;
    case 'T':
      p_tempTitle = std::string(optarg);
      break;
    case 'o':
      p_outputfile = std::string(optarg);
      break;
    case 'c':
      p_configFile = std::string(optarg);
      break;
    case 'E':
      p_fitEngine = std::string(optarg);
      break;
    case 'M':
      p_fitMode = std::string(optarg);
      break;
    case 'm':
      instream.str(optarg);
      if( !(instream >> meta) ){
        std::cerr << "RunFitter \t invalid argument format for [-m]" << std::endl;
        p_msgLevel = 0;
      }
      else{
        p_msgLevel = meta;
      }

      break;
    case 'i':
      instream.str(optarg);
      if( !(instream >> meta) ){
        std::cerr << "RunFitter \t invalid argument format for [-i]" << std::endl;
        p_nIter = 0;
      }
      else{
        p_nIter = meta;
      }

      break;
    case 'r':
      instream.str(optarg);
      if( !(instream >> meta) ){
        std::cerr << "RunFitter \t invalid argument format for [-r]" << std::endl;
        p_rebin = 0;
      }
      else{
        p_rebin = meta;
      }

      break;

    case 'h':
      p_giveHelp = true;
      printHelp();
      break;
    default:
      p_giveHelp = true;
      std::cout << "RunFitter -- Unknown input: -"<< (char)optopt << "\t" << optarg << "\n" << std::endl;
      printHelp();
      break;
    }

  }
  
}

//function to print help text
void RunnerConfig::printHelp(){

  std::cout << "RunFitter" << std::endl;
  std::cout << "=============" << std::endl;
  std::cout << "Executable for Running Fitter Algorithms on given datasets" << std::endl;
  std::cout << "\t $> RunFitter <options>" << std::endl;
  std::cout << "\t -d <args> define data directory" << std::endl;
  std::cout << "\t -o <foo.root> set output file name (to foo.root)" << std::endl;
  std::cout << "\t -c <bar.env> set TEnv style config file" << std::endl;
  std::cout << "\t -m set message level (0=VERBOSE,..,2=INFO,..,5=ERROR)" << std::endl;
  std::cout << "\t -t <num> number of threads to use " << std::endl;
  std::cout << "\t -E <TMinuitEngine> define fit engine" << std::endl;
  std::cout << "\t -M <TMinuitMode> define fit mode" << std::endl;
  std::cout << "\t -D <ObjectName> define data object to retrieve from root file" << std::endl;
  std::cout << "\t -T <ObjectName> define template (+systematics) object(s) to retrieve from root file" << std::endl;
  std::cout << "\t -i <N iterations> define number of pseudo experiments" << std::endl;
  std::cout << "\t -r <factor> rebin all input by factor" << std::endl;
  std::cout << "\t -h print this help" << std::endl;
  std::cout << std::endl;


}

//function to print current config
void RunnerConfig::printConf(){

  std::cout << "RunFitter running on" << std::endl;
  std::cout << "[-d] data path/file = "           << p_datadir.c_str()<< std::endl;
  std::cout << "[-o] output file name =\n"    << ((!p_outputfile.empty()) ? p_outputfile.c_str() : "none given") << std::endl;
  std::cout << "[-c] config file name =\n"    << ((!p_configFile.empty()) ? p_configFile.c_str() : "none given") << std::endl;
  std::cout << "[-m] message level = "<< p_msgLevel << std::endl;
  std::cout << "[-t] N(threads) = "<< p_threads << std::endl;
  std::cout << "[-E] fitEngine = "<< p_fitEngine << std::endl;
  std::cout << "[-M] fitMode = "<< p_fitMode << std::endl;
  std::cout << "[-D] dataTitle = "<< p_dataTitle << std::endl;
  std::cout << "[-T] tempTitle = "<< p_tempTitle << std::endl;
  std::cout << "[-i] NumIterations = "<< p_nIter << std::endl;
  std::cout << "[-r] 2rebin2 = "<< p_rebin << std::endl;
  
}

//load command line options
void RunnerConfig::setOpt(int inArgc, char** inArgv){

  m_argc = inArgc;
  m_argv = inArgv;
  parse();

}

// // TH1* findHisto(const std::vector<TH1*>& _vector, const std::string& _search=""){
  
// //   TH1* value =0;
// //   TString name;
// //   for (int i = 0; i < _vector.size(); ++i)
// //   {
// //     name = _vector.at(i)->GetName();
// //     if(name.Contains(_search.c_str()))
// //       value = 
// //   }
  

// // }
// void createOutput(const std::string& _name,TH1* _fb=0,TH1* _fc=0,TH1* _fl=0){

//   TStyle* aStyle =  AtlasStyle();
//   aStyle->SetOptStat(220002211);
//   gROOT->SetStyle("ATLAS");
//   gROOT->ForceStyle();
  
//   TCanvas c(_name.c_str(),"",3000,1500);
//   c.Clear();
//   c.Draw();
//   c.Divide(3,2);
//   c.cd(1);
//   if(_fb){
//     _fb->Draw();
//   }
//   c.cd(2);
//   if(_fc)
//     _fc->Draw();
//   c.cd(3);
//   if(_fl)
//     _fl->Draw();
  
//   c.cd(4);
//   gPad->SetLogy();
//   if(_fb)
//     _fb->Draw();
//   c.cd(5);
//   gPad->SetLogy();
//   if(_fc)
//     _fc->Draw();
//   c.cd(6);
//   gPad->SetLogy();
//   if(_fl)
//     _fl->Draw();

//   c.Update();
//   c.Print(_name.c_str());

// }


// void createScaledData(const std::vector<TH1*>& _vector,
//                       const std::vector<double>& _scales,
//                       TH1D* _data,
//                       const int& _integral){

//   if(_vector.empty() || !_data){
//     std::cerr << __FILE__ << ":"<< __LINE__ <<"\t inline TH1 pointer vector empty or data histo nil\n";
//     return;}

//   if(_vector.size()!=_scales.size())
//     {
//     std::cerr << __FILE__ << ":"<< __LINE__ <<"\t inline TH1 pointer vector mismatching scale factor vector\n";
//     return;}

//   TH1D* total = dynamic_cast<TH1D*>(_vector.front()->Clone("total"));
//   total->Reset("MICE");
//   total->ResetStats();

//   for (int i = 0; i < _vector.size(); ++i)
//   {
//     total->Add(_vector.at(i),_scales.at(i));
//   }

//   _data->FillRandom(total,_integral);

// }

int main(int argc, char* argv[])
{
  TStyle* aStyle =  AtlasStyle();
  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();

  //set root message level
  //gErrorIgnoreLevel = 2001;
  //
  RunnerConfig conf(argc,argv);
  if(conf.p_giveHelp)
    return -1;
  else
    if(conf.p_msgLevel)
      conf.printConf();

  // ----- INPUT ----- 
  FitterInputs::NormedTH1* input = new FitterInputs::NormedTH1();
  input->loadData(conf.p_datadir.c_str(),conf.p_dataTitle.c_str(),conf.p_rebin);
  input->loadTemplates(conf.p_datadir.c_str(),conf.p_tempTitle.c_str(),conf.p_rebin);
  
  std::vector<TH1*> m_templates;
  input->getTemplatesDeepCopy(m_templates);

  TH1D* m_data=input->getDataDeepCopy();
  
  double dataIntegral = m_data->Integral();
  TRandom3 myRand3;
  // ----- Templates ----- 
  functions::SimpleMaxLLH fcn;
  
  // ----- Results ------
  FitterResults::HistoResult* result = new FitterResults::HistoResult(0,conf.p_msgLevel,"pseudo.root");

  // ----- FitterCore ------
  TH1D pull_fb("fb",";pull fb;N",50,-5.,5.);
  TH1D pull_fc("fc",";pull fc;N",50,-5.,5.);
  TH1D pull_fl("fl",";pull fl;N",50,-5.,5.);
  

  std::vector<double> fitValues(m_templates.size(),0.);
  std::vector<double> fitErrorsUp(m_templates.size(),0.);
  std::vector<double> fitErrorsDown(m_templates.size(),0.);
  std::vector<int>    fitErrorsStatus(m_templates.size(),0.);

  std::vector<double> metaValues(m_templates.size(),0.);
  std::vector<double> metaErrorsUp(m_templates.size(),0.);
  std::vector<double> metaErrorsDown(m_templates.size(),0.);
  std::vector<int>    metaErrorsStatus(m_templates.size(),0.);


  double bPull=0;
  double cPull=0;
  double lPull=0;

  for (int i = 0; i < (conf.p_nIter); ++i)
  {
    
    
    if(i % 50 == 0)
      std::cout << " iteration " << i << "/" << conf.p_nIter << std::endl;

    //init the fitter
    core::FitCore<functions::SimpleMaxLLH,FitterInputs::NormedTH1,FitterResults::AbsResult> fitter(input);
    fitter.configureFromFile(conf.p_configFile);
    fitter.configureKeyWithValue("Engine",conf.p_fitEngine);
    fitter.configureKeyWithValue("Mode",conf.p_fitMode);
    fitter.setupMachinery();

    //run the fitter on data from the input file
    if(conf.p_msgLevel>3)
      fitter.fit(true);
    else
      fitter.fit(false);

    //collect the results
    fitter.getMinosErrorSet(metaErrorsStatus,metaErrorsDown,metaErrorsUp);
    for (int i = 0; i < m_templates.size(); ++i)
    {
     metaValues[i] = fitter.getMinimizer()->X()[i];
    }

    m_data->Reset("MICE");
    m_data->ResetStats();

    //scale b content and
    // add all MC histos according to the just fitted fractions to give pseudo data
    createScaledData(m_templates,metaValues,m_data,myRand3.Poisson(dataIntegral));

    //reset the input
    input->setTemplateHistos(m_templates);
    input->setDataHisto(m_data);
    input->init();

    //fit the pseudo data now
    if(conf.p_msgLevel>3)
      fitter.fit(true);
    else
      fitter.fit(false);


    //collect the results of the second fit
    fitter.getMinosErrorSet(fitErrorsStatus,fitErrorsDown,fitErrorsUp);
    for (int i = 0; i < m_templates.size(); ++i)
    {
     fitValues[i] = fitter.getMinimizer()->X()[i];
    }

    if(fitValues[0]>metaValues[0])
      bPull = (metaValues[0]-fitValues[0])/TMath::Sqrt((fitErrorsDown[0]*fitErrorsDown[0])+(metaErrorsDown[0]*metaErrorsDown[0]));
    else
      bPull = (metaValues[0]-fitValues[0])/TMath::Sqrt((fitErrorsUp[0]*fitErrorsUp[0])+(metaErrorsUp[0]*metaErrorsUp[0]));

    if(fitValues[1]>metaValues[1])
      cPull = (metaValues[1]-fitValues[1])/TMath::Sqrt((fitErrorsDown[1]*fitErrorsDown[1])+(metaErrorsDown[1]*metaErrorsDown[1]));
    else
      cPull = (metaValues[1]-fitValues[1])/TMath::Sqrt((fitErrorsUp[1]*fitErrorsUp[1])+(metaErrorsUp[1]*metaErrorsUp[1]));

    if(fitValues[2]>metaValues[2])
      lPull = (metaValues[2]-fitValues[2])/TMath::Sqrt((fitErrorsDown[2]*fitErrorsDown[2])+(metaErrorsDown[2]*metaErrorsDown[2]));
    else
      lPull = (metaValues[2]-fitValues[2])/TMath::Sqrt((fitErrorsUp[2]*fitErrorsUp[2])+(metaErrorsUp[2]*metaErrorsUp[2]));
    //}

    pull_fb.Fill(bPull);

    pull_fc.Fill(cPull);

    pull_fl.Fill(lPull);


    ///////////////////////////////////////////
    // panic print
    //
    
    if(TMath::Abs(bPull)>2.5 || TMath::Abs(cPull)>2.5 || TMath::Abs(cPull)>2.5){
      std::ostringstream Name;
      Name << "pseudoExperiment_";
      Name << i << ".root";
      result->setFileName(Name.str().c_str());
      if(conf.p_msgLevel>4)
        fitter.printTo(result);
    }


    
  }

  createOutput(conf.p_outputfile,&pull_fb,&pull_fc,&pull_fl);
  return 0; 
   

}
 
