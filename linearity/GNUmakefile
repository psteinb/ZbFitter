PACKAGE = linearity

CXXFLAGS=-I$(SRC) -I$(HOME)/bin/atlasstyle-trunk -I$(TBB_INC) 
EXTRALIBS=-I$(TBB_INC) -L$(TBB_LIB) -lTcore -lTfunctions -lTFitterInputs -lTFitterResults -lMinuit2 -ltbb

#BINLINKFLAGS = -L$(LIBDIR) -I$(TBB_INC) -L$(TBB_LIB) -lTcore -lTfunctions -lTFitterInputs -lTFitterResults -lMinuit2 -ltbb  #_debug 

include $(SRC)/GNUmakefiles/GNUmakefile
