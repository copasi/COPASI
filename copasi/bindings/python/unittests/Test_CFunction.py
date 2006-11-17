import COPASI
import unittest
from types import *


class Test_CFunction(unittest.TestCase):
  def setUp(self):
    pass

  def test_setInfix(self):
    pass

  def test_getVariableIndex(self):
    self.fail()

  def test_getVariableValue(self):
    self.fail()

  def test_isReversible(self):
    self.fail()

  def test_setReversible(self):
    self.fail()

  def test_getVariables(self):
    self.fail()

  def test_addVariable(self):
    self.fail()  

  def test_isSuitable(self):
    self.fail()  

def suite():
  tests=[
          "setUp"
         ,"test_setInfix"
         ,"test_getVariableIndex"
         ,"test_getVariableValue"
         ,"test_isReversible"
         ,"test_setReversible"
         ,"test_getVariables"
         ,"test_addVariable"
         ,"test_isSuitable"                     
        ]
  return unittest.TestSuite(map(Test_CFunction,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


