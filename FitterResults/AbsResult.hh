
#ifndef ABSRESULT_H
#define ABSRESULT_H

class TObject;

namespace FitterResults {


class AbsResult
{
public:



  /**
   * add new data to be formatted
   * @param  _aobject
   */
  virtual void addResult (TObject* _object=0 ) = 0;


  /**
   */
  virtual void print ( ) = 0;

protected:


};
}; // end of package namespace

#endif // ABSRESULT_H
