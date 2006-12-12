/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/java/local.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/12/12 21:26:10 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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
#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "trajectory/CTrajectoryMethod.h"
#include "report/CCopasiStaticString.h"
#include "report/CReportDefinition.h"

//#include <iostream>

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

#include "CopasiDataModel/CCopasiDataModel.h"

void initCopasi()
{
  CCopasiContainer::init();
  CCopasiDataModel::Global = new CCopasiDataModel();
}
