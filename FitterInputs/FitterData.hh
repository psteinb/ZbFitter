#pragma once
#ifndef FITTERDATA_H
#define FITTERDATA_H
#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

namespace FitterInputs {

  enum dataType {
    eData = 0,
    eTempl = 1,
    eTemplSys = 2,
    eTemplUp = 3,
    eTemplDown = 4
  };

class FitterData
{
  
  dataType m_type;
  std::string m_name;
  std::vector<double> m_values;
  std::vector<double> m_weights;

public:
  FitterData(const std::string& _name="defaultValues",const short& _type=0) : 
    m_name(_name), 
    m_type((dataType)_type), 
    m_values(), 
    m_weights(){};

  virtual ~FitterData(){};

  void setContent(const std::vector<double>& _values){
    if(_values.size()){
      m_values.assign(_values.begin(), _values.end());
      // m_values.reserve(_values.size());
      // std::copy(,m_values.begin());
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
  };

  void clear(){m_values.clear();m_weights.clear();};

  const std::string& getName() const {return m_name;};
  void setName(const std::string&  _name="defaultValue"){ m_name = _name;};
};

};
#endif // FITTERDATA_H
