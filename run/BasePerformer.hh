#pragma once
#ifndef __BASEPERFORMER__HH__
#define __BASEPERFORMER__HH__

#include <iostream>
#include <vector>


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

    std::cout <<  "\n"
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
    std::cout <<  "\n";
    
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


};

//small class

#endif
