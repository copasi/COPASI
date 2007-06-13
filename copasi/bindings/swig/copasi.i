// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/copasi.i,v $ 
//   $Revision: 1.17 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2007/06/13 12:58:12 $ 
// End CVS Header 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%module COPASI

%{

#define COPASI_MAIN
#include "copasi.h"
#undef COPASI_MAIN

#include "local.cpp"

%}

%import "copasi.h"

%include std_string.i
%include std_vector.i

%include "CRandom.i"
%include "CCopasiObjectName.i"
%include "CCopasiObject.i"
%include "CCopasiContainer.i"
%include "CAnnotatedMatrix.i"
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
%include "CCopasiVector.i"
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
%include "CCopasiMessage.i"
%include "CSteadyStateProblem.i"
%include "CSteadyStateMethod.i"
%include "CSteadyStateTask.i"
%include "CNewtonMethod.i"
%include "CScanMethod.i"
%include "CScanProblem.i"
%include "CScanTask.i"


