// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CXMLParserData.h"

#include "copasi/layout/CLayout.h"
#include "copasi/layout/CListOfLayouts.h"
#include "copasi/layout/CLLocalRenderInformation.h"
#include "copasi/layout/CLGlobalRenderInformation.h"

CXMLParserData::CXMLParserData():
  pVersion(NULL),
  pModel(NULL),
  CharacterData(),
  mAssignments(),
  pFunctionList(NULL),
  pFunction(NULL),
  pFunctionVariable(NULL),
  FunctionDescription(),
  mPredefinedFunction(false),
  mFunctionParameterKeyMap(),
  mpExpression(NULL),
  mKey2ObjectiveFunction(),
  pReaction(NULL),
  pEvent(NULL),
  pEventAssignment(NULL),
  SourceParameterObjects(),
  mKeyMap(),
  StateVariableList(),
  pTaskList(NULL),
  pReportList(NULL),
  pPlotList(NULL),
  pReport(NULL),
  pCurrentTask(NULL),
  pCurrentParameter(NULL),
  ModelParameterGroupStack(),
  pCurrentModelParameter(NULL),
  pCurrentPlot(NULL),
  pCurrentPlotItem(NULL),
  pCurrentChannelSpec(NULL),
  UnmappedKeyParameters(),
  pLayoutList(NULL),
  pCurrentLayout(NULL),
  pCompartmentGlyph(NULL),
  pMetaboliteGlyph(NULL),
  pReactionGlyph(NULL),
  pTextGlyph(NULL),
  pGeneralGlyph(NULL),
  pCurve(NULL),
  pLineSegment(NULL),
  pMetaboliteReferenceGlyph(NULL),
  pRenderInformation(NULL),
  pGradient(NULL),
  pLineEnding(NULL),
  pStyle(NULL),
  pGroup(NULL),
  pText(NULL),
  pDimensions(NULL),
  pBoundingBox(NULL),
  pPosition(NULL),
  pListOfCurveElements(NULL),
  pRenderCurve(NULL),
  pPolygon(NULL),
  pRectangle(NULL),
  pEllipse(NULL),
  pImage(NULL),
  LocalRenderInformation(true),
  taskReferenceMap(),
  reportReferenceMap(),
  pGUI(NULL),
  pDataModel(NULL),
  pUnitDefinitionImportList(NULL),
  pCurrentUnitDefinition(NULL),
  mUnsupportedAnnotations()
{}

// static
CLRenderInformationBase * CXMLParserData::createRenderInformation(CXMLParserData * pData)
{
  if (pData->LocalRenderInformation)
    {
      if (pData->pCurrentLayout == NULL) return NULL;

      pData->pCurrentLayout->addLocalRenderInformation(new CLLocalRenderInformation());

      size_t index = pData->pCurrentLayout->getListOfLocalRenderInformationObjects().size();

      if (index > 0)
        {
          return &pData->pCurrentLayout->getListOfLocalRenderInformationObjects()[index - 1];
        }
    }
  else
    {
      if (pData->pLayoutList == NULL) return NULL;

      pData->pLayoutList->addGlobalRenderInformation(new CLGlobalRenderInformation());

      size_t index = pData->pLayoutList->getListOfGlobalRenderInformationObjects().size();

      if (index > 0)
        {
          return &pData->pLayoutList->getListOfGlobalRenderInformationObjects()[index - 1];
        }
    }

  return NULL;
}
