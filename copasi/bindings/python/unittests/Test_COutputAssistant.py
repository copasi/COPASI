# -*- coding: utf-8 -*-
# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_COutputAssistant.py,v $ 
#   $Revision: 1.5 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2011/12/21 16:54:48 $ 
# End CVS Header 

# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
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
    self.assert_(object.__class__==COPASI.CReportDefinition) 

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


                                      
