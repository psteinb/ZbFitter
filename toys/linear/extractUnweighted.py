import ROOT,sys

def dumpPlotsToFile(_tfile,factorB=1.,_id="Staco"):
    """
    Arguments:
    - `factorB`:
    """
    nfile = ROOT.TFile(_id+"Unweighted_Btimes"+str(factorB)+".root","RECREATE")
    nfile.WriteHeader()
    nfile.WriteFree()
    data = _tfile.Get(_id+"ZJetsStudySV0/JetsWith1ZCandidate/1f_jet_flavor_SV0mass_1GeV")
    mcb = _tfile.Get(_id+"ZJetsStudySV0/JetsWith1ZCandidate/1f_jet_flavor_SV0mass_1GeV_trueb")
    mcc = _tfile.Get(_id+"ZJetsStudySV0/JetsWith1ZCandidate/1f_jet_flavor_SV0mass_1GeV_truec")
    mcl = _tfile.Get(_id+"ZJetsStudySV0/JetsWith1ZCandidate/1f_jet_flavor_SV0mass_1GeV_truelight")
        
    nData = data.Clone("data");nData.Sumw2()
    nMcb  = mcb .Clone("mcb") ;nMcb .Sumw2()
    nMcc  = mcc .Clone("mcc") ;nMcc .Sumw2()
    nMcl  = mcl .Clone("mcl") ;nMcl .Sumw2()

    nMcb.Scale(factorB)
    
    nData.SetDirectory(nfile.GetDirectory("/"))
    nMcb .SetDirectory(nfile.GetDirectory("/"))
    nMcc .SetDirectory(nfile.GetDirectory("/"))
    nMcl .SetDirectory(nfile.GetDirectory("/"))

    nfile.Write()
    nfile.Close()



if __name__ == '__main__':
    
    if '-h' in sys.argv or '--help' in sys.argv:
        print "usage: extractUnweighted <rootFile>"
        sys.exit(1)
        
    if len(sys.argv[1:])!=1:
        tfile = ROOT.TFile("./ZBAnalysis.SherpaZ3jetstomumuEnhancedcb.root")
    else:
        tfile = ROOT.TFile(sys.argv[1])

    for i in [.2,.4,.6,.8,1.]:
        dumpPlotsToFile(tfile,i)
        dumpPlotsToFile(tfile,i,"Muid")
