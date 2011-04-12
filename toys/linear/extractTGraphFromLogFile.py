import ROOT,sys,os
from array import array

sys.path.append("/home/psteinb/bin/atlasstyle/")

import AtlasStyle    

if not 'gROOT' in dir():
    from ROOT import *
    gROOT.SetBatch(True)
#    ATLASstyle = gROOT.LoadMacro("/home/psteinb/bin/atlasstyle/AtlasStyle.C++")
    gROOT.SetStyle(AtlasStyle.AtlasStyle().GetName())
    gROOT.ForceStyle()


def dumpTripeToTGraph(_triples,_name=""):

    tgraph = ROOT.TGraphErrors(len(_triples))
    tgraph.SetName(_name+"_tge")

    #load the arrays
    for n in _triples:
        tgraph.SetPoint(_triples.index(n),n[0],n[1])
        tgraph.SetPointError(_triples.index(n),0.,n[-1])

    tgraph.GetXaxis().SetTitle("f_{b}/f_{b,mc}")
    tgraph.GetYaxis().SetTitle("f_{b,fitted}")

    tc = ROOT.TCanvas(_name,"",600,400)
    tc.Clear()
    tc.Draw()
    tc.cd()
    tgraph.Draw("AP*")
    tc.Update()
    tc.Print(".eps")


if __name__ == '__main__':
    
    if '-h' in sys.argv or '--help' in sys.argv or len(sys.argv[1:])!=1:
        print "usage: extractUnweighted <log>"
        print "the logifle must follow the format: <factor> <yvalue> +/- <yerror>"
        sys.exit(1)
        
    fname = sys.argv[1]
    outname = str(fname).replace(".log","_tgraph")

    if os.path.isfile(sys.argv[1]):
        filestream = open(sys.argv[1])
    else:
        print sys.argv[1]," DOES NOT EXIST!"
        sys.exit(1)

    fcontent = filestream.readlines()
    
    lTriples = [ item.split(" ") for item in fcontent ]
    fTriples = []
    print "found ..."
    for i in lTriples:
        last = i[-1].strip('/n')
        fTriples.append([float(i[0]),float(i[1]),float(last)])
        print fTriples
        print "%f: %f ( %f )" % (fTriples[-1][0],fTriples[-1][1],fTriples[-1][-1])
        
    dumpTripeToTGraph(fTriples,outname) 
