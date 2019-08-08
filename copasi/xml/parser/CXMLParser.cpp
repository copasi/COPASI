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

/**
 * CXMLParser class.
 * This class parses a COPASI XML file.
 *
 * Created for COPASI by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */

#include "copasi/copasi.h"

#include "copasi/xml/CExpat.h"

#include "CXMLParser.h"
#include "CXMLHandler.h"

#include "copasi/xml/CCopasiXMLInterface.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/function/CFunction.h"
#include "copasi/function/CExpression.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CModelParameterSet.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/report/CReportDefinition.h"
#include "copasi/utilities/CUnitDefinitionDB.h"
#include "copasi/utilities/CUnitDefinition.h"

#include "copasi/utilities/CVersion.h"
#include "copasi/utilities/CCopasiParameter.h"
#include "copasi/utilities/CCopasiParameterGroup.h"
#include "copasi/utilities/CSlider.h"
#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/steadystate/CMCATask.h"
#include "copasi/lna/CLNATask.h"
#include "copasi/tssanalysis/CTSSATask.h"
#include "copasi/scan/CScanTask.h"
#include "copasi/elementaryFluxModes/CEFMTask.h"
#include "copasi/optimization/COptTask.h"
#include "copasi/parameterFitting/CFitTask.h"
#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/lyap/CLyapTask.h"
#include "copasi/sensitivities/CSensTask.h"
#include "copasi/moieties/CMoietiesTask.h"
#include "copasi/crosssection/CCrossSectionTask.h"
#include "copasi/plot/COutputDefinitionVector.h"
#include "copasi/plot/CPlotSpecification.h"
#include "copasi/plot/CPlotItem.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/layout/CListOfLayouts.h"
#include "copasi/core/CRootContainer.h"

#include "copasi/layout/CLGradientStop.h"
#include "copasi/layout/CLGradientBase.h"
#include "copasi/layout/CLLinearGradient.h"
#include "copasi/layout/CLRadialGradient.h"
#include "copasi/layout/CLColorDefinition.h"
#include "copasi/layout/CLRenderPoint.h"
#include "copasi/layout/CLRenderCubicBezier.h"
#include "copasi/layout/CLTransformation.h"
#include "copasi/layout/CLTransformation2D.h"
#include "copasi/layout/CLImage.h"
#include "copasi/layout/CLText.h"
#include "copasi/layout/CLRenderCurve.h"
#include "copasi/layout/CLPolygon.h"
#include "copasi/layout/CLEllipse.h"
#include "copasi/layout/CLRectangle.h"
#include "copasi/layout/CLLocalStyle.h"
#include "copasi/layout/CLGlobalStyle.h"
#include "copasi/layout/CLRenderInformationBase.h"
#include "copasi/layout/CLLocalRenderInformation.h"
#include "copasi/layout/CLGlobalRenderInformation.h"

// Uncomment this line below to get debug print out.
// #define DEBUG_OUTPUT 1

CXMLParser::CXMLParser(CVersion & version) :
  CExpat(),
  mData(),
  mpFactory(NULL),
  mCharacterData(),
  mCharacterDataEncoding(CCopasiXMLInterface::none),
  mElementHandlerStack()
{
  create();

  mData.pVersion = & version;

  mpFactory = new CXMLHandlerFactory(*this, mData);
  mElementHandlerStack.push(mpFactory->getHandler(CXMLHandler::COPASI));

  enableElementHandler(true);
}

CXMLParser::~CXMLParser()
{
  pdelete(mpFactory);
  pdelete(mData.pLineSegment);
  pdelete(mData.pUnitDefinitionImportList);
}

void CXMLParser::onStartElement(const XML_Char *pszName,
                                const XML_Char **papszAttrs)
{
#ifdef DEBUG_OUTPUT
  std::cout << mElementHandlerStack.size() << ", " << getCurrentLineNumber() << ": Start " << pszName << std::endl;
#endif // DEBUG_OUTPUT

  assert(mElementHandlerStack.size() != 0);
  mElementHandlerStack.top()->start(pszName, papszAttrs);
}

void CXMLParser::onEndElement(const XML_Char *pszName)
{
#ifdef DEBUG_OUTPUT
  std::cout << mElementHandlerStack.size() << ", " << getCurrentLineNumber() << ": End   " << pszName << std::endl;
#endif // DEBUG_OUTPUT

  if (mElementHandlerStack.size() != 0)
    mElementHandlerStack.top()->end(pszName);
  else
    return;
}

#ifdef XXXX
void CXMLParser::onStartCdataSection()
{
  long i = mParser.getCurrentByteIndex();
}

void CXMLParser::onEndCdataSection()
{
  long i = mParser.getCurrentByteIndex();
}
#endif // XXXX

/**
 * Skipped entity handler
 * This is called in two situations:
 * 1) An entity reference is encountered for which no declaration
 *    has been read *and* this is not an error.
 * 2) An internal entity reference is read, but not expanded, because
 *    XML_SetDefaultHandler has been called.
 * Note: skipped parameter entities in declarations and skipped general
 *       entities in attribute values cannot be reported, because
 *       the event would be out of sync with the reporting of the
 *       declarations or attribute values
 * @param const XML_Char *entityName
 * @param int is_parameter_entity
 */
void CXMLParser::onSkippedEntityHandler(const XML_Char * entityName,
                                        int is_parameter_entity)
{
  mCharacterData += "&";
  mCharacterData += entityName;
  mCharacterData += ";";

  return;
}

void CXMLParser::enableCharacterDataHandler(bool fEnable)
{
  mCharacterData.erase();
  CExpat::enableCharacterDataHandler(fEnable);
}

void CXMLParser::onCharacterData(const XML_Char *pszData,
                                 int nLength)
{
  std::string Data;
  Data.append(pszData, nLength);

  mCharacterData += CCopasiXMLInterface::encode(Data, mCharacterDataEncoding);
}

std::string CXMLParser::getCharacterData(const std::string & toBeStripped,
    const std::string & join)
{
  std::string tmp(mCharacterData);

  enableCharacterDataHandler(false); /* Resetting for future calls. */

  if (toBeStripped == "") return tmp;

  std::string::size_type Start = tmp.find_first_of(toBeStripped);
  std::string::size_type End = 0;

  while (Start != std::string::npos)
    {
      End = tmp.find_first_not_of(toBeStripped, Start);

      tmp.erase(Start, End - Start);

      if (Start && End != std::string::npos)
        {
          tmp.insert(Start, join);
          Start += join.length();
        }

      Start = tmp.find_first_of(toBeStripped, Start);
    }

  return tmp;
}

void CXMLParser::pushElementHandler(CXMLHandler * pElementHandler)
{mElementHandlerStack.push(pElementHandler);}

void CXMLParser::popElementHandler()
{mElementHandlerStack.pop();}

void CXMLParser::setFunctionList(CDataVectorN< CFunction > * pFunctionList)
{mData.pFunctionList = pFunctionList;}

CModel * CXMLParser::getModel() const
{return mData.pModel;}

CReportDefinitionVector * CXMLParser::getReportList() const
{return mData.pReportList;}

CDataVectorN< CCopasiTask > * CXMLParser::getTaskList() const
{return mData.pTaskList;}

COutputDefinitionVector * CXMLParser::getPlotList() const
{return mData.pPlotList;}

void CXMLParser::setGUI(SCopasiXMLGUI * pGUI)
{mData.pGUI = pGUI;}

void CXMLParser::setLayoutList(CListOfLayouts * pLayoutList)
{mData.pLayoutList = pLayoutList;}

CListOfLayouts * CXMLParser::getLayoutList() const
{return mData.pLayoutList;}

CUnitDefinitionDB * CXMLParser::getUnitDefinitionImportList() const
{return mData.pUnitDefinitionImportList;}

const CCopasiParameterGroup * CXMLParser::getCurrentGroup() const
{return dynamic_cast< const CCopasiParameterGroup * >(mData.pCurrentParameter);}

CXMLHandler * CXMLParser::getHandler(const CXMLHandler::Type & type)
{
  return mpFactory->getHandler(type);
}

void CXMLParser::setDatamodel(CDataModel* pDataModel)
{
  mData.pDataModel = pDataModel;
}

void CXMLParser::setCharacterEncoding(const CCopasiXMLInterface::EncodingType & encoding)
{
  mCharacterDataEncoding = encoding;
}
