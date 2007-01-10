# Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

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

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())

    
