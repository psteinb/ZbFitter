#define _MINIMIZERCONFIGURATION_CC_
#include "core/MinimizerConfiguration.hh"

#include <set>

void core::MinimizerConfiguration::determineItemsFromMap(){

  std::set<std::string> metaNames;
  
  std::map<std::string,std::string>::const_iterator mItr = m_config.begin();
  std::map<std::string,std::string>::const_iterator mEnd = m_config.end();

  std::string subString="";
  size_t endItem=0;
  for (; mItr!=mEnd; ++mItr)
  {
    endItem = mItr->first.find_first_of(".");
    if(endItem != std::string::npos){
      subString = mItr->first.substr(0,endItem);
      metaNames.insert(subString);
    }
    else
      endItem = std::string::npos;
    
  }

  m_names.clear();
  m_names.reserve(metaNames.size());
  std::set<std::string>::const_iterator sItr = metaNames.begin();
  std::set<std::string>::const_iterator sEnd = metaNames.end();
  for (; sItr!=sEnd; ++sItr)
  {
    m_names.push_back(*sItr);
  }

  
}


void core::MinimizerConfiguration::loadItemsFromMap(){

  std::map<std::string,std::string>::const_iterator mItr ;
  std::map<std::string,std::string>::const_iterator mEnd = m_config.end();

  m_namesConfigured.clear();
  m_namesConfigured.reserve(m_names.size());

  m_items.clear();
  m_items.reserve(m_names.size());

  std::string metaString="";
  
  for (int nameIdx = 0; nameIdx < m_names.size(); ++nameIdx)
  {
    mItr = m_config.begin();
    MinimConfigItem metaConfigItem;

    for (; mItr!=mEnd; ++mItr)
    {
      if(mItr->first.find(m_names[nameIdx])!=std::string::npos){
        metaString = mItr->first.substr(mItr->first.find_first_of(".")+1);
        metaConfigItem.setItem(metaString,mItr->second);
      }
    }
    m_items.push_back(metaConfigItem);
    m_namesConfigured.push_back(metaConfigItem.Name);

    itemsTotal++;
    if(!metaConfigItem.omitMeFromFit)
      itemsToConfigure++;
    
    if(metaConfigItem.isFixed() || metaConfigItem.omitMeFromFit)
      itemsFixed++;
  }
  
  
}


void core::MinimizerConfiguration::configureMinimizer(ROOT::Math::Minimizer* _minim){

  std::vector<MinimConfigItem>::const_iterator itItr = m_items.begin();
  std::vector<MinimConfigItem>::const_iterator itEnd = m_items.end();

  for (short i =0; itItr!=itEnd; ++itItr,i++)
  {
    if(itItr->omitMeFromFit){
      itItr->print();
      std::cout << "==> omitted from fit\n";
      continue;
    }

    if(itItr->isFixed()){
      _minim->SetFixedVariable(i,itItr->Name,itItr->Start);
      // std::cout << "setting "<<i<<" fixed\n" ;
      continue;
    }

    if(itItr->lowConstrain && itItr->highConstrain){
      _minim->SetLimitedVariable(i,itItr->Name,itItr->Start,itItr->Step,
                                 itItr->LowLimit,itItr->HighLimit);
      // std::cout << "setting "<<i<<" 2 constrained\n" ;
      continue;
    }

    if(itItr->lowConstrain && !(itItr->highConstrain)){
      _minim->SetLowerLimitedVariable(i,itItr->Name,itItr->Start,itItr->Step,
                                      itItr->LowLimit);
      // std::cout << "setting "<<i<<" low constrained\n" ;
      continue;
    }
    
    if(!(itItr->lowConstrain) && (itItr->highConstrain)){
      _minim->SetUpperLimitedVariable(i,itItr->Name,itItr->Start,itItr->Step,
                                      itItr->HighLimit);
      // std::cout << "setting "<<i<<" high constrained\n" ;
      continue;
    }
    
    if(!(itItr->lowConstrain) && !(itItr->highConstrain)){
      _minim->SetVariable(i,itItr->Name,itItr->Start,itItr->Step);
      // std::cout << "setting "<<i<<" high constrained\n" ;
      continue;
    }
  }
}
