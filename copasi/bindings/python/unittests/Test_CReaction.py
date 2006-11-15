import COPASI
import unittest
from types import *


class Test_CReaction(unittest.TestCase):
  def setUp(self):
    self.model=COPASI.CModel()
    self.comp=model.createCompartment("comp1",1.0)
    self.comp=model.createCompartment("comp2",2.0)
    self.substrate=model.createMetabolite("A","comp1")
    self.product=model.createMetabolite("B","comp2")
    self.reac=model.createReaction("testReaction");


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
    v=self.reac.getParticleFlux()
    self.assert_(type(v)==BooleanType)

  def test_addSubstrate(self):
    self.reac.addSubstrate(self.substrate)

  def test_addProduct(self):
    self.reac.addProduct(self.product)

  def test_addModifier(self):
    self.reac.addModifier(self.product)

  def test_setReversible(self):
    v=false
    self.reac.setReversible(v)
    self.assert_(self.reac.getReversible()==v)
    v=true
    self.reac.setReversible(v)
    self.assert_(self.reac.getReversible()==v)

  def test_getCompartmentNumber(self):
    self.reac.addSubstrate(self.substrate)
    self.reac.addProduct(self.product)
    self.reac.addModifier(self.product)
    n=self.reac.getCompartmentNumber()
    self.assert_(type(n)==IntType)
    self.assert_(n==2)

  def test_getLargestCompartment(self):
    self.reac.addSubstrate(self.substrate)
    self.reac.addProduct(self.product)
    self.reac.addModifier(self.product)
    comp=self.reac.getLargestCompartment()
    self.assert_(comp.__class__==COPASI.CCompartment)
    self.assert_(comp.getObjectName()=="comp2")

  def test_setSBMLId(self):
    id="react_1"
    self.reac.setSBMLId(id)
    self.assert_(self.reac.getSBMLid()==id)

  def test_getSBMLId(self):
    id=self.reac.getSBMLId()
    self.assert_(type(id)==StringType)


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
        ]
  return unittest.TestSuite(map(Test_CReaction,tests))

