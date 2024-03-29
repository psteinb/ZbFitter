#pragma once
#ifndef __BASESTUDY_HH__
#define __BASESTUDY_HH__

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

#include "core/FitCore.hh"
#include "FitterInputs/NormedTH1.hh"
#include "FitterResults/HistoResult.hh"
#include "FitterResults/LLHResult.hh"
#include "functions/SimpleMaxLLH.hh"

#include "TRandom3.h"
#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "Math/Minimizer.h"


class BaseStudy{

  // InputT* m_input;
  // FunctionT m_fitter;
  // ProtoCreator m_creator;
  
  std::string m_fitConfigFile       ;
  std::string m_fitEngine       ;
  std::string m_fitMode         ;
  std::string m_baseName;

  std::vector<TH1*> m_templateTH1s;
  TH1* m_total;
  std::vector<TH1*> m_resultTH1s;
  TH1D* m_maxLLH;

  // int m_threads;
  int m_iterations;

  TRandom3 m_TRand3;

  //results to produce
  std::vector<TH1D> m_pulls;
  std::vector<TH1D> m_MigradPulls;
  std::vector<TH1D> m_means;
  std::vector<TH1D> m_sigmas;
  std::vector<TH2D> m_correlations;
  
  std::vector<double> m_expectedValues   ;
  std::vector<double> m_expectedErrors      ;
  double              m_dataIntegral	;

  std::vector<double> m_fitValues;
  std::vector<double> m_fitErrorsUp;
  std::vector<double> m_fitErrorsDown;
  std::vector<int>    m_fitErrorsStatus;
  std::vector<TCanvas*>    m_resultCanvas;
  

  bool m_doPanicPrint;
  int m_verbosity;

  //setups
  // void setupData(TH1* _data){
  //   m_input->setDataHisto(_data);
  //   //m_input->setTemplateHistos(_templates);
  //   m_input->initData();
  // }
  

  // void setupInput(TH1* _data, const std::vector<TH1*> _templates){
  //   m_input->setDataHisto(_data);
  //   m_input->setTemplateHistos(_templates);
  //   m_input->init();
  // }


  template<typename T>
  std::string addItemToText(const std::string& _text, const T& _aT){
    std::ostringstream value;
    value<< _text.c_str() << _aT;
    return value.str();
  }

  void setupCorrelationResult(){

  }


  void setupResults(const int& _size){
    
    double expMeanDown = 0.;
    double expMeanUp = 0.;

    double expSigmaDown = 0.;
    double expSigmaUp = 0.;

    for (int i = 0; i < _size; ++i)
    {
      expMeanDown = 0.*m_expectedValues.at(i);
      expMeanUp = 2.*(m_expectedValues.at(i));
      expSigmaDown = 0.;
      expSigmaUp = 1.*(m_expectedValues.at(i));

      m_pulls[i] = TH1D(addItemToText<int>("pull_par",i).c_str(),"pull",80,-8,8);
      m_pulls[i].GetXaxis()->SetTitle(addItemToText<int>("pull: ",i).c_str());
      //m_pulls[i].SetBit(TH1::kCanRebin);

      m_MigradPulls[i] = TH1D(addItemToText<int>("Migrad_pull_par",i).c_str(),"pull",80,-8,8);
      m_MigradPulls[i].GetXaxis()->SetTitle(addItemToText<int>("pull: ",i).c_str());
      //m_MigradPulls[i].SetBit(TH1::kCanRebin);

      m_means[i] = TH1D(addItemToText<int>("mean_par",i).c_str(),"mean fitted",
                        80,expMeanDown,expMeanUp);
      m_means[i].GetXaxis()->SetTitle(addItemToText<int>("fitted: ",i).c_str());
      //m_means[i].SetBit(TH1::kCanRebin);

      m_sigmas[i] = TH1D(addItemToText<int>("sigma_par",i).c_str(),"sigma fitted",
                         80,expSigmaDown,expSigmaUp);
      m_sigmas[i].GetXaxis()->SetTitle(addItemToText<int>("fitted error: ",i).c_str());
      //m_sigmas[i].SetBit(TH1::kCanRebin);
    }

    setupCorrelationResults();


  }

  void preparePlots(const std::string& _baseName, FitterResults::HistoResult* _histo= 0, FitterResults::LLHResult* _llh = 0){
             
    std::string cName = _baseName;
    cName += "_fit";
    cName += ".root";
    std::string llhName = _baseName;
    llhName += "_LLH";
    llhName += ".root";
    _histo->setFileName(cName.c_str());
    _llh->setFileName(llhName.c_str());
    
  }

  void setupTotalTemplates(){

    m_total = dynamic_cast<TH1*>(m_templateTH1s.front()->Clone("total"));
    m_total->SetDirectory(0);
    m_total->Reset("MICE");
    m_total->ResetStats();
    
    //ProtoCreator creator;
    m_creator(m_total,m_templateTH1s);
    
  };  

  void prepareData(TH1*& _data=0){
    _data = (TH1*)m_templateTH1s[0]->Clone("data");
    _data->SetDirectory(0);
    _data->Reset("MICE");
    _data->ResetStats();
  };
  
  void treatResultsFromMinimizer(const std::vector<std::string>* _names){
    std::vector<TH1D>::iterator rItr = m_means.begin()    ;
    std::vector<TH1D>::iterator rEnd = m_means.end()      ;
    for (short i = 0; rItr!=rEnd; ++rItr,i++)
    {
      rItr->GetXaxis()->SetTitle(addItemToText<std::string>("fitted ",_names->at(i)).c_str());
    }

    rItr = m_sigmas.begin()    ;
    rEnd = m_sigmas.end()      ;
    for (short i = 0; rItr!=rEnd; ++rItr,i++)
    {
      rItr->GetXaxis()->SetTitle(addItemToText<std::string>("#sigma ",_names->at(i)).c_str());
    }

    rItr = m_pulls.begin()    ;
    rEnd = m_pulls.end()      ;
    for (short i = 0; rItr!=rEnd; ++rItr,i++)
    {
      rItr->GetXaxis()->SetTitle(addItemToText<std::string>("pull ",_names->at(i)).c_str());
    }
  };


  

public:
  
  BaseStudy(const std::vector<TH1*>& _templates,
              const std::vector<double>& _expected,
              const std::vector<double>& _expectedErrors,
              const double& _dataIntegral,
              const int& _thr=1,
              const int& _iters=5000
              ):
    // m_input(new InputT()),
    // m_fitter(),
    // m_creator(),
    m_fitConfigFile(""),       
    m_fitEngine("Minuit2"),       
    m_fitMode  ("Migrad"),       
    m_baseName("BaseStudy_"),
    m_templateTH1s(_templates.size(),0),
    m_total(0),
    m_resultTH1s(),
    m_maxLLH(new TH1D("maxLLH",";max(logLH);N",200,-400,0)),
    m_threads(_thr),
    m_iterations(_iters),
    m_TRand3(),
    m_pulls(_templates.size()),
    m_MigradPulls(_templates.size()),
    m_means(_templates.size()),
    m_sigmas(_templates.size()),
    m_expectedValues    (_expected),   
    m_expectedErrors    (_expectedErrors),   
    m_dataIntegral      (_dataIntegral),   
    m_fitValues(_templates.size(),0.),
    m_fitErrorsUp(_templates.size(),0.),
    m_fitErrorsDown(_templates.size(),0.),
    m_fitErrorsStatus(_templates.size(),0.),
    m_doPanicPrint(false),
    m_verbosity(2),
    m_resultCanvas(3)
  {
    //create deep copies!
    for (int i = 0; i < _templates.size(); ++i)
    {
      std::string name = _templates.at(i)->GetName();
      name += "_pseudo";
      m_templateTH1s[i] = dynamic_cast<TH1*>(_templates.at(i)->Clone(name.c_str()));
      m_templateTH1s[i]->SetDirectory(0);
    }

    
    
    setupResults(_templates.size());
  };

  void createScaledData(TH1* _data=0,
                        const double& _integral=1.){

    if(!_data){
      std::cerr << __FILE__ << ":"<< __LINE__ <<"\t data histo pointer nil\n";
      return ;}

    

    _data->Reset("MICE");
    _data->ResetStats();
    _data->FillRandom(m_total,_integral);
    
    return ;
  }

   // ~BaseStudy(){
   //   delete m_input;
     
   // }

  //setter
  void setFitEngine( const std::string& _engine){m_fitEngine = _engine;};
  void setFitMode( const std::string& _mode){m_fitMode = _mode;};
  void setProtoCreator(const ProtoCreator& _creator){m_creator = _creator;};
  void setFitterConfigFile(const std::string& _file){m_fitConfigFile = _file;};
  void setInput(InputT* _input=0){
    if(m_input){
      delete m_input;
      m_input = 0;
    }
      
    m_input = _input;
  };
  void setPanicPrint(const bool& _value=false){m_doPanicPrint = _value;};
  void setVerbosity(const int& _value=3){m_verbosity = _value;};
  void setBaseName(const std::string& _value){m_baseName = _value;};

  //getters
  void getResultsOfParameter(const int& _idx,std::vector<TH1*>& _results){

    _results.clear();
    
    if(!(_idx<m_templateTH1s.size()))
      return;

    _results.resize(3);
    
    try{
      _results[0] = &(m_means.at(_idx));
    }
    catch(std::exception& exc){
      std::cerr << __FILE__ <<":"<< __LINE__ <<"\t unable to return m_means item at "<< _idx <<" due to \n\t"<< exc.what()<<std::endl;
      _results[0] = 0;
    }

    try{
      _results[1] = &(m_sigmas.at(_idx));
    }
    catch(std::exception& exc){
      std::cerr << __FILE__ <<":"<< __LINE__ <<"\t unable to return m_sigmas item at "
                << _idx <<" due to \n\t"<< exc.what()<<std::endl;
      _results[1] = 0;
    }

    
    try{
      _results[2] = &(m_pulls.at(_idx));
    }
    catch(std::exception& exc){
      std::cerr << __FILE__ <<":"<< __LINE__ <<"\t unable to return m_pulls item at "<< _idx<<" due to \n\t"<< exc.what()<<std::endl;
      _results[2] = 0;
    }

    return;
  };
  TH1D* getMaxLLHDistribution(){return m_maxLLH;};
  //utilities

  void printResults(){
  
    std::cout << "-- meas --\n";
    std::vector<TH1D>::const_iterator rItr = m_means.begin()    ;
    std::vector<TH1D>::const_iterator rEnd = m_means.end()      ;
    std::string rootFileName = m_baseName;
    rootFileName += "_MeansSigmasPullsMaxLLH.root";
    TFile aNewFile(rootFileName.c_str(),"RECREATE");

    m_maxLLH->SetDirectory(aNewFile.GetDirectory("/"));
    m_maxLLH->Write();

    for (; rItr!=rEnd; ++rItr)
    {
      std::cout << rItr->GetName() << "("<< rItr->GetEntries()<<") "
                <<"mean: " << rItr->GetMean()
                <<", rms: " << rItr->GetRMS()
                <<", xmin/xmax: " << rItr->GetXaxis()->GetXmin() << "/" <<  rItr->GetXaxis()->GetXmax() 
                <<", u/o: " << rItr->GetBinContent(0) << "/" <<   rItr->GetBinContent(rItr->GetNbinsX()+1)
                << std::endl;
      rItr->Write();
    }

    std::cout << "-- sigmas --\n";
    rItr = m_sigmas.begin()    ;
    rEnd = m_sigmas.end()      ;
    for (; rItr!=rEnd; ++rItr)
    {
        std::cout << rItr->GetName() << "("<< rItr->GetEntries()<<") "
                  <<"mean: " << rItr->GetMean()
                  <<", rms: " << rItr->GetRMS()
                  <<", xmin/xmax: " << rItr->GetXaxis()->GetXmin() << "/" <<  rItr->GetXaxis()->GetXmax() 
                  <<", u/o: " << rItr->GetBinContent(0) << "/" <<   rItr->GetBinContent(rItr->GetNbinsX()+1)
                  << std::endl;
        rItr->Write();
    }

    std::cout << "-- pulls --\n";
    rItr = m_pulls.begin()    ;
    rEnd = m_pulls.end()      ;
    for (; rItr!=rEnd; ++rItr)
    {
      std::cout << rItr->GetName() << "("<< rItr->GetEntries()<<") "
                <<"mean: " << rItr->GetMean()
                <<", rms: " << rItr->GetRMS()
                <<", xmin/xmax: " << rItr->GetXaxis()->GetXmin() << "/" <<  rItr->GetXaxis()->GetXmax()
                <<", u/o: " << rItr->GetBinContent(0) << "/" <<   rItr->GetBinContent(rItr->GetNbinsX()+1)
                << std::endl;
      rItr->Write();

    }

    std::cout << "-- Migrad pulls --\n";
    rItr = m_MigradPulls.begin()    ;
    rEnd = m_MigradPulls.end()      ;
    for (; rItr!=rEnd; ++rItr)
    {
      std::cout << rItr->GetName() << "("<< rItr->GetEntries()<<") "
                <<"mean: " << rItr->GetMean()
                <<", rms: " << rItr->GetRMS()
                <<", xmin/xmax: " << rItr->GetXaxis()->GetXmin() << "/" <<  rItr->GetXaxis()->GetXmax() << std::endl;
      rItr->Write();

    }


    aNewFile.Write();
    aNewFile.Close();

  };
  
  

  void experiment(){
    
    // if(!m_input){
    //         std::cerr << __FILE__ << ":"<< __LINE__ <<"\t input data object pointer nil\n";
    //   return;}

    setupTotalTemplates();

    FitterResults::HistoResult* histoResult = new FitterResults::HistoResult();
    FitterResults::LLHResult* llhResult = new FitterResults::LLHResult();
    std::ostringstream name;

    setupInput(m_total,m_templateTH1s);
    if(m_verbosity<3){
      std::cout << "\nproto function to fill the data from\n";
      m_total->Print("all");
    }
      
    

    TH1* m_data=0;
    prepareData(m_data);

    int status = 0;
    int numParameters = m_templateTH1s.size();
    int nNon0Status = 0;
    int nMinosFailed = 0;

    double totalData = 1;
    double totalSmearedData = 1;
    double expectationScale =1.;

    double expError=0.;
    double expValue=0.;
    double fitError=0.;
    double fitValue=0.;
    double pullSigma=0.;
    
    std::vector<double> pullValues(numParameters,0.);
    std::vector<double> MigradPullValues(numParameters,0.);

    std::vector<double> fitSymmErrors(numParameters,0.);
    m_fitValues.clear();m_fitValues.reserve(numParameters);
    fitSymmErrors.clear();fitSymmErrors.reserve(numParameters);
    for (int i = 0; i < (m_iterations); ++i)
    {
      //flush the name
      name.str("");
      name << m_baseName << i;
      

      if(i % 500 == 0)
        std::cout << " iteration " << i << "/" << m_iterations << std::endl;

      //scale b content and
      // add all MC histos according to the just fitted fractions to give pseudo data
      totalData = TMath::Abs(m_dataIntegral);
                  
      if(m_dataIntegral<0)
        createScaledData(m_data,totalData);
      else{
        totalSmearedData =  m_TRand3.Poisson(totalData);
        createScaledData(m_data,totalSmearedData);
        expectationScale = totalSmearedData/totalData;
      }

      if(m_verbosity<3){
        std::cout << "\nsampled data\n";
        m_data->Print("all");
      }


      //feed m_input with pseudo data
      setupData(m_data);

      //init the fitter
      core::FitCore<FunctionT,InputT,FitterResults::AbsResult> aFitter(m_input);
      aFitter.configureFromFile(m_fitConfigFile);
      aFitter.configureKeyWithValue("Engine",m_fitEngine);
      aFitter.configureKeyWithValue("Mode",m_fitMode);
      aFitter.setupMachinery();

      //run the fitter on data from the input file
      if(m_verbosity>2)
        status = aFitter.fit(false);
      else
        status = aFitter.fit(true);
      
      

      if(status!=0){
        nNon0Status++;
        std::cout << "fitter status:\t"<< status << std::endl;
        if(m_doPanicPrint){
          name << "_failed";
          preparePlots(name.str(),histoResult,llhResult);
          
            
          if(m_verbosity<3){
            aFitter.printTo(histoResult);
            aFitter.printTo(llhResult);
          }
          
        }
      }
      else{
        name << "_success";
        preparePlots(name.str(),histoResult,llhResult);
        if(i % 5000 == 0 && m_verbosity<6){
          aFitter.printTo(histoResult);
          aFitter.printTo(llhResult);
        }
      }

      //if the fit converged, collect the results
      if(!(status!=0)){
        //collect the errors
        aFitter.getMinosErrorSet(m_fitErrorsStatus,m_fitErrorsDown,m_fitErrorsUp);

        std::copy(aFitter.getFitResults()->begin()      ,
                  aFitter.getFitResults()->end()        ,
                  m_fitValues.begin());

        std::copy(aFitter.getFitSymmetricErrors()->begin()      ,
                  aFitter.getFitSymmetricErrors()->end()        ,
                  fitSymmErrors.begin());

        //collect the results
        m_maxLLH->Fill(aFitter.getMinimizer()->MinValue());
        double pullSigma = 0.;
        for (int i = 0; i < numParameters; ++i)
        {
         
          m_means[i].Fill(m_fitValues[i]);

          expError = m_expectedErrors[i];
          expValue = m_expectedValues[i];

          bool MinosSuccess = false;
          try{
            MinosSuccess = TMath::Abs(m_fitErrorsStatus.at(i))<10;
          }
          catch(std::exception& exc){
            MinosSuccess = true;
          }

          if(MinosSuccess){
            m_sigmas[i].Fill(TMath::Abs(std::max(TMath::Abs(m_fitErrorsDown[i]),m_fitErrorsUp[i])));
            
          if(m_fitValues[i]>(expValue))
            pullSigma  = TMath::Abs(m_fitErrorsDown[i]);
          else
            pullSigma = TMath::Abs(m_fitErrorsUp[i]);

          }
          else{
            nMinosFailed++;
            m_sigmas[i].Fill(fitSymmErrors[i]);
            pullSigma = fitSymmErrors[i];
          }


          pullValues[i] = (m_fitValues[i] - (expValue))/(pullSigma);
          MigradPullValues[i] = (m_fitValues[i] - (m_expectedValues[i]))/(fitError);

          // std::cout << "fit results: "<< totalSmearedData <<" (" <<totalData <<")\n"
          //           << i << ": (fit)\t" << m_fitValues[i] << " +/- " << pullSigma << " (Migrad: "<< aFitter.getMinimizer()->Errors()[i] <<")\n"
          //           << "(expect)\t"<< expectationScale*m_expectedValues[i] << " ["<<m_expectedValues[i] <<"] +/- " << expectationScale*m_expectedErrors[i] << "\n";
        }

        for (int i = 0; i < pullValues.size(); ++i)
        {
          m_pulls[i].Fill(pullValues[i]);
          m_MigradPulls[i].Fill(MigradPullValues[i]);
        }
      }

      //clean-up data
      m_data->Reset("MICE");
      m_data->ResetStats(); 
      
      if(i<1)
        treatResultsFromMinimizer(aFitter.getParameterNames());
    }
    double irregulars = (nNon0Status/double(m_iterations))*100;
    std::cout << nNon0Status<< "/" <<m_iterations << " = ("<< std::setprecision(2) <<irregulars <<" %) were irregular!\n";
    std::cout << nMinosFailed<< "/" <<m_iterations*m_templateTH1s.size() << " = ("<< std::setprecision(2) <<irregulars <<" %) where Minos failed!\n";

    delete histoResult;histoResult=0;
    delete llhResult;llhResult=0;
   
  };
  
};

#endif
