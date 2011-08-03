// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/common/local_common.cpp,v $
//   $Revision: 1.1.2.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/08/03 09:33:38 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CCopasiMethod.h"
#include "utilities/CCopasiProblem.h"
#include "utilities/CCopasiTask.h"
#include "function/CEvaluationTree.h"
#include "function/CFunction.h"
#include "function/CFunctionDB.h"
#include "function/CFunctionParameter.h"
#include "function/CFunctionParameters.h"
#include "model/CModelValue.h"
#include "model/CMetab.h"
#include "model/CModel.h"
#include "model/CChemEq.h"
#include "model/CChemEqElement.h"
#include "model/CReaction.h"
#include "model/CMoiety.h"
#include "model/CEvent.h"
#include "MIRIAM/CBiologicalDescription.h"
#include "MIRIAM/CReference.h"
#include "MIRIAM/CModified.h"
#include "MIRIAM/CModelMIRIAMInfo.h"
#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "trajectory/CTrajectoryMethod.h"
#include "report/CCopasiStaticString.h"
#include "report/CReportDefinition.h"
#include "report/CReportDefinitionVector.h"
#include "utilities/CAnnotatedMatrix.h"
#include "utilities/CMatrix.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"
#include "steadystate/CSteadyStateMethod.h"
#include "steadystate/CNewtonMethod.h"
#include "scan/CScanTask.h"
#include "scan/CScanProblem.h"
#include "scan/CScanMethod.h"
#include "lyap/CLyapTask.h"
#include "lyap/CLyapProblem.h"
#include "lyap/CLyapMethod.h"
#include "optimization/COptItem.h"
#include "optimization/COptTask.h"
#include "optimization/COptProblem.h"
#include "optimization/COptMethod.h"
#include "parameterFitting/CExperiment.h"
#include "parameterFitting/CExperimentFileInfo.h"
#include "parameterFitting/CExperimentObjectMap.h"
#include "parameterFitting/CExperimentSet.h"
#include "parameterFitting/CFitItem.h"
#include "parameterFitting/CFitMethod.h"
#include "parameterFitting/CFitProblem.h"
#include "parameterFitting/CFitTask.h"
#include "sensitivities/CSensMethod.h"
#include "sensitivities/CSensProblem.h"
#include "sensitivities/CSensTask.h"
#include "model/CObjectLists.h"
#include "steadyState/CMCAMethod.h"
#include "steadyState/CMCAProblem.h"
#include "steadyState/CMCATask.h"

typedef CCopasiVector<CEvent> EventVector;
typedef CCopasiVectorN<CEvent> EventVectorN;

typedef CCopasiVector<CEventAssignment> EventAssignmentVector;
typedef CCopasiVectorN<CEventAssignment> EventAssignmentVectorN;


typedef CCopasiVector<CCopasiTask> TaskVector;
typedef CCopasiVectorN<CCopasiTask> TaskVectorN;

typedef CCopasiVectorN<CModelValue> ModelValueVectorN;

typedef CCopasiVector<CMoiety> MoietyVector;

typedef CCopasiVector<CMetab> MetabVector;
typedef CCopasiVectorNS<CMetab> MetabVectorNS;

typedef CCopasiVectorNS<CCompartment> CompartmentVectorNS;

typedef CCopasiVectorNS<CReaction> ReactionVectorNS;

typedef std::vector<CRegisteredObjectName> ReportItemVector;
typedef std::vector<CCopasiParameter*> ParameterVector;

typedef CCopasiVectorN<CEvaluationTree> CEvaluationTreeVectorN;

typedef std::vector<CFunction> CFunctionStdVector;

typedef CCopasiVector<CChemEqElement> CChemEqElementVector;

typedef CCopasiVector<CModelValue> ModelValueVector;
typedef CCopasiVectorN<CReportDefinition> CReportDefinitionVectorN;
typedef CCopasiVectorN<CMetab> MetabVectorN;
typedef CCopasiVector<CCompartment> CompartmentVector;
typedef CCopasiVectorN<CCompartment> CompartmentVectorN;
typedef CCopasiVectorN<CReaction> ReactionVectorN;
typedef CCopasiVector<CReaction> ReactionVector;
typedef CCopasiVector<CEvaluationTree> CEvaluationTreeVector;

typedef CCopasiMatrixInterface<CMatrix<C_FLOAT64> > AnnotatedFloatMatrix;
typedef CCopasiVectorN<CCopasiDataModel> CCopasiDataModelVectorN;

#include "commandline/COptions.h"
#include "report/CCopasiRootContainer.h"


