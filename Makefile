#
#	general makefile to compile this project
#	(there are more clever ways to write this ...)
#

all : 
	make -C $(SRC)/FitterResults
	@echo
	make -C $(SRC)/FitterInputs
	@echo
	make -C $(SRC)/functions           
	@echo
	make -C $(SRC)/core
	@echo
	make -C $(SRC)/Studies
	@echo


clean : 
	make -C $(SRC)/FitterResults clean
	@echo
	make -C $(SRC)/FitterInputs clean
	@echo
	make -C $(SRC)/functions clean  
	@echo
	make -C $(SRC)/core clean
	@echo
	make -C $(SRC)/Studies clean
	@echo


install : 
	make -C $(SRC)/FitterResults installdirs
	@echo
	make -C $(SRC)/FitterInputs installdirs
	@echo
	make -C $(SRC)/functions installdirs  
	@echo
	make -C $(SRC)/core installdirs
	@echo
	make -C $(SRC)/Studies installdirs

runners : 
	make -C $(SRC)/run RunFitter.exe
	make -C $(SRC)/run RunFitterOnFractions.exe
	make -C $(SRC)/run RunPseudoExperiments.exe
	make -C $(SRC)/run RunPseudoExperimentsOnFractions.exe

