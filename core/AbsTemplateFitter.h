
#ifndef ABSTEMPLATEFITTER_H
#define ABSTEMPLATEFITTER_H

#include <string>

namespace core {

class AbsTemplateFitter
{
public:



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

protected:

public:

protected:


private:

public:

private:

public:

private:



};
}; // end of package namespace

#endif // ABSTEMPLATEFITTER_H
