import COPASI
import unittest
from types import *


class Test_CCopasiTask(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CCopasiDataModel.GLOBAL
    self.task=self.datamodel.getTaskList().get(0)


  def test_getType(self):
    t=self.task.getType()
    self.assert_(type(t)==IntType)

  def test_setType(self):
    task=CCopasiTask("TestTask")
    task.setType(COPASI.CCopasiTask.scan)
    self.assert_(task.getType()==COPASI.CCopasiTask.scan)

  def test_getKey(self):
    key=self.task.getKey()
    self.assert_(type(key)==StringType)

  def test_setScheduled(self):
    v=false
    self.task.setScheduled(v)
    self.assert_(self.task.isScheduled()==v)
    v=true
    self.task.setScheduled(v)
    self.assert_(self.task.isScheduled()==v)

  def test_isScheduled(self):
    v=self.task.isScheduled()
    self.assert_(type(v)==BooleanType)

  def test_setUpdateModel(self):
    v=false
    self.task.setUpdateModel(v)
    self.assert_(self.task.isUpdateModel()==v)
    v=true
    self.task.setUpdateModel(v)
    self.assert_(self.task.isUpdateModel()==v)

  def test_isUpdateModel(self):
    v=self.task.isUpdateModel()
    self.assert_(type(v)==BooleanType)


def suite():
  tests=[
          'test_getType'
         ,'test_setType'
         ,'test_getKey'
         ,'test_isScheduled'
         ,'test_setScheduled'
         ,'test_isUpdateModel'
         ,'test_setUpdateModel'
        ]
  return unittest.TestSuite(map(Test_CCopasiTask,tests))
                                      
