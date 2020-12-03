# -*- coding: utf-8 -*-
# Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

import COPASI
import unittest
from types import *


class Test_CTrajectoryTask(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CRootContainer.addDatamodel()
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

  def test_setMethodType(self):
    self.assert_(self.task.setMethodType(COPASI.CTaskEnum.Method_stochastic))
    self.assertFalse(self.task.setMethodType(COPASI.CTaskEnum.Method_HookeJeeves))

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
         ,'test_getTimeSeries'
         ,'test_setMethodType'
         ,'test_getValidMethods'
        ]
  return unittest.TestSuite(map(Test_CTrajectoryTask,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


