# -*- coding: utf-8 -*-
# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CTrajectoryProblem.py,v $ 
#   $Revision: 1.10 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/04/21 10:27:07 $ 
# End CVS Header 
# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

import COPASI
import unittest
from types import *
import math


class Test_CTrajectoryProblem(unittest.TestCase):
  def setUp(self):
    self.problem=COPASI.CTrajectoryProblem()

  def test_getStepNumber(self):
    v=self.problem.getStepNumber()
    self.assert_(type(v)==IntType)

  def test_setStepNumber(self):
    t=42
    self.problem.setStepNumber(t)
    self.assert_(math.fabs((self.problem.getStepNumber()-t)/t)<0.001)

  def test_getStepSize(self):
    v=self.problem.getStepSize()
    self.assert_(type(v)==FloatType)

  def test_setStepSize(self):
    t=13.7
    self.problem.setStepSize(t)
    self.assert_(math.fabs((self.problem.getStepSize()-t)/t)<0.001)

  def test_getDuration(self):
    v=self.problem.getDuration()
    self.assert_(type(v)==FloatType)

  def test_setDuration(self):
    t=13.7
    self.problem.setDuration(t)
    self.assert_(math.fabs((self.problem.getDuration()-t)/t)<0.001)

  def test_getOutputStartTime(self):
    v=self.problem.getOutputStartTime()
    self.assert_(type(v)==FloatType)

  def test_setOutputStartTime(self):
    t=13.7
    self.problem.setOutputStartTime(t)
    self.assert_(math.fabs((self.problem.getOutputStartTime()-t)/t)<0.001)

  def test_setTimeSeriesRequested(self):
    v=False
    self.problem.setTimeSeriesRequested(v)
    self.assert_(self.problem.timeSeriesRequested()==v)
    v=True
    self.problem.setTimeSeriesRequested(v)
    self.assert_(self.problem.timeSeriesRequested()==v)

  def test_timeSeriesRequested(self):
    v=self.problem.timeSeriesRequested()
    self.assert_(type(v)==BooleanType)


def suite():
  tests=[
          'test_getStepNumber'
         ,'test_setStepNumber'
         ,'test_getStepSize'
         ,'test_setStepSize'
         ,'test_getDuration'
         ,'test_setDuration'
         ,'test_getOutputStartTime'
         ,'test_setOutputStartTime'
         ,'test_timeSeriesRequested'
         ,'test_setTimeSeriesRequested'
        ]
  return unittest.TestSuite(map(Test_CTrajectoryProblem,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


