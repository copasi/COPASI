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
    self.assert_(type(e)==IntType)
    self.assert_(e==COPASI.CCopasiMethod.Newton)

  def test_getType(self):
    t=self.method.getType()
    self.assert_(type(t)==IntType)

  def test_getSubType(self):
    t=self.method.getSubType()
    self.assert_(type(t)==IntType)


def suite():
  tests=[
          'test_TypeNameToEnum'
         ,'test_getType'
         ,'test_getSubType'
        ]
  return unittest.TestSuite(map(Test_CCopasiMethod,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


