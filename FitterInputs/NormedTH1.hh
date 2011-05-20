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
      if(metaName.Contains("data"))
        return 0;
      if(metaName.Contains("true") || metaName.Contains("mc") 
         || metaName.Contains("top") || metaName.Contains("ttbar") 
         || metaName.Contains("zjets_") 
         ){
        if(metaName.Contains("sys"))
          return 2;
        if(metaName.Contains("up") || metaName.Contains("+"))
          return 3;
        if(metaName.Contains("down") || metaName.Contains("-"))
          return 4;
        if(metaName.Contains("total") || metaName.Contains("Total"))
          return 5;

        return 1;
      }

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
    void setDataHisto (TH1* _iHisto=0) {
      if(_iHisto){
        //delete this->m_data;
        this->m_data = _iHisto;
      }
      else
        std::cerr << __FILE__ << ":"<< __LINE__ <<"\t inline TH1 pointer nil\n";
    };

    TH1* getDataDeepCopy(){
      std::string name = m_data->GetName();name+="_new";
      TH1* value = dynamic_cast<TH1*>(m_data->Clone(name.c_str()));
      value->SetDirectory(0);
      return value;
    };

    /**
     * @param  _fileNames (comma-separated) file(s) name(s)
     * @param  _histoNames comma-separated list of histo names to load from _fileNames
     */
    void loadTemplates (const std::string& _fileNames = "", const std::string& _histoNames = "", const short& _rebin=1 ) ;
    void addTemplateHisto(TH1* _iHisto=0){
      if(_iHisto)
      {
        if((m_templates.capacity()-m_templates.size())<1)
          m_templates.reserve(m_templates.capacity()+1);
        m_templates.push_back(_iHisto);
      }
      else
        std::cerr << __FILE__ << ":"<< __LINE__ <<"\t inline TH1 pointer nil\n";
    }

    void setTemplateHistos(const std::vector<TH1*>& _templates){
      m_templates = _templates;
    };
    
    void getTemplatesDeepCopy(std::vector<TH1*>&);
    
    /**
     * @param  _data
     */
    virtual void getData (std::vector<FitterData>& _data );

    void clear(){
      delete m_data;
      m_data = 0;

      delete m_totalMC;
      m_totalMC = 0;

      for (int i = 0; i < m_templates.size(); ++i)
      {
        if(!m_templates.at(i)){
          delete m_templates.at(i);
          m_templates.at(i) = 0;
        }
      
      }
      m_templates.clear();


      for (int i = 0; i < m_files.size(); ++i)
      {
        if(!m_files.at(i)){
          m_files.at(i)->Close();
          delete m_files.at(i);
          m_files.at(i) = 0;
        }
      
      }
      m_files.clear();
  
    };


    
  };
}; // end of package namespace

#include "NormedTH1.icc"
#endif // NORMEDTH1_H
