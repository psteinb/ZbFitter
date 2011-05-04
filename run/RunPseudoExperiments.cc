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
#include "FitterInputs/NormalisationFunctors.hh"
#include "FitterInputs/NormedTH1.hh"
#include "FitterResults/HistoResult.hh"
#include "functions/BinnedEML.hh"
#include "Studies/PseudoStudy.hh"

#include "TString.h"
#include "TRegexp.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TRandom3.h"
#include "TMath.h"
#include "TArrow.h"
#include "TPad.h"
#include "TPaveStats.h"

#include "AtlasStyle.h"

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
  double      p_pseudoDataNormFactor;
  
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
  p_pseudoDataNormFactor(1.),
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
  p_pseudoDataNormFactor(1.),
  p_nIter(10000.),
  p_rebin(1)
{

  parse();

}

void RunnerConfig::parse(){


  int opt = 0;
  while( (opt = getopt(m_argc, m_argv, "d:o:c:m:t:E:M:D:T:P:i:r:h" ))!=-1 ){
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
    case 'P':
      instream.str(optarg);
      if( !(instream >> dmeta) ){
        std::cerr << "RunFitter \t invalid argument format for [-P]" << std::endl;
        p_pseudoDataNormFactor = 1.;
      }
      else{
        p_pseudoDataNormFactor = dmeta;
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
  std::cout << "\t -m set message level (0=NONE,1=TERMPANIC,2=INFO)" << std::endl;
  std::cout << "\t -t <num> number of threads to use " << std::endl;
  std::cout << "\t -E <TMinuitEngine> define fit engine" << std::endl;
  std::cout << "\t -M <TMinuitMode> define fit mode" << std::endl;
  std::cout << "\t -D <ObjectName> define data object to retrieve from root file" << std::endl;
  std::cout << "\t -T <ObjectName> define template (+systematics) object(s) to retrieve from root file" << std::endl;
  std::cout << "\t -P <NormFactor> to apply to the data statistics to (if NormFactor<0, the data statistics IS NOT DRAWN from a POISSON(data statistics)" << std::endl;
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
  std::cout << "[-P] NormFactor = "<< p_pseudoDataNormFactor << std::endl;
  std::cout << "[-i] NumIterations = "<< p_nIter << std::endl;
  std::cout << "[-r] 2rebin2 = "<< p_rebin << std::endl;
  
}

//load command line options
void RunnerConfig::setOpt(int inArgc, char** inArgv){

  m_argc = inArgc;
  m_argv = inArgv;
  parse();

}

struct defaultMCValues
{
  

  void operator()(TH1* _total, const std::vector<TH1*>& _input){

    if(_total->GetEntries()!=0){
      _total->Reset("MICE");
      _total->ResetStats();}
    

    for (int i = 0; i < _input.size(); ++i)
    {
      _total->Add(_input[i]);
    }
    
  };

  //private:

};


void createExpectedValuesFromTemplates(const std::vector<TH1*>& _templates,
                                       std::vector<double>& _expected,
                                       std::vector<double>& _errors,
                                       const double& _dataIntegral){

  _expected.clear();
  _expected.resize(_templates.size(),0.);
  _errors.clear();
  _errors.resize(_templates.size(),0.);
  

  
  std::vector<double> integrals(_templates.size(),0.);
  std::vector<double> errors(_templates.size(),0.);
  double total = 0.;
  for (int i = 0; i < _templates.size(); ++i)
  {
    integrals[i] = _templates[i]->IntegralAndError(_templates[i]->GetXaxis()->GetFirst(),
                                                   _templates[i]->GetXaxis()->GetLast(),
                                                   errors[i]
                                                   );
    total += integrals[i];
  }


  for (int i = 0; i < _templates.size(); ++i)
  {
    _expected[i] = (integrals[i]/total)*_dataIntegral;
    _errors[i] = (errors[i]/total)*_expected[i];
    std::cout << "expected value ["<<i <<"]\t"<<_expected[i]<<" +/- "<<_errors[i] <<std::endl;
  }

}

// void addVerticalArrowToPad(TVirtualPad* _thisPad, TArrow* _arrow,const double& _value=0.){
  
//   if(!(_value!=0.))
//     return;

//   double xpos = _thisPad->XtoPad(_value);
//   double yStart = _thisPad->GetUymin();
//   double yEnd = _thisPad->GetUymax();
//   _arrow->DrawArrow(xpos,yStart,
//                     xpos,yEnd,
//                     0.03,"<");

// }

int main(int argc, char* argv[])
{
  TStyle* aStyle =  AtlasStyle();
  aStyle->SetStatY(1.);
  aStyle->SetStatX(.95);
  aStyle->SetStatW(.8);
  aStyle->SetStatH(0.15);
  aStyle->SetStatBorderSize(0.);
  aStyle->SetPadTopMargin(0.2);
  //aStyle->SetHistTopMargin(0.3);
  aStyle->SetOptStat(2210);
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
  FitterInputs::NormedTH1<FitterInputs::Norm2Unity>* input = new FitterInputs::NormedTH1<FitterInputs::Norm2Unity>();
  input->loadData(conf.p_datadir.c_str(),conf.p_dataTitle.c_str(),conf.p_rebin);
  input->loadTemplates(conf.p_datadir.c_str(),conf.p_tempTitle.c_str(),conf.p_rebin);

  std::vector<TH1*> m_templates;
  input->getTemplatesDeepCopy(m_templates);
  TH1* m_data =  input->getDataDeepCopy();

   // ----- EXPECTED VALUES ----- 
  std::vector<double> expected          ;
  std::vector<double> expectedErrors    ;
  createExpectedValuesFromTemplates(m_templates,
                                    expected,          
                                    expectedErrors,
                                    m_data->Integral()*TMath::Abs(conf.p_pseudoDataNormFactor));

   // ----- PSEUDO EXPERIMENTS ----- 
  double scaleExpectation = TMath::Abs(conf.p_pseudoDataNormFactor);
  PseudoStudy<defaultMCValues,FitterInputs::NormedTH1<FitterInputs::Norm2Unity>, functions::BinnedEML>  
    aPseudoStudy(m_templates,
                 expected,
                 expectedErrors,
                 conf.p_pseudoDataNormFactor*(m_data->Integral()),
                 conf.p_threads,
                 conf.p_nIter
                 );

  aPseudoStudy.setInput(input);
  aPseudoStudy.setFitterConfigFile(conf.p_configFile);
  aPseudoStudy.setFitEngine(conf.p_fitEngine);
  aPseudoStudy.setFitMode(conf.p_fitMode);
  aPseudoStudy.setVerbosity(conf.p_msgLevel);
  aPseudoStudy.setBaseName(conf.p_outputfile);
  if(conf.p_msgLevel<3)
    aPseudoStudy.setPanicPrint(true);
  aPseudoStudy.experiment();
  
  

   // ----- COLLECT RESULTS ----- 
  std::vector<std::vector<TH1*> > m_results(m_templates.size());
  for (int i = 0; i < m_templates.size(); ++i)
  {
    aPseudoStudy.getResultsOfParameter(i,m_results[i]);
  }
  
  
  // ----- DRAW RESULTS IN ONE PAD ----- 
  TCanvas myResults(conf.p_outputfile.c_str(),"",3000,2000);
  myResults.Clear();
  myResults.Draw();
  myResults.Divide(3,m_templates.size());
  int padSize = 3*m_templates.size();
  TArrow anArrow;
  anArrow.SetLineColor(kBlue);
  anArrow.SetLineWidth(2);
  int currentPad=0;
  int padStart=1;
  for (int i = 0; i < m_results.size(); ++i,padStart+=3)
  {
    for (int pad = 0; pad < 3; ++pad)
    {
      currentPad= pad + padStart;
      myResults.cd(currentPad);
      m_results[i][pad]->Draw();
      if(pad<1){
        myResults.Update();
        anArrow.DrawArrow(gPad->XtoPad(scaleExpectation*expected[i]),gPad->GetUymin(),
                          gPad->XtoPad(scaleExpectation*expected[i]),gPad->GetUymax(),0.03,"<|");
      }
      
    }
  }
  myResults.Update();
  myResults.Print(".eps");

    // ----- DRAW MEAN RESULTS IN ONE PAD ----- 
  std::string name = conf.p_outputfile;
  name += "_means";
  TCanvas MeanCanvas(name.c_str(),"",3000,1000);
  MeanCanvas.Clear();
  MeanCanvas.Draw();
  MeanCanvas.Divide(m_templates.size(),1);
  int pad=1;
  for (int i = 0; i < m_results.size(); ++i,pad++)
  {
    MeanCanvas.cd(pad);
    // if(i<1){
    m_results[i][0]->Draw();
      MeanCanvas.Update();
      anArrow.DrawArrow(gPad->XtoPad(scaleExpectation*expected[i]),gPad->GetUymin(),
                        gPad->XtoPad(scaleExpectation*expected[i]),gPad->GetUymax(),0.03,"<|");
    // }
    
    
  }
  MeanCanvas.Update();
  MeanCanvas.Print(".eps");

    // ----- DRAW PULL RESULTS IN ONE PAD ----- 
  name = conf.p_outputfile;
  name += "_pulls";
  TCanvas PullCanvas(name.c_str(),"",3000,1000);
  PullCanvas.Clear();
  PullCanvas.Draw();
  PullCanvas.Divide(m_templates.size(),1);
  pad=1;
  TPaveStats *stats=0;
  
  for (int i = 0; i < m_results.size(); ++i,pad++)
  {
    PullCanvas.cd(pad);
    m_results[i][2]->Draw();
    PullCanvas.Update();
    stats = (TPaveStats*)m_results[i][2]->FindObject("stats");
    if(stats){
      stats->SetY2(gPad->GetUymax());
      stats->SetY1(gPad->GetUymax()*.75);
      stats->SetX2(gPad->GetUxmax());
      stats->SetX1(gPad->GetUxmin()*.25);
    }
  }
  PullCanvas.Update();
  PullCanvas.Print(".eps");


  name = conf.p_outputfile;
  name += "_maxLLH";

  TCanvas PseudoMaxLLH(name.c_str(),"",800,600);
  PseudoMaxLLH.Clear();
  PseudoMaxLLH.Draw();
  PseudoMaxLLH.cd(0);
  aPseudoStudy.getMaxLLHDistribution()->Print("all");
  aPseudoStudy.getMaxLLHDistribution()->Draw();
  PseudoMaxLLH.Update();
  PseudoMaxLLH.Print(".eps");

  aPseudoStudy.printResults();
  return 0; 
   

}
 
