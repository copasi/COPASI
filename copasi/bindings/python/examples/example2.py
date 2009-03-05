#
# This is an example on how to load a cps file
# and output some information on the model
#

import sys
from COPASI import *
from types import *

def main(args):
    assert CCopasiRootContainer.getRoot() != None
    # create a datamodel
    dataModel = CCopasiRootContainer.addDatamodel()
    assert CCopasiRootContainer.getDatamodelList().size() == 1
    # the only argument to the main routine should be the name of a CPS file
    if (len(args) == 1):
        filename = args[0]
        try:
            # load the model without progress report
            dataModel.loadModel(filename)
        except:
            print >> sys.stderr, "Error while loading the model from file named \"" + filename + "\"."
            return 1
        model = dataModel.getModel()
        assert model != None
        print "Model statistics for model \"" + model.getObjectName() + "\"."

        # output number and names of all compartments
        iMax = model.getCompartments().size()
        print "Number of Compartments: " , iMax
        print "Compartments: "
        for i in range(0,iMax): 
            compartment = model.getCompartment(i)
            assert compartment != None
            print "\t" + compartment.getObjectName()

        # output number and names of all metabolites
        iMax = model.getMetabolites().size()
        print "Number of Metabolites: " , iMax
        print "Metabolites: "
        for i in range(0,iMax):
            metab = model.getMetabolite(i)
            assert metab != None
            print "\t" + metab.getObjectName()

        # output number and names of all reactions
        iMax = model.getReactions().size()
        print "Number of Reactions: " , iMax
        print "Reactions: "
        for i in range(0,iMax):
            reaction = model.getReaction(i)
            assert reaction != None
            print "\t" + reaction.getObjectName()
    else:
        print >> sys.stderr, "Usage: example2 CPSFILE"
        return 1

if(__name__ == '__main__'):
   main(sys.argv[1:]) 



