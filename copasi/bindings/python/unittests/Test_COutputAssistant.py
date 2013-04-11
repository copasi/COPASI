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


class Test_COutputAssistant(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CCopasiRootContainer.addDatamodel()
    self.task=self.datamodel.getTask(0)
    self.problem=self.task.getProblem()

  def test_getDefaultReportIndex(self):
    self.assert_(self.task!=None)
    index=COPASI.COutputAssistant.getDefaultReportIndex(self.problem)
    self.assert_(type(index)==IntType)

  def test_getListOfDefaultOutputDescriptions(self):
    self.assert_(self.task!=None)
    outputDescriptions=COPASI.COutputAssistant.getListOfDefaultOutputDescriptions(self.task)
    self.assert_(type(outputDescriptions)==TupleType)
    self.assert_(len(outputDescriptions)!=0)

  def test_getItemName(self):
    self.assert_(self.task!=None)
    outputDescriptions=COPASI.COutputAssistant.getListOfDefaultOutputDescriptions(self.task)
    self.assert_(type(outputDescriptions)==TupleType)
    self.assert_(len(outputDescriptions)!=0)
    itemId=outputDescriptions[0]
    name=COPASI.COutputAssistant.getItemName(itemId)
    self.assert_(type(name)==StringType)

  def test_getItem(self):
    self.assert_(self.task!=None)
    outputDescriptions=COPASI.COutputAssistant.getListOfDefaultOutputDescriptions(self.task)
    self.assert_(type(outputDescriptions)==TupleType)
    self.assert_(len(outputDescriptions)!=0)
    itemId=outputDescriptions[0]
    desc=COPASI.COutputAssistant.getItem(itemId)
    self.assert_(desc!=None)
    self.assert_(desc.__class__==COPASI.CDefaultOutputDescription)

  def test_createDefaultOutput(self):
    self.assert_(self.task!=None)
    index=COPASI.COutputAssistant.getDefaultReportIndex(self.problem)
    object=COPASI.COutputAssistant.createDefaultOutput(index,self.task,self.datamodel,True)
    self.assert_(object!=None)
    self.assert_(object.__class__==COPASI.CReportTemplate) 

def suite():
  tests=[
          'test_getDefaultReportIndex'                       
         ,'test_getListOfDefaultOutputDescriptions'                       
         ,'test_getItemName'                       
         ,'test_getItem'                       
         ,'test_createDefaultOutput'                       
        ]
  return unittest.TestSuite(map(Test_COutputAssistant,tests))


if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


                                      
