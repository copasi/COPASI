# -*- coding: utf-8 -*-
# Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 




#  
#  This is an example on how to calculate and output the Jacobian matrix
#  in COPASI
#  
from COPASI import *
import sys


MODEL_STRING = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n <!-- Created by COPASI version 4.5.31 (Debug) on 2010-05-11 13:40 with libSBML version 4.1.0-b3. -->\n <sbml xmlns=\"http://www.sbml.org/sbml/level2/version4\" level=\"2\" version=\"4\">\n <model metaid=\"COPASI1\" id=\"Model_1\" name=\"New Model\">\n <listOfUnitDefinitions>\n <unitDefinition id=\"volume\" name=\"volume\">\n <listOfUnits>\n <unit kind=\"litre\" scale=\"-3\"/>\n </listOfUnits>\n </unitDefinition>\n <unitDefinition id=\"substance\" name=\"substance\">\n <listOfUnits>\n <unit kind=\"mole\" scale=\"-3\"/>\n </listOfUnits>\n </unitDefinition>\n <unitDefinition id=\"unit_0\">\n <listOfUnits>\n <unit kind=\"second\" exponent=\"-1\"/>\n </listOfUnits>\n </unitDefinition>\n </listOfUnitDefinitions>\n <listOfCompartments>\n <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n </listOfCompartments>\n <listOfSpecies>\n <species metaid=\"COPASI2\" id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\"/>\n <species metaid=\"COPASI3\" id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"0\"/>\n <species metaid=\"COPASI4\" id=\"species_3\" name=\"C\" compartment=\"compartment_1\" initialConcentration=\"0\"/>\n </listOfSpecies>\n <listOfReactions>\n <reaction metaid=\"COPASI5\" id=\"reaction_1\" name=\"reaction_1\" reversible=\"false\">\n <listOfReactants>\n <speciesReference species=\"species_1\"/>\n </listOfReactants>\n <listOfProducts>\n <speciesReference species=\"species_2\"/>\n </listOfProducts>\n <kineticLaw>\n <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n <apply>\n <times/>\n <ci> compartment_1 </ci>\n <ci> k1 </ci>\n <ci> species_1 </ci>\n </apply>\n </math>\n <listOfParameters>\n <parameter id=\"k1\" name=\"k1\" value=\"0.2\" units=\"unit_0\"/>\n </listOfParameters>\n </kineticLaw>\n </reaction>\n <reaction metaid=\"COPASI6\" id=\"reaction_2\" name=\"reaction_2\" reversible=\"false\">\n <listOfReactants>\n <speciesReference species=\"species_2\"/>\n </listOfReactants>\n <listOfProducts>\n <speciesReference species=\"species_3\"/>\n </listOfProducts>\n <kineticLaw>\n <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n <apply>\n <times/>\n <ci> compartment_1 </ci>\n <ci> k1 </ci>\n <ci> species_2 </ci>\n </apply>\n </math>\n <listOfParameters>\n <parameter id=\"k1\" name=\"k1\" value=\"0.1\" units=\"unit_0\"/>\n </listOfParameters>\n </kineticLaw>\n </reaction>\n </listOfReactions>\n </model>\n </sbml>\n"


def main():
    assert CRootContainer.getRoot() != None
    # create a new datamodel
    dataModel = CRootContainer.addDatamodel()
    assert dataModel != None
    assert CRootContainer.getDatamodelList().size() == 1
    # next we import a simple SBML model from a string

    # clear the message queue so that we only have error messages from the import in the queue
    CCopasiMessage.clearDeque()
    result=True
    try:
      result = dataModel.importSBMLFromString(MODEL_STRING)
    except:
        sys.stderr.write("Import of model failed miserably.\n")
        return
    # check if the import was successful
    mostSevere = CCopasiMessage.getHighestSeverity()
    # if it was a filtered error, we convert it to an unfiltered type
    # the filtered error messages have the same value as the unfiltered, but they
    # have the 7th bit set which basically adds 128 to the value
    mostSevere = mostSevere & 127

    # we assume that the import succeeded if the return value is True and
    # the most severe error message is not an error or an exception
    if result != True and  mostSevere < CCopasiMessage.ERROR:
        sys.stderr.write("Sorry. Model could not be imported.\n")
        return

    #
    # now we tell the model object to calculate the jacobian
    #
    model = dataModel.getModel()
    assert model != None

    if model != None:
        # running a task, e.g. a trajectory will automatically make sure that
        # the initial values are transferred to the current state before the calculation begins.
        # If we use low level calculation methods like the one to calculate the jacobian, we
        # have to make sure the the initial values are applied to the state
        model.applyInitialValues()
        # we need an array that stores the result
        # the size of the matrix does not really matter because
        # the calculateJacobian autoamtically resizes it to the correct
        # size
        jacobian=FloatMatrix()
        # the first parameter to the calculation function is a reference to
        # the matrix where the result is to be stored
        # the second parameter is the derivationFactor for the calculation
        # it basically represents a relative delta value for the calculation of the derivatives
        # the third parameter is a boolean indicating whether the jacobian should
        # be calculated from the reduced (true) or full (false) system
        model.getMathContainer().calculateJacobian(jacobian, 1e-12, False)
        # now we print the result
        # the jacobian stores the values in the order they are
        # given in the user order in the state template so it is not really straight
        # forward to find out which column/row corresponds to which species
        stateTemplate = model.getStateTemplate()
        # and we need the user order
        userOrder = stateTemplate.getUserOrder()
        # from those two, we can construct an new vector that contains
        # the names of the entities in the jacobian in the order in which they appear in
        # the jacobian
        nameVector=[]
        entity = None
        status=-1

        for i in range(0,userOrder.size()):
            entity = stateTemplate.getEntity(userOrder.get(i))
            assert entity != None
            # now we need to check if the entity is actually
            # determined by an ODE or a reaction
            status = entity.getStatus()

            if (status == CModelEntity.Status_ODE or (status == CModelEntity.Status_REACTIONS and entity.isUsed())):
                nameVector.append(entity.getObjectName())

        assert len(nameVector) == jacobian.numRows()
        # now we print the matrix, for this we assume that no
        # entity name is longer then 5 character which is a save bet since
        # we know the model
        print ("Jacobian Matrix:")
        print ("")
        row = "%7s" % (" ")

        for i in range(0,len(nameVector)):
            row = row + " %7s" % (nameVector[i])

        print (row)

        for i in range(0,len(nameVector)):
            row = "%7s" % (nameVector[i])

            for j in range(0,len(nameVector)):
                row = row + " %7.3f" % (jacobian.get(i,j))

            print (row)

        # we can also calculate the jacobian of the reduced system
        # in a similar way
        model.getMathContainer().calculateJacobian(jacobian, 1e-12, True)
        # this time generating the output is actually simpler because the rows
        # and columns are ordered in the same way as the independent variables of the state temple
        print ("")
        print ("")
        print ("Reduced Jacobian Matrix:")
        print ("")
        row = "%7s" % (" ")
        
        iMax = stateTemplate.getNumIndependent()
        
        for i in range(0,iMax):
          row = row + " %7s" % (stateTemplate.getIndependent(i).getObjectName())

        print (row)

        for i in range(0,iMax):
            row = "%7s" % (stateTemplate.getIndependent(i).getObjectName())

            for j in range(0,iMax):
                row = row + " %7.3f" % (jacobian.get(i,j))

            print (row)

if(__name__ == '__main__'):
   main() 

