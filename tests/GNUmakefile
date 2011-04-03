PACKAGE=tests
#link against boost unit test framework, $(BOOSTLIB) used for backward compatibility
#this requires every test fixture to have '#define BOOST_TEST_DYN_LINK' to be invoked before any boost header is loaded
CXXFLAGS=-I$(SRC) 
BINLINKFLAGS =-L$(LIBDIR) -L$(BOOSTLIB) -lboost_unit_test_framework
include $(SRC)/GNUmakefiles/GNUmakefile
