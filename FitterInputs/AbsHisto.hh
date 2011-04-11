
#ifndef ABSHISTO_H
#define ABSHISTO_H

#include <vector>

#include "FitterInputs/FitterData.hh"

namespace FitterInputs {

class AbsHisto
{
public:
  AbsHisto(){};
  virtual ~AbsHisto(){};
		/**
		 * @param  _data
		 */
  virtual void getData (std::vector<FitterData>& _data ) = 0;


};
}; // end of package namespace

#endif // ABSHISTO_H
