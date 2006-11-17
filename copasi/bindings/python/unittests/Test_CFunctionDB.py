import COPASI
import unittest
from types import *


class Test_CFunctionDB(unittest.TestCase):
  def setUp(self):
    self.functions=COPASI.CCopasiDataModel.GLOBAL.getFunctionList()
    self.assert_(self.functions!=None)
    self.assert_(self.function.__class__==COPASI.CFunctionDB)

  def test_add(self):
    self.fail()

  def test_removeFunction(self):
    self.fail()

  def test_findFunction(self):
    self.fail()

  def test_findLoadFunction(self):
    self.fail()

  def test_loadedFunctions(self):
    self.fail()

  def test_suitableFunctions(self):
    self.fail()

def suite():
  tests=[
          "setUp"
         ,"test_add"
         ,"test_removeFunction"
         ,"test_findFunction"
         ,"test_findLoadFunction"
         ,"test_loadedFunctions"
         ,"test_suitableFunctions"
        ]
  return unittest.TestSuite(map(Test_CFunctionDB,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


