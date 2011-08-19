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
        self.dictToWrite = None
        self.openedFiles = []

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
        function to load dictToWrite from list given by CLI
        """
        self.dictToWrite = {}
        files = [ item.split(":")[0] for item in _text.split(";") ]
        objects = [ item.split(":")[1] for item in _text.split(";") ]
        names = [ item.split(":")[2] for item in _text.split(";") ]
        self.openedFiles = [ ROOT.TFile.Open(item) for item in files if os.path.isfile(item) ]
        for name in objects:
            index = objects.index(name)
            meta = self.openedFiles[index].Get(name)
            if meta.__nonzero__():
                self.dictToWrite[meta] = names[index]
            else:
                print "could not load %s from %s" % (name,files[index])
        
        return 0

    def initDictFromDatabase(self):
        """
        function to load dictToWrite from objectDB
        """
        self.dictToWrite = {}
        for key,value in self.objectDB.loadedDict.iteritems():
            for item in value:
                self.dictToWrite[item] = key
        return 0

        
    def Run(self):

        if not self.dictToWrite:
            print "no objects loaded"
            return
            
        nfile = ROOT.TFile.Open(self.outputname,"RECREATE")

        for key,value in self.dictToWrite.iteritems():
            meta = key.Clone(value)
            meta.SetDirectory(nfile)
            print "adding %s to %s" % (value,self.outputname)
            meta.Write()

        nfile.Close()
        self.objectDB.close()
        if self.openedFiles:
            [ item.Close() for item in self.openedFiles ]

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
        

