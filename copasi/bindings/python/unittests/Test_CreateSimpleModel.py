# Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

import COPASI
import unittest
from types import *

def createModel():
    COPASI.CCopasiDataModel.GLOBAL.newModel()
    model=COPASI.CCopasiDataModel.GLOBAL.getModel()
    model.setVolumeUnit(COPASI.CModel.fl)
    model.setTimeUnit(COPASI.CModel.s)
    model.setQuantityUnit(COPASI.CModel.fMol)
    comp=model.createCompartment("CompartmentA")
    A=model.createMetabolite("A",comp.getObjectName())
    A.setInitialConcentration(2.0e-4)
    B=model.createMetabolite("B",comp.getObjectName())
    B.setInitialConcentration(0.0)
    react=model.createReaction("Decay_1")
    react.addSubstrate(A.getKey())
    react.addProduct(B.getKey())
    react.setReversible(False)
    react.setFunction("Mass action (irreversible)")
    react.setParameterValue("k1",0.5)
    mapping=COPASI.ParameterMapping()
    mapping.append(react.getChemEq().getSubstrate(0).getMetabolite().getKey())
    react.setParameterMappingVector(react.getFunction().getVariables().getParameter(1).getObjectName(),mapping);
    model.compileIfNecessary()
    return model

def extendModel(model):
    metab=model.createMetabolite("C",model.getCompartment(0).getObjectName())
    metab.setInitialConcentration(0.0)
    react=model.createReaction("Decay_2")
    react.addSubstrate(model.getMetabolite(1).getKey())
    react.addProduct(metab.getKey())
    react.setReversible(False)
    react.setFunction("Mass action (irreversible)")
    react.getParameters().getParameter(0).setValue(0.1)
    mapping=COPASI.ParameterMapping()
    mapping.append(react.getChemEq().getSubstrate(0).getMetabolite().getKey())
    react.setParameterMappingVector(react.getFunction().getVariables().getParameter(1).getObjectName(),mapping);
    model.compileIfNecessary()


class Test_CreateSimpleModel(unittest.TestCase):
   def setUp(self):
    self.model=createModel()

   def test_createModel(self):
     self.assert_(self.model!=None)
     self.assert_(self.model.__class__==COPASI.CModel)
     self.assert_(self.model.getCompartments().size()==1)
     self.assert_(self.model.getCompartment(0).getObjectName()=="CompartmentA")
     self.assert_(self.model.getMetabolites().size()==2)
     self.assert_(self.model.getMetabolite(0).getObjectName()=="A")
     self.assert_(self.model.getMetabolite(0).getInitialConcentration()==2.0e-4)
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
     extendModel(self.model) 
     self.assert_(self.model.getMetabolites().size()==3)
     self.assert_(self.model.getMetabolite(2).getObjectName()=="C")
     self.assert_(self.model.getMetabolite(2).getInitialValue()==0.0)
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

 
