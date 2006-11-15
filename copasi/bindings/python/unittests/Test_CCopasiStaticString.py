import COPASI
import unittest
from types import *


class Test_CCopasiStaticString(unittest.TestCase):
  def setUp(self):
    self.s="this_is_a_test"
    self.string=COPASI.CCopasiStaticString(self.s)

  def test_getObjectDisplayName(self):
    st=this.string.getObjectDisplayName()
    self._assert(type(st)==StringType)
    self._assert(st==self.s)

  def test_getStaticString(self):
    st=this.string.getStaticString()
    self._assert(type(st)==StringType)
    self._assert(st==self.s)


def suite():
  tests=[
          'test_getObjectDisplayName'
         ,'test_getStaticString'
        ]
  return unittest.TestSuite(map(Test_CCopasiStaticString,tests))

