import ROOT
import os,sys,re

sys.path.append("/home/psteinb/bin/")
import setupATLASRootStyle

from ConfigParser import *

class RootObjectLoader:
    """
    python class that allows reading a file descriminating files to open and which TNameds to load
    the file names may contain place holders __FOO__  that will be replaced by their corresponding shell variable, if it exists
    """
    
    def __init__(self, _configFile=""):
        """
        
        Arguments:
        - `_configFile`:
        """
        self.cfgParser = ConfigParser()
        self.tFiles = {}
        self.loadedDict = {}
        self.setConfigFile(_configFile)

    def setConfigFile(self,_cfile):
        if os.path.isfile( _cfile ):
            self.__configFile = _cfile
            self.cfgParser.read(_cfile)
        else:
            #print _cfile," not found"
            self.__configFile = None

        
    def findDirString(self,_string):
        """ small function to extract a string of the format __FOO__ from the given string """
        start = _string.find("__")
        end = _string.find("__",start+1)+2
        return _string[start:end]

    def getDirFromEnvironment(self,_string):
        """ return the directory given by _string environment variable if it exists """
        env = os.getenv(_string)
        if env and os.path.isdir(env.split(":")[0]):
            return env.split(":")[0]
        else:
            print "no directory extracted from ", _string
            return None

    def replaceDirString(self,_filestring):
        """ search the _filestring for  __FOO__ and replace it with the directory given by $FOO """
        value = _filestring
        if _filestring.count("__")>1:
            placeHolder = self.findDirString(_filestring)
            dirname = self.getDirFromEnvironment(placeHolder[2:-2])
            if dirname:
                value = _filestring.replace(placeHolder,dirname)
            else:
                print "no directory found according to ", placeHolder
            return value
        else:
            #print "nothing found"
            return value


    def close(self):
        """ close all associated files """
        for i in self.tFiles.values():
            for o in i:
                if o.__nonzero__():
                    o.Close()

  
    def openFiles(self,_verbose=False):
        """ open all files given """
        
        for sec in self.cfgParser.sections():
            self.loadedDict[sec] = []
            self.tFiles[sec] = []
            commands = []
            for k,v in self.cfgParser.items(sec):

                if not v.count(".root") and v.count("[]."):
                    commands.append(v)
                    continue

                fileName = self.replaceDirString(v.split(":")[0])
                currFile = None
                if fileName and os.path.isfile(fileName):
                    currFiles = [ item for item in self.tFiles[sec] if item.GetName().count(fileName.split("/")[-1]) ]
                    if not currFiles:
                        self.tFiles[sec].append(ROOT.TFile(fileName))
                        currFile = self.tFiles[sec][-1]
                    else:
                        currFile = currFiles[0]
                else:
                    print fileName, " does not exist"
                    continue

                if not currFile:
                    print "%s not loaded" % fileName
                    continue

                tnamed = currFile.Get(v.split(":")[-1])
                if tnamed.__nonzero__():
                    self.loadedDict[sec].append(tnamed)
#                    print ">> object %s found in %s " % (v.split(":")[0],v.split(":")[-1])
                else:
                    print ">> object %s not found in %s " % (v.split(":")[-1],fileName)

            for loaded in self.loadedDict[sec]:
                if not loaded.__nonzero__():
                    continue 

                for cmd in commands:
                    try:
                        eval(cmd.replace("[]","loaded"))
                    except Exception as inst:
                        print "unable to execute %s on %s" % (cmd,loaded.GetName())
                    

        if _verbose:
            self.printLoadedObjects()
        

    def printLoadedObjects(self):
        """ print out all loaded objects """
        for k,v in self.loadedDict.iteritems():
            print ">> loaded %s from %s" % (k,self.__configFile)
            for i in v:
                print "\t%s : %s" % (i.GetDirectory().GetFile().GetName(),i.GetName())

        
if __name__ == '__main__':
    
    if '-h' in sys.argv or '--help' in sys.argv and len(sys.argv[1:])!=1:
        print "test usage: RootObjectLoader.py <configFile>"
        sys.exit(1)

        
    if os.path.isfile(sys.argv[1]):
        loader = RootObjectLoader(sys.argv[1])
        try:
            loader.openFiles()
        except Exception as exc:
            print "RootObjectLoader failed due to\n%s(%i >> %i)\t> %s <" % (__file__,sys.exc_info()[-1].tb_lineno,sys.exc_info()[-1].tb_next.tb_lineno,str(exc))
            exitCode = 1
        else:
            exitCode = 0
        finally:
            loader.close()
            sys.exit(exitCode)

        

        
