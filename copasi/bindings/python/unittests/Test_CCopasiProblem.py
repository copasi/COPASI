import COPASI
import unittests
from types import *


class Test_CCopasiProblem(unittests.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CCopasiDataModel.GLOBAL
    self.problem=self.datamodel.getTaskList().get(0).getProblem()


  def test_getType(self):
    t=self.problem.getType()
    self._assert(type(t)==IntType)


  def test_getModel(self):
    model=self.problem.getModel()
    self._assert(model.__class__==COPASI.CModel)
    self._assert(model.getKey()==self.datamodel.getModel().getKey())


