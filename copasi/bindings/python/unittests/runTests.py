#!/usr/bin/python
# -*- coding: utf-8 -*-
# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/unittests/runTests.py,v $ 
#   $Revision: 1.8.6.2 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/04/14 08:19:40 $ 
# End CVS Header 
# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

import unittest
import Test_CCopasiMessage
import Test_CChemEq
import Test_CChemEqElement
import Test_CCompartment
import Test_CCopasiContainer
import Test_CCopasiDataModel
import Test_CCopasiMethod
import Test_CCopasiObject
import Test_CCopasiObjectName
import Test_CCopasiParameter
import Test_CCopasiParameterGroup
import Test_CCopasiProblem
import Test_CCopasiStaticString
import Test_CCopasiTask
import Test_CCopasiVector
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

suites=[
          Test_CVersion.suite()
         ,Test_CCopasiMessage.suite()
         ,Test_CState.suite()
         ,Test_CTimeSeries.suite()
         ,Test_CCopasiObject.suite()
         ,Test_CCopasiContainer.suite()
         ,Test_CMoiety.suite()
         ,Test_CModelValue.suite()
         ,Test_CMetab.suite()
	 ,Test_CChemEq.suite()
	 ,Test_CChemEqElement.suite()
         ,Test_CCopasiVector.suite()
         ,Test_CMatrix.suite()
         ,Test_CCopasiStaticString.suite()
         ,Test_CCopasiObjectName.suite()
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
         ,Test_CCopasiDataModel.suite()
	 ,Test_CFunctionDB.suite()
	 ,Test_CEvaluationTree.suite()
	 ,Test_CFunction.suite()
	 ,Test_CFunctionParameters.suite()
	 ,Test_CFunctionParameter.suite()
         ,Test_CReport.suite()
         ,Test_COutputAssistant.suite()
         ,Test_CreateSimpleModel.suite()
         ,Test_RunSimulations.suite()
       ]

def suite():
    return unittest.TestSuite(suites)

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


