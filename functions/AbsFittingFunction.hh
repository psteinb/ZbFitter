#ifndef ABSFITTINGFUNCTION_H
#define ABSFITTINGFUNCTION_H
#include <vector>
#include <algorithm>
#include <cassert>

namespace functions {



  /**
   * class AbsFittingFunction
   * 
   */

  class AbsFittingFunction
  {
    
    std::vector<double> m_parameters;
    int m_nParameters;
    std::vector<double> m_data;
    std::vector<std::vector<double> > m_templates;
    std::vector<std::vector<double> > m_weights;

  public:
    AbsFittingFunction():
      m_parameters(),
      m_nParameters(3),
      m_data(),
      m_templates(),
      m_weights()
    {};

    virtual ~AbsFittingFunction(){};


    /**
     * @return double
     * @param  _values
     */
    virtual double operator() (const double* _values = 0 ) = 0;


    /**
     * @param  _data function to extract the data from a STL container
     */
    virtual void setData (const std::vector<double>& _data )
    {
      m_data = _data;
    }

    virtual const std::vector<double>* getData ( ) const  {
      return &(m_data);
    }
    /**
     * @param  _data function to extract the data from a STL container
     */
    virtual void setTemplates (const std::vector<std::vector<double> >& _templates ){
      m_templates = _templates;
    }

    /**
     * Get a pointer to a template vector
     * @return 
     */
    const std::vector<double>* getTemplate (const short& _idx ) const  {
      if(_idx<m_templates.size())
        return &(m_templates.at(_idx));
      else
        return 0;
    }
    
    /**
     * @param  _weights function to set the weights
     */
    virtual void setWeights (const std::vector<std::vector<double> >& _weights ){
      m_weights = _weights;
    };


    /**
     * @return double
     */
    virtual double up() = 0;

    virtual void setParameters(const double* _params){

      //shooting into the blind
      //std::assert( _params[(m_nParameters-1)] > 0);
      //copy parameters to vector
      m_parameters.reserve(m_nParameters);
      std::copy(_params,_params+int(m_nParameters),m_parameters.begin());
    };
  
    virtual int getNumberOfParameters() const {return m_nParameters;};
    
    virtual double getParameterValue(const short& _idx) const {return m_parameters.at(_idx);};
  };
}; // end of package namespace

#endif // ABSFITTINGFUNCTION_H
