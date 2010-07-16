# -*- coding: utf-8 -*-
# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CCopasiRootContainer.py,v $ 
#   $Revision: 1.2 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/07/16 18:55:59 $ 
# End CVS Header 

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

import COPASI
import unittest
from types import *
import string


class Test_CCopasiRootContainer(unittest.TestCase):
  def setUp(self):
    pass

  def test_getRoot(self):
    root = COPASI.CCopasiRootContainer.getRoot()
    self.assert_(root != None)
    self.assert_(root.__class__ == COPASI.CCopasiRootContainer)

  def test_AddRemoveDatamodel(self):
      datamodelList=COPASI.CCopasiRootContainer.getDatamodelList()
      self.assert_(datamodelList.__class__ == COPASI.DataModelVector)
      self.assert_(datamodelList.size() == 0)
      datamodel = COPASI.CCopasiRootContainer.addDatamodel()
      self.assert_(datamodel != None)
      self.assert_(datamodel.__class__ == COPASI.CCopasiDataModel)
      self.assert_(datamodelList.size() == 1)
      datamodel = COPASI.CCopasiRootContainer.addDatamodel()
      self.assert_(datamodel != None)
      self.assert_(datamodel.__class__ == COPASI.CCopasiDataModel)
      self.assert_(datamodelList.size() == 2)
      result = COPASI.CCopasiRootContainer.removeDatamodelWithIndex(0)
      self.assert_(result == True)
      self.assert_(datamodelList.size() == 1)
      result = COPASI.CCopasiRootContainer.removeDatamodel(datamodel)
      self.assert_(result == True)
      self.assert_(datamodelList.size() == 0)


  def test_getFunctionList(self):
    functions=COPASI.CCopasiRootContainer.getFunctionList()
    self.assert_(functions!=None)
    self.assert_(functions.__class__==COPASI.CFunctionDB)

  def test_getKeyFactory(self):
      keyFactory = COPASI.CCopasiRootContainer.getKeyFactory()
      self.assert_(keyFactory != None)
      self.assert_(keyFactory.__class__ == COPASI.CKeyFactory)

def suite():
  tests=[
          'test_getRoot'
         ,'test_AddRemoveDatamodel'
         ,'test_getFunctionList'
         ,'test_getKeyFactory'
        ]
  return unittest.TestSuite(map(Test_CCopasiRootContainer,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


