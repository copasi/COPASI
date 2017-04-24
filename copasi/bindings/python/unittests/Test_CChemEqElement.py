# -*- coding: utf-8 -*-
# Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
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

class Test_CChemEqElement(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CRootContainer.addDatamodel()
    self.model=self.datamodel.getModel()
    self.model.createCompartment("comp1",1.0)
    self.model.createCompartment("comp2",4.0)
    self.m1=self.model.createMetabolite("A","comp1")
    self.m2=self.model.createMetabolite("B","comp2")
    self.m3=self.model.createMetabolite("C","comp1")
    r=self.model.createReaction("react1")
    r.addSubstrate(self.m1.getKey())
    r.addProduct(self.m2.getKey())
    r.addModifier(self.m3.getKey())
    self.model.compileIfNecessary()
    self.chemeq=r.getChemEq()
    self.element=self.chemeq.getSubstrate(0)
    self.assert_(self.element!=None)
    self.assert_(self.element.__class__==COPASI.CChemEqElement)

  def test_getMultiplicity(self):
    n=self.element.getMultiplicity()
    self.assert_(type(n)==FloatType)
    self.assert_(n==1.0)

  def test_setMultiplicity(self):
    v=5.2
    self.element.setMultiplicity(v)
    self.assert_(self.element.getMultiplicity()==v)
    

  def test_addToMultiplicity(self):
    n=self.element.getMultiplicity()
    self.element.addToMultiplicity()
    self.assert_(self.element.getMultiplicity()==n+1)
    n2=2.3
    self.element.addToMultiplicity(n2)
    self.assert_(self.element.getMultiplicity()==n+n2+1)

  def test_setMetabolite(self):
    self.element.setMetabolite(self.m3.getKey())
    self.assert_(self.element.getMetabolite().getKey()==self.m3.getKey())

  def test_getMetabolite(self):
    m=self.element.getMetabolite()
    self.assert_(m!=None)
    self.assert_(m.__class__==COPASI.CMetab)
    self.assert_(m.getKey()==self.m1.getKey())

  def test_getMetaboliteKey(self):
    key=self.element.getMetaboliteKey()
    self.assert_(type(key)==StringType)


def suite():
  tests=[
          "test_getMultiplicity"
          ,"test_setMultiplicity"
          ,"test_addToMultiplicity"
          ,"test_getMetabolite"
          ,"test_setMetabolite"
          ,"test_getMetaboliteKey"
        ]
  return unittest.TestSuite(map(Test_CChemEqElement,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


