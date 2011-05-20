if [[ -z $SRC ]];then
    echo 'package not setup, $SRC not found'
else
    echo "compiling modules"
    for dir in {$SRC/FitterResults,$SRC/FitterInputs,$SRC/functions,$SRC/core,$SRC/Studies};do
	echo -e "\n\n --> compiling $dir"
	make -C $dir clean && make -C $dir
    done
    make -C run/ clean
    for file in $SRC/run/Run*.cc;do
	CompileName=${file/$SRC\/run\//}
	echo -e "\n\n --> compiling executable of $file"
	make -C $SRC/run ${CompileName/.cc/.exe}
    done
    echo "All Done!"
fi