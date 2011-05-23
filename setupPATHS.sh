#!/bin/sh

# this needs to be sourced
# $Id: setANALpath.sh,v 1.2 2008/04/17 11:15:53 petzold Exp $
# set -x
function usage
{
    echo "Usage: setANALpath <opt> <arg>"
    echo "Options:"
    echo -e "   -s, --sourcedir <arg> \t source directory \$SRC is set to <arg> "
    echo -e "   -a, --bfarch <arg> \t set \$BFARCH to <arg> "
#    echo -e "   -b, --bindir <arg> \t set \$BINDIR to <arg>"
    echo -e "Defaults:"
    echo -e "   SRC    \t set to $PWD "
    echo -e "   BFARCH \t is guessed"
#    echo -e "   BINDIR \t is set to \$SRC/bin/\$BFARCH/\$ROOTRELEASE"
}

HELPPRINT=""
#
while [ -n "$1" ]; do
    case $1 in
	-s | --sourcedir )     
	    shift
	    if [ ! -d $1 ];then
		echo "Directory $1 doesn't exist!"
		return 3;
	    fi
	    export SRC=$1
	    ;;
	-a | --bfarch )     
	    shift
	    BFARCH=$1
	    ;;
#	-b | --bindir )     
#	    shift
#	    if [ ! -d $1 ];then
#		echo "Directory $1 doesn't exist!"
#		return 3;
#	    fi
#	    BINDIR=$1
#	    BINDIRSET="1"
#	    ;;
	-h | --help )     
	    usage
	    HELPPRINT="1"
	    return 0
	    ;;
	* )                     
	    usage
	    HELPPRINT="1"
	    exit 1
    esac
    shift
done


if [ -z "$ROOTSYS" ]
then
    echo "No ROOT version is set. Use 'setROOTpath' before running setANALpath"
    return 1;
fi

GCCSTR="gcc$(gcc -dumpversion| sed -e 's/\.//g')"
export ROOTRELEASE=`root-config --version | sed -e 's/\//\./g'`

if [ -z "$SRC" ]; then
    export SRC=`pwd`
fi

#mingle with BFARCH variable
if [ -z "$BFARCH" ]; then
	#try to guess the BFARCH
    kernel=`uname -r|awk -F"." '{print $1$2}'`

    which lsb_release 1> /dev/null 2> /dev/null; excode=$?

    if  [ $excode -ne 0 ]; then
	echo "Cannot guess BFARCH because lsb_release cannot be found! Please specify a BFARCH on the command line!"
	return 2;
    fi

    if lsb_release -d | grep -q Scientific ; then
	vendor=SL
	release=`lsb_release -r |awk '{print $2}' |awk -F"." '{print $1}'`
    fi
    if lsb_release -d | grep -q RedHat ; then
	vendor=RHEL
	release=`lsb_release -r |awk '{print $2}'`
    fi

    if uname -m |grep -q -E i?86 ; then
	arch=i386
    fi
    if uname -m |grep -q 64 ; then
	arch=x86_64
    fi

    gccver=`gcc -dumpversion| sed -e 's/\.//g'`

    placeholder1="_"
    placeholder2="_gcc"
    BFARCH="Linux$kernel$vendor$release$placeholder1$arch$placeholder2$gccver"
    
    export BFARCH
fi

#if LIB exists
if [ -n $LIB ]; then
    oldlib=$LIB
fi

#export loki stuff
if [[ $LIB != *loki* ]];then
    export LD_LIBRARY_PATH=/home/psteinb/software/loki_${GCCSTR}/lib:$LD_LIBRARY_PATH
    echo "loaded /home/psteinb/software/loki_${GCCSTR}/lib"
else
    echo "/home/psteinb/software/loki_${GCCSTR}/lib already loaded"
fi

#create LIB for package
export LIB=`echo $SRC/lib/$BFARCH/$ROOTRELEASE |sed -e 's%\/\/%\/%g'`
if [ x$oldlib != x ]; then
    sedlib=`echo $oldlib | sed  -e 's/\_/\\\_/g'  -e 's%\/%\\\/%g' -e 's%\.%\\\.%g'`
    sedstring='s%:[^:]*'$sedlib'[^:]*:%:%g'
    export LD_LIBRARY_PATH=`echo :$LD_LIBRARY_PATH: | sed -e $sedstring  -e 's/^://g' -e 's% .$%%g' -e 's%:$%%g' -e 's%\/\/%\/%g'`:$LIB
fi

if [ -z $oldlib ]; then
    export LD_LIBRARY_PATH=`echo :$LD_LIBRARY_PATH: | sed  -e 's/^://g' -e 's% .$%%g' -e 's%:$%%g' -e 's%\/\/%\/%g'`:$LIB
fi


## do the same for 

#if BIN exists
if [ -n $BINDIR ]; then
    oldbin=$BINDIR
fi

#create BIN for package
export BINDIR=`echo $SRC/bin/$BFARCH/$ROOTRELEASE |sed -e 's%\/\/%\/%g'`
if [ x$oldbin != x ]; then
    sedbin=`echo $oldbin | sed  -e 's/\_/\\\_/g'  -e 's%\/%\\\/%g' -e 's%\.%\\\.%g'`
    sedbinstring='s%:[^:]*'$sedbin'[^:]*:%:%g'
    export PATH=`echo :$PATH: | sed -e $sedbinstring  -e 's/^://g' -e 's% .$%%g' -e 's%:$%%g' -e 's%\/\/%\/%g'`:$BINDIR
fi

if [ -z $oldbin ]; then
    export PATH=`echo :$PATH: | sed  -e 's/^://g' -e 's% .$%%g' -e 's%:$%%g' -e 's%\/\/%\/%g'`:$BINDIR
fi


if [ -z $HELPPRINT ];then
    echo "Setup build environment for ROOT version $ROOTRELEASE in $SRC with BFARCH $BFARCH !"
    echo "$BINDIR appended to \$PATH"

fi


echo -e "SRC\t${SRC}"
echo -e "BFARCH\t${BFARCH}"
echo -e "LIB\t${LIB}"
echo -e "BINDIR\t${BINDIR}"
return 0
