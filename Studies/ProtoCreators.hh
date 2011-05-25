#ifndef _PROTOCREATORS_H_
#define _PROTOCREATORS_H_

class BaseProtoCreator
{
public:

  virtual void operator()(TH1* _total, const std::vector<TH1*>& _input) const {
    
    std::cerr << __FILE__ << ":BaseProtoCreator \t USED\n";
    
  };

};

class defaultMCValues : public BaseProtoCreator
{
  
public:

  void operator()(TH1* _total, const std::vector<TH1*>& _input) const {

    if(_total->GetEntries()!=0){
      _total->Reset("MICE");
      _total->ResetStats();}
    

    for (int i = 0; i < _input.size(); ++i)
    {
      _total->Add(_input[i]);
    }
    
  };

  //private:

};

class MCValues : public BaseProtoCreator
{
  bool externalProtoFunctions;
  std::vector<TH1*> m_functions;
  std::vector<std::string> m_histoNames;
  TFile* m_file;
  
  void loadHistoNamesFromString(const std::string& _text=""){
    
    TString content = _text.c_str();
    TObjArray* tokens = content.Tokenize(",");
    m_histoNames.clear();
    m_histoNames.reserve(tokens->GetEntries());
    for (int i = 0; i < tokens->GetEntries(); ++i)
    {
      m_histoNames.push_back(dynamic_cast<TObjString*>(tokens->At(i))->GetString().Data());
    }
  }
  
public:
  MCValues(const std::string& _file="",const std::string& _text=""):
    externalProtoFunctions(!_text.empty()),
    m_functions(),
    m_histoNames(),
    m_file(TFile::Open(_file.c_str()))
  {
    loadHistoNamesFromString(_text);
    m_functions.clear();
    m_functions.reserve(m_histoNames.size());
    TH1* meta = 0;
    for (int i = 0; i < m_histoNames.size(); ++i)
    {
      meta = 0;
      if(m_file && !m_file->IsZombie()){
        std::string name = m_histoNames[i];
        name += "_proto";
        meta = dynamic_cast<TH1*>(m_file->Get(m_histoNames[i].c_str())->Clone(name.c_str()));
        meta->SetDirectory(0);
      }
      if (meta)
      {
        m_functions.push_back(meta);
      }
        
      
    }
  }

  const std::vector<TH1*>* getProtoFunctions(){
    return &m_functions;
  }

  void operator()(TH1* _total, const std::vector<TH1*>& _input){

    if(_total->GetEntries()!=0){
      _total->Reset("MICE");
      _total->ResetStats();}
    
    bool equalInputs = _input.size()==m_functions.size();
    for (int i = 0; i < _input.size(); ++i)
    {
      if(externalProtoFunctions && equalInputs)
        _total->Add(m_functions[i]);
      else
        _total->Add(_input[i]);
    }
    
  };

  //private:

};

#endif /* _PROTOCREATORS_H_ */
