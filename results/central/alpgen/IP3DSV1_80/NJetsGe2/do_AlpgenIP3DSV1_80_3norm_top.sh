RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/NJetsGe2/AlpgenIP3DSV1_80_NJetsGe2_sumSV12mass.root  -c AlpgenIP3DSV1_80_3norm_top_sumSV12mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o IP3DSV1_80_3norm_top_NJetsGe2 -r 5   > $SRC/results/central/alpgen/IP3DSV1_80/NJetsGe2/IP3DSV1_80_3norm_top.log 2>&1 &

RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/NJetsGe2/AlpgenIP3DSV1_80_NJetsGe2_sumSV12mass.root  -c AlpgenIP3DSV1_80_3norm_top_sumSV12mass.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o IP3DSV1_80_3norm_top_NJetsGe2_PseudoData -r 5   > $SRC/results/central/alpgen/IP3DSV1_80/NJetsGe2/IP3DSV1_80_3norm_top_PseudoData.log 2>&1 &

#RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/NJetsGe2/bundleIP3DSV1_80_NJetsGe2.root  -c bundleIP3DSV1_80_2norm_fixedLight_fixedTop.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Alpgen_2norm_fixedLight_fixedTop_NJetsGe2 -r 5   > $SRC/results/central/alpgen/IP3DSV1_80/NJetsGe2/bundleIP3DSV1_80_2norm_fixedLight_fixedTop.log 2>&1 &

#RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/NJetsGe2/bundleIP3DSV1_80_NJetsGe2.root  -c bundleIP3DSV1_80_2norm_fixedLight_fixedTop.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o Alpgen_2norm_fixedLight_fixedTop_NJetsGe2_PseudoData -r 5   > $SRC/results/central/alpgen/IP3DSV1_80/NJetsGe2/bundleIP3DSV1_80_2norm_fixedLight_fixedTop_PseudoData.log 2>&1 &

#RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/NJetsGe2/bundleIP3DSV1_80_NJetsGe2.root  -c bundleIP3DSV1_80_2norm_fixedLight_fixedTop_HIGHc_lowb.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Alpgen_2norm_fixedLight_fixedTop_NJetsGe2_HIGHc_lowb -r 5   > $SRC/results/central/alpgen/IP3DSV1_80/NJetsGe2/bundleIP3DSV1_80_2norm_fixedLight_fixedTop_HIGHc_lowb.log 2>&1 &

#RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/NJetsGe2/bundleIP3DSV1_80_NJetsGe2.root  -c bundleIP3DSV1_80_2norm_fixedLight_fixedTop_lowc_HIGHb.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o Alpgen_2norm_fixedLight_fixedTop_NJetsGe2_lowc_HIGHb -r 5   > $SRC/results/central/alpgen/IP3DSV1_80/NJetsGe2/bundleIP3DSV1_80_2norm_fixedLight_fixedTop_lowc_HIGHb.log 2>&1 &

#RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/NJetsGe2/bundleIP3DSV1_80_NJetsGe2.root  -c bundleIP3DSV1_80_2norm_fixedLight_fixedTop.env -D "Data" -T "smoothedTrueB,smoothedTrueC,smoothedTrueL,smoothedTop" -o Alpgen_2norm_fixedLight_fixedTop_NJetsGe2_smoothed -r 5   > $SRC/results/central/alpgen/IP3DSV1_80/NJetsGe2/bundleIP3DSV1_80_2norm_fixedLight_fixedTop_smoothed.log 2>&1 &
