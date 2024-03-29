RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/bundleIP3DSV1_80_allJets_sumSV12mass.root  -c AlpgenIP3DSV1_80_3norm_top_sumSV12mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o AlpgenIP3DSV1_80_3norm_top_inclusive_sumSV12mass -r 5 > $SRC/results/central/alpgen/IP3DSV1_80/inclusive/AlpgenIP3DSV1_80_3norm_top_inclusive_sumSV12mass.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/bundleIP3DSV1_80_allJets_sumSV12mass.root  -c AlpgenIP3DSV1_80_3norm_background_sumSV12mass.env -D "Data" -T "TrueB,TrueC,TrueL,Background" -o AlpgenIP3DSV1_80_3norm_background_inclusive_sumSV12mass -r 5 > $SRC/results/central/alpgen/IP3DSV1_80/inclusive/AlpgenIP3DSV1_80_3norm_background_inclusive_sumSV12mass.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/bundleIP3DSV1_80_allJets_sumSV12mass.root  -c AlpgenIP3DSV1_80_3norm_top_sumSV12mass.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o AlpgenIP3DSV1_80_3norm_top_inclusive_sumSV12mass_PseudoData -r 5 > $SRC/results/central/alpgen/IP3DSV1_80/inclusive/AlpgenIP3DSV1_80_3norm_top_inclusive_sumSV12mass_PseudoData.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/bundleIP3DSV1_80_allJets_sumSV12mass.root  -c AlpgenIP3DSV1_80_3norm_background_sumSV12mass.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Background" -o AlpgenIP3DSV1_80_3norm_background_inclusive_sumSV12mass_PseudoData -r 5 > $SRC/results/central/alpgen/IP3DSV1_80/inclusive/AlpgenIP3DSV1_80_3norm_background_inclusive_sumSV12mass_PseudoData.log 2>&1 &


#RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/AlpgenIP3DSV1_80_allJets_sumSV12mass.root  -c AlpgenIP3DSV1_80_3norm_top_sumSV12mass.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o AlpgenIP3DSV1_80_3norm_top_inclusive_sumSV12mass_PseudoData -r 5 > $SRC/results/central/alpgen/IP3DSV1_80/inclusive/AlpgenIP3DSV1_80_3norm_top_inclusive_sumSV12mass_PseudoData.log 2>&1 &

#RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/AlpgenIP3DSV1_80_maxSV12mass.root  -c AlpgenIP3DSV1_80_3norm_top_maxSV12mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o AlpgenIP3DSV1_80_3norm_top_inclusive_maxSV12mass -r 5 > $SRC/results/central/alpgen/IP3DSV1_80/inclusive/AlpgenIP3DSV1_80_3norm_top_inclusive_maxSV12mass.log 2>&1 &

#RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/AlpgenIP3DSV1_80_maxSV12mass.root  -c AlpgenIP3DSV1_80_3norm_top_maxSV12mass.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o AlpgenIP3DSV1_80_3norm_top_inclusive_maxSV12mass_PseudoData -r 5 > $SRC/results/central/alpgen/IP3DSV1_80/inclusive/AlpgenIP3DSV1_80_3norm_top_inclusive_maxSV12mass_PseudoData.log 2>&1 &


