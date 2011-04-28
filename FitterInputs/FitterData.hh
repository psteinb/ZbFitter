#pragma once
#ifndef FITTERDATA_H
#define FITTERDATA_H
#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <numeric>
#include "TH1D.h"


namespace FitterInputs {

  

  enum dataType {
    eData = 0,
    eTempl = 1,
    eTemplSys = 2,
    eTemplUp = 3,
    eTemplDown = 4,
    eTotalMC = 5
  };

class FitterData
{
  
  dataType m_type;
  std::string m_name;
  std::vector<double> m_values;
  double m_sum;
  double m_sumError;
  std::vector<double> m_weights;
  TH1* m_histo;

  void calcSumAndUncertainty(){
    m_sum = std::accumulate(m_values.begin(), m_values.end(),0,std::plus<double>());
    m_sumError = std::sqrt(m_sum);
  };


public:
  FitterData(const std::string& _name="defaultValues",const short& _type=0) : 
    m_name(_name), 
    m_type((dataType)_type), 
    m_values(), 
    m_sum(0.),
    m_sumError(0.),
    m_weights(),
    m_histo(0)
  {};

  virtual ~FitterData(){
    // delete m_histo;
    // m_histo = 0;
  };

  void setContent(const std::vector<double>& _values){
    if(_values.size()){
      m_values.assign(_values.begin(), _values.end());
      // m_values.reserve(_values.size());
      // std::copy(,m_values.begin());
      try{
        calcSumAndUncertainty();}
      catch(std::exception& thisExc){
        std::cerr << __FILE__ << "("<< __LINE__ <<")\t Could not calculate total sum and uncertainty\t> "<< thisExc.what() <<" <\n";
      }

    }
    else
      std::cerr << __FILE__ << "("<< __LINE__ <<")\t NOTHING TO COPY\n";
  };
  
  void setWeights(const std::vector<double>& _weights){
    if(_weights.size()){
      m_weights.assign(_weights.begin(), _weights.end());
      // m_weights.reserve(_weights.size());
      // std::copy(,m_weights.begin());
    }
    else
      std::cerr << __FILE__ << "("<< __LINE__ <<")\t NOTHING TO COPY\n";
  };

  void setContentAndWeights(const std::vector<double>& _values, const std::vector<double>& _weights){
    this->setContent(_values);
    this->setWeights(_weights);
  };  

  std::vector<double>* getContent(){ return &(this->m_values); };
  std::vector<double>* getWeights(){ return &(this->m_weights); };

  void copyContentAndWeightsTo( std::vector<double>& _values,  std::vector<double>& _weights){
    _values.reserve(m_values.size());
    _weights.reserve(m_weights.size());
    std::copy(m_values.begin(), m_values.end(),_values.begin());
    std::copy(m_weights.begin(), m_weights.end(),_weights.begin());
  };

  short getType() const {return (short)m_type;};
  short setType(const short& _type=0){m_type=(dataType)_type;};
  bool isA(const short& _type=0) const { return (m_type==(dataType)_type);}
  bool isA(const dataType& _type=eData) const { return (m_type==_type);}

  void print(){
    std::ostream_iterator<double> comma(std::cout,", ");
    std::cout << "FitterData("<< m_type <<")\t> ";
    std::copy(m_values.begin(), m_values.end(),comma);
    std::cout << "\n\t\t> ";
    std::copy(m_weights.begin(), m_weights.end(),comma);
    std::cout << "\n";
    if(m_histo)
      m_histo->Print("all");
  };

  void clear(){m_values.clear();m_weights.clear();};

  const std::string& getName() const {return m_name;};
  void setName(const std::string&  _name="defaultValue"){ m_name = _name;};

  double getSum() const {return m_sum;};
  double getSumError() const {return m_sumError;};
  double getSumAndError(double& _sum,double& _err) const {_sum=m_sum;_err=m_sumError;};

  const TH1* getHisto() const {return m_histo;};
  void setHisto(TH1* _histo) {
    std::string histo = m_name;
    histo += "_histo";
    m_histo = dynamic_cast<TH1*>(_histo->Clone(histo.c_str()));
    m_histo->SetDirectory(0);
  };
};

struct lessForDataType : public std::binary_function<FitterData,FitterData,bool>
  {
    bool operator()(const FitterData& _first, const FitterData& _second){
      return _first.getType() < _second.getType();
    }

    bool operator()(FitterData* _first, FitterData* _second){
      return _first->getType() < _second->getType();
    }
  };

};
#endif // FITTERDATA_H
