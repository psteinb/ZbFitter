#ifndef _EXPERIMENTERSINPUT_H_
#define _EXPERIMENTERSINPUT_H_

#include <vector>


class ExperimentersInput
{
  //output
  std::vector<double> means;
  std::vector<double> meansRMS;
  std::vector<double> sigma;
  std::vector<double> sigmaRMS;

  //input
  std::vector<TH1*>     templates;
  TH1*                  data;

public:
  ExperimentersInput(const int& _numParameters=4):
    means(_numParameters),
    meansRMS(_numParameters),
    sigma(_numParameters),
    sigmaRMS(_numParameters),
    templates(_numParameters),
    data(0)
  {
  };

  virtual ~ExperimentersInput(){
    for (int i = 0; i < templates.size(); ++i)
    {
      delete templates[i];templates[i] = 0;
    }
    delete data;data=0;
  };
  
  void setMean(const int& _idxParameter,const double& _value){
    if(_idxParameter<0 || _idxParameter>(means.size()-1))
      return;
    means[_idxParameter] = _value;
  }
  
  void setMeanRMS(const int& _idxParameter,const double& _value){
    if(_idxParameter<0 || _idxParameter>(meansRMS.size()-1))
      return;
    meansRMS[_idxParameter] = _value;
  }

  void setSigma(const int& _idxParameter,const double& _value){
    if(_idxParameter<0 || _idxParameter>(sigmas.size()-1))
      return;
    sigmas[_idxParameter] = _value;
  }
  
  void setSigmaRMS(const int& _idxParameter,const double& _value){
    if(_idxParameter<0 || _idxParameter>(sigmasRMS.size()-1))
      return;
    sigmasRMS[_idxParameter] = _value;
  }
  
  double getMean(const int& _idxParameter){
    if(_idxParameter<0 || _idxParameter>(means.size()-1))
      return 0.;
    else
      return means.at(_idxParameter);
  }
  
  double getMeanRMS(const int& _idxParameter){
    if(_idxParameter<0 || _idxParameter>(meansRMS.size()-1))
      return 0.;
    else
      return meansRMS.at(_idxParameter);
  }
  
  double getSigma(const int& _idxParameter){
    if(_idxParameter<0 || _idxParameter>(sigmas.size()-1))
      return 0.;
    else
      return sigmas.at(_idxParameter);
  }
  
  double getSigmaRMS(const int& _idxParameter){
    if(_idxParameter<0 || _idxParameter>(sigmasRMS.size()-1))
      return 0.;
    else
      return sigmasRMS.at(_idxParameter);
  }
};

#endif /* _EXPERIMENTERSINPUT_H_ */
