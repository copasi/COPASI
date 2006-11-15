import COPASI
import unittests
from types import *

class Test_CCopasiContainer(unittests.TestCase):

  def  test_ObjectFromName(self):
    self._assert(false)


def suite():
  tests=[
          'test_ObjectFromName'
        ]
  return unittests.TestSuite(map(Test_CCopasiContainer,tests))

