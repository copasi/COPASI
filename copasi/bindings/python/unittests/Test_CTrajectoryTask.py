import COPASI
import unittest
from types import *


class Test_CTrajectoryTask(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CCopasiDataModel.GLOBAL
    self.datamodel.loadModel("calcium_juergen.cps")


  def test_process(self):
    # can only be tested once we can get the correct object type from the vector
    self.assert_(0)

  def test_getState(self):
    # can only be tested once we can get the correct object type from the vector
    self.assert_(0)

  def test_setMethodType(self):
    # can only be tested once we can get the correct object type from the vector
    self.assert_(0)

  def test_getTimeSeries(self):
    # can only be tested once we can get the correct object type from the vector
    self.assert_(0)

def suite():
  tests=[
          'test_process'
         ,'test_getState'
         ,'test_getTimeSeries'
         ,'test_setMethodType'
        ]
  return unittest.TestSuite(map(Test_CTrajectoryTask,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


