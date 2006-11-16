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
    self.assert_(type(steps)==IntType)
    self.assert_(steps==1)

  def test_getNumVariables(self):
    variables=self.ctimeseries.getNumVariables()
    self.assert_(type(variables)==IntType)
    self.assert_(variables==4)

  def test_getData(self):
    data=self.ctimeseries.getData(0,1)
    self.assert_(type(data)==FloatType)
    # check if it is NaN since NaN != NaN
    self.assert_(data!=data)

  def test_getConcentrationData(self):
    data=self.ctimeseries.getConcentrationData(0,1)
    self.assert_(type(data)==FloatType)
    # check if it is NaN since NaN != NaN
    self.assert_(data!=data)

  def test_getTitle(self):
    title=self.ctimeseries.getTitle(1)
    self.assert_(type(title)==StringType)
    self.assert_(title=="a")


def suite():
  tests=[
          'test_getNumSteps'
         ,'test_getNumVariables'
         ,'test_getData'
         ,'test_getConcentrationData'
         ,'test_getTitle'
        ]
  return unittest.TestSuite(map(Test_CTimeSeries,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


