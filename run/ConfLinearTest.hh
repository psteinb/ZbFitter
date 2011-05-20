#pragma once
#ifndef __CONFLINTEST__HH__
#define __CONFLINTEST__HH__
#include <string>
#include <utility>
#include "TString.h"
#include "TObjArray.h"
#include "TObjString.h"

class ConfLinearTest {

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
  int         p_nIter;
  bool        p_giveHelp;
  double      p_stepsize;
  std::pair<double,double>      p_scaleRange;
  double      p_dataScale;
  bool        p_doFractions;

  ConfLinearTest():
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
  p_nIter(1),
  p_giveHelp(false),
  p_stepsize(.25),
  p_scaleRange(std::make_pair(0.5,1.5)),
  p_dataScale(1.),
  p_doFractions(false)
{};

  ConfLinearTest(int , char**);
  void printHelp();
  void printConf();
  void setOpt(int , char** );
  void parse();
  std::pair<std::string,std::string> getCommaSeparatedPair(const std::string& _text){
    if(_text.empty())
      return std::make_pair(std::string(""),std::string(""));
    else{
      TString data = _text.c_str();
      if(!data.Contains(","))
        return std::make_pair(_text,std::string(""));
      else{
        // TObjArray* tokens = data.Tokenize(",");
        // return std::make_pair(std::string(dynamic_cast<TObjString*>(tokens->At(0))->GetString().Data()),
        //                       std::string(dynamic_cast<TObjString*>(tokens->At(1))->GetString().Data()));
        size_t pos = _text.find(",");
        std::string first = _text.substr(0,pos);
        std::string second = _text.substr(pos+1);
        return std::make_pair(first,second);
      }
    }
    
  };
};

//constructor with initialisation
ConfLinearTest::ConfLinearTest(int inArgc, char** inArgv):
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
  p_nIter(1),
  p_giveHelp(false),
  p_stepsize(.25),
  p_scaleRange(std::make_pair(.5,1.5)),
  p_dataScale(1.),
  p_doFractions(false)
{

  parse();

}

void ConfLinearTest::parse(){


  int opt = 0;
  while( (opt = getopt(m_argc, m_argv, "d:o:c:m:t:r:i:E:M:D:T:P:s:R:hF" ))!=-1 ){
    std::string value = "";
    std::pair<std::string,std::string> stringPair;
    std::istringstream instream;
    std::istringstream altInstream;
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
    case 'i':
      instream.str(optarg);
      if( !(instream >> meta) ){
        std::cerr << "RunFitter \t invalid argument format for [-r]" << std::endl;
        p_nIter = 1;
      }
      else{
        p_nIter = meta;
      }
      break;
    case 't':
      instream.str(optarg);
      if( !(instream >> meta) ){
        std::cerr << "RunFitter \t invalid argument format for [-t]" << std::endl;
        p_threads = 1;
      }
      else{
        p_threads = meta;
      }
      break;
    case 'P':
      instream.str(optarg);
      if( !(instream >> dmeta) ){
        std::cerr << "RunFitter \t invalid argument format for [-P]" << std::endl;
        p_dataScale = 1;
      }
      else{
        p_dataScale = dmeta;
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
    case 'R':
      value = optarg;
      stringPair = getCommaSeparatedPair(value);
      instream.str(stringPair.first);
      if( !(instream >> dmeta) ){
        std::cerr << "RunFitter \t invalid first argument format for [-r]" << std::endl;
        p_scaleRange.first = 0;
      }
      else{
        p_scaleRange.first = dmeta;
      }
      altInstream.str("");
      altInstream.str(stringPair.second);
      if( !(altInstream >> dmeta) ){
        std::cerr << "RunFitter \t invalid second argument format for [-r]" << std::endl;
        p_scaleRange.second = 0;
      }
      else{
        p_scaleRange.second = dmeta;
      }

      break;
    case 'F':
      p_doFractions = true;
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

  //root is not as thread safe as one thinks
  if(p_threads>1)
    p_msgLevel = 6;
  
}

//function to print help text
void ConfLinearTest::printHelp(){

  std::cout << "RunFitter" << std::endl;
  std::cout << "=============" << std::endl;
  std::cout << "Executable for Running Fitter Algorithms on given datasets" << std::endl;
  std::cout << "\t $> RunFitter <options>" << std::endl;
  std::cout << "\t -d <args> define data directory" << std::endl;
  std::cout << "\t -o <foo.root> set output file name (to foo.root)" << std::endl;
  std::cout << "\t -c <bar.env> set TEnv style config file" << std::endl;
  std::cout << "\t -m set message level (0=VERBOSE,..,2=INFO,..,5=ERROR)" << std::endl;
  std::cout << "\t -t <num> number of threads to use " << std::endl;
  std::cout << "\t -i <num> number of iteratios per step " << std::endl;
  std::cout << "\t -r <Count> Rebin Count to call on input histos " << std::endl;
  std::cout << "\t -E <TMinuitEngine> define fit engine" << std::endl;
  std::cout << "\t -M <TMinuitMode> define fit mode" << std::endl;
  std::cout << "\t -D <ObjectName> define data object to retrieve from root file" << std::endl;
  std::cout << "\t -P <scale> scale data per experiment by <scale>" << std::endl;
  std::cout << "\t -T <ObjectName> define template (+systematics) object(s) to retrieve from root file" << std::endl;
  std::cout << "\t -s <step size> define step size to go from 0 .. 1 of the b fraction" << std::endl;
  std::cout << "\t -R <begin,end> define range to vary b fraction" << std::endl;
  std::cout << "\t -F do fraction fit" << std::endl;
  std::cout << "\t -h print this help" << std::endl;
  std::cout << std::endl;


}

//function to print current config
void ConfLinearTest::printConf(){

  std::cout << "RunFitter running on" << std::endl;
  std::cout << "[-d] data path/file = "           << p_datadir.c_str()<< std::endl;
  std::cout << "[-o] output file name =\n"    << ((!p_outputfile.empty()) ? p_outputfile.c_str() : "none given") << std::endl;
  std::cout << "[-c] config file name =\n"    << ((!p_configFile.empty()) ? p_configFile.c_str() : "none given") << std::endl;
  std::cout << "[-m] message level = "<< p_msgLevel << std::endl;
  std::cout << "[-t] N(threads) = "<< p_threads << std::endl;
  std::cout << "[-E] fitEngine = "<< p_fitEngine << std::endl;
  std::cout << "[-M] fitMode = "<< p_fitMode << std::endl;
  std::cout << "[-P] dataScale = "<< p_dataScale << std::endl;
  std::cout << "[-r] rebin = "<< p_rebin << std::endl;
  std::cout << "[-i] iter = "<< p_nIter << std::endl;
  std::cout << "[-D] dataTitle = "<< p_dataTitle << std::endl;
  std::cout << "[-T] tempTitle = "<< p_tempTitle << std::endl;
  std::cout << "[-s] stepSize = "<< p_stepsize << std::endl;
  std::cout << "[-F] doFractions? = "<< ((p_doFractions) ? "yes" : "no") << std::endl;
  std::cout << "[-r] scaleRange = ["<< p_scaleRange.first << ","<< p_scaleRange.second <<"]"<< std::endl;
  
}

//load command line options
void ConfLinearTest::setOpt(int inArgc, char** inArgv){

  m_argc = inArgc;
  m_argv = inArgv;
  parse();

}




#endif
