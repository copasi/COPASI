# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CReaction.py,v $ 
#   $Revision: 1.12.14.1 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/04/08 15:01:33 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

import COPASI
import unittest
from types import *


class Test_CReaction(unittest.TestCase):
  def setUp(self):
    COPASI.CCopasiDataModel.GLOBAL.newModel()
    self.model=COPASI.CCopasiDataModel.GLOBAL.getModel()
    self.comp1=self.model.createCompartment("comp1",1.0)
    self.comp2=self.model.createCompartment("comp2",2.0)
    self.substrate=self.model.createMetabolite("A","comp1")
    self.product=self.model.createMetabolite("B","comp2")
    self.reac=self.model.createReaction("testReaction");
    self.model.compileIfNecessary()

  def test_getKey(self):
    key=self.reac.getKey()
    self.assert_(type(key)==StringType)

  def test_getFlux(self):
    v=self.reac.getFlux()
    self.assert_(type(v)==FloatType)

  def test_getParticleFlux(self):
    v=self.reac.getParticleFlux()
    self.assert_(type(v)==FloatType)

  def test_isReversible(self):
    v=self.reac.isReversible()
    self.assert_(type(v)==BooleanType)

  def test_addSubstrate(self):
    self.reac.addSubstrate(self.substrate.getKey())

  def test_addProduct(self):
    self.reac.addProduct(self.product.getKey())

  def test_addModifier(self):
    self.reac.addModifier(self.product.getKey())

  def test_setReversible(self):
    v=False
    self.reac.setReversible(v)
    self.assert_(self.reac.isReversible()==v)
    v=True
    self.reac.setReversible(v)
    self.assert_(self.reac.isReversible()==v)

  def test_getCompartmentNumber(self):
    self.reac.addSubstrate(self.substrate.getKey())
    self.reac.addProduct(self.product.getKey())
    self.reac.addModifier(self.product.getKey())
    n=self.reac.getCompartmentNumber()
    self.assert_(type(n)==IntType)
    self.assert_(n==2)

  def test_getLargestCompartment(self):
    self.reac.addSubstrate(self.substrate.getKey())
    self.reac.addProduct(self.product.getKey())
    self.reac.addModifier(self.product.getKey())
    comp=self.reac.getLargestCompartment()
    self.assert_(comp.__class__==COPASI.CCompartment)
    self.assert_(comp.getObjectName()=="comp2")

  def test_setSBMLId(self):
    id="react_1"
    self.reac.setSBMLId(id)
    self.assert_(self.reac.getSBMLId()==id)

  def test_getSBMLId(self):
    id=self.reac.getSBMLId()
    self.assert_(type(id)==StringType)

  def test_getChemEq(self):
    chemEq=self.reac.getChemEq()
    self.assert_(chemEq!=None)
    self.assert_(chemEq.__class__==COPASI.CChemEq)

  def test_getFunction(self):
    f=self.reac.getFunction()
    self.assert_(f!=None)
    self.assert_(f.__class__==COPASI.CFunction)

  def test_setFunction(self):
    functionList=COPASI.CCopasiDataModel.GLOBAL.getFunctionList()
    functions=functionList.suitableFunctions(self.reac.getChemEq().getSubstrates().size(),self.reac.getChemEq().getProducts().size(),self.reac.isReversible())              
    self.assert_(len(functions)!=0)
    function=functions[0]
    self.assert_(function!=None)
    self.assert_(self.reac.setFunction(function.getObjectName()))
    f=self.reac.getFunction()
    self.assert_(f.getKey()==function.getKey())


  def test_getParameterValue(self):
    self.reac.addSubstrate(self.substrate.getKey())
    self.reac.addProduct(self.product.getKey())
    self.reac.setReversible(True)
    function=COPASI.CCopasiDataModel.GLOBAL.getFunctionList().findFunction("Iso Uni Uni")
    self.assert_(function!=None)
    self.assert_(self.reac.setFunction(function.getObjectName()))
    parameters=self.reac.getParameters()
    self.assert_(parameters.size()!=0)
    parameter=parameters.getParameter(0)
    self.assert_(parameter!=None)
    value=self.reac.getParameterValue(parameter.getObjectName())                                 
    self.assert_(type(value)==FloatType)
    self.assert_(value==parameter.getValue())

  def test_setParameterValue(self):
    self.reac.addSubstrate(self.substrate.getKey())
    self.reac.addProduct(self.product.getKey())
    self.reac.setReversible(True)
    function=COPASI.CCopasiDataModel.GLOBAL.getFunctionList().findFunction("Iso Uni Uni")
    self.assert_(function!=None)
    self.assert_(self.reac.setFunction(function.getObjectName()))
    parameters=self.reac.getParameters()
    self.assert_(parameters.size()!=0)
    parameter=parameters.getParameter(0)
    self.assert_(parameter!=None)
    value=34.67
    self.reac.setParameterValue(parameter.getObjectName(),value)
    self.assert_(parameter.getValue()==value)

  def test_getFunctionParameters(self):
    params=self.reac.getFunctionParameters()
    self.assert_(params!=None)
    self.assert_(params.__class__==COPASI.CFunctionParameters)


def suite():
  tests=[
          'test_getKey'
         ,'test_getFlux'
         ,'test_getParticleFlux'
         ,'test_isReversible'
         ,'test_addSubstrate'
         ,'test_addProduct'
         ,'test_addModifier'
         ,'test_setReversible'
         ,'test_getCompartmentNumber'
         ,'test_getLargestCompartment'
         ,'test_getSBMLId'
         ,'test_setSBMLId'
         ,'test_getChemEq'
         ,'test_getFunction'
         ,'test_setFunction'
         ,'test_getParameterValue'
         ,'test_setParameterValue'
         ,'test_getFunctionParameters'
        ]
  return unittest.TestSuite(map(Test_CReaction,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


