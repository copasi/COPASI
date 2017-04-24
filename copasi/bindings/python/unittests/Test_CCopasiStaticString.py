# -*- coding: utf-8 -*-
# Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
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


class Test_CDataString(unittest.TestCase):
  def setUp(self):
    self.s="this_is_a_test"
    self.string=COPASI.CDataString(self.s)

  def test_getObjectDisplayName(self):
    st=self.string.getObjectDisplayName()
    self.assert_(type(st)==StringType)
    self.assert_(st=="'"+self.s+"'")

  def test_getStaticString(self):
    st=self.string.getStaticString()
    self.assert_(type(st)==StringType)
    self.assert_(st==self.s)


def suite():
  tests=[
          'test_getObjectDisplayName'
         ,'test_getStaticString'
        ]
  return unittest.TestSuite(map(Test_CDataString,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


