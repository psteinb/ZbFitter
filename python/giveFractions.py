import os,sys,ROOT,math


def listObjectNames(_afile=None):
    """function to return a list of all object names
    """
    listPrim = _afile.GetListOfKeys()
    return [ item.GetName() for item in listPrim if item.ReadObj() ]

        
if __name__ == '__main__':
    
    if '-h' in sys.argv or '--help' in sys.argv:
        print "joinContentSideBySide"
        print "usage: joinContentSideBySide.py <file1> <objects>"
        sys.exit(1)

    if len(sys.argv[1:])!=2:
        print "error: not enough arguments"
        sys.exit(1)

    if not (os.path.exists(sys.argv[1])):
        print "error: files do not exist",sys.argv[1]
        sys.exit(1)

    file1 = ROOT.TFile(sys.argv[1])
    listOfNames = listObjectNames(file1)
    
    list2check = sys.argv[2].split(",")
    selectedNames = [ item for item in listOfNames if item in list2check ]
    data = [ item for item in listOfNames if item.lower().count("data") ]
    if data:
        dataHisto = file1.Get(data[0])

    selectedObjects = [ file1.Get(item) for item in selectedNames if file1.Get(item).__nonzero__()]

    integrals = [ float(item.Integral()) for item in selectedObjects]
    total = sum(integrals)

    for idx in range(len(selectedObjects)):
        ratio = float(integrals[idx]/total)
        print "%10s: %.2f/%.2f\t= %.4f [to data: %.2f]" % (selectedNames[idx],integrals[idx],total,ratio,ratio*dataHisto.Integral())
     
    file1.Close()
