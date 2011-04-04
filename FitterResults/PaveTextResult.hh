
#ifndef PAVETEXTRESULT_H
#define PAVETEXTRESULT_H
#include "core/AbsResult.h"

#include <string>

namespace core {


/**
  * class PaveTextResult
  * 
  */

class PaveTextResult : virtual public AbsResult
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  PaveTextResult ( );

  /**
   * Empty Destructor
   */
  virtual ~PaveTextResult ( );

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * @param  _aobject
   */
  void addResult (void _aobject )
  {
    m_results.push_back(_aobject);
  }


  /**
   */
  void printIt ( )
  {
  }

protected:

  // Static Protected attributes
  //  

  // Protected attributes
  //  

public:


  // Protected attribute accessor methods
  //  

protected:

public:


  // Protected attribute accessor methods
  //  

protected:


private:

  // Static Private attributes
  //  

  // Private attributes
  //  

  std::vector<TObject> m_results;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of m_results
   * @param new_var the new value of m_results
   */
  void setM_results ( std::vector<TObject> new_var )   {
      m_results = new_var;
  }

  /**
   * Get the value of m_results
   * @return the value of m_results
   */
  std::vector<TObject> getM_results ( )   {
    return m_results;
  }
private:


  void initAttributes ( ) ;

};
}; // end of package namespace

#endif // PAVETEXTRESULT_H
