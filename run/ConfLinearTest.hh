#pragma once
#ifndef __CONFLINTEST__HH__
#define __CONFLINTEST__HH__
#include <string>

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
  bool        p_giveHelp;
  double      p_stepsize;
  
  ConfLinearTest();
  ConfLinearTest(int , char**);
  void printHelp();
  void printConf();
  void setOpt(int , char** );
  void parse();

};


#endif
