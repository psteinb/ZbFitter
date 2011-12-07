PACKAGE = FitRunner

 

ifdef TBB_LIB
	CXXFLAGS=-I$(SRC) -I$(HOME)/bin/atlasstyle-trunk -I$(TBB_INC)
	BINLINKFLAGS = -L$(LIBDIR) -I$(TBB_INC) -L$(TBB_LIB) -lTcore -lTfunctions -lTFitterInputs -lTFitterResults -lMinuit2 -ltbb  #_debug 
else
	CXXFLAGS=-I$(SRC) -I$(HOME)/bin/atlasstyle-trunk 
	BINLINKFLAGS = -L$(LIBDIR) -lTcore -lTfunctions -lTFitterInputs -lTFitterResults -lMinuit2 -ltbb  #_debug 
endif

include $(SRC)/GNUmakefiles/GNUmakefile
