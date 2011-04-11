#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE functionsTestSimpleLLH
#include "FitterInputs/TH1Bundle.hh"
#include "functions/SimpleMaxLLH.hh"
#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include <vector>
#include <iostream>


class ObjFixture
{
  

public:
  
  ObjFixture(): m_input(),
                m_llh()
  { 
    BOOST_TEST_MESSAGE( "setting up inputs" ); 
    m_input.loadData("ToyToFit_Weights_Sys.root","data");
    m_input.loadTemplates("ToyToFit_Weights_Sys.root","mcb,mcc,mcl,mcb_Up,mcb_Down");
  };

  virtual ~ObjFixture()  { BOOST_TEST_MESSAGE( "teardown fixture" ); };

  FitterInputs::TH1Bundle m_input;
  functions::SimpleMaxLLH m_llh;
};

///define name and fixture object for suite
BOOST_FIXTURE_TEST_SUITE( simpleFunctions, ObjFixture )

/////////////////////////////////////////
/// checking the data
/////////////////////////////////////////


BOOST_AUTO_TEST_CASE( loadInput )
{
  std::vector<FitterInputs::FitterData> input;input.clear();
  m_input.getData(input);
  BOOST_CHECK(input.size()!=0);
}

BOOST_AUTO_TEST_CASE( loadInputUp )
{

  BOOST_CHECK(m_llh.up()==0.5);
}


BOOST_AUTO_TEST_CASE( loadInputToLLH )
{
  std::vector<FitterInputs::FitterData> input;input.clear();
  m_input.getData(input);
  m_llh.setupFromInput(&m_input);
  BOOST_CHECK(m_llh.up()!=0);
}

BOOST_AUTO_TEST_CASE( loadInputToLLHAndCalc )
{
  std::vector<FitterInputs::FitterData> input;input.clear();
  m_input.getData(input);
  m_llh.setupFromInput(&m_input);
  double parameters[] = {.3,.3,.3};
  BOOST_CHECK(m_llh(parameters)!=0);
  std::cout << "\t >> maxLLH: "<< m_llh(parameters) << std::endl;
}


BOOST_AUTO_TEST_CASE( loadInputToLLHAndCalc2 )
{
  std::vector<FitterInputs::FitterData> input;input.clear();
  m_input.getData(input);
  m_llh.setupFromInput(&m_input);
  double parameters[] = {1.,1.,1.};
  BOOST_CHECK(m_llh(parameters)!=0);
  std::cout << "\t >> maxLLH: "<< m_llh(parameters) << std::endl;
}


// BOOST_AUTO_TEST_CASE( emptyObjectContent )
// {
//   BOOST_CHECK(m_fData.getContent()->empty());
//   BOOST_CHECK(m_fData.getWeights()->empty());
// }

// BOOST_AUTO_TEST_CASE( emptyObjectSetType )
// {
//   m_fData.setType(1);
//   BOOST_CHECK(int(m_fData.getType()) != 0);
// }

// BOOST_AUTO_TEST_CASE( emptyObjectSetContent )
// {
//   m_fData.setContent(data);
  
//   BOOST_CHECK(m_fData.getContent()->size()!=0);
// }

// BOOST_AUTO_TEST_CASE( emptyObjectSetWeights )
// {
//   m_fData.setWeights(weights);
  
//   BOOST_CHECK(m_fData.getWeights()->size()!=0);
// }

// BOOST_AUTO_TEST_CASE( emptyObjectSetContentAndWeights )
// {
//   m_fData.setContentAndWeights(data,weights);

//   BOOST_CHECK(m_fData.getWeights()->size()!=0 && m_fData.getContent()->size()!=0);
// }

// BOOST_AUTO_TEST_CASE( emptyObjectExactContent )
// {
//   m_fData.setContentAndWeights(data,weights);

//   BOOST_CHECK(m_fData.getContent()->at(0)!=0 && m_fData.getContent()->at(0)==16);
//   BOOST_CHECK(m_fData.getWeights()->at(0)!=0 && m_fData.getWeights()->at(0)==4);
// }

// BOOST_AUTO_TEST_CASE( emptyObjectRetrieve )
// {
//   m_fData.setContentAndWeights(data,weights);
//   std::vector<double> nData(data.size());
//   std::vector<double> nWeights(weights.size());
//   m_fData.copyContentAndWeightsTo(nData,nWeights);
//   BOOST_CHECK(nData.size()!=0 );
//   BOOST_CHECK(nWeights.size()!=0 );
// }

// BOOST_AUTO_TEST_CASE( emptyObjectClear )
// {
//   m_fData.setContentAndWeights(data,weights);
//   m_fData.clear();
//   BOOST_CHECK(m_fData.getContent()->empty()!=0);
//   BOOST_CHECK(m_fData.getWeights()->empty()!=0);
// }


BOOST_AUTO_TEST_SUITE_END()
