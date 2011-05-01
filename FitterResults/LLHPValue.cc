#define LLHRESULT_CC
#include <sstream>

#include "FitterResults/LLHPValue.hh"
#include "functions/AbsFittingFunction.hh"
#include "TGraph.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TAxis.h"
#include "TFile.h"

void FitterResults::LLHPValue::print(){

  if(!getMinimizer()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no minimizer given!\n";
    return;
  }

  if(!getFunction()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no function given!\n";
    return;
  }

  if(!m_llh!=0.){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no m_llh value given!\n";
    return;
  }


  TFile newFile(m_filename.c_str(),"RECREATE");
  unsigned int numFitVariables = getMinimizer()->NDim();
  const double *xs = getMinimizer()->X();
  const double *xErrors = getMinimizer()->Errors();
  std::string mode = getMinimizer()->Options().MinimizerAlgorithm();
  //FIXME
  double = getMinimizer()->MinValue();

  //...

  newFile.Write();
  newFile.Close();
}

// void FitterResults::LLHPValue::printTGraphVector(const std::vector<TGraph*>& _results){


//   std::string name;
//   if(m_filename.find(".root")!=std::string::npos)
//    name = this->m_filename.substr(0,m_filename.find(".root"));

//   TCanvas aCanvas(name.c_str(),"",_results.size()*600,500);
//   aCanvas.Clear();
//   aCanvas.Draw();
//   aCanvas.Divide(_results.size(),1);
//   for (int i = 0; i < (_results.size()); ++i)
//   {
//     aCanvas.cd(i+1);
//     _results[i]->Draw("AP+");

//   }
//   aCanvas.Update();
//   aCanvas.Print(".eps");

// }
