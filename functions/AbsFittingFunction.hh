#ifndef ABSFITTINGFUNCTION_H
#define ABSFITTINGFUNCTION_H
#include <vector>
#include <algorithm>
#include <cassert>
#include <iterator>
#include <iostream>
#include <utility>
#include "FitterInputs/AbsHisto.hh"


namespace functions {

  /////////////////////////////////////////
  ///  HELER FUNCTORS 
  /////////////////////////////////////////

  struct compDataType : std::binary_function<FitterInputs::FitterData,FitterInputs::FitterData,bool>
  {
    bool operator()(const FitterInputs::FitterData& _left, const FitterInputs::FitterData& _right) const {
      return _left.getType() < _right.getType();
    }
  };

  struct isDataType : std::binary_function<FitterInputs::FitterData,int,bool>
  {
    bool operator()(const FitterInputs::FitterData& _lhs, const int& _type) const {
      return _lhs.isA(_type);
    }
  };
  
  struct isAdjointSystematic : std::binary_function<FitterInputs::FitterData,std::string,bool>
  {
    bool operator()(const FitterInputs::FitterData& _lhs, const std::string& _toCompto) const {

      
      if(_lhs.getName().find(_toCompto)!=std::string::npos && _lhs.getType()>1)
        return true;
      else
        return false;
    }
  };  

  /**
   * CLASS AbsFittingFunction
   * 
   */

  class AbsFittingFunction
  {
    
    std::vector<double> m_parameters;
    std::vector<double> m_parametersUp;
    std::vector<double> m_parametersDown;
    int m_nParameters;
    int m_nFixedParameters;
    std::vector<FitterInputs::FitterData> m_input;

    virtual void loadSystematics ();

  protected:
    
    FitterInputs::FitterData m_data;
    std::vector<FitterInputs::FitterData> m_templates;
    std::vector<std::vector<FitterInputs::FitterData> > m_templatesSys;
    

  public:
    AbsFittingFunction():
      m_parameters(),
      m_parametersUp(),
      m_parametersDown(),
      m_nParameters(3),
      m_nFixedParameters(0),
      m_input(),
      m_data(),
      m_templates(),
      m_templatesSys()
    {};
    
     AbsFittingFunction( const AbsFittingFunction& _rhs):
      m_parameters(_rhs.m_parameters),
      m_parametersUp(_rhs.m_parametersUp),
      m_parametersDown(_rhs.m_parametersDown),
      m_nParameters(_rhs.m_nParameters),
      m_nFixedParameters(_rhs.m_nFixedParameters),
      m_input(_rhs.m_input),
      m_data(_rhs.m_data),
      m_templates(_rhs.m_templates),
      m_templatesSys(_rhs.m_templatesSys)
    {};

    virtual ~AbsFittingFunction(){};

    /////////////////////////////////////////
    /// the following are methods to overload, but they mustn't be
    /////////////////////////////////////////

    virtual void setParameters(const double* _params){

      //shooting into the blind
      //std::assert( _params[(m_nParameters-1)] > 0);
      //copy parameters to vector
      m_parameters.clear();
      m_parameters.resize(m_nParameters,0);
      // m_parametersUp.resize(m_nParameters,0);
      // m_parametersDown.resize(m_nParameters,0);
      std::copy(_params,_params+int(m_nParameters),m_parameters.begin());

    };

    virtual void setParametersAndErrors(const double* _params, const double* _up, const double* _down){

      //shooting into the blind
      //std::assert( _params[(m_nParameters-1)] > 0);
      //copy parameters to vector
      m_parameters.resize(m_nParameters,0);
      std::copy(_params,_params+int(m_nParameters),m_parameters.begin());

      m_parametersUp.resize(m_nParameters,0);
      std::copy(_up,_up+int(m_nParameters),m_parametersUp.begin());

      m_parametersDown.resize(m_nParameters,0);
      std::copy(_down,_down+int(m_nParameters),m_parametersDown.begin());

    };
  
    virtual int getNumberOfParameters() const {return m_nParameters;};
    virtual int getNumberOfFixedParameters() const {return m_nFixedParameters;};
    virtual int getNFixedParameters() const {};
    virtual void setNumberOfFixedParameters(const int& _new)  { m_nFixedParameters = _new;};
    
    virtual double getParameterValue(const short& _idx) const {return m_parameters.at(_idx);};
    virtual void setParameterValue(const short& _idx, const double& _value)  {
      if(_idx<m_parameters.size())
        m_parameters[_idx] = _value;
    };

    virtual void getParameterValueWithError(const short& _idx, double& _value, double& _valueUp, double& _valueDown) const {
      _value = m_parameters.at(_idx);
      _valueUp = m_parametersUp.at(_idx);
      _valueDown = m_parametersDown.at(_idx);
    };

    virtual std::vector<double>* const getParameters(){return (&m_parameters);};

    virtual void print(){
      std::ostream_iterator<double> dblOutIt (std::cout,", ");

      std::cout << "Parameters\n";
      std::copy(m_parameters.begin(), m_parameters.end(),dblOutIt);
      std::cout << "\n";
      
    };
    
    
    /**
     * method to extract all necessary infos from _input
     * @param  _input 
     */
    virtual void setupFromInput (FitterInputs::AbsHisto* _input=0 );

    const FitterInputs::FitterData* getTemplate(const int& _idx) const { return &(m_templates.at(_idx));};
    const FitterInputs::FitterData* getData() const { return &(m_data);};
    /////////////////////////////////////////////////////////////////////////////////////////
    /// to be overloaded by decendent
    ///

    /**
     * @return double
     * @param  _values
     */
    virtual double operator() (const double* _values = 0 ) = 0;

    /**
     * @return double
     */
    virtual double up() = 0;

    void printTemplates(){

      for (int i = 0; i < m_templates.size(); ++i)
      {
        m_templates.at(i).getHisto()->Print("all");
      }
    }
    
  };
}; // end of package namespace

#endif // ABSFITTINGFUNCTION_H
