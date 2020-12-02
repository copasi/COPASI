# -*- coding: utf-8 -*-
# Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

import COPASI
import unittest
from types import *

def createModel():
    datamodel=COPASI.CRootContainer.addDatamodel()
    model=datamodel.getModel()
    model.setVolumeUnit(COPASI.CUnit.fl)
    model.setTimeUnit(COPASI.CUnit.s)
    model.setQuantityUnit(COPASI.CUnit.fMol)
    comp=model.createCompartment("CompartmentA")
    A=model.createMetabolite("A",comp.getObjectName())
    B=model.createMetabolite("B",comp.getObjectName())
    react=model.createReaction("Decay_1")
    react.addSubstrate(A.getKey())
    react.addProduct(B.getKey())
    react.setReversible(False)
    react.setFunction("Mass action (irreversible)")
    mapping=COPASI.DataObjectVector()
    mapping.append(react.getChemEq().getSubstrate(0).getMetabolite())
    react.setParameterObjects(react.getFunction().getVariables().getParameter(1).getObjectName(),mapping);
    model.compileIfNecessary()

    A.setInitialConcentration(2.0e-4)    
    B.setInitialConcentration(0.0)
    react.setParameterValue("k1",0.5)
    changedObjects=COPASI.ObjectStdVector()
    changedObjects.push_back(comp.getObject(COPASI.CCommonName("Reference=InitialVolume")))
    changedObjects.push_back(A.getObject(COPASI.CCommonName("Reference=InitialConcentration")))
    changedObjects.push_back(B.getObject(COPASI.CCommonName("Reference=InitialConcentration")))
    model.updateInitialValues(changedObjects)

    return datamodel

def extendModel(datamodel):
    model=datamodel.getModel()
    metab=model.createMetabolite("C",model.getCompartment(0).getObjectName())
    react=model.createReaction("Decay_2")
    react.addSubstrate(model.getMetabolite(1).getKey())
    react.addProduct(metab.getKey())
    react.setReversible(False)
    react.setFunction("Mass action (irreversible)")
    mapping=COPASI.DataObjectVector()
    mapping.append(react.getChemEq().getSubstrate(0).getMetabolite())
    react.setParameterObjects(react.getFunction().getVariables().getParameter(1).getObjectName(),mapping);
    model.compileIfNecessary()
    metab.setInitialConcentration(0.0)
    react.getParameters().getParameter(0).setValue(0.1)
    changedObjects=COPASI.ObjectStdVector()
    changedObjects.push_back(metab.getObject(COPASI.CCommonName("Reference=InitialConcentration")))
    changedObjects.push_back(react.getParameters().getParameter(0).getObject(COPASI.CCommonName("Reference=Value")))
    model.updateInitialValues(changedObjects);


class Test_CreateSimpleModel(unittest.TestCase):
   def setUp(self):
    self.datamodel=createModel()
    self.model=self.datamodel.getModel()

   def test_createModel(self):
     self.assert_(self.model!=None)
     self.assert_(self.model.__class__==COPASI.CModel)
     self.assert_(self.model.getCompartments().size()==1)
     self.assert_(self.model.getCompartment(0).getObjectName()=="CompartmentA")
     self.assert_(self.model.getMetabolites().size()==2)
     self.assert_(self.model.getMetabolite(0).getObjectName()=="A")
     self.assertEquals(self.model.getMetabolite(0).getInitialConcentration(),2.0e-4)
     self.assert_(self.model.getMetabolite(1).getObjectName()=="B")
     self.assert_(self.model.getMetabolite(1).getInitialValue()==0.0)
     self.assert_(self.model.getReactions().size()==1)
     self.assert_(self.model.getReaction(0).getObjectName()=="Decay_1")
     self.assert_(self.model.getReaction(0).isReversible()==False)
     self.assert_(self.model.getReaction(0).getChemEq().getSubstrates().size()==1)
     self.assert_(self.model.getReaction(0).getChemEq().getSubstrate(0).getMetabolite().getObjectName()=="A")
     self.assert_(self.model.getReaction(0).getChemEq().getSubstrate(0).getMultiplicity()==1.0)
     self.assert_(self.model.getReaction(0).getChemEq().getProducts().size()==1)
     self.assert_(self.model.getReaction(0).getChemEq().getProduct(0).getMetabolite().getObjectName()=="B")
     self.assert_(self.model.getReaction(0).getChemEq().getProduct(0).getMultiplicity()==1.0)
     self.assert_(self.model.getReaction(0).getChemEq().getModifiers().size()==0)
     self.assert_(self.model.getReaction(0).getFunction()!=None)
     self.assert_(self.model.getReaction(0).getFunction().getObjectName()=="Mass action (irreversible)")
     self.assert_(self.model.getReaction(0).getParameters().size()==1)
     self.assert_(self.model.getReaction(0).getParameters().getParameter(0).getObjectName()=="k1")
     self.assert_(self.model.getReaction(0).getParameters().getParameter(0).getValue()==0.5)

   def test_extendModel(self):
     extendModel(self.datamodel) 
     self.assert_(self.model.getMetabolites().size()==3)
     self.assert_(self.model.getMetabolite(2).getObjectName()=="C")
     self.assertEquals(self.model.getMetabolite(2).getInitialValue(),0.0)
     self.assert_(self.model.getReactions().size()==2)
     self.assert_(self.model.getReaction(1).getObjectName()=="Decay_2")
     self.assert_(self.model.getReaction(1).isReversible()==False)
     self.assert_(self.model.getReaction(1).getChemEq().getSubstrates().size()==1)
     self.assert_(self.model.getReaction(1).getChemEq().getSubstrate(0).getMetabolite().getObjectName()=="B")
     self.assert_(self.model.getReaction(1).getChemEq().getSubstrate(0).getMultiplicity()==1.0)
     self.assert_(self.model.getReaction(1).getChemEq().getProducts().size()==1)
     self.assert_(self.model.getReaction(1).getChemEq().getProduct(0).getMetabolite().getObjectName()=="C")
     self.assert_(self.model.getReaction(1).getChemEq().getProduct(0).getMultiplicity()==1.0)
     self.assert_(self.model.getReaction(1).getChemEq().getModifiers().size()==0)
     self.assert_(self.model.getReaction(1).getFunction()!=None)
     self.assert_(self.model.getReaction(1).getFunction().getObjectName()=="Mass action (irreversible)")
     self.assert_(self.model.getReaction(1).getParameters().size()==1)
     self.assert_(self.model.getReaction(1).getParameters().getParameter(0).getObjectName()=="k1")
     self.assert_(self.model.getReaction(1).getParameters().getParameter(0).getValue()==0.1)

def suite():
  tests=[
          'test_createModel'
         ,'test_extendModel'
        ]
  return unittest.TestSuite(map(Test_CreateSimpleModel,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())

 
