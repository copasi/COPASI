import COPASI
import unittests
from types import *


class Test_CTrajectoryTask(unittests.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CCopasiDataModel.GLOBAL
    self.datamodel.loadModel("calcium_juergen.cps")


  def test_process(self):
    # can only be tested once we can get the correct object type from the vector
    self._assert(false)

  def test_getState(self):
    # can only be tested once we can get the correct object type from the vector
    self._assert(false)

  def test_setMethodType(self):
    # can only be tested once we can get the correct object type from the vector
    self._assert(false)

  def test_getTimeSeries(self):
    # can only be tested once we can get the correct object type from the vector
    self._assert(false)

def suite():
  tests=[
          'test_process'
         ,'test_getState'
         ,'test_getTimeSeries'
         ,'test_setMethodType'
        ]
  return unittests.TestSuite(map(Test_CTrajectoryTask,tests))

