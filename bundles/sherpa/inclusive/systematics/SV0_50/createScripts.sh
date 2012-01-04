
for item in `find ${PWD} -type f -name "bundle*cfg"|grep -v template|sed -e 's/.*_sumSV0mass_\(.*\)\.cfg.*/\1/'|sort`;do 
    echo $item
    cp -v customSV0_50_allJets_sumSV0mass_template.cfg customSV0_50_allJets_sumSV0mass_${item}.cfg
    sed -i -e "s/_JER_/_${item}_/g" customSV0_50_allJets_sumSV0mass_${item}.cfg
    cp -v bundleSV0_50_allJets_sumSV0mass_template.cfg bundleSV0_50_allJets_sumSV0mass_${item}.cfg
    sed -i -e "s/_JER_/_${item}_/g" bundleSV0_50_allJets_sumSV0mass_${item}.cfg

done
