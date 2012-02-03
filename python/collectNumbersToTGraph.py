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
from RootObjectExtractors import *

class BundleHistos:
    
    def __init__(self):
        self.usage = "usage: collectNumbersToTGraph.py [options]"
        #define the parser with options only relevant for the digester
        self.parser = OptionParser(self.usage)
        self.parser.add_option("-f", "--file", dest="filename",action="store",
                               help="ini file(s) to read root object from ")
        self.parser.add_option("-o", "--outputname", dest="outputname",action="store",
                               default="./fitterInputs.root", help="name of root file to dump to")
        self.parser.add_option("-l", "--fileHistoList", dest="fileHistoList",action="store",
                               help="semi colon separated list of triple <file:histoName:newName>")
        self.parser.add_option("-E", "--extractor", dest="extractor",action="store",
                               help="extractor object to use on inline histo for value,error yields, see %s/python/RootObjectExtractors.py for details" % basePath)

        self.objectDB         = RootObjectLoader()
        self.configFile = None
        self.fileHistoList    = []
        self.outputname = None
        self.dictToWrite = None
        self.openedFiles = []
        self.extractor = None
        self.extractorString = "TotalIntegralExtractor()"

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

        if self.parsedOpts['extractor']:
            self.extractorString = self.parsedOpts['extractor']
            

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
        self.extractor = createExtractor(self.extractorString)
        self.openedFiles = [ ROOT.TFile.Open(item) for item in files if os.path.isfile(item) ]
        for name in objects:
            index = objects.index(name)
            meta = self.openedFiles[index].Get(name)
            if meta.__nonzero__():
                self.dictToWrite[names[index]] = meta
            else:
                print "could not load %s from %s" % (name,files[index])
        
        return 0

    def initDictFromDatabase(self):
        """
        function to load dictToWrite from objectDB
        """
        self.dictToWrite = {}
        #print self.objectDB.loadedCommands
        for key,value in self.objectDB.loadedDict.iteritems():
            for item in value:
                self.dictToWrite[key] = item

            # if self.objectDB.loadedCommands.has_key(key):
            #     for cmd in self.objectDB.loadedCommands[key]:
            #         try:
            #             eval(cmd.replace("[]","self.dictToWrite["+key+"]"))
            #         except:
            #             print ">> command %s failed on object named [%s], %s" % (cmd,key,self.dictToWrite[key].GetName())
            #         else:
            #             print ">> command %s succeeded for [%s]" % (cmd,key)
            # else:
            #     print ">> no commands found for ",key
        return 0

    def getXValueForKey(self,_key):
        
        section = self.objectDB.cfgParser.items(_key)
        
        if not section:
            print "command DB does not contain key ", _key
            print self.objectDB.cfgParser
            return None

        xvalKeys = [ v for (k,v) in section if k.lower().count("x") and k.lower().count("value") ]

        if not xvalKeys:
            print "no xvalue keys found in command section for ", _key
            print section
            return None
        else:
            return float(xvalKeys[0])
        
        
    def Run(self):

        if not self.dictToWrite:
            print "no objects loaded"
            return
        
            
        nfile = ROOT.TFile.Open(self.outputname,"RECREATE")
        tgre = ROOT.TGraphErrors(len(self.dictToWrite.keys()))

        points = []


        for key,value in self.dictToWrite.iteritems():
            print "procesing ",key

            xvalue = self.getXValueForKey(key)
            if not xvalue:
                print "no xvalue found!"
                continue

            section = [ v for (k,v) in self.objectDB.cfgParser.items(key) if v.lower().count("extractor") ]
            if section:
                self.extractorString = section[0]
                self.extractor = createExtractor(self.extractorString)

            self.extractor.setup(value)
            central,error = self.extractor.value(),self.extractor.error()
            print ">> x = %f, y = (%f +/- %f)" % (xvalue,central,error)
            points.append((xvalue,central,error))

        
        for p in sorted(points, key=lambda x: x[0],reverse=False):
            tgre.SetPoint(points.index(p),p[0],p[1])
            tgre.SetPointError(points.index(p),0.,p[-1])

        #draw everything
        acanvas = ROOT.TCanvas(self.outputname.split("/")[-1].replace(".root",""),"",800,600)
        acanvas.Clear()
        acanvas.Draw()
        
        tgre.Draw("AP")
        
        acanvas.Update()
        acanvas.Print(".eps")
        acanvas.SaveAs(self.outputname.replace(".root",".C"))
        tgre.SaveAs(self.outputname.replace(".root","_graph.root"))
        
        
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
        bundler.Run()
        

