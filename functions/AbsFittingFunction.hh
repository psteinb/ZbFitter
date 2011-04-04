#ifndef ABSFITTINGFUNCTION_H
#define ABSFITTINGFUNCTION_H
#include <vector>

namespace functions {


/**
  * class AbsFittingFunction
  * 
  */

class AbsFittingFunction
{

  std::vector<double> m_data;
  std::vector<std::vector<double> > m_templates;
  std::vector<std::vector<double> > m_weights;

 public:
  AbsFittingFunction(){};
  virtual ~AbsFittingFunction(){};


  /**
   * @return double
   * @param  _values
   */
  virtual double operator() (double* _values = 0 ) = 0;


  /**
   * @param  _data function to extract the data from a STL container
   */
  virtual void setData (const std::vector<double>& _data ) = 0;

  /**
   * @param  _data function to extract the data from a STL container
   */
  virtual void setTemplates (const std::vector<std::vector<double> >& _templates ) = 0;


  /**
   * @param  _weights function to set the weights
   */
  virtual void setWeights (const std::vector<std::vector<double> >& _weights ) =0;


  /**
   * @return double
   */
  virtual double up ( )=0;



};
}; // end of package namespace

#endif // ABSFITTINGFUNCTION_H
