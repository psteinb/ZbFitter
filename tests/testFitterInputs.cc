#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FitterInputTest
#include "FitterInputs/TH1Bundle.hh"
#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include <vector>


class Fixture
{
public:
  
  Fixture(): m_bundle( ) { BOOST_TEST_MESSAGE( "setup fixture" ); };
  virtual ~Fixture()  { BOOST_TEST_MESSAGE( "teardown fixture" ); };
  FitterInputs::TH1Bundle m_bundle;

};

BOOST_FIXTURE_TEST_SUITE( Inputs, Fixture )

/////////////////////////////////////////
/// checking the data
/////////////////////////////////////////


BOOST_AUTO_TEST_CASE( emptyLoadData )
{
  
  BOOST_CHECK_THROW(m_bundle.loadData(), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE( emptyHistoNameLoadData )
{
  BOOST_CHECK_THROW(m_bundle.loadData("./ToyToFit_NoWeight.root"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE( incorrectFileLoadData )
{
  
  BOOST_CHECK_THROW(m_bundle.loadData("./bla.root","data"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE( fullNameLoadData )
{
  BOOST_CHECK_NO_THROW(m_bundle.loadData("./ToyToFit_NoWeight.root","data"));
}

BOOST_AUTO_TEST_CASE( fullLoadDataOnValues )
{
  m_bundle.loadData("./ToyToFit_NoWeight.root","data");
  std::vector<double> data;data.clear();
  m_bundle.getData(data);
  BOOST_CHECK( data.size()>0 );
}

BOOST_AUTO_TEST_CASE( fullLoadDataOnExactValues )
{
  m_bundle.loadData("./ToyToFit_NoWeight.root","data");
  std::vector<double> data;data.clear();
  m_bundle.getData(data);
  BOOST_CHECK( data.at(0)==26. &&  data.at(1)==6.);
}
/////////////////////////////////////////
/// checking the templates
/////////////////////////////////////////


BOOST_AUTO_TEST_CASE( emptyLoadTemplates )
{
  BOOST_CHECK_THROW( m_bundle.loadTemplates(), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE( emptyHistoNameLoadTemplates )
{
  BOOST_CHECK_THROW( m_bundle.loadTemplates("./ToyToFit_NoWeight.root"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE( fullLoadTemplatesThrow )
{
  BOOST_CHECK_NO_THROW( m_bundle.loadTemplates("./ToyToFit_NoWeight.root","mcb,mcc,mcl"));
}

BOOST_AUTO_TEST_CASE( fullLoadTemplates )
{
  FitterInputs::TH1Bundle m_BUNDLE;
  m_BUNDLE.loadTemplates("./ToyToFit_NoWeight.root","mcb,mcc,mcl");
  std::vector<std::vector<double> > temps;temps.clear();
  m_BUNDLE.getTemplates(temps);
  BOOST_CHECK( temps.size()>0 );
}


BOOST_AUTO_TEST_CASE( fullLoadTemplatesMCB )
{
  FitterInputs::TH1Bundle m_BUNDLE;
  m_BUNDLE.loadTemplates("./ToyToFit_NoWeight.root","mcb,mcc,mcl");
  std::vector<std::vector<double> > temps;temps.clear();
  m_BUNDLE.getTemplates(temps);
  BOOST_CHECK( temps.at(0).at(0)==5. && temps.at(0).at(1)==3. );
}


BOOST_AUTO_TEST_CASE( fullLoadTemplatesMCC )
{
  FitterInputs::TH1Bundle m_BUNDLE;
  m_BUNDLE.loadTemplates("./ToyToFit_NoWeight.root","mcb,mcc,mcl");
  std::vector<std::vector<double> > temps;temps.clear();
  m_BUNDLE.getTemplates(temps);
  BOOST_CHECK( temps.at(1).at(0)==9. && temps.at(1).at(1)==3. );
}


BOOST_AUTO_TEST_CASE( fullLoadTemplatesMCL )
{
  FitterInputs::TH1Bundle m_BUNDLE;
  m_BUNDLE.loadTemplates("./ToyToFit_NoWeight.root","mcb,mcc,mcl");
  std::vector<std::vector<double> > temps;temps.clear();
  m_BUNDLE.getTemplates(temps);
  BOOST_CHECK( temps.at(2).at(0)==12. && temps.at(2).at(1)==0. );
}

BOOST_AUTO_TEST_CASE( fullLoadTemplatesWithWeightsSize )
{
  FitterInputs::TH1Bundle m_BUNDLE;
  m_BUNDLE.loadTemplates("./ToyToFit_NoWeight.root","mcb,mcc,mcl");
  std::vector<std::vector<double> > temps;temps.clear();
  std::vector<std::vector<double> > weights;weights.clear();
  m_BUNDLE.getTemplatesWithWeights(temps,weights);
  BOOST_CHECK( temps.size() );
  BOOST_CHECK( weights.size() );
}

BOOST_AUTO_TEST_CASE( fullLoadTemplatesWithWeightsEqualSize )
{
  FitterInputs::TH1Bundle m_BUNDLE;
  m_BUNDLE.loadTemplates("./ToyToFit_Weights.root","mcb,mcc,mcl");
  std::vector<std::vector<double> > temps;temps.clear();
  std::vector<std::vector<double> > weights;weights.clear();
  m_BUNDLE.getTemplatesWithWeights(temps,weights);
  BOOST_CHECK( temps.size() == weights.size());
  BOOST_CHECK( temps.at(0).size() == weights.at(0).size());
}

BOOST_AUTO_TEST_CASE( fullLoadTemplatesWithWeightsMCB )
{
  FitterInputs::TH1Bundle m_BUNDLE;
  m_BUNDLE.loadTemplates("./ToyToFit_Weights.root","mcb,mcc,mcl");
  std::vector<std::vector<double> > temps;temps.clear();
  std::vector<std::vector<double> > weights;weights.clear();
  m_BUNDLE.getTemplatesWithWeights(temps,weights);
  
  BOOST_CHECK( temps.at(0).at(0)==.75 && temps.at(0).at(1)==5. );
  BOOST_CHECK_MESSAGE( weights.at(0).at(0)==.75 && weights.at(0).at(1)==5., "weights were " << weights.at(0).at(0) << ", " << weights.at(0).at(1) );
}

BOOST_AUTO_TEST_SUITE_END()
