#include "Chi2Result.hh"
#include "functions/AbsFittingFunction.hh"
#include "TH1D.h"
#include "TFile.h"
#include "TMath.h"
#include "TAxis.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TPaveText.h"
#include "TLegend.h"

void FitterResults::Chi2Result::print(){

  
  if(!getMinimizer()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no minimizer given!\n";
    return;
  }



  if(!getFunction()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no function given!\n";
    return;
  }

  TFile* newFile=0;
  newFile = new TFile(m_filename.c_str(),"RECREATE");

  THStack newStack(appendToNameString<std::string>("_stack").c_str(),"");

  TH1D* fitterData = (TH1D*)getFunction()->getData()->getHisto()->Clone(appendToNameString<std::string>("_data").c_str());
  
  TH1D* fitterT0 = (TH1D*)getFunction()->getTemplate(0)->getHisto()->Clone(appendToNameString<int>(0).c_str());
  TH1D* fitterT1 = (TH1D*)getFunction()->getTemplate(1)->getHisto()->Clone(appendToNameString<int>(1).c_str());
  TH1D* fitterT2 = (TH1D*)getFunction()->getTemplate(2)->getHisto()->Clone(appendToNameString<int>(2).c_str());
  
  const double *xs = getMinimizer()->X();
  const double *xErrors = getMinimizer()->Errors();
  
  double mcBFrac = fitterT0->Integral();
  double mcCFrac = fitterT1->Integral();
  double mcLFrac = fitterT2->Integral();
  double totData = fitterData->Integral();

  fitterT0->Scale(xs[0]);fitterT0->SetFillColor(kRed);
  fitterT1->Scale(xs[1]);fitterT1->SetFillColor(kViolet);
  fitterT2->Scale(xs[2]);fitterT2->SetFillColor(kAzure); 

  //real work starts here [REFACTOR!]
  //goal: calculate a chi2 over the bins fitted
  //as a first approach, I add up errors
  double chi2 = 0;
  double data = 0;
  double exp = 0;
  double uncert = 0;
  double uncert0 = 0;
  double uncert1 = 0;
  double uncert2 = 0;
  for (int i = 1; i < fitterData->GetNbinsX(); ++i)
  {
    data = fitterData->GetBinContent(i);
    exp = (xs[0]*fitterT0->GetBinContent(i)) + (xs[1]*fitterT1->GetBinContent(i)) + (xs[2]*fitterT2->GetBinContent(i));
    uncert0 = xErrors[0]*fitterT0->GetBinContent(i);
    uncert1 = xErrors[1]*fitterT1->GetBinContent(i);
    uncert2 = xErrors[2]*fitterT2->GetBinContent(i);
    uncert = (uncert0*uncert0) + (uncert1*uncert1) + (uncert2*uncert2);
    
    if(uncert)
      chi2+= ((data-exp)*(data-exp))/(uncert);
  }
  
  int ndf = fitterData->GetNbinsX() - 3;
  
  std::cout << "chi2 of LLH fitted bins\n";
  std::cout << "chi2 = "<< chi2<<"\n";
  std::cout << "ndf = "<<ndf <<"\n";
  std::cout << "chi2/ndf = "<< chi2/ndf <<"\n";
}

