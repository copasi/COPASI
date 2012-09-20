<<<<<<< HEAD
=======

>>>>>>> resolved conflicts
// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%module COPASI



%{

#define COPASI_MAIN
#include "copasi.h"
#undef COPASI_MAIN

#include "local.cpp"

/**
 * This method is used to get the C_INVALID_INDEX
 * value in an architecture independent way.
 * Since size_t is defined differently depending on
 * the platform, the conversion from size_t to long in
 * java depends on the architecture and the result is different for
 * 32 bit and 64 bit systems.
 */
size_t INVALID_INDEX() {
    return C_INVALID_INDEX;
}


%}

%ignore DebugFile;

%include "copasi.h"

// warp method to get C_INVALID_INDEX
size_t INVALID_INDEX(); 

%include std_string.i
%include std_vector.i


%include "CObjectLists.i"
%include "CVector.i"
%include "CRandom.i"
%include "CCopasiMessage.i"
%include "messages.i"
%include "CKeyFactory.i"
%include "CCopasiException.i"
%include "CCopasiObjectName.i"
%include "CCopasiObject.i"
%include "CCopasiObjectReference.i"
%include "CCopasiContainer.i"
%include "CCopasiArray.i"
%include "CAnnotatedMatrix.i"
%include "CCopasiVector.i"
%include "CEigen.i"
%include "CFunctionParameter.i"
%include "CFunctionParameters.i"
%include "CCallParameters.i"
%include "CAnnotation.i"
%include "CEvaluationTree.i"
%include "CExpression.i"
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
%include "CPlotItem.i"
%include "CPlotColors.i"
%include "CPlotSpecification.i"
%include "COutputDefinitionVector.i"
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
%include "CExperimentFileInfo.i"
%include "CExperiment.i"
%include "CExperimentSet.i"
%include "CExperimentObjectMap.i"
%include "CFitItem.i"
%include "CFitMethod.i"
%include "CFitProblem.i"
%include "CFitTask.i"
%include "CMCAMethod.i"
%include "CMCAProblem.i"
%include "CMCATask.i"
%include "compare_utilities.i"
%include "CCopasiRootContainer.i"
%include "CEvent.i"
%include "CLBase.i"
%include "CLGraphicalObject.i"
%include "CLGlyphs.i"
%include "CLCurve.i"
%include "CLReactionGlyph.i"
%include "CLayout.i"
%include "CListOfLayouts.i"
%include "CSensMethod.i"
%include "CSensProblem.i"
%include "CSensTask.i"
%include "CBiologicalDescription.i"
%include "CReference.i"
%include "CCreator.i"
%include "CModified.i"
%include "CModelMIRIAMInfo.i"


