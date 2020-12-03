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
import sys
import pdb

class Test_CTimeSeries(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CRootContainer.addDatamodel()
    self.datamodel.loadModel("calcium_juergen.cps")
    task = self.datamodel.getTask('Time-Course')
    problem = task.getProblem()
    problem.time_series_requested = True
    task.process(True)
    self.ctimeseries=task.time_series

  def test_getRecordedSteps(self):
    steps=self.ctimeseries.getRecordedSteps()
    self.assert_(type(steps)==IntType)
    self.assertEquals(steps,20001)

  def test_getNumVariables(self):
    variables=self.ctimeseries.getNumVariables()
    self.assert_(type(variables)==IntType)
    self.assertEquals(variables,4)

  def test_getData(self):
    data=self.ctimeseries.getData(0,1)
    self.assert_(type(data)==FloatType)    

  def test_getConcentrationData(self):
    data=self.ctimeseries.getConcentrationData(0,1)
    self.assert_(type(data)==FloatType)

  def test_getTitle(self):
    title=self.ctimeseries.getTitle(1)
    self.assert_(type(title)==StringType)
    self.assert_(title=="a")

  def test_getTitles(self):
    titles=self.ctimeseries.getTitles()
    self.assert_(type(titles) == ListType)
    self.assertEquals(len(titles),4)
    self.assert_(titles[0] == "Time")
    self.assert_(titles[1] == "a")
    self.assert_(titles[2] == "b")
    self.assert_(titles[3] == "c")

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


