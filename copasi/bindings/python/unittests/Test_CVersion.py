import COPASI
import unittest
from types import *

class Test_CVersion(unittest.TestCase):
  def setUp(self):
    self.cversion=CVersion()
  
  def test_getVersionMajor(self):
    versionMajor=self.cversion.getVersionMajor()
    self.assert_(type(versionMajor)==IntType)

  def test_getVersionMinoar(self):
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
    

