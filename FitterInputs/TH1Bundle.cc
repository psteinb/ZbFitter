#include "TH1Bundle.hh"
#include <algorithm>
#include "TString.h"

// Constructors/Destructors
//  

TH1Bundle::TH1Bundle ( ):
  AbsHisto(),
  m_dataPlotName(""),
  m_dataFile    (""),
  m_mcFileNames (""),
  m_mcPlotNames (""),
  m_data(0),
  m_templates(3,0),
  m_dataEntries(),
  m_templatesEntries(),
  m_files()
{
  m_files.reserve(4);
  m_templates.reserve(3);
}

TH1Bundle::~TH1Bundle ( ) {
  delete m_data;
  m_data = 0;

  for (int i = 0; i < m_templates.size(); ++i)
  {
    if(!m_templates.at(i)){
      m_templates.at(i)->Close();
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

const TH1* TH1Bundle::openFile(const std::string& _fileName){

  std::vector<TFile*>::const_iterator fItr = std::find_if(m_files.begin(), m_files.end(),
                                                          std::bind2nd(TFileNameCompare(),_fileName));
  if(fItr!=m_files.end())
    return (*fItr);
  else{
    m_files.push_back(TFile::Open(_fileName.c_str()));
    return m_files.back();
  }
    
  
}

void TH1Bundle::loadData (const std::string& _fileName, const std::string& _histoNames ){
  
  if(_fileName.empty() || _histoNames.empty()){
    std::cerr<< __FILE__ << ":"<< __LINE__ << "\t File name or histo name not filled " << _fileName.c_str() << "("<< _histoNames.c_str() <<")\n";
  }

  
  m_data = openFile(_fileName)->Get(_histoNames.c_str());
  if(!m_data)
    std::cerr<< __FILE__ << ":"<< __LINE__ << "\t histo named "<< _histoNames.c_str() <<" not found in " << _fileName.c_str() <<")\n";

}

void TH1Bundle::loadTemplatesFromOneFile (const std::string& _fileNames, const std::string& _histoNames ){

  TFile* fileObject = openFile(_fileNames);
  if(!fileObject || _fileNames.empty())
  {
    std::cerr<< __FILE__ << ":"<< __LINE__ << "\t File name not filled or not found " << _fileName.c_str()  <<")\n";
    return;
  }

  if(_histoNames.empty()){
    std::cerr<< __FILE__ << ":"<< __LINE__ << "\t histo names "<< "("<< _histoNames.c_str() <<") empty for " << _fileName.c_str() <<"\n";
    return
  }

  TString HistNames(_histoNames.c_str());
  TObjArray* Histo = HistNames.Tokenize(",");
  TString aHistName;
  TH1* metaObject = 0;
  for (int i = 0; i < Histo->GetEntries(); ++i)
  {
    aHistName = Histo->At(i)->GetString();
    metaObject = dynamic_cast<TH1*>(fileObject->Get(aHistName.Data()));

    if(metaObject){
      m_templates.push_back(metaObject);
    }
    else
      std::cerr << __FILE__ << ":"<< __LINE__ << "\t couldn't load " << aHistName.Data() << " from " << _fileNames << std::endl;
      
  }
  
}

void TH1Bundle::loadTemplatesFromMultipleFiles (const std::string& _fileNames, const std::string& _histoNames){
  if(!fileObject || _fileNames.empty())
  {
    std::cerr<< __FILE__ << ":"<< __LINE__ << "\t File name not filled or not found " << _fileName.c_str()  <<")\n";
    return;
  }

  if(_histoNames.empty()){
    std::cerr<< __FILE__ << ":"<< __LINE__ << "\t histo names "<< "("<< _histoNames.c_str() <<") empty for " << _fileName.c_str() <<"\n";
    return
  }

  TString FileNames(_fileNames.c_str());
  TObjArray* Files = FileNames.Tokenize(",");
  TString HistNames(_histoNames.c_str());
  TObjArray* Histo = HistNames.Tokenize(",");
  TString aFileName;
  TString aHistName;
  for (int i = 0; i < Files->GetEntries(); ++i)
  {
    aFileName = Files->At(i)->GetString();
    aHistName = Histo->At(i)->GetString();
    loadTemplatesFromOneFile(aFileName.Data(),aHistName.Data());
  }
}

void TH1Bundle::loadTemplates (const std::string& _fileNames , const std::string& _histoNames  ){
  
  if(_fileName.empty() || _histoNames.empty()){
    std::cerr<< __FILE__ << ":"<< __LINE__ << "\t File name or histo name not filled " << _fileName.c_str() << "("<< _histoNames.c_str() <<")\n";
    return;
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

void TH1Bundle::pushBinContentsToVector(TH1* _hist, std::vector<double>& _target){

  _target.clear();
  if(!_hist){
    std::cerr<< __FILE__ << ":"<< __LINE__ << "\t no histo available\n";
    return;
  }

  _target.reserve(_hist->GetNbinsX());
  
  for (int i = 0; i < _hist->GetNbinsX(); ++i)
  {
    _data.push_back();
  }
  
}

void TH1Bundle::getData (std::vector<double>& _data ){
  _data.clear();
  if(!m_data){
    std::cerr<< __FILE__ << ":"<< __LINE__ << "\t no data histo available\n";
    return;
  }

  _data.reserve(m_data->GetNbinsX());
  
  pushBinContentsToVector(m_data,_data);

}

void TH1Bundle::getTemplates (std::vector<std::vector<double> >& _templates ){
  _templates.clear();
  

  if(!m_templates.size()){
    std::cerr<< __FILE__ << ":"<< __LINE__ << "\t no templates histos available\n";
    return;
  }

  _templates.resize(m_templates.size());
    
  for (int i = 0; i < m_templates.size(); ++i)
  {
    pushBinContentsToVector(m_templates.at(i),_templates.at(i));
  }
  

}
