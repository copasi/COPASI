# -*- coding: utf-8 -*-
# Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual </comment>
# Properties, Inc., University of Heidelberg, and The University </comment>
# of Manchester. </comment>
# All rights reserved. </comment>

import COPASI
import unittest
from types import *


class Test_CReportTemplateVector(unittest.TestCase):
  def setUp(self):
    self.vec=COPASI.CReportTemplateVector();

  def test_getKey(self):
    key=self.vec.getKey()
    self.assert_(type(key)==StringType)

  def test_createReportTemplate(self):
    name="testReport"
    comment="test test test"
    size=self.vec.size()
    repdef=self.vec.createReportTemplate(name,comment)
    self.assert_(self.vec.size()==size+1)
    self.assert_(repdef.__class__==COPASI.CReportTemplate)
    self.assert_(repdef.getObjectName()==name)
    self.assert_(repdef.getComment()==comment)


  def test_removeReportTemplate(self):
    name="testReport"
    comment="test test test"
    size=self.vec.size()
    repdef=self.vec.createReportTemplate(name,comment)
    self.assert_(self.vec.size()==size+1)
    key=repdef.getKey()
    self.vec.removeReportTemplate(key)
    self.assert_(self.vec.size()==size)



def suite():
  tests=[
          'test_getKey'
         ,'test_createReportTemplate'
         ,'test_removeReportTemplate'
        ]
  return unittest.TestSuite(map(Test_CReportTemplateVector,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


