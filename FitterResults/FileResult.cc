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
  
  
  TH1* centralValues = new TH1D("centralValues","",getNumberOfParameters(),0,getNumberOfParameters());
  TH1* SymmErrors = new TH1D("SymmErrors","",getNumberOfParameters(),0,getNumberOfParameters());
  TH1* AsymmErrorsUp = new TH1D("AsymmErrorsUp","",getNumberOfParameters(),0,getNumberOfParameters());
  TH1* AsymmErrorsDown = new TH1D("AsymmErrorsDown","",getNumberOfParameters(),0,getNumberOfParameters());

  int minosStatus = 0;
  double minosUp =0.;
  double minosDown =0.;
  std::string currentLabel;
  for (int i = 0; i < getNumberOfParameters(); ++i)
  {
    currentLabel = getParameterNames()->at(i);
    centralValues->Fill(i,getResults()->at(i));
    SymmErrors->Fill(i,getSymmErrors()->at(i));
    getMinosResultsForIndex(i,minosStatus,minosUp,minosDown);
    AsymmErrorsUp->Fill(i,TMath::Abs(minosUp));
    AsymmErrorsDown->Fill(i,TMath::Abs(minosDown));
    
    centralValues->GetXaxis()->SetBinLabel(i+1,currentLabel.c_str());
    currentLabel = "sigma ";currentLabel+=getParameterNames()->at(i);
    SymmErrors->GetXaxis()->SetBinLabel(i+1,currentLabel.c_str());
    currentLabel = "sigma(Up) ";currentLabel+=getParameterNames()->at(i);
    AsymmErrorsUp->GetXaxis()->SetBinLabel(i+1,currentLabel.c_str());
    currentLabel = "sigma(Down) ";currentLabel+=getParameterNames()->at(i);
    AsymmErrorsDown->GetXaxis()->SetBinLabel(i+1,currentLabel.c_str());
  }
  fileContent.push_back(centralValues);
  fileContent.push_back(SymmErrors);
  fileContent.push_back(AsymmErrorsUp);
  fileContent.push_back(AsymmErrorsDown);

  addCovarianceFromMinimizer();
  
  addCorrelationFromMinimizer();

  for (int index = 0; index < fileContent.size(); index++){
    fileContent[index]->SetDirectory(newFile->GetDirectory("/"));
  }
  newFile->Write();
  newFile->Close();
}


