#include "TH1Bundle.h"

// Constructors/Destructors
//  

TH1Bundle::TH1Bundle ( ) {
initAttributes();
}

TH1Bundle::~TH1Bundle ( ) { }

//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  

void TH1Bundle::initAttributes ( ) {
  m_dataPlotName = "";
  m_dataFile = 0;
  m_mcFileNames = "";
  m_mcPlotNames = "";
}

