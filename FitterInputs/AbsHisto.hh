
#ifndef ABSHISTO_H
#define ABSHISTO_H

#include <string>

namespace FitterInputs {

class AbsHisto
{
public:
  AbsHisto(){};
  virtual ~AbsHisto(){};
		/**
		 * @param  _data
		 */
  virtual void getData (std::vector<double>& _data ) = 0;
		

		/**
		 * @param  _templates
		 */
  virtual void getTemplates (std::vector<std::vector<double> >& _templates ) = 0;
		


};
}; // end of package namespace

#endif // ABSHISTO_H
