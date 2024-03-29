#ifndef _FRACTIONEXPERIMENTPERFORMERS_H_
#define _FRACTIONEXPERIMENTPERFORMERS_H_

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <sstream>


#include "lineariy/ConfLinearTest.hh"
#include "core/FitCore.hh"
#include "FitterInputs/NormedTH1.hh"
#include "functions/BinnedEMLFraction.hh"
#include "Studies/PseudoStudy.hh"
#include "Studies/ProtoCreators.hh"
#include "FitterInputs/NormalisationFunctors.hh"
#include "FitterResults/HistoResult.hh"
#include "lineariy/BasePerformer.hh"
#include "lineariy/LinearTestFunctors.hh"



class FractionExperimentPerformer : public BasePerformer
{
  ConfLinearTest m_configuration;
  double m_scale;
  std::string m_outname;
  std::vector<TH1*> m_templates;
  TH1* m_data;
  PseudoStudy<FitterInputs::NormedTH1<FitterInputs::Norm2Unity>, functions::BinnedEMLFraction>*  m_PseudoStudy;

  void createExpectedValuesFromTemplates();
public:

  FractionExperimentPerformer( const ConfLinearTest& _configuration, 
                       const double& _scale=1.
                       ):
    BasePerformer(),
    m_configuration(_configuration),
    m_scale(_scale),
    m_outname(),
    m_templates(),
    m_data(0),
    m_PseudoStudy(0)
  {
    std::ostringstream name(_configuration.p_outputfile);
    name << "_step"<<_scale;
    m_outname = name.str();
  };

  FractionExperimentPerformer( const FractionExperimentPerformer& _other):
    BasePerformer(_other),
    // m_means(_other.m_means),
    // m_sigmas(_other.m_sigmas),
    // m_expected(_other.m_expected)
    m_configuration(_other.m_configuration),
    m_scale(_other.m_scale),
    m_outname(_other.m_outname),
    m_templates(_other.m_templates),
    m_data(_other.m_data),
    m_PseudoStudy(0)
  {
    std::cout << _other.m_outname << "COPIED\n";
  };

  virtual ~FractionExperimentPerformer(){

    delete m_data;
    for (int i = 0; i < m_templates.size(); ++i)
    {
      delete m_templates[i];
    }
    m_templates.clear();

  };

  void experiment()  ;
  
  void print() const{
    std::cout << "FractionExperimentPerformer at "<<m_scale<<std::endl;
    this->printContent();
  };

  void prepare();
  

};


void FractionExperimentPerformer::createExpectedValuesFromTemplates(){

  std::vector<double> metaExpected(m_templates.size(),0.);

  std::vector<double> integrals(m_templates.size(),0.);
  std::vector<double> errors(m_templates.size(),0.);
  double total = 0.;
  for (int i = 0; i < m_templates.size(); ++i)
  {
    integrals[i] = m_templates[i]->IntegralAndError(m_templates[i]->GetXaxis()->GetFirst(),
                                                   m_templates[i]->GetXaxis()->GetLast(),
                                                   errors[i]
                                                   );
    if(i<1)
      total += m_scale*integrals[i];
    else
      total += integrals[i];
  }

  double dataIntegral = m_data->Integral();

  for (int i = 0; i < m_templates.size(); ++i)
  {
    if(i<1)
      metaExpected[i] = (integrals[i]/total)*m_scale;
    else
      metaExpected[i] = (integrals[i]/total);
    std::cout << m_scale<< "x, expected value ["<<i <<"]\t"<<metaExpected[i] <<std::endl;
  }

  this->setExpected(metaExpected);

}

void FractionExperimentPerformer::prepare( )  {
  // ----- INPUT ----- 
  FitterInputs::NormedTH1<FitterInputs::Norm2Unity>* input = new FitterInputs::NormedTH1<FitterInputs::Norm2Unity>();
  input->loadData(m_configuration.p_datadir.c_str(),m_configuration.p_dataTitle.c_str(),m_configuration.p_rebin);
  input->loadTemplates(m_configuration.p_datadir.c_str(),m_configuration.p_tempTitle.c_str(),m_configuration.p_rebin);

  input->getTemplatesDeepCopy(m_templates);
  m_data =  input->getDataDeepCopy();

  if(m_configuration.p_dataScale!=1.)
    m_data->Scale(m_configuration.p_dataScale);


  this->createExpectedValuesFromTemplates();

  scaleMCByValue aScaler(m_scale);
  // dummy values here for they are only important for the pulls
  std::vector<double> expectedErrors    (m_templates.size(),1.);
  std::vector<double> expected    (getExpected()->begin(),getExpected()->end());
  
  m_PseudoStudy = new PseudoStudy<FitterInputs::NormedTH1<FitterInputs::Norm2Unity>, functions::BinnedEMLFraction>(
                                                                                                                          m_templates,expected,expectedErrors,
                                                                                                                          (m_data->Integral()),m_configuration.p_threads,
                                                                                                                          m_configuration.p_nIter
                                                                                                                          );

   m_PseudoStudy->setProtoCreator(&aScaler);
   m_PseudoStudy->setFitterConfigFile(createScaledConfigFileString(m_configuration.p_configFile,m_scale));
   m_PseudoStudy->setFitEngine(m_configuration.p_fitEngine);
   m_PseudoStudy->setFitMode(m_configuration.p_fitMode);
   m_PseudoStudy->setVerbosity(m_configuration.p_msgLevel);
   m_PseudoStudy->setBaseName(this->m_outname);

   delete input;
}

void FractionExperimentPerformer::experiment( )  {
  
  // ----- PSEUDO EXPERIMENTS ----- 
  m_PseudoStudy->experiment();

  std::vector<std::vector<TH1*> > m_results(m_templates.size());
  std::vector<double> metaMeans;metaMeans.reserve(m_templates.size());
  std::vector<double> metaSigmas;metaSigmas.reserve(m_templates.size());

  for (int i = 0; i < m_templates.size(); ++i)
  {
    m_PseudoStudy->getResultsOfParameter(i,m_results[i]);
    metaMeans.push_back(m_results[i][0]->GetMean());
    metaSigmas.push_back(m_results[i][1]->GetMean());
  }

  setMeans(metaMeans);
  setSigmas(metaSigmas);
}


#endif /* _EXPERIMENTPERFORMERS_H_ */
