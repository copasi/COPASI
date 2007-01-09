import COPASI
import unittest
from types import *


class Test_CReport(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CCopasiDataModel.GLOBAL
    self.task=self.datamodel.getTask(0)
    self.report=self.task.getReport()

  def test_getReportDefinition(self):
    reportDefinition=self.report.getReportDefinition()
    self.assert_(reportDefinition!=None)
    self.assert_(reportDefinition.__class__==COPASI.CReportDefinition)

  def test_setReportDefinition(self):
    listOfReportDefinitions=self.datamodel.getReportDefinitionList()
    reportDefinition=listOfReportDefinitions.createReportDefinition("MyReportDefinition","No Comment")
    self.assert_(reportDefinition!=None)
    self.report.setReportDefinition(reportDefinition)
    self.assert_(self.report.getReportDefinition().getKey()==reportDefinition.getKey())

  def test_getTarget(self):
    target=self.report.getTarget()
    self.assert_(target!=None)
    self.assert_(type(target)==StringType)

  def test_setTarget(self):
    target="MyTaget.txt"
    self.report.setTarget(target)
    t=self.report.getTarget()
    self.assert_(t!=None)
    self.assert_(t==target)

  def test_append(self):
    append=self.report.append()
    self.assert_(type(append)==BooleanType)

  def test_setAppend(self):
    self.report.setAppend(True)
    append=self.report.append()
    self.assert_(append==True)
    self.report.setAppend(False)
    append=self.report.append()
    self.assert_(append==False)




def suite():
  tests=[
          'test_getReportDefinition'                       
         ,'test_setReportDefinition'                       
         ,'test_getTarget'                       
         ,'test_setTarget'                       
         ,'test_append'                       
         ,'test_setAppend'                       
        ]
  return unittest.TestSuite(map(Test_CReport,tests))


if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


                                      
