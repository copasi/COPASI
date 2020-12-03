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

import COPASI
import unittest
from types import *
import string


class Test_CRootContainer(unittest.TestCase):
  def setUp(self):
    datamodelList=COPASI.CRootContainer.getDatamodelList()
    datamodelList.clear()

  def test_getRoot(self):
    root = COPASI.CRootContainer.getRoot()
    self.assert_(root != None)
    self.assert_(root.__class__ == COPASI.CRootContainer)

  def test_AddRemoveDatamodel(self):
      datamodelList=COPASI.CRootContainer.getDatamodelList()
      self.assert_(datamodelList.__class__ == COPASI.DataModelVector)
      self.assertEqual(datamodelList.size(), 0)
      datamodel = COPASI.CRootContainer.addDatamodel()
      self.assert_(datamodel != None)
      self.assert_(datamodel.__class__ == COPASI.CDataModel)
      self.assert_(datamodelList.size() == 1)
      datamodel = COPASI.CRootContainer.addDatamodel()
      self.assert_(datamodel != None)
      self.assert_(datamodel.__class__ == COPASI.CDataModel)
      self.assert_(datamodelList.size() == 2)
      result = COPASI.CRootContainer.removeDatamodelWithIndex(0)
      self.assert_(result == True)
      self.assert_(datamodelList.size() == 1)
      result = COPASI.CRootContainer.removeDatamodel(datamodel)
      self.assert_(result == True)
      self.assert_(datamodelList.size() == 0)


  def test_getFunctionList(self):
    functions=COPASI.CRootContainer.getFunctionList()
    self.assert_(functions!=None)
    self.assert_(functions.__class__==COPASI.CFunctionDB)

  def test_getKeyFactory(self):
      keyFactory = COPASI.CRootContainer.getKeyFactory()
      self.assert_(keyFactory != None)
      self.assert_(keyFactory.__class__ == COPASI.CKeyFactory)

def suite():
  tests=[
          'test_getRoot'
         ,'test_AddRemoveDatamodel'
         ,'test_getFunctionList'
         ,'test_getKeyFactory'
        ]
  return unittest.TestSuite(map(Test_CRootContainer,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


