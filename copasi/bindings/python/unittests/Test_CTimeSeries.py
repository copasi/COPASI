import COPASI
import unittests
from types import *

class Test_CTimeSeries(unittests.TestCase):
  def setUp(self):
    COPASI.CCopasiDataModel.GLOBAL.load("calcium_juergen.cps")
    self.ctimeseries=COPASI.CTimeSeries()
    self.ctimeseries.init(100,COPASI.CCopasiDataModel.GLOBAL.getModel())
    self.ctimeseries.add()
    self.ctimeseries.finish()

  def test_getNumSteps(self)
    steps=self.ctimeseries.getNumSteps()
    self.assert_(type(steps)==IntType)
    self.assert_(steps==1)

  def test_getNumVariables(self)
    variables=self.ctimeseries.getNumVariables()
    self.assert_(type(variables)==IntType)
    self.assert(variables==4)

  def test_getData(self)
    data=self.ctimeseries.getData(0,1)
    self.assert_(type(data)==DoubleType)
    self.assert_(data==float("nan"))

  def test_getConcentrationData(self):
    data=self.ctimeseries.getConcentrationData(0,1)
    self.assert_(type(data)==DoubleType)
    self.assert_(data==float("nan"))

  def test_getTitle(self):
    title=self.ctimeseries.getTitle(1)
    self.assert_(type(title)==StringType)
    self.assert_(title=="a")



