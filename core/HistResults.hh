
#ifndef HISTRESULTS_H
#define HISTRESULTS_H
#include "core/AbsResult.h"

#include <string>

namespace core {


/**
  * class HistResults
  * 
  */

class HistResults : virtual public AbsResult
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  HistResults ( );

  /**
   * Empty Destructor
   */
  virtual ~HistResults ( );

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

  std::vector<TObject> _results;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of _results
   * @param new_var the new value of _results
   */
  void set_results ( std::vector<TObject> new_var )   {
      _results = new_var;
  }

  /**
   * Get the value of _results
   * @return the value of _results
   */
  std::vector<TObject> get_results ( )   {
    return _results;
  }
private:


  void initAttributes ( ) ;

};
}; // end of package namespace

#endif // HISTRESULTS_H
