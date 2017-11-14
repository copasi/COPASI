// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifdef SWIGPERL
#undef NORMAL
#endif // SWIGPERL

#include "CopasiDataModel/CDataModel.h"
#include "utilities/CCopasiMethod.h"
#include "utilities/CCopasiProblem.h"
#include "utilities/CCopasiTask.h"
#include "function/CEvaluationTree.h"
#include "function/CFunction.h"
#include "function/CFunctionDB.h"
#include "function/CFunctionParameter.h"
#include "function/CFunctionParameters.h"
#include "MIRIAM/CBiologicalDescription.h"
#include "MIRIAM/CReference.h"
#include "MIRIAM/CModified.h"
#include "MIRIAM/CModelMIRIAMInfo.h"
#include "model/CModelValue.h"
#include "model/CMetab.h"
#include "model/CModel.h"
#include "model/CChemEq.h"
#include "model/CChemEqElement.h"
#include "model/CReaction.h"
#include "model/CMoiety.h"
#include "model/CEvent.h"
#include "core/CDataString.h"
#include "report/CReportDefinition.h"
#include "core/CDataArray.h"
#include "copasi/core/CMatrix.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"
#include "steadystate/CSteadyStateMethod.h"
#include "steadystate/CNewtonMethod.h"
#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "trajectory/CTrajectoryMethod.h"
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
#include "optimization/COptMethod.h"
#include "parameterFitting/CFitProblem.h"
#include "parameterFitting/CFitTask.h"

// since COPASI undefines TRUE from swig, we have to redefine it here
// if needed
#ifndef TRUE
#define TRUE
#endif

#include "copasi/bindings/common/local_common.cpp"
#include "copasi/bindings/common/downcast_common.cpp"
