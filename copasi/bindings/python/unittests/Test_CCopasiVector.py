# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CCopasiVector.py,v $ 
#   $Revision: 1.11.14.1 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/04/08 15:01:33 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

import COPASI
import unittest
from types import *


class Test_CCopasiVector(unittest.TestCase):
  def setUp(self):
    COPASI.CCopasiDataModel.GLOBAL.newModel()
    self.model=COPASI.CCopasiDataModel.GLOBAL.getModel()
    self.compartment=self.model.createCompartment("Comp1")
    self.model.createMetabolite("metab1","Comp1")
    self.model.createMetabolite("metab2","Comp1")
    self.metab=self.model.createMetabolite("metab3","Comp1")
    self.model.createMetabolite("metab4","Comp1")
    self.model.createMetabolite("metab5","Comp1")
    self.vector=self.compartment.getMetabolites()

  def test_add(self):
    v=COPASI.CompartmentVectorNS()
    comp=COPASI.CCompartment("test_compartment")
    self.assert_(v.add(comp))
    self.assert_(v.size()==1)

  def test_remove(self):
    n=self.vector.size()  
    self.vector.removeObject(self.metab)
    self.assert_(self.vector.size()==n-1)
    self.vector.remove(0)
    self.assert_(self.vector.size()==n-2)

  def test_remove_viaName(self):
    n=self.vector.size()  
    self.vector.removeByName(self.metab.getObjectName())
    self.assert_(self.vector.size()==n-1)


  def test_size(self):
    n=self.vector.size()
    self.assert_(type(n)==IntType)
    self.assert_(n==5)

  def test_getIndex(self):
   index=self.vector.getIndex(self.metab)
   self.assert_(type(index)==IntType)
   self.assert_(index==2)
   index=self.vector.getIndexByName(self.metab.getObjectName())
   self.assert_(type(index)==IntType)
   self.assert_(index==2)



def suite():
  tests=[
          'test_add'
         ,'test_remove'
         ,'test_remove_viaName'
         ,'test_size'
         ,'test_getIndex'
        ]
  return unittest.TestSuite(map(Test_CCopasiVector,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


