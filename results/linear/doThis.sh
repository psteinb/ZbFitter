RunLinearTest.exe -M Migrad -d $SRC/Saclay_ee.root   -c $SRC/results/linear/BinnedEML.2params.env -D "data" -T "mcb,mccpl" -o Saclay_2p_ee -i 100 -r 5
RunLinearTest.exe -M Migrad -d $SRC/Saclay_mumu.root -c $SRC/results/linear/BinnedEML.2params.env -D "data" -T "mcb,mccpl" -o Saclay_2p_mm -i 100 -r 5
