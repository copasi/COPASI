# -*- coding: utf-8 -*-
# Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
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

import unittest
import Test_CCopasiMessage
import Test_CChemEq
import Test_CChemEqElement
import Test_CCompartment
import Test_CDataContainer
import Test_CDataModel
import Test_CCopasiMethod
import Test_CDataObject
import Test_CCommonName
import Test_CCopasiParameter
import Test_CCopasiParameterGroup
import Test_CCopasiProblem
import Test_CDataString
import Test_CCopasiTask
#import Test_CDataVector
import Test_CEvaluationTree
import Test_CFunction
import Test_CFunctionDB
import Test_CFunctionParameter
import Test_CFunctionParameters
import Test_CMatrix
import Test_CMetab
import Test_CModel
import Test_CModelValue
import Test_CMoiety
import Test_COutputAssistant
import Test_CReaction
import Test_CreateSimpleModel
import Test_CReport
import Test_CReportDefinition
import Test_CReportDefinitionVector
import Test_RunSimulations
import Test_CState
import Test_CTimeSeries
import Test_CTrajectoryMethod
import Test_CTrajectoryProblem
import Test_CTrajectoryTask
import Test_CVersion
import Test_CEvent
import Test_CRootContainer

suites=[
          Test_CVersion.suite()
         ,Test_CRootContainer.suite()
         ,Test_CCopasiMessage.suite()
         ,Test_CState.suite()
         ,Test_CTimeSeries.suite()
         ,Test_CDataObject.suite()
         ,Test_CDataContainer.suite()
         ,Test_CMoiety.suite()
         ,Test_CModelValue.suite()
         ,Test_CMetab.suite()
	 ,Test_CChemEq.suite()
	 ,Test_CChemEqElement.suite()
#         ,Test_CDataVector.suite()
         ,Test_CMatrix.suite()
         ,Test_CDataString.suite()
         ,Test_CCommonName.suite()
         ,Test_CCopasiParameter.suite()
         ,Test_CCopasiParameterGroup.suite()
         ,Test_CReportDefinition.suite()
         ,Test_CReportDefinitionVector.suite()
         ,Test_CReaction.suite()
         ,Test_CModel.suite()
         ,Test_CCopasiProblem.suite()
         ,Test_CCopasiMethod.suite()
         ,Test_CCopasiTask.suite()
         ,Test_CTrajectoryProblem.suite()
         ,Test_CTrajectoryMethod.suite()
         ,Test_CTrajectoryTask.suite()
         ,Test_CDataModel.suite()
	 ,Test_CFunctionDB.suite()
	 ,Test_CEvaluationTree.suite()
	 ,Test_CFunction.suite()
	 ,Test_CFunctionParameters.suite()
	 ,Test_CFunctionParameter.suite()
         ,Test_CReport.suite()
         ,Test_CEvent.suite()
         ,Test_COutputAssistant.suite()
         ,Test_CreateSimpleModel.suite()
         ,Test_RunSimulations.suite()
       ]

def suite():
    return unittest.TestSuite(suites)

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


