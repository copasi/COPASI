import COPASI
import unittest
from types import *

class Test_CVersion(unittest.TestCase):
  def setUp(self):
    self.cversion=CVersion()
  
  def test_getVersionMajor(self):
    versionMajor=self.cversion.getVersionMajor()
    self._assert(type(versionMajor)==IntType)

  def test_getVersionMinor(self):
    versionMinor=self.cversion.getVersionMinor()
    self._assert(type(versionMinor)==IntType)

  def test_getVersionDevel(self):
    versionDevel=self.cversion.getVersionDevel()
    self._assert(type(versionDevel)==IntType)

  def test_getVersion(self):
    version=self.cversion.getVersion()
    self._assert(type(version)==StringType)

  def test_setVersion(self):
    self.cversion.setVersion(5,12,57,"testtesttest")
    self._assert(self.cversion.getVersionMajor()==5)
    self._assert(self.cversion.getVersionMinor()==12)
    self._assert(self.cversion.getVersionDevel()==57)
    

def suite():
  tests=[
          'test_getVersionMajor'
         ,'test_getVersionMinor'
         ,'test_getVersionDevel'
         ,'test_getVersion'
         ,'test_setVersion'
        ]
  return unittests.TestSuite(map(Test_CVersion,tests))

