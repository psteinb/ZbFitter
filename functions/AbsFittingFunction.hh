#ifndef ABSFITTINGFUNCTION_H
#define ABSFITTINGFUNCTION_H
#include <vector>
#include <algorithm>
#include <cassert>
#include <iterator>
#include <iostream>
#include "FitterInputs/AbsHisto.hh"


namespace functions {


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
   * class AbsFittingFunction
   * 
   */

  class AbsFittingFunction
  {
    
    std::vector<double> m_parameters;
    int m_nParameters;
    std::vector<FitterInputs::FitterData> m_input;

    virtual void loadSystematics ();

  protected:
    
    FitterInputs::FitterData m_data;
    std::vector<FitterInputs::FitterData> m_templates;
    std::vector<std::vector<FitterInputs::FitterData> > m_templatesSys;


  public:
    AbsFittingFunction():
      m_parameters(),
      m_nParameters(3),
      m_input(),
      m_data(),
      m_templates(),
      m_templatesSys()
    {};

    virtual ~AbsFittingFunction(){};

    /////////////////////////////////////////
    /// the following are methods to overload, but they mustn't be
    /////////////////////////////////////////

    virtual void setParameters(const double* _params){

      //shooting into the blind
      //std::assert( _params[(m_nParameters-1)] > 0);
      //copy parameters to vector
      m_parameters.resize(m_nParameters,0);
      std::copy(_params,_params+int(m_nParameters),m_parameters.begin());

    };
  
    virtual int getNumberOfParameters() const {return m_nParameters;};
    
    virtual double getParameterValue(const short& _idx) const {return m_parameters.at(_idx);};

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

    
    
  };
}; // end of package namespace

#endif // ABSFITTINGFUNCTION_H
