import os,sys,ROOT,math,gc
gc.disable()
sys.path.append("/home/psteinb/bin/atlasstyle/")
import AtlasStyle    

if not 'gROOT' in dir():
    from ROOT import *
    gROOT.SetBatch(True)
    gROOT.SetStyle(AtlasStyle.AtlasStyle().GetName())
    gROOT.ForceStyle()

#def combineHistos(_file2Write2=None,_plot1=None,_plot2=None):
#    """
#    function to create a new histogram containing _plot1 and _plot2 side by side
#    """
#    newMinX=min(_plot1.GetXaxis().GetXmin(),_plot2.GetXaxis().GetXmin())
#    newMaxX=_plot1.GetXaxis().GetXmax() + _plot2.GetXaxis().GetXmax()
#    Nbins = _plot1.GetNbinsX() + _plot2.GetNbinsX()
#    newName = "_".join([_plot1.GetName(),_plot2.GetName(),"_joined"])
#
#    if _file2Write2.Get(newName).__nonzero__():
#        return None
#
#    newPlot = ROOT.TH1D(newName,";"+_plot1.GetXaxis().GetTitle()+";"+_plot1.GetYaxis().GetTitle(),Nbins,newMinX,newMaxX)
#    newPlot.SetDirectory(_file2Write2.GetDirectory("/"))
#    
#    for binIdx in range(1,_plot1.GetNbinsX()):
#        newPlot.SetBinContent(binIdx,_plot1.GetBinContent(binIdx))
#        newPlot.SetBinError(binIdx,_plot1.GetBinError(binIdx))
#        
#    for binIdx in range(_plot1.GetNbinsX(),Nbins):
#        bin2 = binIdx-_plot1.GetNbinsX()+1
#        newPlot.SetBinContent(binIdx,_plot2.GetBinContent(bin2))
#        newPlot.SetBinError(binIdx,_plot2.GetBinError(bin2))
#    
#    return newPlot
#
def add2Canvas(_row,_canvas,_plot1,_plot2):
    """ function to add new line to canvas for 2 columns (row numbering starts at 0!)"""
    startPad = (2*_row)+1
    

def listObjectNames(_afile=None):
    """function to return a list of all object names
    """
    listPrim = _afile.GetListOfKeys()
    names = {}
    value = []
    for item in listPrim:
        #item.ReadObj()
        if not names.has_key(item.GetName()):
            names[item.GetName()] = item.GetCycle()
        else:
            if item.GetCycle()>names[item.GetName()]:
                names[item.GetName()] = item.GetCycle()

    names2return = []            
    for k,v in names.iteritems():
        names2return.append(str(k+";"+str(v)))

    #return [ item.GetName() for item in listPrim if item.ReadObj() ]
    
    return names2return

def calculateIntegral(_aplot=None)        :
    """ function to compute integral plus error and return it as tuple """
    integral = ROOT.Double(0.)
    error = ROOT.Double(0.)
    if _aplot:
        integral = _aplot.IntegralAndError(_aplot.GetXaxis().GetFirst(),_aplot.GetXaxis().GetLast(),error)
        return (integral,error)
    else:
        return (0.,0.)
    
if __name__ == '__main__':
    
    if '-h' in sys.argv or '--help' in sys.argv:
        print "joinContentSideBySide"
        print "usage: joinContentSideBySide.py <file1> <file2> <listfile1> <listfile2>"
        sys.exit(1)

    if not (len(sys.argv[1:])>2 and len(sys.argv[1:])<5):
        print "error: not enough arguments"
        sys.exit(1)

    if not (os.path.exists(sys.argv[1]) and os.path.exists(sys.argv[2])):
        print "error: files do not exist",sys.argv[1],sys.argv[2]
        sys.exit(1)

    file1 = ROOT.TFile(sys.argv[1])
    file2 = ROOT.TFile(sys.argv[2])
    fileBase1 = file1.GetName().rstrip(".root")
    fileBase2 = file2.GetName().rstrip(".root")

    listOfNames1 = listObjectNames(file1)
    listOfNames2 = listObjectNames(file2)
    
    if sys.argv[3]:
        checkList = str(sys.argv[3]).split(",")
        loopList1 = [ item for item in listOfNames1 if str(item).split(";")[0] in checkList ]


    if len(sys.argv[1:])>3:
        checkList = str(sys.argv[4]).split(",")
        loopList2 = [ item for item in listOfNames2 if str(item).split(";")[0] in checkList ]
    else:
        loopList2 = loopList1[:]
   
    newName = fileBase1+"_"+fileBase2
    max2Loop = min(len(loopList1),len(loopList2))
    print max2Loop, " object to loop on"
    if(max2Loop==1):
        newName+="_"+str(loopList1[0]).split(";")[0]
    aCanvas = ROOT.TCanvas(newName,"",1600,max2Loop*600)
    aCanvas.Clear()
    aCanvas.Draw()
    aCanvas.Divide(2,max2Loop)

    for index in range(max2Loop):
        
        plot1 = file1.Get(loopList1[index])
        plot1.Rebin(5)
        plot1.Sumw2()
        plot2 = file2.Get(loopList2[index])
        plot2.Rebin(5)
        plot2.Sumw2()
        print ">>> processing %s (%i/%i)" % (loopList1[index],index+1,max2Loop)
        currentLine = (2*index)+1
        aCanvas.cd(currentLine)
        int1,err1 = calculateIntegral(plot1)
        int2,err2 = calculateIntegral(plot2)
        plot1.SetTitle(str("%s/%s, I: (%.1f #pm %.1f) " % (fileBase1,plot1.GetName(),int1,err1)))
        plot2.SetTitle(str("%s/%s, I: (%.1f #pm %.1f) " % (fileBase2,plot2.GetName(),int2,err2)))
        print plot1.GetTitle(),plot2.GetTitle()
        plot1.SetMaximum(1.75*max(plot1.GetMaximum(),plot2.GetMaximum()))
        plot1.Draw("e1")
        plot2.SetLineColor(ROOT.kRed)
        plot2.SetMarkerColor(ROOT.kRed)
        plot2.Draw("e0same")

        aCanvas.cd(currentLine+1)
        scaledPlot1 = plot1.Clone("scaled1")
        scaledPlot2 = plot2.Clone("scaled2")
        scaledPlot1.Scale(1/int1)
        scaledPlot2.Scale(1/int2)
        scaledPlot1.SetMaximum(1.75*max(scaledPlot1.GetMaximum(),scaledPlot2.GetMaximum()))
        scaledPlot1.Draw("e1")
        scaledPlot2.SetLineColor(ROOT.kRed)
        scaledPlot2.SetMarkerColor(ROOT.kRed)
        scaledPlot2.Draw("e0same")
        leg = ROOT.TLegend(0.35,0.6,0.95,0.92)
        leg.SetFillColor(ROOT.kWhite)
        leg.SetShadowColor(ROOT.kWhite)
        leg.SetBorderSize(1)
        leg.AddEntry(plot1,plot1.GetTitle(),"lep")
        leg.AddEntry(plot2,plot2.GetTitle(),"lep")
        leg.Draw()
        
        
    aCanvas.Update()
    aCanvas.Print(".eps")
    
    
