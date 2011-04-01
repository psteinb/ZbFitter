
#ifndef ABSFITTINGFUNCTION_H
#define ABSFITTINGFUNCTION_H

#include <string>

namespace functions {


/**
  * class AbsFittingFunction
  * 
  */

class AbsFittingFunction
{
public:


		// Public attribute accessor methods
		//  


		// Public attribute accessor methods
		//  



		/**
		 * @param  _values
		 */
		virtual void operator_ (double* _values = 0 )
		{
		}


		/**
		 * @param  _data function to extract the data from a STL container
		 */
		virtual void setData (std::vector<double> _data )
		{
		}


		/**
		 * @param  _parameters function to set the function parameters from the inline stl
		 * container
		 */
		virtual void setParameters (std::vector<double> _parameters )
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

#endif // ABSFITTINGFUNCTION_H
