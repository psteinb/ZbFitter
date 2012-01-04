RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/AlpgenIP3DSV1_70_allJets_sumSV12mass.root  -c AlpgenIP3DSV1_70_2norm_fixedLight_fixedTop_sumSV1mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o AlpgenIP3DSV1_70_2norm_fixedLight_fixedTop_inclusive_sumSV12mass -r 5 > $SRC/results/central/alpgen/IP3DSV1_70/inclusive/AlpgenIP3DSV1_70_2norm_fixedLight_fixedTop_inclusive_sumSV12mass.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/AlpgenIP3DSV1_70_allJets_sumSV12mass.root  -c AlpgenIP3DSV1_70_2norm_fixedLight_fixedTop_sumSV1mass.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o AlpgenIP3DSV1_70_2norm_fixedLight_fixedTop_inclusive_sumSV12mass_PseudoData -r 5 > $SRC/results/central/alpgen/IP3DSV1_70/inclusive/AlpgenIP3DSV1_70_2norm_fixedLight_fixedTop_inclusive_sumSV12mass_PseudoData.log 2>&1 &

#RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/AlpgenIP3DSV1_70_maxSV12mass.root  -c AlpgenIP3DSV1_70_2norm_fixedLight_fixedTop_maxSV1mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o AlpgenIP3DSV1_70_2norm_fixedLight_fixedTop_inclusive_maxSV12mass -r 5 > $SRC/results/central/alpgen/IP3DSV1_70/inclusive/AlpgenIP3DSV1_70_2norm_fixedLight_fixedTop_inclusive_maxSV12mass.log 2>&1 &

#RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/AlpgenIP3DSV1_70_maxSV12mass.root  -c AlpgenIP3DSV1_70_2norm_fixedLight_fixedTop_maxSV1mass.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o AlpgenIP3DSV1_70_2norm_fixedLight_fixedTop_inclusive_maxSV12mass_PseudoData -r 5 > $SRC/results/central/alpgen/IP3DSV1_70/inclusive/AlpgenIP3DSV1_70_2norm_fixedLight_fixedTop_inclusive_maxSV12mass_PseudoData.log 2>&1 &


