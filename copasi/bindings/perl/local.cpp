// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#ifdef SWIGPERL
#undef NORMAL
#endif // SWIGPERL

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/utilities/CCopasiProblem.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/function/CEvaluationTree.h"
#include "copasi/function/CFunction.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/function/CFunctionParameter.h"
#include "copasi/function/CFunctionParameters.h"
#include "copasi/MIRIAM/CBiologicalDescription.h"
#include "copasi/MIRIAM/CReference.h"
#include "copasi/MIRIAM/CModified.h"
#include "copasi/MIRIAM/CModelMIRIAMInfo.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CChemEq.h"
#include "copasi/model/CChemEqElement.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CMoiety.h"
#include "copasi/model/CEvent.h"
#include "copasi/core/CDataString.h"
#include "copasi/report/CReportDefinition.h"
#include "copasi/core/CDataArray.h"
#include "copasi/core/CMatrix.h"
#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/steadystate/CSteadyStateProblem.h"
#include "copasi/steadystate/CSteadyStateMethod.h"
#include "copasi/steadystate/CNewtonMethod.h"
#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/trajectory/CTrajectoryProblem.h"
#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/scan/CScanTask.h"
#include "copasi/scan/CScanProblem.h"
#include "copasi/scan/CScanMethod.h"
#include "copasi/lyap/CLyapTask.h"
#include "copasi/lyap/CLyapProblem.h"
#include "copasi/lyap/CLyapMethod.h"
#include "copasi/optimization/COptItem.h"
#include "copasi/optimization/COptTask.h"
#include "copasi/optimization/COptProblem.h"
#include "copasi/optimization/COptMethod.h"
#include "copasi/parameterFitting/CExperiment.h"
#include "copasi/parameterFitting/CExperimentFileInfo.h"
#include "copasi/parameterFitting/CExperimentObjectMap.h"
#include "copasi/parameterFitting/CExperimentSet.h"
#include "copasi/parameterFitting/CFitItem.h"
#include "copasi/optimization/COptMethod.h"
#include "copasi/parameterFitting/CFitProblem.h"
#include "copasi/parameterFitting/CFitTask.h"

// since COPASI undefines TRUE from swig, we have to redefine it here
// if needed
#ifndef TRUE
#define TRUE
#endif

#include "copasi/bindings/common/local_common.cpp"
#include "copasi/bindings/common/downcast_common.cpp"
