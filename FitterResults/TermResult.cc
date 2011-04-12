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

  double up=0.;
  double down=0.;
  std::string mode = getMinimizer()->Options().MinimizerAlgorithm();
  
  if(!(mode.find("MINOS")!=std::string::npos 
       || mode.find("Minos")!=std::string::npos) ){
    std::cout << getMinimizer()->VariableName(0) << ":\t" << xs[0]*(getFunction()->getTemplate(0)->getSum()) 
              << "\t+/-\t" << xErrors[0]*(getFunction()->getTemplate(0)->getSum()) << std::endl;

    std::cout << getMinimizer()->VariableName(1) << ":\t" << xs[1]*(getFunction()->getTemplate(1)->getSum()) 
              << "\t+/-\t" << xErrors[1]*(getFunction()->getTemplate(1)->getSum()) << std::endl;
    
    std::cout << getMinimizer()->VariableName(2) << ":\t" << xs[2]*(getFunction()->getTemplate(2)->getSum()) 
              << "\t+/-\t" << xErrors[2]*(getFunction()->getTemplate(2)->getSum()) << std::endl;}
    else{
      std::cout << ">> minimized using "<< mode <<"\n";
      std::cout << getMinimizer()->VariableName(0) << ":\t" << xs[0]*(getFunction()->getTemplate(0)->getSum()) 
                << "\t(+ "<< up*(getFunction()->getTemplate(0)->getSum()) <<")\t(-"<< down*(getFunction()->getTemplate(0)->getSum()) <<")\n";
      getMinimizer()->GetMinosError(1,down,up);
      std::cout << getMinimizer()->VariableName(1) << ":\t" << xs[1]*(getFunction()->getTemplate(1)->getSum()) 
                << "\t(+ "<< up*(getFunction()->getTemplate(1)->getSum()) 
                << ")\t(-"<< down*(getFunction()->getTemplate(1)->getSum()) <<")\n";
    
      getMinimizer()->GetMinosError(2,down,up);
      std::cout << getMinimizer()->VariableName(2) << ":\t" << xs[2]*(getFunction()->getTemplate(2)->getSum()) 
                << "\t(+ "<< up*(getFunction()->getTemplate(2)->getSum()) 
                <<")\t(-"<< down*(getFunction()->getTemplate(2)->getSum()) <<")\n";
    }

  
}
