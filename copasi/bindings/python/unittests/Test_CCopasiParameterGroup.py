# -*- coding: utf-8 -*-
# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CCopasiParameterGroup.py,v $ 
#   $Revision: 1.9 $ 
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


class Test_CCopasiParameterGroup(unittest.TestCase):
  def setUp(self):
    self.paramgroup=COPASI.CCopasiParameterGroup("ParameterGroup")
    self.paramgroup.addParameter("param1",COPASI.CCopasiParameter.DOUBLE)
    self.paramgroup.addParameter("param2",COPASI.CCopasiParameter.DOUBLE)
    self.paramgroup.addParameter("param3",COPASI.CCopasiParameter.DOUBLE)


   
  def test_addParameter(self):
    self.paramgroup.clear()
    self.paramgroup.addParameter("testparam1",COPASI.CCopasiParameter.DOUBLE)
    self.paramgroup.addParameter("testparam2",COPASI.CCopasiParameter.UDOUBLE)
    self.paramgroup.addParameter("testparam3",COPASI.CCopasiParameter.INT)
    self.paramgroup.addParameter("testparam4",COPASI.CCopasiParameter.UINT)
    self.paramgroup.addParameter("testparam5",COPASI.CCopasiParameter.BOOL)
    self.paramgroup.addParameter("testparam6",COPASI.CCopasiParameter.GROUP)
    self.paramgroup.addParameter("testparam7",COPASI.CCopasiParameter.CN)
    self.paramgroup.addParameter("testparam8",COPASI.CCopasiParameter.STRING)
    self.paramgroup.addParameter("testparam9",COPASI.CCopasiParameter.KEY)
    self.paramgroup.addParameter("testparam10",COPASI.CCopasiParameter.FILE)
    self.assert_(self.paramgroup.size()==10)


  def test_addGroup(self):
    self.paramgroup.addGroup("testgroup")
    self.assert_(self.paramgroup.size()==4)

  def test_removeParameter(self):
    self.paramgroup.removeParameter("param1")
    self.assert_(self.paramgroup.size()==2)
    self.paramgroup.removeParameter(0)
    self.assert_(self.paramgroup.size()==1)

  def test_getParameter(self):
    param=self.paramgroup.getParameter("param2")
    self.assert_(param.__class__==COPASI.CCopasiParameter)
    self.assert_(param.getObjectName()=="param2")
    param=self.paramgroup.getParameter(0)
    self.assert_(param.__class__==COPASI.CCopasiParameter)
    self.assert_(param.getObjectName()=="param1")

  def test_getGroup(self):
    self.paramgroup.addGroup("testgroup")
    self.paramgroup.addGroup("testgroup_2")
    group=self.paramgroup.getGroup("testgroup")
    self.assert_(group.__class__==COPASI.CCopasiParameterGroup)
    self.assert_(group.getObjectName()=="testgroup")
    group=self.paramgroup.getGroup(4)
    self.assert_(group.__class__==COPASI.CCopasiParameterGroup)
    self.assert_(group.getObjectName()=="testgroup_2")



  def test_getType(self):
    t=self.paramgroup.getType(0)
    self.assert_(type(t)==IntType)
    self.assert_(t==COPASI.CCopasiParameter.DOUBLE)
    t2=self.paramgroup.getType("param2")
    self.assert_(type(t2)==IntType)
    self.assert_(t2==COPASI.CCopasiParameter.DOUBLE)

  def test_getKey(self):
    key=self.paramgroup.getKey("param1")
    self.assert_(type(key)==StringType)
    key=self.paramgroup.getKey(2)
    self.assert_(type(key)==StringType)

  def test_getName(self):
    name=self.paramgroup.getName(1)
    self.assert_(type(name)==StringType)
    self.assert_(name=="param2")

  def test_size(self):
    size=self.paramgroup.size()
    self.assert_(type(size)==IntType)
    self.assert_(size==3)

  def test_clear(self):
    self.paramgroup.clear()
    self.assert_(self.paramgroup.size()==0)

  def test_getIndex(self):
    index=self.paramgroup.getIndex("param3")
    self.assert_(type(index)==IntType)
    self.assert_(index==2)

def suite():
  tests=[
          'test_size'
         ,'test_clear'
         ,'test_addParameter'
         ,'test_getParameter'
         ,'test_addGroup'
         ,'test_removeParameter'
         ,'test_getGroup'
         ,'test_getType'
         ,'test_getKey'
         ,'test_getName'
         ,'test_getIndex'
        ]
  return unittest.TestSuite(map(Test_CCopasiParameterGroup,tests))


if __name__=='__main__':
    unittest.TextTestRunner(verbosity=2).run(suite())
  

