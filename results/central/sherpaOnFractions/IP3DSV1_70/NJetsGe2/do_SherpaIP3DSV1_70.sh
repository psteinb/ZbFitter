RunFitterOnFractions.exe -M Migrad -d ${SRC}/bundles/sherpa/NJetsGe2/SherpaIP3DSV1_70_NJetsGe2_maxSV12mass.root  -c SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_maxSV1mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaIP3DSV1_70_2norm_2fixed_NJetsGe2_fractions_maxSV1mass -r 5 > ${SRC}/results/central/sherpaOnFractions/IP3DSV1_70/NJetsGe2/SherpaIP3DSV1_70_2norm_2fixed_NJetsGe2_fractions_maxSV1mass.log 2>&1 &

RunFitterOnFractions.exe -M Migrad -d ${SRC}/bundles/sherpa/NJetsGe2/SherpaIP3DSV1_70_NJetsGe2_maxSV12mass.root  -c SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_maxSV1mass.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o SherpaIP3DSV1_70_2norm_2fixed_NJetsGe2_fractions_maxSV1mass_PseudoData -r 5 > ${SRC}/results/central/sherpaOnFractions/IP3DSV1_70/NJetsGe2/SherpaIP3DSV1_70_2norm_2fixed_NJetsGe2_fractions_maxSV1mass_PseudoData.log 2>&1 &

RunFitterOnFractions.exe -M Migrad -d ${SRC}/bundles/sherpa/NJetsGe2/SherpaIP3DSV1_70_NJetsGe2_sumSV12mass.root  -c SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_sumSV1mass.env -D "Data" -T "TrueB,TrueC,TrueL,Top" -o SherpaIP3DSV1_70_2norm_2fixed_NJetsGe2_fractions_sumSV1mass -r 5 > ${SRC}/results/central/sherpaOnFractions/IP3DSV1_70/NJetsGe2/SherpaIP3DSV1_70_2norm_2fixed_NJetsGe2_fractions_sumSV1mass.log 2>&1 &

RunFitterOnFractions.exe -M Migrad -d ${SRC}/bundles/sherpa/NJetsGe2/SherpaIP3DSV1_70_NJetsGe2_sumSV12mass.root  -c SherpaIP3DSV1_70_2norm_fixedLight_fixedTop_sumSV1mass.env -D "PseudoData" -T "TrueB,TrueC,TrueL,Top" -o SherpaIP3DSV1_70_2norm_2fixed_NJetsGe2_fractions_sumSV1mass_PseudoData -r 5 > ${SRC}/results/central/sherpaOnFractions/IP3DSV1_70/NJetsGe2/SherpaIP3DSV1_70_2norm_2fixed_NJetsGe2_fractions_sumSV1mass.log 2>&1 &