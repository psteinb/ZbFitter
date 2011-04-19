#define NORMEDTH1_CC
#include "FitterInputs/NormedTH1.hh"
#include <algorithm>

#include "TObjString.h"
#include "TObjArray.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

// Constructors/Destructors
//  

FitterInputs::NormedTH1::NormedTH1 ( ):
  AbsHisto(),
  m_values(),
  m_dataFile    (""),
  m_dataPlotName(""),
  m_data(0),
  m_totalMC(0),
  m_mcFileNames (""),
  m_mcPlotNames (""),
  m_templates(),
  m_files()
{
  m_files.reserve(4);
  m_templates.reserve(3);
}

FitterInputs::NormedTH1::~NormedTH1 ( ) {
  this->clear();
}

TFile* FitterInputs::NormedTH1::openFile(const std::string& _fileName){

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

void FitterInputs::NormedTH1::loadData (const std::string& _fileName, const std::string& _histoNames, const short& _rebin ){
  
  if(_fileName.empty() || _histoNames.empty()){
    std::ostringstream error;
    error<< __FILE__ << ":"<< __LINE__ << "\t File name or histo name not filled " << _fileName.c_str() << "("<< _histoNames.c_str() <<")\n";
    throw std::invalid_argument(error.str());
  }

  if(openFile(_fileName)){
    m_data = dynamic_cast<TH1*>(openFile(_fileName)->Get(_histoNames.c_str()));
    m_data->Sumw2();
    if(_rebin!=1){
      m_data->Rebin(_rebin);
    }
  }
  else
    throw std::runtime_error("file not found");

  if(!m_data){
    std::ostringstream error;
    error<< __FILE__ << ":"<< __LINE__ << "\t histo named "<< _histoNames.c_str() <<" not found in " << _fileName.c_str() <<")\n";
    throw std::runtime_error(error.str());
  }
  
  
}

void FitterInputs::NormedTH1::loadTemplatesFromOneFile (const std::string& _fileNames, const std::string& _histoNames , const short& _rebin){


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
  TObjArray* Histo = HistNames.Tokenize(",");m_templates.reserve(Histo->GetSize());
  TString aHistName;
  TH1* metaObject = 0;
  for (int i = 0; i < Histo->GetEntries(); ++i)
  {
    aHistName = dynamic_cast<TObjString*>(Histo->At(i))->GetString();
    metaObject = dynamic_cast<TH1*>(fileObject->Get(aHistName.Data()));
    metaObject->Sumw2();
    if(_rebin!=1)
      metaObject->Rebin(_rebin);

    if(metaObject){
      m_templates.push_back(metaObject);
      std::cout << "NormedTH1::loadTemplatesFromOneFile\t" << "loaded " << m_templates.back()->GetName() << " from " << _fileNames << std::endl;
    }
    else
      std::cerr << __FILE__ << ":"<< __LINE__ << "\t couldn't load " << aHistName.Data() << " from " << _fileNames << std::endl;
      
  }

  

  delete Histo;Histo=0;
}

void FitterInputs::NormedTH1::loadTemplatesFromMultipleFiles (const std::string& _fileNames, const std::string& _histoNames, const short& _rebin){
  
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
    loadTemplatesFromOneFile(aFileName.Data(),aHistName.Data(),_rebin);
  }

  delete Files;Files=0;
  delete Histo;Histo=0;
}

void FitterInputs::NormedTH1::loadTemplates (const std::string& _fileNames , const std::string& _histoNames , const short& _rebin ){
  
  if(_fileNames.empty() || _histoNames.empty()){
    std::ostringstream error;
    error << __FILE__ << ":"<< __LINE__ << "\t File name or histo name not filled " << _fileNames.c_str() << "("<< _histoNames.c_str() <<")\n";
    throw std::invalid_argument(error.str());
  }  

  TString FileNames(_fileNames.c_str());

  if(FileNames.CountChar(',')){
    loadTemplatesFromMultipleFiles(_fileNames,_histoNames,_rebin);
  }
  else
  {
    loadTemplatesFromOneFile(_fileNames,_histoNames,_rebin);
  }

    
}

void FitterInputs::NormedTH1::pushBinContentsToVector(TH1* _hist, std::vector<double>& _target){

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

void FitterInputs::NormedTH1::pushBinWeightsToVector(TH1* _hist, std::vector<double>& _target){

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


void FitterInputs::NormedTH1::getData (std::vector<FitterData>& _data ){
  _data.clear();
  if(m_values.empty()){
    //std::cerr<< __FILE__ << ":"<< __LINE__ << "\t no data available, trying to reload it ... \n";
    this->setupFitterData();
  }

  _data.assign(m_values.begin(),m_values.end());
}

void FitterInputs::NormedTH1::init(){
  m_values.clear();
  this->setupFitterData();
}

void FitterInputs::NormedTH1::createFitterDataFromTH1(TH1* _hist, FitterData& _fdata){
  //setup
  _fdata.setName(_hist->GetName());
  _fdata.setType(DecideDataTypeFromString()(_hist->GetName()));
  _fdata.clear();
  
  //retrieve content
  std::vector<double> m_content;    
  pushBinContentsToVector(_hist,m_content);

  //retrieve weights
  std::vector<double> m_weights;
  pushBinWeightsToVector(_hist,m_weights);

  //ship to _fdata
  _fdata.setContentAndWeights(m_content,m_weights);
  _fdata.setHisto(_hist);
}

void FitterInputs::NormedTH1::setupFitterData(){

  FitterData metaData;
  if(m_data){
    m_values.reserve(m_values.capacity()+1);
    createFitterDataFromTH1(m_data,metaData);
    m_values.push_back(metaData);  
  }
  
  //normalize templates to each other
  normalizeTemplateTH1s();
  
  //load contents of TH1* templates to FitterData container
  std::vector<TH1*>::const_iterator tempItr = m_templates.begin();
  std::vector<TH1*>::const_iterator tempEnd = m_templates.end();
  m_values.reserve(m_values.capacity()+m_templates.size());
  for (; tempItr!=tempEnd; ++tempItr)
  {
    createFitterDataFromTH1((*tempItr),metaData);
    m_values.push_back(metaData);  
  }

}

void FitterInputs::NormedTH1::getTemplatesDeepCopy(std::vector<TH1*>& _templates){
  _templates.clear();
  _templates.reserve(m_templates.size());
  std::string name;
  for (int i = 0; i < m_templates.size(); ++i)
  {
    name = m_templates.at(i)->GetName();
    name += "_new";
    _templates.push_back(dynamic_cast<TH1*>(m_templates.at(i)->Clone(name.c_str())));
  }

}

void FitterInputs::NormedTH1::normalizeTemplateTH1s(){

  //this function assumes that we are provided 3 templates only!!

  if(m_templates.empty())
    return;

  ///////////////////////////////////////////////////////////////////////
  /////////////// create the sum of all templates

  //create name
  std::string preName = m_templates.front()->GetName();
  std::string totalName;
  if(preName.find("_true")!=std::string::npos)
    totalName = preName.substr(0,preName.find(""))+"_total";
  else
    totalName = "totalMC";

  //create object
  TH1D* total = dynamic_cast<TH1D*>(m_templates.front()->Clone(totalName.c_str()));

  //add all up
  std::vector<TH1*>::const_iterator histItr = m_templates.begin()+1;
  std::vector<TH1*>::const_iterator histEnd = m_templates.end();
  for (; histItr!=histEnd; ++histItr)
  {
    total->Add(*histItr);
  }

  //find integral
  double totalIntegral = total->Integral();

  //Scale all templates to give 1 in the sum
  histItr = m_templates.begin();
  for (; histItr!=histEnd; ++histItr)
  {
    (*histItr)->Scale(1/totalIntegral);
  }

  std::cout << ">>> normalized all distributions to add up to 1 in the integral\n";
  for (int i = 0; i < m_templates.size(); ++i)
  {
    std::cout << m_templates.at(i)->GetName() << "\t" << m_templates.at(i)->Integral()<<std::endl;
  }
  
}
