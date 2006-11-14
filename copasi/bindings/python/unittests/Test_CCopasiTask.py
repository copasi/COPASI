import COPASI
import unittests
from types import *


class Test_CCopasiTask(unittests.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CCopasiDataModel.GLOBAL
    self.task=self.datamodel.getTaskList().get(0)


  def test_getType(self):
    t=self.task.getType()
    self._assert(type(t)==IntType)

  def test_setType(self):
    task=CCopasiTask("TestTask")
    task.setType(COPASI.CCopasiTask.scan)
    self._assert(task.getType()==COPASI.CCopasiTask.scan)

  def test_getKey(self):
    key=self.task.getKey()
    self._assert(type(key)==StringType)

  def test_setScheduled(self):
    v=false
    self.task.setScheduled(v)
    self._assert(self.task.isScheduled()==v)
    v=true
    self.task.setScheduled(v)
    self._assert(self.task.isScheduled()==v)

  def test_isScheduled(self):
    v=self.task.isScheduled()
    self._assert(type(v)==BooleanType)

  def test_setUpdateModel(self):
    v=false
    self.task.setUpdateModel(v)
    self._assert(self.task.isUpdateModel()==v)
    v=true
    self.task.setUpdateModel(v)
    self._assert(self.task.isUpdateModel()==v)

  def test_isUpdateModel(self):
    v=self.task.isUpdateModel()
    self._assert(type(v)==BooleanType)

