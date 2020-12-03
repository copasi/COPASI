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


class Test_CCopasiParameterGroup(unittest.TestCase):
  def setUp(self):
    self.paramgroup=COPASI.CCopasiParameterGroup("ParameterGroup")
    self.paramgroup.addParameter("param1",COPASI.CCopasiParameter.Type_DOUBLE)
    self.paramgroup.addParameter("param2",COPASI.CCopasiParameter.Type_DOUBLE)
    self.paramgroup.addParameter("param3",COPASI.CCopasiParameter.Type_DOUBLE)


   
  def test_addParameter(self):
    self.paramgroup.clear()
    self.paramgroup.addParameter("testparam1",COPASI.CCopasiParameter.Type_DOUBLE)
    self.paramgroup.addParameter("testparam2",COPASI.CCopasiParameter.Type_UDOUBLE)
    self.paramgroup.addParameter("testparam3",COPASI.CCopasiParameter.Type_INT)
    self.paramgroup.addParameter("testparam4",COPASI.CCopasiParameter.Type_UINT)
    self.paramgroup.addParameter("testparam5",COPASI.CCopasiParameter.Type_BOOL)
    self.paramgroup.addParameter("testparam6",COPASI.CCopasiParameter.Type_GROUP)
    self.paramgroup.addParameter("testparam7",COPASI.CCopasiParameter.Type_CN)
    self.paramgroup.addParameter("testparam8",COPASI.CCopasiParameter.Type_STRING)
    self.paramgroup.addParameter("testparam9",COPASI.CCopasiParameter.Type_KEY)
    self.paramgroup.addParameter("testparam10",COPASI.CCopasiParameter.Type_FILE)
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
    self.assert_(type(t)==int)
    self.assert_(t==COPASI.CCopasiParameter.Type_DOUBLE)
    t2=self.paramgroup.getType("param2")
    self.assert_(type(t2)==int)
    self.assert_(t2==COPASI.CCopasiParameter.Type_DOUBLE)

  def test_getKeyForParameter(self):
    key=self.paramgroup.getKeyForParameter("param1")
    self.assert_(type(key)==str)
    key=self.paramgroup.getKeyForParameter(2)
    self.assert_(type(key)==str)

  def test_getName(self):
    name=self.paramgroup.getName(1)
    self.assert_(type(name)==str)
    self.assert_(name=="param2")

  def test_size(self):
    size=self.paramgroup.size()
    self.assert_(type(size)==int)
    self.assert_(size==3)

  def test_clear(self):
    self.paramgroup.clear()
    self.assert_(self.paramgroup.size()==0)

  def test_getIndex(self):
    index=self.paramgroup.getIndex("param3")
    self.assert_(type(index)==int)
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
         ,'test_getKeyForParameter'
         ,'test_getName'
         ,'test_getIndex'
        ]
  return unittest.TestSuite(map(Test_CCopasiParameterGroup,tests))


if __name__=='__main__':
    unittest.TextTestRunner(verbosity=2).run(suite())
  

