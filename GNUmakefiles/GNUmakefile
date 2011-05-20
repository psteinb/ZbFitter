###############################################################
#
# $Id: GNUmakefile,v 1.5 2008/06/02 09:18:40 petzold Exp $
#
# Makefile for shared libs with dictionary to be loaded in root
# 
###############################################################

# file extensions
# extensions can be defined for each package in the package GNUmakefile

ifndef CXXHDREXT
	CXXHDREXT = hh
endif

ifndef CXXSRCEXT
	CXXSRCEXT = cc
endif

ifndef WARN
	WARNOPT = -w
endif

ifdef WARN
	WARNOPT = -Wall -Woverloaded-virtual
endif

#user may add BINDIR in his/her GNUmakefile
ifndef BINDIR
	BINDIR        = $(SRC)/bin/$(BFARCH)/$(ROOTRELEASE)/
endif



# Directories
OBJDIRBASE    = $(SRC)/lib/$(BFARCH)/$(ROOTRELEASE)
LIBDIR        = $(SRC)/lib/$(BFARCH)/$(ROOTRELEASE)
TEMPLATEDIR   = $(OBJDIRBASE)/$(PACKAGE)


# ROOT - Stuff
ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)
ROOTLDFLAGS   = $(shell root-config --ldflags)

# Fortran Compiler Flags
FC = g77
FCFLAGS = -ggdb3 -fno-automatic -fvxt -fdollar-ok -fno-backslash \
          -ffixed-line-length-132 -fno-second-underscore

# C++ - Compiler Flags
CXX = g++

#check if any optimisation is requested
ifndef CXXOPTFLAGS
	CXXOPTFLAGS = -ggdb3 -O0
endif

#user may introduce special debug symbol flags as well, -ggdb etc.
ifdef CXXFLAGS
	CXXFLAGS += $(WARNOPT) $(CXXOPTFLAGS)  -fexceptions -fPIC -I..
else
	CXXFLAGS =  $(WARNOPT) $(CXXOPTFLAGS)  -fexceptions -fPIC -I..
endif

ifdef LDFLAGS
	LDFLAGS += $(ROOTLDFLAGS) 
else
	LDFLAGS = $(ROOTLDFLAGS) $(CXXOPTFLAGS)
endif


# BABAR specific settings for TUD. AFAIK nobody uses this but 
# it's better to keep it for backward compatibility
#ifeq "tud" "$(BFSITE)"
#   CXX = g++
##   CXXFLAGS += -g $(WARNOPT) $(CXXOPTFLAGS) -DBABAR_COMP_INST -fexceptions -fPIC -I..
#   CXXFLAGS += -ggdb3 $(WARNOPT) $(CXXOPTFLAGS) -fexceptions -fPIC -I..
#endif
#

LD            =  $(CXX)
SOFLAGS       = -shared
XFLAGS	      = -o
CXXFLAGS     += $(ROOTCFLAGS) #-Wfatal-errors
CXXFLAGSD     = $(CXXFLAGS) -ggdb3
LIBS          = $(ROOTLIBS) -lEG -lProof -lTreePlayer
GLIBS         = $(ROOTGLIBS) -lEG -lProof -lTreePlayer -lMinuit
#XName declared by client
###################################################################################

# cint dicttionary settings
DICT    = $(PACKAGE)_Cint
DICTO   = $(DICT).o
DICTCXX = $(DICT).$(CXXSRCEXT)

# List of lib and object directories:
LIBA	= libT$(PACKAGE).a
LIBSO	= libT$(PACKAGE).so
OBJDIR  = $(OBJDIRBASE)/$(PACKAGE)

# Lists of objects NOT to include in library:
NOTTOCOMPILE += $(DICT)

# c++ files
ALL       = $(basename $(wildcard *.$(CXXSRCEXT)) )
NAMELIST  = $(filter-out  $(NOTTOCOMPILE),$(ALL))
HDRS      = $(addsuffix .$(CXXHDREXT), $(NAMELIST) )
# filter out hdrs that should not get into the rootcint dict
# NOTINDICT is usually defined in the PACKAGE GNUmakefile
DICTHDRS  = $(filter-out  $(NOTINDICT), $(HDRS))
OO 	  = $(addprefix $(OBJDIR)/, $(NAMELIST))
OBJS      = $(addsuffix .o, $(OO) )

# Fortran files
ALLF      = $(basename $(wildcard *.F) )
NAMELISTF = $(filter-out  $(NOTTOCOMPILE),$(ALLF))
OOF 	  = $(addprefix $(OBJDIR)/, $(NAMELISTF))
OBJSF     = $(addsuffix .o, $(OOF) )


# Default target build shared lib
all shlib: $(LIBSO)

statlib: $(LIBA)


# Static library:
$(LIBA) : $(OBJSF) $(OBJS) ##$(OBJDIR)/$(DICTO)
	@if [ ! -d $(LIBDIR)/$(PACKAGE) ] ; then echo -e "\n   !!!! ERROR: $(LIBDIR)/$(PACKAGE) doesn't exist!\nMaybe you should run 'make installdirs'!\n"; exit 1; fi
	rm -f $@
	$(AR) $(ARFLAGS)  $(LIBDIR)/$@ $^

# Shared library:
$(LIBSO) : $(OBJSF) $(OBJS) ##$(OBJDIR)/$(DICTO)
	@if [ ! -d $(LIBDIR)/$(PACKAGE) ] ; then echo -e "\n   !!!! ERROR: $(LIBDIR)/$(PACKAGE)  doesn't exist!\nMaybe you should run 'make installdirs'!\n"; fi
	@echo "   >>>> Linking shared library $@"
	$(LD) $(LDFLAGS) $(EXTRALIBS) $(SOFLAGS) $(GLIBS) -o $(LIBDIR)/$@ $^



# Rules for Dictionary:
$(OBJDIR)/$(DICTO) : $(DICTCXX) 
	@echo "   >>>> Compiling dictionary $(DICTCXX)"
	@if [ ! -d $(OBJDIR) ] ; then echo -e "\n   !!!! ERROR: $(OBJDIR) doesn't exist!\nMaybe you should run 'make installdirs'!\n"; fi
	$(CXX) $(CXXFLAGS) -I$(PACKAGE) -c $< -o $(OBJDIR)/$(DICTO)


$(DICTCXX) : $(DICTHDRS) $(PACKAGE)_LinkDef.$(CXXHDREXT)
	@echo "   >>>> Creating dictionary $(DICTCXX)"
	rootcint  -f $@ -c  -I.. -I$(PACKAGE) $^


# Static pattern rule for object file dependency on sources:
$(OBJS) : $(OBJDIR)/%.o : %.$(CXXSRCEXT)  %.$(CXXHDREXT) 
	@if [ ! -d $(OBJDIR) ] ; then echo -e "\n   !!!! ERROR: $(OBJDIR) doesn't exist!\nMaybe you should run make installdirs!\n"; exit 1 ; fi
	@echo "   >>>> Compiling $<";
	$(CXX) $(CXXFLAGS) -I$(PACKAGE) -c $< -o $@



# Static pattern rule for object file dependency on Fortran sources
$(OBJSF) : $(OBJDIR)/%.o : %.F
	@echo "   >>>> Compiling $<";
	$(FC) $(CXXFLAGS)  $< -c -o $@

#BINLINKFLAGS can be set by client GNUmakefile to point to required shared libs
#vpath %.so $(LIBDIR)
%.exe: %.$(CXXSRCEXT)
	echo "Building executable $(BINDIR)/$@ from $^!\n"
	$(LD) $(EXTRALIBS) $(CXXFLAGS) $(GLIBS) $(BINLINKFLAGS) $^ $(XFLAGS)  $(BINDIR)/$@
#vpath %.so

# create required directories for libs etc.
installdirs : 
	@if [ ! -d $(SRC)/lib/$(BFARCH) ] ; then mkdir -p $(SRC)/lib/$(BFARCH); fi
	@if [ ! -d $(SRC)/bin/$(BFARCH) ] ; then mkdir -p $(SRC)/bin/$(BFARCH); fi
	@if [ ! -d $(OBJDIRBASE) ]; then mkdir -p $(OBJDIRBASE); echo "   >>>> Create $(OBJDIRBASE)"; fi
	@if [ ! -d $(BINDIR) ]; then mkdir -p $(BINDIR); echo "   >>>> Create $(BINDIR)"; fi
	@if [ ! -d $(OBJDIR) ]; then mkdir -p $(OBJDIR); echo "   >>>> Create $(OBJDIR)"; \
        else echo " $(OBJDIR) already existent"; fi	

install :
	@echo "   >>>> The 'install' target is deprecated! Use 'make installdirs' instead!";

clean : 
	rm -f $(OBJDIRBASE)/$(LIBA) \
        $(OBJDIRBASE)/$(LIBSO) \
	$(OBJDIRBASE)/$(PACKAGE)/*.o \
	$(SRC)/$(PACKAGE)/$(PACKAGE)_Cint.$(CXXSRCEXT) \
	$(SRC)/$(PACKAGE)/$(PACKAGE)_Cint.$(CXXHDREXT) \
	$(SRC)/$(PACKAGE)/$(PACKAGE)_Cint.h \
	$(BINDIR)/*.exe

help :
	@echo " This Makefile only works if setANALpath has been run to setup the build environment!";
	@echo "";
	@echo " Available makefile targets:";
	@echo "";
	@echo " make all or make shlib :      build shared libs (.so)";
	@echo " make statlib :                build static libs (.a)";
	@echo " make clean :                  cleans up all object files and the dictionary stuff";
	@echo " make installdirs :            sets up the lib directory";
	@echo " make help :		      this help";
	@echo " make <target>.exe :	      build executable source file, <target>.cxx";
	@echo "";
	@echo " Available options:";
	@echo "";
	@echo " make <target> WARN=1 :        enable compiler warnings (-Wall -Woverloaded-virtual)";
