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
                               help="produce environments fraction fits")

        self.parser.add_option("-N", "--ObjectNames", 
                               dest="ObjectNames",
                               action="store",
                               default="TrueB,TrueC,TrueL,Top,Background",
                               help="override default object names following: TrueB,TrueC,TrueL,Top,Background")

        self.rootFile = None
        self.objectNames = []
        self.make31env = False
        self.make22env = False
        self.valueDict = {}
        self.doFractions = False
        self.objDict = {}

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
            
        if "ObjectNames" in self.parsedOpts.keys():
            self.objectNames = [ item for item in self.parsedOpts["ObjectNames"].split(",") ]


    def findObjectName(self,_contained):

        meta = _contained.lower()
        valueL = [ item for item in self.objectNames if item.lower().count(meta) ]
        if not valueL:
            self.rootFile.ls()
            raise KeyError("item dubbed "+_contained+" not found in provided object names "+str(self.objectNames))
        else:
            return valueL[0]
        
    def loadObjects(self):
       
        for item in self.objectNames:
            try:
                self.objDict[item] = self.rootFile.Get(self.findObjectName(item))
            except Exception as inst:
                self.objDict[item] = None
                print inst
            else:
                if self.objDict[item].__nonzero__():    
                    print ">>> loaded ",item
                else:
                    print ">>> item *%s* not found in input file %s" % (item,self.rootFile.GetName())
                    


    def fillValues(self):

        self.loadObjects()        

        total        = sum([float(item.Integral()) for item in self.objDict.values()])
        for item in self.objDict.values():
            if item.__nonzero__():
                if not self.doFractions:
                    self.valueDict[item.GetName().split("_")[0]] = item.Integral()
                else:
                    self.valueDict[item.GetName().split("_")[0]] = item.Integral()/float(total)


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
    except Exception as inst:
        print "FAILED TO INIT HISTOS!", inst
        sys.exit(-1)
    else:
        #try:
        printer.Run()
        #except Exception as inst:
        #    print "failed to call printEnvFile.Run()\n\t>>> ",inst
        #    sys.exit(-1)
        #else:
        #    sys.exit(0)
        

