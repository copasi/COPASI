import COPASI
import unittest
from types import *


class Test_CMoiety(unittest.TestCase):
  def setUp(self):
    self.model=COPASI.CModel()
    self.model.createCompartment("comp1",1.0)
    self.model.createCompartment("comp2",2.0)
    m1=self.model.createMetabolite("A","comp1")
    m2=self.model.createMetabolite("B","comp1")
    m3=self.model.createMetabolite("C","comp1")
    m4=self.model.createMetabolite("D","comp1")
    m5=self.model.createMetabolite("E","comp2")
    m6=self.model.createMetabolite("F","comp2")
    m7=self.model.createMetabolite("G","comp2")
    r=self.model.createReaction("react1")
    r.addSubstrate(m1.getKey())
    r.addProduct(m2.getKey())
    r=self.model.createReaction("react2")
    r.addSubstrate(m3.getKey())
    r.addProduct(m5.getKey())
    r=self.model.createReaction("react3")
    r.addSubstrate(m6.getKey())
    r.addProduct(m2.getKey())
    self.model.buildStoi()
    self.model.buildMoieties()
    self.moieties=self.model.getMoieties()
    self.moiety=self.moieties.get(0)

  def test_getDescription(self):
    desc=self.moiety.getDescription()
    self.assert_(type(desc)==StringType)

  def test_dependentNumber(self):
    v=self.moiety.dependentNumber()
    self.assert_(type(v)==FloatType)

  def test_getNumber(self):
    v=self.moiety.getNumber()
    self.assert_(type(v)==FloatType)

  def test_getKey(self):
    key=self.moiety.getKey()
    self.assert_(type(key)==StringType)

  def test_getDependentRate(self):
    v=self.moiety.getDependentRate()
    self.assert_(type(v)==FloatType)

  def test_getDependentNumber(self):
    v=self.moiety.getDependentNumber()
    self.assert_(type(v)==FloatType)

def suite():
  tests=[
          'test_getDescription'
         ,'test_getDependentNumber'
         ,'test_getNumber'
         ,'test_getKey'
         ,'test_getDependentRate'
         ,'test_getDependentNumber'
        ]
  return unittest.TestSuite(map(Test_CMoiety,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


