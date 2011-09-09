#!/usr/bin/env python
import os,sys
basePath = os.getenv("SRC")
if basePath:
    sys.path.append(basePath+"/python")
else:
    print "WARNING, PACKAGE NOT SETUP!"

sys.path.append("/home/%s/bin/atlasstyle-trunk" % (os.getenv("USER")))

if not 'gROOT' in dir():
    import ROOT
    import AtlasStyle
    ROOT.gROOT.SetBatch(True)
    ROOT.gROOT.SetStyle(AtlasStyle.AtlasStyle().GetName())
    ROOT.gROOT.ForceStyle()

    
#from RootObjectLoader import RootObjectLoader
from optparse import OptionParser

class printEnvFile:
    
    def __init__(self):
        self.usage = "usage: printEnvFile [options]"
        #define the parser with options only relevant for the digester
        self.parser = OptionParser(self.usage)
        self.parser.add_option("-f", "--file", dest="filename",action="store",
                               help="root file to parse ")
        self.parser.add_option("-3", "--make31env", dest="make31env",action="store_true",
                               help="pruduce environment for 3-1 fit")
        self.parser.add_option("-2", "--make22env", dest="make22env",action="store_true",
                               help="pruduce environment for 2-2 fit")

        self.parser.add_option("-F", "--doFractions", dest="doFractions",action="store_true",
                               help="pruduce environments fraction fits")

        self.rootFile = None
        self.make31env = False
        self.make22env = False
        self.valueDict = {}
        self.doFractions = False

    def initFromInput(self):

        popts,pargs = self.parser.parse_args()
        self.parsedOpts = popts.__dict__
        self.parsedArgs = pargs
        if "help" in self.parsedOpts.keys() or "h" in self.parsedOpts.keys() or not self.parsedOpts.keys():
            self.parser.print_help()
            return 1
        
        #do all flags
        if self.parsedOpts['filename']:
            filename = self.parsedOpts['filename']
            if os.path.isfile(filename):
                self.rootFile = ROOT.TFile.Open(filename)
            else:
                self.rootFile = None
                raise Exception("%s does not exist" % filename)

        if "make31env" in self.parsedOpts.keys():
            self.make31env = self.parsedOpts["make31env"]
        else:
            self.make31env = False
            
        
        if "make22env" in self.parsedOpts.keys():
            self.make22env = self.parsedOpts["make22env"]
        else:
            self.make22env = False

        if "doFractions" in self.parsedOpts.keys():
            self.doFractions = self.parsedOpts["doFractions"]


    def fillValues(self):

        TrueB 		= self.rootFile.Get("TrueB")
        TrueC 		= self.rootFile.Get("TrueC")
        TrueL 		= self.rootFile.Get("TrueL")
        Top   		= self.rootFile.Get("Top")
        Background      = self.rootFile.Get("Background")
        
        if Background.__nonzero__():
            total        = sum([float(item.Integral()) for item in [TrueB,TrueC,TrueL,Background]])
        else:
            total        = sum([float(item.Integral()) for item in [TrueB,TrueC,TrueL,Top]])

        for item in [TrueB,TrueC,TrueL,Top,Background]:
            if item.__nonzero__():
                if not self.doFractions:
                    self.valueDict[item.GetName()] = item.Integral()
                else:
                    self.valueDict[item.GetName()] = item.Integral()/float(total)


    def print31Environment(self):
        print ""
        print "%-40s %10s" % ("Parameter1.Name:","N_{b}")
        print "%-40s %9.1f" % ("Parameter1.Start:",self.valueDict["TrueB"])
        print "%-40s %10s" % ("Parameter1.Step:","0.1")
        print "%-40s %10s" % ("Parameter1.low:","0.")
        print "%-40s %10s" % ("Parameter2.Name:","N_{c}")
        print "%-40s %9.1f" % ("Parameter2.Start:",self.valueDict["TrueC"])
            
        print "%-40s %10s" % ("Parameter2.Step:","0.1")
        print "%-40s %10s" % ("Parameter2.low:","0.")
        print "%-40s %10s" % ("Parameter3.Name:","N_{l}")
        print "%-40s %9.1f" % ("Parameter3.Start:",self.valueDict["TrueL"])

        print "%-40s %10s" % ("Parameter3.Step:","0.1")
        print "%-40s %10s" % ("Parameter3.low:","0.")
        print "%-40s %10s" % ("#fixed Parameters","")

        if "Background" in self.valueDict.keys():
            print "%-40s %10s" % ("Parameter4.Name:","N_{background}")
            print "%-40s %8.2f" % ("Parameter4.Start:",self.valueDict["Background"])
        else:
            print "%-40s %10s" % ("Parameter4.Name:","N_{top}")
            print "%-40s %8.2f" % ("Parameter4.Start:",self.valueDict["Top"])

        print "%-40s %10s" % ("Parameter4.Step:","0.")
        print "%-40s %10s" % ("Tolerance:","0.0005")
        print "%-40s %10s" % ("MaxFunCalls:","1000000")
        print "%-40s %10s" % ("MaxIterations:","100000")

    def print22Environment(self):
        print ""
        print "%-40s %10s" % ("Parameter1.Name:","N_{b}")
        print "%-40s %9.1f" % ("Parameter1.Start:",self.valueDict["TrueB"])
        print "%-40s %10s" % ("Parameter1.Step:","0.1")
        print "%-40s %10s" % ("Parameter1.low:","0.")
        print "%-40s %10s" % ("Parameter2.Name:","N_{c}")
        print "%-40s %9.1f" % ("Parameter2.Start:",self.valueDict["TrueC"])
        print "%-40s %10s" % ("Parameter2.Step:","0.1")
        print "%-40s %10s" % ("Parameter2.low:","0.")
        print "%-40s %10s" % ("#fixed Parameters","")
        print "%-40s %10s" % ("Parameter3.Name:","N_{l}")
        print "%-40s %9.1f" % ("Parameter3.Start:",self.valueDict["TrueL"])

        print "%-40s %10s" % ("Parameter3.Step:","0.")

        if "Background" in self.valueDict.keys():
            print "%-40s %10s" % ("Parameter4.Name:","N_{background}")
            print "%-40s %8.2f" % ("Parameter4.Start:",self.valueDict["Background"])
        else:
            print "%-40s %10s" % ("Parameter4.Name:","N_{top}")
            print "%-40s %8.2f" % ("Parameter4.Start:",self.valueDict["Top"])

        print "%-40s %10s" % ("Parameter4.Step:","0.")
        print "%-40s %10s" % ("Tolerance:","0.0005")
        print "%-40s %10s" % ("MaxFunCalls:","1000000")
        print "%-40s %10s" % ("MaxIterations:","100000")

    def print22EnvironmentOnFractions(self):
        print ""
        print "%-40s %10s" % ("Parameter1.Name:","f_{b}")
        print "%-40s %2.5f" % ("Parameter1.Start:",self.valueDict["TrueB"])
        print "%-40s %10s" % ("Parameter1.Step:","0.1")
        print "%-40s %10s" % ("Parameter1.low:","0.")
        if "Background" in self.valueDict.keys():
            print "%-40s %2.5f" % ("Parameter1.high:",float(1-self.valueDict["TrueL"]-self.valueDict["Background"]))
        else:
            print "%-40s %2.5f" % ("Parameter1.high:",float(1-self.valueDict["TrueL"]-self.valueDict["Top"]))
        print "%-40s %10s" % ("#fixed Parameters","")
        print "%-40s %10s" % ("Parameter2.Name:","f_{l}")
        print "%-40s %2.5f" % ("Parameter2.Start:",self.valueDict["TrueL"])
        print "%-40s %10s" % ("Parameter2.Step:","0.")

        if "Background" in self.valueDict.keys():
            print "%-40s %10s" % ("Parameter3.Name:","f_{background}")
            print "%-40s %2.5f" % ("Parameter3.Start:",self.valueDict["Background"])
        else:
            print "%-40s %10s" % ("Parameter3.Name:","f_{top}")
            print "%-40s %2.5f" % ("Parameter3.Start:",self.valueDict["Top"])
        print "%-40s %10s" % ("Parameter3.Step:","0.")

        print "%-40s %10s" % ("Parameter4.Name:","f_{c}")
        print "%-40s %2.5f" % ("Parameter4.Start:",self.valueDict["TrueC"])
        print "%-40s %10s" % ("Parameter4.Omit:","True")
        print "%-40s %10s" % ("Tolerance:","0.0005")
        print "%-40s %10s" % ("MaxFunCalls:","1000000")
        print "%-40s %10s" % ("MaxIterations:","100000")

    def Run(self):

        self.fillValues()
        
        if self.doFractions:
            self.print22EnvironmentOnFractions()
        else:
            if self.make31env:
                self.print31Environment()
            elif self.make22env:
                self.print22Environment()
            else:
                print "no printing scheme specified"
        
        self.rootFile.Close()
        
if __name__=="__main__":
    #initialize from command line options
    
    printer = printEnvFile()
    
    try: 
        printer.initFromInput()
    except:
        print "FAILED TO INIT HISTOS!"
        sys.exit(-1)
    else:
        try:
            printer.Run()
        except Exception as inst:
            print "failed to call printEnvFile.Run()\n\t>>> ",inst
            sys.exit(-1)
        else:
            sys.exit(0)
        

