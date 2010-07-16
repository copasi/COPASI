# -*- coding: utf-8 -*-
# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CState.py,v $ 
#   $Revision: 1.9 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/07/16 18:55:59 $ 
# End CVS Header 

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
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

class Test_CState(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CCopasiRootContainer.addDatamodel()
    self.model=self.datamodel.getModel()
    self.cstate=self.model.getInitialState()

  def test_getTime(self):
    time=self.cstate.getTime()
    self.assert_(type(time)==FloatType,"Error. The time value returned by CState.getTime() is not a double value.")

  def test_setTime(self):
    TIME=27.96
    self.cstate.setTime(TIME)
    self.assert_(self.cstate.getTime()==TIME)

  def test_getNumIndependent(self):
    result=self.cstate.getNumIndependent()
    self.assert_(type(result)==IntType)

  def test_getNumDependent(self):
    result=self.cstate.getNumDependent()
    self.assert_(type(result)==IntType)

  def test_getNumVariable(self):
    result=self.cstate.getNumVariable()
    self.assert_(type(result)==IntType)

  def test_getNumFixed(self):
    result=self.cstate.getNumFixed()
    self.assert_(type(result)==IntType)


def suite():
  tests=[
          'test_getTime'
         ,'test_setTime'
         ,'test_getNumIndependent'
         ,'test_getNumDependent'
         ,'test_getNumVariable'
         ,'test_getNumFixed'
        ]
  return unittest.TestSuite(map(Test_CState,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())

    
