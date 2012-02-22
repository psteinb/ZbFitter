PACKAGE = FitRunner

 

ifdef TBB_LIB
	CXXFLAGS= -I$(SRC) -I$(HOME)/bin/atlasstyle -I$(TBB_INC)
	BINLINKFLAGS = -L$(LIBDIR) -L$(TBB_LIB) -lTcore -lTfunctions -lTFitterInputs -lTFitterResults -lMinuit2 -ltbb  #_debug 
else
	CXXFLAGS= -I$(SRC)  -I$(HOME)/bin/atlasstyle 
	BINLINKFLAGS = -L$(LIBDIR) -lTcore -lTfunctions -lTFitterInputs -lTFitterResults -lMinuit2 -ltbb  #_debug 
endif

include $(SRC)/GNUmakefiles/GNUmakefile
