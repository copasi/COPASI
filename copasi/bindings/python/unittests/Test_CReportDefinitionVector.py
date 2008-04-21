# -*- coding: utf-8 -*-
# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CReportDefinitionVector.py,v $ 
#   $Revision: 1.7 $ 
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


class Test_CReportDefinitionVector(unittest.TestCase):
  def setUp(self):
    self.vec=COPASI.CReportDefinitionVector();

  def test_getKey(self):
    key=self.vec.getKey()
    self.assert_(type(key)==StringType)

  def test_createReportDefinition(self):
    name="testReport"
    comment="test test test"
    size=self.vec.size()
    repdef=self.vec.createReportDefinition(name,comment)
    self.assert_(self.vec.size()==size+1)
    self.assert_(repdef.__class__==COPASI.CReportDefinition)
    self.assert_(repdef.getObjectName()==name)
    self.assert_(repdef.getComment()==comment)


  def test_removeReportDefinition(self):
    name="testReport"
    comment="test test test"
    size=self.vec.size()
    repdef=self.vec.createReportDefinition(name,comment)
    self.assert_(self.vec.size()==size+1)
    key=repdef.getKey()
    self.vec.removeReportDefinition(key)
    self.assert_(self.vec.size()==size)



def suite():
  tests=[
          'test_getKey'
         ,'test_createReportDefinition'
         ,'test_removeReportDefinition'
        ]
  return unittest.TestSuite(map(Test_CReportDefinitionVector,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


