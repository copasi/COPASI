# -*- coding: utf-8 -*-
# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CCopasiParameter.py,v $ 
#   $Revision: 1.8.14.2 $ 
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
import math

class Test_CCopasiParameter(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CCopasiDataModel.GLOBAL
    self.datamodel.loadModel("calcium_juergen.cps")
    self.param=self.datamodel.getModel().getReaction(0).getParameters().getParameter(0)

  def test_setUp(self):
    self.assert_(self.param.getType()==COPASI.CCopasiParameter.DOUBLE)

  def test_getKey(self):
    key=self.param.getKey()
    self.assert_(type(key)==StringType)


  def test_setValue(self):
    value=15.3
    self.param.setValue(value)
    self.assert_(math.fabs((self.param.getValue()-value)/value)<0.001)

  def test_getValue(self):
    value=self.param.getValue()
    self.assert_(type(value)==FloatType)

  def test_getType(self):
    t=self.param.getType()
    self.assert_(type(t)==IntType)
    self.assert_(t==COPASI.CCopasiParameter.DOUBLE)

  def test_isValidValue(self):
    value=1.5
    self.assert_(self.param.isValidValue(value))
    value=3
    self.assert_(not self.param.isValidValue(value))
    value=0
    self.assert_(not self.param.isValidValue(value))
    value="test"
    self.assert_(not self.param.isValidValue(value))
    value=COPASI.CCopasiObjectName("myObject")
    self.assert_(not self.param.isValidValue(value))
     


def suite():
  tests=[
          'test_setUp'
         ,'test_getKey'
         ,'test_getValue'
         ,'test_setValue'
         ,'test_getType'
         ,'test_isValidValue'
        ]
  return unittest.TestSuite(map(Test_CCopasiParameter,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


