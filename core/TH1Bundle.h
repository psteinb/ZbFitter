
#ifndef TH1BUNDLE_H
#define TH1BUNDLE_H
#include "core/AbsHisto.h"

#include <string>

namespace core {


/**
  * class TH1Bundle
  * 
  */

class TH1Bundle : virtual public AbsHisto
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  TH1Bundle ( );

  /**
   * Empty Destructor
   */
  virtual ~TH1Bundle ( );

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * @param  _fileName file to be opened
   * @param  _histoNames single plot or comma-seperated list of plot names to be read
   * from files
   */
  void loadData (string _fileName = "", std::string _histoNames = "" )
  {
  }


  /**
   * @param  _fileNames (comma-separated) file(s) name(s)
   * @param  _histoNames comma-separated list of histo names to load from _fileNames
   */
  void loadTemplates (std::string _fileNames = "", std::string _histoNames = "" )
  {
  }


  /**
   * @return TH1
   */
  TH1 getData ( )
  {
    {return m_data;}
  }


  /**
   * @param  _templates
   */
  void getTemplates (std::vector<TH1> _templates )
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

  // string that represents the object to be loaded from <m_dataFile>
  string m_dataPlotName;
  // file name to open for data plot
  string m_dataFile;
  // file name or comma separated list of file names (if the latter, the order of the mcPlotNames must be the same as here)
  string m_mcFileNames;
  string m_mcPlotNames;
  TH1 m_data;
  std::vector<TH1> m_templates;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of m_dataPlotName
   * string that represents the object to be loaded from <m_dataFile>
   * @param new_var the new value of m_dataPlotName
   */
  void setM_dataPlotName ( string new_var )   {
      m_dataPlotName = new_var;
  }

  /**
   * Get the value of m_dataPlotName
   * string that represents the object to be loaded from <m_dataFile>
   * @return the value of m_dataPlotName
   */
  string getM_dataPlotName ( )   {
    return m_dataPlotName;
  }

  /**
   * Set the value of m_dataFile
   * file name to open for data plot
   * @param new_var the new value of m_dataFile
   */
  void setM_dataFile ( string new_var )   {
      m_dataFile = new_var;
  }

  /**
   * Get the value of m_dataFile
   * file name to open for data plot
   * @return the value of m_dataFile
   */
  string getM_dataFile ( )   {
    return m_dataFile;
  }

  /**
   * Set the value of m_mcFileNames
   * file name or comma separated list of file names (if the latter, the order of the
   * mcPlotNames must be the same as here)
   * @param new_var the new value of m_mcFileNames
   */
  void setM_mcFileNames ( string new_var )   {
      m_mcFileNames = new_var;
  }

  /**
   * Get the value of m_mcFileNames
   * file name or comma separated list of file names (if the latter, the order of the
   * mcPlotNames must be the same as here)
   * @return the value of m_mcFileNames
   */
  string getM_mcFileNames ( )   {
    return m_mcFileNames;
  }

  /**
   * Set the value of m_mcPlotNames
   * @param new_var the new value of m_mcPlotNames
   */
  void setM_mcPlotNames ( string new_var )   {
      m_mcPlotNames = new_var;
  }

  /**
   * Get the value of m_mcPlotNames
   * @return the value of m_mcPlotNames
   */
  string getM_mcPlotNames ( )   {
    return m_mcPlotNames;
  }

  /**
   * Set the value of m_data
   * @param new_var the new value of m_data
   */
  void setM_data ( TH1 new_var )   {
      m_data = new_var;
  }

  /**
   * Get the value of m_data
   * @return the value of m_data
   */
  TH1 getM_data ( )   {
    return m_data;
  }

  /**
   * Set the value of m_templates
   * @param new_var the new value of m_templates
   */
  void setM_templates ( std::vector<TH1> new_var )   {
      m_templates = new_var;
  }

  /**
   * Get the value of m_templates
   * @return the value of m_templates
   */
  std::vector<TH1> getM_templates ( )   {
    return m_templates;
  }
private:


  void initAttributes ( ) ;

};
}; // end of package namespace

#endif // TH1BUNDLE_H
