#define LLHRESULT_CC
#include <sstream>

#include "FitterResults/LLHResult.hh"
#include "functions/AbsFittingFunction.hh"
#include "TGraph.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TAxis.h"
#include "TFile.h"
#include "TLine.h"

void FitterResults::LLHResult::print(){

  if(!getMinimizer()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no minimizer given!\n";
    return;
  }

  if(!getFunction()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no function given!\n";
    return;
  }

  std::string fname = m_filename;
  if(!(m_filename.find(".root")!=std::string::npos))
    fname += ".root";

  TFile newFile(fname.c_str(),"RECREATE");
  unsigned int numFitVariables = getNumberOfParameters() - getFunction()->getNFixedParameters();
  // std::cout << __FILE__ << ":" << __LINE__ << "\t dimensions received "<< numFitVariables << std::endl;


  std::vector<TGraph*> results(numFitVariables);
  const double *xs = getMinimizer()->X();
  double input[numFitVariables];
  std::ostringstream GraphTitle;
  std::string GraphName;
  for (int i = 0; i < numFitVariables; ++i)
  {
    GraphName = "LLH_";
    GraphName += getMinimizer()->VariableName(i);
    GraphTitle.str(GraphName);
    GraphTitle << ";" << getMinimizer()->VariableName(i) 
               << ";" << " -log(L) / a.u.";

    results[i] = new TGraph(14);
    results[i]->SetTitle(GraphTitle.str().c_str());
    results[i]->SetName(GraphName.c_str());
  }

  

  const double *xErrors = getMinimizer()->Errors();
  double LLHatPoint= 0.;
  std::string mode = getMinimizer()->Options().MinimizerAlgorithm();

  double errShift = 0.;
  int    pointIdx = 0;
  std::cout << std::endl;
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

      #ifdef __DEBUG__
      if(TMath::Abs(errShift)<2 && j<1)
        std::cout << " ["<<j<<"] "<< errShift <<"\t LLH at "<<input[j]<<" is " << LLHatPoint << " ("<< xErrors[j] <<")\n";
      #endif
      
    }
  }
      
  printTGraphVector(results);
  //  newFile.Write();
  newFile.Close();
  
  
}

void FitterResults::LLHResult::printTGraphVector(const std::vector<TGraph*>& _results){


  std::string name;
  if(m_filename.find(".root")!=std::string::npos)
   name = this->m_filename.substr(0,m_filename.find(".root"));
  else
    name = m_filename;

  TCanvas aCanvas(name.c_str(),"",_results.size()*600,500);
  aCanvas.Clear();
  aCanvas.Draw();
  aCanvas.Divide(_results.size(),1);
  TLine Half;
  for (int i = 0; i < (_results.size()); ++i)
  {
    aCanvas.cd(i+1);
    _results[i]->Draw("AP+");
    gPad->SetGridy(true);
    gPad->SetGridx(true);
    _results[i]->Write();
    // aCanvas.Update();
    // Half.DrawLine(gPad->GetUxmin(),gPad->YtoPad(_results[i]->GetMinimum()+.5),
    //               gPad->GetUxmax(),gPad->YtoPad(_results[i]->GetMinimum()+.5));
    
  }
  aCanvas.Update();
  aCanvas.Print(".eps");

}
