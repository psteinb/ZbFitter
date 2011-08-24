#include "FileResult.hh"
#include <sstream>

#include "TH2D.h"
#include "TGraphAsymmErrors.h"
#include "TMath.h"
#include "TAxis.h"



// void FitterResults::FileResult::setDirectoryOfContentTo(TFile* _file){

//   if(_file && !(_file->IsZombie())){
    
//     for (int i = 0; i < fileContent.size(); ++i)
//     {
//       fileContent[i]->SetDirectory(_file->GetDirectory("/"));
//     }
      
//   }
//   else
//     std::cerr << __FILE__ << ":" << __LINE__ << "\t file does not exist\n";
// }

void FitterResults::FileResult::addCovarianceFromMinimizer(){
  TH2D* covariances = new TH2D("covariances","",
                               getNumberOfParameters(),0.,(double)getNumberOfParameters(),
                               getNumberOfParameters(),0.,(double)getNumberOfParameters());

  for (int xIndex = 0;  xIndex < getNumberOfParameters(); xIndex++)
  {
    for (int yIndex = 0 ; yIndex < getNumberOfParameters(); yIndex++)
    {
      covariances->Fill(xIndex,yIndex,getMinimizer()->CovMatrix(xIndex,yIndex));
    }
  }

  addObjectToSave(covariances);
}

void FitterResults::FileResult::addCorrelationFromMinimizer(){

  TH2D* correlations = new TH2D("correlations","",
                                getNumberOfParameters(),0.,(double)getNumberOfParameters(),
                                getNumberOfParameters(),0.,(double)getNumberOfParameters());
  
  for (int xIndex = 0;  xIndex < getNumberOfParameters(); xIndex++)
  {
    for (int yIndex = 0 ; yIndex < getNumberOfParameters(); yIndex++)
    {
      correlations->Fill(xIndex,yIndex,getMinimizer()->Correlation(xIndex,yIndex));
    }
  }

  addObjectToSave(correlations);

}

void FitterResults::FileResult::print(){

  
  if(!getMinimizer()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no minimizer given!\n";
    return;
  }



  if(!getFunction()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no function given!\n";
    return;
  }

  // setupFiles();

  TFile* newFile=0;
  std::string name = m_filename;

  if(!(m_filename.find(".root")!=std::string::npos))
    name += ".root";
  newFile = new TFile(name.c_str(),"RECREATE");
  
  
  TGraphAsymmErrors* tgraph = new TGraphAsymmErrors(getNumberOfParameters());
  tgraph->SetName("fitResults");
  int minosStatus = 0;
  double minosUp =0.;
  double minosDown =0.;
  std::string currentLabel;
  for (int i = 0; i < getNumberOfParameters(); ++i)
  {
    currentLabel = getParameterNames()->at(i);
    tgraph->SetPoint(i,double(i),getResults()->at(i));
    tgraph->GetXaxis()->SetBinLabel(i+1,currentLabel.c_str());
    getMinosResultsForIndex(i,minosStatus,minosUp,minosDown);
    tgraph->SetPointError(i,0.,0.,TMath::Abs(minosDown),TMath::Abs(minosUp));
  }
  fileContent.push_back(tgraph);

  addCovarianceFromMinimizer();
  
  addCorrelationFromMinimizer();

  for (int index = 0; index < fileContent.size(); index++){
    fileContent[index]->Write(fileContent[index]->GetName());
  }
  //newFile->Write();
  newFile->Close();
}


