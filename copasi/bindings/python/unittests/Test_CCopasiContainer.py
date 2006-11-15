import COPASI
import unittest
from types import *

class Test_CCopasiContainer(unittest.TestCase):

  def  test_ObjectFromName(self):
    self.assert_(0)


def suite():
  tests=[
          'test_ObjectFromName'
        ]
  return unittest.TestSuite(map(Test_CCopasiContainer,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


