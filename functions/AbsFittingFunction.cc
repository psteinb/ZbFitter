#define ABSFITTINGFUNCTION_CC
#include "functions/AbsFittingFunction.hh"
#include <functional>
#include <utility>
#include <algorithm>

void functions::AbsFittingFunction::setupFromInput (FitterInputs::AbsHisto* _input ){

  if(!_input){
    std::cerr << __FILE__ << "("<< __LINE__ <<")\t input unavailble, CANNOT LOAD DATA!!\n";
    return;
  }
    
  //receive the data from the input
  _input->getData(m_input);

  //sort the input to make searching easier
  std::sort(m_input.begin(), m_input.end(),compDataType());
  
  //data input
  if(m_input.size() && m_input.at(0).isA(FitterInputs::eData)){
    m_data = m_input.at(0);
  }

  //generate templates from input
  std::pair<std::vector<FitterInputs::FitterData>::iterator,std::vector<FitterInputs::FitterData>::iterator> bounds;
  bounds = std::equal_range(m_input.begin(), 
                            m_input.end(),FitterInputs::FitterData("",FitterInputs::eTempl),
                            compDataType());

  int nFound = bounds.second - bounds.first;
  if((nFound)!=0){
    //templates found
    m_templates.clear();
    m_templates.resize((nFound));
    std::copy(bounds.first, bounds.second, m_templates.begin());

    //anything left, then load the systematic distributions
    if((nFound+1) != m_input.size()){
      try{
        loadSystematics();}
      catch(std::exception& exc){
        std::cerr << __FILE__ << "("<< __LINE__ <<")\t loading systematics failed! >"<< exc.what() <<"<\n";}
    }
    else
      return;
  }
  else{
    //nothing found
    std::cerr << __FILE__ << "("<< __LINE__ <<")\t input does not have any templates stored\n";
    m_templates.clear();
    m_templatesSys.clear();
    return;
  }

}

void functions::AbsFittingFunction::loadSystematics(){

  std::vector<FitterInputs::FitterData>::const_iterator tempItr = m_templates.begin();
  std::vector<FitterInputs::FitterData>::const_iterator tempEnd = m_templates.end();

  
  m_templatesSys.resize(m_templates.size());
  int Cnt=0;

  for (; tempItr!=tempEnd; ++tempItr, ++Cnt)
  {
    int toAdd = std::count_if(
                              m_input.begin(), 
                              m_input.end(),
                              std::bind2nd(isAdjointSystematic(), tempItr->getName())
                              );

    m_templatesSys.at(Cnt).resize(toAdd);

    std::vector<FitterInputs::FitterData>::iterator newEnd = 
      std::remove_copy_if(
                          m_input.begin(), 
                          m_input.end(),
                          m_templatesSys.at(Cnt).begin(),
                          std::not1(std::bind2nd(isAdjointSystematic(), tempItr->getName()))
                          );
    m_templatesSys.at(Cnt).erase(
                                 newEnd,
                                 m_templatesSys.at(Cnt).end()
                                 );
  }


}
