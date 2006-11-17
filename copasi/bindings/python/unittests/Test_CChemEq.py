import COPASI
import unittest
from types import *


class Test_CChemEq(unittest.TestCase):
  def setUp(self):
    self.model=COPASI.CModel()
    self.comp1=self.model.createCompartment("comp1",1.0)
    self.comp2=self.model.createCompartment("comp2",4.0)
    self.m1=self.model.createMetabolite("A","comp1")
    self.m2=self.model.createMetabolite("B","comp2")
    self.m3=self.model.createMetabolite("C","comp1")
    self.m4=self.model.createMetabolite("D","comp1")
    self.m5=self.model.createMetabolite("E","comp1")
    r=self.model.createReaction("react1")
    r.addSubstrate(self.m1.getKey())
    r.addSubstrate(self.m5.getKey())
    r.addProduct(self.m2.getKey())
    r.addModifier(self.m3.getKey())
    self.model.compileIfNecessary()
    self.chemeq=r.getChemEq()

  def test_getReversibility(self):
    b=self.chemeq.getReversibility()
    self.assert_(type(b)==BooleanTyp)

  def test_setReversibility(self):
    b=True
    self.chemeq.setReversibility(b)
    self.assert_(self.chemeq.getReversibility()==b)
    b=False
    self.chemeq.setReversibility(b)
    self.assert_(self.chemeq.getReversibility()==b)

  def test_addMetabolite(self):
    self.chemeq.addMetabolite(self.m4.getKey(),3.0,COPASI.CChemEq.SUBSTRATE)

  def test_getSubstrates(self):
    vect=self.chemeq.getSubstrates()
    self.assert_(vect!=None)
    self.assert_(vect.__class__==COPASI.CChemEqElementVector)
    self.assert_(vect.size()==2)

  def test_getProducts(self):
    vect=self.chemeq.getProducts()
    self.assert_(vect!=None)
    self.assert_(vect.__class__==COPASI.CChemEqElementVector)
    self.assert_(vect.size()==1)

  def test_getModifiers(self):
    vect=self.chemeq.getModifiers()
    self.assert_(vect!=None)
    self.assert_(vect.__class__==COPASI.CChemEqElementVector)
    self.assert_(vect.size()==1)

  def test_getBalances(self):
    vect=self.chemeq.getBalances()
    self.assert_(vect!=None)
    self.assert_(vect.__class__==COPASI.CChemEqElementVector)
    self.assert_(vect.size()==1)

  def test_getCompartmentNumber(self):
    n=self.chemeq.getCompartmentNumber()
    self.assert_(type(n)==IntType)
    self.assert_(n==2)

  def test_getLargestCompartment(self):
    comp=self.chemeq.getLargestCompartment()
    self.assert_(comp!=None)
    self.assert_(comp.__class__==COPASI.CCompartment)
    self.assert_(comp.getKey()==self.comp2.getKey())


def suite():
  tests=[
           "test_getReversibility"
          ,"test_setReversibility"
          ,"test_addMetabolite"
          ,"test_getSubstrates"
          ,"test_getProducts"
          ,"test_getModifiers"
          ,"test_getBalances"
          ,"test_getCompartmentNumber"
          ,"test_getLargestCompartment"
        ]
  return unittest.TestSuite(map(Test_CChemEq,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


