#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FitterDataTest
#include "FitterInputs/FitterData.hh"
#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include <vector>
#include <iostream>


class ObjFixture
{
  

public:
  
  ObjFixture(): m_fData( ), data(), weights() { 
    BOOST_TEST_MESSAGE( "setup fixture" ); 
    data.reserve(3);
    data.push_back(16);
    data.push_back(25);
    data.push_back(36);
    weights.reserve(3);
    weights.push_back(4);
    weights.push_back(5);
    weights.push_back(6);
  };

  virtual ~ObjFixture()  { BOOST_TEST_MESSAGE( "teardown fixture" ); };

  FitterInputs::FitterData m_fData;
  std::vector<double> data;
  std::vector<double> weights;
};

///define name and fixture object for suite
BOOST_FIXTURE_TEST_SUITE( FData, ObjFixture )

/////////////////////////////////////////
/// checking the data
/////////////////////////////////////////


BOOST_AUTO_TEST_CASE( emptyObject )
{
  BOOST_CHECK(int(m_fData.getType()) == 0);
}

BOOST_AUTO_TEST_CASE( emptyObjectContent )
{
  BOOST_CHECK(m_fData.getContent()->empty());
  BOOST_CHECK(m_fData.getWeights()->empty());
}

BOOST_AUTO_TEST_CASE( emptyObjectSetType )
{
  m_fData.setType(1);
  BOOST_CHECK(int(m_fData.getType()) != 0);
}

BOOST_AUTO_TEST_CASE( emptyObjectSetContent )
{
  m_fData.setContent(data);
  
  BOOST_CHECK(m_fData.getContent()->size()!=0);
}

BOOST_AUTO_TEST_CASE( emptyObjectSetWeights )
{
  m_fData.setWeights(weights);
  
  BOOST_CHECK(m_fData.getWeights()->size()!=0);
}

BOOST_AUTO_TEST_CASE( emptyObjectSetContentAndWeights )
{
  m_fData.setContentAndWeights(data,weights);

  BOOST_CHECK(m_fData.getWeights()->size()!=0 && m_fData.getContent()->size()!=0);
}

BOOST_AUTO_TEST_CASE( emptyObjectExactContent )
{
  m_fData.setContentAndWeights(data,weights);

  BOOST_CHECK(m_fData.getContent()->at(0)!=0 && m_fData.getContent()->at(0)==16);
  BOOST_CHECK(m_fData.getWeights()->at(0)!=0 && m_fData.getWeights()->at(0)==4);
}

BOOST_AUTO_TEST_CASE( emptyObjectRetrieve )
{
  m_fData.setContentAndWeights(data,weights);
  std::vector<double> nData(data.size());
  std::vector<double> nWeights(weights.size());
  m_fData.copyContentAndWeightsTo(nData,nWeights);
  BOOST_CHECK(nData.size()!=0 );
  BOOST_CHECK(nWeights.size()!=0 );
}

BOOST_AUTO_TEST_CASE( emptyObjectClear )
{
  m_fData.setContentAndWeights(data,weights);
  m_fData.clear();
  BOOST_CHECK(m_fData.getContent()->empty()!=0);
  BOOST_CHECK(m_fData.getWeights()->empty()!=0);
}


BOOST_AUTO_TEST_SUITE_END()
