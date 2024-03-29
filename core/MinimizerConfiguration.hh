#ifndef _MINIMIZERCONFIGURATION_HH_
#define _MINIMIZERCONFIGURATION_HH_

#include <map>
#include <string>
#include <sstream>
#include "Math/Minimizer.h"
#include "TString.h"

namespace core {

struct  MinimConfigItem
{
  double Start;
  double Step;
  bool lowConstrain;
  bool highConstrain;
  double LowLimit;
  double HighLimit;
  std::string Name;
  bool omitMeFromFit;
  bool omitSet;
  
  MinimConfigItem():
    Start(1.),
    Step(0.),
    lowConstrain(false),
    highConstrain(false),
    LowLimit(0.),
    HighLimit(100.),
    Name("Parameter"),
    omitMeFromFit(false),
    omitSet(false)
  {};

  void setItem(const std::string& _key, const std::string& _value){
   
    int metaInt = 0;
    TString tKey = _key.c_str();
    tKey.ToLower();

    //yiek, a huge if else
    //can't do it any better for now
    if(tKey.Contains("name",TString::kIgnoreCase))
      Name = _value;
    
    if(tKey.Contains("start",TString::kIgnoreCase))
      Start = string2double(_value);
    
    if(tKey.Contains("step",TString::kIgnoreCase))
      Step = string2double(_value);

    if(tKey.Contains("low",TString::kIgnoreCase)){
      LowLimit = string2double(_value);
      lowConstrain = true;
    }

    if(tKey.Contains("high",TString::kIgnoreCase)){
      HighLimit = string2double(_value);
      highConstrain = true;
    }
    
    if(tKey.Contains("omit",TString::kIgnoreCase) && !omitSet){
      omitMeFromFit = true;
      omitSet= true;
    }


     
  }

  bool isFixed() const{
    if(Start && !Step)
      return true;
    else
      return false;
  }

  void print() const {
    std::cout << "MinimConfigItem\t"<< Name << "\t" << Start << ", " << Step;
      if(!omitMeFromFit)
        std::cout    << ((isFixed()) ? " fixed " : " ") << " "
                     << ((lowConstrain) ? LowLimit : -999. ) << " "
                     << ((highConstrain) ? HighLimit : +999. ) << " ";
      else
        std::cout    << " omitted from fit";

    std::cout  << "\n";
   }

  double string2double( const std::string& _value){
    
    std::istringstream instream;
    double metaDouble = 0.;
    double value =0.;
    instream.str(_value); 
    if( !(instream >> metaDouble) ){
      std::cerr << "MinimConfigItem::string2double \t invalid argument format in "<< _value << std::endl;
      value = 0;
    }
    else{
      value = metaDouble;
    }

    return value;
  }
  
};

class MinimizerConfiguration
{
  std::map<std::string,std::string> m_config;
  std::vector<MinimConfigItem> m_items;
  std::vector<std::string> m_names;
  std::vector<std::string> m_namesConfigured;

  void determineItemsFromMap();
  void loadItemsFromMap();
  
  int itemsToConfigure;
  int itemsFixed;
  int itemsTotal;

public:
  MinimizerConfiguration():
    m_config(),
    m_items(),
    m_names(),
    m_namesConfigured(),
    itemsToConfigure(0),
    itemsFixed(0),
    itemsTotal(0)
  {};

  virtual ~MinimizerConfiguration(){};
  
  void setNames(const std::vector<std::string>& _names){
    if(_names.size())
      m_names = _names;
  };

  const std::vector<std::string>* getNames() const {
    if(m_names.size())
      return &m_names;
    else
      0;
  };
  
  const std::vector<std::string>* getConfiguredNames() const {
    if(m_namesConfigured.size())
      return &m_namesConfigured;
    else
      0;
  };

  void configureMinimizer(ROOT::Math::Minimizer*);

  void init(const std::map<std::string,std::string>& _map,const std::vector<std::string>& _names){
    m_config = _map;
    
    determineItemsFromMap();

    setNames(_names);

    loadItemsFromMap();
  };

  void print(){
    std::cout << __FILE__ << "\n";
    std::vector<MinimConfigItem>::const_iterator itItr = m_items.begin();
    std::vector<MinimConfigItem>::const_iterator itEnd = m_items.end();

    for (short i =0; itItr!=itEnd; ++itItr,i++)
      (*itItr).print();
  
  }


  int getNumberOfParametersConfigured(){return itemsToConfigure;};
  int getNumberOfParametersFixed(){return itemsFixed;};
  int getNumberOfParameters(){return itemsTotal;};

  MinimConfigItem* getItem(const int& _index){
    MinimConfigItem* value=0;
    if(_index>-1 && _index<m_items.size())
      value = &(m_items[_index]);
    
    return value;
  };
};

};
#endif /* _MINIMIZERCONFIGURATION_H_ */
