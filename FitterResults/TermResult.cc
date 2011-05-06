#include "TermResult.hh"
#include "functions/AbsFittingFunction.hh"

void FitterResults::TermResult::print(){

  if(!getMinimizer()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no minimizer given!\n";
    return;
  }

  if(!getFunction()){
    std::cerr << __FILE__ <<":"<< __LINE__ <<"\t no function given!\n";
    return;
  }

  const double *xs = getMinimizer()->X();
  const double *xErrors = getMinimizer()->Errors();
  int nParameters = getMinimizer()->NDim();

  double up=0.;
  double down=0.;
  std::string mode = getMinimizer()->Options().MinimizerAlgorithm();

  std::cout << ">> minimized using "<< mode <<"\n";

  if(!(mode.find("MINOS")!=std::string::npos 
       || mode.find("Minos")!=std::string::npos) ){
    for (int i = 0; i < nParameters; ++i)
    {
      std::cout << getMinimizer()->VariableName(i) << ":\t" 
                << xs[i]*(getFunction()->getTemplate(i)->getSum()) 
                << "\t+/-\t" << xErrors[i]*(getFunction()->getTemplate(i)->getSum()) << std::endl;
    }
    }
    else{
      for (int i = 0; i < nParameters; ++i)
      {
        getMinimizer()->GetMinosError(i,down,up);
        std::cout << getMinimizer()->VariableName(i) << ":\t" 
                  << xs[0]*(getFunction()->getTemplate(i)->getSum()) 
                  << "\t(+ "<< up*(getFunction()->getTemplate(i)->getSum()) 
                  <<")\t(-"<< down*(getFunction()->getTemplate(i)->getSum()) <<")\n";
      }
      
    }

  
}
