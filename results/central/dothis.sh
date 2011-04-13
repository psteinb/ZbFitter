echo "\n>>MIGRAD"
RunFitter.exe -M MIGRAD -d ./extractedSV0.root -c $SRC/functions/SimpleMaxLLH.env -D "data_muid" -T "z_muid_trueB,z_muid_trueC,z_muid_trueL" -o migrad.muid.root
echo "\n>>MINOS"
RunFitter.exe -M MINOS  -d ./extractedSV0.root -c $SRC/functions/SimpleMaxLLH.env -D "data_muid" -T "z_muid_trueB,z_muid_trueC,z_muid_trueL" -o minos.muid.root
echo "\n>>MINOS w/o background"
RunFitter.exe -M MINOS  -d ./extractedSV0.root -c $SRC/functions/SimpleMaxLLH.env -D "data_muid_minusttbar" -T "z_muid_trueB,z_muid_trueC,z_muid_trueL" -o minos.muidttbar.root
