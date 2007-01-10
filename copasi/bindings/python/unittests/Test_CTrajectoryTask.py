# Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

import COPASI
import unittest
from types import *


class Test_CTrajectoryTask(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CCopasiDataModel.GLOBAL
    self.datamodel.loadModel("calcium_juergen.cps")
    self.task=None
    for x in range(0,self.datamodel.getTaskList().size()):
      task=self.datamodel.getTask(x)
      if(task.__class__==COPASI.CTrajectoryTask):
        self.task=task

  def test_setUp(self):
    self.assert_(self.task!=None)

  def test_process(self):
    self.task.process(True)

  def test_getState(self):
    cstate=self.task.getState()
    self.task.process(True)
    cstate=self.task.getState()
    self.assert_(cstate.__class__==COPASI.CState)

  def test_setMethodType(self):
    self.assert_(self.task.setMethodType(COPASI.CCopasiMethod.stochastic))
    self.failIf(self.task.setMethodType(COPASI.CCopasiMethod.HookeJeeves))

  def test_getTimeSeries(self):
    self.task.process(True)
    timeseries=self.task.getTimeSeries()
    self.assert_(timeseries.__class__==COPASI.CTimeSeries)

  def test_getValidMethods(self):
    validMethods=self.task.getValidMethods();
    self.assert_(len(validMethods)!=0)


def suite():
  tests=[
          'test_setUp'
         ,'test_process'
         ,'test_getState'
         ,'test_getTimeSeries'
         ,'test_setMethodType'
         ,'test_getValidMethods'
        ]
  return unittest.TestSuite(map(Test_CTrajectoryTask,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


