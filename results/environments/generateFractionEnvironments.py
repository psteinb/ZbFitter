import os,sys

contents = { 'b' : 43, 'c' : 14.9 , 'l' : 7.6 }
total = sum(contents.values())

for i in [.50,.75,1.00,1.25,1.50]:
    newContents = dict(contents)
    newContents['b'] *= i
    total = sum(newContents.values())
    print "\n"
    for k,v in newContents.iteritems():
        print "%.2f: %s = %.4f (%f)" % (i,k,v/total,v)
