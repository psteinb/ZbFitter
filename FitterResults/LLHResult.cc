#define LLHRESULT_CC
#include "FitterResults/LLHResult.hh"
#include "functions/AbsFittingFunction.hh"
#include "TGraph.h"
#include "TMath.h"
#include "TAxis.h"

void FitterResults::LLHResult::print(){

  if(!getMinimizer()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no minimizer given!\n";
    return;
  }

  if(!getFunction()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no function given!\n";
    return;
  }

  TGraph result(7);
  const double *xs = getMinimizer()->X();
  double input[] = {};

  const double *xErrors = getMinimizer()->Errors();
  double LLHatPoint= 0.;
  std::string mode = getMinimizer()->Options().MinimizerAlgorithm();

  for (int i = -3; i < 4; ++i)
  {
    input[0] = xs[0]+(i*xErrors[0]);
    LLHatPoint = getFunction()->operator()(input);
    if(TMath::IsNaN(LLHatPoint))
      result.SetPoint(i+4, input[0], 0.);
    else
      result.SetPoint(i+4, input[0], LLHatPoint);
  }
  
  result.SetTitle(";parameter;- log(L) / a.u. ");
  result.GetXaxis()->SetTitle(getMinimizer()->VariableName(0).c_str());
  result.SetName("fitResult");
  result.SaveAs(m_filename.c_str());
  
  
}
