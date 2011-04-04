#define TH1BUNDLE_CC
#include "TH1Bundle.hh"
#include <algorithm>
#include "TString.h"
#include "TObjString.h"
#include "TObjArray.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

// Constructors/Destructors
//  

FitterInputs::TH1Bundle::TH1Bundle ( ):
  AbsHisto(),
  m_dataPlotName(""),
  m_dataFile    (""),
  m_mcFileNames (""),
  m_mcPlotNames (""),
  m_data(0),
  m_templates(),
  m_dataEntries(),
  m_templatesEntries(),
  m_files()
{
  m_files.reserve(4);
  m_templates.reserve(3);
}

FitterInputs::TH1Bundle::~TH1Bundle ( ) {
  delete m_data;
  m_data = 0;

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

}

TFile* FitterInputs::TH1Bundle::openFile(const std::string& _fileName){

  std::vector<TFile*>::const_iterator fItr = std::find_if(m_files.begin(), m_files.end(),
                                                          std::bind2nd(TFileNameCompare(),_fileName));
  if(fItr!=m_files.end())
    return (*fItr);
  else{
    TFile* metafile = new TFile(_fileName.c_str());
    if(!metafile->IsZombie()){
      m_files.push_back(metafile);
      return m_files.back();}
    else{
      
      return 0;
    }
  }
    
  
}

void FitterInputs::TH1Bundle::loadData (const std::string& _fileName, const std::string& _histoNames ){
  
  if(_fileName.empty() || _histoNames.empty()){
    std::ostringstream error;
    error<< __FILE__ << ":"<< __LINE__ << "\t File name or histo name not filled " << _fileName.c_str() << "("<< _histoNames.c_str() <<")\n";
    throw std::invalid_argument(error.str());
  }

  if(openFile(_fileName)){
    m_data = dynamic_cast<TH1*>(openFile(_fileName)->Get(_histoNames.c_str()));
    m_data->Sumw2();
  }
  else
    throw std::runtime_error("file not found");

  if(!m_data){
    std::ostringstream error;
    error<< __FILE__ << ":"<< __LINE__ << "\t histo named "<< _histoNames.c_str() <<" not found in " << _fileName.c_str() <<")\n";
    throw std::runtime_error(error.str());
  }
}

void FitterInputs::TH1Bundle::loadTemplatesFromOneFile (const std::string& _fileNames, const std::string& _histoNames ){

  TFile* fileObject = openFile(_fileNames);
  if(!fileObject || _fileNames.empty())
  {
    std::ostringstream error;
    error<< __FILE__ << ":"<< __LINE__ << "\t File name not filled or not found " << _fileNames.c_str()  <<")\n";
    throw std::invalid_argument(error.str());
      //return;
  }

  if(_histoNames.empty()){
    std::ostringstream error;
    error << __FILE__ << ":"<< __LINE__ << 
      "\t histo names "<< "("<< _histoNames.c_str() <<") empty for " << _fileNames.c_str() <<"\n";
    throw std::invalid_argument(error.str());
  }

  TString HistNames(_histoNames.c_str());
  TObjArray* Histo = HistNames.Tokenize(",");
  TString aHistName;
  TH1* metaObject = 0;
  for (int i = 0; i < Histo->GetEntries(); ++i)
  {
    aHistName = dynamic_cast<TObjString*>(Histo->At(i))->GetString();
    metaObject = dynamic_cast<TH1*>(fileObject->Get(aHistName.Data()));
    metaObject->Sumw2();

    if(metaObject){
      m_templates.push_back(metaObject);
      std::cout << "TH1Bundle::loadTemplatesFromOneFile\t" << "loaded " << m_templates.back()->GetName() << " from " << _fileNames << std::endl;
    }
    else
      std::cerr << __FILE__ << ":"<< __LINE__ << "\t couldn't load " << aHistName.Data() << " from " << _fileNames << std::endl;
      
  }
  
  delete Histo;Histo=0;
}

void FitterInputs::TH1Bundle::loadTemplatesFromMultipleFiles (const std::string& _fileNames, const std::string& _histoNames){
  
  if(_fileNames.empty())
  {
    std::cerr<< __FILE__ << ":"<< __LINE__ << "\t File name not filled or not found " << _fileNames.c_str()  <<")\n";
    return;
  }

  if(_histoNames.empty()){
    std::cerr<< __FILE__ << ":"<< __LINE__ << "\t histo names "<< "("<< _histoNames.c_str() <<") empty for " << _fileNames.c_str() <<"\n";
    return;
  }

  TString FileNames(_fileNames.c_str());
  TObjArray* Files = FileNames.Tokenize(",");
  TString HistNames(_histoNames.c_str());
  TObjArray* Histo = HistNames.Tokenize(",");
  TString aFileName;
  TString aHistName;
  for (int i = 0; i < Files->GetEntries(); ++i)
  {
    aFileName = dynamic_cast<TObjString*>(Files->At(i))->GetString();
    aHistName = dynamic_cast<TObjString*>(Histo->At(i))->GetString();
    loadTemplatesFromOneFile(aFileName.Data(),aHistName.Data());
  }

  delete Files;Files=0;
  delete Histo;Histo=0;
}

void FitterInputs::TH1Bundle::loadTemplates (const std::string& _fileNames , const std::string& _histoNames  ){
  
  if(_fileNames.empty() || _histoNames.empty()){
    std::ostringstream error;
    error << __FILE__ << ":"<< __LINE__ << "\t File name or histo name not filled " << _fileNames.c_str() << "("<< _histoNames.c_str() <<")\n";
    throw std::invalid_argument(error.str());
  }  

  TString FileNames(_fileNames.c_str());

  if(FileNames.CountChar(',')){
    loadTemplatesFromMultipleFiles(_fileNames,_histoNames);
  }
  else
  {
    loadTemplatesFromOneFile(_fileNames,_histoNames);
  }
}

void FitterInputs::TH1Bundle::pushBinContentsToVector(TH1* _hist, std::vector<double>& _target){

  _target.clear();
  if(!_hist){
    std::cerr<< __FILE__ << ":"<< __LINE__ << "\t no histo available for bin content transfer"<< _hist <<"\n";
    return;
  }

  _target.reserve(_hist->GetNbinsX());
  
  for (int i = 0; i < _hist->GetNbinsX(); ++i)
  {
    _target.push_back(_hist->GetBinContent(i+1));
  }
  
}

void FitterInputs::TH1Bundle::pushBinWeightsToVector(TH1* _hist, std::vector<double>& _target){

  _target.clear();
  if(!_hist){
    std::cerr<< __FILE__ << ":"<< __LINE__ << "\t no histo available for bin content transfer"<< _hist <<"\n";
    return;
  }

  _target.reserve(_hist->GetNbinsX());
  TArrayD* weights = _hist->GetSumw2();

  if(weights->GetSize()){
    for (int i = 0; i < _hist->GetNbinsX() ; ++i)
    {
      //      if((i+1)<weights->GetSize())
      _target.push_back(weights->At(i+1));
    }
  }
  else
    std::cerr << __FILE__ << ":"<< __LINE__ << " " << _hist->GetName() << "exhibits 0 size weight array\n";
}


void FitterInputs::TH1Bundle::getData (std::vector<double>& _data ){
  _data.clear();
  if(!m_data){
    std::cerr<< __FILE__ << ":"<< __LINE__ << "\t no data histo available\n";
    return;
  }

  _data.reserve(m_data->GetNbinsX());
  
  pushBinContentsToVector(dynamic_cast<TH1*>(m_data),_data);

}

void FitterInputs::TH1Bundle::getTemplates (std::vector<std::vector<double> >& _templates ){
  _templates.clear();
  

  if(m_templates.empty()){
    std::cerr<< __FILE__ << ":"<< __LINE__ << "\t no template histos available\n";
    return;
  }

  _templates.resize(m_templates.size());
    
  for (int i = 0; i < m_templates.size(); ++i)
  {
    pushBinContentsToVector(dynamic_cast<TH1*>(this->m_templates.at(i)),_templates.at(i));
  }
  

}

void FitterInputs::TH1Bundle::getTemplatesWithWeights (std::vector<std::vector<double> >& _templates , std::vector<std::vector<double> >& _weights){

  _templates.clear();
  _weights.clear();

  if(m_templates.empty()){
    std::cerr<< __FILE__ << ":"<< __LINE__ << "\t no template histos available\n";
    return;
  }

  _templates.resize(m_templates.size());
  _weights.resize(m_templates.size());
    
  for (int i = 0; i < m_templates.size(); ++i)
  {
    pushBinContentsToVector(dynamic_cast<TH1*>(this->m_templates.at(i)),_templates.at(i));
    pushBinWeightsToVector(dynamic_cast<TH1*>(this->m_templates.at(i)),_weights.at(i));
  }
  

}
