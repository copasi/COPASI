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

#include "copasi.h"

#include "xml/CExpat.h"

#include "CXMLParser.h"
#include "CXMLHandler.h"

#include "xml/CCopasiXMLInterface.h"
#include "utilities/CCopasiMessage.h"
#include "function/CFunction.h"
#include "function/CExpression.h"
#include "model/CModel.h"
#include "model/CModelParameterSet.h"
#include "report/CKeyFactory.h"
#include "report/CReportDefinitionVector.h"
#include "report/CReportDefinition.h"
#include "utilities/CUnitDefinitionDB.h"
#include "utilities/CUnitDefinition.h"

#include "utilities/CVersion.h"
#include "utilities/CCopasiParameter.h"
#include "utilities/CCopasiParameterGroup.h"
#include "utilities/CSlider.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CMCATask.h"
#include "lna/CLNATask.h"
#include "tssanalysis/CTSSATask.h"
#include "scan/CScanTask.h"
#include "elementaryFluxModes/CEFMTask.h"
#include "optimization/COptTask.h"
#include "parameterFitting/CFitTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "lyap/CLyapTask.h"
#include "sensitivities/CSensTask.h"
#include "moieties/CMoietiesTask.h"
#include "crosssection/CCrossSectionTask.h"
#include "plot/COutputDefinitionVector.h"
#include "plot/CPlotSpecification.h"
#include "plot/CPlotItem.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "layout/CListOfLayouts.h"
#include "report/CCopasiRootContainer.h"

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

void CXMLParser::setFunctionList(CCopasiVectorN< CFunction > * pFunctionList)
{mData.pFunctionList = pFunctionList;}

CModel * CXMLParser::getModel() const
{return mData.pModel;}

CReportDefinitionVector * CXMLParser::getReportList() const
{return mData.pReportList;}

CCopasiVectorN< CCopasiTask > * CXMLParser::getTaskList() const
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

const CCopasiObject * CXMLParser::getObjectFromCN(const std::string & cn) const
{
  const CObjectInterface * pObject = NULL;
  CCopasiObjectName CN = CCopasiObjectName(cn).getRemainder();

  if (mData.pModel &&
      (pObject = mData.pModel->getObject(CN)))
    return static_cast< const CCopasiObject * >(pObject);

  if (mData.pTaskList &&
      (pObject = mData.pTaskList->getObject(CN)))
    return static_cast< const CCopasiObject * >(pObject);

  if (mData.pFunctionList &&
      (pObject = mData.pFunctionList->getObject(CN)))
    return static_cast< const CCopasiObject * >(pObject);

  return NULL;
}

CXMLHandler * CXMLParser::getHandler(const CXMLHandler::Type & type)
{
  return mpFactory->getHandler(type);
}

void CXMLParser::setDatamodel(CCopasiDataModel* pDataModel)
{
  mData.pDataModel = pDataModel;
}

void CXMLParser::setCharacterEncoding(const CCopasiXMLInterface::EncodingType & encoding)
{
  mCharacterDataEncoding = encoding;
}
