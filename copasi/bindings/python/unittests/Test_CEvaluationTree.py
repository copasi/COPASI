import COPASI
import unittest
from types import *


class Test_CEvaluationTree(unittest.TestCase):
  def setUp(self):
    pass

  def test_create(self):
    self.fail()

  def test_copy(self):
    self.fail()

  def test_getType(self):
    self.fail()

  def test_setType(self):
    self.fail()

  def test_getInfix(self):
    self.fail()

  def test_setInfix(self):
    self.fail()

  def test_getErrorPosition(self):
    self.fail()

  def test_getVariableIndex(self):
    self.fail()

  def test_getVariableValue(self):
    self.fail()

  def test_getSBMLId(self):
    self.fail()

  def test_setSBMLId(self):
    self.fail()


def suite():
  tests=[
          "setUp"
         ,"test_create"
         ,"test_copy"
         ,"test_getType"
         ,"test_setType"
         ,"test_getInfix"
         ,"test_setInfix"
         ,"test_getErrorPosition"
         ,"test_getVariableIndex"
         ,"test_getVariableValue"
         ,"test_getSBMLId"
         ,"test_setSBMLId"
        ]
  return unittest.TestSuite(map(Test_CEvaluationTree,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


