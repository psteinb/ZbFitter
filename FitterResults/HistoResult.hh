#pragma once
#ifndef HISTORESULT_H
#define HISTORESULT_H
#include "AbsResult.hh"
#include "TObject.h"

namespace FitterResults {


/**
  * class HistoResult
  * 
  */

class HistoResult : public AbsResult
{
private:

public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  HistoResult ( ):
    AbsResult()
  {};

  /**
   * Empty Destructor
   */
  virtual ~HistoResult ( ){};

   /**
   * add new data to be formatted
   * @param  _aobject
   */
  virtual void addResult (TObject* _object=0 ) {};


  virtual void print ( ) {};


};
}; // end of package namespace

#endif // HISTORESULT_H
