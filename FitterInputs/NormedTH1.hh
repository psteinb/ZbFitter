#pragma once
#ifndef NORMEDTH1_H
#define NORMEDTH1_H
#include "FitterInputs/AbsHisto.hh"
#include "FitterInputs/FitterData.hh"

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <algorithm>

#include "TH1D.h"
#include "TFile.h"
#include "TString.h"
#include "TObjString.h"
#include "TObjArray.h"



namespace FitterInputs {

  struct TFileNameCompare : std::binary_function<TFile*,std::string,bool>{
    bool operator()(TFile* _file, std::string _name) const {
      std::string tfile = _file->GetName();
      return tfile.compare(_name);
    }
  };

  struct DecideDataTypeFromString : std::unary_function<std::string,int>{
    int operator()(const std::string& _name) const {
      TString metaName = _name.c_str();
      metaName.ToLower();
      int value = 0;
      if(metaName.Contains("data"))
        value = 0;
      else
      {
        if(metaName.Contains("sys"))
          value = 2;
        if(metaName.Contains("up") || metaName.Contains("+"))
          value = 3;
        if(metaName.Contains("down") || metaName.Contains("-"))
          value = 4;
        if(metaName.Contains("total") || metaName.Contains("Total"))
          value = 5;

        value = 1;
      }
      
      return value;
    };
  };
  
  template<typename NormFunc>
  class NormedTH1 : public AbsHisto
  {
  private:

    // Private attributes
    // the values that need to be handed to the outside at some point
    std::vector<FitterData> m_values;

    // file name to open for data plot
    std::string m_dataFile;
    // string that represents the object to be loaded from <m_dataFile>
    std::string m_dataPlotName;
    TH1* m_data;
    TH1* m_totalMC;

    // file name or comma separated list of file names (if the latter, the order of the mcPlotNames must be the same as here)
    std::string m_mcFileNames;
    std::string m_mcPlotNames;
    std::vector<TH1*> m_templates;
    std::vector<TFile*> m_files;


    //open file at _fileName and add the TFile object to m_files
    TFile* openFile(const std::string& _fileNames = "");

    //open 1 file of name _fileNames and retrieve all TH1* objects according to _histoNames
    void loadTemplatesFromOneFile (const std::string& _fileNames = "", const std::string& _histoNames = "",const short& _rebin=1 );

    //open files of name _fileNames and retrieve all TH1* objects according to _histoNames using loadTemplatesFromOneFile
    void loadTemplatesFromMultipleFiles (const std::string& _fileNames = "", const std::string& _histoNames = "",const short& _rebin=1 );

    
    void pushBinContentsToVector(TH1*, std::vector<double>&);
    void pushBinWeightsToVector(TH1*, std::vector<double>&);

    void createFitterDataFromTH1(TH1*, FitterData&);
    void setupFitterData();

    void normalizeTemplateTH1s(std::vector<TH1*>&);

  protected:
                
  public:

    // Constructors/Destructors
    //  


    /**
     * Empty Constructor
     */
    NormedTH1 (  );

    /**
     * Empty Destructor
     */
    virtual ~NormedTH1 ( );

    
    void init();
    void initData();

    /**
     * open _fileName and retrieve histoNames
     * @param  _fileName file to be opened
     * @param  _histoNames single plot 
     * from files
     */
    void loadData (const std::string& _fileName = "", const std::string& _histoNames = "", const short& _rebin=1 ) ;
    
    /**
       set m_data to _iHisto
    */
    void setDataHisto (TH1* _iHisto=0);
    
    /**
       get a copy of the data object performing a call to new
       [method uses TH1::Clone, new object may not transfer its ownership]
     */
    TH1* getDataDeepCopy();

    /**
       master method to load all Templates from files, 
       if _fileNames is has multiple commas in it, loadTemplatesFromMultipleFiles is called
       if _fileNames has no commas in it, loadTemplatesFromOneFile is called
     * @param  _fileNames (comma-separated) file(s) name(s)
     * @param  _histoNames comma-separated list of histo names to load from _fileNames
     */
    void loadTemplates (const std::string& _fileNames = "", const std::string& _histoNames = "", const short& _rebin=1 ) ;

    /**
       _iHisto is added to m_templates
    */
    void addTemplateHisto(TH1* _iHisto=0);

    /**
       external set method
    */
    void setTemplateHistos(const std::vector<TH1*>& _templates){
      m_templates = _templates;
    };
    
    /**
       retrieve a copy of the templates
       [method uses TH1::Clone, new object may not transfer its ownership]
    */
    void getTemplatesDeepCopy(std::vector<TH1*>&);
    
    /**
     * @param  _data
     */
    virtual void getData (std::vector<FitterData>& _data );

    void clear();


    
  };
}; // end of package namespace

#include "NormedTH1.icc"
#endif // NORMEDTH1_H
