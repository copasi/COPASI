# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/Test_CVersion.py,v $ 
#   $Revision: 1.6.14.1 $ 
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

class Test_CVersion(unittest.TestCase):
  def setUp(self):
    self.cversion=COPASI.CVersion()
  
  def test_getVersionMajor(self):
    versionMajor=self.cversion.getVersionMajor()
    self.assert_(type(versionMajor)==IntType,"Error. the major version of CVersion is not an Integer type.")

  def test_getVersionMinor(self):
    versionMinor=self.cversion.getVersionMinor()
    self.assert_(type(versionMinor)==IntType)

  def test_getVersionDevel(self):
    versionDevel=self.cversion.getVersionDevel()
    self.assert_(type(versionDevel)==IntType)

  def test_getVersion(self):
    version=self.cversion.getVersion()
    self.assert_(type(version)==StringType)

  def test_setVersion(self):
    self.cversion.setVersion(5,12,57,"testtesttest")
    self.assert_(self.cversion.getVersionMajor()==5)
    self.assert_(self.cversion.getVersionMinor()==12)
    self.assert_(self.cversion.getVersionDevel()==57)
    

def suite():
  tests=[
          'test_getVersionMajor'
         ,'test_getVersionMinor'
         ,'test_getVersionDevel'
         ,'test_getVersion'
         ,'test_setVersion'
        ]
  return unittest.TestSuite(map(Test_CVersion,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


