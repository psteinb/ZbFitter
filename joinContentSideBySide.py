import os,sys,ROOT,math

def combineHistos(_file2Write2=None,_plot1=None,_plot2=None):
    """
    function to create a new histogram containing _plot1 and _plot2 side by side
    """
    newMinX=min(_plot1.GetXaxis().GetXmin(),_plot2.GetXaxis().GetXmin())
    newMaxX=_plot1.GetXaxis().GetXmax() + _plot2.GetXaxis().GetXmax()
    Nbins = _plot1.GetNbinsX() + _plot2.GetNbinsX()
    newName = "_".join([_plot1.GetName(),_plot2.GetName(),"_joined"])

    if _file2Write2.Get(newName).__nonzero__():
        return None

    newPlot = ROOT.TH1D(newName,";"+_plot1.GetXaxis().GetTitle()+";"+_plot1.GetYaxis().GetTitle(),Nbins,newMinX,newMaxX)
    newPlot.SetDirectory(_file2Write2.GetDirectory("/"))
    
    for binIdx in range(1,_plot1.GetNbinsX()):
        newPlot.SetBinContent(binIdx,_plot1.GetBinContent(binIdx))
        newPlot.SetBinError(binIdx,_plot1.GetBinError(binIdx))
        
    for binIdx in range(_plot1.GetNbinsX(),Nbins):
        bin2 = binIdx-_plot1.GetNbinsX()+1
        newPlot.SetBinContent(binIdx,_plot2.GetBinContent(bin2))
        newPlot.SetBinError(binIdx,_plot2.GetBinError(bin2))
    
    return newPlot

def listObjectNames(_afile=None):
    """function to return a list of all object names
    """
    listPrim = _afile.GetListOfKeys()
    return [ item.GetName() for item in listPrim if item.ReadObj() ]

        
if __name__ == '__main__':
    
    if '-h' in sys.argv or '--help' in sys.argv:
        print "joinContentSideBySide"
        print "usage: joinContentSideBySide.py <file1> <file2>"
        sys.exit(1)

    if len(sys.argv[1:])!=2:
        print "error: not enough arguments"
        sys.exit(1)

    if not (os.path.exists(sys.argv[1]) and os.path.exists(sys.argv[2])):
        print "error: files do not exist",sys.argv[1],sys.argv[2]
        sys.exit(1)

    file1 = ROOT.TFile(sys.argv[1])
    file2 = ROOT.TFile(sys.argv[2])
    fileNew = ROOT.TFile(sys.argv[1].split("_")[0]+"_combined.root","RECREATE")

    listOfNames = listObjectNames(file1)
    
    for name in listOfNames:
        
        print ">>> processing %s (%i/%i)" % (name,listOfNames.index(name)+1,len(listOfNames))
        plot1 = file1.Get(name)
        plot1.Print("")
        plot2 = file2.Get(name)
        plot2.Print("")
        newPlot = combineHistos(fileNew,plot1,plot2)
        if newPlot:
            newPlot.Print("")
            newPlot.Write()
            print ">>> %s: integral %f" % (newPlot.GetName(),newPlot.Integral())
        else:
            print "<<< skipped"
     

    
    #fileNew.Write()
    fileNew.Close()
