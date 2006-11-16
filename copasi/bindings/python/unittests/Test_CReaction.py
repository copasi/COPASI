import COPASI
import unittest
from types import *


class Test_CReaction(unittest.TestCase):
  def setUp(self):
    self.model=COPASI.CModel()
    self.comp=self.model.createCompartment("comp1",1.0)
    self.comp=self.model.createCompartment("comp2",2.0)
    self.substrate=self.model.createMetabolite("A","comp1")
    self.product=self.model.createMetabolite("B","comp2")
    self.reac=self.model.createReaction("testReaction");


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

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


