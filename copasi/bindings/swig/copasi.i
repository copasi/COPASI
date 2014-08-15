// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
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

%warnfilter(402) CCopasiObjectName;
// cannot do anything about warnings due to multiple inheritance
// so hide those errors
#pragma SWIG nowarn=314,402,813;

// more elements to ignore
%ignore create_expression(const ASTNode* pSource, const ListOfFunctionDefinitions* pFunctions);
%ignore *::fromAST;
%ignore *::getMathModel;
%ignore *::isPrerequisiteForContext;
%ignore *::getPrerequisites;
%ignore *::appendDependentTasks;
%ignore *::mustBeDeleted;
%ignore *::getReactionEquation;
%ignore *::autoUpdateMIRIAMResources;
%ignore CModelParameterSet::saveToStream;
%ignore CMoiety::getEquation;
%ignore CChemEq::getCompartments;
%ignore *::is_mass_action;
%ignore *::print;
%ignore *::printResult;
%ignore *::getTreesWithDiscontinuities;
%ignore *::begin;
%ignore *::end;
%ignore COutputHandler::getInterfaces;
%ignore CEFMProblem::getFluxModes() const;
%ignore CEFMProblem::getReorderedReactions() const;


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
%include "CAnnotation.i"
%include "CEigen.i"
%include "CFunctionParameter.i"
%include "CFunctionParameters.i"
%include "CCallParameters.i"
%include "CEvaluationTree.i"
%include "CExpression.i"
%include "CFunction.i"
%include "CFunctionDB.i"
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
%include "CReaction.i"
%include "CModel.i"
%include "CCopasiParameter.i"
%include "CCopasiParameterGroup.i"
%include "CModelParameter.i"
%include "CModelParameterGroup.i"
%include "CModelParameterSet.i"
%include "CCopasiVector.i"
%include "CVersion.i"
%include "CCopasiMethod.i"
%include "CCopasiProblem.i"
%include "COutputHandler.i"
%include "CReport.i"
%include "CCopasiTask.i"

%ignore CPlotItem::getChannels() const;
%ignore CPlotItem::XMLRecordingActivity;
%ignore CPlotItem::getRecordingActivityName;


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
%include "CLGeneralGlyph.i"
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

%include "CRenderInformation.i"

%ignore CFluxMode::CFluxMode(const std::map< size_t, C_FLOAT64 > & reactions,const bool & reversible);
%ignore CFluxMode::CFluxMode(const CTableauLine * line);
%ignore CEFMProblem::getReorderedReactions;
%ignore CEFMTask::getSpeciesChanges;

%include <copasi/elementaryFluxModes/CFluxMode.h>
%include <copasi/elementaryFluxModes/CEFMTask.h>
%include <copasi/elementaryFluxModes/CEFMMethod.h>
%include <copasi/elementaryFluxModes/CEFMProblem.h>

%include <copasi/crosssection/CCrossSectionTask.h>
%include <copasi/crosssection/CCrossSectionMethod.h>
%include <copasi/crosssection/CCrossSectionProblem.h>

%include <copasi/moieties/CMoietiesTask.h>
%include <copasi/moieties/CMoietiesProblem.h>
%include <copasi/moieties/CMoietiesMethod.h>

%ignore CLNAProblem::load;
%ignore CLNATask::load;

%include <copasi/lna/CLNATask.h>
%include <copasi/lna/CLNAProblem.h>
%include <copasi/lna/CLNAMethod.h>

%ignore CTSSATask::mapTableToName;

%include <copasi/tssanalysis/CTSSATask.h>
%include <copasi/tssanalysis/CTSSAProblem.h>
%include <copasi/tssanalysis/CTSSAMethod.h>

%{


#include <copasi/elementaryFluxModes/CFluxMode.h>
#include <copasi/elementaryFluxModes/CEFMTask.h>
#include <copasi/elementaryFluxModes/CEFMMethod.h>
#include <copasi/elementaryFluxModes/CEFMProblem.h>

#include <copasi/crosssection/CCrossSectionTask.h>
#include <copasi/crosssection/CCrossSectionMethod.h>
#include <copasi/crosssection/CCrossSectionProblem.h>

#include <copasi/moieties/CMoietiesTask.h>
#include <copasi/moieties/CMoietiesProblem.h>
#include <copasi/moieties/CMoietiesMethod.h>

#include <copasi/lna/CLNATask.h>
#include <copasi/lna/CLNAProblem.h>
#include <copasi/lna/CLNAMethod.h>

#include <copasi/tssanalysis/CTSSATask.h>
#include <copasi/tssanalysis/CTSSAProblem.h>
#include <copasi/tssanalysis/CTSSAMethod.h>

%}

%template(CFluxModeStdVector) std::vector<CFluxMode>;
typedef std::vector<CFluxMode> CFluxModeStdVector;
