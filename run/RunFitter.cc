
#include <iostream>
#include <exception>
#include "TROOT.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TChain.h"
//available for ROOT version 5.26 or higher
//#include "TTreePerfStats.h"
#include "TStopwatch.h"

#include "ZBAnalysis/ZBAnalysis.hh"
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "stdio.h"
#include "unistd.h"

Logger::TLog gLog(Logger::INFO);
//small class
class RunnerConfig {

private:
  int m_argc;
  char** m_argv;
  
public:
  std::vector<std::string> p_alldatadir;
  std::string p_datadir;
  std::string p_outputfile;
  std::string p_slicefile;
  std::string p_anaIni;
  std::string p_braIni;
  std::string p_GRL;
  std::string p_mcTrigger;
  int         p_numevents;
  int         p_msgLevel;
  int         p_threads;
  bool        p_givehelp;
  bool        p_isfile;
  bool        p_dumpPerf;
  bool        p_isESD;
  bool        p_isData;

  
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
  p_alldatadir(),
  p_datadir("/some/path/"),
  p_outputfile(""),
  p_slicefile(""),
  p_anaIni("analysis.ini"),
  p_braIni("branches.ini"),
  p_GRL(""),
  p_mcTrigger("EF_mu13_MG"),
  p_numevents(-1),
  p_msgLevel(2),
  p_threads(1),
  p_givehelp(false),
  p_isfile(false),
  p_dumpPerf(false),
  p_isESD(false),
  p_isData(false)
{}

//constructor with initialisation
RunnerConfig::RunnerConfig(int inArgc, char** inArgv):
  m_argc(inArgc),m_argv(inArgv),
  p_alldatadir(),
  p_datadir("/some/path/"),
  p_outputfile(""),
  p_slicefile(""),
  p_anaIni("analysis.ini"),
  p_braIni("branches.ini"),
  p_GRL(""),
  p_mcTrigger("EF_mu13_MG"),
  p_numevents(-1),
  p_msgLevel(2),
  p_threads(1),
  p_givehelp(false),
  p_isfile(false),
  p_dumpPerf(false),
  p_isESD(false),
  p_isData(false)
{

  parse();

}

void RunnerConfig::parse(){


  int opt = 0;
  while( (opt = getopt(m_argc, m_argv, "a:b:d:f:n:m:g:s:t:T:epDh" ))!=-1 ){
    std::istringstream instream;
    std::ostringstream outstream;
    size_t found;
    int meta=0;
    switch(opt){
    case 'd':
      outstream << optarg;
      //check if given argument extents to multiple comma seperated names
      if((found = outstream.str().find(",")) != std::string::npos  ){
        int position = 0;
        while(position != std::string::npos){
          int start = (position!=0) ? position+1 : 0;
          position = outstream.str().find(",",position+1);
          p_alldatadir.push_back(outstream.str().substr(start,position-start));
        }
      }else{
        //check if given argument is a root FILENAME
        if((found = outstream.str().find(".root")) != std::string::npos  ){
          p_isfile = true;
        }
        else{//if not, it is a directory
          if( ((found = outstream.str().find_last_of("/")) > (outstream.str().size()-2)) )
            outstream << "*.root";
          else
            outstream << "/*.root";
        }
        p_alldatadir.push_back(outstream.str());
      }
      p_datadir = outstream.str();//optarg was defined in unistd.h      
      
      break;
    case 'a':
      p_anaIni = std::string(optarg);
      break;
    case 'b':
      p_braIni = std::string(optarg);
      break;
    case 'f':
      p_outputfile = std::string(optarg);
      break;
    case 's':
      p_slicefile = std::string(optarg);
      break;
    case 'g':
      p_GRL = std::string(optarg);
      break;
    case 't':
      p_mcTrigger = std::string(optarg);
      break;
    case 'n':
      instream.str(optarg);
      if( !(instream >> meta) ){
        std::cerr << "D3PDRunner \t invalid argument format for [-n]" << std::endl;
        p_numevents = 0;
      }
      else{
        p_numevents = meta;
      }
      break;
    case 'm':
      instream.str(optarg);
      if( !(instream >> meta) ){
        std::cerr << "D3PDRunner \t invalid argument format for [-m]" << std::endl;
        p_msgLevel = 0;
      }
      else{
        p_msgLevel = meta;
      }

      break;
    case 'T':
      instream.str(optarg);
      if( !(instream >> meta) ){
        std::cerr << "D3PDRunner \t invalid argument format for [-T]" << std::endl;
        p_threads = 0;
      }
      else{
        p_threads = meta;
      }

      break;

    case 'p':
      p_dumpPerf = true;
      break;
    case 'e':
      p_isESD = true;
      break;
    case 'D':
      p_isData = true;
      break;
    case 'h':
      p_givehelp = true;
      printHelp();
      break;
    default:
      p_givehelp = true;
      std::cout << "D3PDRunner -- Unknown input: -"<< (char)optopt << "\t" << optarg << "\n" << std::endl;
      printHelp();
      break;
    }

  }
  
}

//function to print help text
void RunnerConfig::printHelp(){

  std::cout << "D3PDRunner" << std::endl;
  std::cout << "=============" << std::endl;
  std::cout << "Executable for Running D3PDSelector on given datasets" << std::endl;
  std::cout << "\t $> D3PDRunner <options>" << std::endl;
  std::cout << "\t -a <arg> location of analysis steering file " << std::endl;
  std::cout << "\t -b <arg> location of branch steering file " << std::endl;
  std::cout << "\t -d <args> define data directory,file name or comma-seperated list of file names " << std::endl;
  std::cout << "\t -f <foo.root> set output file name (to foo.root)" << std::endl;
  std::cout << "\t -s <bar.root> set slice file name BASE (no suffix), if slicing to be done (to bar.root)" << std::endl;
  std::cout << "\t -n <num> run on <num> events of this chain" << std::endl;
  std::cout << "\t -m set message level (0=VERBOSE,..,2=INFO,..,5=ERROR)" << std::endl;
  std::cout << "\t -p enable ROOT performance histos (output to ./ZBAnalysisPerformance.root)" << std::endl;
  std::cout << "\t -e input file is from ESD origin" << std::endl;
  std::cout << "\t -D input file is from Data origin" << std::endl;
  std::cout << "\t -g <name> GRL file name " << std::endl;
  std::cout << "\t -t <trigger> trigger item to use in MC " << std::endl;
  std::cout << "\t -T <num> number of threads to use " << std::endl;
  std::cout << "\t -h print this help" << std::endl;
  std::cout << std::endl;


}

//function to print current config
void RunnerConfig::printConf(){

  std::cout << "D3PDRunner running on" << std::endl;
  std::cout << "[-d] data path = "           << p_datadir.c_str() << "\t" << ((p_isfile) ? "-f-":"-d-" )<< std::endl;
  if(!p_alldatadir.empty()){
    for(int i = 0;i<p_alldatadir.size();i++)
      std::cout << p_alldatadir.at(i).c_str()<< "\n";
  }
  std::cout << "[-a] analsys steering " << p_anaIni.c_str() << std::endl;
  std::cout << "[-b] branch steering " << p_braIni.c_str() << std::endl;
  std::cout << "[-f] output file name =\n"    << ((!p_outputfile.empty()) ? p_outputfile.c_str() : "none given") << std::endl;
  std::cout << "[-s] slice file name (if set, enables slicing) =\n"    << ((!p_slicefile.empty()) ? p_slicefile.c_str() : "none given") << std::endl;
  std::cout << "[-n] num events = "          << p_numevents << std::endl;
  std::cout << "[-p] perfstats = "          << p_dumpPerf << std::endl;
  if(!p_GRL.empty())
    std::cout << "[-g] GRL = "          << p_GRL.c_str() << std::endl;
  std::cout << "[-t] mcTrigger = "          << p_mcTrigger.c_str() << std::endl;
  std::cout << "[-e] ESD origin = " << p_isESD << std::endl;
  std::cout << "[-D] Data origin = " << p_isData << std::endl;
  std::cout << "[-m] message level = "<< p_msgLevel << std::endl;
  std::cout << "[-T] N(threads) = "<< p_threads << std::endl;

}

//load command line options
void RunnerConfig::setOpt(int inArgc, char** inArgv){

  m_argc = inArgc;
  m_argv = inArgv;
  parse();

}




int main(int argc, char* argv[])
{
  gErrorIgnoreLevel = 2001;
  //
  RunnerConfig conf(argc,argv);
  if(conf.p_givehelp)
    return -1;
  
  // ----- LAUNCHING ----- 
  TChain* ToRunChain = new TChain("physics");
  if(!conf.p_alldatadir.empty()){
    for(int i = 0;i<conf.p_alldatadir.size();i++)
      ToRunChain->Add(conf.p_alldatadir.at(i).c_str());
  }
  else
    ToRunChain->Add(conf.p_datadir.c_str());
  
  if(conf.p_dumpPerf){
    ToRunChain->SetCacheLearnEntries(20);
    ToRunChain->SetCacheSize(50*1000*1000);

    ToRunChain->AddBranchToCache("trk_*");
    ToRunChain->AddBranchToCache("mu_staco_*");
    ToRunChain->AddBranchToCache("mu_muid_*");
    ToRunChain->AddBranchToCache("jet_antikt6h1topo_*");
    ToRunChain->AddBranchToCache("jet_antikt6h1tower_*");
    ToRunChain->AddBranchToCache("jet_antikt4h1topo_*");
    ToRunChain->AddBranchToCache("jet_antikt4h1tower_*");

    if(conf.p_isData){
      ToRunChain->AddBranchToCache("mc_*");
      ToRunChain->AddBranchToCache("*jet_antikt6truth_*");
      ToRunChain->AddBranchToCache("*jet_antikt4truth_*");
    }

  }


  int NumEvents = conf.p_numevents;
  gLog.setColor(Logger::YELLOW);
  int events = ToRunChain->GetEntries();
  gLog << "D3PDRunner \t fChain detected with "<< events << " entries" << Logger::END;
  if(NumEvents>0)
    gLog << "D3PDRunner \t running only on  "<< NumEvents << " entries" << Logger::END;
  gLog.resetColor();
    
    
  ZBAnalysis* ctselector = new ZBAnalysis();
  ctselector->isESD(conf.p_isESD);
  ctselector->isFromData(conf.p_isData);
  ctselector->setDBGLevel(conf.p_msgLevel);
  ctselector->setRunLimit(NumEvents);
  ctselector->setAnalysisConfigFile(conf.p_anaIni);
  ctselector->setBranchesConfigFile(conf.p_braIni);
  ctselector->setNumberOfThreads(conf.p_threads);
  ctselector->setMCTriggerName(conf.p_mcTrigger);

  if(!conf.p_outputfile.empty())
    ctselector->setFileName(conf.p_outputfile.c_str());
  if(!conf.p_slicefile.empty())
    ctselector->setFindAndSlice(conf.p_slicefile.c_str());
  if(!conf.p_GRL.empty())
    ctselector->setGRLFileName(conf.p_GRL.c_str());
  conf.printConf();

  TStopwatch watch;

  try{
    watch.Start();
    ToRunChain->Process(ctselector);
    watch.Stop();
  }
  catch(std::exception& ex){
    std::cout << "ToRunChain->Process ... threw exception\t"<< ex.what() << std::endl;
  }

    //ps->Finish();
    double cput  = watch.CpuTime();
    double realt = watch.RealTime();
    

    if(events){
      gLog << Logger::INFO << "Runner \t  CpuTime = \t"<< std::setw(10) << std::setprecision(4)<< cput << " ( "<< std::setw(10)<< cput/events<<" per event )"<< Logger::END;
      gLog << Logger::INFO << "Runner \t  RealTime = \t"<< std::setw(10) << std::setprecision(4)<< realt << " ( "<< std::setw(10)<< realt/events<<" per event )"<< Logger::END;
      
    }

   
  return 0; 
   

}
 
