import COPASI
import unittests
from types import *


class Test_CCopasiVector(unittests.TestCase):
  def setUp(self):
    self.model=COPASI.CModel()
    self.compartment=self.model.createCompartment("Comp1")
    self.model.createMetabolite("metab1","Comp1")
    self.model.createMetabolite("metab2","Comp1")
    self.metab=self.model.createMetabolite("metab3","Comp1")
    self.model.createMetabolite("metab4","Comp1")
    self.model.createMetabolite("metab5","Comp1")
    self.vector=self.compartment.getMetabolites()

  def test_add(self):
    self._assert(false)

  def test_remove(self):
    n=self.vector.size()  
    self.vector.remove(self.metab)
    self._assert(self.vector.size()==n-1)
    self.vector.remove(0)
    self._assert(self.vector.size()==n-2)

  def test_getObject(self):
    object=self.vector.getObject(self.metab.getCN())
    self._assert(object==self.metab)

  def test_size(self):
    n=self.vector.size()
    self._assert(type(n)==IntType)
    self._assert(n==5)

  def test_getIndex(self):
   index=self.vector.getIndex(self.metab)
   self._assert(type(index)==IntType)
   self._assert(index==2)



def suite():
  tests=[
          'test_add'
         ,'test_remove'
         ,'test_getObject'
         ,'test_size'
         ,'test_getIndex'
        ]
  return unittests.TestSuite(map(Test_CCopasiVector,tests))

