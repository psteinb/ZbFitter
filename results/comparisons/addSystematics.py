import os,ROOT

def listObjectNames(_afile=None):
    """function to return a list of all object names
    """
    listPrim = _afile.GetListOfKeys()
    return [ item.GetName() for item in listPrim if item.ReadObj() ]

        
if __name__ == '__main__':
    
    if '-h' in sys.argv or '--help' in sys.argv:
        print "usage: %s <NameItemIdx> <file1> <file2> ..." % __file__
        print "\t <NameItemIdx> refers to the position of a string in in the filename if subject ot a split('_') call " 
        sys.exit(1)

    if not (len(sys.argv[1:])>2):
        print "error: wrong input"
        print "usage: %s <NameItemIdx> <file1> <file2> ..." % __file__
        print "\t <NameItemIdx> refers to the position of a string in in the filename if subject ot a split('_') call " 
        sys.exit(1)

    files2open = []

    for item in sys.argv[2:]:
        if os.path.exists(item):
            files2open.append(str(item))
        else:
            print "error: %s does not exist" % (item)


    if sys.argv[1]:
        idx = int(sys.argv[1])
    else:
        idx = -1

    rootfiles = [ ROOT.TFile(item) for item in files2open ]
    fileItems = [ item.rstrip(".root").split("_")[idx] for item in files2open ]

    newName = "AllSystematicErrors.root"
    fileNew = ROOT.TFile(newName,"RECREATE")

#    listOfNames = listObjectNames(file1)
    
    for rfile in rootfiles:
        index = rootfiles.index(rfile)
        print ">>> processing %s " % (rfile.GetName())
        lTObjects = listObjectNames(rfile)
        
        for name in lTObjects:
            obj = rfile.Get(name)
            if obj.__nonzero__():
                nObj = obj.Clone(fileItems[index]+"_"+name)
                nObj.SetDirectory(fileNew.GetDirectory(""))
                nObj.Write()
            else:
                print name," could not be loaded from ",rfile.GetName()

    
     

    

    fileNew.Close()
    for item in rootfiles:
        item.Close()
