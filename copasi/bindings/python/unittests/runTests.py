# -*- coding: utf-8 -*-
# Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual </comment>
# Properties, Inc., University of Heidelberg, and The University </comment>
# of Manchester. </comment>
# All rights reserved. </comment>

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual </comment>
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, </comment>
# and The University of Manchester. </comment>
# All rights reserved. </comment>

# Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual </comment>
# Properties, Inc. and EML Research, gGmbH. </comment>
# All rights reserved. </comment>

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
#import Test_CCopasiVector
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
import Test_CReportTemplate
import Test_CReportTemplateVector
import Test_RunSimulations
import Test_CState
import Test_CTimeSeries
import Test_CTrajectoryMethod
import Test_CTrajectoryProblem
import Test_CTrajectoryTask
import Test_CVersion
import Test_CEvent
import Test_CCopasiRootContainer

suites=[
          Test_CVersion.suite()
         ,Test_CCopasiRootContainer.suite()
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
#         ,Test_CCopasiVector.suite()
         ,Test_CMatrix.suite()
         ,Test_CCopasiStaticString.suite()
         ,Test_CCopasiObjectName.suite()
         ,Test_CCopasiParameter.suite()
         ,Test_CCopasiParameterGroup.suite()
         ,Test_CReportTemplate.suite()
         ,Test_CReportTemplateVector.suite()
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
         ,Test_CEvent.suite()
         ,Test_COutputAssistant.suite()
         ,Test_CreateSimpleModel.suite()
         ,Test_RunSimulations.suite()
       ]

def suite():
    return unittest.TestSuite(suites)

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


