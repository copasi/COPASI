# -*- coding: utf-8 -*-
# Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

import COPASI
import unittest
from types import *
import string

CPS_FILE="calcium_juergen.cps"
SBML_FILE="calcium_juergen.xml"

class Test_CDataModel(unittest.TestCase):
  def setUp(self):
    self.datamodel=COPASI.CRootContainer.addDatamodel()

  def test_loadModel(self):
    self.assert_(self.datamodel.loadModel(CPS_FILE),"Error. Could not load model.")
    self.CHECK_CALCIUM_JUERGEN()

  def test_saveModel(self):
    self.assert_(self.datamodel.loadModel(CPS_FILE),"Error. Could not load model.")
    TMPFILE="calcium_juergen2.cps"
    self.assert_(self.datamodel.saveModel(TMPFILE,True),"Error. Could not save model.")
    self.assert_(self.datamodel.loadModel(TMPFILE),"Error. Could not reload saved model.")
    self.CHECK_CALCIUM_JUERGEN()

  def test_newModel(self):
    self.assert_(self.datamodel.newModel())
    

  def test_importSBMLFromString(self):
    FILE=file(SBML_FILE,"r")
    FILECONTENT=string.join(FILE.readlines())
    self.assert_(self.datamodel.importSBMLFromString(FILECONTENT))
    self.CHECK_CALCIUM_JUERGEN_MODEL()


  def test_importSBML(self):
    self.assert_(self.datamodel.importSBML(SBML_FILE))
    self.CHECK_CALCIUM_JUERGEN_MODEL()

  def test_exportSBMLToString(self):
    self.assert_(self.datamodel.loadModel(CPS_FILE))
    modelString=self.datamodel.exportSBMLToString()
    self.assert_(type(modelString)==str)
    self.assert_(modelString!="")

  def test_exportSBML(self):
    self.assert_(self.datamodel.loadModel(CPS_FILE))
    FILENAME="calcium_juergen2.xml"
    self.assert_(self.datamodel.exportSBML(FILENAME,True))

  def test_getModel(self):
    model=self.datamodel.getModel()
    self.assert_(model.__class__==COPASI.CModel)

  def test_getTaskList(self):
    taskList=self.datamodel.getTaskList()
    self.assert_(taskList.__class__==COPASI.TaskVectorN)

  def test_addDefaultTasks(self):
    while(self.datamodel.getTaskList().size()!=0):
        self.datamodel.getTaskList().remove(0)
    self.assert_(self.datamodel.getTaskList().size()==0)
    self.datamodel.addDefaultTasks()
    self.assert_(self.datamodel.getTaskList().size()!=0)


  def test_getReportDefinitionList(self):
    reportDefinitionList=self.datamodel.getReportDefinitionList()
    self.assert_(reportDefinitionList.__class__==COPASI.CReportDefinitionVector)

  def test_addDefaultReports(self):
    while(self.datamodel.getReportDefinitionList().size()!=0):
        self.datamodel.getReportDefinitionList().remove(0)
    self.assert_(self.datamodel.getReportDefinitionList().size()==0)
    self.datamodel.addDefaultReports()
    self.assert_(self.datamodel.getReportDefinitionList().size()!=0)

  def test_getFileName(self):
    self.datamodel.loadModel(CPS_FILE)
    fileName=self.datamodel.getFileName()
    self.assert_(type(fileName)==str)
    self.assert_(fileName.endswith(CPS_FILE))

  def test_getSBMLFileName(self):
    self.datamodel.importSBML(SBML_FILE)
    fileName=self.datamodel.getSBMLFileName()
    self.assert_(type(fileName)==str)
    self.assert_(fileName.endswith(SBML_FILE))

  def CHECK_CALCIUM_JUERGEN(self):
    # check the model
    self.CHECK_CALCIUM_JUERGEN_MODEL()
    # test getTaskList
    taskList=self.datamodel.getTaskList()
    # test getReportDefinitionList
    reportDefinitionList=self.datamodel.getReportDefinitionList()
    # test getFileName
    fileName=self.datamodel.getFileName()

  def CHECK_CALCIUM_JUERGEN_MODEL(self):
    # test getModel
    model=self.datamodel.getModel()


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
         ,'test_getTaskList'
         ,'test_addDefaultTasks'
         ,'test_getReportDefinitionList'
         ,'test_addDefaultReports'
         ,'test_getFileName'
         ,'test_getSBMLFileName'
        ]
  return unittest.TestSuite(map(Test_CDataModel,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


