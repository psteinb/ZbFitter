set -x
RunPseudoExperiments.exe -M Migrad -d /home/psteinb/development/sandbox/ZbFitter/tests/ToFit_bcl_511.root -c $SRC/results/ensemble/SimpleMaxLLH.env -D "data" -T "mcb_mult5,mcc,mcl" -o results.511_mult5 -i 1000 > test.511_mult5.log 2>&1 &
RunPseudoExperiments.exe -M Migrad -d /home/psteinb/development/sandbox/ZbFitter/tests/ToFit_bcl_511.root -c $SRC/results/ensemble/SimpleMaxLLH.env -D "data" -T "mcb,mcc,mcl" -o results.511 -i 1000 > test.511.log 2>&1 &
set +x