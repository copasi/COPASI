# -*- coding: utf-8 -*-
# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CTimeSeries.py,v $ 
#   $Revision: 1.13 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2012/03/05 18:09:29 $ 
# End CVS Header 

# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

import COPASI
import unittest
from types import *
import sys
import pdb

class Test_CTimeSeries(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CCopasiRootContainer.addDatamodel()
    self.datamodel.loadModel("calcium_juergen.cps")
    self.ctimeseries=COPASI.CTimeSeries()
    self.ctimeseries.allocate(100)
    v=COPASI.ContainerStdVector()
    self.ctimeseries.compile(v,self.datamodel)
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

  def test_getTitles(self):
    titles=self.ctimeseries.getTitles()
    self.assert_(type(titles) == ListType)
    self.assert_(len(titles) == 5)
    self.assert_(titles[0] == "Time")
    self.assert_(titles[1] == "a")
    self.assert_(titles[2] == "b")
    self.assert_(titles[3] == "c")
    self.assert_(titles[4] == "Compartments[compartment]")

  def test_getDataForIndex(self):
    data=self.ctimeseries.getDataForIndex(0)
    self.assert_(data != None)
    self.assert_(type(data) == ListType)
    self.assert_(len(data) == self.ctimeseries.getRecordedSteps())
    data=self.ctimeseries.getDataForIndex(2)
    self.assert_(data != None)
    self.assert_(type(data) == ListType)
    self.assert_(len(data) == self.ctimeseries.getRecordedSteps())
    # with this test setup there is only one step and the
    # corresponding value is nan, so futher tests here don't make sense


  def test_getConcentrationDataForIndex(self):
    data=self.ctimeseries.getConcentrationDataForIndex(0)
    self.assert_(data != None)
    self.assert_(type(data) == ListType)
    self.assert_(len(data) == self.ctimeseries.getRecordedSteps())
    data=self.ctimeseries.getConcentrationDataForIndex(2)
    self.assert_(data != None)
    self.assert_(type(data) == ListType)
    self.assert_(len(data) == self.ctimeseries.getRecordedSteps())
    # with this test setup there is only one step and the
    # corresponding value is nan, so futher tests here don't make sense

  def test_getDataForObject(self):
    data=self.ctimeseries.getConcentrationDataForObject(self.datamodel.getModel())
    self.assert_(data != None)
    self.assert_(type(data) == ListType)
    self.assert_(len(data) == self.ctimeseries.getRecordedSteps())
    data=self.ctimeseries.getConcentrationDataForObject(self.datamodel.getModel().getMetabolite(1))
    self.assert_(data != None)
    self.assert_(type(data) == ListType)
    self.assert_(len(data) == self.ctimeseries.getRecordedSteps())

  def test_getConcentrationDataForObject(self):
    data=self.ctimeseries.getConcentrationDataForObject(self.datamodel.getModel())
    self.assert_(data != None)
    self.assert_(type(data) == ListType)
    self.assert_(len(data) == self.ctimeseries.getRecordedSteps())
    data=self.ctimeseries.getConcentrationDataForObject(self.datamodel.getModel().getMetabolite(1))
    self.assert_(data != None)
    self.assert_(type(data) == ListType)
    self.assert_(len(data) == self.ctimeseries.getRecordedSteps())


def suite():
  tests=[
          'test_getRecordedSteps'
         ,'test_getNumVariables'
         ,'test_getData'
         ,'test_getConcentrationData'
         ,'test_getTitle'
         ,'test_getTitles'
         ,'test_getDataForIndex'
         ,'test_getConcentrationDataForIndex'
         ,'test_getDataForObject'
         ,'test_getConcentrationDataForObject'
        ]
  return unittest.TestSuite(map(Test_CTimeSeries,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


