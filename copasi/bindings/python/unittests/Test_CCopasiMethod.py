import COPASI
import unittests
from types import *


class Test_CCopasiMethod(unittests.TestCase):
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



