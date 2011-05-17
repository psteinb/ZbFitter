#include "AbsResult.hh"

void FitterResults::AbsResult::setupHistos(){

  if(!m_numOfParameters)
    m_numOfParameters = m_fitResults.size();

  if(m_templatesScaled.size()){
    // for (int i = 0; i < m_templatesScaled.size(); ++i)
    // {
    //   delete m_templatesScaled[i];
    // }
    m_templatesScaled.clear();
  }
  m_templatesScaled.reserve(m_numOfParameters);

  TH1* metaTemplate = 0;
  std::string name;
  std::vector<double>::const_iterator resItr = m_fitResults.begin();
  std::vector<double>::const_iterator resEnd = m_fitResults.end();
  for (int idx = 0; resItr!=resEnd; ++resItr,++idx)
  {
    name = getFunction()->getTemplate(idx)->getHisto()->GetName();
    name += "_scaled2FittedValues";
    metaTemplate = dynamic_cast<TH1*>(getFunction()->getTemplate(idx)->getHisto()->Clone(name.c_str()));
    metaTemplate->SetDirectory(0);
    if(m_doFractions)
      metaTemplate->Scale((*resItr)*getFunction()->getData()->getHisto()->Integral());
    else
      metaTemplate->Scale(*resItr);

    m_templatesScaled.push_back(metaTemplate);
  }
  
  
}
//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  


