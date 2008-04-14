# -*- coding: utf-8 -*-
# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CFunctionParameter.py,v $ 
#   $Revision: 1.4.14.2 $ 
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


class Test_CFunctionParameter(unittest.TestCase):
  def setUp(self):
    self.functions=COPASI.CCopasiDataModel.GLOBAL.getFunctionList()
    self.function=self.functions.findFunction("Iso Uni Uni")
    self.assert_(self.function!=None)
    self.assert_(self.function.__class__==COPASI.CFunction)
    self.parameters=self.function.getVariables()
    self.assert_(self.parameters!=None)
    self.assert_(self.parameters.__class__==COPASI.CFunctionParameters)
    index=self.parameters.findParameterByName("Keq",COPASI.CFunctionParameter.FLOAT64)
    self.parameter=self.parameters.getParameter(index)
    self.assert_(self.parameter!=None)
    self.assert_(self.parameter.__class__==COPASI.CFunctionParameter)

  def test_getKey(self):
    key=self.parameter.getKey()
    self.assert_(type(key)==StringType)

  def test_getType(self):
    b=self.parameter.getType()
    self.assert_(type(b)==IntType)
    self.assert_(b==COPASI.CFunctionParameter.FLOAT64)

  def test_setType(self):
    t=COPASI.CFunctionParameter.INT32
    self.parameter.setType(t)
    self.assert_(self.parameter.getType()==t)

  def test_getUsage(self):
    b=self.parameter.getUsage()
    self.assert_(type(b)==IntType)
    self.assert_(b==COPASI.CFunctionParameter.PARAMETER)

  def test_setUsage(self):
    t=COPASI.CFunctionParameter.VOLUME
    self.parameter.setUsage(t)
    self.assert_(self.parameter.getUsage()==t)




def suite():
  tests=[
          "test_getKey"        
         ,"test_getType"        
         ,"test_setType"        
         ,"test_getUsage"        
         ,"test_setUsage"        
        ]
  return unittest.TestSuite(map(Test_CFunctionParameter,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


