ITEMS="HeavyFlavorBTagEffDown HeavyFlavorBTagEffUp JER JESDOWN JESUP LightBTagEffDown LightBTagEffUp MuonEff MuonPt AllFlavorsBTagEffUp AllFlavorsBTagEffDown"

for item in $ITEMS;do
    NEWFILE80=bundleIP3DSV1_80_NJetsGe2_sumSV12mass_${item}.cfg 
    NEWFILE70=bundleIP3DSV1_70_NJetsGe2_sumSV12mass_${item}.cfg 
    cp bundleIP3DSV1_80_NJetsGe2_sumSV12mass_template.cfg ${NEWFILE80}
    cp bundleIP3DSV1_70_NJetsGe2_sumSV12mass_template.cfg ${NEWFILE70}
    sed -i -e "s/JER/${item}/g" $NEWFILE80 $NEWFILE70
done
    
#call for deleting   
#for file in `find . -type f -name "*cfg"|grep -v template`;do rm $file;done