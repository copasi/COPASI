import COPASI
import unittest
from types import *


class Test_CReportDefinitionVector(unittest.TestCase):
  def setUp(self):
    self.vec=COPASI.CReportDefinitionVector();

  def test_getKey(self):
    key=self.vec.getKey()
    self.assert_(type(key)==StringType)

  def test_createReportDefinition(self):
    name="testReport"
    comment="test test test"
    size=self.vect.size()
    repdef=self.vec.createReportDefinition(name,comment)
    self.assert_(self.vec.size()==size+1)
    self.assert_(repdef.__class__==COPASI.CReportDefinition)
    self.assert_(repdef.getObjectName()==name)
    self.assert_(repdef.getComment()==comment)


  def test_removeReportDefinition(self):
    name="testReport"
    comment="test test test"
    size=self.vec.size()
    repdef=self.vec.createReportDefinition(name,comment)
    self.assert_(self.vec.size()==size+1)
    key=repdef.getKey()
    self.vec.removeReportDefinition(key)
    self.assert_(self.vec.size()==size)



def suite():
  tests=[
          'test_getKey'
         ,'test_createReportDefinition'
         ,'test_removeReportDefinition'
        ]
  return unittest.TestSuite(map(Test_CReportDefinitionVector,tests))

