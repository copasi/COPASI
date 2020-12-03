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

class Test_CDataObject(unittest.TestCase):
    def setUp(self):
      self.datamodel=COPASI.CRootContainer.addDatamodel()
      self.model=self.datamodel.getModel()
      self.compartment=self.model.createCompartment("Comp1")
      self.object=self.model.createMetabolite("Metab1","Comp1")
      self.model.compileIfNecessary()

    def test_getObjectName(self):
      t=self.object.getObjectName()
      self.assert_(type(t)==str)

    def test_setObjectName(self):
      NAME="MyObject"
      self.object.setObjectName(NAME)
      self.assert_(self.object.getObjectName()==NAME)

    def test_getObjectDisplayName(self):
      t=self.object.getObjectDisplayName()
      self.assert_(type(t)==str)

    def test_getObjectType(self):
      t=self.object.getObjectType()
      self.assert_(type(t)==str)

    def test_getObjectParent(self):
      parent=self.object.getObjectParent()  
      self.assert_(parent!=None)
      self.assert_(parent.__class__==COPASI.MetabVectorNS)
      self.assert_(parent.getKey()==self.compartment.getMetabolites().getKey())

    def test_getCN(self):
      cn=self.object.getCN()
      self.assert_(cn.__class__==COPASI.CCommonName)

    def test_getKey(self):
      key=self.object.getKey()
      self.assert_(type(key)==str) 

def suite():
  tests=[
          'test_getObjectName'
         ,'test_setObjectName'
         ,'test_getObjectDisplayName'
         ,'test_getObjectType'
         ,'test_getObjectParent'
         ,'test_getCN'
         ,'test_getKey'
        ]
  return unittest.TestSuite(map(Test_CDataObject,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


