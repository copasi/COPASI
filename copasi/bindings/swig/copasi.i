// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/copasi.i,v $ 
//   $Revision: 1.26.6.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/12 15:18:48 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%module COPASI



%{

#define COPASI_MAIN
#include "copasi.h"
#undef COPASI_MAIN

#include "local.cpp"

%}

%ignore DebugFile;

%include "copasi.h"

%include std_string.i
%include std_vector.i

//enum TriLogic
//{
//  TriUnspecified = -1,
//  TriFalse = 0,
//  TriTrue = 1
//};

%include "CVector.i"
%include "CRandom.i"
%include "CCopasiMessage.i"
%include "messages.i"
%include "CCopasiException.i"
%include "CCopasiObjectName.i"
%include "CCopasiObject.i"
%include "CCopasiContainer.i"
%include "CCopasiArray.i"
%include "CAnnotatedMatrix.i"
%include "CCopasiVector.i"
%include "CEigen.i"
%include "CFunctionParameter.i"
%include "CFunctionParameters.i"
%include "CEvaluationTree.i"
%include "CFunction.i"
%include "CFunctionDB.i"
%include "CCopasiParameter.i"
%include "CCopasiParameterGroup.i"
%include "CCopasiStaticString.i"
%include "CMoiety.i"
%include "CModelValue.i"
%include "CMetab.i"
%include "CCompartment.i"
%include "CMatrix.i"
%include "CState.i"
%include "CChemEqElement.i"
%include "CChemEq.i"
%include "CReaction.i"
%include "CModel.i"
%include "CVersion.i"
%include "CCopasiMethod.i"
%include "CCopasiProblem.i"
%include "COutputHandler.i"
%include "CReport.i"
%include "CCopasiTask.i"
%include "CReportDefinition.i"
%include "CReportDefinitionVector.i"
%include "CCopasiDataModel.i"
%include "CTimeSeries.i"
%include "CTrajectoryProblem.i"
%include "CTrajectoryMethod.i"
%include "CTrajectoryTask.i"
%include "COutputAssistant.i"
%include "CSteadyStateProblem.i"
%include "CSteadyStateMethod.i"
%include "CSteadyStateTask.i"
%include "CNewtonMethod.i"
%include "CScanMethod.i"
%include "CScanProblem.i"
%include "CScanTask.i"
%include "CLyapMethod.i"
%include "CLyapProblem.i"
%include "CLyapTask.i"
%include "COptItem.i"
%include "COptMethod.i"
%include "COptProblem.i"
%include "COptTask.i"
%include "compare_utilities.i"


