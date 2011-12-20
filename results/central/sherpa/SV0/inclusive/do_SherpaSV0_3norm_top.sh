RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaSV0_sumSV0mass.root  -c SherpaSV0_3norm_top_sumSV0mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaSV0_3norm_top_inclusive_sumSV0mass -r 5 > $SRC/results/central/sherpa/SV0/inclusive/SherpaSV0_3norm_top_inclusive_sumSV0mass.log 2>&1 &

#RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaSV0_sumSV0mass.root  -c SherpaSV0_3norm_top_sumSV0mass.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o SherpaSV0_3norm_top_inclusive_sumSV0mass_PseudoData -r 5 > $SRC/results/central/sherpa/SV0/inclusive/SherpaSV0_3norm_top_inclusive_sumSV0mass_PseudoData.log 2>&1 &

#RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaSV0_maxSV0mass.root  -c SherpaSV0_3norm_top_maxSV0mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaSV0_3norm_top_inclusive_maxSV0mass -r 5 > $SRC/results/central/sherpa/SV0/inclusive/SherpaSV0_3norm_top_inclusive_maxSV0mass.log 2>&1 &

#RunFitter.exe -M Migrad -d $SRC/bundles/sherpa/inclusive/SherpaSV0_maxSV0mass.root  -c SherpaSV0_3norm_top_maxSV0mass.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o SherpaSV0_3norm_top_inclusive_maxSV0mass_PseudoData -r 5 > $SRC/results/central/sherpa/SV0/inclusive/SherpaSV0_3norm_top_inclusive_maxSV0mass_PseudoData.log 2>&1 &


