set -x
RunPseudoExperiments.exe -M Migrad -d $SRC/results/ensemble/extractedSV0.root -c $SRC/results/ensemble/SimpleMaxLLH.env -D "data_muid" -T "z_muid_trueB,z_muid_trueC,z_muid_trueL" -o results.10k -i 1000 -r 5 > $SRC/results/ensemble/runPseudo.10k.log 2>&1 &
set +x

