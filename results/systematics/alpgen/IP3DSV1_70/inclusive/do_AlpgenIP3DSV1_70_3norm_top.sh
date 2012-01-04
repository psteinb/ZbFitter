
echo "using input files from $SRC/bundles/alpgen/inclusive/systematics/IP3DSV1_70"

if [[ -n ${1} ]];then
    
    for file in {AllFlavorsBTagEffDown,AllFlavorsBTagEffUp,HeavyFlavorBTagEffDown,HeavyFlavorBTagEffUp,JER,JESDOWN,JESUP,LightBTagEffDown,LightBTagEffUp,MuonEff,MuonPt};
    do
	ENVFILE=Alpgen_bundleIP3DSV1_70_allJets_sumSV12mass_${file}_3norm_top.env
	RFILE=$SRC/bundles/alpgen/inclusive/systematics/IP3DSV1_70/bundleIP3DSV1_70_allJets_sumSV12mass_${file}.root
	RunFitter.exe -M Migrad -d $RFILE -c $ENVFILE -D "Data" -T "TrueB_varied,TrueC_varied,TrueL_varied,Top_varied" -o Inclusive_${ENVFILE/.env/} -r 5 > `pwd`/${ENVFILE/.env/.log}  2>&1 &

    done

else
    echo "not input file given"
fi


