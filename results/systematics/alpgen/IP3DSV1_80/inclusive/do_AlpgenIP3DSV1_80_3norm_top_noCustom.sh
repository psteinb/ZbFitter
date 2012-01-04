
echo "using input files from $SRC/bundles/alpgen/inclusive/systematics/IP3DSV1_80"

    for file in {AllFlavorsBTagEffDown,AllFlavorsBTagEffUp,HeavyFlavorBTagEffDown,HeavyFlavorBTagEffUp,JER,JESDOWN,JESUP,LightBTagEffDown,LightBTagEffUp,MuonEff,MuonPt};
    do
	ENVFILE=Alpgen_bundleIP3DSV1_80_allJets_sumSV12mass_${file}_3norm_top.env
	set -x
	RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/systematics/IP3DSV1_80/bundleIP3DSV1_80_allJets_sumSV12mass_${file}.root -c ${ENVFILE} -D "Data" -T "TrueB_varied,TrueC_varied,TrueL_varied,Top_varied" -o InclusiveData_${ENVFILE/.env/} -r 5 > `pwd`/${ENVFILE/.env/.log} 2>&1 &
	RunFitter.exe -M Migrad -d $SRC/bundles/alpgen/inclusive/systematics/IP3DSV1_80/bundleIP3DSV1_80_allJets_sumSV12mass_${file}.root -c ${ENVFILE} -D "PseudoData" -T "TrueB_varied,TrueC_varied,TrueL_varied,Top_varied" -o InclusivePseudoData_${ENVFILE/.env/} -r 5 > `pwd`/raw_${ENVFILE/.env/.log} 2>&1 &
	set +x
    done


