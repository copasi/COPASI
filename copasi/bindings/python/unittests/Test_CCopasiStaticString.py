# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CCopasiStaticString.py,v $ 
#   $Revision: 1.7.14.1 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/04/08 15:01:33 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

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
    self.assert_(st=="'"+self.s+"'")

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


