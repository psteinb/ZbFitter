#pragma once
#ifndef TH1BUNDLE_H
#define TH1BUNDLE_H
#include "FitterInputs/AbsHisto.hh"

#include <string>
#include <vector>
#include "TH1D.h"
#include "TFile.h"


namespace FitterInputs {

  struct TFileNameCompare : std::binary_function<TFile*,std::string,bool>{
    bool operator()(TFile* _file, std::string _name) const {
      std::string tfile = _file->GetName();
      return tfile.compare(_name);
    }
  };


  class TH1Bundle : public AbsHisto
  {
  private:

    // Private attributes
    //  

    // string that represents the object to be loaded from <m_dataFile>
    std::string m_dataPlotName;
    // file name to open for data plot
    std::string m_dataFile;
    // file name or comma separated list of file names (if the latter, the order of the mcPlotNames must be the same as here)
    std::string m_mcFileNames;
    std::string m_mcPlotNames;
    TH1* m_data;
    std::vector<TH1*> m_templates;
    std::vector<double> m_dataEntries;
    std::vector<std::vector<double> > m_templatesEntries;
    std::vector<TFile*> m_files;

    TFile* openFile(const std::string& _fileNames = "");
    void loadTemplatesFromOneFile (const std::string& _fileNames = "", const std::string& _histoNames = "" );
    void loadTemplatesFromMultipleFiles (const std::string& _fileNames = "", const std::string& _histoNames = "" );
    void pushBinContentsToVector(TH1*, std::vector<double>&);
    void pushBinWeightsToVector(TH1*, std::vector<double>&);

  protected:
                
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



    /**
     * @param  _fileName file to be opened
     * @param  _histoNames single plot 
     * from files
     */
    void loadData (const std::string& _fileName = "", const std::string& _histoNames = "" ) ;


    /**
     * @param  _fileNames (comma-separated) file(s) name(s)
     * @param  _histoNames comma-separated list of histo names to load from _fileNames
     */
    void loadTemplates (const std::string& _fileNames = "", const std::string& _histoNames = "" ) ;
  


    /**
     * @param  _data
     */
    virtual void getData (std::vector<double>& _data );
		

    /**
     * @param  _templates
     */
    virtual void getTemplates (std::vector<std::vector<double> >& _templates );
    virtual void getTemplatesWithWeights (std::vector<std::vector<double> >& _templates, std::vector<std::vector<double> >& _weights );




  };
}; // end of package namespace

#endif // TH1BUNDLE_H
