
#ifndef FITRUNNER_H
#define FITRUNNER_H

#include <string>

namespace core {


/**
  * class FitRunner
  * 
  */

/******************************* Abstract Class ****************************
FitRunner does not have any pure virtual methods, but its author
  defined it as an abstract class, so you should not use it directly.
  Inherit from it instead and create only objects from the derived classes
*****************************************************************************/

class FitRunner
{
public:


		// Public attribute accessor methods
		//  


		// Public attribute accessor methods
		//  



		/**
		 * @param  data
		 * @param  mc
		 */
		virtual void AbsFitter (core::AbsHisto data = 0, std::map<AbsHisto> mc )
		{
		}


		/**
		 * @param  constraints
		 */
		virtual void setConstraints (std::map<AbsConstraints> constraints )
		{
		}


		/**
		 * @param  _fnc
		 */
		virtual void setFitter (AbsFittingFunction _fnc = 0 )
		{
		}


		/**
		 */
		virtual void fit ( )
		{
		}


		/**
		 */
		virtual void getResult ( )
		{
		}

protected:

public:


		// Protected attribute accessor methods
		//  

protected:

public:


		// Protected attribute accessor methods
		//  

protected:


private:

public:


		// Private attribute accessor methods
		//  

private:

public:


		// Private attribute accessor methods
		//  

private:



};
}; // end of package namespace

#endif // FITRUNNER_H
