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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi/core/CMatrix.h"
#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/utilities/CCopasiProblem.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/function/CEvaluationTree.h"
#include "copasi/function/CFunction.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/function/CFunctionParameter.h"
#include "copasi/function/CFunctionParameters.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CChemEq.h"
#include "copasi/model/CChemEqElement.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CMoiety.h"
#include "copasi/model/CEvent.h"
#include "copasi/MIRIAM/CBiologicalDescription.h"
#include "copasi/MIRIAM/CReference.h"
#include "copasi/MIRIAM/CModified.h"
#include "copasi/MIRIAM/CModelMIRIAMInfo.h"
#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/trajectory/CTrajectoryProblem.h"
#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/core/CDataString.h"
#include "copasi/report/CReportDefinition.h"
#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/core/CDataArray.h"
#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/steadystate/CSteadyStateProblem.h"
#include "copasi/steadystate/CSteadyStateMethod.h"
#include "copasi/steadystate/CNewtonMethod.h"
#include "copasi/scan/CScanTask.h"
#include "copasi/scan/CScanProblem.h"
#include "copasi/scan/CScanMethod.h"
#include "copasi/lyap/CLyapTask.h"
#include "copasi/lyap/CLyapProblem.h"
#include "copasi/lyap/CLyapMethod.h"
#include "copasi/steadystate/CMCATask.h"
#include "copasi/steadystate/CMCAProblem.h"
#include "copasi/steadystate/CMCAMethod.h"
#include "copasi/sensitivities/CSensTask.h"
#include "copasi/sensitivities/CSensProblem.h"
#include "copasi/sensitivities/CSensMethod.h"
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
#include "copasi/optimization/COptMethod.h"
#include "copasi/parameterFitting/CFitProblem.h"
#include "copasi/parameterFitting/CFitTask.h"

//#include <iostream>
typedef CDataVector<CEvent> EventVector;
typedef CDataVectorN<CEvent> EventVectorN;

typedef CDataVector<CEventAssignment> EventAssignmentVector;
typedef CDataVectorN<CEventAssignment> EventAssignmentVectorN;

typedef CDataVector<CCopasiTask> TaskVector;
typedef CDataVectorN<CCopasiTask> TaskVectorN;

typedef CDataVectorN<CModelValue> ModelValueVectorN;

typedef CDataVector<CMoiety> MoietyVector;

typedef CDataVector<CMetab> MetabVector;
typedef CDataVectorNS<CMetab> MetabVectorNS;

typedef CDataVectorNS<CCompartment> CompartmentVectorNS;

typedef CDataVectorNS<CReaction> ReactionVectorNS;

typedef std::vector<CRegisteredCommonName> ReportItemVector;
typedef std::vector<CCopasiParameter*> ParameterVector;

typedef CDataVectorN<CEvaluationTree> CEvaluationTreeVectorN;

typedef std::vector<CFunction> CFunctionStdVector;

typedef CDataVector<CChemEqElement> CChemEqElementVector;

typedef CDataVector<CModelValue> ModelValueVector;
typedef CDataVectorN<CReportDefinition> CReportDefinitionVectorN;
typedef CDataVectorN<CMetab> MetabVectorN;
typedef CDataVector<CCompartment> CompartmentVector;
typedef CDataVectorN<CCompartment> CompartmentVectorN;
typedef CDataVectorN<CReaction> ReactionVectorN;
typedef CDataVector<CReaction> ReactionVector;
typedef CDataVector<CEvaluationTree> CEvaluationTreeVector;

typedef CMatrixInterface<CMatrix<C_FLOAT64> > AnnotatedFloatMatrix;

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/commandline/COptions.h"
#include "copasi/core/CRootContainer.h"

void initCopasi()
{
  CRootContainer::init(0, NULL, false);
}
