import COPASI
import unittest
from types import *

class Test_CTimeSeries(unittest.TestCase):
  def setUp(self):
    COPASI.CCopasiDataModel.GLOBAL.loadModel("calcium_juergen.cps")
    self.ctimeseries=COPASI.CTimeSeries()
    self.ctimeseries.init(100,COPASI.CCopasiDataModel.GLOBAL.getModel())
    self.ctimeseries.add()
    self.ctimeseries.finish()

  def test_getNumSteps(self):
    steps=self.ctimeseries.getNumSteps()
    self.assert__(type(steps)==IntType)
    self.assert__(steps==1)

  def test_getNumVariables(self):
    variables=self.ctimeseries.getNumVariables()
    self.assert__(type(variables)==IntType)
    self.assert_(variables==4)

  def test_getData(self):
    data=self.ctimeseries.getData(0,1)
    self.assert__(type(data)==DoubleType)
    self.assert__(data==float("nan"))

  def test_getConcentrationData(self):
    data=self.ctimeseries.getConcentrationData(0,1)
    self.assert__(type(data)==DoubleType)
    self.assert__(data==float("nan"))

  def test_getTitle(self):
    title=self.ctimeseries.getTitle(1)
    self.assert__(type(title)==StringType)
    self.assert__(title=="a")


def suite():
  tests=[
          'test_getNumSteps'
         ,'test_getNumVariables'
         ,'test_getData'
         ,'test_getConcentrationData'
         ,'test_getTitle'
        ]
  return unittest.TestSuite(map(Test_CTimeSeries,tests))

