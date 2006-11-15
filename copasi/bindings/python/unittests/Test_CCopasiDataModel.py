import COPASI
import unittest
import types
import string

CPS_FILE="calcium_juergen.cps"
SBML_FILE="calcium_juergen.xml"

class Test_CCopasiDataModel(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CCopasiDataModel.GLOBAL

  def test_loadModel(self):
    self.assert_(datamodel.loadModel(CPS_FILE))
    self.CHECK_CALCIUM_JUERGEN()

  def test_saveModel(self):
    self.assert_(datamodel.loadModel(CPS_FILE))
    TMPFILE="calcium_juergen2.cps"
    self.assert_(datamodel.saveModel(TMPFILE,true))
    self.assert_(datamodel.loadModel(TMPFILE))
    self.CHECK_CALCIUM_JUERGEN()

  def test_newModel(self):
    self.assert_(datamodel.newModel())
    

  def test_importSBMLFromString(self):
    FILE=file(SBML_FILE,"r")
    FILECONTENT=string.join(FILE.readlines())
    self.assert_(datamodel.importSBMLFromString(FILECONTENT))
    self.CHECK_CALCIUM_JUERGEN_MODEL()


  def test_importSBML(self):
    self.assert_(datamodel.importSBML(SBML_FILE))
    self.CHECK_CALCIUM_JUERGEN_MODEL()

  def test_exportSBMLToString(self):
    self.assert_(datamodel.loadModel(CPS_FILE))
    modelString=datamodel.exportSBMLToString()
    self.assert_(types.type(modelString)==types.StringType)
    self.assert_(modelString!="")

  def test_exportSBML(self):
    datamodel.loadModel(CPS_FILE)
    FILENAME=calcium_juergen2.xml
    self.assert_(datamodel.exportSBML(FILENAME,true))

  def test_getModel(self):
   # test getModel
    model=datamodel.getModel()
    self.assert_(model.__class__==COPASI.CModel)

  def test_getVersion(self):
    # test getVersion
    version=datamodel.getVersion()
    self.assert_(version.__class__==COPASI.CVersion)

  def test_getTaskList(self):
    # test getTaskList
    taskList=datamodel.getTaskList()
    self.assert_(taskList.__class__==COPASI.TaskVectorN)

  def test_addTask(self):
    self._assert(false)

  def test_addDefaultTasks():
    self._assert(false)

  def test_getReportDefinitionList(self):
    # test getReportDefinitionList
    reportDefinitionList=datamodel.getReportDefinitionList()
    self.assert_(reportDefinitionList.__class__==COPASI.CReportDefinitionVector)

  def test_addReport(self):
    self._assert(false)

  def test_addDefaultReports(self):
    self._assert(false)

  def test_getFileName(self):
    datamodel.loadModel(CPS_FILE)
    fileName=datamodel.getFileName()
    self.assert_(types.type(fileName)==types.StringType)
    self.assert_(fileName==CPS_FILE)

  def test_getSBMLFileName(self):
    datamodel.importSBML(CPS_FILE)
    fileName=datamodel.getSBMLFileName()
    self.assert_(types.type(fileName)==types.StringType)
    self.assert_(fileName==SBML_FILE)

  def CHECK_CALCIUM_JUERGEN(self):
    # check the model
    self.CHECK_CALCIUM_JUERGEN_MODEL()
    # test getVersion
    version=datamodel.getVersion()
    # test getTaskList
    taskList=datamodel.getTaskList()
    # test getReportDefinitionList
    reportDefinitionList=datamodel.getReportDefinitionList()
    # test getFileName
    fileName=datamodel.getFileName()

  def CHECK_CALCIUM_JUERGEN_MODEL(self):
    # test getModel
    model=datamodel.getModel()

def suite():
  tests=[
          'test_loadModel'
         ,'test_saveModel'
         ,'test_newModel'
         ,'test_importSBMLFromString'
         ,'test_importSBML'
         ,'test_exportSBMLToString'
         ,'test_exportSBML'
         ,'test_getModel'
         ,'test_getVersion'
         ,'test_getTaskList'
         ,'test_addTask'
         ,'test_addDefaultTasks'
         ,'test_getReportDefinitionList'
         ,'test_addReport'
         ,'test_addDefaultReports'
         ,'test_getFileName'
         ,'test_getSBMLFileName'
        ]
  return unittest.TestSuite(map(Test_CCopasiDataModel,tests))

