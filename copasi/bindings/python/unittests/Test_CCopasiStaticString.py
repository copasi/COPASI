import COPASI
import unittest
from types import *


class Test_CCopasiStaticString(unittest.TestCase):
  def setUp(self):
    self.s="this_is_a_test"
    self.string=COPASI.CCopasiStaticString(self.s)

  def test_getObjectDisplayName(self):
    st=self.string.getObjectDisplayName()
    self.assert_(type(st)==StringType)
    self.assert_(st==self.s)

  def test_getStaticString(self):
    st=self.string.getStaticString()
    self.assert_(type(st)==StringType)
    self.assert_(st==self.s)


def suite():
  tests=[
          'test_getObjectDisplayName'
         ,'test_getStaticString'
        ]
  return unittest.TestSuite(map(Test_CCopasiStaticString,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


