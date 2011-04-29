#define LLHRESULT_CC
#include <sstream>

#include "FitterResults/LLHResult.hh"
#include "functions/AbsFittingFunction.hh"
#include "TGraph.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TAxis.h"
#include "TFile.h"

void FitterResults::LLHResult::print(){

  if(!getMinimizer()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no minimizer given!\n";
    return;
  }

  if(!getFunction()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no function given!\n";
    return;
  }


  TFile newFile(m_filename.c_str(),"RECREATE");
  unsigned int numFitVariables = getMinimizer()->NDim();
  // std::cout << __FILE__ << ":" << __LINE__ << "\t dimensions received "<< numFitVariables << std::endl;
  std::vector<TGraph*> results(numFitVariables);

  std::ostringstream name;
  for (int i = 0; i < numFitVariables; ++i)
  {
    name.str("");
    name << "parameter " << i;
    results[i] = new TGraph(14);
    results[i]->GetXaxis()->SetTitle(name.str().c_str());
    results[i]->GetYaxis()->SetTitle(" - log(L) / a.u.");
    name << " -log(L)";
    results[i]->SetName(name.str().c_str());
    //results[i]->SetDirectory(newFile.GetDirectory("/"));
  }

  const double *xs = getMinimizer()->X();
  double input[numFitVariables];

  const double *xErrors = getMinimizer()->Errors();
  double LLHatPoint= 0.;
  std::string mode = getMinimizer()->Options().MinimizerAlgorithm();

  double errShift = 0.;
  int    pointIdx = 0;

  for (int i = -6; i < 8; ++i,pointIdx++)
  {
    errShift = i/2.;
    for (int j = 0; j < numFitVariables; ++j)
    {
      std::copy(xs,xs+numFitVariables,input);
      input[j] = xs[j]+(errShift*xErrors[j]);
      LLHatPoint = getFunction()->operator()(input);
      if(TMath::IsNaN(LLHatPoint))
        results[j]->SetPoint(i+6, input[j], 0.);
      else
        results[j]->SetPoint(i+6, input[j], LLHatPoint);
      
    }
  }
      
  printTGraphVector(results);
  newFile.Write();
  newFile.Close();
}

void FitterResults::LLHResult::printTGraphVector(const std::vector<TGraph*>& _results){


  std::string name;
  if(m_filename.find(".root")!=std::string::npos)
   name = this->m_filename.substr(0,m_filename.find(".root"));

  TCanvas aCanvas(name.c_str(),"",_results.size()*600,500);
  aCanvas.Clear();
  aCanvas.Draw();
  aCanvas.Divide(_results.size(),1);
  for (int i = 0; i < (_results.size()); ++i)
  {
    aCanvas.cd(i+1);
    _results[i]->Draw("AP+");

  }
  aCanvas.Update();
  aCanvas.Print(".eps");

}
