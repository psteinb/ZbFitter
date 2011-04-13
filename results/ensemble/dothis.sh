set -x
RunPseudoExperiments.exe -M MINOS -d ./extractedSV0.root -c $SRC/functions/SimpleMaxLLH.env -D "data_muid" -T "z_muid_trueB,z_muid_trueC,z_muid_trueL" -o $SRC/results/ensemble/results.10k.eps -i 10000 > $SRC/results/ensemble/test.10k.log 2>&1 &

RunPseudoExperiments.exe -M MINOS -d ./extractedSV0.root -c $SRC/functions/SimpleMaxLLH.env -D "data_muid" -T "z_muid_trueB,z_muid_trueC,z_muid_trueL" -o $SRC/results/ensemble/results.50k.eps -i 50000 > $SRC/results/ensemble/test.50k.log 2>&1 &


set +x