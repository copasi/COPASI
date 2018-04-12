# -*- coding: utf-8 -*-
# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
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





# This is an example on how to build models with the COPASI backend API.

from COPASI import *
from types import *
import sys 

def main():
  assert CRootContainer.getRoot() != None
  # create a new datamodel
  dataModel = CRootContainer.addDatamodel()
  assert CRootContainer.getDatamodelList().size() == 1
  # get the model from the datamodel
  model = dataModel.getModel()
  assert model != None
  # set the units for the model
  # we want seconds as the time unit
  # microliter as the volume units
  # and nanomole as the substance units
  model.setTimeUnit(CUnit.s)
  model.setVolumeUnit(CUnit.microl)
  model.setQuantityUnit(CUnit.nMol)

  # we have to keep a set of all the initial values that are changed during
  # the model building process
  # They are needed after the model has been built to make sure all initial
  # values are set to the correct initial value
  changedObjects=ObjectStdVector()

  # create a compartment with the name cell and an initial volume of 5.0
  # microliter
  compartment = model.createCompartment("cell", 5.0)
  object = compartment.getInitialValueReference()
  assert object != None
  changedObjects.push_back(object)
  assert compartment != None
  assert model.getCompartments().size() == 1
  # create a new metabolite with the name glucose and an inital
  # concentration of 10 nanomol
  # the metabolite belongs to the compartment we created and is is to be
  # fixed
  glucose = model.createMetabolite("glucose", compartment.getObjectName(), 10.0, CModelEntity.Status_FIXED)
  assert glucose != None
  object = glucose.getInitialConcentrationReference()
  assert object != None
  changedObjects.push_back(object)
  assert model.getMetabolites().size() == 1
  # create a second metabolite called glucose-6-phosphate with an initial
  # concentration of 0. This metabolite is to be changed by reactions
  g6p = model.createMetabolite("glucose-6-phosphate", compartment.getObjectName(), 0.0, CModelEntity.Status_REACTIONS)
  assert g6p != None
  object = g6p.getInitialConcentrationReference()
  assert object != None
  changedObjects.push_back(object)
  assert model.getMetabolites().size() == 2
  # another metabolite for ATP, also fixed
  atp = model.createMetabolite("ATP", compartment.getObjectName(), 10.0, CModelEntity.Status_FIXED)
  assert atp != None
  object = atp.getInitialConcentrationReference()
  assert object != None
  changedObjects.push_back(object)
  assert model.getMetabolites().size() == 3
  # and one for ADP
  adp = model.createMetabolite("ADP", compartment.getObjectName(), 0.0, CModelEntity.Status_REACTIONS)
  assert adp != None
  object = adp.getInitialConcentrationReference()
  assert object != None
  changedObjects.push_back(object)
  assert model.getMetabolites().size() == 4
  # now we create a reaction
  reaction = model.createReaction("hexokinase")
  assert reaction != None
  assert model.getReactions().size() == 1
  # hexokinase converts glucose and ATP to glucose-6-phosphate and ADP
  # we can set these on the chemical equation of the reaction
  chemEq = reaction.getChemEq()
  # glucose is a substrate with stoichiometry 1
  chemEq.addMetabolite(glucose.getKey(), 1.0, CChemEq.SUBSTRATE)
  # ATP is a substrate with stoichiometry 1
  chemEq.addMetabolite(atp.getKey(), 1.0, CChemEq.SUBSTRATE)
  # glucose-6-phosphate is a product with stoichiometry 1
  chemEq.addMetabolite(g6p.getKey(), 1.0, CChemEq.PRODUCT)
  # ADP is a product with stoichiometry 1
  chemEq.addMetabolite(adp.getKey(), 1.0, CChemEq.PRODUCT)
  assert chemEq.getSubstrates().size() == 2
  assert chemEq.getProducts().size() == 2
  # this reaction is to be irreversible
  reaction.setReversible(False)
  assert reaction.isReversible() == False
  # now we ned to set a kinetic law on the reaction
  # maybe constant flux would be OK
  # we need to get the function from the function database
  funDB = CRootContainer.getFunctionList()
  assert funDB != None
  # it should be in the list of suitable functions
  # lets get all suitable functions for an irreversible reaction with  2 substrates
  # and 2 products
  suitableFunctions = funDB.suitableFunctions(2, 2, TriFalse)
  assert len(suitableFunctions) > 0
  function=None
  for f in suitableFunctions:
      # we just assume that the only suitable function with Constant in
      # it's name is the one we want
      if f.getObjectName().find("Constant") != -1:
          function=f
          break
  if function:
      # we set the function
      # the method should be smart enough to associate the reaction entities
      # with the correct function parameters
      reaction.setFunction(function)
      assert reaction.getFunction() != None
      # constant flux has only one function parameter
      assert reaction.getFunctionParameters().size() == 1
      # so there should be only one entry in the parameter mapping as well
      assert len(reaction.getParameterObjects()) == 1
      parameterGroup = reaction.getParameters()
      assert parameterGroup.size() == 1
      parameter = parameterGroup.getParameter(0)
      # make sure the parameter is a local parameter
      assert reaction.isLocalParameter(parameter.getObjectName())
      # now we set the value of the parameter to 0.5
      parameter.setValue(0.5)
      object = parameter.getValueReference()
      assert object != None
      changedObjects.push_back(object)
  else:
      sys.stderr.write("Error. Could not find a kinetic law that contains the term \"Constant\".\n" )
      return 1
  # now we also create a separate reaction for the backwards reaction and
  # set the kinetic law to irreversible mass action
  # now we create a reaction
  reaction = model.createReaction("hexokinase-backwards")
  assert reaction != None
  assert model.getReactions().size() == 2
  chemEq = reaction.getChemEq()
  # glucose is a product with stoichiometry 1
  chemEq.addMetabolite(glucose.getKey(), 1.0, CChemEq.PRODUCT)
  # ATP is a product with stoichiometry 1
  chemEq.addMetabolite(atp.getKey(), 1.0, CChemEq.PRODUCT)
  # glucose-6-phosphate is a substrate with stoichiometry 1
  chemEq.addMetabolite(g6p.getKey(), 1.0, CChemEq.SUBSTRATE)
  # ADP is a substrate with stoichiometry 1
  chemEq.addMetabolite(adp.getKey(), 1.0, CChemEq.SUBSTRATE)
  assert chemEq.getSubstrates().size() == 2
  assert chemEq.getProducts().size() == 2
  # this reaction is to be irreversible
  reaction.setReversible(False)
  assert reaction.isReversible() == False
  # now we ned to set a kinetic law on the reaction
  massAction = funDB.findFunction("Mass action (irreversible)")
  assert massAction != None
  # we set the function
  # the method should be smart enough to associate the reaction entities
  # with the correct function parameters
  reaction.setFunction(massAction)
  assert reaction.getFunction() != None

  assert reaction.getFunctionParameters().size() == 2
  # so there should be two entries in the parameter mapping as well
  assert len(reaction.getParameterObjects()) == 2
  # mass action is a special case since the parameter mappings for the
  # substrates (and products) are in a vector

  # Let us create a global parameter that is determined by an assignment
  # and that is used as the rate constant of the mass action kinetics
  # it gets the name rateConstant and an initial value of 1.56
  modelValue = model.createModelValue("rateConstant", 1.56)
  assert modelValue != None
  object = modelValue.getInitialValueReference()
  assert object != None
  changedObjects.push_back(object)
  assert model.getModelValues().size() == 1
  # set the status to assignment
  modelValue.setStatus(CModelEntity.Status_ASSIGNMENT)
  # the assignment does not have to make sense
  modelValue.setExpression("1.0 / 4.0 + 2.0")

  # now we have to adjust the parameter mapping in the reaction so
  # that the kinetic law uses the global parameter we just created instead
  # of the local one that is created by default
  # The first parameter is the one for the rate constant, so we point it to
  # the key of out model value
  reaction.setParameterObject(0, modelValue)
  # now we have to set the parameter mapping for the substrates
  reaction.addParameterObject("substrate", g6p)
  reaction.addParameterObject("substrate", adp)

  # finally compile the model
  # compile needs to be done before updating all initial values for
  # the model with the refresh sequence
  model.compileIfNecessary()

  # now that we are done building the model, we have to make sure all
  # initial values are updated according to their dependencies
  model.updateInitialValues(changedObjects);

  # save the model to a COPASI file
  # we save to a file named example1.cps, we don't want a progress report
  # and we want to overwrite any existing file with the same name
  # Default tasks are automatically generated and will always appear in cps
  # file unless they are explicitley deleted before saving.
  dataModel.saveModel("example1.cps", True)

  # export the model to an SBML file
  # we save to a file named example1.xml, we want to overwrite any
  # existing file with the same name and we want SBML L2V3
  dataModel.exportSBML("example1.xml", True, 2, 3)


if(__name__ == '__main__'):
   main() 


