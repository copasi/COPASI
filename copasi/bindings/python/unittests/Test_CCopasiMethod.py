import COPASI
import unittest
from types import *


class Test_CCopasiMethod(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CCopasiDataModel.GLOBAL
    self.method=self.datamodel.getTaskList().get(0).getMethod()

  def test_TypeNameToEnum(self):
    typename="Enhanced Newton"
    e=COPASI.CCopasiMethod.TypeNameToEnum(typename)
    self._assert(type(e)==IntType)
    self._assert(e==COPASI.CCopasiMethod.Newton)

  def test_getType(self):
    t=self.method.getType()
    self._assert(type(t)==IntType)

  def test_getSubType(self):
    t=self.method.getSubType()
    self._assert(type(t)==IntType)


def suite():
  tests=[
          'test_TypeNameToEnum'
         ,'test_getType'
         ,'test_getSubType'
        ]
  return unittest.TestSuite(map(Test_CCopasiMethod,tests))

