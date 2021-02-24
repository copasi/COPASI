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


class Test_CCopasiTask(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CRootContainer.addDatamodel()
    self.task=self.datamodel.getTask(0)


  def test_getType(self):
    t=self.task.getType()
    self.assert_(type(t)==IntType)

  def test_getKey(self):
    key=self.task.getKey()
    self.assert_(type(key)==StringType)

  def test_setScheduled(self):
    v=False
    self.task.setScheduled(v)
    self.assert_(self.task.isScheduled()==v)
    v=True
    self.task.setScheduled(v)
    self.assert_(self.task.isScheduled()==v)

  def test_isScheduled(self):
    v=self.task.isScheduled()
    self.assert_(type(v)==BooleanType)

  def test_setUpdateModel(self):
    v=False
    self.task.setUpdateModel(v)
    self.assert_(self.task.isUpdateModel()==v)
    v=True
    self.task.setUpdateModel(v)
    self.assert_(self.task.isUpdateModel()==v)

  def test_isUpdateModel(self):
    v=self.task.isUpdateModel()
    self.assert_(type(v)==BooleanType)

  def test_getValidMethods(self):
    validMethods=self.task.getValidMethods();
    self.assert_(type(validMethods)==TupleType);
    self.assert_(len(validMethods)!=0)

  def test_getReport(self):
    report=self.task.getReport()
    self.assert_(report!=None)
    self.assert_(report.__class__==COPASI.CReport)


def suite():
  tests=[
          'test_getType'
         ,'test_getKey'
         ,'test_isScheduled'
         ,'test_setScheduled'
         ,'test_isUpdateModel'
         ,'test_setUpdateModel'
         ,'test_getValidMethods'
         ,'test_getReport'                       
        ]
  return unittest.TestSuite(map(Test_CCopasiTask,tests))


if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


                                      
