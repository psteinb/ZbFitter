#pragma once
#ifndef __BASEPERFORMER__HH__
#define __BASEPERFORMER__HH__

#include <fstream>
#include <iostream>
#include <vector>
#include "TString.h"


class BasePerformer
{
  std::vector<double> m_means;
  std::vector<double> m_sigmas;
  std::vector<double> m_expected      ;

public:
  BasePerformer():
    m_means(),
    m_sigmas(),
    m_expected()
  {};

  // BasePerformer(const BasePerformer&):
  //   m_means(),
  //   m_sigmas(),
  //   m_expected()
  // {};

  virtual ~BasePerformer(){};

  void printContent() const {
    std::cout << "\tfound means: " << m_means.size() << "\n\t";
    for (int i = 0; i < m_means.size(); ++i)
    {
      std::cout <<  m_means[i] << ", ";
    }

    std::cout <<  "\t sum = " << std::accumulate(m_means.begin(),m_means.end(),0.) << "\n"
              << "\n\tfound sigmas: " << m_sigmas.size() << "\n\t";

    for (int i = 0; i < m_sigmas.size(); ++i)
    {
      std::cout <<  m_sigmas[i] << ", ";
    }
    std::cout << "\nexpected values\n\t";
    for (int i = 0; i < m_expected.size(); ++i)
    {
      std::cout <<  m_expected[i] << ", ";
    }
    std::cout <<  "\t sum = " << std::accumulate(m_expected.begin(),m_expected.end(),0.) << "\n";
    
  }

  const std::vector<double>* getMeans(){
    return &m_means;
  }

  const std::vector<double>* getSigmas(){
    return &m_sigmas;
  }

  const std::vector<double>* getExpected(){
    return &m_expected;
  }

   void setMeans(const std::vector<double>& _new){
    m_means = _new;
  }

  void setSigmas(const std::vector<double>& _new){
    m_sigmas = _new;
  }

  void setExpected(const std::vector<double>& _new){
    m_expected = _new;
  }

  virtual void experiment() = 0 ;
  virtual void print() const = 0;
  virtual void prepare() = 0;

  std::string createScaledConfigFileString(const std::string& _file, const double& _id){
    TString newName = _file.c_str();
    int id = int(_id*100.);
    TString toInsert = "_";
    toInsert += id;
    toInsert += ".env";
    newName.ReplaceAll(".env",toInsert);

    fstream test;
    test.open(newName.Data(),std::ios::in);
    if(test.is_open()){
      test.close();
      return newName.Data();}
    else
      return _file;

    
  }
};

//small class

#endif
