set -x
RunFitter.exe -M Migrad -d $SRC/tests/ToFit_bcl_511.root -c $SRC/results/central/BinnedEML.env -D "data" -T "mcb,mcc,mcl" -o results.511_ -m 2 > test.511.log 2>&1 &
RunFitter.exe -M Migrad -d $SRC/tests/ToFit_bcl_111.root -c $SRC/results/central/BinnedEML.env -D "data" -T "mcb,mcc,mcl" -o results.111_ -m 2 > test.111.log 2>&1 &
set +x