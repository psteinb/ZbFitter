
echo "using input files from $SRC/bundles/alpgen/inclusive/systematics/SV0_50"

    for file in {AllFlavorsBTagEffDown,AllFlavorsBTagEffUp,HeavyFlavorBTagEffDown,HeavyFlavorBTagEffUp,JER,JESDOWN,JESUP,LightBTagEffDown,LightBTagEffUp,MuonEff,MuonPt};
    do
	ENVFILE=Alpgen_bundleSV0_50_allJets_sumSV0mass_${file}_3norm_top.env
	RFILE=$SRC/bundles/alpgen/inclusive/systematics/SV0_50/bundleSV0_50_allJets_sumSV0mass_${file}.root
	set -x
	RunFitter.exe -M Migrad -d $RFILE -c ${ENVFILE} -D "Data" -T "TrueB_varied,TrueC_varied,TrueL_varied,Top_varied" -o InclusiveData_${ENVFILE/.env/} -r 5 > `pwd`/${ENVFILE/.env/.log} 2>&1 &
	RunFitter.exe -M Migrad -d $RFILE -c ${ENVFILE} -D "PseudoData" -T "TrueB_varied,TrueC_varied,TrueL_varied,Top_varied" -o InclusivePseudoData_${ENVFILE/.env/} -r 5 > `pwd`/PseudoData_${ENVFILE/.env/.log} 2>&1 &
	set +x
    done


