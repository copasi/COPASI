# -*- coding: utf-8 -*-
# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CTrajectoryMethod.py,v $ 
#   $Revision: 1.6 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/04/21 10:27:07 $ 
# End CVS Header 
# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
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

    
