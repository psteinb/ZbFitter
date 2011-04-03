#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE AClassTest
#include "aClass.hh"
#include <boost/test/unit_test.hpp>
class Fixture
{
public:
  
  Fixture(): m_object( ) { BOOST_TEST_MESSAGE( "setup fixture" ); };
  virtual ~Fixture()  { BOOST_TEST_MESSAGE( "teardown fixture" ); };
  aClass m_object;

};

BOOST_FIXTURE_TEST_SUITE( test_suite1, Fixture )


BOOST_AUTO_TEST_CASE( test_5 )
{
  BOOST_CHECK( m_object.checkDouble(5.));

}

BOOST_AUTO_TEST_CASE( test_1 )
{
  BOOST_CHECK( !m_object.checkDouble(1.5) );

}

BOOST_AUTO_TEST_CASE( testInt_5 )
{
  BOOST_CHECK( m_object.checkInt(5.));

}

BOOST_AUTO_TEST_CASE( testInt_100 )
{
  BOOST_CHECK( m_object.checkInt(100) );

}

BOOST_AUTO_TEST_SUITE_END()
