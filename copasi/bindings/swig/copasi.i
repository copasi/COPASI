// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
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


%module(directors="1") COPASI

%include "typemaps.i"

%warnfilter(402) CCommonName;
// cannot do anything about warnings due to multiple inheritance
// so hide those errors

#pragma SWIG nowarn=314,402,813,833,302,325,362,503;

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

%ignore *::toData;
%ignore *::applyData;

#if SWIGR
%include "rtype.swg"
%include "copasi_rtype.swg"
%typemap("rtype") size_t, size_t *, size_t &, const size_t&      "integer";
%typemap("rtype") bool, bool *, bool &, const bool&      "logical";
#endif 

%{

#define COPASI_MAIN
#include "copasi/copasi.h"
#undef COPASI_MAIN

#include <omex/common/libcombine-namespace.h>
LIBCOMBINE_CPP_NAMESPACE_USE

#include "local.cpp"

#include <copasi/core/CCore.h>

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
%include <copasi/core/CCore.h>

// warp method to get C_INVALID_INDEX
size_t INVALID_INDEX();

%include std_string.i
%include std_vector.i
%include std_map.i

#if defined(SWIGCSHARP) || defined(SWIGJAVA)
%include copasi_std_set.i
#elif defined(SWIGPYTHON) || defined(SWIGRUBY)
%include std_set.i
#endif

%ignore CIssue::operator bool;
%ignore CIssue::kindNames;
%ignore CIssue::kindDescriptions;
%ignore CIssue::Success;
%ignore CIssue::Information;
%ignore CIssue::Warning;
%ignore CIssue::Error;

%ignore CIssue::eKind;
%ignore CIssue::eSeverity;

%ignore *::beginName;
%ignore *::begin_name;
%ignore *::endName;
%ignore *::end_name;

%include <copasi/undo/CUndoObjectInterface.h>
%template(CDataStdVector) std::vector<CData>;
%include <copasi/undo/CData.h>
%template(CDataValueStdVector) std::vector<CDataValue>;
%include <copasi/undo/CDataValue.h>
%include <copasi/undo/CUndoData.h>

%include <copasi/core/CObjectInterface.h>
%include <copasi/utilities/CValidity.h>

%include "CCommonName.i"
%include "CObjectLists.i"
%include "CVector.i"
%include "CRandom.i"
%include "CCopasiMessage.i"
%include "messages.i"
%include "CKeyFactory.i"
%include "CCopasiException.i"
%include "CDataObject.i"
%include "CDataObjectReference.i"
%include "CDataContainer.i"
%include "CArray.i"
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
%include "CDataString.i"
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
// enable process report 
%feature("director") CProcessReport;
%extend CProcessReport
{
    static double getValue(const double* pValue)
    {
        if (pValue == NULL)
            return 0.0;
        return *pValue;
    }

    static int getValue(const int* pValue)
    {
        if (pValue == NULL)
            return 0;
        return *pValue;
    }


    static unsigned int getValue(const unsigned int* pValue)
    {
        if (pValue == NULL)
            return 0;
        return *pValue;
    }

    static std::string getValue(const std::string* pValue)
    {
        if (pValue == NULL)
            return "";
        return *pValue;
    }

    static std::string getStringValue(const void* pValue)
    {
        if (pValue == NULL)
            return "";
        return *static_cast<const std::string*>(pValue);
    }

    static double getDoubleValue(const void* pValue)
    {
        if (pValue == NULL)
            return 0.0;
        return *static_cast<const double*>(pValue);
    }

    static int getIntValue(const void* pValue)
    {
        if (pValue == NULL)
            return 0;
        return *static_cast<const int*>(pValue);
    }

    static unsigned int getUIntValue(const void* pValue)
    {
        if (pValue == NULL)
            return 0;
        return *static_cast<const unsigned int*>(pValue);
    }
}

%include <copasi/utilities/CProcessReport.h>

%include "CCopasiParameterGroup.i"
%include "CModelParameter.i"
%include "CModelParameterGroup.i"
%include "CModelParameterSet.i"
%include "CDataVector.i"
%include "CVersion.i"
%include "CCopasiMethod.i"
%include "CCopasiProblem.i"
%include "COutputHandler.i"
%include "CReport.i"
%include "CCopasiTask.i"
%include "CDataHandler.i"

%ignore CPlotItem::getChannels() const;
%ignore CPlotItem::XMLRecordingActivity;
%ignore CPlotItem::getRecordingActivityName;


%include "CPlotItem.i"
%include "CPlotColors.i"
%include "CPlotSpecification.i"
%include "COutputDefinitionVector.i"
%include "CReportDefinition.i"
%include "CReportDefinitionVector.i"
%include "CDataModel.i"
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
%include "CFitProblem.i"
%include "CFitTask.i"
%include "CMCAMethod.i"
%include "CMCAProblem.i"
%include "CMCATask.i"
%include "compare_utilities.i"
%include "CRootContainer.i"
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


%ignore COptMethodPS::COptMethodPS(const COptMethodPS&);
%ignore COptMethodPS::COptMethodPS(const CDataContainer *);
%ignore COptMethodPS::COptMethodPS(const CDataContainer *,const CTaskEnum::Method &,const CTaskEnum::Task &);

%ignore COptMethodEP::COptMethodEP(const COptMethodEP&);
%ignore COptMethodEP::COptMethodEP(const CDataContainer *);
%ignore COptMethodEP::COptMethodEP(const CDataContainer *,const CTaskEnum::Method &,const CTaskEnum::Task &);

%ignore COptMethodGASR::COptMethodGASR(const COptMethodGASR&);
%ignore COptMethodGASR::COptMethodGASR(const CDataContainer *);
%ignore COptMethodGASR::COptMethodGASR(const CDataContainer *,const CTaskEnum::Method &,const CTaskEnum::Task &);

%ignore COptMethodHookeJeeves::COptMethodHookeJeeves(const COptMethodHookeJeeves&);
%ignore COptMethodHookeJeeves::COptMethodHookeJeeves(const CDataContainer *);
%ignore COptMethodHookeJeeves::COptMethodHookeJeeves(const CDataContainer *,const CTaskEnum::Method &,const CTaskEnum::Task &);

%ignore COptMethodPS::COptMethodPS(const COptMethodPS&);
%ignore COptMethodPS::COptMethodPS(const CDataContainer *);
%ignore COptMethodPS::COptMethodPS(const CDataContainer *,const CTaskEnum::Method &,const CTaskEnum::Task &);

%ignore COptMethodPraxis::COptMethodPraxis(const COptMethodPraxis&);
%ignore COptMethodPraxis::COptMethodPraxis(const CDataContainer *);
%ignore COptMethodPraxis::COptMethodPraxis(const CDataContainer *,const CTaskEnum::Method &,const CTaskEnum::Task &);


%include <copasi/plot/CPlotItem.h>
%ignore COptMethodCoranaWalk(const COptMethodCoranaWalk&);
%include <copasi/optimization/COptMethod.h>
// %include <copasi/optimization/COptPopulationMethod.h>
%include <copasi/optimization/COptMethodCoranaWalk.h>
%include <copasi/optimization/COptMethodDE.h>
%include <copasi/optimization/COptMethodEP.h>
%include <copasi/optimization/COptMethodGA.h>
%include <copasi/optimization/COptMethodGASR.h>
%include <copasi/optimization/COptMethodHookeJeeves.h>
%include <copasi/optimization/COptMethodLevenbergMarquardt.h>
%include <copasi/optimization/COptMethodNelderMead.h>
%include <copasi/optimization/COptMethodPraxis.h>
%include <copasi/optimization/COptMethodPS.h>
%include <copasi/optimization/COptMethodSA.h>
%include <copasi/optimization/COptMethodSRES.h>
%include <copasi/optimization/COptMethodSS.h>
%include <copasi/optimization/COptMethodStatistics.h>
%include <copasi/optimization/COptMethodSteepestDescent.h>
%include <copasi/optimization/CRandomSearch.h>
%include <copasi/optimization/COptMethodTruncatedNewton.h>

%include <copasi/function/CFunctionAnalyzer.h>
%include <copasi/model/CModelAnalyzer.h>

%include <copasi/commandline/COptions.h>
%include <copasi/commandline/CConfigurationFile.h>

%include <copasi/utilities/CopasiTime.h>
%include <copasi/core/CDataTimer.h>

%include <copasi/math/CJitCompilerImplementation.h>

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

#include <copasi/plot/CPlotItem.h>
#include <copasi/optimization/COptMethodCoranaWalk.h>
#include <copasi/optimization/COptMethodDE.h>
#include <copasi/optimization/COptMethodEP.h>
#include <copasi/optimization/COptMethodGA.h>
#include <copasi/optimization/COptMethodGASR.h>
#include <copasi/optimization/COptMethodHookeJeeves.h>
#include <copasi/optimization/COptMethodLevenbergMarquardt.h>
#include <copasi/optimization/COptMethodNelderMead.h>
#include <copasi/optimization/COptMethodPraxis.h>
#include <copasi/optimization/COptMethodPS.h>
#include <copasi/optimization/COptMethodSA.h>
#include <copasi/optimization/COptMethodSRES.h>
#include <copasi/optimization/COptMethodSS.h>
#include <copasi/optimization/COptMethodStatistics.h>
#include <copasi/optimization/COptMethodSteepestDescent.h>
#include <copasi/optimization/CRandomSearch.h>
#include <copasi/optimization/COptMethodTruncatedNewton.h>

#include <copasi/function/CFunctionAnalyzer.h>
#include <copasi/model/CModelAnalyzer.h>


#include <copasi/commandline/COptions.h>
#include <copasi/commandline/CConfigurationFile.h>
#include <copasi/utilities/CopasiTime.h>
#include <copasi/core/CDataTimer.h>

#include <copasi/math/CJitCompilerImplementation.h>

%}


%template(CReactionResultStdVector) std::vector< CReactionResult >;
typedef std::vector< CReactionResult > CReactionResultStdVector;

%template(CFluxModeStdVector) std::vector<CFluxMode>;
typedef std::vector<CFluxMode> CFluxModeStdVector;
