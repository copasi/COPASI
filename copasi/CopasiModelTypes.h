// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * This file is a convenience header that includes COPASI model types
 */

#ifndef COPASI_MODEL_TYPES_H
#define COPASI_MODEL_TYPES_H

#include "copasi.h"

#include "core/CRootContainer.h"
#include "core/CDataObject.h"
#include "core/CDataObjectReference.h"
#include "core/CDataContainer.h"
#include "core/CCore.h"
#include "core/CArray.h"
#include "core/CArrayElementReference.h"
#include "core/CRegisteredCommonName.h"
#include "CopasiDataModel/CDataModel.h"


#include "copasi/math/CMathContainer.h"
#include "copasi/math/CMathObject.h"
#include "copasi/math/CMathEvent.h"

#include "model/CModel.h"
#include "model/CCompartment.h"
#include "model/CMetab.h"
#include "model/CEvent.h"
#include "model/CReaction.h"
#include "model/CReactionInterface.h"
#include "model/CModelValue.h"

#include "model/CModelParameter.h"
#include "model/CModelParameterGroup.h"
#include "model/CModelParameterSet.h"

#include "utilities/CCopasiTask.h"
#include "utilities/CCopasiProblem.h"
#include "utilities/CCopasiMethod.h"

#include "randomGenerator/CRandom.h"

#include "report/COutputAssistant.h"

#include "report/CReport.h"
#include "report/CReportBody.h"
#include "report/CReportDefinition.h"
#include "report/CReportDefinitionVector.h"

#include "plot/CPlotItem.h"
#include "plot/CPlotColors.h"
#include "plot/CPlotSpecification.h"
#include "plot/COutputDefinitionVector.h"

#endif // COPASI_MODEL_TYPES_H
