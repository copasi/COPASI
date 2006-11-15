import COPASI
import unittest
from types import *
import math

class Test_CCopasiParameter(unittest.TestCase):
  def setUp(self):
    self.param=COPASI.CCopasiParameter("testParameter",COPASI.CCopasiParameter.DOUBLE,34.0)

  def test_getKey(self):
    key=self.param.getKey()
    self._assert(type(key)==StringType)


  def test_setValue(self):
    value=15.3
    self.param.setValue(value)
    self._assert(math.fabs(self.param.getValue()-value/value)<0.001)


  def test_getValue(self):
    value=self.param.getValue()
    self._assert(type(value)==FloatType)

  def test_getType(self):
    t=self.param.getType()
    self._assert(type(t)==IntType)
    self._assert(t==COPASI.CCopasiParameter.DOUBLE)


  def test_isValidValue(self):
    value=1.5
    self._assert(self.param.isValidValue(value))
    value=3
    self._assert(not self.param.isValidValue(value))
    value=false
    self._assert(not self.param.isValidValue(value))
    value="test"
    self._assert(not self.param.isValidValue(value))
    value=COPASI.CCopasiObjectName("myObject")
    self._assert(not self.param.isValidValue(value))
    # other types should be tested as well as vectors of parameters
    self._assert(false)
     


def suite():
  tests=[
          'test_getKey'
         ,'test_getValue'
         ,'test_setValue'
         ,'test_getType'
         ,'test_isValidValue'
        ]
  return unittest.TestSuite(map(Test_CCopasiParameter,tests))

