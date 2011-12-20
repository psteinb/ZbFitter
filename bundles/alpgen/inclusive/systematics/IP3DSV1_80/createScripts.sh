
for item in `find ${PWD} -name "bundle*cfg"|grep -v template|sed -e 's/.*_sumSV12mass_\(.*\)\.cfg.*/\1/'|sort`;do 
    echo $item
    cp -v bundleIP3DSV1_80_allJets_sumSV12mass_template.cfg bundleIP3DSV1_80_allJets_sumSV12mass_${item}.cfg;
    sed -i -e "s/_JER_/_${item}_/g" bundleIP3DSV1_80_allJets_sumSV12mass_${item}.cfg;
done
