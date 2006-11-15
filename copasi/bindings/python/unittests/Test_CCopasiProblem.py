import COPASI
import unittest
from types import *


class Test_CCopasiProblem(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CCopasiDataModel.GLOBAL
    self.problem=self.datamodel.getTaskList().get(0).getProblem()


  def test_getType(self):
    t=self.problem.getType()
    self.assert_(type(t)==IntType)


  def test_getModel(self):
    model=self.problem.getModel()
    self.assert_(model.__class__==COPASI.CModel)
    self.assert_(model.getKey()==self.datamodel.getModel().getKey())

def suite():
  tests=[
          'test_getType'
         ,'test_getModel'
        ]
  return unittest.TestSuite(map(Test_CCopasiProblem,tests))

