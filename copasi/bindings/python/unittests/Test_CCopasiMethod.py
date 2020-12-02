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


class Test_CCopasiMethod(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CRootContainer.addDatamodel()
    self.method=self.datamodel.getTask(0).getMethod()

  def test_TypeNameToEnum(self):
    typename="Enhanced Newton"
    e=COPASI.CCopasiMethod.TypeNameToEnum(typename)
    self.assert_(type(e)==IntType)
    self.assert_(e==COPASI.CTaskEnum.Method_Newton)

  def test_getType(self):
    t=self.method.getType()
    self.assert_(type(t)==IntType)

  def test_getSubType(self):
    t=self.method.getSubType()
    self.assert_(type(t)==IntType)


def suite():
  tests=[
          'test_TypeNameToEnum'
         ,'test_getType'
         ,'test_getSubType'
        ]
  return unittest.TestSuite(map(Test_CCopasiMethod,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


