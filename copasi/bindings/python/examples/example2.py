# -*- coding: utf-8 -*-
# Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 


#
# This is an example on how to load a cps file
# and output some information on the model
#

import sys
from COPASI import *
from types import *

def main(args):
    assert CRootContainer.getRoot() != None
    # create a datamodel
    dataModel = CRootContainer.addDatamodel()
    assert CRootContainer.getDatamodelList().size() == 1
    # the only argument to the main routine should be the name of a CPS file
    if (len(args) == 1):
        filename = args[0]
        try:
            # load the model without progress report
            dataModel.loadModel(filename)
        except:
            sys.stderr.write("Error while loading the model from file named \"" + filename + "\".\n")
            return 1
        model = dataModel.getModel()
        assert model != None
        print ("Model statistics for model \"" + model.getObjectName() + "\".")

        # output number and names of all compartments
        iMax = model.getCompartments().size()
        print ("Number of Compartments: " , iMax)
        print ("Compartments: ")
        for i in range(0,iMax): 
            compartment = model.getCompartment(i)
            assert compartment != None
            print ("\t" + compartment.getObjectName())

        # output number and names of all metabolites
        iMax = model.getMetabolites().size()
        print ("Number of Metabolites: " , iMax)
        print ("Metabolites: ")
        for i in range(0,iMax):
            metab = model.getMetabolite(i)
            assert metab != None
            print ("\t" + metab.getObjectName())

        # output number and names of all reactions
        iMax = model.getReactions().size()
        print ("Number of Reactions: " , iMax)
        print ("Reactions: ")
        for i in range(0,iMax):
            reaction = model.getReaction(i)
            assert reaction != None
            print ("\t" + reaction.getObjectName())
    else:
        sys.stderr.write("Usage: example2 CPSFILE\n")
        return 1

if(__name__ == '__main__'):
   main(sys.argv[1:]) 



