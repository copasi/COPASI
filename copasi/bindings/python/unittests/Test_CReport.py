# -*- coding: utf-8 -*-
# Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual </comment>
# Properties, Inc., University of Heidelberg, and The University </comment>
# of Manchester. </comment>
# All rights reserved. </comment>

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual </comment>
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, </comment>
# and The University of Manchester. </comment>
# All rights reserved. </comment>

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual </comment>
# Properties, Inc. and EML Research, gGmbH. </comment>
# All rights reserved. </comment>

import COPASI
import unittest
from types import *


class Test_CReport(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CCopasiRootContainer.addDatamodel()
    self.task=self.datamodel.getTask(0)
    self.report=self.task.getReport()

  def test_getReportTemplate(self):
    reportTemplate=self.report.getReportTemplate()
    self.assert_(reportTemplate!=None)
    self.assert_(reportTemplate.__class__==COPASI.CReportTemplate)

  def test_setReportTemplate(self):
    listOfReportTemplates=self.datamodel.getReportTemplateList()
    reportTemplate=listOfReportTemplates.createReportTemplate("MyReportTemplate","No Comment")
    self.assert_(reportTemplate!=None)
    self.report.setReportTemplate(reportTemplate)
    self.assert_(self.report.getReportTemplate().getKey()==reportTemplate.getKey())

  def test_getTarget(self):
    target=self.report.getTarget()
    self.assert_(target!=None)
    self.assert_(type(target)==StringType)

  def test_setTarget(self):
    target="MyTaget.txt"
    self.report.setTarget(target)
    t=self.report.getTarget()
    self.assert_(t!=None)
    self.assert_(t==target)

  def test_append(self):
    append=self.report.append()
    self.assert_(type(append)==BooleanType)

  def test_setAppend(self):
    self.report.setAppend(True)
    append=self.report.append()
    self.assert_(append==True)
    self.report.setAppend(False)
    append=self.report.append()
    self.assert_(append==False)




def suite():
  tests=[
          'test_getReportTemplate'                       
         ,'test_setReportTemplate'                       
         ,'test_getTarget'                       
         ,'test_setTarget'                       
         ,'test_append'                       
         ,'test_setAppend'                       
        ]
  return unittest.TestSuite(map(Test_CReport,tests))


if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


                                      
