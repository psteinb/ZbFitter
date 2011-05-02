set -x
RunPseudoExperiments.exe -M Migrad -d $SRC/tests/ToFit_bcl_511.root -c $SRC/results/ensemble/BinnedEML.env -D "data" -T "mcb,mcc,mcl" -o results.511_ -i 100 > test.511.log 2>&1 &
RunPseudoExperiments.exe -M Migrad -d $SRC/tests/ToFit_bcl_111.root -c $SRC/results/ensemble/BinnedEML.env -D "data" -T "mcb,mcc,mcl" -o results.111_ -i 100 > test.111.log 2>&1 &
set +x