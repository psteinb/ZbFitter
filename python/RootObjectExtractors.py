import os,math,sys

# if os.getenv("SRC"):
#     sys.path.append("/home/psteinb/current/plots/python")

if not 'gROOT' in dir():
    import ROOT
    sys.path.append("/home/psteinb/bin/atlasstyle-trunk")
    import AtlasStyle
    ROOT.gROOT.SetBatch(True)
    ROOT.gROOT.SetStyle(AtlasStyle.AtlasStyle().GetName())
    ROOT.gROOT.ForceStyle()

class BaseExtractor:
    """base class to put extraction in order

    """
    
    def __init__(self, _name = "BaseExtractor"):
        """empty initialisatn, call setup method instead
        """
        self.name = _name
        self.histo = None
        self.valid = False

    def setup(self, _histo = None):
        """ setup the root object here """
        pass

    def value(self):
        
        pass

    def error(self):
        
        pass


    def getName(self):
        return self.name

    def setName(self, _text = None):
        self.name = _text

    def setHisto(self,_histo):
        """small method to set the histogram
        """
        if _histo and _histo.__nonzero__():
            self.histo = _histo
            self.valid = True
        else:
            print "%s::\t could not setup histo for %s" % (self,self.name)
            return

    def getHisto(self):
        """histo getter"""
        if self.valid:
            return self.histo
        else:
            return None
 
    
class XaxisBinExtractor(BaseExtractor):
    
    def __init__(self,_binNumber=-1):
        self.setName("XaxisBinExtractor")
        self.binNumber = _binNumber

    def setup(self, _histo = None):
        """ setup the root object here """
        self.setHisto(_histo)

        if not (self.binNumber in range(0,self.getHisto().GetXaxis().GetLast()+2)):
            print "BinExtractor::\t given binNumber %i not found on xaxis [%i,%i] for %s" % (self.binNumber,0,self.getHisto().GetXaxis().GetLast()+1,self.name)
            return
        else:
            self.valid = True

        return 

    def value(self):
        
        if self.valid:
            self.result = self.getHisto().GetBinContent(self.binNumber)
            return self.result
        else:
            print "BinExtractor::\t extractor %s invalid" % self.name
            return 0.

    def error(self):
        
        if self.valid:
            self.resultError = self.getHisto().GetBinError(self.binNumber)
            return self.resultError
        else:
            print "BinExtractor::\t extractor %s invalid" % self.name
            return 0.

class MeanExtractor(BaseExtractor):
    
    def __init__(self):
        self.setName("MeanExtractor")

    def setup(self, _histo = None):
        """ setup the root object here """
        
        if _histo and isinstance(_histo,ROOT.TH1):
            self.setHisto(_histo)
            self.valid = True
            self.result = _histo.GetMean()
            self.resultError = _histo.GetMeanError()
        else:
            self.valid = False
        
        return 

    def value(self):
        
        if self.valid:
            return float(self.result)
        else:
            print "MeanExtractor::\t extractor %s invalid" % self.name
            return 0.

    def error(self):
        
        if self.valid:
            return float(self.resultError)
        else:
            print "MeanExtractor::\t extractor %s invalid" % self.name
            return 0.

class MeanUncFromHiddenExtractor(BaseExtractor):
    
    def __init__(self, _uncObjectName="sigma_par0"):
        self.uncObjectName = _uncObjectName
        self.setName("MeanUncFromHiddenExtractor")

    def setup(self, _histo = None):
        """ setup the root object here """
        
        if _histo and isinstance(_histo,ROOT.TH1):
            self.setHisto(_histo)

            self.result = _histo.GetMean()
            if self.uncObjectName:
                self.uncObject = _histo.GetDirectory().Get(self.uncObjectName)
                
            if self.uncObject:
                self.resultError = self.uncObject.GetMean()
                
            if _histo and self.uncObject:
                self.valid = True
        else:
            self.valid = False
        
        return 

    def value(self):
        
        if self.valid:
            return float(self.result)
        else:
            print "MeanUncFromHiddenExtractor::\t extractor %s invalid" % self.name
            return 0.

    def error(self):
        
        if self.valid:
            return float(self.resultError)
        else:
            print "MeanUncFromHiddenExtractor::\t extractor %s invalid" % self.name
            return 0.




class TotalIntegralExtractor(BaseExtractor):
    
    def __init__(self):
        self.setName("TotalIntegralExtractor")
        

    def setup(self, _histo = None):
        """ setup the root object here """
        if _histo and _histo.__nonzero__():
            self.setHisto(_histo)
            self.resultError = ROOT.Double()
            first = self.getHisto().GetXaxis().GetFirst()
            last  = self.getHisto().GetXaxis().GetLast()
            self.result = self.getHisto().IntegralAndError(first,last,self.resultError)
            #print "%s: int = %f, err = %f" % (self.getName(),self.result,self.resultError)
        else:
            print "IntegralExtractor::\t could not setup histo for %s" % (self.name)
            return
        
        return 

    def value(self):
        
        if self.valid:
            return float(self.result)
        else:
            print "IntegralExtractor::\t extractor %s invalid" % self.name
            return 0.

    def error(self):
        
        if self.valid:
            return float(self.resultError)
        else:
            print "IntegralExtractor::\t extractor %s invalid" % self.name
            return 0.
        
        
def createExtractor(_text=None):
        
    aExtractor = None

    if _text:
        try:
            aExtractor = eval(_text)
        except:
            print __file__," >> call to %s failed!" % _text
        else:
            print __file__," >> call to %s succeeded\n>> created %s" % (_text,aExtractor)
    else:
        print __file__,"no code given!!"

    return aExtractor
