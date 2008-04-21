# -*- coding: utf-8 -*-
# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CTimeSeries.py,v $ 
#   $Revision: 1.9.14.2 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/04/14 08:19:40 $ 
# End CVS Header 
# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

import COPASI
import unittest
from types import *
import sys

class Test_CTimeSeries(unittest.TestCase):
  def setUp(self):
    COPASI.CCopasiDataModel.GLOBAL.loadModel("calcium_juergen.cps")
    self.ctimeseries=COPASI.CTimeSeries()
    self.ctimeseries.allocate(100)
    v=COPASI.ContainerStdVector()
    self.ctimeseries.compile(v)
    self.ctimeseries.output(COPASI.COutputHandler.DURING)
    self.ctimeseries.finish()

  def test_getRecordedSteps(self):
    steps=self.ctimeseries.getRecordedSteps()
    self.assert_(type(steps)==IntType)
    self.assert_(steps==1)

  def test_getNumVariables(self):
    variables=self.ctimeseries.getNumVariables()
    self.assert_(type(variables)==IntType)
    self.assert_(variables==5)

  def test_getData(self):
    data=self.ctimeseries.getData(0,1)
    self.assert_(type(data)==FloatType)
    version=sys.version.split(".")
    major=int(version[0])
    minor=int(version[1])
    if(major>2 or (major==2 and minor>3)):
      # check if it is NaN since NaN != NaN
      self.assert_(data!=data)

  def test_getConcentrationData(self):
    data=self.ctimeseries.getConcentrationData(0,1)
    self.assert_(type(data)==FloatType)
    version=sys.version.split(".")
    major=int(version[0])
    minor=int(version[1])
    if(major>2 or (major==2 and minor>3)):
      # check if it is NaN since NaN != NaN
      self.assert_(data!=data)

  def test_getTitle(self):
    title=self.ctimeseries.getTitle(1)
    self.assert_(type(title)==StringType)
    self.assert_(title=="a")


def suite():
  tests=[
          'test_getRecordedSteps'
         ,'test_getNumVariables'
         ,'test_getData'
         ,'test_getConcentrationData'
         ,'test_getTitle'
        ]
  return unittest.TestSuite(map(Test_CTimeSeries,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


