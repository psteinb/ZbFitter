#pragma once
#ifndef NORMALISATIONFUNCTORS_H
#define NORMALISATIONFUNCTORS_H
#include "TH1.h"

namespace FitterInputs {
class Norm2MCFrac
{
public:
  Norm2MCFrac(){};
  virtual ~Norm2MCFrac(){};

  void operator()(std::vector<TH1*>& _templates){
      //create name

  std::string preName = _templates.front()->GetName();
  std::string totalName;
  if(preName.find("_true")!=std::string::npos)
    totalName = preName.substr(0,preName.find(""))+"_total";
  else
    totalName = "totalMC";

  //create object
  TH1* total = dynamic_cast<TH1*>(_templates.front()->Clone(totalName.c_str()));
  total->Reset("MICE");
  total->ResetStats();
  
  //add all up
  std::vector<TH1*>::iterator histItr = _templates.begin();
  std::vector<TH1*>::iterator histEnd = _templates.end();
  for (; histItr!=histEnd; ++histItr)
  {
    total->Add(*histItr);
  }

  //find integral
  double totalIntegral = total->Integral();

  //Scale all templates to give 1 in the sum
  histItr = _templates.begin();
  for (; histItr!=histEnd; ++histItr)
  {
    std::cout << "\n\noriginal\t" << (*histItr)->GetName() << "\t" << (*histItr)->Integral() << " , max " << (*histItr)->GetMaximum()  <<std::endl;


    (*histItr)->Scale(1/totalIntegral);

    std::cout << "\n\nscaled\t" << (*histItr)->GetName() << "\t" << (*histItr)->Integral()<< " , max " << (*histItr)->GetMaximum()<<std::endl;

  }

  }
};


class Norm2AThird
{
public:
  Norm2AThird(){};
  virtual ~Norm2AThird(){};

  void operator()(std::vector<TH1*>& _templates){
      //create name

  std::vector<TH1*>::iterator histItr = _templates.begin();
  std::vector<TH1*>::iterator histEnd = _templates.end();
  double Normalisation = 0.;
  double binWidth = 0;
  for (; histItr!=histEnd; ++histItr)
  {
    std::cout << "\n\noriginal\t" << (*histItr)->GetName() << "\t" << (*histItr)->Integral() << "("<< (*histItr)->Integral("width") <<")" << " , max " << (*histItr)->GetMaximum() << ", w: "<<(*histItr)->GetBinWidth(1) <<std::endl;
    (*histItr)->Print("all");

    binWidth = (*histItr)->GetBinWidth(1);
    Normalisation = 1./double((*histItr)->Integral()*_templates.size()*binWidth);
    /////////////////////////////////////////////////////////
    (*histItr)->Scale(Normalisation);
    ////////////^^^^^^^^^^^^^^^^^^^^^^^^^^^^^////////////////
    //// this computest newbin = (bin*scale)/width
    //// see http://root.cern.ch/root/html528/src/TH1.cxx.html#1055
    //// used by http://root.cern.ch/root/html528/src/TH1.cxx.html#5545

    std::cout << "\n\nscaled\t" << (*histItr)->GetName() << "\t entries: " << (*histItr)->Integral() << " ( integral: "<< (*histItr)->Integral("width") <<")"<< " , max " << (*histItr)->GetMaximum()<<std::endl;
    (*histItr)->Print("all");
  }

  }
};


class Norm2Unity
{
public:
  Norm2Unity(){};
  virtual ~Norm2Unity(){};

  void operator()(std::vector<TH1*>& _templates){
      //create name

  std::vector<TH1*>::iterator histItr = _templates.begin();
  std::vector<TH1*>::iterator histEnd = _templates.end();
  double Normalisation = 0.;

  for (; histItr!=histEnd; ++histItr)
  {
    std::cout << "\n\noriginal\t" << (*histItr)->GetName() << "\t" << (*histItr)->Integral() << "("<< (*histItr)->Integral("width") <<")" << " , max " << (*histItr)->GetMaximum() << ", w: "<<(*histItr)->GetBinWidth(1) <<std::endl;
    (*histItr)->Print("all");
    
    Normalisation = 1./double((*histItr)->Integral());
    /////////////////////////////////////////////////////////
    (*histItr)->Scale(Normalisation);
    ////////////^^^^^^^^^^^^^^^^^^^^^^^^^^^^^////////////////
    //// this computest newbin = (bin*scale)/"width"
    //// see http://root.cern.ch/root/html528/src/TH1.cxx.html#1055
    //// used by http://root.cern.ch/root/html528/src/TH1.cxx.html#5545

    std::cout << "\n\nscaled\t" << (*histItr)->GetName() << "\t entries: " << (*histItr)->Integral() << " ( integral: "<< (*histItr)->Integral("width") <<")"<< " , max " << (*histItr)->GetMaximum()<<std::endl;
    (*histItr)->Print("all");
  }

  }
};

};
#endif
