import COPASI
import unittests
from types import *


class Test_CTrajectoryMethod(unittests.TestCase):
  def setUp(self):
    self.method=COPASI.CTrajectoryMethod.createTrajectoryMethod(COPASI.CCopasiMethod.deterministic,CTrajectoryProblem())


def suite():
  tests=[
        ]
  return unittests.TestSuite(map(Test_CTrajectoryMethod,tests))
    
