// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * This file is a convenience header that includes COPASI model types
 */

#ifndef COPASI_MODEL_TYPES_H
#define COPASI_MODEL_TYPES_H

#include "copasi/copasi.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/core/CDataObject.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/core/CDataContainer.h"
#include "copasi/core/CCore.h"
#include "copasi/core/CArray.h"
#include "copasi/core/CArrayElementReference.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/CopasiDataModel/CDataModel.h"

#include "copasi/math/CMathContainer.h"
#include "copasi/math/CMathObject.h"
#include "copasi/math/CMathEvent.h"

#include "copasi/model/CModel.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CEvent.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CReactionInterface.h"
#include "copasi/model/CModelValue.h"

#include "copasi/model/CModelParameter.h"
#include "copasi/model/CModelParameterGroup.h"
#include "copasi/model/CModelParameterSet.h"

#include "copasi/utilities/CCopasiTask.h"
#include "copasi/utilities/CCopasiProblem.h"
#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/utilities/CBaseUnit.h"
#include "copasi/utilities/CUnit.h"
#include "copasi/utilities/CUnitComponent.h"
#include "copasi/utilities/CUnitDefinition.h"
#include "copasi/utilities/CUnitDefinitionDB.h"
#include "copasi/utilities/CExpressionGenerator.h"

#include "copasi/randomGenerator/CRandom.h"

#include "copasi/report/COutputAssistant.h"

#include "copasi/report/CReport.h"
#include "copasi/report/CReportBody.h"
#include "copasi/report/CReportDefinition.h"
#include "copasi/report/CReportDefinitionVector.h"

#include "copasi/plot/CPlotItem.h"
#include "copasi/plot/CPlotColors.h"
#include "copasi/plot/CPlotSpecification.h"
#include "copasi/plot/COutputDefinitionVector.h"

#endif // COPASI_MODEL_TYPES_H
