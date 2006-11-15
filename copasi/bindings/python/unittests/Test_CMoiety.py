import COPASI
import unittest
from types import *


class Test_CMoiety(unittest.TestCase):
  def setUp(self):
    self.moiety=COPASI.CMoiety()

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

