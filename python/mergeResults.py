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

    
from RootObjectLoader import RootObjectLoader
from optparse import OptionParser

class BundleHistos:
    
    def __init__(self):
        self.usage = "usage: BundleHistos [options]"
        #define the parser with options only relevant for the digester
        self.parser = OptionParser(self.usage)
        self.parser.add_option("-f", "--file", dest="filename",action="store",
                               help="ini file(s) to read root object from ")
        self.parser.add_option("-o", "--outputname", dest="outputname",action="store",
                               default="./fitterInputs.root", help="name of root file to dump to")
        self.parser.add_option("-l", "--fileHistoList", dest="fileHistoList",action="store",
                               help="semi colon separated list of triple <file:histoName:newName>")
        self.objectDB         = RootObjectLoader()
        self.configFile = None
        self.fileHistoList    = []
        self.outputname = None
        self.loaded = None
        self.openedFiles = []
        self.nBins = 0
        self.nFits = 0
        self.fitNames = []
        self.BinBorders = set()
        self.UpperBinLimit = 0
        self.LowerBinLimit = 0

    def initFromInput(self):
        print "%s >> parseInput" % self.__class__
        popts,pargs = self.parser.parse_args()
        self.parsedOpts = popts.__dict__
        self.parsedArgs = pargs
        if "help" in self.parsedOpts.keys() or "h" in self.parsedOpts.keys() or not self.parsedOpts.keys():
            self.parser.print_help()
            return 1
        
        #do all flags
        if self.parsedOpts['outputname']:
            self.outputname = self.parsedOpts['outputname']

        if self.parsedOpts['filename']:
            self.configFile = self.parsedOpts['filename']
            filename = self.configFile.split("/")[-1]

            self.objectDB.setConfigFile(self.configFile)
            self.objectDB.openFiles(False)
            self.initDictFromDatabase()
        else:
            if self.parsedOpts['fileHistoList']:
                self.initDictFromList(self.parsedOpts['fileHistoList'])
            else:
                raise Exception("no input given, exiting")


    def initDictFromList(self,_text=""):
        """
        function to load loaded from list given by CLI
        """
        self.loaded = {}
        files = [ item.split(":")[0] for item in _text.split(";") ]
        objects = [ item.split(":")[1] for item in _text.split(";") ]
        names = [ item.split(":")[2] for item in _text.split(";") ]
        self.openedFiles = [ ROOT.TFile.Open(item) for item in files if os.path.isfile(item) ]
        for name in objects:
            index = objects.index(name)
            meta = self.openedFiles[index].Get(name)
            if meta.__nonzero__():
                self.loaded[meta] = names[index]
            else:
                print "could not load %s from %s" % (name,files[index])
        
        return 0

    def initDictFromDatabase(self):
        """
        function to load loaded from objectDB
        """
        self.loaded = {}
        self.loadedKeys = {}
        for key,value in self.objectDB.loadedDict.iteritems():
            for item in value:
                self.loaded[item] = key

        for sec in self.objectDB.cfgParser.sections():
            self.loadedKeys[sec] = {}
            for k,v in self.objectDB.cfgParser.items(sec):
                if v.lower().count(".root"):
                    continue
                else:
                    self.loadedKeys[sec][k] = v

        return 0

    def collectData(self):

        self.nBins = len(self.loadedKeys.keys())

        centralValueObjs = [ item.Get("centralValues") for item in self.openedFiles if item.Get("centralValues").__nonzero__() ]
        if len(centralValueObjs):
            self.nFits = centralValueObjs[0].GetNbinsX()
            for item in range(1,self.nFits+1):
                self.fitNames.append(str(centralValueObjs[0].GetXaxis().GetBinLabel(item)))

                
        for item,content in self.loadedKeys.keys():
            if content.has_key("binID"):
                self.BinBorders.insert(float(content["binID"]))
            elif content.has_key("binValue"):
                self.BinBorders.insert(float(content["binValue"].split(",")[0]))
                if len(content["binValue"].split(","))>1:
                    self.BinBorders.insert(float(content["binValue"].split(",")[-1]))
                

        self.UpperBinLimit = max(self.BinBorders)
        self.LowerBinLimit = min(self.BinBorders)
        
        return

    def createResultHistos(self):
        
        return

    def fillResultHistos(self):
        return
    
    def writeAll(self):
        return
    

    def Run(self):

        if not self.loaded:
            print "no objects loaded"
            return
            

        try:
            self.collectData()
        except Exception:
            print "collectData failed due to ",Exception

        try:
            self.createResultHistos()
        except Exception:
            print "createResultHistos failed due to ",Exception
            
        try:
            self.fillResultHistos()
        except Exception:
            print "fillResultHistos failed due to ",Exception

        try:
            self.writeAll()
        except Exception:
            print "writeAll failed due to ",Exception
            
        
        # nfile = ROOT.TFile.Open(self.outputname,"RECREATE")

        # for key,value in self.loaded.iteritems():
        #     meta = key.Clone(value)
        #     meta.SetDirectory(nfile)
        #     print "adding %s to %s" % (value,self.outputname)
        #     meta.Write()

        # nfile.Close()
        # self.objectDB.close()
        # if self.openedFiles:
        #     [ item.Close() for item in self.openedFiles ]

if __name__=="__main__":
    #initialize from command line options
    
    bundler = BundleHistos()
    
    try: 
        bundler.initFromInput()
    except:
        print "FAILED TO INIT HISTOS!"
        sys.exit(-1)
    else:
        try:
            bundler.Run()
        except:
            sys.exit(-1)
        else:
            sys.exit(0)
        

