import os,sys,ROOT,math,gc

sys.path.append("/home/psteinb/bin/atlasstyle/")
import AtlasStyle    

if not 'gROOT' in dir():
    from ROOT import *
    gROOT.SetBatch(True)
    aStyle = AtlasStyle.AtlasStyle()
    aStyle.SetStatY(1.)
    aStyle.SetStatX(.95)
    aStyle.SetStatW(.8)
    aStyle.SetStatH(0.15)
    aStyle.SetStatBorderSize(0)
    aStyle.SetPadTopMargin(0.22)
    aStyle.SetOptStat(2210)
    gROOT.SetStyle(AtlasStyle.AtlasStyle().GetName())
    gROOT.ForceStyle()

if __name__ == '__main__':
    
    if '-h' in sys.argv or '--help' in sys.argv:
        print "takeAndFit"
        print "usage: takeAndFit.py <file1> <histo2fit>"
        sys.exit(1)

    if not (len(sys.argv[1:])>0 and len(sys.argv[1:])<3):
        print "error: not enough arguments"
        sys.exit(1)

    if not (os.path.exists(sys.argv[1])):
        print "error: file do not exist ",sys.argv[1]
        sys.exit(1)
        
    tfile = ROOT.TFile(sys.argv[1])
    if tfile.Get(sys.argv[2]).__nonzero__():
        histo = tfile.Get(sys.argv[2])
    else:
        print "error: object '%s' not found in %s " % (sys.argv[2],sys.argv[1])
        sys.exit(1)

    name = "%s_%s" % (os.path.split(sys.argv[1])[-1].rstrip(".root"),sys.argv[2])

    aCanvas = ROOT.TCanvas(name+"_fit","",800,600)
    aCanvas.Clear()
    aCanvas.Draw()

        
    fitValues = ROOT.TPaveText()
    fitValues.SetTextColor(kBlue)
    fitValues.SetBorderSize(0)
    fitValues.SetFillColor(kWhite)
    fitValues.SetTextAlign(21)

    aCanvas.cd(1)
    ROOT.gPad.SetTopMargin(.2);
    histo.SetStats(False)
    histo.DrawClone("e0")
    histo.Fit("gaus","VR","",histo.GetXaxis().GetXmin(),histo.GetXaxis().GetXmax())
    fitted = histo.GetFunction("gaus")
#    fitValues.AddText(str("#mu\t: %.3f #pm %.3f" % (fitted.GetParameter(1),fitted.GetParError(1))))
#    fitValues.AddText(str("#sigma\t: %.3f #pm %.3f" % (fitted.GetParameter(2),fitted.GetParError(2))))

    fitInfo = "#mu : %.3f #pm %.3f, #sigma : %.3f #pm %.3f" % (fitted.GetParameter(1),fitted.GetParError(1),fitted.GetParameter(2),fitted.GetParError(2))
    fitValues.AddText(fitInfo)
    fitValues.AddText(str("#chi^{2}/NDF\t: %.3f / %i" % (fitted.GetChisquare(),fitted.GetNDF())))

    fitValues.SetX1NDC(0.15);
    fitValues.SetX2NDC(1.);
    fitValues.SetY1NDC(.82);
    fitValues.SetY2NDC(.98);
    fitValues.Draw();
    aCanvas.Update()
    aCanvas.Print(".pdf")
    aCanvas.Print(".eps")

    aCanvas = ROOT.TCanvas(name+"_logfit","",800,600)
    aCanvas.Clear()
    aCanvas.Draw()
#    aCanvas.cd(2)
    ROOT.gPad.SetTopMargin(.2);
    ROOT.gPad.SetLogy()
    histo.Draw("e0")
    fitted.Draw("same")
    fitValues.Draw()

    aCanvas.Update()
    aCanvas.Print(".pdf")
    aCanvas.Print(".eps")
        
    tfile.Close()
    sys.exit(0)
