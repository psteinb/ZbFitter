#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FitterInputTest
#include "FitterInputs/TH1Bundle.hh"
#include "FitterInputs/FitterData.hh"
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
  std::vector<FitterInputs::FitterData> data;data.clear();
  m_bundle.getData(data);
  BOOST_CHECK( data.size()>0 );
}

BOOST_AUTO_TEST_CASE( fullLoadDataOnExactValues )
{
  m_bundle.loadData("./ToyToFit_NoWeight.root","data");
  std::vector<FitterInputs::FitterData> data;data.clear();
  m_bundle.getData(data);
  BOOST_CHECK( data.at(0).getContent()->at(0)==26.);
  BOOST_CHECK( data.at(0).getContent()->at(1)==6.);
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
  std::vector<FitterInputs::FitterData> temps;temps.clear();
  m_BUNDLE.getData(temps);
  BOOST_CHECK( temps.size()>0 );
}


// BOOST_AUTO_TEST_CASE( fullLoadTemplatesMCB )
// {
//   FitterInputs::TH1Bundle m_BUNDLE;
//   m_BUNDLE.loadTemplates("./ToyToFit_NoWeight.root","mcb,mcc,mcl");
//   std::vector<std::vector<double> > temps;temps.clear();
//   m_BUNDLE.getTemplates(temps);
//   BOOST_CHECK( temps.at(0).at(0)==5. && temps.at(0).at(1)==3. );
// }


// BOOST_AUTO_TEST_CASE( fullLoadTemplatesMCC )
// {
//   FitterInputs::TH1Bundle m_BUNDLE;
//   m_BUNDLE.loadTemplates("./ToyToFit_NoWeight.root","mcb,mcc,mcl");
//   std::vector<std::vector<double> > temps;temps.clear();
//   m_BUNDLE.getTemplates(temps);
//   BOOST_CHECK( temps.at(1).at(0)==9. && temps.at(1).at(1)==3. );
// }


// BOOST_AUTO_TEST_CASE( fullLoadTemplatesMCL )
// {
//   FitterInputs::TH1Bundle m_BUNDLE;
//   m_BUNDLE.loadTemplates("./ToyToFit_NoWeight.root","mcb,mcc,mcl");
//   std::vector<std::vector<double> > temps;temps.clear();
//   m_BUNDLE.getTemplates(temps);
//   BOOST_CHECK( temps.at(2).at(0)==12. && temps.at(2).at(1)==0. );
// }

BOOST_AUTO_TEST_CASE( fullLoadTemplatesWithWeightsSize )
{
  FitterInputs::TH1Bundle m_BUNDLE;
  m_BUNDLE.loadTemplates("./ToyToFit_NoWeight.root","mcb,mcc,mcl");
  std::vector<FitterInputs::FitterData> temps;temps.clear();
  m_BUNDLE.getData(temps);
  BOOST_CHECK( temps.size() );
  BOOST_CHECK( temps.at(0).getContent()->size() && temps.at(0).getWeights()->size());
}

BOOST_AUTO_TEST_CASE( fullLoadDeepCopy )
{

  FitterInputs::TH1Bundle m_BUNDLE;
  m_BUNDLE.loadTemplates("./ToyToFit_NoWeight.root","mcb,mcc,mcl");
  std::vector<TH1*> temps;temps.clear();
  m_BUNDLE.getTemplatesDeepCopy(temps);
  BOOST_CHECK( temps.at(0) );
  BOOST_CHECK( temps.at(0)->GetEntries() );
}

BOOST_AUTO_TEST_CASE( fullLoadDeepCopyClean )
{
  FitterInputs::TH1Bundle m_BUNDLE;
  m_BUNDLE.loadTemplates("./ToyToFit_NoWeight.root","mcb,mcc,mcl");
  std::vector<TH1*> temps;temps.clear();
  m_BUNDLE.getTemplatesDeepCopy(temps);
  int beforeClear = temps.at(0)->GetEntries();
  m_BUNDLE.clear();
  BOOST_CHECK( temps.at(0) );
  BOOST_CHECK( temps.at(0)->GetEntries() == beforeClear );
}

BOOST_AUTO_TEST_CASE( fullLoadDeepCopyCleanDestroy )
{
  FitterInputs::TH1Bundle* m_BUNDLE = new FitterInputs::TH1Bundle;
  m_BUNDLE->loadTemplates("./ToyToFit_NoWeight.root","mcb,mcc,mcl");
  std::vector<TH1*> temps;temps.clear();
  m_BUNDLE->getTemplatesDeepCopy(temps);
  int beforeClear = temps.at(0)->GetEntries();
  m_BUNDLE->clear();
  delete m_BUNDLE;
  m_BUNDLE = 0;
  BOOST_CHECK( temps.at(0) );
  BOOST_CHECK( temps.at(0)->GetEntries() == beforeClear );
}

BOOST_AUTO_TEST_SUITE_END()
