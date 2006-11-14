import COPASI
import unittests
from types import *


class Test_CCompartment(unittests.TestCase):
  def setUp(self):
    self.model=COPASI.CModel()
    self.compartment=self.model.createCompartment("Comp1")
    self.model.createMetabolite("metab1","Comp1")
    self.model.createMetabolite("metab2","Comp1")
    self.metab=self.model.createMetabolite("metab3","Comp1")
    self.model.createMetabolite("metab4","Comp1")
    self.model.createMetabolite("metab5","Comp1")

  def getMetabolites(self):
    metabolites=self.compartment.getMetabolites()
    self._assert(false)

  def test_removeMetabolite(self):
    self.compartment.removeMetabolite(self.metab)
    self._assert(false)

  def test_setInitialValue(self):
    value=5.0
    self.compartment.setInitialValue(value)
    self._assert(math.abs((self.compartment.getInitialValue()-value)/value)<0.001)
    




