import COPASI
import unittest
from types import *


class Test_CTrajectoryMethod(unittest.TestCase):
  def setUp(self):
    self.method=COPASI.CTrajectoryMethod.createTrajectoryMethod(COPASI.CCopasiMethod.deterministic,CTrajectoryProblem())


def suite():
  tests=[
        ]
  return unittest.TestSuite(map(Test_CTrajectoryMethod,tests))
    
