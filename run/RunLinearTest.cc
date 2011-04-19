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
#include "AtlasStyle.h"
#include "TCanvas.h"

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
  int         p_rebin;
  bool        p_giveHelp;
  double      p_stepsize;
  
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
  p_outputfile(""),
  p_configFile(""),
  p_fitEngine("Minuit2"),
  p_fitMode  ("Scan"),
  p_dataTitle("data"),
  p_tempTitle("mcb,mcc,mcl"),
  p_msgLevel(3),
  p_threads(1),
  p_rebin(1),
  p_giveHelp(false),
  p_stepsize(.2)
{}

//constructor with initialisation
RunnerConfig::RunnerConfig(int inArgc, char** inArgv):
  m_argc(inArgc),m_argv(inArgv),
  p_datadir("/some/path/"),
  p_outputfile(""),
  p_configFile(""),
  p_fitEngine("Minuit2"),
  p_fitMode  ("Scan"),
  p_dataTitle("data"),
  p_tempTitle("mcb,mcc,mcl"),
  p_msgLevel(3),
  p_threads(1),
  p_rebin(1),
  p_giveHelp(false),
  p_stepsize(.2)
{

  parse();

}

void RunnerConfig::parse(){


  int opt = 0;
  while( (opt = getopt(m_argc, m_argv, "d:o:c:m:t:r:E:M:D:T:s:h" ))!=-1 ){
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
    case 'r':
      instream.str(optarg);
      if( !(instream >> meta) ){
        std::cerr << "RunFitter \t invalid argument format for [-r]" << std::endl;
        p_rebin = 1;
      }
      else{
        p_rebin = meta;
      }

      break;
    case 's':
      instream.str(optarg);
      if( !(instream >> dmeta) ){
        std::cerr << "RunFitter \t invalid argument format for [-s]" << std::endl;
        p_stepsize = 0;
      }
      else{
        p_stepsize = dmeta;
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
  std::cout << "\t -r <Count> Rebin Count to call on input histos " << std::endl;
  std::cout << "\t -E <TMinuitEngine> define fit engine" << std::endl;
  std::cout << "\t -M <TMinuitMode> define fit mode" << std::endl;
  std::cout << "\t -D <ObjectName> define data object to retrieve from root file" << std::endl;
  std::cout << "\t -T <ObjectName> define template (+systematics) object(s) to retrieve from root file" << std::endl;
  std::cout << "\t -s <step size> define step size to go from 0 .. 1 of the b fraction" << std::endl;
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
  std::cout << "[-r] rebin = "<< p_rebin << std::endl;
  std::cout << "[-D] dataTitle = "<< p_dataTitle << std::endl;
  std::cout << "[-T] tempTitle = "<< p_tempTitle << std::endl;
  std::cout << "[-s] stepSize = "<< p_stepsize << std::endl;
  
}

//load command line options
void RunnerConfig::setOpt(int inArgc, char** inArgv){

  m_argc = inArgc;
  m_argv = inArgv;
  parse();

}



void createScaledData(const std::vector<TH1*>& _vector,double _scale,TH1D* _data){

  if(_vector.empty() || !_data){
    std::cerr << __FILE__ << ":"<< __LINE__ <<"\t inline TH1 pointer vector empty or data histo nil\n";
    return;}

  std::cout << ">>> old content " << _data->GetEntries() << ", "<< _data->GetNbinsX() <<"\n";
  TString name;
  for (int i = 0; i < _vector.size(); ++i)
  {
    name = _vector.at(i)->GetName();
    name.ToLower();
    if(name.Contains(TRegexp(".*mcb.*")) || name.Contains(TRegexp(".*trueb.*"))){
      std::cout << ">>> scaled " << name.Data() << " by " << _scale << " from "<< _vector.at(i)->Integral();
      _data->Add(_vector.at(i),_scale);

    }
    else{
      _data->Add(_vector.at(i),1.);
      std::cout << ">>> added "<<_vector.at(i)->GetEntries() << "\n";
    }
  }

  std::cout << ">>> new content " << _data->GetEntries() << ", "<< _data->GetNbinsX() << "\n";

}

std::string stripRootString(const std::string& _filename){
  
  size_t pos = _filename.find(".root");
  if(pos!=std::string::npos)
    return _filename.substr(0,pos);
  else
    return _filename;

}

void cloneTH1VectorFromTo(const std::vector<TH1*>& _reference, std::vector<TH1*>& _target){
  
  _target.clear();
  _target.resize(_reference.size(),0);
  std::string newName;
  for (int i = 0; i < _reference.size(); ++i)
  {
    newName = _reference.at(i)->GetName();
    newName += "_cloned";
    _target[i] = dynamic_cast<TH1*>(_reference.at(i)->Clone(newName.c_str()));
  }

}

void deleteTH1InVector(std::vector<TH1*>& _vec){
  

  for (int i = 0; i < _vec.size(); ++i)
  {
    delete _vec[i];
    _vec[i]=0;
  }

  _vec.clear();
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
  std::vector<TH1*> m_meta;
  input->getTemplatesDeepCopy(m_templates);
  cloneTH1VectorFromTo(m_templates,m_meta);

  // ----- Templates ----- 
  functions::SimpleMaxLLH fcn;
  
  // ----- Results ------
  FitterResults::HistoResult* result;

  // ----- FitterCore ------
  TH1D* m_data = dynamic_cast<TH1D*>(m_templates.front()->Clone("linearData"));
  
  int steps = 2./conf.p_stepsize;
  TGraph linResults(steps);
  TGraphErrors linResults0(steps);
  TGraphErrors linResults1(steps);
  TGraphErrors linResults2(steps);
  TGraph Line(2);
  double fitValue = 0;
  double fitUncertainty = 0;
  double scale = 0.;

  for (int i = 1; i < (steps+1); ++i)
  {
    //clear input
    //input->clear();
    m_data->Reset("MICE");
    m_data->ResetStats();

    //scale b content and add all histos
    scale = i*conf.p_stepsize;
    createScaledData(m_meta,scale,m_data);

    //reset the input (attention, the following 2 calls copy pointers)
    input->setTemplateHistos(m_meta);
    input->setDataHisto(m_data);
    input->init();

    //init the fitter
    core::FitCore<functions::SimpleMaxLLH,FitterInputs::NormedTH1,FitterResults::AbsResult> fitter(input);
    fitter.configureFromFile(conf.p_configFile);
    fitter.configureKeyWithValue("Engine",conf.p_fitEngine);
    fitter.configureKeyWithValue("Mode",conf.p_fitMode);
    fitter.setupMachinery();

    //fit
    fitter.fit(true);

    //plot the results
    fitValue = fitter.getMinimizer()->X()[0]/m_templates[0]->Integral();
    fitUncertainty = fitter.getMinimizer()->Errors()[0]/fitValue;

    linResults0.SetPoint(i-1,scale,fitValue );
    linResults.SetPoint(i-1,scale,fitValue );
    linResults0.SetPointError(i-1,(conf.p_stepsize)/2,fitUncertainty);

    linResults1.SetPoint(i-1,scale,fitter.getMinimizer()->X()[1] );
    linResults1.SetPointError(i-1,(conf.p_stepsize)/2,fitter.getMinimizer()->Errors()[1]);

    linResults2.SetPoint(i-1,scale,fitter.getMinimizer()->X()[2] );
    linResults2.SetPointError(i-1,(conf.p_stepsize)/2,fitter.getMinimizer()->Errors()[2]);

    //clean-up and reset
    deleteTH1InVector(m_meta);
    cloneTH1VectorFromTo(m_templates,m_meta);
  }

  linResults.SetTitle(";scale factor(f_{b});N_{b,fitted}/N_{b,unscaled}");
  linResults0.SetTitle(";scale factor(f_{b});N_{b,fitted}");
  linResults1.SetTitle(";scale factor(f_{b});N_{c,fitted}");
  linResults2.SetTitle(";scale factor(f_{b});N_{l,fitted}");
  linResults0.SaveAs(conf.p_outputfile.c_str());
  std::string coreName = stripRootString(conf.p_outputfile);
  
  TCanvas myCanvas(coreName.c_str(),"",800,600);
  myCanvas.Clear();
  myCanvas.Draw();
  myCanvas.Divide(2,1);
  myCanvas.cd(1);
  linResults0.Draw("AP+");
  linResults0.GetXaxis()->SetRangeUser(0.,(2.+conf.p_stepsize));

  myCanvas.cd(2);  
  gPad->SetGrid(1,1);
  
  linResults.Draw("AP+");
  linResults.GetXaxis()->SetRangeUser(0.,(2.+conf.p_stepsize));
  // Line.SetPoint(0,0,0);
  // Line.SetPoint(1,2+conf.p_stepsize,2+conf.p_stepsize);
  // Line.SetLineColor(kGray);
  // Line.SetLineStyle(3);
  // Line.Draw("L");

  myCanvas.Update();
  myCanvas.Print(".eps");

  return 0; 
   

}
 
