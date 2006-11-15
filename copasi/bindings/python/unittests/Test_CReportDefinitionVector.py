import COPASI
import unittests
from types import *


class Test_CReportDefinitionVector(unittests.TestCase):
  def setUp(self):
    self.vec=COPASI.CReportDefinitionVector();

  def test_getKey(self):
    key=self.vec.getKey()
    self._assert(type(key)==StringType)

  def test_createReportDefinition(self):
    name="testReport"
    comment="test test test"
    size=self.vect.size()
    repdef=self.vec.createReportDefinition(name,comment)
    self._assert(self.vec.size()==size+1)
    self._assert(repdef.__class__==COPASI.CReportDefinition)
    self._assert(repdef.getObjectName()==name)
    self._assert(repdef.getComment()==comment)


  def test_removeReportDefinition(self):
    name="testReport"
    comment="test test test"
    size=self.vec.size()
    repdef=self.vec.createReportDefinition(name,comment)
    self._assert(self.vec.size()==size+1)
    key=repdef.getKey()
    self.vec.removeReportDefinition(key)
    self._assert(self.vec.size()==size)



def suite():
  tests=[
          'test_getKey'
         ,'test_createReportDefinition'
         ,'test_removeReportDefinition'
        ]
  return unittests.TestSuite(map(Test_CReportDefinitionVector,tests))

