PACKAGE=tests
#link against boost unit test framework, $(BOOSTLIB) used for backward compatibility
#this requires every test fixture to have '#define BOOST_TEST_DYN_LINK' to be invoked before any boost header is loaded
CXXFLAGS=-I$(SRC) -I$(BOOST_INC)
BINLINKFLAGS =-L$(LIBDIR) -L$(BOOST_LIB) -lboost_unit_test_framework -lTFitterInputs -lTfunctions
include $(SRC)/GNUmakefiles/GNUmakefile
