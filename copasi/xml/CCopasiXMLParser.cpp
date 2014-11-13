// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

/**
 * CCopasiXMLParser class.
 * This class parses a COPASI XML file.
 *
 * Created for COPASI by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */

#include "copasi.h"

#include "CExpat.h"

#include "CCopasiXMLParser.h"
#include "CCopasiXMLInterface.h"
#include "utilities/CCopasiMessage.h"
#include "function/CFunction.h"
#include "function/CExpression.h"
#include "model/CModel.h"
#include "model/CModelParameterSet.h"
#include "report/CKeyFactory.h"
#include "report/CReportDefinitionVector.h"
#include "report/CReportDefinition.h"

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

#define START_ELEMENT   -1
#define UNKNOWN_ELEMENT -2

#ifdef COPASI_TEMPLATE
CCopasiXMLParser::TEMPLATEElement::TEMPLATEElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::TEMPLATEElement::~TEMPLATEElement()
{
  pdelete(mpetcElement);
}

void CCopasiXMLParser::TEMPLATEElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mpCurrentHandler = NULL;
  mCurrentElement = mLastKnownElement;

  while (mpCurrentHandler == NULL)
    {
      mCurrentElement++; /* We should always be on the next element */

      switch (mCurrentElement)
        {
          case TEMPLATE:

            if (strcmp(pszName, "TEMPLATE"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                             pszName, "TEMPLATE", mParser.getCurrentLineNumber());

            mLastKnownElement = TEMPLATE;

            // Element specific code.
            return;

          case etc:

            if (!strcmp(pszName, "etc"))
              {
                /* If we do not have an etc element handler we create one. */
                if (!mpetcElement)
                  mpetcElement = new etcElement(mParser, mCommon);

                mpCurrentHandler = mpetcElement;
              }
            // Optional
            else
              {
                CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                               pszName, "etc", mParser.getCurrentLineNumber());
              }

            break;

          default:
            mCurrentElement = UNKNOWN_ELEMENT;
            mpCurrentHandler = &mParser.mUnknownElement;
            break;
        }
    }

  mParser.pushElementHandler(mpCurrentHandler);

  if (mpCurrentHandler != &mParser.mUnknownElement)
    {
      mLastKnownElement = mCurrentElement;
    }

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::TEMPLATEElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case TEMPLATE:

        if (strcmp(pszName, "TEMPLATE"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "TEMPLATE", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mLastKnownElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case etc:

        if (strcmp(pszName, "etc"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "etc", mParser.getCurrentLineNumber());

        // Element specific code

        break;

      case UNKNOWN_ELEMENT:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  mCurrentElement = TEMPLATE;
  return;
}

#endif // COPASI_TEMPLATE

CCopasiXMLParser::CCopasiXMLParser(CVersion & version) :
  CExpat(),
  mCommon(),
  mElementHandlerStack(),
  mUnknownElement(*this, this->mCommon),
  mCharacterDataElement(*this, this->mCommon),
  mListOfUnsupportedAnnotationsElement(*this, this->mCommon),
  mCommentElement(*this, this->mCommon),
  mMiriamAnnotationElement(*this, this->mCommon)
{
  create();

  mElementHandlerStack.push(new COPASIElement(*this, mCommon));

  //  mCommon.pParser = this;
  mCommon.pVersion = & version;
  mCommon.pModel = NULL;
  mCommon.pFunctionList = NULL;
  mCommon.pFunction = NULL;
  mCommon.pTaskList = NULL;
  mCommon.pReportList = NULL;
  mCommon.pReport = NULL;
  mCommon.mParameterGroupLevel = -1;
  mCommon.pGUI = NULL;

  mCommon.pPlotList = NULL;
  mCommon.UnmappedKeyParameters.clear();

  mCommon.pLayoutList = NULL;
  mCommon.pCurrentLayout = NULL;
  mCommon.pCompartmentGlyph = NULL;
  mCommon.pMetaboliteGlyph = NULL;
  mCommon.pReactionGlyph = NULL;
  mCommon.pTextGlyph = NULL;
  //mCommon.pAdditionalGO = NULL;
  mCommon.pGeneralGlyph = NULL;
  mCommon.pCurve = NULL;
  mCommon.pLineSegment = NULL;
  mCommon.pMetaboliteReferenceGlyph = NULL;
  mCommon.pRenderInformation = NULL;
  mCommon.pGradient = NULL;
  mCommon.pLineEnding = NULL;
  mCommon.pStyle = NULL;
  mCommon.pGroup = NULL;
  mCommon.pText = NULL;
  mCommon.pListOfCurveElements = NULL;

  enableElementHandler(true);
}

CCopasiXMLParser::~CCopasiXMLParser()
{
  // We need to destruct the top most element on the stack since it has been
  // allocated in the constructor.
  if (mElementHandlerStack.empty())
    return;

  while (mElementHandlerStack.size() > 1)
    mElementHandlerStack.pop();

  delete mElementHandlerStack.top();
}

void CCopasiXMLParser::onStartElement(const XML_Char *pszName,
                                      const XML_Char **papszAttrs)
{
  assert(mElementHandlerStack.size() != 0);
  mElementHandlerStack.top()->start(pszName, papszAttrs);
}

void CCopasiXMLParser::onEndElement(const XML_Char *pszName)
{
  if (mElementHandlerStack.size() != 0)
    mElementHandlerStack.top()->end(pszName);
  else
    return;
}

#ifdef XXXX
void CCopasiXMLParser::onStartCdataSection()
{
  long i = mParser.getCurrentByteIndex();
}

void CCopasiXMLParser::onEndCdataSection()
{
  long i = mParser.getCurrentByteIndex();
}
#endif // XXXX

void CCopasiXMLParser::enableCharacterDataHandler(bool fEnable)
{
  mCharacterData.erase();
  CExpat::enableCharacterDataHandler(fEnable);
}

void CCopasiXMLParser::onCharacterData(const XML_Char *pszData,
                                       int nLength)
{
  mCharacterData.append(pszData, nLength);
}

std::string CCopasiXMLParser::getCharacterData(const std::string & toBeStripped,
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

void CCopasiXMLParser::pushElementHandler(CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon > * elementHandler)
{mElementHandlerStack.push(elementHandler);}

void CCopasiXMLParser::popElementHandler()
{mElementHandlerStack.pop();}

void CCopasiXMLParser::setFunctionList(CCopasiVectorN< CFunction > * pFunctionList)
{mCommon.pFunctionList = pFunctionList;}

CModel * CCopasiXMLParser::getModel() const
{return mCommon.pModel;}

CReportDefinitionVector * CCopasiXMLParser::getReportList() const
{return mCommon.pReportList;}

CCopasiVectorN< CCopasiTask > * CCopasiXMLParser::getTaskList() const
{return mCommon.pTaskList;}

COutputDefinitionVector * CCopasiXMLParser::getPlotList() const
{return mCommon.pPlotList;}

void CCopasiXMLParser::setGUI(SCopasiXMLGUI * pGUI)
{mCommon.pGUI = pGUI;}

void CCopasiXMLParser::setLayoutList(CListOfLayouts * pLayoutList)
{mCommon.pLayoutList = pLayoutList;}

CListOfLayouts * CCopasiXMLParser::getLayoutList() const
{return mCommon.pLayoutList;}

const CCopasiParameterGroup * CCopasiXMLParser::getCurrentGroup() const
{return dynamic_cast< const CCopasiParameterGroup * >(mCommon.pCurrentParameter);}

const CCopasiObject * CCopasiXMLParser::getObjectFromName(const std::string & cn) const
{
  const CObjectInterface * pObject = NULL;
  CCopasiObjectName CN = CCopasiObjectName(cn).getRemainder();

  if (mCommon.pModel &&
      (pObject = mCommon.pModel->getObject(CN)))
    return static_cast< const CCopasiObject * >(pObject);

  if (mCommon.pTaskList &&
      (pObject = mCommon.pTaskList->getObject(CN)))
    return static_cast< const CCopasiObject * >(pObject);

  if (mCommon.pFunctionList &&
      (pObject = mCommon.pFunctionList->getObject(CN)))
    return static_cast< const CCopasiObject * >(pObject);

  return NULL;
}

CCopasiXMLParser::UnknownElement::UnknownElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mLineNumber(0)
{}

CCopasiXMLParser::UnknownElement::~UnknownElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::UnknownElement::start(const XML_Char * /*pszName*/ ,
    const XML_Char ** /* papszAttrs */)
{
  /* We count the level of subelements of the Unknown Element */
  mCurrentElement++;

  if (mCurrentElement == Unknown)
    {
      mLineNumber = mParser.getCurrentLineNumber();
    }

  return;
}

void CCopasiXMLParser::UnknownElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Unknown:
        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;
        {
          CCopasiMessage(CCopasiMessage::WARNING, MCXML + 3,
                         pszName, mLineNumber);
        }

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      default:
        mCurrentElement--;
        break;
    }

  return;
}

CCopasiXMLParser::COPASIElement::COPASIElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::COPASIElement::~COPASIElement() {deleteCurrentHandler();}

void CCopasiXMLParser::COPASIElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */
  mpCurrentHandler = NULL;

  const char * versionMajor;
  C_INT32 VersionMajor;
  const char * versionMinor;
  C_INT32 VersionMinor;
  const char * versionDevel;
  C_INT32 VersionDevel;
  bool CopasiSourcesModified = true;

  switch (mCurrentElement)
    {
      case COPASI:

        if (!strcmp(pszName, "COPASI"))
          {
            versionMajor = mParser.getAttributeValue("versionMajor", papszAttrs, "0");
            VersionMajor = strToInt(versionMajor);
            versionMinor = mParser.getAttributeValue("versionMinor", papszAttrs, "0");
            VersionMinor = strToInt(versionMinor);
            versionDevel = mParser.getAttributeValue("versionDevel", papszAttrs, "0");
            VersionDevel = strToInt(versionDevel);
            CopasiSourcesModified = mParser.toBool(mParser.getAttributeValue("copasiSourcesModified", papszAttrs, "true"));

            mCommon.pVersion->setVersion(VersionMajor, VersionMinor, VersionDevel, CopasiSourcesModified);

            return;
          }
        // We may have a configuration file which starts with a parameter group
        else if (!strcmp(pszName, "ParameterGroup"))
          {
            mpCurrentHandler = new ParameterGroupElement(mParser, mCommon);
          }
        else
          {
            mpCurrentHandler = &mParser.mUnknownElement;

            CCopasiMessage(CCopasiMessage::WARNING, MCXML + 10,
                           pszName, "COPASI", mParser.getCurrentLineNumber());
          }

        break;

      case ListOfFunctions:

        if (!strcmp(pszName, "ListOfFunctions"))
          mpCurrentHandler = new ListOfFunctionsElement(mParser, mCommon);

        break;

      case Model:

        if (!strcmp(pszName, "Model"))
          mpCurrentHandler = new ModelElement(mParser, mCommon);

        break;

      case ListOfTasks:

        if (!strcmp(pszName, "ListOfTasks"))
          mpCurrentHandler = new ListOfTasksElement(mParser, mCommon);

        break;

      case ListOfReports:

        if (!strcmp(pszName, "ListOfReports"))
          mpCurrentHandler = new ListOfReportsElement(mParser, mCommon);

        break;

      case ListOfPlots:

        if (!strcmp(pszName, "ListOfPlots"))
          mpCurrentHandler = new ListOfPlotsElement(mParser, mCommon);

        break;

      case GUI:

        if (!strcmp(pszName, "GUI"))
          {
            if (mCommon.pGUI)
              mpCurrentHandler = new GUIElement(mParser, mCommon);
            else
              mpCurrentHandler = &mParser.mUnknownElement;
          }

        break;

      case ListOfLayouts:

        if (!strcmp(pszName, "ListOfLayouts"))
          mpCurrentHandler = new ListOfLayoutsElement(mParser, mCommon);

        break;

      case SBMLReference:

        if (!strcmp(pszName, "SBMLReference"))
          mpCurrentHandler = new SBMLReferenceElement(mParser, mCommon);

        break;

      default:
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::COPASIElement::end(const XML_Char * pszName)
{
  if (!strcmp(pszName, "COPASI"))
    {
      mCurrentElement = START_ELEMENT;

      // We need to handle the unmapped parameters of type key.
      std::vector< std::string >::iterator it = mCommon.UnmappedKeyParameters.begin();
      std::vector< std::string >::iterator end = mCommon.UnmappedKeyParameters.end();

      for (; it != end; ++it)
        {
          CCopasiParameter * pParameter =
            dynamic_cast< CCopasiParameter * >(CCopasiRootContainer::getKeyFactory()->get(*it));

          if (pParameter != NULL &&
              pParameter->getType() == CCopasiParameter::KEY)
            {
              CCopasiObject * pObject =
                mCommon.KeyMap.get(*pParameter->getValue().pKEY);

              if (pObject != NULL)
                pParameter->setValue(pObject->getKey());
              else
                pParameter->setValue(std::string(""));
            }
        }

      // We need to remove the no longer needed expression "Objective Function" from the function list.
      if (mCommon.pFunctionList != NULL &&
          mCommon.pFunctionList->getIndex("Objective Function") != C_INVALID_INDEX)
        {
          mCommon.pFunctionList->remove("Objective Function");
        }

      return;
    }

  if (!strcmp(pszName, "ParameterGroup"))
    {
      mCurrentElement = START_ELEMENT;
    }
  else if (!strcmp(pszName, "GUI") && mCommon.pGUI == NULL)
    {
      CCopasiMessage::getLastMessage();
    }

  deleteCurrentHandler();

  //TODO why no case statement with error checking (like in other elements)?

  return;
}

CCopasiXMLParser::ListOfFunctionsElement::ListOfFunctionsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfFunctionsElement::~ListOfFunctionsElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfFunctionsElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfFunctions:

        if (strcmp(pszName, "ListOfFunctions"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfFunctions", mParser.getCurrentLineNumber());

        if (!mCommon.pFunctionList)
          mCommon.pFunctionList = new CCopasiVectorN< CFunction >;

        break;

      case Function:

        if (strcmp(pszName, "Function"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Function", mParser.getCurrentLineNumber());

        /* If we do not have a function element handler we create one. */
        if (!mpCurrentHandler)
          mpCurrentHandler = new FunctionElement(mParser, mCommon);

        /* Push the Function element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfFunctionsElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ListOfFunctions:

        if (strcmp(pszName, "ListOfFunctions"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfFunctions", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;
        {
          size_t i, imax = mCommon.pFunctionList->size();

          for (i = imax - 1; i != C_INVALID_INDEX; i--)
            {
              CFunction * pFunction =
                dynamic_cast<CFunction *>((*mCommon.pFunctionList)[i]);

              if (pFunction && !pFunction->compile())
                {
                  CCopasiMessage(CCopasiMessage::RAW, MCXML + 6,
                                 pFunction->getObjectName().c_str(),
                                 mParser.getCurrentLineNumber());
                  // We can keep the function as the compile is later checked again.
                  // mCommon.pFunctionList->CCopasiVector< CEvaluationTree >::remove(i);
                }
            }
        }

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case Function:

        if (strcmp(pszName, "Function"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Function", mParser.getCurrentLineNumber());

        mCurrentElement = ListOfFunctions;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::FunctionElement::FunctionElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mpMathMLElement(NULL),
  mpListOfParameterDescriptionsElement(NULL)
{}

CCopasiXMLParser::FunctionElement::~FunctionElement()
{
  pdelete(mpMathMLElement);
  pdelete(mpListOfParameterDescriptionsElement);
}

void CCopasiXMLParser::FunctionElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * type;
  CEvaluationTree::Type Type;
  const char * Name;
  const char * Reversible;
  size_t Index;

  mpCurrentHandler = NULL;
  mCurrentElement = mLastKnownElement;

  while (mpCurrentHandler == NULL)
    {
      mCurrentElement++; /* We should always be on the next element */
      CEvaluationTree* pEvaluationTree = NULL;

      switch (mCurrentElement)
        {
          case Function:

            if (strcmp(pszName, "Function"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                             pszName, "Function", mParser.getCurrentLineNumber());

            mKey = mParser.getAttributeValue("key", papszAttrs);
            Name = mParser.getAttributeValue("name", papszAttrs);
            type = mParser.getAttributeValue("type", papszAttrs);
            Type = toEnum(type, CEvaluationTree::XMLType, CEvaluationTree::UserDefined);

            Reversible = mParser.getAttributeValue("reversible", papszAttrs, false);

            if (!Reversible) // We may have an old file format using positive
              Reversible = mParser.getAttributeValue("positive", papszAttrs, "unspecified");

            mLastKnownElement = Function;

            mCommon.mPredefinedFunction = false;
            mCommon.mFunctionParameterKeyMap.clear();
            mExistingFunctionIndex.clear();

            pEvaluationTree = CEvaluationTree::create(Type);

            if (Type == CEvaluationTree::Expression)
              {
                mCommon.pFunction = NULL;

                mCommon.mpExpression = static_cast< CExpression * >(pEvaluationTree);
                mCommon.mKey2ObjectiveFunction[mKey] = mCommon.mpExpression;
              }
            else
              {
                mCommon.mpExpression = NULL;

                mCommon.pFunction = static_cast<CFunction *>(pEvaluationTree);
                mCommon.pFunction->setObjectName(Name);

                if (!strcmp(Reversible, "true"))
                  mCommon.pFunction->setReversible(TriTrue);
                else if (!strcmp(Reversible, "false"))
                  mCommon.pFunction->setReversible(TriFalse);
                else
                  mCommon.pFunction->setReversible(TriUnspecified);

                Index = mCommon.pFunctionList->getIndex(Name);

                if (Index != C_INVALID_INDEX) // A function with that name exists.
                  {
                    mExistingFunctionIndex.insert(Index);

                    switch ((*mCommon.pFunctionList)[Index]->getType())
                      {
                        case CEvaluationTree::MassAction:

                          if (Type == CEvaluationTree::MassAction)
                            {
                              pdelete(mCommon.pFunction);
                              mCommon.pFunction = (*mCommon.pFunctionList)[Index];
                              mCommon.mPredefinedFunction = true;
                            }
                          else
                            {
                              size_t Counter = 0;
                              std::string NewName;

                              while (true)
                                {
                                  Counter++;
                                  std::ostringstream ss;
                                  ss << Name << " [" << Counter << "]";
                                  NewName = ss.str();
                                  Index = mCommon.pFunctionList->getIndex(NewName);

                                  if (Index == C_INVALID_INDEX)
                                    break;

                                  mExistingFunctionIndex.insert(Index);
                                }

                              mCommon.pFunction->setObjectName(NewName);
                            }

                          break;

                        case CEvaluationTree::PreDefined:

                          if (Type == CEvaluationTree::PreDefined)
                            {
                              pdelete(mCommon.pFunction);
                              mCommon.pFunction = (*mCommon.pFunctionList)[Index];
                              mCommon.mPredefinedFunction = true;
                            }
                          else
                            {
                              size_t Counter = 0;
                              std::string NewName;

                              while (true)
                                {
                                  Counter++;
                                  std::ostringstream ss;
                                  ss << Name << " [" << Counter << "]";
                                  NewName = ss.str();
                                  Index = mCommon.pFunctionList->getIndex(NewName);

                                  if (Index == C_INVALID_INDEX)
                                    break;

                                  mExistingFunctionIndex.insert(Index);
                                }

                              mCommon.pFunction->setObjectName(NewName);
                            }

                          break;

                        case CEvaluationTree::UserDefined:
                        case CEvaluationTree::Function:
                          // Create a unique name
                        {
                          size_t Counter = 0;
                          std::string NewName;

                          while (true)
                            {
                              Counter++;
                              std::ostringstream ss;
                              ss << Name << " [" << Counter << "]";
                              NewName = ss.str();
                              Index = mCommon.pFunctionList->getIndex(NewName);

                              if (Index == C_INVALID_INDEX)
                                break;

                              mExistingFunctionIndex.insert(Index);
                            }

                          mCommon.pFunction->setObjectName(NewName);
                        }

                        break;

                        default:
                          break;
                      }
                  }
              }

            return;

          case MiriamAnnotation:

            if (!strcmp(pszName, "MiriamAnnotation"))
              mpCurrentHandler = &mParser.mMiriamAnnotationElement;

            break;

          case Comment:

            if (!strcmp(pszName, "Comment"))
              mpCurrentHandler = &mParser.mCommentElement;

            break;

          case ListOfUnsupportedAnnotations:

            if (!strcmp(pszName, "ListOfUnsupportedAnnotations"))
              mpCurrentHandler = &mParser.mListOfUnsupportedAnnotationsElement;

            break;

          case Expression:

            if (!strcmp(pszName, "Expression"))
              mpCurrentHandler = &mParser.mCharacterDataElement;
            else if (!strcmp(pszName, "MathML"))
              {
                /* If we do not have a MathML element handler we create one. */
                if (!mpMathMLElement)
                  mpMathMLElement = new MathMLElement(mParser, mCommon);

                mCurrentElement = MathML;
                mpCurrentHandler = mpMathMLElement;
              }
            else
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                             pszName, "Expression", mParser.getCurrentLineNumber());

            break;

          case ListOfParameterDescriptions:

            if (strcmp(pszName, "ListOfParameterDescriptions"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                             pszName, "ListOfParameterDescriptions", mParser.getCurrentLineNumber());

            /* If we do not have a ListOfParameterDescriptions element handler we create one. */
            if (!mpListOfParameterDescriptionsElement)
              mpListOfParameterDescriptionsElement = new ListOfParameterDescriptionsElement(mParser, mCommon);

            /* Push the ListOfParameterDescriptions element handler on the stack and call it. */
            mpCurrentHandler = mpListOfParameterDescriptionsElement;
            break;

          default:
            mCurrentElement = UNKNOWN_ELEMENT;
            mpCurrentHandler = &mParser.mUnknownElement;
            break;
        }
    }

  mParser.pushElementHandler(mpCurrentHandler);

  if (mpCurrentHandler != &mParser.mUnknownElement)
    {
      mLastKnownElement = mCurrentElement;
    }

  mParser.onStartElement(pszName, papszAttrs);
}

void CCopasiXMLParser::FunctionElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Function:

        if (strcmp(pszName, "Function"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Function", mParser.getCurrentLineNumber());

        mLastKnownElement = START_ELEMENT;
        mParser.popElementHandler();

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);

        if (mCommon.pFunction != NULL)
          {
            if (!mCommon.mPredefinedFunction)
              {
                // TODOWe need to check whether any existing function with the same
                // name is identical

                std::set< size_t >::const_iterator it = mExistingFunctionIndex.begin();
                std::set< size_t >::const_iterator end = mExistingFunctionIndex.end();

                for (; it != end; ++it)
                  {
                    CFunction * pFunction = (*mCommon.pFunctionList)[*it];

                    if (*pFunction == *mCommon.pFunction)
                      {
                        pdelete(mCommon.pFunction);
                        mCommon.pFunction = (*mCommon.pFunctionList)[*it];

                        break;
                      }
                  }

                /* We have a new function and add it to the list */
                if (it == end)
                  {
                    mCommon.pFunctionList->add(mCommon.pFunction, true);
                  }
              }

            addFix(mKey , mCommon.pFunction);

            std::map< size_t, std::string >::const_iterator it = mCommon.mFunctionParameterKeyMap.begin();
            std::map< size_t, std::string >::const_iterator end = mCommon.mFunctionParameterKeyMap.end();

            for (; it != end; ++it)
              {
                addFix(it->second, mCommon.pFunction->getVariables()[it->first]);
              }
          }

        break;

      case MiriamAnnotation:

        if (strcmp(pszName, "MiriamAnnotation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "MiriamAnnotation", mParser.getCurrentLineNumber());

        if (mCommon.pFunction != NULL)
          {
            mCommon.pFunction->setMiriamAnnotation(mCommon.CharacterData, mCommon.pFunction->getKey(), mKey);
            mCommon.CharacterData = "";
          }

        break;

      case Comment:

        if (strcmp(pszName, "Comment"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Comment", mParser.getCurrentLineNumber());

        if (mCommon.pFunction != NULL)
          {
            mCommon.pFunction->setNotes(mCommon.CharacterData);
            mCommon.CharacterData = "";
          }

        break;

      case ListOfUnsupportedAnnotations:

        if (strcmp(pszName, "ListOfUnsupportedAnnotations"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfUnsupportedAnnotations", mParser.getCurrentLineNumber());

        if (mCommon.pFunction != NULL)
          {
            mCommon.pFunction->getUnsupportedAnnotations() = mParser.mListOfUnsupportedAnnotationsElement.getUnsupportedAnnotations();
          }

        break;

      case Expression:

        if (strcmp(pszName, "Expression"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Expression", mParser.getCurrentLineNumber());

        if (mCommon.pFunction != NULL)
          {
            if (!mCommon.mPredefinedFunction)
              mCommon.pFunction->setInfix(mCommon.CharacterData);
          }
        else if (mCommon.mpExpression != NULL)
          {
            mCommon.mpExpression->setInfix(mCommon.CharacterData);
          }

        break;

      case ListOfParameterDescriptions:

        if (strcmp(pszName, "ListOfParameterDescriptions"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfParameterDescriptions", mParser.getCurrentLineNumber());

        break;

      case MathML:

        if (strcmp(pszName, "MathML"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "MathML", mParser.getCurrentLineNumber());

        if (mCommon.pFunction != NULL)
          {
            if (!mCommon.mPredefinedFunction)
              mCommon.pFunction->setInfix(mCommon.CharacterData);
          }
        else if (mCommon.mpExpression != NULL)
          {
            mCommon.mpExpression->setInfix(mCommon.CharacterData);
          }

        // MathML is in place of Expression in old CopasiML files.
        mLastKnownElement = Expression;
        break;

      case UNKNOWN_ELEMENT:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  mCurrentElement = Function;

  return;
}

CCopasiXMLParser::MathMLElement::MathMLElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::MathMLElement::~MathMLElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::MathMLElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case MathML:

        if (strcmp(pszName, "MathML"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "MathML", mParser.getCurrentLineNumber());

        break;

      case Text:

        if (strcmp(pszName, "Text"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Text", mParser.getCurrentLineNumber());

        /* If we do not have a function element handler we create one. */
        if (!mpCurrentHandler)
          mpCurrentHandler = new CharacterDataElement(mParser, mCommon);

        /* Push the Function element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::MathMLElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case MathML:

        if (strcmp(pszName, "MathML"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "MathML", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case Text:

        if (strcmp(pszName, "Text"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Text", mParser.getCurrentLineNumber());

        mCurrentElement = MathML;

        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }
}

CCopasiXMLParser::CharacterDataElement::CharacterDataElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::CharacterDataElement::~CharacterDataElement()
{}

void CCopasiXMLParser::CharacterDataElement::start(const XML_Char *pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case CharacterData:
        mCurrentElementName = pszName;
        mParser.enableCharacterDataHandler(true);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::CharacterDataElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case CharacterData:

        if (strcmp(pszName, mCurrentElementName.c_str()))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, mCurrentElementName.c_str(), mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;
        mCommon.CharacterData = mParser.getCharacterData("\x0a\x0d\t", "");
        {
          std::string::size_type Start = mCommon.CharacterData.find_first_not_of(" ");

          if (Start == std::string::npos)
            mCommon.CharacterData = "";
          else
            {
              std::string::size_type End = mCommon.CharacterData.find_last_not_of(" ");

              if (End == std::string::npos)
                mCommon.CharacterData = mCommon.CharacterData.substr(Start);
              else
                mCommon.CharacterData = mCommon.CharacterData.substr(Start, End - Start + 1);
            }
        }
        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }
}

CCopasiXMLParser::ListOfParameterDescriptionsElement::ListOfParameterDescriptionsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfParameterDescriptionsElement::~ListOfParameterDescriptionsElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfParameterDescriptionsElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfParameterDescriptions:

        mCommon.mFunctionParameterKeyMap.clear();

        if (strcmp(pszName, "ListOfParameterDescriptions"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfParameterDescriptions", mParser.getCurrentLineNumber());

        if (mpCurrentHandler) mpCurrentHandler->reset();

        break;

      case ParameterDescription:

        if (strcmp(pszName, "ParameterDescription"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ParameterDescription", mParser.getCurrentLineNumber());

        /* If we do not have a ParameterDescription element handler we create one. */
        if (!mpCurrentHandler)
          mpCurrentHandler = new ParameterDescriptionElement(mParser, mCommon);

        /* Push the ParameterDescription element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfParameterDescriptionsElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ListOfParameterDescriptions:

        if (strcmp(pszName, "ListOfParameterDescriptions"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfParameterDescriptions", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        // We need to remove all parameters which have been temporarily added to the list of variables
        {
          CFunction * pFunction = dynamic_cast<CFunction *>(mCommon.pFunction);

          if (pFunction)
            {
              CFunctionParameters & Variables = pFunction->getVariables();
              size_t i = Variables.size() - 1;

              for (; i != C_INVALID_INDEX && Variables[i]->getUsage() == CFunctionParameter::TEMPORARY; i--)
                Variables.remove(Variables[i]->getObjectName());
            }
        }
        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case ParameterDescription:

        if (strcmp(pszName, "ParameterDescription"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ParameterDescription", mParser.getCurrentLineNumber());

        mCurrentElement = ListOfParameterDescriptions;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ParameterDescriptionElement::ParameterDescriptionElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mOrder(0)
{}

CCopasiXMLParser::ParameterDescriptionElement::~ParameterDescriptionElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ParameterDescriptionElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * Key;
  const char * Name;
  const char * order;
  unsigned C_INT32 Order;
  const char * role; /*substrate, product, modifier, constant, other*/
  CFunctionParameter::Role Role;
  const char * minOccurs;
  unsigned C_INT32 MinOccurs;
  const char * maxOccurs;
  unsigned C_INT32 MaxOccurs;

  mCurrentElement++; /* We should always be on the next element */

  //std::string Usage[] = {"SUBSTRATE", "PRODUCT", "MODIFIER", "PARAMETER"};
  CFunctionParameter * pParm = NULL;
  CFunction * pFunction = dynamic_cast<CFunction *>(mCommon.pFunction);

  if (!pFunction) mCurrentElement++;

  switch (mCurrentElement)
    {
      case ParameterDescription:

        if (strcmp(pszName, "ParameterDescription"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ParameterDescription", mParser.getCurrentLineNumber());

        Key = mParser.getAttributeValue("key", papszAttrs);
        Name = mParser.getAttributeValue("name", papszAttrs);

        order = mParser.getAttributeValue("order", papszAttrs);
        Order = (unsigned C_INT32) atoi(order);

        role = mParser.getAttributeValue("role", papszAttrs);
        Role = CFunctionParameter::xmlRole2Enum(role);
        //if (Role == "") fatalError();

        minOccurs = mParser.getAttributeValue("minOccurs", papszAttrs, "1");
        MinOccurs = strToUnsignedInt(minOccurs);

        maxOccurs = mParser.getAttributeValue("maxOccurs", papszAttrs , "1");

        if (std::string("unbounded") == std::string(maxOccurs))
          MaxOccurs = (unsigned C_INT32) - 1;
        else
          MaxOccurs = strToUnsignedInt(maxOccurs);

        if (mCommon.mPredefinedFunction)
          {
            addFix(Key, pFunction->getVariables()[Name]);
          }
        else
          {
            // If we are here we have a user defined function.
            // We need to check whether the variable exists within the function.
            CFunctionParameter::DataType DataType;
            size_t Index =
              pFunction->getVariables().findParameterByName(Name, DataType);

            bool isUsed = true;

            if (Index == C_INVALID_INDEX)
              {
                // We add the missing parameter and mark it as unused.
                pFunction->getVariables().add(Name,
                                              CFunctionParameter::FLOAT64,
                                              Role);

                Index = pFunction->getVariables().findParameterByName(Name, DataType);
                isUsed = false;
              }

            // Make sure that we have enough parameter to swap
            size_t Counter = 0;

            while (Order >= pFunction->getVariables().size())
              {
                std::string NewName = StringPrint("TMP_%d", Counter++);

                while (!pFunction->getVariables().add(NewName,
                                                      CFunctionParameter::FLOAT64,
                                                      CFunctionParameter::TEMPORARY)) {};

                NewName = StringPrint("TMP_%d", Counter++);
              }

            // Assure that the order is correct
            if (Order != Index)
              pFunction->getVariables().swap(Order, Index);

            pParm = pFunction->getVariables()[Order];
            pParm->setObjectName(Name);
            pParm->setUsage(Role);
            pParm->setIsUsed(isUsed);

            if (MaxOccurs == 1 && MinOccurs == 1)
              pParm->setType(CFunctionParameter::FLOAT64);
            else
              pParm->setType(CFunctionParameter::VFLOAT64);

            mCommon.mFunctionParameterKeyMap[Order] = Key;
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ParameterDescriptionElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ParameterDescription:

        if (strcmp(pszName, "ParameterDescription"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ParameterDescription", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

void CCopasiXMLParser::ParameterDescriptionElement::reset()
{mOrder = 0;}

CCopasiXMLParser::ModelElement::ModelElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ModelElement::~ModelElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ModelElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * Name;
  const char * timeUnit;
  CUnit::TimeUnit TimeUnit;
  const char * volumeUnit;
  CUnit::VolumeUnit VolumeUnit;
  const char * areaUnit;
  CUnit::AreaUnit AreaUnit;
  const char * lengthUnit;
  CUnit::LengthUnit LengthUnit;
  const char * quantityUnit;
  CUnit::QuantityUnit QuantityUnit;
  CModel::ModelType ModelType;
  C_FLOAT64 Avogadro;

  mpCurrentHandler = NULL;
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case Model:

        if (strcmp(pszName, "Model"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Model", mParser.getCurrentLineNumber());

        mKey = mParser.getAttributeValue("key", papszAttrs);
        Name = mParser.getAttributeValue("name", papszAttrs);

        timeUnit = mParser.getAttributeValue("timeUnit", papszAttrs);
        TimeUnit = toEnum(timeUnit, CUnit::TimeUnitNames, CUnit::OldMinute);

        if (TimeUnit == CUnit::OldMinute)
          {
            if (strcmp(timeUnit, "m"))
              TimeUnit = CUnit::s;
            else
              TimeUnit = CUnit::min;
          }

        volumeUnit = mParser.getAttributeValue("volumeUnit", papszAttrs);
        VolumeUnit = toEnum(volumeUnit, CUnit::VolumeUnitNames, CUnit::ml);

        //the next 2 attributes are introduced in Build 31, they have a default for
        //reading older cps files
        areaUnit = mParser.getAttributeValue("areaUnit", papszAttrs, "m\xc2\xb2");
        AreaUnit = toEnum(areaUnit, CUnit::AreaUnitNames, CUnit::m2);

        lengthUnit = mParser.getAttributeValue("lengthUnit", papszAttrs, "m");
        LengthUnit = toEnum(lengthUnit, CUnit::LengthUnitNames, CUnit::m);

        quantityUnit = mParser.getAttributeValue("quantityUnit", papszAttrs);
        QuantityUnit = toEnum(quantityUnit, CUnit::QuantityUnitNames, CUnit::OldXML);

        if (QuantityUnit == CUnit::OldXML)
          QuantityUnit = toEnum(quantityUnit, CUnit::QuantityUnitOldXMLNames, CUnit::mMol);

        ModelType = toEnum(mParser.getAttributeValue("type", papszAttrs, "deterministic"),
                           CModel::ModelTypeNames, CModel::deterministic);

        Avogadro = CCopasiXMLInterface::DBL(mParser.getAttributeValue("avogadroConstant", papszAttrs, CUnit::Avogadro));

        if (!mCommon.pModel) mCommon.pModel = new CModel(mCommon.pDataModel);

        // We remove the default parameter set:
        mCommon.pModel->getModelParameterSets().CCopasiVector< CModelParameterSet >::remove((size_t) 0);

        addFix(mKey, mCommon.pModel);
        mCommon.pModel->setObjectName(Name);
        mCommon.pModel->setTimeUnit(TimeUnit);
        mCommon.pModel->setVolumeUnit(VolumeUnit);
        mCommon.pModel->setAreaUnit(AreaUnit);
        mCommon.pModel->setLengthUnit(LengthUnit);
        mCommon.pModel->setQuantityUnit(QuantityUnit);
        mCommon.pModel->setModelType(ModelType);
        mCommon.pModel->setAvogadro(Avogadro);

        return;
        break;

      case MiriamAnnotation:

        if (!strcmp(pszName, "MiriamAnnotation"))
          {
            mpCurrentHandler = &mParser.mMiriamAnnotationElement;
            mLastKnownElement = mCurrentElement;
          }

        break;

      case Comment:

        if (!strcmp(pszName, "Comment"))
          {
            mpCurrentHandler = &mParser.mCommentElement;
            mLastKnownElement = mCurrentElement;
          }

        break;

      case ListOfUnsupportedAnnotations:

        if (!strcmp(pszName, "ListOfUnsupportedAnnotations"))
          {
            mpCurrentHandler = &mParser.mListOfUnsupportedAnnotationsElement;
            mLastKnownElement = mCurrentElement;
          }

        break;

      case InitialExpression:

        if (!strcmp(pszName, "InitialExpression"))
          {
            mpCurrentHandler = &mParser.mCharacterDataElement;
            mLastKnownElement = mCurrentElement;
          }

        break;

      case ListOfCompartments:

        if (!strcmp(pszName, "ListOfCompartments"))
          {
            mpCurrentHandler = new ListOfCompartmentsElement(mParser, mCommon);
            mLastKnownElement = mCurrentElement;
          }

        break;

      case ListOfMetabolites:

        if (!strcmp(pszName, "ListOfMetabolites"))
          {
            mpCurrentHandler = new ListOfMetabolitesElement(mParser, mCommon);
            mLastKnownElement = mCurrentElement;
          }

        break;

      case ListOfModelValues:

        if (!strcmp(pszName, "ListOfModelValues"))
          {
            mpCurrentHandler = new ListOfModelValuesElement(mParser, mCommon);
            mLastKnownElement = mCurrentElement;
          }

        break;

      case ListOfReactions:

        if (!strcmp(pszName, "ListOfReactions"))
          {
            mpCurrentHandler = new ListOfReactionsElement(mParser, mCommon);
            mLastKnownElement = mCurrentElement;
          }

        break;

      case ListOfEvents:

        if (!strcmp(pszName, "ListOfEvents"))
          {
            mpCurrentHandler = new ListOfEventsElement(mParser, mCommon);
            mLastKnownElement = mCurrentElement;
          }

        break;

      case ListOfModelParameterSets:

        if (!strcmp(pszName, "ListOfModelParameterSets"))
          {
            mpCurrentHandler = new ListOfModelParameterSetsElement(mParser, mCommon);
            mLastKnownElement = mCurrentElement;
          }

        break;

      case StateTemplate:

        if (!strcmp(pszName, "StateTemplate"))
          {
            mpCurrentHandler = new StateTemplateElement(mParser, mCommon);
            mLastKnownElement = mCurrentElement;
          }

        break;

      case InitialState:

        if (!strcmp(pszName, "InitialState"))
          {
            mpCurrentHandler = new InitialStateElement(mParser, mCommon);
            mLastKnownElement = mCurrentElement;
          }

        break;

      default:
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler =  &mParser.mUnknownElement;
        break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::ModelElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Model:

        if (strcmp(pszName, "Model"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Model", mParser.getCurrentLineNumber());

        mCommon.pModel->setCompileFlag(true);

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case MiriamAnnotation:

        if (strcmp(pszName, "MiriamAnnotation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "MiriamAnnotation", mParser.getCurrentLineNumber());

        mCommon.pModel->setMiriamAnnotation(mCommon.CharacterData, mCommon.pModel->getKey(), mKey);
        mCommon.CharacterData = "";
        break;

      case Comment:

        if (strcmp(pszName, "Comment"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Comment", mParser.getCurrentLineNumber());

        mCommon.pModel->setNotes(mCommon.CharacterData);
        mCommon.CharacterData = "";
        break;

      case ListOfUnsupportedAnnotations:

        if (strcmp(pszName, "ListOfUnsupportedAnnotations"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfUnsupportedAnnotations", mParser.getCurrentLineNumber());

        mCommon.pModel->getUnsupportedAnnotations() = mParser.mListOfUnsupportedAnnotationsElement.getUnsupportedAnnotations();
        break;

      case InitialExpression:

        if (strcmp(pszName, "InitialExpression"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "InitialExpression", mParser.getCurrentLineNumber());

        {
          size_t Size = CCopasiMessage::size();

          mCommon.pModel->setInitialExpression(mCommon.CharacterData);

          // Remove error messages created by setExpression as this may fail
          // due to incomplete model specification at this time.
          while (CCopasiMessage::size() > Size)
            CCopasiMessage::getLastMessage();
        }

        // Old CopasiML files have the incorrect order and the comment may appear after
        // the initial expression. Therefore, we reset to MiriamAnnotation.
        mCurrentElement = MiriamAnnotation;
        break;

      case ListOfCompartments:

        if (strcmp(pszName, "ListOfCompartments"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfCompartments", mParser.getCurrentLineNumber());

        deleteCurrentHandler();
        break;

      case ListOfMetabolites:

        if (strcmp(pszName, "ListOfMetabolites"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfMetabolites", mParser.getCurrentLineNumber());

        deleteCurrentHandler();
        break;

      case ListOfModelValues:

        if (strcmp(pszName, "ListOfModelValues"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfModelValues", mParser.getCurrentLineNumber());

        deleteCurrentHandler();
        break;

      case ListOfReactions:

        if (strcmp(pszName, "ListOfReactions"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfReactions", mParser.getCurrentLineNumber());

        deleteCurrentHandler();
        break;

      case ListOfEvents:

        if (strcmp(pszName, "ListOfEvents"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfEvents", mParser.getCurrentLineNumber());

        deleteCurrentHandler();
        break;

      case ListOfModelParameterSets:

        if (strcmp(pszName, "ListOfModelParameterSets"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfModelParameterSets", mParser.getCurrentLineNumber());

        deleteCurrentHandler();
        mCurrentElement = Model; // This is possibly the last element.
        break;

      case StateTemplate:

        if (strcmp(pszName, "StateTemplate"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "StateTemplate", mParser.getCurrentLineNumber());

        deleteCurrentHandler();
        break;

      case InitialState:

        if (strcmp(pszName, "InitialState"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "InitialState", mParser.getCurrentLineNumber());

        deleteCurrentHandler();
        mCurrentElement = Model; // This is possibly the last element.
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        mCurrentElement = Model; // This is possibly the last element.
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::CommentElement::CommentElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mXhtml(),
  mLevel(0)
{}

CCopasiXMLParser::CommentElement::~CommentElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::CommentElement::start(const XML_Char *pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */
  const XML_Char ** ppAttrs;

  if (mLevel) mCurrentElement = xhtml;

  switch (mCurrentElement)
    {
      case Comment:

        if (strcmp(pszName, "Comment"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Comment", mParser.getCurrentLineNumber());

        mXhtml.str("");
        mLevel = 0;
        mParser.enableCharacterDataHandler();
        mElementEmpty.push(false);
        break;

      case xhtml:

        if (mElementEmpty.top() == true)
          {
            mXhtml << ">";
            mElementEmpty.top() = false;
          }

        mXhtml << CCopasiXMLInterface::encode(mParser.getCharacterData());
        mXhtml << "<" << pszName;

        for (ppAttrs = papszAttrs; *ppAttrs && **ppAttrs; ppAttrs += 2)
          mXhtml << " " << *ppAttrs << "=\""
                 << CCopasiXMLInterface::encode(*(ppAttrs + 1), CCopasiXMLInterface::attribute) << "\"";

        mLevel++;
        mElementEmpty.push(true);

        mParser.enableCharacterDataHandler();
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::CommentElement::end(const XML_Char *pszName)
{
  std::string Xhtml;

  switch (mCurrentElement)
    {
      case Comment:

        if (strcmp(pszName, "Comment"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Comment", mParser.getCurrentLineNumber());

        if (mXhtml.str() != "")
          mXhtml << CCopasiXMLInterface::encode(mParser.getCharacterData());
        else
          mXhtml << mParser.getCharacterData();

        mCommon.CharacterData = mXhtml.str();

        {
          // remove leading whitepsaces
          std::string::size_type pos = mCommon.CharacterData.find_first_not_of("\x0a\x0d\t ");

          if (pos != 0) mCommon.CharacterData.erase(0, pos);

          // remove trailing whitepsace
          pos = mCommon.CharacterData.find_last_not_of("\x0a\x0d\t ");

          if (pos < mCommon.CharacterData.length())
            mCommon.CharacterData = mCommon.CharacterData.substr(0, pos + 1);
        }

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;
        mElementEmpty.pop();

        deleteCurrentHandler();

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case xhtml:
        Xhtml = mParser.getCharacterData();

        // Check whether and how we need to close the attribute
        if (mElementEmpty.top() == true)
          {
            if (Xhtml != "")
              {
                mElementEmpty.top() = false;
                mXhtml << ">";
              }
            else
              mXhtml << " />";
          }

        if (Xhtml != "")
          mXhtml << CCopasiXMLInterface::encode(Xhtml);

        if (mElementEmpty.top() == false)
          mXhtml << "</" << pszName << ">";

        mElementEmpty.pop();
        mElementEmpty.top() = false;
        mLevel--;

        if (!mLevel) mCurrentElement = Comment;

        mParser.enableCharacterDataHandler();
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ListOfCompartmentsElement::ListOfCompartmentsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfCompartmentsElement::~ListOfCompartmentsElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfCompartmentsElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfCompartments:

        if (strcmp(pszName, "ListOfCompartments"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfCompartments", mParser.getCurrentLineNumber());

        mCommon.pModel->getCompartments().clear();
        break;

      case Compartment:

        if (strcmp(pszName, "Compartment"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Compartment", mParser.getCurrentLineNumber());

        /* If we do not have a function element handler we create one. */
        if (!mpCurrentHandler)
          mpCurrentHandler = new CompartmentElement(mParser, mCommon);

        /* Push the Compartment element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfCompartmentsElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ListOfCompartments:

        if (strcmp(pszName, "ListOfCompartments"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfCompartments", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case Compartment:

        if (strcmp(pszName, "Compartment"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Compartment", mParser.getCurrentLineNumber());

        mCurrentElement = ListOfCompartments;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::CompartmentElement::CompartmentElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mpCompartment(NULL)
{}

CCopasiXMLParser::CompartmentElement::~CompartmentElement()
{}

void CCopasiXMLParser::CompartmentElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * Name;
  const char * simulationType;
  const char * Dimensionality;
  CModelEntity::Status SimulationType;

  mpCurrentHandler = NULL;
  mCurrentElement = mLastKnownElement;

  while (mpCurrentHandler == NULL)
    {
      mCurrentElement++; /* We should always be on the next element */

      switch (mCurrentElement)
        {
          case Compartment:

            if (strcmp(pszName, "Compartment"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                             pszName, "Compartment", mParser.getCurrentLineNumber());

            mKey = mParser.getAttributeValue("key", papszAttrs);
            Name = mParser.getAttributeValue("name", papszAttrs);
            simulationType = mParser.getAttributeValue("simulationType", papszAttrs, "fixed");
            SimulationType = toEnum(simulationType, CModelEntity::XMLStatus, CModel::FIXED);
            Dimensionality = mParser.getAttributeValue("dimensionality", papszAttrs, "3");

            mpCompartment = new CCompartment();
            addFix(mKey, mpCompartment);

            mpCompartment->setObjectName(Name);
            mpCompartment->setStatus(SimulationType);
            mpCompartment->setDimensionality(strToUnsignedInt(Dimensionality));

            mCommon.pModel->getCompartments().add(mpCompartment, true);
            mLastKnownElement = Compartment;
            return;

          case MiriamAnnotation:

            if (!strcmp(pszName, "MiriamAnnotation"))
              mpCurrentHandler = &mParser.mMiriamAnnotationElement;

            break;

          case Comment:

            if (!strcmp(pszName, "Comment"))
              mpCurrentHandler = &mParser.mCommentElement;

            break;

          case ListOfUnsupportedAnnotations:

            if (!strcmp(pszName, "ListOfUnsupportedAnnotations"))
              mpCurrentHandler = &mParser.mListOfUnsupportedAnnotationsElement;

            break;

          case Expression:

            if (!strcmp(pszName, "Expression"))
              mpCurrentHandler = &mParser.mCharacterDataElement;

            break;

          case InitialExpression:

            if (!strcmp(pszName, "InitialExpression"))
              mpCurrentHandler = &mParser.mCharacterDataElement;

            break;

          default:
            mCurrentElement = UNKNOWN_ELEMENT;
            mpCurrentHandler = &mParser.mUnknownElement;
            break;
        }
    }

  mParser.pushElementHandler(mpCurrentHandler);

  if (mpCurrentHandler != &mParser.mUnknownElement)
    {
      mLastKnownElement = mCurrentElement;
    }

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::CompartmentElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Compartment:

        if (strcmp(pszName, "Compartment"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Compartment", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mLastKnownElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case MiriamAnnotation:

        if (strcmp(pszName, "MiriamAnnotation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "MiriamAnnotation", mParser.getCurrentLineNumber());

        mpCompartment->setMiriamAnnotation(mCommon.CharacterData, mpCompartment->getKey(), mKey);
        mCommon.CharacterData = "";
        break;

      case Comment:

        if (strcmp(pszName, "Comment"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Comment", mParser.getCurrentLineNumber());

        mpCompartment->setNotes(mCommon.CharacterData);
        mCommon.CharacterData = "";
        break;

      case ListOfUnsupportedAnnotations:

        if (strcmp(pszName, "ListOfUnsupportedAnnotations"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfUnsupportedAnnotations", mParser.getCurrentLineNumber());

        mpCompartment->getUnsupportedAnnotations() = mParser.mListOfUnsupportedAnnotationsElement.getUnsupportedAnnotations();

        break;

      case Expression:

        if (strcmp(pszName, "Expression"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Expression", mParser.getCurrentLineNumber());

        {
          size_t Size = CCopasiMessage::size();

          mpCompartment->setExpression(mCommon.CharacterData);

          // Remove error messages created by setExpression as this may fail
          // due to incomplete model specification at this time.
          while (CCopasiMessage::size() > Size)
            CCopasiMessage::getLastMessage();
        }
        break;

      case InitialExpression:

        if (strcmp(pszName, "InitialExpression"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "InitialExpression", mParser.getCurrentLineNumber());

        {
          size_t Size = CCopasiMessage::size();

          mpCompartment->setInitialExpression(mCommon.CharacterData);

          // Remove error messages created by setExpression as this may fail
          // due to incomplete model specification at this time.
          while (CCopasiMessage::size() > Size)
            CCopasiMessage::getLastMessage();
        }

        break;

      case UNKNOWN_ELEMENT:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  mCurrentElement = Compartment;
  return;
}

CCopasiXMLParser::ListOfMetabolitesElement::ListOfMetabolitesElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfMetabolitesElement::~ListOfMetabolitesElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfMetabolitesElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfMetabolites:

        if (strcmp(pszName, "ListOfMetabolites"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfMetabolites", mParser.getCurrentLineNumber());

        break;

      case Metabolite:

        if (strcmp(pszName, "Metabolite"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Metabolite", mParser.getCurrentLineNumber());

        /* If we do not have a function element handler we create one. */
        if (!mpCurrentHandler)
          mpCurrentHandler = new MetaboliteElement(mParser, mCommon);

        /* Push the Metabolite element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfMetabolitesElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ListOfMetabolites:

        if (strcmp(pszName, "ListOfMetabolites"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfMetabolites", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case Metabolite:

        if (strcmp(pszName, "Metabolite"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Metabolite", mParser.getCurrentLineNumber());

        mCurrentElement = ListOfMetabolites;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::MetaboliteElement::MetaboliteElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mpMetabolite(NULL)
{}

CCopasiXMLParser::MetaboliteElement::~MetaboliteElement()
{}

void CCopasiXMLParser::MetaboliteElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  CCompartment * pCompartment = NULL;
  const char * Name;
  const char * simulationType;
  CModelEntity::Status SimulationType;
  const char reactions[] = "reactions";
  const char * Compartment;

  mpCurrentHandler = NULL;
  mCurrentElement = mLastKnownElement;

  while (mpCurrentHandler == NULL)
    {
      mCurrentElement++; /* We should always be on the next element */

      switch (mCurrentElement)
        {
          case Metabolite:

            if (strcmp(pszName, "Metabolite"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                             pszName, "Metabolite", mParser.getCurrentLineNumber());

            mKey = mParser.getAttributeValue("key", papszAttrs);
            Name = mParser.getAttributeValue("name", papszAttrs);

            simulationType = mParser.getAttributeValue("simulationType", papszAttrs, false);

            // We need to handle old files which used the attribute status.
            if (!simulationType)
              {
                simulationType = mParser.getAttributeValue("status", papszAttrs, false);

                if (!simulationType) // status and simulationType are both missing
                  simulationType = mParser.getAttributeValue("simulationType", papszAttrs);
                else if (!strcmp(simulationType, "variable")) // reactions was named variable
                  simulationType = reactions;
              }

            SimulationType = toEnum(simulationType, CModelEntity::XMLStatus, CModelEntity::REACTIONS);
            Compartment = mParser.getAttributeValue("compartment", papszAttrs);

            mpMetabolite = new CMetab();
            addFix(mKey, mpMetabolite);
            mpMetabolite->setObjectName(Name);
            mpMetabolite->setStatus(SimulationType);

            pCompartment =
              dynamic_cast< CCompartment* >(mCommon.KeyMap.get(Compartment));

            if (!pCompartment) fatalError();

            pCompartment->addMetabolite(mpMetabolite);
            mCommon.pModel->getMetabolites().add(mpMetabolite);

            mLastKnownElement = mCurrentElement;
            return;

          case MiriamAnnotation:

            if (!strcmp(pszName, "MiriamAnnotation"))
              mpCurrentHandler = &mParser.mMiriamAnnotationElement;

            break;

          case Comment:

            if (!strcmp(pszName, "Comment"))
              {
                mpCurrentHandler = &mParser.mCommentElement;
                mLastKnownElement = mCurrentElement;
              }

            break;

          case ListOfUnsupportedAnnotations:

            if (!strcmp(pszName, "ListOfUnsupportedAnnotations"))
              mpCurrentHandler = &mParser.mListOfUnsupportedAnnotationsElement;

            break;

          case Expression:

            if (!strcmp(pszName, "Expression"))
              mpCurrentHandler = &mParser.mCharacterDataElement;

            break;

          case InitialExpression:

            if (!strcmp(pszName, "InitialExpression"))
              mpCurrentHandler = &mParser.mCharacterDataElement;

            break;

          default:
            mCurrentElement = UNKNOWN_ELEMENT;
            mpCurrentHandler = &mParser.mUnknownElement;
            break;
        }
    }

  mParser.pushElementHandler(mpCurrentHandler);

  if (mpCurrentHandler != &mParser.mUnknownElement)
    {
      mLastKnownElement = mCurrentElement;
    }

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::MetaboliteElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Metabolite:

        if (strcmp(pszName, "Metabolite"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Metabolite", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mLastKnownElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case MiriamAnnotation:

        if (strcmp(pszName, "MiriamAnnotation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "MiriamAnnotation", mParser.getCurrentLineNumber());

        mpMetabolite->setMiriamAnnotation(mCommon.CharacterData, mpMetabolite->getKey(), mKey);
        mCommon.CharacterData = "";
        break;

      case Comment:

        if (strcmp(pszName, "Comment"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Comment", mParser.getCurrentLineNumber());

        mpMetabolite->setNotes(mCommon.CharacterData);
        mCommon.CharacterData = "";
        break;

      case ListOfUnsupportedAnnotations:

        if (strcmp(pszName, "ListOfUnsupportedAnnotations"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfUnsupportedAnnotations", mParser.getCurrentLineNumber());

        mpMetabolite->getUnsupportedAnnotations() = mParser.mListOfUnsupportedAnnotationsElement.getUnsupportedAnnotations();

        break;

      case Expression:

        if (strcmp(pszName, "Expression"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Expression", mParser.getCurrentLineNumber());

        {
          size_t Size = CCopasiMessage::size();

          mpMetabolite->setExpression(mCommon.CharacterData);

          // Remove error messages created by setExpression as this may fail
          // due to incomplete model specification at this time.
          while (CCopasiMessage::size() > Size)
            CCopasiMessage::getLastMessage();
        }

        break;

      case InitialExpression:

        if (strcmp(pszName, "InitialExpression"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "InitialExpression", mParser.getCurrentLineNumber());

        {
          size_t Size = CCopasiMessage::size();

          mpMetabolite->setInitialExpression(mCommon.CharacterData);

          // Remove error messages created by setExpression as this may fail
          // due to incomplete model specification at this time.
          while (CCopasiMessage::size() > Size)
            CCopasiMessage::getLastMessage();
        }

        break;

      case UNKNOWN_ELEMENT:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  mCurrentElement = Metabolite;
  return;
}

//****** TODO: ModelValues

CCopasiXMLParser::ListOfModelValuesElement::ListOfModelValuesElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfModelValuesElement::~ListOfModelValuesElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfModelValuesElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfModelValues:

        if (strcmp(pszName, "ListOfModelValues"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfModelValues", mParser.getCurrentLineNumber());

        break;

      case ModelValue:

        if (strcmp(pszName, "ModelValue"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ModelValue", mParser.getCurrentLineNumber());

        /* If we do not have a function element handler we create one. */
        if (!mpCurrentHandler)
          mpCurrentHandler = new ModelValueElement(mParser, mCommon);

        /* Push the Metabolite element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfModelValuesElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ListOfModelValues:

        if (strcmp(pszName, "ListOfModelValues"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfModelValues", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case ModelValue:

        if (strcmp(pszName, "ModelValue"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ModelValue", mParser.getCurrentLineNumber());

        mCurrentElement = ListOfModelValues;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ModelValueElement::ModelValueElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mpMV(NULL),
  mpMathMLElement(NULL),
  mKey("")
{}

CCopasiXMLParser::ModelValueElement::~ModelValueElement()
{
  pdelete(mpMathMLElement);
}

void CCopasiXMLParser::ModelValueElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * Name;
  const char * simulationType;
  CModelEntity::Status SimulationType;

  mpCurrentHandler = NULL;
  mCurrentElement = mLastKnownElement;

  while (mpCurrentHandler == NULL)
    {
      mCurrentElement++; /* We should always be on the next element */

      switch (mCurrentElement)
        {
          case ModelValue:

            if (strcmp(pszName, "ModelValue"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                             pszName, "ModelValue", mParser.getCurrentLineNumber());

            mKey = mParser.getAttributeValue("key", papszAttrs);
            Name = mParser.getAttributeValue("name", papszAttrs);
            simulationType = mParser.getAttributeValue("simulationType", papszAttrs, false);

            // We need to handle old files which used the attribute status.
            if (!simulationType)
              {
                simulationType = mParser.getAttributeValue("status", papszAttrs, false);

                if (!simulationType) // status and simulationType are both missing
                  simulationType = mParser.getAttributeValue("simulationType", papszAttrs);
              }

            SimulationType = toEnum(simulationType, CModelEntity::XMLStatus, CModelEntity::FIXED);

            mpMV = new CModelValue();
            addFix(mKey, mpMV);
            mpMV->setObjectName(Name);
            mpMV->setStatus(SimulationType);

            mCommon.pModel->getModelValues().add(mpMV, true);
            mLastKnownElement = mCurrentElement;

            return;

          case MiriamAnnotation:

            if (!strcmp(pszName, "MiriamAnnotation"))
              mpCurrentHandler = &mParser.mMiriamAnnotationElement;

            break;

          case Comment:

            if (!strcmp(pszName, "Comment"))
              mpCurrentHandler = &mParser.mCommentElement;

            break;

          case ListOfUnsupportedAnnotations:

            if (!strcmp(pszName, "ListOfUnsupportedAnnotations"))
              mpCurrentHandler = &mParser.mListOfUnsupportedAnnotationsElement;

            break;

          case Expression:

            if (!strcmp(pszName, "Expression"))
              mpCurrentHandler = &mParser.mCharacterDataElement;

            break;

          case InitialExpression:

            if (!strcmp(pszName, "InitialExpression"))
              mpCurrentHandler = &mParser.mCharacterDataElement;

            break;

          case MathML:                                                   // Old file format support

            if (!strcmp(pszName, "MathML"))
              {
                /* If we do not have a MathML element handler we create one. */
                if (!mpMathMLElement)
                  mpMathMLElement = new MathMLElement(mParser, mCommon);

                mpCurrentHandler = mpMathMLElement;
              }

            break;

          default:
            mCurrentElement = UNKNOWN_ELEMENT;
            mpCurrentHandler = &mParser.mUnknownElement;
            break;
        }
    }

  mParser.pushElementHandler(mpCurrentHandler);

  if (mpCurrentHandler != &mParser.mUnknownElement)
    {
      mLastKnownElement = mCurrentElement;
    }

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::ModelValueElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ModelValue:

        if (strcmp(pszName, "ModelValue"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ModelValue", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mLastKnownElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case MiriamAnnotation:

        if (strcmp(pszName, "MiriamAnnotation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "MiriamAnnotation", mParser.getCurrentLineNumber());

        mpMV->setMiriamAnnotation(mCommon.CharacterData, mpMV->getKey(), mKey);
        mCommon.CharacterData = "";
        break;

      case Comment:

        if (strcmp(pszName, "Comment"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Comment", mParser.getCurrentLineNumber());

        mpMV->setNotes(mCommon.CharacterData);
        mCommon.CharacterData = "";
        break;

      case ListOfUnsupportedAnnotations:

        if (strcmp(pszName, "ListOfUnsupportedAnnotations"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfUnsupportedAnnotations", mParser.getCurrentLineNumber());

        mpMV->getUnsupportedAnnotations() = mParser.mListOfUnsupportedAnnotationsElement.getUnsupportedAnnotations();

        break;

      case Expression:

        if (strcmp(pszName, "Expression"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Expression", mParser.getCurrentLineNumber());

        {
          size_t Size = CCopasiMessage::size();

          mpMV->setExpression(mCommon.CharacterData);

          // Remove error messages created by setExpression as this may fail
          // due to incomplete model specification at this time.

          while (CCopasiMessage::size() > Size)
            CCopasiMessage::getLastMessage();
        }

        break;

      case InitialExpression:

        if (strcmp(pszName, "InitialExpression"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "InitialExpression", mParser.getCurrentLineNumber());

        {
          size_t Size = CCopasiMessage::size();

          mpMV->setInitialExpression(mCommon.CharacterData);

          // Remove error messages created by setExpression as this may fail
          // due to incomplete model specification at this time.
          while (CCopasiMessage::size() > Size)
            CCopasiMessage::getLastMessage();
        }

        break;

      case MathML:                                                   // Old file format support

        if (strcmp(pszName, "MathML"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "MathML", mParser.getCurrentLineNumber());

        {
          size_t Size = CCopasiMessage::size();

          mpMV->setExpression(mCommon.CharacterData);

          // Remove error messages created by setExpression as this may fail
          // due to incomplete model specification at this time.

          while (CCopasiMessage::size() > Size)
            CCopasiMessage::getLastMessage();
        }

        break;

      case UNKNOWN_ELEMENT:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  mCurrentElement = ModelValue;
  return;
}

//****** TODO: Event

CCopasiXMLParser::ListOfEventsElement::ListOfEventsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfEventsElement::~ListOfEventsElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfEventsElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfEvents:

        if (strcmp(pszName, "ListOfEvents"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfEvents", mParser.getCurrentLineNumber());

        mEventOrders.clear();
        break;

      case Event:

        if (strcmp(pszName, "Event"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Event", mParser.getCurrentLineNumber());

        /* If we do not have a function element handler we create one. */
        if (!mpCurrentHandler)
          mpCurrentHandler = new EventElement(mParser, mCommon);

        /* Push the Metabolite element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfEventsElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ListOfEvents:

        if (strcmp(pszName, "ListOfEvents"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfEvents", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case Event:

        if (strcmp(pszName, "Event"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Event", mParser.getCurrentLineNumber());

        mCurrentElement = ListOfEvents;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::EventElement::EventElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mpListOfAssignmentsElementHandler(NULL)
{}

CCopasiXMLParser::EventElement::~EventElement()
{
  pdelete(mpListOfAssignmentsElementHandler);
}

void CCopasiXMLParser::EventElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * Name;
  bool DelayAssignment;
  bool FireAtInitialTime;
  bool PersistentTrigger;

  mpCurrentHandler = NULL;
  mCurrentElement = mLastKnownElement;

  while (mpCurrentHandler == NULL)
    {
      mCurrentElement++; /* We should always be on the next element */

      switch (mCurrentElement)
        {
          case Event:

            if (strcmp(pszName, "Event"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                             pszName, "Event", mParser.getCurrentLineNumber());

            mKey = mParser.getAttributeValue("key", papszAttrs);
            Name = mParser.getAttributeValue("name", papszAttrs);
            DelayAssignment =
              mParser.toBool(mParser.getAttributeValue("delayAssignment", papszAttrs, false));
            FireAtInitialTime =
              mParser.toBool(mParser.getAttributeValue("fireAtInitialTime", papszAttrs, false));

            if (mCommon.pVersion->getVersionDevel() <= 90)
              {
                PersistentTrigger = true;
              }
            else
              {
                mParser.toBool(mParser.getAttributeValue("persistentTrigger", papszAttrs, true));
              }

            mCommon.pEvent = new CEvent();
            addFix(mKey, mCommon.pEvent);
            mCommon.pEvent->setObjectName(Name);
            mCommon.pEvent->setDelayAssignment(DelayAssignment);
            mCommon.pEvent->setFireAtInitialTime(FireAtInitialTime);
            mCommon.pEvent->setPersistentTrigger(PersistentTrigger);

            mCommon.pModel->getEvents().add(mCommon. pEvent, true);

            mLastKnownElement = Event;
            return;

          case MiriamAnnotation:

            if (!strcmp(pszName, "MiriamAnnotation"))
              mpCurrentHandler = &mParser.mMiriamAnnotationElement;

            break;

          case Comment:

            if (!strcmp(pszName, "Comment"))
              mpCurrentHandler = &mParser.mCommentElement;

            break;

          case ListOfUnsupportedAnnotations:

            if (!strcmp(pszName, "ListOfUnsupportedAnnotations"))
              mpCurrentHandler = &mParser.mListOfUnsupportedAnnotationsElement;

            break;

          case TriggerExpression:

            if (!strcmp(pszName, "TriggerExpression"))
              mpCurrentHandler = &mParser.mCharacterDataElement;

            break;

          case DelayExpression:

            if (!strcmp(pszName, "DelayExpression"))
              mpCurrentHandler = &mParser.mCharacterDataElement;

            break;

          case ListOfAssignments:

            if (!strcmp(pszName, "ListOfAssignments"))
              {
                if (!mpListOfAssignmentsElementHandler)
                  {
                    mpListOfAssignmentsElementHandler =
                      new ListOfAssignmentsElement(mParser, mCommon);

                    mCommon.mAssignments.reserve(100);
                    mCommon.mAssignments.resize(0);
                  }

                mpCurrentHandler = mpListOfAssignmentsElementHandler;
              }

            break;

          default:
            mCurrentElement = UNKNOWN_ELEMENT;
            mpCurrentHandler = &mParser.mUnknownElement;
            break;
        }
    }

  mParser.pushElementHandler(mpCurrentHandler);

  if (mpCurrentHandler != &mParser.mUnknownElement)
    {
      mLastKnownElement = mCurrentElement;
    }

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::EventElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Event:

        if (strcmp(pszName, "Event"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Event", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mLastKnownElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case MiriamAnnotation:

        if (strcmp(pszName, "MiriamAnnotation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "MiriamAnnotation", mParser.getCurrentLineNumber());

        mCommon.pEvent->setMiriamAnnotation(mCommon.CharacterData, mCommon.pEvent->getKey(), mKey);
        mCommon.CharacterData = "";
        break;

      case Comment:

        if (strcmp(pszName, "Comment"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Comment", mParser.getCurrentLineNumber());

        mCommon.pEvent->setNotes(mCommon.CharacterData);
        mCommon.CharacterData = "";
        break;

      case ListOfUnsupportedAnnotations:

        if (strcmp(pszName, "ListOfUnsupportedAnnotations"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfUnsupportedAnnotations", mParser.getCurrentLineNumber());

        mCommon.pEvent->getUnsupportedAnnotations() = mParser.mListOfUnsupportedAnnotationsElement.getUnsupportedAnnotations();

        break;

      case TriggerExpression:

        if (strcmp(pszName, "TriggerExpression"))
          {
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "TriggerExpression", mParser.getCurrentLineNumber());
          }

        {
          size_t Size = CCopasiMessage::size();

          mCommon.pEvent->setTriggerExpression(mCommon.CharacterData);

          // Remove error messages created by setExpression as this may fail
          // due to incomplete model specification at this time.
          while (CCopasiMessage::size() > Size)
            {
              CCopasiMessage msg = CCopasiMessage::getLastMessage();
            }
        }

        break;

      case DelayExpression:

        if (strcmp(pszName, "DelayExpression"))
          {
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "DelayExpression", mParser.getCurrentLineNumber());
          }

        {
          size_t Size = CCopasiMessage::size();

          mCommon.pEvent->setDelayExpression(mCommon.CharacterData);

          // Remove error messages created by setExpression as this may fail
          // due to incomplete model specification at this time.
          while (CCopasiMessage::size() > Size)
            {
              CCopasiMessage msg = CCopasiMessage::getLastMessage();
            }
        }

        break;

      case ListOfAssignments:
        break;

      case UNKNOWN_ELEMENT:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  mCurrentElement = Event;
  return;
}

//****** TODO: Assignments

CCopasiXMLParser::ListOfAssignmentsElement::ListOfAssignmentsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfAssignmentsElement::~ListOfAssignmentsElement()
{}

void CCopasiXMLParser::ListOfAssignmentsElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfAssignments:

        if (strcmp(pszName, "ListOfAssignments"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfAssignments", mParser.getCurrentLineNumber());

        break;

      case Assignment:

        if (strcmp(pszName, "Assignment"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Assignment", mParser.getCurrentLineNumber());

        /* If we do not have a function element handler we create one. */
        if (!mpCurrentHandler)
          {
            mpCurrentHandler = new AssignmentElement(mParser, mCommon);
          }

        /* Push the Metabolite element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfAssignmentsElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ListOfAssignments:

        if (strcmp(pszName, "ListOfAssignments"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfAssignments", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case Assignment:

        if (strcmp(pszName, "Assignment"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Assignment", mParser.getCurrentLineNumber());

        mCurrentElement = ListOfAssignments;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::AssignmentElement::AssignmentElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::AssignmentElement::~AssignmentElement()
{}

void CCopasiXMLParser::AssignmentElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mpCurrentHandler = NULL;
  mCurrentElement++; /* We should always be on the next element */

  const CModelEntity* pME = NULL;

  switch (mCurrentElement)
    {
      case Assignment:

        if (strcmp(pszName, "Assignment"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Assignment", mParser.getCurrentLineNumber());

        mCommon.pEventAssignment = NULL;
        mKey = mParser.getAttributeValue("targetKey", papszAttrs);
        pME = dynamic_cast<const CModelEntity *>(mCommon.KeyMap.get(mKey));

        if (pME != NULL &&
            mCommon.pEvent->getAssignments().getIndex(pME->getKey()) == C_INVALID_INDEX)
          {
            mCommon.pEventAssignment = new CEventAssignment(pME->getKey());
            mCommon.pEvent->getAssignments().add(mCommon.pEventAssignment, true);
          }

        return;

      case Expression:

        if (!strcmp(pszName, "Expression"))
          {
            mpCurrentHandler = &mParser.mCharacterDataElement;
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::AssignmentElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Assignment:

        if (strcmp(pszName, "Assignment"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Assignment", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case Expression:

        if (strcmp(pszName, "Expression"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Expression", mParser.getCurrentLineNumber());

        {
          size_t Size = CCopasiMessage::size();

          if (mCommon.pEventAssignment != NULL)
            mCommon.pEventAssignment->setExpression(mCommon.CharacterData);

          CCopasiMessage msg = CCopasiMessage::getLastMessage();

          // Remove error messages created by setExpression as this may fail
          // due to incomplete model specification at this time.
          while (CCopasiMessage::size() > Size)
            {
              msg = CCopasiMessage::getLastMessage();
            }
        }

        mCurrentElement = Assignment;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

//******

CCopasiXMLParser::ListOfReactionsElement::ListOfReactionsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfReactionsElement::~ListOfReactionsElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfReactionsElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfReactions:

        if (strcmp(pszName, "ListOfReactions"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfReactions", mParser.getCurrentLineNumber());

        mCommon.pModel->getReactions().clear();
        break;

      case Reaction:

        if (strcmp(pszName, "Reaction"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Reaction", mParser.getCurrentLineNumber());

        /* If we do not have a Reaction element handler we create one. */
        if (!mpCurrentHandler)
          mpCurrentHandler = new ReactionElement(mParser, mCommon);

        /* Push the Reaction element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfReactionsElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ListOfReactions:

        if (strcmp(pszName, "ListOfReactions"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfReactions", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case Reaction:

        if (strcmp(pszName, "Reaction"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Reaction", mParser.getCurrentLineNumber());

        mCurrentElement = ListOfReactions;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ReactionElement::ReactionElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mpListOfSubstratesElement(NULL),
  mpListOfProductsElement(NULL),
  mpListOfModifiersElement(NULL),
  mpListOfConstantsElement(NULL),
  mpKineticLawElement(NULL)
{}

CCopasiXMLParser::ReactionElement::~ReactionElement()
{
  pdelete(mpListOfSubstratesElement);
  pdelete(mpListOfProductsElement);
  pdelete(mpListOfModifiersElement);
  pdelete(mpListOfConstantsElement);
  pdelete(mpKineticLawElement);
}

void CCopasiXMLParser::ReactionElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  CCompartment * pCompartment;
  const char * Name;
  const char * Compartment; // Default Compartment_00
  const char * reversible;
  bool Reversible;
  const char * fast;
  bool Fast;
  const char * SBMLId;

  mCurrentElement = mLastKnownElement;
  mpCurrentHandler = NULL;

  while (mpCurrentHandler == NULL)
    {
      mCurrentElement++; /* We should always be on the next element */

      switch (mCurrentElement)
        {
          case Reaction:

            if (strcmp(pszName, "Reaction"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                             pszName, "Reaction", mParser.getCurrentLineNumber());

            mKey = mParser.getAttributeValue("key", papszAttrs);
            Name = mParser.getAttributeValue("name", papszAttrs);
            Compartment = mParser.getAttributeValue("compartment", papszAttrs,
                                                    "Compartment_00");

            reversible = mParser.getAttributeValue("reversible", papszAttrs);
            Reversible = mParser.toBool(reversible);

            fast = mParser.getAttributeValue("fast", papszAttrs, "false");
            Fast = mParser.toBool(fast);

            mCommon.pReaction = new CReaction();
            addFix(mKey, mCommon.pReaction);
            mCommon.pReaction->setObjectName(Name);
            mCommon.pReaction->setReversible(Reversible);
            mCommon.pReaction->setFast(Fast);
            SBMLId = mParser.getAttributeValue("sbmlid", papszAttrs, "");

            if (std::string(SBMLId) != std::string(""))
              {
                mCommon.pReaction->setSBMLId(SBMLId);
              }

            if (strcmp(Compartment, "Compartment_00")) //TODO necessary?
              {
                pCompartment =
                  dynamic_cast< CCompartment* >(mCommon.KeyMap.get(Compartment));

                if (!pCompartment) fatalError();

                //mCommon.pReaction->setCompartment(pCompartment);
              }

            mCommon.pModel->getReactions().add(mCommon.pReaction, true);

            mLastKnownElement = Reaction;
            return;
            break;

          case MiriamAnnotation:

            if (!strcmp(pszName, "MiriamAnnotation"))
              mpCurrentHandler = &mParser.mMiriamAnnotationElement;

            break;

          case Comment:

            if (!strcmp(pszName, "Comment"))
              {
                mpCurrentHandler = &mParser.mCommentElement;
                mLastKnownElement = mCurrentElement;
              }

            break;

          case ListOfUnsupportedAnnotations:

            if (!strcmp(pszName, "ListOfUnsupportedAnnotations"))
              mpCurrentHandler = &mParser.mListOfUnsupportedAnnotationsElement;

            break;

          case ListOfSubstrates:

            if (!strcmp(pszName, "ListOfSubstrates"))
              {
                /* If we do not have a function element handler we create one. */
                if (!mpListOfSubstratesElement)
                  mpListOfSubstratesElement =
                    new ListOfSubstratesElement(mParser, mCommon);

                mpCurrentHandler = mpListOfSubstratesElement;
              }

            break;

          case ListOfProducts:

            if (!strcmp(pszName, "ListOfProducts"))
              {
                if (!mpListOfProductsElement)
                  mpListOfProductsElement =
                    new ListOfProductsElement(mParser, mCommon);

                mpCurrentHandler = mpListOfProductsElement;
              }

            break;

          case ListOfModifiers:

            if (!strcmp(pszName, "ListOfModifiers"))
              {
                if (!mpListOfModifiersElement)
                  mpListOfModifiersElement =
                    new ListOfModifiersElement(mParser, mCommon);

                mpCurrentHandler = mpListOfModifiersElement;
              }

            break;

          case ListOfConstants:

            if (!strcmp(pszName, "ListOfConstants"))
              {
                if (!mpListOfConstantsElement)
                  mpListOfConstantsElement =
                    new ListOfConstantsElement(mParser, mCommon);

                mpCurrentHandler = mpListOfConstantsElement;
              }

            break;

          case KineticLaw:

            if (!strcmp(pszName, "KineticLaw"))
              {
                if (!mpKineticLawElement)
                  mpKineticLawElement = new KineticLawElement(mParser, mCommon);

                mpCurrentHandler = mpKineticLawElement;
              }

            break;

          default:
            mCurrentElement = UNKNOWN_ELEMENT;
            mpCurrentHandler = &mParser.mUnknownElement;
            break;
        }
    }

  mParser.pushElementHandler(mpCurrentHandler);

  if (mpCurrentHandler != &mParser.mUnknownElement)
    {
      mLastKnownElement = mCurrentElement;
    }

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::ReactionElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Reaction:

        if (strcmp(pszName, "Reaction"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Reaction", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mLastKnownElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case MiriamAnnotation:

        if (strcmp(pszName, "MiriamAnnotation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "MiriamAnnotation", mParser.getCurrentLineNumber());

        mCommon.pReaction->setMiriamAnnotation(mCommon.CharacterData, mCommon.pReaction->getKey(), mKey);
        mCommon.CharacterData = "";
        break;

      case Comment:

        if (strcmp(pszName, "Comment"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Comment", mParser.getCurrentLineNumber());

        mCommon.pReaction->setNotes(mCommon.CharacterData);
        mCommon.CharacterData = "";
        break;

      case ListOfUnsupportedAnnotations:

        if (strcmp(pszName, "ListOfUnsupportedAnnotations"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfUnsupportedAnnotations", mParser.getCurrentLineNumber());

        mCommon.pReaction->getUnsupportedAnnotations() = mParser.mListOfUnsupportedAnnotationsElement.getUnsupportedAnnotations();

        break;

      case ListOfSubstrates:

        if (strcmp(pszName, "ListOfSubstrates"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfSubstrates", mParser.getCurrentLineNumber());

        break;

      case ListOfProducts:

        if (strcmp(pszName, "ListOfProducts"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfProducts", mParser.getCurrentLineNumber());

        break;

      case ListOfModifiers:

        if (strcmp(pszName, "ListOfModifiers"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfModifiers", mParser.getCurrentLineNumber());

        break;

      case ListOfConstants:

        if (strcmp(pszName, "ListOfConstants"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfConstants", mParser.getCurrentLineNumber());

        break;

      case KineticLaw:

        if (strcmp(pszName, "KineticLaw"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "KineticLaw", mParser.getCurrentLineNumber());

        break;

      case UNKNOWN_ELEMENT:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  mCurrentElement = Reaction;

  return;
}

CCopasiXMLParser::ListOfSubstratesElement::ListOfSubstratesElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfSubstratesElement::~ListOfSubstratesElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfSubstratesElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfSubstrates:

        if (strcmp(pszName, "ListOfSubstrates"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfSubstrates", mParser.getCurrentLineNumber());

        break;

      case Substrate:

        if (strcmp(pszName, "Substrate"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Substrate", mParser.getCurrentLineNumber());

        /* If we do not have a Substrate element handler we create one. */
        if (!mpCurrentHandler)
          mpCurrentHandler = new SubstrateElement(mParser, mCommon);

        /* Push the Substrate element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfSubstratesElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ListOfSubstrates:

        if (strcmp(pszName, "ListOfSubstrates"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfSubstrates", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case Substrate:

        if (strcmp(pszName, "Substrate"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Substrate", mParser.getCurrentLineNumber());

        mCurrentElement = ListOfSubstrates;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::SubstrateElement::SubstrateElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::SubstrateElement::~SubstrateElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::SubstrateElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * Metabolite;
  CMetab * pMetabolite;

  const char * Stoichiometry;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case Substrate:

        if (strcmp(pszName, "Substrate"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Substrate", mParser.getCurrentLineNumber());

        Metabolite = mParser.getAttributeValue("metabolite", papszAttrs);
        Stoichiometry = mParser.getAttributeValue("stoichiometry", papszAttrs);

        pMetabolite = dynamic_cast< CMetab * >(mCommon.KeyMap.get(Metabolite));

        if (!pMetabolite) fatalError();

        mCommon.pReaction->addSubstrate(pMetabolite->getKey(),
                                        CCopasiXMLInterface::DBL(Stoichiometry));
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::SubstrateElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Substrate:

        if (strcmp(pszName, "Substrate"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Substrate", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ListOfProductsElement::ListOfProductsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfProductsElement::~ListOfProductsElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfProductsElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfProducts:

        if (strcmp(pszName, "ListOfProducts"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfProducts", mParser.getCurrentLineNumber());

        break;

      case Product:

        if (strcmp(pszName, "Product"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Product", mParser.getCurrentLineNumber());

        /* If we do not have a Product element handler we create one. */
        if (!mpCurrentHandler)
          mpCurrentHandler = new ProductElement(mParser, mCommon);

        /* Push the Product element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfProductsElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ListOfProducts:

        if (strcmp(pszName, "ListOfProducts"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfProducts", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case Product:

        if (strcmp(pszName, "Product"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Product", mParser.getCurrentLineNumber());

        mCurrentElement = ListOfProducts;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ProductElement::ProductElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ProductElement::~ProductElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ProductElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * Metabolite;
  CMetab * pMetabolite;

  const char * Stoichiometry;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case Product:

        if (strcmp(pszName, "Product"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Product", mParser.getCurrentLineNumber());

        Metabolite = mParser.getAttributeValue("metabolite", papszAttrs);
        Stoichiometry = mParser.getAttributeValue("stoichiometry", papszAttrs);

        pMetabolite = dynamic_cast< CMetab * >(mCommon.KeyMap.get(Metabolite));

        if (!pMetabolite) fatalError();

        mCommon.pReaction->addProduct(pMetabolite->getKey(),
                                      CCopasiXMLInterface::DBL(Stoichiometry));
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ProductElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Product:

        if (strcmp(pszName, "Product"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Product", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ListOfModifiersElement::ListOfModifiersElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfModifiersElement::~ListOfModifiersElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfModifiersElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfModifiers:

        if (strcmp(pszName, "ListOfModifiers"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfModifiers", mParser.getCurrentLineNumber());

        break;

      case Modifier:

        if (strcmp(pszName, "Modifier"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Modifier", mParser.getCurrentLineNumber());

        /* If we do not have a Modifier element handler we create one. */
        if (!mpCurrentHandler)
          mpCurrentHandler = new ModifierElement(mParser, mCommon);

        /* Push the Modifier element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfModifiersElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ListOfModifiers:

        if (strcmp(pszName, "ListOfModifiers"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfModifiers", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case Modifier:

        if (strcmp(pszName, "Modifier"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Modifier", mParser.getCurrentLineNumber());

        mCurrentElement = ListOfModifiers;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ModifierElement::ModifierElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ModifierElement::~ModifierElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ModifierElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * Metabolite;
  CMetab * pMetabolite;

  const char * Stoichiometry;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case Modifier:

        if (strcmp(pszName, "Modifier"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Modifier", mParser.getCurrentLineNumber());

        Metabolite = mParser.getAttributeValue("metabolite", papszAttrs);
        Stoichiometry = mParser.getAttributeValue("stoichiometry", papszAttrs);

        pMetabolite = dynamic_cast< CMetab * >(mCommon.KeyMap.get(Metabolite));

        if (!pMetabolite) fatalError();

        mCommon.pReaction->addModifier(pMetabolite->getKey(),
                                       CCopasiXMLInterface::DBL(Stoichiometry));
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ModifierElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Modifier:

        if (strcmp(pszName, "Modifier"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Modifier", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ListOfConstantsElement::ListOfConstantsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfConstantsElement::~ListOfConstantsElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfConstantsElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfConstants:

        if (strcmp(pszName, "ListOfConstants"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfConstants", mParser.getCurrentLineNumber());

        mCommon.pReaction->getParameters().clear();
        break;

      case Constant:

        if (strcmp(pszName, "Constant"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Constant", mParser.getCurrentLineNumber());

        /* If we do not have a Constant element handler we create one. */
        if (!mpCurrentHandler)
          mpCurrentHandler = new ConstantElement(mParser, mCommon);

        /* Push the Constant element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfConstantsElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ListOfConstants:

        if (strcmp(pszName, "ListOfConstants"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfConstants", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case Constant:

        if (strcmp(pszName, "Constant"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Constant", mParser.getCurrentLineNumber());

        mCurrentElement = ListOfConstants;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ConstantElement::ConstantElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ConstantElement::~ConstantElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ConstantElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * Key;
  const char * Name;
  const char * Value;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case Constant:

        if (strcmp(pszName, "Constant"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Constant", mParser.getCurrentLineNumber());

        Key = mParser.getAttributeValue("key", papszAttrs);
        Name = mParser.getAttributeValue("name", papszAttrs);
        Value = mParser.getAttributeValue("value", papszAttrs);

        mCommon.pReaction->
        getParameters().addParameter(Name,
                                     CCopasiParameter::DOUBLE,
                                     (C_FLOAT64) CCopasiXMLInterface::DBL(Value));

        addFix(Key,
               mCommon.pReaction->getParameters().getParameter(Name));

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ConstantElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Constant:

        if (strcmp(pszName, "Constant"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Constant", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::KineticLawElement::KineticLawElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::KineticLawElement::~KineticLawElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::KineticLawElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * Function;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case KineticLaw:

        if (strcmp(pszName, "KineticLaw"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "KineticLaw", mParser.getCurrentLineNumber());

        Function = mParser.getAttributeValue("function", papszAttrs);

        mCommon.pFunction =
          dynamic_cast< CFunction* >(mCommon.KeyMap.get(Function));

        if (!mCommon.pFunction)
          {
            CCopasiMessage(CCopasiMessage::RAW, MCXML + 7, Function,
                           mCommon.pReaction->getObjectName().c_str(),
                           mParser.getCurrentLineNumber());
            mCommon.pFunction = CCopasiRootContainer::getUndefinedFunction();
          }

        // This must be deferred till the end since we need to check for consistency
        // of the parameters first (Bug 832)
        // mCommon.pReaction->setFunction(pFunction);
        break;

      case ListOfCallParameters:

        if (strcmp(pszName, "ListOfCallParameters"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfCallParameters", mParser.getCurrentLineNumber());

        if (mCommon.pFunction == CCopasiRootContainer::getUndefinedFunction())
          mParser.onStartElement(pszName, papszAttrs);

        /* If we do not have a etc element handler we create one. */
        if (!mpCurrentHandler)
          mpCurrentHandler = new ListOfCallParametersElement(mParser, mCommon);

        /* Push the etc element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::KineticLawElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case KineticLaw:

        if (strcmp(pszName, "KineticLaw"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "KineticLaw", mParser.getCurrentLineNumber());

        mCommon.pReaction->setFunction(dynamic_cast< CFunction * >(mCommon.pFunction));

        {
          std::map< std::string, std::vector< std::string > >::const_iterator it
          = mCommon.SourceParameterKeys.begin();
          std::map< std::string, std::vector< std::string > >::const_iterator end
          = mCommon.SourceParameterKeys.end();

          for (; it != end; ++it)
            if (it->second.size() > 0)
              mCommon.pReaction->setParameterMappingVector(it->first, it->second);
        }
        mCommon.SourceParameterKeys.clear();

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case ListOfCallParameters:

        if (strcmp(pszName, "ListOfCallParameters"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfCallParameters", mParser.getCurrentLineNumber());

        mCurrentElement = KineticLaw;
        break;

      case UNKNOWN_ELEMENT:

        if (mCommon.pReaction->getFunction() == CCopasiRootContainer::getUndefinedFunction())
          mCurrentElement = KineticLaw;
        else
          mCurrentElement = mLastKnownElement;

        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ListOfCallParametersElement::ListOfCallParametersElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfCallParametersElement::~ListOfCallParametersElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfCallParametersElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfCallParameters:

        if (strcmp(pszName, "ListOfCallParameters"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfCallParameters", mParser.getCurrentLineNumber());

        break;

      case CallParameter:

        if (strcmp(pszName, "CallParameter"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "CallParameter", mParser.getCurrentLineNumber());

        /* If we do not have a CallParameter element handler we create one. */
        if (!mpCurrentHandler)
          mpCurrentHandler = new CallParameterElement(mParser, mCommon);

        /* Push the CallParameter element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfCallParametersElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ListOfCallParameters:

        if (strcmp(pszName, "ListOfCallParameters"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfCallParameters", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case CallParameter:

        if (strcmp(pszName, "CallParameter"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "CallParameter", mParser.getCurrentLineNumber());

        mCurrentElement = ListOfCallParameters;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::CallParameterElement::CallParameterElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::CallParameterElement::~CallParameterElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::CallParameterElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * FunctionParameter;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case CallParameter:

        if (strcmp(pszName, "CallParameter"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "CallParameter", mParser.getCurrentLineNumber());

        FunctionParameter =
          mParser.getAttributeValue("functionParameter", papszAttrs);

        mCommon.pFunctionVariable =
          dynamic_cast< CFunctionParameter* >(mCommon.KeyMap.get(FunctionParameter));

        if (!mCommon.pFunctionVariable)
          {
            fatalError();
          }

        break;

      case SourceParameter:

        if (strcmp(pszName, "SourceParameter"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "SourceParameter", mParser.getCurrentLineNumber());

        /* If we do not have a SourceParameter element handler we create one. */
        if (!mpCurrentHandler)
          mpCurrentHandler = new SourceParameterElement(mParser, mCommon);

        /* Push the SourceParameter element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::CallParameterElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case CallParameter:

        if (strcmp(pszName, "CallParameter"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "CallParameter", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case SourceParameter:

        if (strcmp(pszName, "SourceParameter"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "SourceParameter", mParser.getCurrentLineNumber());

        mCurrentElement = CallParameter;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::SourceParameterElement::SourceParameterElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::SourceParameterElement::~SourceParameterElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::SourceParameterElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  const char * Reference;
  CCopasiObject * pObject;
  CCopasiParameter * pParameter;
  CModelEntity * pME;

  switch (mCurrentElement)
    {
      case SourceParameter:

        if (strcmp(pszName, "SourceParameter"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "SourceParameter", mParser.getCurrentLineNumber());

        Reference =
          mParser.getAttributeValue("reference", papszAttrs);

        pObject = mCommon.KeyMap.get(Reference);

        if ((pParameter = dynamic_cast< CCopasiParameter * >(pObject)))
          {
            // We need to assure that the parameter name for variables which are not
            // of type vector match.
            if (mCommon.pFunctionVariable->getType() < CFunctionParameter::VINT32)
              pParameter->setObjectName(mCommon.pFunctionVariable->getObjectName());

            mCommon.SourceParameterKeys[mCommon.pFunctionVariable->getObjectName()].push_back(pParameter->getKey());
          }
        else if ((pME = dynamic_cast<CModelEntity*>(pObject)))
          mCommon.SourceParameterKeys[mCommon.pFunctionVariable->getObjectName()].push_back(pME->getKey());
        else
          mCommon.SourceParameterKeys[mCommon.pFunctionVariable->getObjectName()].push_back(CFunctionParameterMap::pUnmappedObject->getKey());

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::SourceParameterElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case SourceParameter:

        if (strcmp(pszName, "SourceParameter"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "SourceParameter", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::StateTemplateElement::StateTemplateElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::StateTemplateElement::~StateTemplateElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::StateTemplateElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case StateTemplate:

        if (strcmp(pszName, "StateTemplate"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "StateTemplate", mParser.getCurrentLineNumber());

        mCommon.StateVariableList.clear();
        break;

      case StateTemplateVariable:

        if (strcmp(pszName, "StateTemplateVariable"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "StateTemplateVariable", mParser.getCurrentLineNumber());

        /* If we do not have a StateTemplateVariable element handler we create one. */
        if (!mpCurrentHandler)
          mpCurrentHandler = new StateTemplateVariableElement(mParser, mCommon);

        /* Push the StateTemplateVariable element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::StateTemplateElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case StateTemplate:

        if (strcmp(pszName, "StateTemplate"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "StateTemplate", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case StateTemplateVariable:

        if (strcmp(pszName, "StateTemplateVariable"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "StateTemplateVariable", mParser.getCurrentLineNumber());

        mCurrentElement = StateTemplate;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::StateTemplateVariableElement::StateTemplateVariableElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::StateTemplateVariableElement::~StateTemplateVariableElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::StateTemplateVariableElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * ObjectReference;
  CModelEntity * pME;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case StateTemplateVariable:

        if (strcmp(pszName, "StateTemplateVariable"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "StateTemplateVariable", mParser.getCurrentLineNumber());

        ObjectReference = mParser.getAttributeValue("objectReference",
                          papszAttrs);
        pME = dynamic_cast< CModelEntity * >(mCommon.KeyMap.get(ObjectReference));

        if (pME != NULL)
          mCommon.StateVariableList.push_back(pME);
        else
          fatalError();

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::StateTemplateVariableElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case StateTemplateVariable:

        if (strcmp(pszName, "StateTemplateVariable"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "StateTemplateVariable", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::InitialStateElement::InitialStateElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::InitialStateElement::~InitialStateElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::InitialStateElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * Type;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case InitialState:

        if (strcmp(pszName, "InitialState"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "InitialState", mParser.getCurrentLineNumber());

        Type = mParser.getAttributeValue("type", papszAttrs, "initialState");

        if (strcmp(Type, "initialState")) fatalError();

        mParser.enableCharacterDataHandler();
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::InitialStateElement::end(const XML_Char *pszName)
{
  std::istringstream Values;
  std::string StringValue;
  std::vector< CModelEntity * >::iterator it;
  std::vector< CModelEntity * >::iterator end;
  double Value;

  const CStateTemplate & Template = mCommon.pModel->getStateTemplate();
  CState IState = mCommon.pModel->getInitialState();
  C_FLOAT64 * pValues = IState.beginIndependent() - 1;
  size_t Index;

  switch (mCurrentElement)
    {
      case InitialState:

        if (strcmp(pszName, "InitialState"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "InitialState", mParser.getCurrentLineNumber());

        Values.str(mParser.getCharacterData("\x0a\x0d\t ", " "));

        it = mCommon.StateVariableList.begin();
        end = mCommon.StateVariableList.end();

        for (Values >> StringValue; it != end; ++it, Values >> StringValue)
          {
            if (Values.fail()) break;

            Value = CCopasiXMLInterface::DBL(StringValue.c_str());

            Index = Template.getIndex(*it);

            if (Index != C_INVALID_INDEX)
              {
                pValues[Index] = Value;
                continue;
              }

            fatalError();
          }

        if (it != end || !Values.fail() || !Values.eof())
          {
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 17, mParser.getCurrentLineNumber());
          }

        mCommon.pModel->setInitialState(IState);

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ListOfPlotItemsElement::ListOfPlotItemsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfPlotItemsElement::~ListOfPlotItemsElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfPlotItemsElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfPlotItems:

        if (strcmp(pszName, "ListOfPlotItems"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfPlotItems", mParser.getCurrentLineNumber());

        break;

      case PlotItem:

        if (strcmp(pszName, "PlotItem"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "PlotItem", mParser.getCurrentLineNumber());

        // If we do not have a plot specification element handler, we create one
        if (!mpCurrentHandler)
          {
            mpCurrentHandler = new PlotItemElement(mParser, mCommon);
          }

        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfPlotItemsElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ListOfPlotItems:

        if (strcmp(pszName, "ListOfPlotItems"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfPlotItems", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;
        mParser.onEndElement(pszName);
        break;

      case PlotItem:

        if (strcmp(pszName, "PlotItem"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "PlotItem", mParser.getCurrentLineNumber());

        mCommon.pCurrentPlotItem = mCommon.pCurrentPlot;
        mCurrentElement = ListOfPlotItems;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ListOfChannelsElement::ListOfChannelsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfChannelsElement::~ListOfChannelsElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfChannelsElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfChannels:

        if (strcmp(pszName, "ListOfChannels"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfChannels", mParser.getCurrentLineNumber());

        break;

      case ChannelSpec:

        if (strcmp(pszName, "ChannelSpec"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ChannelSpec", mParser.getCurrentLineNumber());

        if (!mpCurrentHandler)
          {
            mpCurrentHandler = new ChannelSpecElement(mParser, mCommon);
          }

        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfChannelsElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ListOfChannels:

        if (strcmp(pszName, "ListOfChannels"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfChannels", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;
        mParser.onEndElement(pszName);
        break;

      case ChannelSpec:

        if (strcmp(pszName, "ChannelSpec"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ChannelSpec", mParser.getCurrentLineNumber());

        mCommon.pCurrentPlotItem->getChannels().push_back(*(mCommon.pCurrentChannelSpec));

        delete mCommon.pCurrentChannelSpec;
        mCommon.pCurrentChannelSpec = NULL;
        mCurrentElement = ListOfChannels;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ListOfPlotsElement::ListOfPlotsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfPlotsElement::~ListOfPlotsElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfPlotsElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfPlots:

        if (strcmp(pszName, "ListOfPlots"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfPlots", mParser.getCurrentLineNumber());

        if (!mCommon.pPlotList)
          {
            mCommon.pPlotList = new COutputDefinitionVector;
          }

        break;

      case PlotSpecification:

        if (strcmp(pszName, "PlotSpecification"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "PlotSpecification", mParser.getCurrentLineNumber());

        // If we do not have a plot specification element handler, we create one
        if (!mpCurrentHandler)
          {
            mpCurrentHandler = new PlotSpecificationElement(mParser, mCommon);
          }

        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfPlotsElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ListOfPlots:

        if (strcmp(pszName, "ListOfPlots"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfPlots", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;
        mParser.onEndElement(pszName);
        break;

      case PlotSpecification:

        if (strcmp(pszName, "PlotSpecification"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "PlotSpecification", mParser.getCurrentLineNumber());

        // add mCommon.pCurrentPlot to the listOfPlots and set
        // mCommon.pCurrentPlot to NULL
        mCommon.pPlotList->add(*mCommon.pCurrentPlot);
        delete mCommon.pCurrentPlot;
        mCommon.pCurrentPlot = NULL;
        mCommon.pCurrentPlotItem = NULL;
        mCurrentElement = ListOfPlots;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ChannelSpecElement::ChannelSpecElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common): CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ChannelSpecElement::~ChannelSpecElement()
{}

void CCopasiXMLParser::ChannelSpecElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  mpCurrentHandler = NULL;
  std::string name;
  double min;
  double max;
  const char* sMin;
  const char* sMax;

  switch (mCurrentElement)
    {
      case ChannelSpec:

        if (strcmp(pszName, "ChannelSpec"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ChannelSpec", mParser.getCurrentLineNumber());

        // create a new CPlotSpecification element depending on the type
        name = mParser.getAttributeValue("cn", papszAttrs);

        mCommon.pCurrentChannelSpec = new CPlotDataChannelSpec(name);
        sMin = mParser.getAttributeValue("min", papszAttrs, false);

        if (sMin == NULL)
          {
            mCommon.pCurrentChannelSpec->minAutoscale = true;
          }
        else
          {
            min = CCopasiXMLInterface::DBL(sMin);
            mCommon.pCurrentChannelSpec->min = min;
          }

        sMax = mParser.getAttributeValue("max", papszAttrs, false);

        if (sMax == NULL)
          {
            mCommon.pCurrentChannelSpec->maxAutoscale = true;
          }
        else
          {
            max = CCopasiXMLInterface::DBL(sMax);
            mCommon.pCurrentChannelSpec->max = max;
          }

        return;
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::ChannelSpecElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ChannelSpec:

        if (strcmp(pszName, "ChannelSpec"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ChannelSpec", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::PlotItemElement::PlotItemElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mpParameterElement(NULL),
  mpParameterGroupElement(NULL),
  mpListOfChannelsElement(NULL),
  mLineNumber(0)

{}

CCopasiXMLParser::PlotItemElement::~PlotItemElement()
{
  pdelete(mpParameterElement);
  pdelete(mpParameterGroupElement);
  pdelete(mpListOfChannelsElement);
}

void CCopasiXMLParser::PlotItemElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  mpCurrentHandler = NULL;
  std::string name;
  std::string sType;

  mLineNumber = (size_t) - 1;

  switch (mCurrentElement)
    {
      case PlotItem:

        if (strcmp(pszName, "PlotItem"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "PlotItem", mParser.getCurrentLineNumber());

        // create a new CPlotSpecification element depending on the type
        name = mParser.getAttributeValue("name", papszAttrs);
        sType = mParser.getAttributeValue("type", papszAttrs);
        mCommon.pCurrentPlotItem =
          mCommon.pCurrentPlot->createItem(name, toEnum(sType.c_str(), CPlotItem::XMLType, CPlotItem::unset));

        return;
        break;

      case Parameter:

        if (!strcmp(pszName, "Parameter"))
          {
            mLineNumber = mParser.getCurrentLineNumber();

            if (!mpParameterElement)
              {
                mpParameterElement = new ParameterElement(mParser, mCommon);
              }

            mpCurrentHandler = mpParameterElement;
          }

        break;

      case ParameterGroup:

        if (!strcmp(pszName, "ParameterGroup"))
          {
            mLineNumber = mParser.getCurrentLineNumber();

            if (!mpParameterGroupElement)
              {
                mpParameterGroupElement = new ParameterGroupElement(mParser, mCommon);
              }

            mpCurrentHandler = mpParameterGroupElement;
          }

        break;

      case ListOfChannels:

        if (!strcmp(pszName, "ListOfChannels"))
          {
            mLineNumber = mParser.getCurrentLineNumber();

            if (!mpListOfChannelsElement)
              {
                mpListOfChannelsElement = new ListOfChannelsElement(mParser, mCommon);
              }

            mpCurrentHandler = mpListOfChannelsElement;
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::PlotItemElement::end(const XML_Char *pszName)
{
  CCopasiParameter * p = NULL;

  switch (mCurrentElement)
    {
      case PlotItem:

        if (strcmp(pszName, "PlotItem"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "PlotItem", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;
        mParser.onEndElement(pszName);
        break;

      case Parameter:

        if (!strcmp(pszName, "Parameter"))
          {
            p = mCommon.pCurrentPlotItem->getParameter(mCommon.pCurrentParameter->getObjectName());
            //TODO warning if type mismatch. Is silently ignored currently.

            if (p && p->getType() == mCommon.pCurrentParameter->getType())
              {
                switch (p->getType())
                  {
                    case CCopasiParameter::INT:
                      p->setValue(* mCommon.pCurrentParameter->getValue().pINT);
                      break;

                    case CCopasiParameter::UINT:
                      p->setValue(* mCommon.pCurrentParameter->getValue().pUINT);
                      break;

                    case CCopasiParameter::DOUBLE:
                      p->setValue(* mCommon.pCurrentParameter->getValue().pDOUBLE);
                      break;

                    case CCopasiParameter::UDOUBLE:
                      p->setValue(* mCommon.pCurrentParameter->getValue().pUDOUBLE);
                      break;

                    case CCopasiParameter::BOOL:
                      p->setValue(* mCommon.pCurrentParameter->getValue().pBOOL);
                      break;

                    case CCopasiParameter::STRING:
                      p->setValue(* mCommon.pCurrentParameter->getValue().pSTRING);
                      break;

                    case CCopasiParameter::KEY:
                    {
                      CCopasiObject * pObject =
                        mCommon.KeyMap.get(* mCommon.pCurrentParameter->getValue().pKEY);

                      if (pObject)
                        p->setValue(pObject->getKey());
                      else
                        {
                          p->setValue(*mCommon.pCurrentParameter->getValue().pKEY);
                          mCommon.UnmappedKeyParameters.push_back(p->getKey());
                        }
                    }
                    break;

                    case CCopasiParameter::FILE:
                      p->setValue(* mCommon.pCurrentParameter->getValue().pFILE);
                      break;

                    case CCopasiParameter::CN:
                      p->setValue(* mCommon.pCurrentParameter->getValue().pCN);
                      break;

                    case CCopasiParameter::EXPRESSION:
                    case CCopasiParameter::GROUP:
                    case CCopasiParameter::INVALID:
                      break;

                    default:
                      fatalError();
                      break;
                  }
              }
            else
              {
                CCopasiMessage(CCopasiMessage::RAW, MCXML + 4,
                               mCommon.pCurrentParameter->getObjectName().c_str(),
                               mLineNumber);
              }

            pdelete(mCommon.pCurrentParameter);
            mCurrentElement = PlotItem;
          }

        break;

      case ParameterGroup:

        if (!strcmp(pszName, "ParameterGroup"))
          {
            mCurrentElement = PlotItem;
          }

        break;

      case ListOfChannels:

        if (!strcmp(pszName, "ListOfChannels"))
          {
            mCurrentElement = PlotItem;
          }

        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::PlotSpecificationElement::PlotSpecificationElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mLineNumber(0)
{}

CCopasiXMLParser::PlotSpecificationElement::~PlotSpecificationElement()
{}

void CCopasiXMLParser::PlotSpecificationElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  mpCurrentHandler = NULL;
  mLineNumber = (size_t) - 1;

  const char * name;
  const char * sType;
  const char * active;

  switch (mCurrentElement)
    {
      case PlotSpecification:

        if (strcmp(pszName, "PlotSpecification"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "PlotSpecification", mParser.getCurrentLineNumber());

        // create a new CPlotSpecification element depending on the type
        mCommon.pCurrentPlot = new CPlotSpecification();
        mCommon.pCurrentPlotItem = mCommon.pCurrentPlot;
        name = mParser.getAttributeValue("name", papszAttrs);
        mCommon.pCurrentPlot->setObjectName(name);
        sType = mParser.getAttributeValue("type", papszAttrs);
        mCommon.pCurrentPlot->setType(toEnum(sType, CPlotItem::XMLType, CPlotItem::curve2d));
        active = mParser.getAttributeValue("active", papszAttrs, "true");

        mCommon.pCurrentPlot->setActive(mParser.toBool(active));
        return;
        break;

      case Parameter:

        if (!strcmp(pszName, "Parameter"))
          {
            mLineNumber = mParser.getCurrentLineNumber();

            if (!mpCurrentHandler)
              {
                mpCurrentHandler = new ParameterElement(mParser, mCommon);
              }
          }

        break;

      case ParameterGroup:

        if (!strcmp(pszName, "ParameterGroup"))
          {
            mLineNumber = mParser.getCurrentLineNumber();

            if (!mpCurrentHandler)
              {
                mpCurrentHandler = new ParameterGroupElement(mParser, mCommon);
              }
          }

        break;

      case ListOfChannels:

        if (!strcmp(pszName, "ListOfChannels"))
          {
            if (!mpCurrentHandler)
              {
                mpCurrentHandler = new ListOfChannelsElement(mParser, mCommon);
              }
          }

        break;

      case ListOfPlotItems:

        if (!strcmp(pszName, "ListOfPlotItems"))
          {
            if (!mpCurrentHandler)
              {
                mpCurrentHandler = new ListOfPlotItemsElement(mParser, mCommon);
              }
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::PlotSpecificationElement::end(const XML_Char *pszName)
{
  CCopasiParameter* p;

  switch (mCurrentElement)
    {
      case PlotSpecification:

        if (!strcmp(pszName, "PlotSpecification"))
          {
            mParser.popElementHandler();
            mCurrentElement = START_ELEMENT;
            mParser.onEndElement(pszName);
          }

        break;

      case Parameter:

        if (!strcmp(pszName, "Parameter"))
          {
            p = mCommon.pCurrentPlot->getParameter(mCommon.pCurrentParameter->getObjectName());

            if (p)
              {
                switch (p->getType())
                  {
                    case CCopasiParameter::INT:
                      p->setValue(* mCommon.pCurrentParameter->getValue().pINT);
                      break;

                    case CCopasiParameter::UINT:
                      p->setValue(* mCommon.pCurrentParameter->getValue().pUINT);
                      break;

                    case CCopasiParameter::DOUBLE:
                      p->setValue(* mCommon.pCurrentParameter->getValue().pDOUBLE);
                      break;

                    case CCopasiParameter::UDOUBLE:
                      p->setValue(* mCommon.pCurrentParameter->getValue().pUDOUBLE);
                      break;

                    case CCopasiParameter::BOOL:
                      p->setValue(* mCommon.pCurrentParameter->getValue().pBOOL);
                      break;

                    case CCopasiParameter::STRING:
                      p->setValue(* mCommon.pCurrentParameter->getValue().pSTRING);
                      break;

                    case CCopasiParameter::KEY:
                    {
                      CCopasiObject * pObject =
                        mCommon.KeyMap.get(* mCommon.pCurrentParameter->getValue().pKEY);

                      if (pObject)
                        p->setValue(pObject->getKey());
                      else
                        {
                          p->setValue(*mCommon.pCurrentParameter->getValue().pKEY);
                          mCommon.UnmappedKeyParameters.push_back(p->getKey());
                        }
                    }
                    break;

                    case CCopasiParameter::FILE:
                      p->setValue(* mCommon.pCurrentParameter->getValue().pFILE);
                      break;

                    case CCopasiParameter::CN:
                      p->setValue(* mCommon.pCurrentParameter->getValue().pCN);
                      break;

                    case CCopasiParameter::EXPRESSION:
                    case CCopasiParameter::GROUP:
                    case CCopasiParameter::INVALID:
                      break;

                    default:
                      fatalError();
                      break;
                  }
              }
            else
              {
                CCopasiMessage(CCopasiMessage::RAW, MCXML + 4,
                               mCommon.pCurrentParameter->getObjectName().c_str(),
                               mLineNumber);
              }

            pdelete(mCommon.pCurrentParameter);
            mCurrentElement = PlotSpecification;
          }

        break;

      case ParameterGroup:

        if (strcmp(pszName, "ParameterGroup"))
          {
            p = mCommon.pCurrentPlot->getParameter(mCommon.pCurrentParameter->getObjectName());

            if (p)
              {
                switch (p->getType())
                  {
                    case CCopasiParameter::GROUP:
                      *(CCopasiParameterGroup *) p =
                        * (CCopasiParameterGroup *) mCommon.pCurrentParameter;
                      break;

                    case CCopasiParameter::INT:
                    case CCopasiParameter::UINT:
                    case CCopasiParameter::DOUBLE:
                    case CCopasiParameter::UDOUBLE:
                    case CCopasiParameter::BOOL:
                    case CCopasiParameter::STRING:
                    case CCopasiParameter::CN:
                    case CCopasiParameter::KEY:
                    case CCopasiParameter::FILE:
                    case CCopasiParameter::EXPRESSION:
                    case CCopasiParameter::INVALID:
                      break;

                    default:
                      fatalError();
                      break;
                  }
              }
            else
              {
                CCopasiMessage(CCopasiMessage::RAW, MCXML + 4,
                               mCommon.pCurrentParameter->getObjectName().c_str(),
                               mLineNumber);
              }

            pdelete(mCommon.pCurrentParameter);
            mCurrentElement = PlotSpecification;
          }

        break;

      case ListOfChannels:

        if (!strcmp(pszName, "ListOfChannels"))
          {
            mCurrentElement = PlotSpecification;
          }

        break;

      case ListOfPlotItems:

        if (!strcmp(pszName, "ListOfPlotItems"))
          {
            mCurrentElement = PlotSpecification;
          }

        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  deleteCurrentHandler();
  return;
}

//******** Curve **********

CCopasiXMLParser::CurveElement::CurveElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mLineNumber(0)
{}

CCopasiXMLParser::CurveElement::~CurveElement()
{}

void CCopasiXMLParser::CurveElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  //  mpCurrentHandler = NULL;
  mLineNumber = (size_t) - 1;

  switch (mCurrentElement)
    {
      case Curve:

        if (strcmp(pszName, "Curve"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Curve", mParser.getCurrentLineNumber());

        if (!mCommon.pCurve) fatalError(); //pCurve must point to a curve of a reaction glyph

        //or a metab reference glyph
        mCommon.pCurve->clear();
        {
          //workload

          /*        mCommon.pReactionGlyph = new CLReactionGlyph(name);

                  CReaction * pReaction = dynamic_cast< CReaction * >(mCommon.KeyMap.get(reaction));
                  if (!pReaction) fatalError();
                  mCommon.pReactionGlyph->setModelObjectKey(pReaction->getKey());

                  mCommon.pCurrentLayout->addReactionGlyph(mCommon.pReactionGlyph);
                  addFix(key, mCommon.pReactionGlyph);*/
        }
        return;
        break;

      case ListOfCurveSegments:

        if (!strcmp(pszName, "ListOfCurveSegments"))
          return;

        break;

      case CurveSegment:

        if (!strcmp(pszName, "CurveSegment"))
          {
            //workload
            const char * type;
            type = mParser.getAttributeValue("xsi:type", papszAttrs);

            if (!mCommon.pLineSegment)
              mCommon.pLineSegment = new CLLineSegment;

            mCommon.pLineSegment->setIsBezier(!strcmp(type, "CubicBezier"));
          }

        return;
        break;

      case Start:

        if (!strcmp(pszName, "Start"))
          {
            //workload
            const char * attr;
            attr = mParser.getAttributeValue("x", papszAttrs);
            C_FLOAT64 dX = CCopasiXMLInterface::DBL(attr);
            attr = mParser.getAttributeValue("y", papszAttrs);
            C_FLOAT64 dY = CCopasiXMLInterface::DBL(attr);
            mCommon.pLineSegment->setStart(CLPoint(dX, dY));
            return;
          }

        return;
        break;

      case End:

        if (!strcmp(pszName, "End"))
          {
            //workload
            const char * attr;
            attr = mParser.getAttributeValue("x", papszAttrs);
            C_FLOAT64 dX = CCopasiXMLInterface::DBL(attr);
            attr = mParser.getAttributeValue("y", papszAttrs);
            C_FLOAT64 dY = CCopasiXMLInterface::DBL(attr);
            mCommon.pLineSegment->setEnd(CLPoint(dX, dY));
            return;
          }

        return;
        break;

      case BasePoint1:

        if (!strcmp(pszName, "BasePoint1"))
          {
            //workload
            const char * attr;
            attr = mParser.getAttributeValue("x", papszAttrs);
            C_FLOAT64 dX = CCopasiXMLInterface::DBL(attr);
            attr = mParser.getAttributeValue("y", papszAttrs);
            C_FLOAT64 dY = CCopasiXMLInterface::DBL(attr);
            mCommon.pLineSegment->setBase1(CLPoint(dX, dY));
            return;
          }

        return;
        break;

      case BasePoint2:

        if (!strcmp(pszName, "BasePoint2"))
          {
            //workload
            const char * attr;
            attr = mParser.getAttributeValue("x", papszAttrs);
            C_FLOAT64 dX = CCopasiXMLInterface::DBL(attr);
            attr = mParser.getAttributeValue("y", papszAttrs);
            C_FLOAT64 dY = CCopasiXMLInterface::DBL(attr);
            mCommon.pLineSegment->setBase2(CLPoint(dX, dY));
            return;
          }

        return;
        break;

      default:
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  //   if (mpCurrentHandler)
  //     mParser.pushElementHandler(mpCurrentHandler);
  //
  //   mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::CurveElement::end(const XML_Char *pszName)
{
  if (!strcmp(pszName, "Curve"))
    {
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
    }
  else
    {
      switch (mCurrentElement)
        {
          case ListOfCurveSegments:
            break;

          case CurveSegment:
            mCommon.pCurve->addCurveSegment(mCommon.pLineSegment);
            //tell the handler where to continue
            mCurrentElement = ListOfCurveSegments;
            break;

          case Start:
            break;

          case End:

            //tell the handler where to continue, depending on the type of the curve segment
            if (mCommon.pLineSegment && !mCommon.pLineSegment->isBezier())
              mCurrentElement = CurveSegment;

            break;

          case BasePoint1:
            break;

          case BasePoint2:
            mCurrentElement = CurveSegment;
            break;

          default:
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "???", mParser.getCurrentLineNumber());
            break;
        }
    }

  return;
}

//******** CompartmentGlyph **********

CCopasiXMLParser::CompartmentGlyphElement::CompartmentGlyphElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mLineNumber(0)
{}

CCopasiXMLParser::CompartmentGlyphElement::~CompartmentGlyphElement()
{}

void CCopasiXMLParser::CompartmentGlyphElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  mpCurrentHandler = NULL;
  mLineNumber = (size_t) - 1;

  switch (mCurrentElement)
    {
      case CompartmentGlyph:

        if (strcmp(pszName, "CompartmentGlyph"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "CompartmentGlyph", mParser.getCurrentLineNumber());

        {
          //workload
          const char * key;
          const char * name;
          const char * compartment;
          key = mParser.getAttributeValue("key", papszAttrs);
          name = mParser.getAttributeValue("name", papszAttrs);
          compartment = mParser.getAttributeValue("compartment", papszAttrs);

          mCommon.pCompartmentGlyph = new CLCompartmentGlyph(name);
          const char * objectRole = mParser.getAttributeValue("objectRole", papszAttrs, false);

          if (objectRole != NULL && objectRole[0] != 0)
            {
              mCommon.pCompartmentGlyph->setObjectRole(objectRole);
            }

          if (compartment && compartment[0])
            {
              CCompartment * pComp = dynamic_cast< CCompartment * >(mCommon.KeyMap.get(compartment));

              if (!pComp)
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCXML + 19 , "CompartmentGlyph", key);
                }
              else
                {
                  mCommon.pCompartmentGlyph->setModelObjectKey(pComp->getKey());
                }
            }

          mCommon.pCurrentLayout->addCompartmentGlyph(mCommon.pCompartmentGlyph);
          addFix(key, mCommon.pCompartmentGlyph);
        }
        return;
        break;

      case BoundingBox:

        if (!strcmp(pszName, "BoundingBox"))
          return;

        break;

      case Position:

        if (!strcmp(pszName, "Position"))
          {
            //workload
            const char * attr;
            attr = mParser.getAttributeValue("x", papszAttrs);
            mCommon.pCompartmentGlyph->setX(CCopasiXMLInterface::DBL(attr));
            attr = mParser.getAttributeValue("y", papszAttrs);
            mCommon.pCompartmentGlyph->setY(CCopasiXMLInterface::DBL(attr));
            return;
          }

        break;

      case Dimensions:

        if (!strcmp(pszName, "Dimensions"))
          {
            //workload
            const char * attr;
            attr = mParser.getAttributeValue("width", papszAttrs);
            mCommon.pCompartmentGlyph->setWidth(CCopasiXMLInterface::DBL(attr));
            attr = mParser.getAttributeValue("height", papszAttrs);
            mCommon.pCompartmentGlyph->setHeight(CCopasiXMLInterface::DBL(attr));
            return;
          }

        break;

      default:
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::CompartmentGlyphElement::end(const XML_Char *pszName)
{
  if (!strcmp(pszName, "CompartmentGlyph"))
    {
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
    }
  else
    {
      switch (mCurrentElement)
        {
          case BoundingBox:
            break;

          case Position:
            break;

          case Dimensions:
            //tell the handler where to continue
            mCurrentElement = BoundingBox;
            break;

          case UNKNOWN_ELEMENT:
            mCurrentElement = CompartmentGlyph;
            break;

          default:
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "???", mParser.getCurrentLineNumber());
            break;
        }
    }

  return;
}

//******* ListOfCompartmentGlyphs ********

CCopasiXMLParser::ListOfCompartmentGlyphsElement::ListOfCompartmentGlyphsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfCompartmentGlyphsElement::~ListOfCompartmentGlyphsElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfCompartmentGlyphsElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfCompartmentGlyphs:

        if (strcmp(pszName, "ListOfCompartmentGlyphs"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfCompartmentGlyphs", mParser.getCurrentLineNumber());

        break;

      case CompartmentGlyph:

        //only one type of tags may occur here, so we can throw an exception.
        //No need to silently ignore unknown tags here.
        if (!strcmp(pszName, "CompartmentGlyph"))
          {
            //only one type of tags may occur here, so if the handler exists
            //it must be the correct one
            if (!mpCurrentHandler)
              mpCurrentHandler = new CompartmentGlyphElement(mParser, mCommon);

            mParser.pushElementHandler(mpCurrentHandler);
            mpCurrentHandler->start(pszName, papszAttrs);
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfCompartmentGlyphsElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ListOfCompartmentGlyphs:

        if (strcmp(pszName, "ListOfCompartmentGlyphs"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfCompartmentGlyphs", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case CompartmentGlyph:

        if (strcmp(pszName, "CompartmentGlyph"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "CompartmentGlyph", mParser.getCurrentLineNumber());

        //tell the handler where to continue
        mCurrentElement = ListOfCompartmentGlyphs;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

//******** MetaboliteGlyph **********

CCopasiXMLParser::MetaboliteGlyphElement::MetaboliteGlyphElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mLineNumber(0)
{}

CCopasiXMLParser::MetaboliteGlyphElement::~MetaboliteGlyphElement()
{}

void CCopasiXMLParser::MetaboliteGlyphElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  mpCurrentHandler = NULL;
  mLineNumber = (size_t) - 1;

  switch (mCurrentElement)
    {
      case MetaboliteGlyph:

        if (strcmp(pszName, "MetaboliteGlyph"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "MetaboliteGlyph", mParser.getCurrentLineNumber());

        {
          //workload
          const char * key;
          const char * name;
          const char * metabolite;
          key = mParser.getAttributeValue("key", papszAttrs);
          name = mParser.getAttributeValue("name", papszAttrs);
          metabolite = mParser.getAttributeValue("metabolite", papszAttrs, false);

          mCommon.pMetaboliteGlyph = new CLMetabGlyph(name);
          const char * objectRole = mParser.getAttributeValue("objectRole", papszAttrs, false);

          if (objectRole != NULL && objectRole[0] != 0)
            {
              mCommon.pMetaboliteGlyph->setObjectRole(objectRole);
            }

          if (metabolite && metabolite[0])
            {
              CMetab * pMetab = dynamic_cast< CMetab * >(mCommon.KeyMap.get(metabolite));

              if (!pMetab)
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCXML + 19, "MetaboliteGlyph", key);
                }
              else
                {
                  mCommon.pMetaboliteGlyph->setModelObjectKey(pMetab->getKey());
                }
            }

          mCommon.pCurrentLayout->addMetaboliteGlyph(mCommon.pMetaboliteGlyph);
          addFix(key, mCommon.pMetaboliteGlyph);
        }
        return;
        break;

      case BoundingBox:

        if (!strcmp(pszName, "BoundingBox"))
          return;

        break;

      case Position:

        if (!strcmp(pszName, "Position"))
          {
            //workload
            const char * attr;
            attr = mParser.getAttributeValue("x", papszAttrs);
            mCommon.pMetaboliteGlyph->setX(CCopasiXMLInterface::DBL(attr));
            attr = mParser.getAttributeValue("y", papszAttrs);
            mCommon.pMetaboliteGlyph->setY(CCopasiXMLInterface::DBL(attr));
            return;
          }

        break;

      case Dimensions:

        if (!strcmp(pszName, "Dimensions"))
          {
            //workload
            const char * attr;
            attr = mParser.getAttributeValue("width", papszAttrs);
            mCommon.pMetaboliteGlyph->setWidth(CCopasiXMLInterface::DBL(attr));
            attr = mParser.getAttributeValue("height", papszAttrs);
            mCommon.pMetaboliteGlyph->setHeight(CCopasiXMLInterface::DBL(attr));
            return;
          }

        break;

      default:
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::MetaboliteGlyphElement::end(const XML_Char *pszName)
{
  if (!strcmp(pszName, "MetaboliteGlyph"))
    {
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
    }
  else
    {
      switch (mCurrentElement)
        {
          case BoundingBox:
            break;

          case Position:
            break;

          case Dimensions:
            //tell the handler where to continue
            mCurrentElement = BoundingBox;
            break;

          case UNKNOWN_ELEMENT:
            mCurrentElement = MetaboliteGlyph;
            break;

          default:
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "???", mParser.getCurrentLineNumber());
            break;
        }
    }

  return;
}

//******* ListOfMetabGlyphs ********

CCopasiXMLParser::ListOfMetabGlyphsElement::ListOfMetabGlyphsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfMetabGlyphsElement::~ListOfMetabGlyphsElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfMetabGlyphsElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfMetabGlyphs:

        if (strcmp(pszName, "ListOfMetabGlyphs"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfMetabGlyphs", mParser.getCurrentLineNumber());

        break;

      case MetaboliteGlyph:

        if (!strcmp(pszName, "MetaboliteGlyph"))
          {
            if (!mpCurrentHandler)
              mpCurrentHandler = new MetaboliteGlyphElement(mParser, mCommon);

            mParser.pushElementHandler(mpCurrentHandler);
            mpCurrentHandler->start(pszName, papszAttrs);
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfMetabGlyphsElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ListOfMetabGlyphs:

        if (strcmp(pszName, "ListOfMetabGlyphs"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfMetabGlyphs", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case MetaboliteGlyph:

        if (!strcmp(pszName, "MetaboliteGlyph"))
          mCurrentElement = ListOfMetabGlyphs;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

//******** MetaboliteReferenceGlyph **********

CCopasiXMLParser::MetaboliteReferenceGlyphElement::MetaboliteReferenceGlyphElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mLineNumber(0)
{}

CCopasiXMLParser::MetaboliteReferenceGlyphElement::~MetaboliteReferenceGlyphElement()
{}

void CCopasiXMLParser::MetaboliteReferenceGlyphElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  mpCurrentHandler = NULL;
  mLineNumber = (size_t) - 1;

  switch (mCurrentElement)
    {
      case MetaboliteReferenceGlyph:

        if (strcmp(pszName, "MetaboliteReferenceGlyph"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "MetaboliteReferenceGlyph", mParser.getCurrentLineNumber());

        {
          //workload
          const char * key;
          const char * name;
          const char * metaboliteGlyph;
          const char * role;
          key = mParser.getAttributeValue("key", papszAttrs);
          name = mParser.getAttributeValue("name", papszAttrs);
          metaboliteGlyph = mParser.getAttributeValue("metaboliteGlyph", papszAttrs);
          role = mParser.getAttributeValue("role", papszAttrs);

          mCommon.pMetaboliteReferenceGlyph = new CLMetabReferenceGlyph(name);
          const char * objectRole = mParser.getAttributeValue("objectRole", papszAttrs, false);

          if (objectRole != NULL && objectRole[0] != 0)
            {
              mCommon.pMetaboliteReferenceGlyph->setObjectRole(objectRole);
            }

          CLMetabGlyph * pMetabGlyph = dynamic_cast< CLMetabGlyph * >(mCommon.KeyMap.get(metaboliteGlyph));

          //if (!pMetabGlyph) fatalError();

          if (pMetabGlyph)
            mCommon.pMetaboliteReferenceGlyph->setMetabGlyphKey(pMetabGlyph->getKey());

          //interpret role string
          C_INT32 i;

          for (i = 0; (CLMetabReferenceGlyph::XMLRole[i] != "") && (CLMetabReferenceGlyph::XMLRole[i] != role); ++i) {};

          if (CLMetabReferenceGlyph::XMLRole[i] == "")
            mCommon.pMetaboliteReferenceGlyph->setRole(CLMetabReferenceGlyph::UNDEFINED);
          else
            mCommon.pMetaboliteReferenceGlyph->setRole(CLMetabReferenceGlyph::Role(i));

          mCommon.pReactionGlyph->addMetabReferenceGlyph(mCommon.pMetaboliteReferenceGlyph);
          addFix(key, mCommon.pMetaboliteReferenceGlyph);
        }
        return;
        break;

      case BoundingBox:

        if (!strcmp(pszName, "BoundingBox"))
          return;

        break;

      case Position:

        if (!strcmp(pszName, "Position"))
          {
            //workload
            const char * attr;
            attr = mParser.getAttributeValue("x", papszAttrs);
            mCommon.pMetaboliteReferenceGlyph->setX(CCopasiXMLInterface::DBL(attr));
            attr = mParser.getAttributeValue("y", papszAttrs);
            mCommon.pMetaboliteReferenceGlyph->setY(CCopasiXMLInterface::DBL(attr));
            return;
          }

        break;

      case Dimensions:

        if (!strcmp(pszName, "Dimensions"))
          {
            //workload
            const char * attr;
            attr = mParser.getAttributeValue("width", papszAttrs);
            mCommon.pMetaboliteReferenceGlyph->setWidth(CCopasiXMLInterface::DBL(attr));
            attr = mParser.getAttributeValue("height", papszAttrs);
            mCommon.pMetaboliteReferenceGlyph->setHeight(CCopasiXMLInterface::DBL(attr));
            return;
          }

        break;

      case Curve:

        if (!strcmp(pszName, "Curve"))
          {
            mpCurrentHandler = new CurveElement(mParser, mCommon);

            if (mCommon.pMetaboliteReferenceGlyph)
              mCommon.pCurve = &mCommon.pMetaboliteReferenceGlyph->getCurve();
          }

        break;

      default:
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::MetaboliteReferenceGlyphElement::end(const XML_Char *pszName)
{
  if (!strcmp(pszName, "MetaboliteReferenceGlyph"))
    {
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
    }
  else
    {
      switch (mCurrentElement)
        {
          case BoundingBox:
            break;

          case Position:
            break;

          case Dimensions:
            //tell the handler where to continue
            mCurrentElement = BoundingBox;
            break;

          case Curve:
            break;

          case UNKNOWN_ELEMENT:
            mCurrentElement = MetaboliteReferenceGlyph;
            break;

          default:
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "???", mParser.getCurrentLineNumber());
            break;
        }
    }

  return;
}

//******* ListOfMetaboliteReferenceGlyphs ********

CCopasiXMLParser::ListOfMetaboliteReferenceGlyphsElement::ListOfMetaboliteReferenceGlyphsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfMetaboliteReferenceGlyphsElement::~ListOfMetaboliteReferenceGlyphsElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfMetaboliteReferenceGlyphsElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfMetaboliteReferenceGlyphs:

        if (strcmp(pszName, "ListOfMetaboliteReferenceGlyphs"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfMetaboliteReferenceGlyphs", mParser.getCurrentLineNumber());

        break;

      case MetaboliteReferenceGlyph:

        if (!strcmp(pszName, "MetaboliteReferenceGlyph"))
          {
            if (!mpCurrentHandler)
              mpCurrentHandler = new MetaboliteReferenceGlyphElement(mParser, mCommon);

            mParser.pushElementHandler(mpCurrentHandler);
            mpCurrentHandler->start(pszName, papszAttrs);
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfMetaboliteReferenceGlyphsElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ListOfMetaboliteReferenceGlyphs:

        if (strcmp(pszName, "ListOfMetaboliteReferenceGlyphs"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfMetaboliteReferenceGlyphs", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case MetaboliteReferenceGlyph:

        if (!strcmp(pszName, "MetaboliteReferenceGlyph"))
          mCurrentElement = ListOfMetaboliteReferenceGlyphs;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

//******** ReactionGlyph **********

CCopasiXMLParser::ReactionGlyphElement::ReactionGlyphElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mLineNumber(0)
{}

CCopasiXMLParser::ReactionGlyphElement::~ReactionGlyphElement()
{}

void CCopasiXMLParser::ReactionGlyphElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  mpCurrentHandler = NULL;
  mLineNumber = (size_t) - 1;

  switch (mCurrentElement)
    {
      case ReactionGlyph:

        if (strcmp(pszName, "ReactionGlyph"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ReactionGlyph", mParser.getCurrentLineNumber());

        {
          //workload
          const char * key;
          const char * name;
          const char * reaction;
          key = mParser.getAttributeValue("key", papszAttrs);
          name = mParser.getAttributeValue("name", papszAttrs);
          reaction = mParser.getAttributeValue("reaction", papszAttrs);

          mCommon.pReactionGlyph = new CLReactionGlyph(name);
          const char * objectRole = mParser.getAttributeValue("objectRole", papszAttrs, false);

          if (objectRole != NULL && objectRole[0] != 0)
            {
              mCommon.pReactionGlyph->setObjectRole(objectRole);
            }

          if (reaction && reaction[0])
            {
              CReaction * pReaction = dynamic_cast< CReaction * >(mCommon.KeyMap.get(reaction));

              if (!pReaction)
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCXML + 19, "ReactionGlyph" , key);
                }
              else
                {
                  mCommon.pReactionGlyph->setModelObjectKey(pReaction->getKey());
                }
            }

          mCommon.pCurrentLayout->addReactionGlyph(mCommon.pReactionGlyph);
          addFix(key, mCommon.pReactionGlyph);
        }
        return;
        break;

      case BoundingBox:

        if (!strcmp(pszName, "BoundingBox"))
          return;

        break;

      case Position:

        if (!strcmp(pszName, "Position"))
          {
            //workload
            const char * attr;
            attr = mParser.getAttributeValue("x", papszAttrs);
            mCommon.pReactionGlyph->setX(CCopasiXMLInterface::DBL(attr));
            attr = mParser.getAttributeValue("y", papszAttrs);
            mCommon.pReactionGlyph->setY(CCopasiXMLInterface::DBL(attr));
            return;
          }

        break;

      case Dimensions:

        if (!strcmp(pszName, "Dimensions"))
          {
            //workload
            const char * attr;
            attr = mParser.getAttributeValue("width", papszAttrs);
            mCommon.pReactionGlyph->setWidth(CCopasiXMLInterface::DBL(attr));
            attr = mParser.getAttributeValue("height", papszAttrs);
            mCommon.pReactionGlyph->setHeight(CCopasiXMLInterface::DBL(attr));
            return;
          }

        break;

      case Curve:

        if (!strcmp(pszName, "Curve"))
          {
            mpCurrentHandler = new CurveElement(mParser, mCommon);

            if (mCommon.pReactionGlyph)
              mCommon.pCurve = &mCommon.pReactionGlyph->getCurve();
          }

        break;

      case ListOfMetaboliteReferenceGlyphs:

        if (!strcmp(pszName, "ListOfMetaboliteReferenceGlyphs"))
          mpCurrentHandler = new ListOfMetaboliteReferenceGlyphsElement(mParser, mCommon);

        break;

      default:
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::ReactionGlyphElement::end(const XML_Char *pszName)
{
  if (!strcmp(pszName, "ReactionGlyph"))
    {
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
    }
  else
    {
      switch (mCurrentElement)
        {
          case BoundingBox:
            break;

          case Position:
            break;

          case Dimensions:
            break;

          case Curve:
            break;

          case ListOfMetaboliteReferenceGlyphs:
            break;

          case UNKNOWN_ELEMENT:
            mCurrentElement = ReactionGlyph;
            break;

          default:
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "???", mParser.getCurrentLineNumber());
            break;
        }
    }

  return;
}

//******* ListOfReactionGlyphs ********

CCopasiXMLParser::ListOfReactionGlyphsElement::ListOfReactionGlyphsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfReactionGlyphsElement::~ListOfReactionGlyphsElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfReactionGlyphsElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfReactionGlyphs:

        if (strcmp(pszName, "ListOfReactionGlyphs"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfReactionGlyphs", mParser.getCurrentLineNumber());

        break;

      case ReactionGlyph:

        if (!strcmp(pszName, "ReactionGlyph"))
          {
            if (!mpCurrentHandler)
              mpCurrentHandler = new ReactionGlyphElement(mParser, mCommon);

            mParser.pushElementHandler(mpCurrentHandler);
            mpCurrentHandler->start(pszName, papszAttrs);
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfReactionGlyphsElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ListOfReactionGlyphs:

        if (strcmp(pszName, "ListOfReactionGlyphs"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfReactionGlyphs", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case ReactionGlyph:

        if (!strcmp(pszName, "ReactionGlyph"))
          mCurrentElement = ListOfReactionGlyphs;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

//******** TextGlyph **********

CCopasiXMLParser::TextGlyphElement::TextGlyphElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mLineNumber(0)
{}

CCopasiXMLParser::TextGlyphElement::~TextGlyphElement()
{}

void CCopasiXMLParser::TextGlyphElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  mpCurrentHandler = NULL;
  mLineNumber = (size_t) - 1;

  switch (mCurrentElement)
    {
      case TextGlyph:

        if (strcmp(pszName, "TextGlyph"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "TextGlyph", mParser.getCurrentLineNumber());

        {
          //workload
          const char * key;
          const char * name;
          const char * graphicalObject;
          const char * originOfText;
          const char * text;
          key = mParser.getAttributeValue("key", papszAttrs);
          name = mParser.getAttributeValue("name", papszAttrs);
          graphicalObject = mParser.getAttributeValue("graphicalObject", papszAttrs); //TODO
          originOfText = mParser.getAttributeValue("originOfText", papszAttrs, false);
          text = mParser.getAttributeValue("text", papszAttrs, false);

          mCommon.pTextGlyph = new CLTextGlyph(name);
          const char * objectRole = mParser.getAttributeValue("objectRole", papszAttrs, false);

          if (objectRole != NULL && objectRole[0] != 0)
            {
              mCommon.pTextGlyph->setObjectRole(objectRole);
            }

          CLGraphicalObject * pGO = dynamic_cast<CLGraphicalObject *>(mCommon.KeyMap.get(graphicalObject));

          if (pGO)
            mCommon.pTextGlyph->setGraphicalObjectKey(pGO->getKey());

          if (text)
            mCommon.pTextGlyph->setText(text);
          else if (originOfText && originOfText[0])
            {
              CCopasiObject * pObj = mCommon.KeyMap.get(originOfText);
              CModelEntity * pME = dynamic_cast<CModelEntity *>(pObj);
              CReaction * pR = dynamic_cast<CReaction *>(pObj);

              if (pME)
                {
                  mCommon.pTextGlyph->setModelObjectKey(pME->getKey());
                }
              else if (pR)
                {
                  mCommon.pTextGlyph->setModelObjectKey(pR->getKey());
                }
              else
                {
                  if (!text)
                    {
                      mCommon.pTextGlyph->setText("unset");
                      CCopasiMessage(CCopasiMessage::WARNING, MCXML + 20, key);
                    }
                }

              //TODO: When we have a way to handle references to metab references, this needs to be adapted.
            }

          mCommon.pCurrentLayout->addTextGlyph(mCommon.pTextGlyph);
          addFix(key, mCommon.pTextGlyph);
        }
        return;
        break;

      case BoundingBox:

        if (!strcmp(pszName, "BoundingBox"))
          return;

        break;

      case Position:

        if (!strcmp(pszName, "Position"))
          {
            //workload
            const char * attr;
            attr = mParser.getAttributeValue("x", papszAttrs);
            mCommon.pTextGlyph->setX(CCopasiXMLInterface::DBL(attr));
            attr = mParser.getAttributeValue("y", papszAttrs);
            mCommon.pTextGlyph->setY(CCopasiXMLInterface::DBL(attr));
            return;
          }

        break;

      case Dimensions:

        if (!strcmp(pszName, "Dimensions"))
          {
            //workload
            const char * attr;
            attr = mParser.getAttributeValue("width", papszAttrs);
            mCommon.pTextGlyph->setWidth(CCopasiXMLInterface::DBL(attr));
            attr = mParser.getAttributeValue("height", papszAttrs);
            mCommon.pTextGlyph->setHeight(CCopasiXMLInterface::DBL(attr));
            return;
          }

        break;

      default:
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::TextGlyphElement::end(const XML_Char *pszName)
{
  if (!strcmp(pszName, "TextGlyph"))
    {
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
    }
  else
    {
      switch (mCurrentElement)
        {
          case BoundingBox:
            break;

          case Position:
            break;

          case Dimensions:
            //tell the handler where to continue
            mCurrentElement = BoundingBox;
            break;

          case UNKNOWN_ELEMENT:
            mCurrentElement = TextGlyph;
            break;

          default:
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "???", mParser.getCurrentLineNumber());
            break;
        }
    }

  return;
}

//******* ListOfTextGlyphs ********

CCopasiXMLParser::ListOfTextGlyphsElement::ListOfTextGlyphsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfTextGlyphsElement::~ListOfTextGlyphsElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfTextGlyphsElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfTextGlyphs:

        if (strcmp(pszName, "ListOfTextGlyphs"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfTextGlyphs", mParser.getCurrentLineNumber());

        break;

      case TextGlyph:

        if (!strcmp(pszName, "TextGlyph"))
          {
            if (!mpCurrentHandler)
              mpCurrentHandler = new TextGlyphElement(mParser, mCommon);

            mParser.pushElementHandler(mpCurrentHandler);
            mpCurrentHandler->start(pszName, papszAttrs);
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfTextGlyphsElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ListOfTextGlyphs:

        if (strcmp(pszName, "ListOfTextGlyphs"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfTextGlyphs", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case TextGlyph:

        if (!strcmp(pszName, "TextGlyph"))
          mCurrentElement = ListOfTextGlyphs;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

//******** AdditionalGO **********

CCopasiXMLParser::AdditionalGOElement::AdditionalGOElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mLineNumber(0)
{}

CCopasiXMLParser::AdditionalGOElement::~AdditionalGOElement()
{}

void CCopasiXMLParser::AdditionalGOElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  mpCurrentHandler = NULL;
  mLineNumber = (size_t) - 1;

  switch (mCurrentElement)
    {
      case AdditionalGO:

        if (strcmp(pszName, "AdditionalGraphicalObject"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "AdditionalGraphicalObject", mParser.getCurrentLineNumber());

        {
          //workload //TODO
          const char * key;
          const char * name;
          key = mParser.getAttributeValue("key", papszAttrs);
          name = mParser.getAttributeValue("name", papszAttrs);

          mCommon.pGeneralGlyph = new CLGeneralGlyph(name);
          const char * objectRole = mParser.getAttributeValue("objectRole", papszAttrs, false);

          if (objectRole != NULL && objectRole[0] != 0)
            {
              mCommon.pGeneralGlyph->setObjectRole(objectRole);
            }

          mCommon.pCurrentLayout->addGeneralGlyph(mCommon.pGeneralGlyph);
          addFix(key, mCommon.pGeneralGlyph);
        }
        return;
        break;

      case BoundingBox:

        if (!strcmp(pszName, "BoundingBox"))
          return;

        break;

      case Position:

        if (!strcmp(pszName, "Position"))
          {
            //workload
            const char * attr;
            attr = mParser.getAttributeValue("x", papszAttrs);
            mCommon.pGeneralGlyph->setX(CCopasiXMLInterface::DBL(attr));
            attr = mParser.getAttributeValue("y", papszAttrs);
            mCommon.pGeneralGlyph->setY(CCopasiXMLInterface::DBL(attr));
            return;
          }

        break;

      case Dimensions:

        if (!strcmp(pszName, "Dimensions"))
          {
            //workload
            const char * attr;
            attr = mParser.getAttributeValue("width", papszAttrs);
            mCommon.pGeneralGlyph->setWidth(CCopasiXMLInterface::DBL(attr));
            attr = mParser.getAttributeValue("height", papszAttrs);
            mCommon.pGeneralGlyph->setHeight(CCopasiXMLInterface::DBL(attr));
            return;
          }

        break;

      default:
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::AdditionalGOElement::end(const XML_Char *pszName)
{
  if (!strcmp(pszName, "AdditionalGraphicalObject"))
    {
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
    }
  else
    {
      switch (mCurrentElement)
        {
          case BoundingBox:
            break;

          case Position:
            break;

          case Dimensions:
            //tell the handler where to continue
            mCurrentElement = BoundingBox;
            break;

          case UNKNOWN_ELEMENT:
            mCurrentElement = AdditionalGO;
            break;

          default:
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "???", mParser.getCurrentLineNumber());
            break;
        }
    }

  return;
}

//******* ListOfAdditionalGOs ********

CCopasiXMLParser::ListOfAdditionalGOsElement::ListOfAdditionalGOsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfAdditionalGOsElement::~ListOfAdditionalGOsElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfAdditionalGOsElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfAdditionalGOs:

        if (strcmp(pszName, "ListOfAdditionalGraphicalObjects"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfAdditionalGraphicalObjects", mParser.getCurrentLineNumber());

        break;

      case AdditionalGO:

        if (!strcmp(pszName, "AdditionalGraphicalObject"))
          {
            if (!mpCurrentHandler)
              mpCurrentHandler = new AdditionalGOElement(mParser, mCommon);

            mParser.pushElementHandler(mpCurrentHandler);
            mpCurrentHandler->start(pszName, papszAttrs);
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfAdditionalGOsElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ListOfAdditionalGOs:

        if (strcmp(pszName, "ListOfAdditionalGraphicalObjects"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfAdditionalGraphicalObjects", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case AdditionalGO:

        if (!strcmp(pszName, "AdditionalGraphicalObject"))
          mCurrentElement = ListOfAdditionalGOs;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

//******** Layout **********

CCopasiXMLParser::LayoutElement::LayoutElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mLineNumber(0)
{}

CCopasiXMLParser::LayoutElement::~LayoutElement()
{}

void CCopasiXMLParser::LayoutElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */
  mpCurrentHandler = NULL;
  mLineNumber = (size_t) - 1;

  switch (mCurrentElement)
    {
      case Layout:
        mLastKnownElement = Layout;

        if (strcmp(pszName, "Layout"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Layout", mParser.getCurrentLineNumber());

        {
          //workload
          const char * key;
          const char * name;
          key = mParser.getAttributeValue("key", papszAttrs);
          name = mParser.getAttributeValue("name", papszAttrs);

          mCommon.pCurrentLayout = new CLayout();
          addFix(key, mCommon.pCurrentLayout);
          mCommon.pCurrentLayout->setObjectName(name);
        }
        return;
        break;

      case Dimensions:

        if (!strcmp(pszName, "Dimensions"))
          {
            mLastKnownElement = Dimensions;

            //workload
            const char * attr;
            attr = mParser.getAttributeValue("width", papszAttrs);
            double tmpW = CCopasiXMLInterface::DBL(attr);
            attr = mParser.getAttributeValue("height", papszAttrs);
            double tmpH = CCopasiXMLInterface::DBL(attr);
            mCommon.pCurrentLayout->setDimensions(CLDimensions(tmpW, tmpH));

            //we are finished with this tag
            return;
          }

        break;

      case ListOfCompartmentGlyphs:

        if (!strcmp(pszName, "ListOfCompartmentGlyphs"))
          {
            mLastKnownElement = ListOfCompartmentGlyphs;
            mpCurrentHandler = new ListOfCompartmentGlyphsElement(mParser, mCommon);
          }

        break;

      case ListOfMetabGlyphs:

        if (!strcmp(pszName, "ListOfMetabGlyphs"))
          {
            mLastKnownElement = ListOfMetabGlyphs;
            mpCurrentHandler = new ListOfMetabGlyphsElement(mParser, mCommon);
          }

        break;

      case ListOfReactionGlyphs:

        if (!strcmp(pszName, "ListOfReactionGlyphs"))
          {
            mLastKnownElement = ListOfReactionGlyphs;
            mpCurrentHandler = new ListOfReactionGlyphsElement(mParser, mCommon);
          }

        break;

      case ListOfTextGlyphs:

        if (!strcmp(pszName, "ListOfTextGlyphs"))
          {
            mLastKnownElement = ListOfTextGlyphs;
            mpCurrentHandler = new ListOfTextGlyphsElement(mParser, mCommon);
          }

        break;

      case ListOfAdditionalGOs:

        if (!strcmp(pszName, "ListOfAdditionalGraphicalObjects"))
          {
            mLastKnownElement = ListOfAdditionalGOs;
            mpCurrentHandler = new ListOfAdditionalGOsElement(mParser, mCommon);
          }

        break;

      case ListOfLocalRenderInformation:

        if (!strcmp(pszName, "ListOfRenderInformation"))
          {
            mLastKnownElement = ListOfLocalRenderInformation;
            mpCurrentHandler = new ListOfLocalRenderInformationElement(mParser, mCommon);
          }

        break;

      default:
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::LayoutElement::end(const XML_Char *pszName)
{
  if (!strcmp(pszName, "Layout"))
    {
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
    }
  else
    {
      switch (mCurrentElement)
        {
            //     case Layout:
            //       if (strcmp(pszName, "Layout"))
            //         CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
            //                        pszName, "Layout", mParser.getCurrentLineNumber());
            //       mParser.popElementHandler();
            //       mCurrentElement = START_ELEMENT;
            //
            //       /* Tell the parent element we are done. */
            //       mParser.onEndElement(pszName);
            //       break;

          case Dimensions:

            if (strcmp(pszName, "Dimensions"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                             pszName, "Dimensions", mParser.getCurrentLineNumber());

            deleteCurrentHandler();
            break;

          case ListOfCompartmentGlyphs:

            if (strcmp(pszName, "ListOfCompartmentGlyphs"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                             pszName, "ListOfCompartmentGlyphs", mParser.getCurrentLineNumber());

            deleteCurrentHandler();
            break;

          case ListOfMetabGlyphs:

            if (strcmp(pszName, "ListOfMetabGlyphs"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                             pszName, "ListOfMetabGlyphs", mParser.getCurrentLineNumber());

            deleteCurrentHandler();
            break;

          case ListOfReactionGlyphs:

            if (strcmp(pszName, "ListOfReactionGlyphs"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                             pszName, "ListOfReactionGlyphs", mParser.getCurrentLineNumber());

            deleteCurrentHandler();
            break;

          case ListOfTextGlyphs:

            if (strcmp(pszName, "ListOfTextGlyphs"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                             pszName, "ListOfTextGlyphs", mParser.getCurrentLineNumber());

            deleteCurrentHandler();
            break;

          case ListOfAdditionalGOs:

            if (strcmp(pszName, "ListOfAdditionalGraphicalObjects"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                             pszName, "ListOfAdditionalGraphicalObjects", mParser.getCurrentLineNumber());

            deleteCurrentHandler();
            break;

          case ListOfLocalRenderInformation:

            if (strcmp(pszName, "ListOfRenderInformation"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                             pszName, "ListOfRenderInformation", mParser.getCurrentLineNumber());

            deleteCurrentHandler();
            break;

          case UNKNOWN_ELEMENT:
            mCurrentElement = mLastKnownElement;
            break;

          default:
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "???", mParser.getCurrentLineNumber());
            break;
        }
    }

  //  deleteCurrentHandler(); //TODO ??? is not done in ModelElement
  return;
}

CCopasiXMLParser::ListOfLayoutsElement::ListOfLayoutsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfLayoutsElement::~ListOfLayoutsElement()
{}

void CCopasiXMLParser::ListOfLayoutsElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  this->mCurrentElement++; /* We should always be on the next element */
  // we set the handler to NULL so that we can see if a handler was
  // created in this call
  this->mpCurrentHandler = NULL;

  switch (this->mCurrentElement)
    {
      case ListOfLayouts:

        if (strcmp(pszName, "ListOfLayouts"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfLayouts", this->mParser.getCurrentLineNumber());

        //workload
        if (!this->mCommon.pLayoutList)
          {
            this->mCommon.pLayoutList = new CListOfLayouts;
          }

        // we need to jump out of this method here
        // because otherwise the call at the end would
        // call this method again in an endless loop
        return;
        break;

      case Layout:

        if (!strcmp(pszName, "Layout"))
          {
            this->mLastKnownElement = Layout;
            this->mpCurrentHandler = new LayoutElement(this->mParser, this->mCommon);
          }

        break;

      case ListOfGlobalRenderInformation:

        if (!strcmp(pszName, "ListOfGlobalRenderInformation"))
          {
            this->mLastKnownElement = ListOfGlobalRenderInformation;
            this->mpCurrentHandler = new ListOfGlobalRenderInformationElement(this->mParser, this->mCommon);
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        break;
    }

  // if we created a handler in this call, we add it to the stack
  if (this->mpCurrentHandler != NULL)
    {
      this->mParser.pushElementHandler(this->mpCurrentHandler);
    }

  // we call the current handler
  // if we created one, the new one will be called, otherwise
  // the one for ListOfLayouts should be the current one
  // and this method will be called again
  this->mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::ListOfLayoutsElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ListOfLayouts:

        if (strcmp(pszName, "ListOfLayouts"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfLayouts", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case Layout:

        if (strcmp(pszName, "Layout"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Layout", mParser.getCurrentLineNumber());

        //workload
        mCommon.pLayoutList->add(mCommon.pCurrentLayout, true);
        //delete mCommon.pCurrentLayout; //??
        mCommon.pCurrentLayout = NULL;

        //tell the handler where to continue
        mCurrentElement = ListOfLayouts;

        deleteCurrentHandler();

        break;

      case ListOfGlobalRenderInformation:

        if (strcmp(pszName, "ListOfGlobalRenderInformation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfGlobalRenderInformation", mParser.getCurrentLineNumber());

        //tell the handler where to continue
        mCurrentElement = ListOfLayouts;

        deleteCurrentHandler();
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ListOfTasksElement::ListOfTasksElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfTasksElement::~ListOfTasksElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfTasksElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfTasks:

        if (strcmp(pszName, "ListOfTasks"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfTasks", mParser.getCurrentLineNumber());

        if (!mCommon.pTaskList)
          {
            mCommon.pTaskList = new CCopasiVectorN<CCopasiTask>("TaskList");
          }

        break;

      case Task:

        if (strcmp(pszName, "Task"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Task", mParser.getCurrentLineNumber());

        /* If we do not have a task element handler, we create one */
        if (!mpCurrentHandler)
          {
            mpCurrentHandler = new TaskElement(mParser, mCommon);
          }

        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfTasksElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ListOfTasks:

        if (strcmp(pszName, "ListOfTasks"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfTasks", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;
        mParser.onEndElement(pszName);
        break;

      case Task:

        if (strcmp(pszName, "Task"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Task", mParser.getCurrentLineNumber());

        if (mCommon.pCurrentTask != NULL)
          {
            mCommon.pTaskList->add(mCommon.pCurrentTask, true);
            mCommon.pCurrentTask = NULL;
          }

        mCurrentElement = ListOfTasks;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::TaskElement::TaskElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common):
  CXMLElementHandler < CCopasiXMLParser,
  SCopasiXMLParserCommon > (parser, common),
  mpReportElement(NULL),
  mpProblemElement(NULL),
  mpMethodElement(NULL)
{}

CCopasiXMLParser::TaskElement::~TaskElement()
{
  pdelete(mpReportElement);
  pdelete(mpProblemElement);
  pdelete(mpMethodElement);
}

void CCopasiXMLParser::TaskElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */
  mpCurrentHandler = NULL;

  const char * Key;
  const char * type;
  CCopasiTask::Type Type;
  bool Scheduled = false;
  bool UpdateModel = false;

  switch (mCurrentElement)
    {
      case Task:

        if (strcmp(pszName, "Task"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Task", mParser.getCurrentLineNumber());

        mCommon.pCurrentTask = NULL;

        Key = mParser.getAttributeValue("key", papszAttrs, false);
        type = mParser.getAttributeValue("type", papszAttrs);
        Type = toEnum(type, CCopasiTask::XMLType, CCopasiTask::unset);
        Scheduled = mParser.toBool(mParser.getAttributeValue("scheduled", papszAttrs, "false"));
        UpdateModel = mParser.toBool(mParser.getAttributeValue("updateModel", papszAttrs, "false"));

        // create a new CCopasiTask element depending on the type
        switch (Type)
          {
            case CCopasiTask::steadyState:
              mCommon.pCurrentTask = new CSteadyStateTask(mCommon.pTaskList);
              break;

            case CCopasiTask::timeCourse:
              mCommon.pCurrentTask = new CTrajectoryTask(mCommon.pTaskList);
              break;

            case CCopasiTask::scan:
              mCommon.pCurrentTask = new CScanTask(mCommon.pTaskList);
              break;

            case CCopasiTask::fluxMode:
              mCommon.pCurrentTask = new CEFMTask(mCommon.pTaskList);
              break;

            case CCopasiTask::optimization:
              mCommon.pCurrentTask = new COptTask(Type, mCommon.pTaskList);
              mCommon.pCurrentTask->getProblem()->assertParameter("Steady-State", CCopasiParameter::STRING, std::string(""));
              mCommon.pCurrentTask->getProblem()->assertParameter("Time-Course", CCopasiParameter::STRING, std::string(""));
              break;

            case CCopasiTask::parameterFitting:
              mCommon.pCurrentTask = new CFitTask(Type, mCommon.pTaskList);
              break;

            case CCopasiTask::mca:
              mCommon.pCurrentTask = new CMCATask(mCommon.pTaskList);
              break;

            case CCopasiTask::lna:
              mCommon.pCurrentTask = new CLNATask(mCommon.pTaskList);
              break;

            case CCopasiTask::lyap:
              mCommon.pCurrentTask = new CLyapTask(mCommon.pTaskList);
              break;

            case CCopasiTask::sens:
              mCommon.pCurrentTask = new CSensTask(mCommon.pTaskList);
              break;

            case CCopasiTask::tssAnalysis:
              mCommon.pCurrentTask = new CTSSATask(mCommon.pTaskList);
              break;

            case CCopasiTask::moieties:
              mCommon.pCurrentTask = new CMoietiesTask(Type, mCommon.pTaskList);
              break;

            case CCopasiTask::crosssection:
              mCommon.pCurrentTask = new CCrossSectionTask(mCommon.pTaskList);
              break;

            default:
              mParser.pushElementHandler(&mParser.mUnknownElement);
              mParser.onStartElement(pszName, papszAttrs);

              CCopasiMessage(CCopasiMessage::RAW, MCXML + 5,
                             type, mParser.getCurrentLineNumber());
              break;
          }

        if (mCommon.pCurrentTask != NULL)
          {
            mCommon.pCurrentTask->setScheduled(Scheduled);
            mCommon.pCurrentTask->setUpdateModel(UpdateModel);
            mCommon.pCurrentTask->getProblem()->setModel(mCommon.pModel);

            if (Key != NULL)
              {
                addFix(Key, mCommon.pCurrentTask);
              }
          }

        return;
        break;

      case Report:

        if (!strcmp(pszName, "Report"))
          {
            if (!mpReportElement)
              {
                mpReportElement = new ReportInstanceElement(mParser, mCommon);
              }

            mpCurrentHandler = mpReportElement;
          }

        break;

      case Problem:

        if (!strcmp(pszName, "Problem"))
          {
            if (!mpProblemElement)
              {
                mpProblemElement = new ParameterGroupElement(mParser, mCommon);
              }

            mpProblemElement->setDerivedElement(mCommon.pCurrentTask->getProblem());
            mpCurrentHandler = mpProblemElement;
          }

        break;

      case Method:

        if (!strcmp(pszName, "Method"))
          {
            if (!mpMethodElement)
              {
                mpMethodElement = new MethodElement(mParser, mCommon);
              }

            mpCurrentHandler = mpMethodElement;
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::TaskElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Task:

        if (strcmp(pszName, "Task"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Task", mParser.getCurrentLineNumber());

        if (mCommon.pCurrentTask == NULL)
          CCopasiMessage::getLastMessage();

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;
        mParser.onEndElement(pszName);
        break;

      case Report:

        if (strcmp(pszName, "Report"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Report", mParser.getCurrentLineNumber());

        // do nothing, the pointer to the correct report definition can
        // only be set after the report definitions have been read.
        break;

      case Problem:

        if (strcmp(pszName, "Problem"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Problem", mParser.getCurrentLineNumber());

        // This is needed for old files containing the objective function as
        // part of the list of function definitions
        if (mCommon.pCurrentTask->getType() == CCopasiTask::optimization)
          {
            CCopasiProblem * pProblem = mCommon.pCurrentTask->getProblem();
            CCopasiParameter * pParameter = pProblem->getParameter("ObjectiveFunction");

            if (pParameter != NULL)
              {
                if (mCommon.mKey2ObjectiveFunction.find(*pParameter->getValue().pSTRING) !=
                    mCommon.mKey2ObjectiveFunction.end())
                  {
                    std::string Infix = mCommon.mKey2ObjectiveFunction[*pParameter->getValue().pSTRING]->getInfix();
                    pProblem->setValue("ObjectiveExpression", Infix);
                  }

                pProblem->remove(pParameter);
              }

            std::map< std::string, CExpression * >::iterator it = mCommon.mKey2ObjectiveFunction.begin();
            std::map< std::string, CExpression * >::iterator end = mCommon.mKey2ObjectiveFunction.end();

            for (; it != end; ++it)
              {
                pdelete(it->second);
              }

            mCommon.mKey2ObjectiveFunction.clear();
          }

        mCommon.pCurrentTask->getProblem()->elevateChildren();
        break;

      case Method:

        if (strcmp(pszName, "Method"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Method", mParser.getCurrentLineNumber());

        mCommon.pCurrentTask->getMethod()->elevateChildren();
        mCurrentElement = Task;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ReportInstanceElement::ReportInstanceElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ReportInstanceElement::~ReportInstanceElement()
{}

void CCopasiXMLParser::ReportInstanceElement::start(const XML_Char* pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; // We should always be on the next element

  std::string target;
  bool append;
  bool confirmOverwrite;
  std::string reference;

  switch (mCurrentElement)
    {
      case Report:

        if (strcmp(pszName, "Report"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Report", mParser.getCurrentLineNumber());

        reference = mParser.getAttributeValue("reference", papszAttrs);
        target = mParser.getAttributeValue("target", papszAttrs);

        append = mParser.toBool(mParser.getAttributeValue("append", papszAttrs, "false"));
        mCommon.pCurrentTask->getReport().setAppend(append);
        confirmOverwrite = mParser.toBool(mParser.getAttributeValue("confirmOverwrite", papszAttrs, "false"));

        mCommon.pCurrentTask->getReport().setConfirmOverwrite(confirmOverwrite);
        mCommon.pCurrentTask->getReport().setTarget(target);

        if (mCommon.taskReferenceMap.find(reference) == mCommon.taskReferenceMap.end())
          {
            mCommon.taskReferenceMap[reference] = std::vector<CCopasiTask*>();
          }

        mCommon.taskReferenceMap[reference].push_back(mCommon.pCurrentTask);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }
}

void CCopasiXMLParser::ReportInstanceElement::end(const XML_Char* pszName)
{
  switch (mCurrentElement)
    {
      case Report:

        if (strcmp(pszName, "Report"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Report", mParser.getCurrentLineNumber());

        mCurrentElement = START_ELEMENT;
        mParser.popElementHandler();
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }
}

CCopasiXMLParser::ParameterGroupElement::ParameterGroupElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mpParameterHandler(NULL),
  mpParameterTextHandler(NULL),
  mpParameterGroupHandler(NULL),
  mDerivedElement(false)
{}

CCopasiXMLParser::ParameterGroupElement::~ParameterGroupElement()
{
  pdelete(mpParameterHandler);
  pdelete(mpParameterTextHandler);
  pdelete(mpParameterGroupHandler);
}

void CCopasiXMLParser::ParameterGroupElement::start(const XML_Char *pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; // We should always be on the next element
  mpCurrentHandler = NULL;
  std::string name;

  switch (mCurrentElement)
    {
      case ParameterGroup:

        if (mDerivedElement)
          {
            return;
          }
        else if (!strcmp(pszName, "ParameterGroup"))
          {
            name = mParser.getAttributeValue("name", papszAttrs);
            mCommon.ParameterGroupStack.push(new CCopasiParameterGroup(name));
            return;
          }

        break;

      case Content:

        if (!strcmp(pszName, "Parameter"))
          {
            if (!mpParameterHandler)
              {
                mpParameterHandler = new ParameterElement(mParser, mCommon);
              }

            mpCurrentHandler = mpParameterHandler;
          }
        else if (!strcmp(pszName, "ParameterText"))
          {
            if (!mpParameterTextHandler)
              {
                mpParameterTextHandler = new ParameterTextElement(mParser, mCommon);
              }

            mpCurrentHandler = mpParameterTextHandler;
          }
        else if (!strcmp(pszName, "ParameterGroup"))
          {
            if (!mpParameterGroupHandler)
              {
                mpParameterGroupHandler = new ParameterGroupElement(mParser, mCommon);
              }

            mpCurrentHandler = mpParameterGroupHandler;
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);
}

void CCopasiXMLParser::ParameterGroupElement::end(const XML_Char *pszName)
{
  CCopasiParameter * pParameter = NULL;

  switch (mCurrentElement)
    {
      case ParameterGroup:

        if (strcmp(pszName, "ParameterGroup") && !mDerivedElement)
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ParameterGroup", mParser.getCurrentLineNumber());

        mCommon.pCurrentParameter = mCommon.ParameterGroupStack.top();
        mCommon.ParameterGroupStack.pop();
        mCurrentElement = START_ELEMENT;

        mDerivedElement = false;

        mParser.popElementHandler();
        mParser.onEndElement(pszName);

        break;

      case Content:

        if (!strcmp(pszName, "Parameter") &&
            !strcmp(pszName, "ParameterText") &&
            !strcmp(pszName, "ParameterGroup"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Parameter", mParser.getCurrentLineNumber());

        // We need to fix the "Key" parameter of each "Experiment" of the the "Parameter Estimation" problem,
        // since they are handled by the elevation of the problem to CFitProblem.
        if (mCommon.pCurrentTask != NULL &&
            mCommon.pCurrentTask->getType() == CCopasiTask::parameterFitting &&
            (mCommon.pCurrentParameter->getObjectName() == "Key" ||
             mCommon.pCurrentParameter->getObjectName() == "Experiment Key"))
          {
            if (mCommon.UnmappedKeyParameters.size() > 0 &&
                mCommon.UnmappedKeyParameters[mCommon.UnmappedKeyParameters.size() - 1] == mCommon.pCurrentParameter->getKey())
              mCommon.UnmappedKeyParameters.erase(mCommon.UnmappedKeyParameters.begin() + mCommon.UnmappedKeyParameters.size() - 1);
          }

        // Derived elements like methods and problems have already parameters:
        if (mDerivedElement)
          {
            pParameter =
              mCommon.ParameterGroupStack.top()->getParameter(mCommon.pCurrentParameter->getObjectName());
          }

        if (pParameter != NULL)
          {
            CCopasiParameter::Type OriginalType = pParameter->getType();
            *pParameter = *mCommon.pCurrentParameter;

            if (mCommon.UnmappedKeyParameters.size() > 0 &&
                mCommon.UnmappedKeyParameters[mCommon.UnmappedKeyParameters.size() - 1] == mCommon.pCurrentParameter->getKey())
              {
                if (OriginalType == CCopasiParameter::KEY)
                  {
                    mCommon.UnmappedKeyParameters[mCommon.UnmappedKeyParameters.size() - 1] = pParameter->getKey();
                  }
                else
                  {
                    mCommon.UnmappedKeyParameters.erase(mCommon.UnmappedKeyParameters.begin() + mCommon.UnmappedKeyParameters.size() - 1);
                  }
              }

            pdelete(mCommon.pCurrentParameter);
          }
        else
          {
            mCommon.ParameterGroupStack.top()->addParameter(mCommon.pCurrentParameter);
            mCommon.pCurrentParameter = NULL;
          }

        mCurrentElement = ParameterGroup;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

void CCopasiXMLParser::ParameterGroupElement::setDerivedElement(CCopasiParameterGroup * pDerivedElement)
{
  mCommon.ParameterGroupStack.push(pDerivedElement);
  mDerivedElement = true;
}

CCopasiXMLParser::ParameterElement::ParameterElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ParameterElement::~ParameterElement()
{}

void CCopasiXMLParser::ParameterElement::start(const XML_Char *pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; // We should always be on the next element

  const char * cValue = NULL;
  const char * cType = NULL;

  std::string name;
  std::string sValue("");
  bool UnmappedKey = false;

  void * pValue = NULL;
  CCopasiParameter::Type type;

  C_FLOAT64 d;
  C_INT32 i;
  size_t ui;
  bool b;

  switch (mCurrentElement)
    {
      case Parameter:

        if (strcmp(pszName, "Parameter"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Parameter", mParser.getCurrentLineNumber());

        // Parameter has attributes name, type and value
        name = mParser.getAttributeValue("name", papszAttrs);
        cType = mParser.getAttributeValue("type", papszAttrs);
        type = toEnum(cType, CCopasiParameter::XMLType, CCopasiParameter::INVALID);
        cValue = mParser.getAttributeValue("value", papszAttrs);

        if (cValue != NULL)
          {
            sValue = cValue;
          }

        switch (type)
          {
            case CCopasiParameter::DOUBLE:
              d = CCopasiXMLInterface::DBL(sValue.c_str());
              pValue = &d;
              break;

            case CCopasiParameter::UDOUBLE:
              d = CCopasiXMLInterface::DBL(sValue.c_str());
              pValue = &d;
              break;

            case CCopasiParameter::INT:
              i = strToInt(sValue.c_str());
              pValue = &i;
              break;

            case CCopasiParameter::UINT:
              ui = strToUnsignedInt(sValue.c_str());
              pValue = &ui;
              break;

            case CCopasiParameter::BOOL:

              if (sValue == "0" || sValue == "false")
                {
                  b = false;
                }
              else
                {
                  b = true;
                }

              pValue = &b;
              break;

            case CCopasiParameter::STRING:
            case CCopasiParameter::FILE:
            case CCopasiParameter::CN:
              pValue = &sValue;
              break;

            case CCopasiParameter::KEY:
            {
              if (sValue != "" &&
                  CKeyFactory::isValidKey(sValue))
                {
                  CCopasiObject * pObject = mCommon.KeyMap.get(sValue);

                  if (pObject)
                    {
                      sValue = pObject->getKey();
                    }
                  else
                    {
                      UnmappedKey = true;
                    }
                }

              pValue = &sValue;
            }
            break;

            default:
              CCopasiMessage(CCopasiMessage::ERROR, MCXML + 16, name.c_str(), cType, mParser.getCurrentLineNumber());
              pValue = NULL;
              break;
          }

        mCommon.pCurrentParameter = new CCopasiParameter(name, type, pValue);

        if (UnmappedKey)
          {
            mCommon.UnmappedKeyParameters.push_back(mCommon.pCurrentParameter->getKey());
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ParameterElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Parameter:

        if (strcmp(pszName, "Parameter"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Parameter", mParser.getCurrentLineNumber());

        mCurrentElement = START_ELEMENT;
        mParser.popElementHandler();
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ParameterTextElement::ParameterTextElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ParameterTextElement::~ParameterTextElement()
{}

void CCopasiXMLParser::ParameterTextElement::start(const XML_Char *pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; // We should always be on the next element

  std::string name;
  const char * cType;
  CCopasiParameter::Type type;

  switch (mCurrentElement)
    {
      case ParameterText:

        if (strcmp(pszName, "ParameterText"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Parameter", mParser.getCurrentLineNumber());

        // Parameter has attributes name, type and value
        name = mParser.getAttributeValue("name", papszAttrs);
        cType = mParser.getAttributeValue("type", papszAttrs);
        type = toEnum(cType, CCopasiParameter::XMLType, CCopasiParameter::INVALID);

        switch (type)
          {
            case CCopasiParameter::EXPRESSION:
              mParser.pushElementHandler(&mParser.mCharacterDataElement);
              mParser.onStartElement(pszName, papszAttrs);
              break;

            default:
              CCopasiMessage(CCopasiMessage::ERROR, MCXML + 16, name.c_str(), cType, mParser.getCurrentLineNumber());
              break;
          }

        mCommon.pCurrentParameter = new CCopasiParameter(name, type, NULL);

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ParameterTextElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ParameterText:

        if (strcmp(pszName, "ParameterText"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Parameter", mParser.getCurrentLineNumber());

        if (mCommon.pCurrentParameter != NULL)
          {
            mCommon.pCurrentParameter->setValue(mCommon.CharacterData);
          }

        mCurrentElement = START_ELEMENT;
        mParser.popElementHandler();
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::MethodElement::MethodElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler < CCopasiXMLParser,
  SCopasiXMLParserCommon > (parser, common),
  mpContentHandler(NULL),
  mLineNumber(0)
{}

CCopasiXMLParser::MethodElement::~MethodElement()
{
  pdelete(mpContentHandler);
}

void CCopasiXMLParser::MethodElement::start(const XML_Char *pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; // We should always be on the next element
  mpCurrentHandler = NULL;
  mLineNumber = (size_t) - 1;

  std::string name;
  std::string sType;

  switch (mCurrentElement)
    {
      case Method:

        if (!strcmp(pszName, "Method"))
          {
            // get name and type attribute
            name = mParser.getAttributeValue("name", papszAttrs);
            sType = mParser.getAttributeValue("type", papszAttrs, "default");
            // first set the type of the with setMethodType of the current task
            // object
            CCopasiMethod::SubType type =
              toEnum(sType.c_str(), CCopasiMethod::XMLSubType, CCopasiMethod::unset);

            if (type != CCopasiMethod::unset)
              {
                mCommon.pCurrentTask->setMethodType(type);
              }
            else
              {
                // We use the default method for this task and issue a warning
                CCopasiMessage(CCopasiMessage::WARNING, MCXML + 18, sType.c_str(),
                               mParser.getCurrentLineNumber(),
                               CCopasiMethod::XMLSubType[mCommon.pCurrentTask->getMethod()->getSubType()]);
              }

            mCommon.pCurrentTask->getMethod()->setObjectName(name);

            if (!mpContentHandler)
              {
                mpContentHandler = new ParameterGroupElement(mParser, mCommon);
              }

            mpContentHandler->setDerivedElement(mCommon.pCurrentTask->getMethod());
            mpCurrentHandler = mpContentHandler;
          }

        break;

      case Content:
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);
}

void CCopasiXMLParser::MethodElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Method:

        if (strcmp(pszName, "Method"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Method", mParser.getCurrentLineNumber());

        mCurrentElement = START_ELEMENT;
        mParser.popElementHandler();
        mParser.onEndElement(pszName);
        break;

      case Content:
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

//Mrinmayee
CCopasiXMLParser::ListOfReportsElement::ListOfReportsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfReportsElement::~ListOfReportsElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfReportsElement::start(const XML_Char *pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; // We should always be on the next element

  switch (mCurrentElement)
    {
      case ListOfReports:

        if (strcmp(pszName, "ListOfReports"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfReports", mParser.getCurrentLineNumber());

        if (!mCommon.pReportList)
          mCommon.pReportList = new CReportDefinitionVector;

        break;

      case Report:

        if (strcmp(pszName, "Report"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Report", mParser.getCurrentLineNumber());

        /* If we do not have a report element handler we create one. */
        if (!mpCurrentHandler)
          mpCurrentHandler = new ReportElement(mParser, mCommon);

        /* Push the report element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfReportsElement::end(const XML_Char *pszName)
{
  std::map<std::string, std::vector<CCopasiTask*> >::iterator it;

  std::vector<CCopasiTask*>::iterator innerIt;

  CReportDefinition* reportDefinition;

  std::map<std::string , std::vector < std::pair < std::vector <CRegisteredObjectName >*, size_t > > >::iterator outerIt;

  std::vector<std::pair < std::vector <CRegisteredObjectName >*, size_t > >::iterator innerIt2;

  std::vector<CRegisteredObjectName>* nameVector;

  size_t reportIndex;

  switch (mCurrentElement)
    {
      case ListOfReports:

        if (strcmp(pszName, "ListOfReports"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfReports", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;
        // here would be a good place to resolve the report reference
        // issues
        it = mCommon.taskReferenceMap.begin();

        while (it != mCommon.taskReferenceMap.end())
          {
            reportDefinition = dynamic_cast<CReportDefinition*>(mCommon.KeyMap.get((*it).first));
            innerIt = (*it).second.begin();

            while (innerIt != (*it).second.end())
              {
                (*innerIt)->getReport().setReportDefinition(reportDefinition);
                ++innerIt;
              }

            ++it;
          }

        outerIt = mCommon.reportReferenceMap.begin();

        while (outerIt != mCommon.reportReferenceMap.end())
          {
            reportDefinition = dynamic_cast<CReportDefinition*>(mCommon.KeyMap.get((*outerIt).first));
            innerIt2 = (*outerIt).second.begin();

            while (innerIt2 != (*outerIt).second.end())
              {
                reportIndex = (*innerIt2).second;
                nameVector = (*innerIt2).first;
                (*nameVector)[reportIndex] = reportDefinition->getCN();
                ++innerIt2;
              }

            ++outerIt;
          }

        //Tell the parent element we are done.
        mParser.onEndElement(pszName);
        break;

      case Report:
        mCurrentElement = ListOfReports;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ReportElement::ReportElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mpHeaderElement(NULL),
  mpBodyElement(NULL),
  mpFooterElement(NULL),
  mpTableElement(NULL),
  tableFound(false),
  otherFound(false)
{}

CCopasiXMLParser::ReportElement::~ReportElement()
{
  pdelete(mpHeaderElement);
  pdelete(mpBodyElement);
  pdelete(mpFooterElement);
  pdelete(mpTableElement);
}

void CCopasiXMLParser::ReportElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * Key;
  const char * Name;
  const char * Separator;
  const char * Precision;
  CCopasiTask::Type type;

  mCurrentElement++; /* We should always be on the next element */
  mpCurrentHandler = NULL;

  switch (mCurrentElement)
    {
      case Report:

        if (strcmp(pszName, "Report"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Report", mParser.getCurrentLineNumber());

        // We have not found anything yet.
        tableFound = false;
        otherFound = false;

        Key = mParser.getAttributeValue("key", papszAttrs);
        Name = mParser.getAttributeValue("name", papszAttrs);
        type = toEnum(mParser.getAttributeValue("taskType", papszAttrs),
                      CCopasiTask::XMLType, CCopasiTask::unset);

        Separator = mParser.getAttributeValue("separator", papszAttrs, "\t");
        Precision = mParser.getAttributeValue("precision", papszAttrs, "6");

        // create a new report
        mCommon.pReport = new CReportDefinition();
        mCommon.pReport->setTaskType(type);
        mCommon.pReport->setSeparator(CCopasiReportSeparator(Separator));
        mCommon.pReport->setPrecision(strToUnsignedInt(Precision));

        {
          // We need to make sure that the name is unique.
          std::string ValidName(Name);
          size_t Index = 1;

          while (mCommon.pReportList->getIndex(ValidName) != C_INVALID_INDEX)
            {
              std::ostringstream ValidNameStream;
              ValidNameStream << Name << " " << Index++;
              ValidName = ValidNameStream.str();
            }

          mCommon.pReport->setObjectName(ValidName);
        }

        /* We have a new report and add it to the list */
        mCommon.pReportList->add(mCommon.pReport, true);
        addFix(Key, mCommon.pReport);
        return;
        break;

      case Comment:

        if (!strcmp(pszName, "Comment"))
          {
            /* Push the Comment element handler on the stack and call it. */
            mpCurrentHandler = &mParser.mCommentElement;
          }

        break;

      case Header:

        if (!strcmp(pszName, "Header"))
          {
            /* If we do not have a Header element handler we create one. */
            if (tableFound) fatalError();

            otherFound = true;
            mCommon.pReport->setIsTable(false);

            if (!mpHeaderElement)
              mpHeaderElement = new HeaderElement(mParser, mCommon);

            /* Push the Header element handler on the stack and call it. */
            mpCurrentHandler = mpHeaderElement;
          }

        break;

      case Body:

        if (!strcmp(pszName, "Body"))
          {
            /* If we do not have a Body element handler we create one. */
            if (tableFound) fatalError();

            otherFound = true;
            mCommon.pReport->setIsTable(false);

            if (!mpBodyElement)
              mpBodyElement = new BodyElement(mParser, mCommon);

            /* Push the Body element handler on the stack and call it. */
            mpCurrentHandler = mpBodyElement;
          }

        break;

      case Footer:

        if (!strcmp(pszName, "Footer"))
          {
            /* If we do not have a Body element handler we create one. */
            if (tableFound) fatalError();

            otherFound = true;
            mCommon.pReport->setIsTable(false);

            if (!mpFooterElement)
              mpFooterElement = new FooterElement(mParser, mCommon);

            /* Push the Body element handler on the stack and call it. */
            mpCurrentHandler = mpFooterElement;
          }

        break;

      case Table:

        if (!strcmp(pszName, "Table"))
          {
            if (otherFound) fatalError();

            tableFound = true;
            mCommon.pReport->setIsTable(true);

            if (!mpTableElement)
              {
                mpTableElement = new TableElement(mParser, mCommon);
              }

            mpCurrentHandler = mpTableElement;
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  if (mpCurrentHandler)
    {
      mParser.pushElementHandler(mpCurrentHandler);
    }

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::ReportElement::end(const XML_Char *pszName)
{
  if (!strcmp(pszName, "Report") &&
      (mCurrentElement == Comment ||
       mCurrentElement == Header ||
       mCurrentElement == Body))
    mCurrentElement = Report;

  switch (mCurrentElement)
    {
      case Report:

        if (strcmp(pszName, "Report"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Report", mParser.getCurrentLineNumber());

        mCurrentElement = START_ELEMENT;
        mParser.popElementHandler();

        // Tell the parent element we are done.
        mParser.onEndElement(pszName);
        break;

      case Comment:

        if (strcmp(pszName, "Comment"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Comment", mParser.getCurrentLineNumber());

        // check parameter type CCopasiStaticString
        mCommon.pReport->setComment(mCommon.CharacterData);
        mCommon.CharacterData = "";
        break;

      case Header:

        if (strcmp(pszName, "Header"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Header", mParser.getCurrentLineNumber());

        break;

      case Body:

        if (strcmp(pszName, "Body"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Body", mParser.getCurrentLineNumber());

        break;

      case Footer:

        if (strcmp(pszName, "Footer"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Footer", mParser.getCurrentLineNumber());

        mCurrentElement = Report;
        break;

      case Table:

        if (strcmp(pszName, "Table"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Table", mParser.getCurrentLineNumber());

        mCurrentElement = Report;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }
}

CCopasiXMLParser::HeaderElement::HeaderElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mpObjectElement(NULL)
{}

CCopasiXMLParser::HeaderElement::~HeaderElement()
{
  pdelete(mpObjectElement);
}

void CCopasiXMLParser::HeaderElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */
  mpCurrentHandler = NULL;

  switch (mCurrentElement)
    {
      case Header:

        if (strcmp(pszName, "Header"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Header", mParser.getCurrentLineNumber());

        return;
        break;

      case Text:

        if (!strcmp(pszName, "html"))
          {
            mpCurrentHandler = &mParser.mCommentElement;
          }

        break;

      case Object:

        if (!strcmp(pszName, "Object"))
          {
            /* If we do not have an Object element handler we create one. */
            if (!mpObjectElement)
              mpObjectElement = new ObjectElement(mParser, mCommon);

            mpCurrentHandler = mpObjectElement;
          }

        break;

      case Report:

        if (!strcmp(pszName, "Report"))
          mpCurrentHandler = &mParser.mCharacterDataElement;

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  /* Push the current element handler on the stack and call it. */
  if (mpCurrentHandler)
    {
      mParser.pushElementHandler(mpCurrentHandler);
    }

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::HeaderElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Header:

        if (strcmp(pszName, "Header"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Header", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case Text:

        if (strcmp(pszName, "html"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "html", mParser.getCurrentLineNumber());

        mCommon.pReport->getHeaderAddr()->push_back(CCopasiStaticString(mCommon.CharacterData).getCN());
        mCurrentElement = Header;
        break;

      case Object:

        if (strcmp(pszName, "Object"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Object", mParser.getCurrentLineNumber());

        mCommon.pReport->getHeaderAddr()->push_back(CCopasiObjectName(mCommon.CharacterData));
        mCurrentElement = Header;
        break;

      case Report:

        if (strcmp(pszName, "Report"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Report", mParser.getCurrentLineNumber());

        // add the key that is stored in mCommon.CharacterData to the map
        if (mCommon.reportReferenceMap.find(mCommon.CharacterData) == mCommon.reportReferenceMap.end())
          {
            mCommon.reportReferenceMap[mCommon.CharacterData] = std::vector<std::pair <std::vector<CRegisteredObjectName>*, size_t> >();
          }

        mCommon.reportReferenceMap[mCommon.CharacterData].push_back(std::pair<std::vector<CRegisteredObjectName>*, size_t>(mCommon.pReport->getHeaderAddr(), mCommon.pReport->getHeaderAddr()->size()));
        mCommon.pReport->getHeaderAddr()->push_back(CCopasiObjectName(""));
        mCurrentElement = Header;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = Header;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }
}

CCopasiXMLParser::BodyElement::BodyElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mpObjectElement(NULL)
{}

CCopasiXMLParser::BodyElement::~BodyElement()
{
  pdelete(mpObjectElement);
}

void CCopasiXMLParser::BodyElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */
  mpCurrentHandler = NULL;

  switch (mCurrentElement)
    {
      case Body:

        if (strcmp(pszName, "Body"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Body", mParser.getCurrentLineNumber());

        return;
        break;

      case Text:

        if (!strcmp(pszName, "html"))
          {
            mpCurrentHandler = &mParser.mCommentElement;
          }

        break;

      case Object:

        if (!strcmp(pszName, "Object"))
          {
            /* If we do not have an Object element handler we create one. */
            if (!mpObjectElement)
              mpObjectElement = new ObjectElement(mParser, mCommon);

            mpCurrentHandler = mpObjectElement;
          }

        break;

      case Report:

        if (!strcmp(pszName, "Report"))
          mpCurrentHandler = &mParser.mCharacterDataElement;

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  /* Push the current element handler on the stack and call it. */
  if (mpCurrentHandler)
    {
      mParser.pushElementHandler(mpCurrentHandler);
    }

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::BodyElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Body:

        if (strcmp(pszName, "Body"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Body", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case Text:

        if (strcmp(pszName, "html"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "html", mParser.getCurrentLineNumber());

        mCommon.pReport->getBodyAddr()->push_back(CCopasiStaticString(mCommon.CharacterData).getCN());
        mCurrentElement = Body;
        break;

      case Object:

        if (strcmp(pszName, "Object"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Object", mParser.getCurrentLineNumber());

        mCommon.pReport->getBodyAddr()->push_back(CCopasiObjectName(mCommon.CharacterData));
        mCurrentElement = Body;
        break;

      case Report:

        if (strcmp(pszName, "Report"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Report", mParser.getCurrentLineNumber());

        // add the key that is stored in mCommon.CharacterData to the map
        if (mCommon.reportReferenceMap.find(mCommon.CharacterData) == mCommon.reportReferenceMap.end())
          {
            mCommon.reportReferenceMap[mCommon.CharacterData] = std::vector<std::pair <std::vector<CRegisteredObjectName>*, size_t> >();
          }

        mCommon.reportReferenceMap[mCommon.CharacterData].push_back(std::pair<std::vector<CRegisteredObjectName>*, size_t>(mCommon.pReport->getBodyAddr(), mCommon.pReport->getBodyAddr()->size()));
        mCommon.pReport->getBodyAddr()->push_back(CCopasiObjectName(""));
        mCurrentElement = Body;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = Body;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }
}

CCopasiXMLParser::FooterElement::FooterElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mpObjectElement(NULL)
{}

CCopasiXMLParser::FooterElement::~FooterElement()
{
  pdelete(mpObjectElement);
}

void CCopasiXMLParser::FooterElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */
  mpCurrentHandler = NULL;

  switch (mCurrentElement)
    {
      case Footer:

        if (strcmp(pszName, "Footer"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Footer", mParser.getCurrentLineNumber());

        return;
        break;

      case Text:

        if (!strcmp(pszName, "html"))
          {
            mpCurrentHandler = &mParser.mCommentElement;
          }

        break;

      case Object:

        if (!strcmp(pszName, "Object"))
          {
            /* If we do not have an Object element handler we create one. */
            if (!mpObjectElement)
              mpObjectElement = new ObjectElement(mParser, mCommon);

            mpCurrentHandler = mpObjectElement;
          }

        break;

      case Report:

        if (!strcmp(pszName, "Report"))
          mpCurrentHandler = &mParser.mCharacterDataElement;

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  /* Push the current element handler on the stack and call it. */
  if (mpCurrentHandler)
    {
      mParser.pushElementHandler(mpCurrentHandler);
    }

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::FooterElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Footer:

        if (strcmp(pszName, "Footer"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Footer", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case Text:

        if (strcmp(pszName, "html"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "html", mParser.getCurrentLineNumber());

        mCommon.pReport->getFooterAddr()->push_back(CCopasiStaticString(mCommon.CharacterData).getCN());
        mCurrentElement = Footer;
        break;

      case Object:

        if (strcmp(pszName, "Object"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Object", mParser.getCurrentLineNumber());

        mCommon.pReport->getFooterAddr()->push_back(CCopasiObjectName(mCommon.CharacterData));
        mCurrentElement = Footer;
        break;

      case Report:

        if (strcmp(pszName, "Report"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Object", mParser.getCurrentLineNumber());

        // add the key that is stored in mCommon.CharacterData to the map
        if (mCommon.reportReferenceMap.find(mCommon.CharacterData) == mCommon.reportReferenceMap.end())
          {
            mCommon.reportReferenceMap[mCommon.CharacterData] = std::vector<std::pair <std::vector<CRegisteredObjectName>*, size_t> >();
          }

        mCommon.reportReferenceMap[mCommon.CharacterData].push_back(std::pair<std::vector<CRegisteredObjectName>*, size_t>(mCommon.pReport->getFooterAddr(), mCommon.pReport->getFooterAddr()->size()));
        mCommon.pReport->getFooterAddr()->push_back(CCopasiObjectName(""));
        mCurrentElement = Footer;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = Footer;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }
}

CCopasiXMLParser::TableElement::TableElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::TableElement::~TableElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::TableElement::start(const XML_Char *pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; // We should always be on the next element

  const char * printTitle;

  switch (mCurrentElement)
    {
      case Table:

        if (strcmp(pszName, "Table"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Table", mParser.getCurrentLineNumber());

        printTitle = mParser.getAttributeValue("printTitle", papszAttrs, "false");
        mCommon.pReport->setTitle(mParser.toBool(printTitle));
        break;

      case Object:

        if (strcmp(pszName, "Object"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Object", mParser.getCurrentLineNumber());

        if (!mpCurrentHandler)
          {
            mpCurrentHandler = new ObjectElement(mParser, mCommon);
          }

        mParser.pushElementHandler(mpCurrentHandler);
        mParser.onStartElement(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::TableElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Table:

        if (strcmp(pszName, "Table"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Table", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case Object:

        if (strcmp(pszName, "Object"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Object", mParser.getCurrentLineNumber());

        mCommon.pReport->getTableAddr()->push_back(mCommon.CharacterData);
        mCommon.CharacterData = "";
        mCurrentElement = Table;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ObjectElement::ObjectElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ObjectElement::~ObjectElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ObjectElement::start(const XML_Char *pszName,
    const XML_Char ** papszAttrs)
{
  const char *cn;
  mCurrentElement++; // We should always be on the next element

  switch (mCurrentElement)
    {
      case Object:

        if (strcmp(pszName, "Object"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Object", mParser.getCurrentLineNumber());

        cn = mParser.getAttributeValue("cn", papszAttrs);
        mCommon.CharacterData = cn;
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ObjectElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Object:

        if (strcmp(pszName, "Object"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Object", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        // Tell the parent element we are done.
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }
}

CCopasiXMLParser::MiriamAnnotationElement::MiriamAnnotationElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mRDF(),
  mLevel(0)
{}

CCopasiXMLParser::MiriamAnnotationElement::~MiriamAnnotationElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::MiriamAnnotationElement::start(const XML_Char *pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */
  const XML_Char ** ppAttrs;

  if (mLevel) mCurrentElement = RDF;

  switch (mCurrentElement)
    {
      case MiriamAnnotation:

        if (strcmp(pszName, "MiriamAnnotation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "MiriamAnnotation", mParser.getCurrentLineNumber());

        mRDF.str("");
        mLevel = 0;
        mParser.enableCharacterDataHandler();
        mElementEmpty.push(false);
        break;

      case RDF:

        if (mElementEmpty.top() == true)
          {
            mRDF << ">";
            mElementEmpty.top() = false;
          }

        mRDF << CCopasiXMLInterface::encode(mParser.getCharacterData());
        mRDF << "<" << pszName;

        for (ppAttrs = papszAttrs; *ppAttrs && **ppAttrs; ppAttrs += 2)
          mRDF << " " << *ppAttrs << "=\""
               << CCopasiXMLInterface::encode(*(ppAttrs + 1), CCopasiXMLInterface::attribute) << "\"";

        mLevel++;
        mElementEmpty.push(true);

        mParser.enableCharacterDataHandler();
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::MiriamAnnotationElement::end(const XML_Char *pszName)
{
  std::string rdf;

  switch (mCurrentElement)
    {
      case MiriamAnnotation:

        if (strcmp(pszName, "MiriamAnnotation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "MiriamAnnotation", mParser.getCurrentLineNumber());

        if (mRDF.str() != "")
          mRDF << CCopasiXMLInterface::encode(mParser.getCharacterData());
        else
          mRDF << mParser.getCharacterData();

        mCommon.CharacterData = mRDF.str();

        {
          // remove leading whitepsaces
          std::string::size_type pos = mCommon.CharacterData.find_first_not_of("\x0a\x0d\t ");

          if (pos != 0) mCommon.CharacterData.erase(0, pos);

          // remove trailing whitepsace
          pos = mCommon.CharacterData.find_last_not_of("\x0a\x0d\t ");

          if (pos < mCommon.CharacterData.length())
            mCommon.CharacterData = mCommon.CharacterData.substr(0, pos + 1);
        }

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;
        mElementEmpty.pop();

        deleteCurrentHandler();

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case RDF:
        rdf = mParser.getCharacterData();

        // Check whether and how we need to close the attribute
        if (mElementEmpty.top() == true)
          {
            if (rdf != "")
              {
                mElementEmpty.top() = false;
                mRDF << ">";
              }
            else
              mRDF << " />";
          }

        if (rdf != "")
          mRDF << CCopasiXMLInterface::encode(rdf);

        if (mElementEmpty.top() == false)
          mRDF << "</" << pszName << ">";

        mElementEmpty.pop();
        mElementEmpty.top() = false;
        mLevel--;

        if (!mLevel) mCurrentElement = MiriamAnnotation;

        mParser.enableCharacterDataHandler();
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::GUIElement::GUIElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::GUIElement::~GUIElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::GUIElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case GUI:

        if (strcmp(pszName, "GUI"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "GUI", mParser.getCurrentLineNumber());

        return;
        break;

      case ListOfSliders:

        if (!strcmp(pszName, "ListOfSliders"))
          mpCurrentHandler = new ListOfSlidersElement(mParser, mCommon);

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mpCurrentHandler = &mParser.mUnknownElement;
        break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::GUIElement::end(const XML_Char *pszName)
{
  if (!strcmp(pszName, "GUI"))
    {
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
    }
  else
    deleteCurrentHandler();

  return;
}

CCopasiXMLParser::ListOfSlidersElement::ListOfSlidersElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfSlidersElement::~ListOfSlidersElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::ListOfSlidersElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfSliders:

        if (strcmp(pszName, "ListOfSliders"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfSliders", mParser.getCurrentLineNumber());

        if (!mCommon.pGUI->getSliderList())
          {
            fatalError();
          }

        break;

      case Slider:

        if (strcmp(pszName, "Slider"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Slider", mParser.getCurrentLineNumber());

        /* If we do not have a Slider element handler we create one. */
        if (!mpCurrentHandler)
          mpCurrentHandler = new SliderElement(mParser, mCommon);

        /* Push the Slider element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfSlidersElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ListOfSliders:

        if (strcmp(pszName, "ListOfSliders"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfSliders", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case Slider:

        if (strcmp(pszName, "Slider"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Slider", mParser.getCurrentLineNumber());

        mCurrentElement = ListOfSliders;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::SliderElement::SliderElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::SliderElement::~SliderElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::SliderElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  CSlider * pSlider = NULL;
  const char * Key;
  const char * AssociatedEntityKey;
  const char * ObjectCN;
  const char * objectType;
  CSlider::Type ObjectType;
  const char * tmp;
  C_FLOAT64 ObjectValue;
  C_FLOAT64 MinValue;
  C_FLOAT64 MaxValue;
  unsigned C_INT32 TickNumber;
  unsigned C_INT32 TickFactor;
  const char* scaling;

  switch (mCurrentElement)
    {
      case Slider:

        if (strcmp(pszName, "Slider"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Slider", mParser.getCurrentLineNumber());

        Key = mParser.getAttributeValue("key", papszAttrs);
        AssociatedEntityKey = mParser.getAttributeValue("associatedEntityKey", papszAttrs);
        ObjectCN = mParser.getAttributeValue("objectCN", papszAttrs);
        objectType = mParser.getAttributeValue("objectType", papszAttrs);
        ObjectType = toEnum(objectType, CSlider::TypeName, CSlider::Float);
        tmp = mParser.getAttributeValue("objectValue", papszAttrs);
        ObjectValue = CCopasiXMLInterface::DBL(tmp);
        tmp = mParser.getAttributeValue("minValue", papszAttrs);
        MinValue = CCopasiXMLInterface::DBL(tmp);
        tmp = mParser.getAttributeValue("maxValue", papszAttrs);
        MaxValue = CCopasiXMLInterface::DBL(tmp);
        tmp = mParser.getAttributeValue("tickNumber", papszAttrs, "1000");
        TickNumber = strToUnsignedInt(tmp);
        tmp = mParser.getAttributeValue("tickFactor", papszAttrs, "100");
        TickFactor = strToUnsignedInt(tmp);

        scaling = mParser.getAttributeValue("scaling", papszAttrs, "linear");

        // This is always the case if the XML is conforming to the schema.

        if (mCommon.KeyMap.get(AssociatedEntityKey))
          {
            pSlider = new CSlider("slider", mCommon.pGUI->getSliderList());
            addFix(Key, pSlider);

            if (strncmp(AssociatedEntityKey, "", 1))
              {
                pSlider->setAssociatedEntityKey(mCommon.KeyMap.get(AssociatedEntityKey)->getKey());
              }
            else
              {
                pSlider->setAssociatedEntityKey("");
              }

            pSlider->setSliderObject((std::string) ObjectCN);
            pSlider->setSliderType(ObjectType);
            pSlider->setMaxValue(MaxValue);
            pSlider->setMinValue(MinValue);
            pSlider->setSliderValue(ObjectValue);
            pSlider->setTickNumber(TickNumber);
            pSlider->setTickFactor(TickFactor);
            pSlider->setScaling(pSlider->convertScaleNameToScale(scaling));
            mCommon.pGUI->getSliderList()->add(pSlider, true);
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::SliderElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case Slider:

        if (strcmp(pszName, "Slider"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Slider", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::SBMLReferenceElement::SBMLReferenceElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::SBMLReferenceElement::~SBMLReferenceElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::SBMLReferenceElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * File;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case SBMLReference:

        if (strcmp(pszName, "SBMLReference"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "SBMLReference", mParser.getCurrentLineNumber());

        File = mParser.getAttributeValue("file", papszAttrs);

        if (mCommon.pDataModel)
          mCommon.pDataModel->setSBMLFileName(File);

        break;

      case SBMLMap:

        if (strcmp(pszName, "SBMLMap"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "SBMLMap", mParser.getCurrentLineNumber());

        /* If we do not have a etc element handler we create one. */
        if (!mpCurrentHandler)
          mpCurrentHandler = new SBMLMapElement(mParser, mCommon);

        /* Push the etc element handler on the stack and call it. */
        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::SBMLReferenceElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case SBMLReference:

        if (strcmp(pszName, "SBMLReference"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "SBMLReference", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case SBMLMap:

        if (strcmp(pszName, "SBMLMap"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "SBMLMap", mParser.getCurrentLineNumber());

        mCurrentElement = SBMLReference;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::SBMLMapElement::SBMLMapElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::SBMLMapElement::~SBMLMapElement()
{
  deleteCurrentHandler();
}

void CCopasiXMLParser::SBMLMapElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * SBMLid;
  const char * COPASIkey;
  CCopasiObject * pObject;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case SBMLMap:

        if (strcmp(pszName, "SBMLMap"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "SBMLMap", mParser.getCurrentLineNumber());

        SBMLid = mParser.getAttributeValue("SBMLid", papszAttrs);
        COPASIkey = mParser.getAttributeValue("COPASIkey", papszAttrs);

        if ((pObject = mCommon.KeyMap.get(COPASIkey)))
          {
            CFunction * pFunction;
            CCompartment* pCompartment;
            CMetab * pMetab;
            CModelValue * pModelValue;
            CReaction * pReaction;

            if ((pFunction = dynamic_cast<CFunction *>(pObject)))
              pFunction->setSBMLId(SBMLid);
            else if ((pCompartment = dynamic_cast<CCompartment *>(pObject)))
              pCompartment->setSBMLId(SBMLid);
            else if ((pMetab = dynamic_cast<CMetab *>(pObject)))
              pMetab->setSBMLId(SBMLid);
            else if ((pModelValue = dynamic_cast<CModelValue *>(pObject)))
              pModelValue->setSBMLId(SBMLid);
            else if ((pReaction = dynamic_cast<CReaction *>(pObject)))
              pReaction->setSBMLId(SBMLid);
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::SBMLMapElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case SBMLMap:

        if (strcmp(pszName, "SBMLMap"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "SBMLMap", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

void CCopasiXMLParser::setDatamodel(CCopasiDataModel* pDataModel)
{
  this->mCommon.pDataModel = pDataModel;
}

// ListOfGlobalRenderInformation

CCopasiXMLParser::ListOfGlobalRenderInformationElement::ListOfGlobalRenderInformationElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfGlobalRenderInformationElement::~ListOfGlobalRenderInformationElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::ListOfGlobalRenderInformationElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfGlobalRenderInformation:

        if (strcmp(pszName, "ListOfGlobalRenderInformation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfGlobalRenderInformation", mParser.getCurrentLineNumber());

        break;

      case GlobalRenderInformation:

        //only one type of tags may occur here, so we can throw an exception.
        //No need to silently ignore unknown tags here.
        if (strcmp(pszName, "RenderInformation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "RenderInformation", mParser.getCurrentLineNumber());

        //only one type of tags may occur here, so if the handler exists
        //it must be the correct one
        if (!mpCurrentHandler)
          mpCurrentHandler = new GlobalRenderInformationElement(mParser, mCommon);

        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfGlobalRenderInformationElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ListOfGlobalRenderInformation:

        if (strcmp(pszName, "ListOfGlobalRenderInformation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfGlobalRenderInformation", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case GlobalRenderInformation:

        if (strcmp(pszName, "RenderInformation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "RenderInformation", mParser.getCurrentLineNumber());

        //tell the handler where to continue
        mCurrentElement = ListOfGlobalRenderInformation;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// ListOfLocalRenderInformation

CCopasiXMLParser::ListOfLocalRenderInformationElement::ListOfLocalRenderInformationElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfLocalRenderInformationElement::~ListOfLocalRenderInformationElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::ListOfLocalRenderInformationElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfLocalRenderInformation:

        if (strcmp(pszName, "ListOfRenderInformation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfRenderInformation", mParser.getCurrentLineNumber());

        break;

      case LocalRenderInformation:

        if (!strcmp(pszName, "RenderInformation"))
          {
            //only one type of tags may occur here, so if the handler exists
            //it must be the correct one
            if (!mpCurrentHandler)
              mpCurrentHandler = new LocalRenderInformationElement(mParser, mCommon);

            mParser.pushElementHandler(mpCurrentHandler);
            mpCurrentHandler->start(pszName, papszAttrs);
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfLocalRenderInformationElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ListOfLocalRenderInformation:

        if (strcmp(pszName, "ListOfRenderInformation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfRenderInformation", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case LocalRenderInformation:

        if (strcmp(pszName, "RenderInformation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "RenderInformation", mParser.getCurrentLineNumber());

        //tell the handler where to continue
        mCurrentElement = ListOfLocalRenderInformation;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// ColorDefinitionElement

CCopasiXMLParser::ColorDefinitionElement::ColorDefinitionElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ColorDefinitionElement::~ColorDefinitionElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::ColorDefinitionElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  const char * Id;
  const char * Value;
  CLColorDefinition* pColorDef = NULL;

  switch (mCurrentElement)
    {
      case ColorDefinition:

        if (strcmp(pszName, "ColorDefinition"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ColorDefinition", mParser.getCurrentLineNumber());

        Id = mParser.getAttributeValue("id", papszAttrs);
        Value = mParser.getAttributeValue("value", papszAttrs);
        pColorDef = new  CLColorDefinition();
        pColorDef->setColorValue(Value);
        pColorDef->setId(Id);
        mCommon.pRenderInformation->addColorDefinition(pColorDef);
        // delete the color definition again since the add method made a copy
        delete pColorDef;
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ColorDefinitionElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ColorDefinition:

        if (strcmp(pszName, "ColorDefinition"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ColorDefinition", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// GradientStop

CCopasiXMLParser::GradientStopElement::GradientStopElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::GradientStopElement::~GradientStopElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::GradientStopElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  const char * Offset;
  const char * StopColor;
  CLGradientStop* pStop = NULL;

  switch (mCurrentElement)
    {
      case GradientStop:

        if (strcmp(pszName, "Stop"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Stop", mParser.getCurrentLineNumber());

        Offset = mParser.getAttributeValue("offset", papszAttrs);
        StopColor = mParser.getAttributeValue("stop-color", papszAttrs);
        pStop = new CLGradientStop();
        pStop->setOffset(Offset);
        pStop->setStopColor(StopColor);
        mCommon.pGradient->addGradientStop(pStop);
        // delete the gradient stop again since the add method made a copy
        delete pStop;
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::GradientStopElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case GradientStop:

        if (strcmp(pszName, "Stop"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Stop", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// LinearGradient

CCopasiXMLParser::LinearGradientElement::LinearGradientElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::LinearGradientElement::~LinearGradientElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::LinearGradientElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  const char * X1;
  const char * Y1;
  const char * Z1;
  const char * X2;
  const char * Y2;
  const char * Z2;
  const char * ID;
  const char * SPREADMETHOD;
  CLLinearGradient* pLinearGradient = NULL;

  switch (mCurrentElement)
    {
      case LinearGradient:

        if (strcmp(pszName, "LinearGradient"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "LinearGradient", mParser.getCurrentLineNumber());

        X1 = mParser.getAttributeValue("x1", papszAttrs);
        Y1 = mParser.getAttributeValue("y1", papszAttrs);
        Z1 = mParser.getAttributeValue("z1", papszAttrs, false);
        X2 = mParser.getAttributeValue("x2", papszAttrs);
        Y2 = mParser.getAttributeValue("y2", papszAttrs);
        Z2 = mParser.getAttributeValue("z2", papszAttrs, false);
        ID = mParser.getAttributeValue("id", papszAttrs);
        SPREADMETHOD = mParser.getAttributeValue("spreadMethod", papszAttrs, "pad");
        pLinearGradient = new CLLinearGradient();
        pLinearGradient->setId(ID);

        if (Z1 == NULL)
          {
            pLinearGradient->setPoint1(CLRelAbsVector(X1), CLRelAbsVector(Y1));
          }
        else
          {
            pLinearGradient->setPoint1(CLRelAbsVector(X1), CLRelAbsVector(Y1), CLRelAbsVector(Z1));
          }

        if (Z2 == NULL)
          {
            pLinearGradient->setPoint2(CLRelAbsVector(X2), CLRelAbsVector(Y2));
          }
        else
          {
            pLinearGradient->setPoint2(CLRelAbsVector(X2), CLRelAbsVector(Y2), CLRelAbsVector(Z2));
          }

        if (!strcmp(SPREADMETHOD, "reflect"))
          {
            pLinearGradient->setSpreadMethod(CLGradientBase::REFLECT);
          }
        else if (!strcmp(SPREADMETHOD, "repeat"))
          {
            pLinearGradient->setSpreadMethod(CLGradientBase::REPEAT);
          }
        else
          {
            pLinearGradient->setSpreadMethod(CLGradientBase::PAD);
          }

        mCommon.pGradient = pLinearGradient;
        break;

      case GradientStop:

        //only one type of tags may occur here, so we can throw an exception.
        //No need to silently ignore unknown tags here.
        if (strcmp(pszName, "Stop"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Stop", mParser.getCurrentLineNumber());

        //only one type of tags may occur here, so if the handler exists
        //it must be the correct one
        if (!mpCurrentHandler)
          mpCurrentHandler = new GradientStopElement(mParser, mCommon);

        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::LinearGradientElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case LinearGradient:

        if (strcmp(pszName, "LinearGradient"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "LinearGradient", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCommon.pRenderInformation->addGradientDefinition(mCommon.pGradient);
        // delete the gradient since the add method made a copy
        delete mCommon.pGradient;
        mCommon.pGradient = NULL;

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case GradientStop:

        if (strcmp(pszName, "Stop"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Stop", mParser.getCurrentLineNumber());

        //tell the handler where to continue
        mCurrentElement = LinearGradient;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// RadialGradient

CCopasiXMLParser::RadialGradientElement::RadialGradientElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::RadialGradientElement::~RadialGradientElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::RadialGradientElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  const char * CX;
  const char * CY;
  const char * CZ;
  const char * R;
  const char * FX;
  const char * FY;
  const char * FZ;
  const char * ID;
  const char * SPREADMETHOD;
  CLRadialGradient* pRadialGradient = NULL;

  switch (mCurrentElement)
    {
      case RadialGradient:

        if (strcmp(pszName, "RadialGradient"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "RadialGradient", mParser.getCurrentLineNumber());

        CX = mParser.getAttributeValue("cx", papszAttrs, false);
        CY = mParser.getAttributeValue("cy", papszAttrs, false);
        CZ = mParser.getAttributeValue("cz", papszAttrs, false);
        FX = mParser.getAttributeValue("fx", papszAttrs, false);
        FY = mParser.getAttributeValue("fy", papszAttrs, false);
        FZ = mParser.getAttributeValue("fz", papszAttrs, false);
        R =  mParser.getAttributeValue("r", papszAttrs);
        ID = mParser.getAttributeValue("id", papszAttrs);
        SPREADMETHOD = mParser.getAttributeValue("spreadMethod", papszAttrs, "pad");
        pRadialGradient = new CLRadialGradient();
        pRadialGradient->setId(ID);

        if (CX == NULL)
          {
            CX = "50%";
          }

        if (CY == NULL)
          {
            CY = "50%";
          }

        if (CZ == NULL)
          {
            CZ = "50%";
          }

        pRadialGradient->setCenter(CLRelAbsVector(CX), CLRelAbsVector(CY), CLRelAbsVector(CZ));

        if (R == NULL)
          {
            R = "50%";
          }

        pRadialGradient->setRadius(CLRelAbsVector(R));

        if (FX == NULL)
          {
            FX = CX;
          }

        if (FY == NULL)
          {
            FY = CY;
          }

        if (FZ == NULL)
          {
            FZ = CZ;
          }

        pRadialGradient->setFocalPoint(CLRelAbsVector(FX), CLRelAbsVector(FY), CLRelAbsVector(FZ));

        if (!strcmp(SPREADMETHOD, "reflect"))
          {
            pRadialGradient->setSpreadMethod(CLGradientBase::REFLECT);
          }
        else if (!strcmp(SPREADMETHOD, "repeat"))
          {
            pRadialGradient->setSpreadMethod(CLGradientBase::REPEAT);
          }
        else
          {
            pRadialGradient->setSpreadMethod(CLGradientBase::PAD);
          }

        mCommon.pGradient = pRadialGradient;
        break;

      case GradientStop:

        //only one type of tags may occur here, so we can throw an exception.
        //No need to silently ignore unknown tags here.
        if (strcmp(pszName, "Stop"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Stop", mParser.getCurrentLineNumber());

        //only one type of tags may occur here, so if the handler exists
        //it must be the correct one
        if (!mpCurrentHandler)
          mpCurrentHandler = new GradientStopElement(mParser, mCommon);

        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::RadialGradientElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case RadialGradient:

        if (strcmp(pszName, "RadialGradient"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "RadialGradient", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCommon.pRenderInformation->addGradientDefinition(mCommon.pGradient);
        // delete the gradient since the add method made a copy
        delete mCommon.pGradient;
        mCommon.pGradient = NULL;

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case GradientStop:

        if (strcmp(pszName, "Stop"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Stop", mParser.getCurrentLineNumber());

        //tell the handler where to continue
        mCurrentElement = RadialGradient;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// Rectangle Element

CCopasiXMLParser::RectangleElement::RectangleElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::RectangleElement::~RectangleElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::RectangleElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  const char * Transform;
  const char * Stroke;
  const char * StrokeWidth;
  const char * StrokeDashArray;
  const char * Fill;
  const char * FillRule;
  const char * X;
  const char * Y;
  const char * Z;
  const char * WIDTH;
  const char * HEIGHT;
  const char * RX;
  const char * RY;
  CLRectangle* pRectangle = NULL;

  switch (mCurrentElement)
    {
      case Rectangle:

        if (strcmp(pszName, "Rectangle"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Rectangle", mParser.getCurrentLineNumber());

        Transform = mParser.getAttributeValue("transform", papszAttrs, false);
        Stroke = mParser.getAttributeValue("stroke", papszAttrs, false);
        StrokeWidth = mParser.getAttributeValue("stroke-width", papszAttrs, false);
        StrokeDashArray = mParser.getAttributeValue("stroke-dasharray", papszAttrs, false);
        Fill = mParser.getAttributeValue("fill", papszAttrs, false);
        FillRule = mParser.getAttributeValue("fill-rule", papszAttrs, false);
        X = mParser.getAttributeValue("x", papszAttrs);
        Y = mParser.getAttributeValue("y", papszAttrs);
        Z = mParser.getAttributeValue("z", papszAttrs, "0.0");
        WIDTH = mParser.getAttributeValue("width", papszAttrs);
        HEIGHT = mParser.getAttributeValue("height", papszAttrs);
        RX = mParser.getAttributeValue("rx", papszAttrs, "0.0");
        RY = mParser.getAttributeValue("ry", papszAttrs, "0.0");
        pRectangle = new CLRectangle();

        if (Transform != NULL)
          {
            pRectangle->parseTransformation(Transform);
          }

        if (Stroke != NULL)
          {
            pRectangle->setStroke(Stroke);
          }

        if (StrokeWidth != NULL)
          {
            double width = strToDouble(StrokeWidth, NULL);
            pRectangle->setStrokeWidth(width);
          }

        if (StrokeDashArray != NULL)
          {
            pRectangle->parseDashArray(StrokeDashArray);
          }

        if (Fill != NULL)
          {
            pRectangle->setFillColor(Fill);
          }

        if (FillRule != NULL)
          {
            std::string f(FillRule);

            if (f == "nonzero")
              {
                pRectangle->setFillRule(CLGraphicalPrimitive2D::NONZERO);
              }
            else if (f == "evenodd")
              {
                pRectangle->setFillRule(CLGraphicalPrimitive2D::EVENODD);
              }
            else
              {
                pRectangle->setFillRule(CLGraphicalPrimitive2D::INHERIT);
              }
          }

        pRectangle->setCoordinatesAndSize(CLRelAbsVector(X), CLRelAbsVector(Y), CLRelAbsVector(Z), CLRelAbsVector(WIDTH), CLRelAbsVector(HEIGHT));
        pRectangle->setRadii(CLRelAbsVector(RX), CLRelAbsVector(RY));
        mCommon.pGroup->addChildElement(pRectangle);
        // delete the gradient stop again since the add method made a copy
        delete pRectangle;
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::RectangleElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case Rectangle:

        if (strcmp(pszName, "Rectangle"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Rectangle", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// Ellipse Element

CCopasiXMLParser::EllipseElement::EllipseElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::EllipseElement::~EllipseElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::EllipseElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  const char * Transform;
  const char * Stroke;
  const char * StrokeWidth;
  const char * StrokeDashArray;
  const char * Fill;
  const char * FillRule;
  const char * CX;
  const char * CY;
  const char * CZ;
  const char * RX;
  const char * RY;
  CLEllipse* pEllipse = NULL;

  switch (mCurrentElement)
    {
      case Ellipse:

        if (strcmp(pszName, "Ellipse"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Ellipse", mParser.getCurrentLineNumber());

        Transform = mParser.getAttributeValue("transform", papszAttrs, false);
        Stroke = mParser.getAttributeValue("stroke", papszAttrs, false);
        StrokeWidth = mParser.getAttributeValue("stroke-width", papszAttrs, false);
        StrokeDashArray = mParser.getAttributeValue("stroke-dasharray", papszAttrs, false);
        Fill = mParser.getAttributeValue("fill", papszAttrs, false);
        FillRule = mParser.getAttributeValue("fill-rule", papszAttrs, false);
        CX = mParser.getAttributeValue("cx", papszAttrs);
        CY = mParser.getAttributeValue("cy", papszAttrs);
        CZ = mParser.getAttributeValue("cz", papszAttrs, "0.0");
        RX = mParser.getAttributeValue("rx", papszAttrs);
        RY = mParser.getAttributeValue("ry", papszAttrs, RX);
        pEllipse = new CLEllipse();

        if (Transform != NULL)
          {
            pEllipse->parseTransformation(Transform);
          }

        if (Stroke != NULL)
          {
            pEllipse->setStroke(Stroke);
          }

        if (StrokeWidth != NULL)
          {
            double width = strToDouble(StrokeWidth, NULL);
            pEllipse->setStrokeWidth(width);
          }

        if (StrokeDashArray != NULL)
          {
            pEllipse->parseDashArray(StrokeDashArray);
          }

        if (Fill != NULL)
          {
            pEllipse->setFillColor(Fill);
          }

        if (FillRule != NULL)
          {
            std::string f(FillRule);

            if (f == "nonzero")
              {
                pEllipse->setFillRule(CLGraphicalPrimitive2D::NONZERO);
              }
            else if (f == "evenodd")
              {
                pEllipse->setFillRule(CLGraphicalPrimitive2D::EVENODD);
              }
            else
              {
                pEllipse->setFillRule(CLGraphicalPrimitive2D::INHERIT);
              }
          }

        pEllipse->setCenter3D(CLRelAbsVector(CX), CLRelAbsVector(CY), CLRelAbsVector(CZ));
        pEllipse->setRadii(CLRelAbsVector(RX), CLRelAbsVector(RY));
        mCommon.pGroup->addChildElement(pEllipse);
        // delete the gradient stop again since the add method made a copy
        delete pEllipse;
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::EllipseElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case Ellipse:

        if (strcmp(pszName, "Ellipse"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Ellipse", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// Polygon Element

CCopasiXMLParser::PolygonElement::PolygonElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::PolygonElement::~PolygonElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::PolygonElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  const char * Transform;
  const char * Stroke;
  const char * StrokeWidth;
  const char * StrokeDashArray;
  const char * Fill;
  const char * FillRule;
  CLPolygon* pPolygon = NULL;

  switch (mCurrentElement)
    {
      case Polygon:

        if (strcmp(pszName, "Polygon"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Polygon", mParser.getCurrentLineNumber());

        Transform = mParser.getAttributeValue("transform", papszAttrs, false);
        Stroke = mParser.getAttributeValue("stroke", papszAttrs, false);
        StrokeWidth = mParser.getAttributeValue("stroke-width", papszAttrs, false);
        StrokeDashArray = mParser.getAttributeValue("stroke-dasharray", papszAttrs, false);
        Fill = mParser.getAttributeValue("fill", papszAttrs, false);
        FillRule = mParser.getAttributeValue("fill-rule", papszAttrs, false);
        pPolygon = new CLPolygon();

        if (Transform != NULL)
          {
            pPolygon->parseTransformation(Transform);
          }

        if (Stroke != NULL)
          {
            pPolygon->setStroke(Stroke);
          }

        if (StrokeWidth != NULL)
          {
            double width = strToDouble(StrokeWidth, NULL);
            pPolygon->setStrokeWidth(width);
          }

        if (StrokeDashArray != NULL)
          {
            pPolygon->parseDashArray(StrokeDashArray);
          }

        if (Fill != NULL)
          {
            pPolygon->setFillColor(Fill);
          }

        if (FillRule != NULL)
          {
            std::string f(FillRule);

            if (f == "nonzero")
              {
                pPolygon->setFillRule(CLGraphicalPrimitive2D::NONZERO);
              }
            else if (f == "evenodd")
              {
                pPolygon->setFillRule(CLGraphicalPrimitive2D::EVENODD);
              }
            else
              {
                pPolygon->setFillRule(CLGraphicalPrimitive2D::INHERIT);
              }
          }

        mCommon.pGroup->addChildElement(pPolygon);
        // delete the polygon again since the addElement method made a copy
        delete pPolygon;
        pPolygon = dynamic_cast<CLPolygon*>(mCommon.pGroup->getElement(mCommon.pGroup->getNumElements() - 1));
        assert(pPolygon != NULL);
        mCommon.pListOfCurveElements = pPolygon->getListOfElements();
        break;

      case ListOfElements:

        //only one type of tags may occur here, so we can throw an exception.
        //No need to silently ignore unknown tags here.
        if (strcmp(pszName, "ListOfElements"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfElements", mParser.getCurrentLineNumber());

        //only one type of tags may occur here, so if the handler exists
        //it must be the correct one
        if (!mpCurrentHandler)
          mpCurrentHandler = new ListOfCurveElementsElement(mParser, mCommon);

        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::PolygonElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case Polygon:

        if (strcmp(pszName, "Polygon"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Polygon", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCommon.pListOfCurveElements = NULL;

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case ListOfElements:

        if (strcmp(pszName, "ListOfElements"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfElements", mParser.getCurrentLineNumber());

        //tell the handler where to continue
        mCurrentElement = Polygon;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// RenderCurve Element

CCopasiXMLParser::RenderCurveElement::RenderCurveElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::RenderCurveElement::~RenderCurveElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::RenderCurveElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  const char * Transform;
  const char * Stroke;
  const char * StrokeWidth;
  const char * StrokeDashArray;
  const char * StartHead;
  const char * EndHead;
  CLRenderCurve* pRenderCurve = NULL;

  switch (mCurrentElement)
    {
      case RenderCurve:

        if (strcmp(pszName, "Curve"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Curve", mParser.getCurrentLineNumber());

        Transform = mParser.getAttributeValue("transform", papszAttrs, false);
        Stroke = mParser.getAttributeValue("stroke", papszAttrs, false);
        StrokeWidth = mParser.getAttributeValue("stroke-width", papszAttrs, false);
        StrokeDashArray = mParser.getAttributeValue("stroke-dasharray", papszAttrs, false);
        StartHead = mParser.getAttributeValue("startHead", papszAttrs, false);
        EndHead = mParser.getAttributeValue("endHead", papszAttrs, false);
        pRenderCurve = new CLRenderCurve();

        if (Transform != NULL)
          {
            pRenderCurve->parseTransformation(Transform);
          }

        if (Stroke != NULL)
          {
            pRenderCurve->setStroke(Stroke);
          }

        if (StrokeWidth != NULL)
          {
            double width = strToDouble(StrokeWidth, NULL);
            pRenderCurve->setStrokeWidth(width);
          }

        if (StrokeDashArray != NULL)
          {
            pRenderCurve->parseDashArray(StrokeDashArray);
          }

        if (StartHead != NULL)
          {
            pRenderCurve->setStartHead(StartHead);
          }

        if (EndHead != NULL)
          {
            pRenderCurve->setEndHead(EndHead);
          }

        assert(mCommon.pGroup != NULL);
        mCommon.pGroup->addChildElement(pRenderCurve);
        // delete the polygon again since the addElement method made a copy
        delete pRenderCurve;
        pRenderCurve = dynamic_cast<CLRenderCurve*>(mCommon.pGroup->getElement(mCommon.pGroup->getNumElements() - 1));
        assert(pRenderCurve != NULL);
        mCommon.pListOfCurveElements = pRenderCurve->getListOfCurveElements();
        break;

      case ListOfElements:

        //only one type of tags may occur here, so we can throw an exception.
        //No need to silently ignore unknown tags here.
        if (strcmp(pszName, "ListOfElements"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfElements", mParser.getCurrentLineNumber());

        //only one type of tags may occur here, so if the handler exists
        //it must be the correct one
        if (!mpCurrentHandler)
          mpCurrentHandler = new ListOfCurveElementsElement(mParser, mCommon);

        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::RenderCurveElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case RenderCurve:

        if (strcmp(pszName, "Curve"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Curve", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCommon.pListOfCurveElements = NULL;

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case ListOfElements:

        if (strcmp(pszName, "ListOfElements"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfElements", mParser.getCurrentLineNumber());

        //tell the handler where to continue
        mCurrentElement = RenderCurve;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// Text Element

CCopasiXMLParser::TextElement::TextElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::TextElement::~TextElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::TextElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  const char * Transform;
  const char * Stroke;
  const char * StrokeWidth;
  const char * StrokeDashArray;
  const char * X;
  const char * Y;
  const char * Z;
  const char * FontFamily;
  const char * FontSize;
  const char * FontWeight;
  const char * FontStyle;
  const char * TextAnchor;
  const char * VTextAnchor;
  CLText* pText = NULL;

  switch (mCurrentElement)
    {
      case RenderText:

        if (strcmp(pszName, "Text"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Text", mParser.getCurrentLineNumber());

        Transform = mParser.getAttributeValue("transform", papszAttrs, false);
        Stroke = mParser.getAttributeValue("stroke", papszAttrs, false);
        StrokeWidth = mParser.getAttributeValue("stroke-width", papszAttrs, false);
        StrokeDashArray = mParser.getAttributeValue("stroke-dasharray", papszAttrs, false);
        X = mParser.getAttributeValue("x", papszAttrs);
        Y = mParser.getAttributeValue("y", papszAttrs);
        Z = mParser.getAttributeValue("z", papszAttrs, "0.0");
        FontFamily = mParser.getAttributeValue("font-family", papszAttrs, false);
        FontSize = mParser.getAttributeValue("font-size", papszAttrs, false);
        FontWeight = mParser.getAttributeValue("font-weight", papszAttrs, false);
        FontStyle = mParser.getAttributeValue("font-style", papszAttrs, false);
        TextAnchor = mParser.getAttributeValue("text-anchor", papszAttrs, false);
        VTextAnchor = mParser.getAttributeValue("vtext-anchor", papszAttrs, false);
        pText = new CLText(NULL);

        if (Transform != NULL)
          {
            pText->parseTransformation(Transform);
          }

        if (Stroke != NULL)
          {
            pText->setStroke(Stroke);
          }

        if (StrokeWidth != NULL)
          {
            double width = strToDouble(StrokeWidth, NULL);
            pText->setStrokeWidth(width);
          }

        if (StrokeDashArray != NULL)
          {
            pText->parseDashArray(StrokeDashArray);
          }

        pText->setCoordinates(CLRelAbsVector(X), CLRelAbsVector(Y), CLRelAbsVector(Z));

        if (FontFamily != NULL)
          {
            pText->setFontFamily(FontFamily);
          }

        if (FontSize != NULL)
          {
            pText->setFontSize(CLRelAbsVector(FontSize));
          }

        if (FontStyle != NULL)
          {
            std::string s(FontStyle);

            if (s == "normal")
              {
                pText->setFontStyle(CLText::STYLE_NORMAL);
              }
            else if (s == "italic")
              {
                pText->setFontStyle(CLText::STYLE_ITALIC);
              }
          }

        if (FontWeight != NULL)
          {
            std::string s(FontWeight);

            if (s == "normal")
              {
                pText->setFontWeight(CLText::WEIGHT_NORMAL);
              }
            else if (s == "bold")
              {
                pText->setFontWeight(CLText::WEIGHT_BOLD);
              }
          }

        if (TextAnchor != NULL)
          {
            std::string s(TextAnchor);

            if (s == "start")
              {
                pText->setTextAnchor(CLText::ANCHOR_START);
              }
            else if (s == "middle")
              {
                pText->setTextAnchor(CLText::ANCHOR_MIDDLE);
              }
            else if (s == "end")
              {
                pText->setTextAnchor(CLText::ANCHOR_END);
              }
          }

        if (VTextAnchor != NULL)
          {
            std::string s(VTextAnchor);

            if (s == "top")
              {
                pText->setVTextAnchor(CLText::ANCHOR_TOP);
              }
            else if (s == "middle")
              {
                pText->setVTextAnchor(CLText::ANCHOR_MIDDLE);
              }
            else if (s == "bottom")
              {
                pText->setVTextAnchor(CLText::ANCHOR_BOTTOM);
              }
          }

        mCommon.pGroup->addChildElement(pText);
        // delete the text element again since the add method made a copy
        delete pText;
        mCommon.pText = dynamic_cast<CLText*>(mCommon.pGroup->getElement(mCommon.pGroup->getNumElements() - 1));
        assert(mCommon.pText != NULL);
        mParser.enableCharacterDataHandler();
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::TextElement::end(const XML_Char * pszName)
{
  std::string text;

  switch (mCurrentElement)
    {
      case RenderText:

        if (strcmp(pszName, "Text"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Text", mParser.getCurrentLineNumber());

        text = mParser.getCharacterData("\x0a\x0d\t ", "");
        assert(mCommon.pText != NULL);
        mCommon.pText->setText(text);
        mCommon.pText = NULL;
        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// Image Element

CCopasiXMLParser::ImageElement::ImageElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ImageElement::~ImageElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::ImageElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  const char * Transform;
  const char * X;
  const char * Y;
  const char * Z;
  const char * WIDTH;
  const char * HEIGHT;
  const char * HREF;
  CLImage* pImage = NULL;

  switch (mCurrentElement)
    {
      case Image:

        if (strcmp(pszName, "Image"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Image", mParser.getCurrentLineNumber());

        Transform = mParser.getAttributeValue("transform", papszAttrs, false);
        X = mParser.getAttributeValue("x", papszAttrs);
        Y = mParser.getAttributeValue("y", papszAttrs);
        Z = mParser.getAttributeValue("z", papszAttrs, "0.0");
        WIDTH = mParser.getAttributeValue("width", papszAttrs);
        HEIGHT = mParser.getAttributeValue("height", papszAttrs);
        HREF = mParser.getAttributeValue("href", papszAttrs);
        pImage = new CLImage();

        if (Transform != NULL)
          {
            pImage->parseTransformation(Transform);
          }

        pImage->setCoordinates(CLRelAbsVector(X), CLRelAbsVector(Y), CLRelAbsVector(Z));
        pImage->setDimensions(CLRelAbsVector(WIDTH), CLRelAbsVector(HEIGHT));
        pImage->setImageReference(HREF);
        mCommon.pGroup->addChildElement(pImage);
        // delete the image again since the add method made a copy
        delete pImage;
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ImageElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case Image:

        if (strcmp(pszName, "Image"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Image", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// Group Element

CCopasiXMLParser::GroupElement::GroupElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::GroupElement::~GroupElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::GroupElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{

  // TODO This will not work for groups, since the order of children is not fixed.
  mCurrentElement++; /* We should always be on the next element */

  const char * Transform;
  const char * Stroke;
  const char * StrokeWidth;
  const char * StrokeDashArray;
  const char * Fill;
  const char * FillRule;
  const char * FontFamily;
  const char * FontSize;
  const char * FontWeight;
  const char * FontStyle;
  const char * TextAnchor;
  const char * VTextAnchor;
  const char * StartHead;
  const char * EndHead;
  mpCurrentHandler = NULL;
  CLGroup* pGroup = NULL;

  switch (mCurrentElement)
    {
      case Group:

        if (strcmp(pszName, "Group"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Group", mParser.getCurrentLineNumber());

        Transform = mParser.getAttributeValue("transform", papszAttrs, false);
        Stroke = mParser.getAttributeValue("stroke", papszAttrs, false);
        StrokeWidth = mParser.getAttributeValue("stroke-width", papszAttrs, false);
        StrokeDashArray = mParser.getAttributeValue("stroke-dasharray", papszAttrs, false);
        Fill = mParser.getAttributeValue("fill", papszAttrs, false);
        FillRule = mParser.getAttributeValue("fill-rule", papszAttrs, false);
        FontFamily = mParser.getAttributeValue("font-family", papszAttrs, false);
        FontSize = mParser.getAttributeValue("font-size", papszAttrs, false);
        FontWeight = mParser.getAttributeValue("font-weight", papszAttrs, false);
        FontStyle = mParser.getAttributeValue("font-style", papszAttrs, false);
        TextAnchor = mParser.getAttributeValue("text-anchor", papszAttrs, false);
        VTextAnchor = mParser.getAttributeValue("vtext-anchor", papszAttrs, false);
        StartHead = mParser.getAttributeValue("startHead", papszAttrs, false);
        EndHead = mParser.getAttributeValue("endHead", papszAttrs, false);
        pGroup = new CLGroup();

        if (Transform != NULL)
          {
            pGroup->parseTransformation(Transform);
          }

        if (Stroke != NULL)
          {
            pGroup->setStroke(Stroke);
          }

        if (StrokeWidth != NULL)
          {
            double width = strToDouble(StrokeWidth, NULL);
            pGroup->setStrokeWidth(width);
          }

        if (StrokeDashArray != NULL)
          {
            pGroup->parseDashArray(StrokeDashArray);
          }

        if (Fill != NULL)
          {
            pGroup->setFillColor(Fill);
          }

        if (FillRule != NULL)
          {
            std::string f(FillRule);

            if (f == "nonzero")
              {
                pGroup->setFillRule(CLGraphicalPrimitive2D::NONZERO);
              }
            else if (f == "evenodd")
              {
                pGroup->setFillRule(CLGraphicalPrimitive2D::EVENODD);
              }
            else
              {
                pGroup->setFillRule(CLGraphicalPrimitive2D::INHERIT);
              }
          }

        if (FontFamily != NULL)
          {
            pGroup->setFontFamily(FontFamily);
          }

        if (FontSize != NULL)
          {
            pGroup->setFontSize(CLRelAbsVector(FontSize));
          }

        if (FontStyle != NULL)
          {
            std::string s(FontStyle);

            if (s == "normal")
              {
                pGroup->setFontStyle(CLText::STYLE_NORMAL);
              }
            else if (s == "italic")
              {
                pGroup->setFontStyle(CLText::STYLE_ITALIC);
              }
          }

        if (FontWeight != NULL)
          {
            std::string s(FontWeight);

            if (s == "normal")
              {
                pGroup->setFontWeight(CLText::WEIGHT_NORMAL);
              }
            else if (s == "bold")
              {
                pGroup->setFontWeight(CLText::WEIGHT_BOLD);
              }
          }

        if (TextAnchor != NULL)
          {
            std::string s(TextAnchor);

            if (s == "start")
              {
                pGroup->setTextAnchor(CLText::ANCHOR_START);
              }
            else if (s == "middle")
              {
                pGroup->setTextAnchor(CLText::ANCHOR_MIDDLE);
              }
            else if (s == "end")
              {
                pGroup->setTextAnchor(CLText::ANCHOR_END);
              }
          }

        if (VTextAnchor != NULL)
          {
            std::string s(VTextAnchor);

            if (s == "top")
              {
                pGroup->setVTextAnchor(CLText::ANCHOR_TOP);
              }
            else if (s == "middle")
              {
                pGroup->setVTextAnchor(CLText::ANCHOR_MIDDLE);
              }
            else if (s == "bottom")
              {
                pGroup->setVTextAnchor(CLText::ANCHOR_BOTTOM);
              }
          }

        if (StartHead != NULL)
          {
            pGroup->setStartHead(StartHead);
          }

        if (EndHead != NULL)
          {
            pGroup->setEndHead(EndHead);
          }

        // now we have to check where to add the group
        // it could belong to another group,
        // a style or a line ending
        if (mCommon.pGroup != NULL)
          {
            mCommon.pGroup->addChildElement(pGroup);
            mCommon.pGroup = dynamic_cast<CLGroup*>(mCommon.pGroup->getElement(mCommon.pGroup->getNumElements() - 1));
          }
        else if (mCommon.pStyle != NULL)
          {
            mCommon.pStyle->setGroup(pGroup);
            mCommon.pGroup = mCommon.pStyle->getGroup();
          }
        else
          {
            assert(mCommon.pLineEnding != NULL);
            mCommon.pLineEnding->setGroup(pGroup);
            mCommon.pGroup = mCommon.pLineEnding->getGroup();
          }

        assert(mCommon.pGroup != NULL);
        // delete the group element again since the add/set methods made a copy
        delete pGroup;
        return;
        break;

        // a group can have many different children
      case GroupChild:

        // handle the possible children
        if (!strcmp(pszName, "Curve"))
          {
            mpCurrentHandler = new RenderCurveElement(mParser, mCommon);
          }
        else if (!strcmp(pszName, "Text"))
          {
            mpCurrentHandler = new TextElement(mParser, mCommon);
          }
        else if (!strcmp(pszName, "Rectangle"))
          {
            mpCurrentHandler = new RectangleElement(mParser, mCommon);
          }
        else if (!strcmp(pszName, "Polygon"))
          {
            mpCurrentHandler = new PolygonElement(mParser, mCommon);
          }
        else if (!strcmp(pszName, "Ellipse"))
          {
            mpCurrentHandler = new EllipseElement(mParser, mCommon);
          }
        else if (!strcmp(pszName, "Group"))
          {
            mpCurrentHandler = new GroupElement(mParser, mCommon);
          }
        else if (!strcmp(pszName, "Image"))
          {
            mpCurrentHandler = new ImageElement(mParser, mCommon);
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  if (mpCurrentHandler != NULL)
    {
      mParser.pushElementHandler(mpCurrentHandler);
    }

  mpCurrentHandler->start(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::GroupElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case Group:
      {
        if (strcmp(pszName, "Group"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Group", mParser.getCurrentLineNumber());

        assert(mCommon.pGroup != NULL);

        // if the group is part of another group, we have to set mCommon.pGroup
        // to that group, otherwise, we have to set it to NULL
        // a group is part of another group, if its grandFather is a group
        // (as group elements are stored in a separate vector)
        CCopasiContainer* parent = mCommon.pGroup->getObjectParent();
        CCopasiContainer* grandFather = (parent == NULL ? NULL : parent->getObjectParent());

        if (grandFather != NULL && dynamic_cast<CLGroup*>(grandFather) != NULL)
          {
            mCommon.pGroup = dynamic_cast<CLGroup*>(grandFather);
            //tell the handler where to continue

            mParser.popElementHandler();

            //reset handler
            mCurrentElement = Group;
            //call parent handler
            mParser.onEndElement(pszName);

            //no need to delete Handler (since it is the only one the destructor
            //will handle it)
            break;
          }
        else
          {
            if (dynamic_cast<CLStyle*>(parent) != NULL)
              {
                // if this group is the child of a style, we should set some default values on attributes
                // so that they are set explicitly
                if (!mCommon.pGroup->isSetStroke())
                  {
                    mCommon.pGroup->setStroke("none");
                  }

                if (!mCommon.pGroup->isSetStrokeWidth())
                  {
                    mCommon.pGroup->setStrokeWidth(0.0);
                  }

                if (!mCommon.pGroup->isSetFill())
                  {
                    mCommon.pGroup->setFillColor("none");
                  }

                if (!mCommon.pGroup->isSetFillRule())
                  {
                    mCommon.pGroup->setFillRule(CLGraphicalPrimitive2D::NONZERO);
                  }

                if (!mCommon.pGroup->isSetFontFamily())
                  {
                    mCommon.pGroup->setFontFamily("sans-serif");
                  }

                if (!mCommon.pGroup->isSetFontWeight())
                  {
                    mCommon.pGroup->setFontWeight(CLText::WEIGHT_NORMAL);
                  }

                if (!mCommon.pGroup->isSetFontStyle())
                  {
                    mCommon.pGroup->setFontStyle(CLText::STYLE_NORMAL);
                  }

                if (!mCommon.pGroup->isSetTextAnchor())
                  {
                    mCommon.pGroup->setTextAnchor(CLText::ANCHOR_START);
                  }

                if (!mCommon.pGroup->isSetVTextAnchor())
                  {
                    mCommon.pGroup->setVTextAnchor(CLText::ANCHOR_TOP);
                  }

                if (!mCommon.pGroup->isSetStartHead())
                  {
                    mCommon.pGroup->setStartHead("none");
                  }

                if (!mCommon.pGroup->isSetEndHead())
                  {
                    mCommon.pGroup->setEndHead("none");
                  }
              }

            mCommon.pGroup = NULL;
          }

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;
      }

      case GroupChild:

        // a group can have many different children
        if (strcmp(pszName, "Curve")
            && strcmp(pszName, "Text")
            && strcmp(pszName, "Rectangle")
            && strcmp(pszName, "Polygon")
            && strcmp(pszName, "Ellipse")
            && strcmp(pszName, "Group")
            && strcmp(pszName, "Image")
           )
          {
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "???", mParser.getCurrentLineNumber());
          }

        //tell the handler where to continue
        mCurrentElement = Group;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// Curve Element Element

CCopasiXMLParser::CurveElementElement::CurveElementElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::CurveElementElement::~CurveElementElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::CurveElementElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  const char * X;
  const char * Y;
  const char * Z;
  const char * BP1X;
  const char * BP1Y;
  const char * BP1Z;
  const char * BP2X;
  const char * BP2Y;
  const char * BP2Z;
  CLRenderPoint* pCurveElement = NULL;

  switch (mCurrentElement)
    {
      case CurveElement:

        if (strcmp(pszName, "Element"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Element", mParser.getCurrentLineNumber());

        X = mParser.getAttributeValue("x", papszAttrs);
        Y = mParser.getAttributeValue("y", papszAttrs);
        Z = mParser.getAttributeValue("z", papszAttrs, "0.0");
        BP1X = mParser.getAttributeValue("basePoint1_x", papszAttrs, false);
        BP1Y = mParser.getAttributeValue("basePoint1_y", papszAttrs, false);
        BP1Z = mParser.getAttributeValue("basePoint1_z", papszAttrs, "0.0");
        BP2X = mParser.getAttributeValue("basePoint2_x", papszAttrs, false);
        BP2Y = mParser.getAttributeValue("basePoint2_y", papszAttrs, false);
        BP2Z = mParser.getAttributeValue("basePoint2_z", papszAttrs, "0.0");

        // for a cubic bezier, x any y value for both basepoints are mandatory
        if (BP1X != NULL && BP1Y != NULL && BP2X != NULL && BP2Y != NULL)
          {
            pCurveElement = new CLRenderCubicBezier(CLRelAbsVector(BP1X), CLRelAbsVector(BP1Y), CLRelAbsVector(BP1Z),
                                                    CLRelAbsVector(BP2X), CLRelAbsVector(BP2Y), CLRelAbsVector(BP2Z),
                                                    CLRelAbsVector(X), CLRelAbsVector(Y), CLRelAbsVector(Z));
          }
        else
          {
            pCurveElement = new CLRenderPoint(CLRelAbsVector(X), CLRelAbsVector(Y), CLRelAbsVector(Z));
          }

        mCommon.pListOfCurveElements->push_back(pCurveElement);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::CurveElementElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case CurveElement:

        if (strcmp(pszName, "Element"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Element", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// LineEnding Element

CCopasiXMLParser::LineEndingElement::LineEndingElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::LineEndingElement::~LineEndingElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::LineEndingElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */
  mpCurrentHandler = NULL;

  const char * Id;
  const char * EnableRotationalMapping;
  CLLineEnding* pLineEnding = NULL;

  switch (mCurrentElement)
    {
      case LineEnding:

        if (strcmp(pszName, "LineEnding"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "LineEnding", mParser.getCurrentLineNumber());

        Id = mParser.getAttributeValue("id", papszAttrs);
        EnableRotationalMapping = mParser.getAttributeValue("enableRotationalMapping", papszAttrs, "true");
        pLineEnding = new CLLineEnding();
        pLineEnding->setId(Id);

        if (!strcmp(EnableRotationalMapping, "true"))
          {
            pLineEnding->setEnableRotationalMapping(true);
          }
        else
          {
            pLineEnding->setEnableRotationalMapping(false);
          }

        mCommon.pRenderInformation->addLineEnding(pLineEnding);
        // delete the line ending again since the addLineEnding method made a copy
        delete pLineEnding;
        assert(mCommon.pRenderInformation->getNumLineEndings() > 0);
        mCommon.pLineEnding = mCommon.pRenderInformation->getLineEnding(mCommon.pRenderInformation->getNumLineEndings() - 1);
        break;

      case BoundingBox:

        //only one type of tags may occur here, so we can throw an exception.
        //No need to silently ignore unknown tags here.
        if (strcmp(pszName, "BoundingBox"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "BoundingBox", mParser.getCurrentLineNumber());

        //only one type of tags may occur here, so if the handler exists
        //it must be the correct one
        if (!mpCurrentHandler)
          mpCurrentHandler = new BoundingBoxElement(mParser, mCommon);

        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      case Group:

        //only one type of tags may occur here, so we can throw an exception.
        //No need to silently ignore unknown tags here.
        if (strcmp(pszName, "Group"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Group", mParser.getCurrentLineNumber());

        //only one type of tags may occur here, so if the handler exists
        //it must be the correct one
        if (!mpCurrentHandler)
          mpCurrentHandler = new GroupElement(mParser, mCommon);

        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::LineEndingElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case LineEnding:

        if (strcmp(pszName, "LineEnding"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "LineEnding", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCommon.pLineEnding = NULL;

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case BoundingBox:

        if (strcmp(pszName, "BoundingBox"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "BoundingBox", mParser.getCurrentLineNumber());

        pdelete(mpCurrentHandler);
        break;

      case Group:

        if (strcmp(pszName, "Group"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Group", mParser.getCurrentLineNumber());

        //tell the handler where to continue
        mCurrentElement = LineEnding;
        pdelete(mpCurrentHandler);
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// GlobalStyle Element

CCopasiXMLParser::GlobalStyleElement::GlobalStyleElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::GlobalStyleElement::~GlobalStyleElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::GlobalStyleElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  const char * RoleList;
  const char * TypeList;
  CLGlobalStyle* pGlobalStyle = NULL;

  switch (mCurrentElement)
    {
      case GlobalStyle:

        if (strcmp(pszName, "Style"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Style", mParser.getCurrentLineNumber());

        RoleList = mParser.getAttributeValue("roleList", papszAttrs, false);
        TypeList = mParser.getAttributeValue("typeList", papszAttrs, false);
        pGlobalStyle = new CLGlobalStyle();

        if (RoleList != NULL)
          {
            std::set<std::string> s;
            CLStyle::readIntoSet(RoleList, s);
            pGlobalStyle->setRoleList(s);
          }

        if (TypeList != NULL)
          {
            std::set<std::string> s;
            CLStyle::readIntoSet(TypeList, s);
            pGlobalStyle->setTypeList(s);
          }

        assert(dynamic_cast<CLGlobalRenderInformation*>(mCommon.pRenderInformation) != NULL);
        static_cast<CLGlobalRenderInformation*>(mCommon.pRenderInformation)->addStyle(pGlobalStyle);
        // delete the line ending again since the addGlobalStyle method made a copy
        delete pGlobalStyle;
        assert(static_cast<CLGlobalRenderInformation*>(mCommon.pRenderInformation)->getNumStyles() > 0);
        mCommon.pStyle = static_cast<CLGlobalRenderInformation*>(mCommon.pRenderInformation)->getStyle(static_cast<CLGlobalRenderInformation*>(mCommon.pRenderInformation)->getNumStyles() - 1);
        break;

      case Group:

        //only one type of tags may occur here, so we can throw an exception.
        //No need to silently ignore unknown tags here.
        if (strcmp(pszName, "Group"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Group", mParser.getCurrentLineNumber());

        //only one type of tags may occur here, so if the handler exists
        //it must be the correct one
        if (!mpCurrentHandler)
          mpCurrentHandler = new GroupElement(mParser, mCommon);

        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::GlobalStyleElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case GlobalStyle:

        if (strcmp(pszName, "Style"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Style", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCommon.pStyle = NULL;

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case Group:

        if (strcmp(pszName, "Group"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Group", mParser.getCurrentLineNumber());

        //tell the handler where to continue
        mCurrentElement = GlobalStyle;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// LocalStyle Element

CCopasiXMLParser::LocalStyleElement::LocalStyleElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::LocalStyleElement::~LocalStyleElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::LocalStyleElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  const char * RoleList;
  const char * TypeList;
  const char * KeyList;
  CLLocalStyle* pLocalStyle = NULL;

  switch (mCurrentElement)
    {
      case LocalStyle:

        if (strcmp(pszName, "Style"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Style", mParser.getCurrentLineNumber());

        RoleList = mParser.getAttributeValue("roleList", papszAttrs, false);
        TypeList = mParser.getAttributeValue("typeList", papszAttrs, false);
        KeyList = mParser.getAttributeValue("keyList", papszAttrs, false);
        pLocalStyle = new CLLocalStyle();

        if (RoleList != NULL)
          {
            std::set<std::string> s;
            CLStyle::readIntoSet(RoleList, s);
            pLocalStyle->setRoleList(s);
          }

        if (TypeList != NULL)
          {
            std::set<std::string> s;
            CLStyle::readIntoSet(TypeList, s);
            pLocalStyle->setTypeList(s);
          }

        if (KeyList != NULL)
          {
            std::set<std::string> s;
            CLStyle::readIntoSet(KeyList, s);
            // we need to translate the keys from the file to the actual keys assigned now
            std::set<std::string> s_conv;
            std::set<std::string>::const_iterator keyIt = s.begin(), keyEndit = s.end();
            CLGraphicalObject* pGO = NULL;

            while (keyIt != keyEndit)
              {
                pGO = dynamic_cast<CLGraphicalObject *>(mCommon.KeyMap.get(*keyIt));
                assert(pGO);

                if (pGO != NULL)
                  {
                    s_conv.insert(pGO->getKey());
                  }

                ++keyIt;
              }

            pLocalStyle->setKeyList(s_conv);
          }

        assert(dynamic_cast<CLLocalRenderInformation*>(mCommon.pRenderInformation) != NULL);
        static_cast<CLLocalRenderInformation*>(mCommon.pRenderInformation)->addStyle(pLocalStyle);
        // delete the line ending again since the addLocalStyle method made a copy
        delete pLocalStyle;
        assert(static_cast<CLLocalRenderInformation*>(mCommon.pRenderInformation)->getNumStyles() > 0);
        mCommon.pStyle = static_cast<CLLocalRenderInformation*>(mCommon.pRenderInformation)->getStyle(static_cast<CLLocalRenderInformation*>(mCommon.pRenderInformation)->getNumStyles() - 1);
        break;

      case Group:

        //only one type of tags may occur here, so we can throw an exception.
        //No need to silently ignore unknown tags here.
        if (strcmp(pszName, "Group"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Group", mParser.getCurrentLineNumber());

        //only one type of tags may occur here, so if the handler exists
        //it must be the correct one
        if (!mpCurrentHandler)
          mpCurrentHandler = new GroupElement(mParser, mCommon);

        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::LocalStyleElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case LocalStyle:

        if (strcmp(pszName, "Style"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Style", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCommon.pStyle = NULL;

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case Group:

        if (strcmp(pszName, "Group"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Group", mParser.getCurrentLineNumber());

        //tell the handler where to continue
        mCurrentElement = LocalStyle;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// ListOfColorDefinitions

CCopasiXMLParser::ListOfColorDefinitionsElement::ListOfColorDefinitionsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfColorDefinitionsElement::~ListOfColorDefinitionsElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::ListOfColorDefinitionsElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfColorDefinitions:

        if (strcmp(pszName, "ListOfColorDefinitions"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfColorDefinitions", mParser.getCurrentLineNumber());

        break;

      case ColorDefinition:

        //only one type of tags may occur here, so we can throw an exception.
        //No need to silently ignore unknown tags here.
        if (strcmp(pszName, "ColorDefinition"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ColorDefinition", mParser.getCurrentLineNumber());

        //only one type of tags may occur here, so if the handler exists
        //it must be the correct one
        if (!mpCurrentHandler)
          mpCurrentHandler = new ColorDefinitionElement(mParser, mCommon);

        mParser.pushElementHandler(mpCurrentHandler);
        mpCurrentHandler->start(pszName, papszAttrs);
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfColorDefinitionsElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ListOfColorDefinitions:

        if (strcmp(pszName, "ListOfColorDefinitions"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfColorDefinitions", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case ColorDefinition:

        if (strcmp(pszName, "ColorDefinition"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ColorDefinition", mParser.getCurrentLineNumber());

        //tell the handler where to continue
        mCurrentElement = ListOfColorDefinitions;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// ListOfGradientDefinitions

CCopasiXMLParser::ListOfGradientDefinitionsElement::ListOfGradientDefinitionsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfGradientDefinitionsElement::~ListOfGradientDefinitionsElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::ListOfGradientDefinitionsElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfGradientDefinitions:

        if (strcmp(pszName, "ListOfGradientDefinitions"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfGradientDefinitions", mParser.getCurrentLineNumber());

        break;

      case GradientDefinition:

        //only one type of tags may occur here, so we can throw an exception.
        //No need to silently ignore unknown tags here.
        if (!strcmp(pszName, "RadialGradient"))
          {
            if (!mpCurrentHandler)
              mpCurrentHandler = new RadialGradientElement(mParser, mCommon);

            mParser.pushElementHandler(mpCurrentHandler);
            mpCurrentHandler->start(pszName, papszAttrs);
          }
        else if (!strcmp(pszName, "LinearGradient"))
          {
            if (!mpCurrentHandler)
              mpCurrentHandler = new LinearGradientElement(mParser, mCommon);

            mParser.pushElementHandler(mpCurrentHandler);
            mpCurrentHandler->start(pszName, papszAttrs);
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfGradientDefinitionsElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ListOfGradientDefinitions:

        if (strcmp(pszName, "ListOfGradientDefinitions"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfGradientDefinitions", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case GradientDefinition:

        if (strcmp(pszName, "LinearGradient") && strcmp(pszName, "RadialGradient"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "???", mParser.getCurrentLineNumber());

        //tell the handler where to continue
        mCurrentElement = ListOfGradientDefinitions;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// ListOfLineEndings

CCopasiXMLParser::ListOfLineEndingsElement::ListOfLineEndingsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfLineEndingsElement::~ListOfLineEndingsElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::ListOfLineEndingsElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfLineEndings:

        if (strcmp(pszName, "ListOfLineEndings"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfLineEndings", mParser.getCurrentLineNumber());

        break;

      case LineEnding:

        if (!strcmp(pszName, "LineEnding"))
          {
            if (!mpCurrentHandler)
              mpCurrentHandler = new LineEndingElement(mParser, mCommon);

            mParser.pushElementHandler(mpCurrentHandler);
            mpCurrentHandler->start(pszName, papszAttrs);
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfLineEndingsElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ListOfLineEndings:

        if (strcmp(pszName, "ListOfLineEndings"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfLineEndings", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case LineEnding:

        if (strcmp(pszName, "LineEnding"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "LineEnding", mParser.getCurrentLineNumber());

        //tell the handler where to continue
        mCurrentElement = ListOfLineEndings;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// ListOfLocalStyles

CCopasiXMLParser::ListOfLocalStylesElement::ListOfLocalStylesElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfLocalStylesElement::~ListOfLocalStylesElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::ListOfLocalStylesElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfLocalStyles:

        if (strcmp(pszName, "ListOfStyles"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfStyles", mParser.getCurrentLineNumber());

        break;

      case LocalStyle:

        if (!strcmp(pszName, "Style"))
          {
            if (!mpCurrentHandler)
              mpCurrentHandler = new LocalStyleElement(mParser, mCommon);

            mParser.pushElementHandler(mpCurrentHandler);
            mpCurrentHandler->start(pszName, papszAttrs);
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfLocalStylesElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ListOfLocalStyles:

        if (strcmp(pszName, "ListOfStyles"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfStyles", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case LocalStyle:

        if (strcmp(pszName, "Style"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Style", mParser.getCurrentLineNumber());

        //tell the handler where to continue
        mCurrentElement = ListOfLocalStyles;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// ListOfGlobalStyles

CCopasiXMLParser::ListOfGlobalStylesElement::ListOfGlobalStylesElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfGlobalStylesElement::~ListOfGlobalStylesElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::ListOfGlobalStylesElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfGlobalStyles:

        if (strcmp(pszName, "ListOfStyles"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfStyles", mParser.getCurrentLineNumber());

        break;

      case GlobalStyle:

        if (!strcmp(pszName, "Style"))
          {
            //only one type of tags may occur here, so if the handler exists
            //it must be the correct one
            if (!mpCurrentHandler)
              mpCurrentHandler = new GlobalStyleElement(mParser, mCommon);

            mParser.pushElementHandler(mpCurrentHandler);
            mpCurrentHandler->start(pszName, papszAttrs);
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfGlobalStylesElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ListOfGlobalStyles:

        if (strcmp(pszName, "ListOfStyles"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfStyles", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case GlobalStyle:

        if (strcmp(pszName, "Style"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Style", mParser.getCurrentLineNumber());

        //tell the handler where to continue
        mCurrentElement = ListOfGlobalStyles;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// ListOfCurveElements

CCopasiXMLParser::ListOfCurveElementsElement::ListOfCurveElementsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfCurveElementsElement::~ListOfCurveElementsElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::ListOfCurveElementsElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
      case ListOfCurveElements:

        if (strcmp(pszName, "ListOfElements"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "ListOfElements", mParser.getCurrentLineNumber());

        break;

      case CurveElement:

        //only one type of tags may occur here, so we can throw an exception.
        //No need to silently ignore unknown tags here.
        if (!strcmp(pszName, "Element"))
          {
            //only one type of tags may occur here, so if the handler exists
            //it must be the correct one
            if (!mpCurrentHandler)
              mpCurrentHandler = new CurveElementElement(mParser, mCommon);

            mParser.pushElementHandler(mpCurrentHandler);
            mpCurrentHandler->start(pszName, papszAttrs);
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::ListOfCurveElementsElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case ListOfCurveElements:

        if (strcmp(pszName, "ListOfElements"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfElements", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case CurveElement:

        if (strcmp(pszName, "Element"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Element", mParser.getCurrentLineNumber());

        //tell the handler where to continue
        mCurrentElement = ListOfCurveElements;

        //no need to delete Handler (since it is the only one the destructor
        //will handle it)
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

// GlobalRenderInformation Element

CCopasiXMLParser::GlobalRenderInformationElement::GlobalRenderInformationElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::GlobalRenderInformationElement::~GlobalRenderInformationElement()
{}

void CCopasiXMLParser::GlobalRenderInformationElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */
  mpCurrentHandler = NULL;
  const char* background;

  switch (mCurrentElement)
    {
      case GlobalRenderInformation:

        if (strcmp(pszName, "RenderInformation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "RenderInformation", mParser.getCurrentLineNumber());

        mCommon.pLayoutList->addGlobalRenderInformation(new CLGlobalRenderInformation());
        // delete the global render information again since the addGlobalRenderInformationObject method made a copy
        assert(mCommon.pLayoutList->getListOfGlobalRenderInformationObjects().size() > 0);
        mCommon.pRenderInformation = mCommon.pLayoutList->getListOfGlobalRenderInformationObjects()[mCommon.pLayoutList->getListOfGlobalRenderInformationObjects().size() - 1];
        background = mParser.getAttributeValue("backgroundColor", papszAttrs);
        assert(background != NULL);

        if (background != NULL)
          {
            mCommon.pRenderInformation->setBackgroundColor(background);
          }

        // we have to return here because otherwise the call
        // at the end will lead to an endless loop
        return;
        break;

      case ListOfColorDefinitions:

        if (!strcmp(pszName, "ListOfColorDefinitions"))
          {
            this->mLastKnownElement = ListOfColorDefinitions;
            mpCurrentHandler = new ListOfColorDefinitionsElement(mParser, mCommon);
          }

        break;

      case ListOfGradientDefinitions:

        if (!strcmp(pszName, "ListOfGradientDefinitions"))
          {
            this->mLastKnownElement = ListOfGradientDefinitions;
            mpCurrentHandler = new ListOfGradientDefinitionsElement(mParser, mCommon);
          }

        break;

      case ListOfLineEndings:

        if (!strcmp(pszName, "ListOfLineEndings"))
          {
            this->mLastKnownElement = ListOfLineEndings;
            mpCurrentHandler = new ListOfLineEndingsElement(mParser, mCommon);
          }

        break;

      case ListOfStyles:

        if (!strcmp(pszName, "ListOfStyles"))
          {
            this->mLastKnownElement = ListOfStyles;
            mpCurrentHandler = new ListOfGlobalStylesElement(mParser, mCommon);
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  // if we created a handler in this call, we add it to the stack
  if (this->mpCurrentHandler != NULL)
    {
      this->mParser.pushElementHandler(this->mpCurrentHandler);
    }

  // we call the current handler
  // if we created one, the new one will be called, otherwise
  // the one for ListOfLayouts should be the current one
  // and this method will be called again
  this->mParser.onStartElement(pszName, papszAttrs);
  return;
}

void CCopasiXMLParser::GlobalRenderInformationElement::end(const XML_Char * pszName)
{
  if (!strcmp(pszName, "RenderInformation"))
    {
      mParser.popElementHandler();
      mCommon.pRenderInformation = NULL;

      //reset handler
      mCurrentElement = START_ELEMENT;
      //call parent handler
      mParser.onEndElement(pszName);
    }
  else
    {
      switch (mCurrentElement)
        {

          case ListOfColorDefinitions:

            if (strcmp(pszName, "ListOfColorDefinitions"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                             pszName, "ListOfColorDefinitions", mParser.getCurrentLineNumber());

            deleteCurrentHandler();
            break;

          case ListOfGradientDefinitions:

            if (strcmp(pszName, "ListOfGradientDefinitions"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                             pszName, "ListOfGradientDefinitions", mParser.getCurrentLineNumber());

            deleteCurrentHandler();
            break;

          case ListOfLineEndings:

            if (strcmp(pszName, "ListOfLineEndings"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                             pszName, "ListOfLineEndings", mParser.getCurrentLineNumber());

            deleteCurrentHandler();
            break;

          case ListOfStyles:

            if (strcmp(pszName, "ListOfStyles"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                             pszName, "ListOfStyles", mParser.getCurrentLineNumber());

            deleteCurrentHandler();
            break;

          case UNKNOWN_ELEMENT:
            mCurrentElement = mLastKnownElement;
            break;

          default:
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "???", mParser.getCurrentLineNumber());
            break;
        }
    }

  return;
}

// LocalRenderInformation Element

CCopasiXMLParser::LocalRenderInformationElement::LocalRenderInformationElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::LocalRenderInformationElement::~LocalRenderInformationElement()
{}

void CCopasiXMLParser::LocalRenderInformationElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */
  mpCurrentHandler = NULL;
  const char* background;

  switch (mCurrentElement)
    {
      case LocalRenderInformation:

        if (strcmp(pszName, "RenderInformation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "RenderInformation", mParser.getCurrentLineNumber());

        mCommon.pCurrentLayout->addLocalRenderInformation(new CLLocalRenderInformation());
        // delete the global render information again since the addLocalRenderInformationObject method made a copy
        assert(mCommon.pCurrentLayout->getListOfLocalRenderInformationObjects().size() > 0);
        mCommon.pRenderInformation = mCommon.pCurrentLayout->getListOfLocalRenderInformationObjects()[mCommon.pCurrentLayout->getListOfLocalRenderInformationObjects().size() - 1];
        background = mParser.getAttributeValue("backgroundColor", papszAttrs);
        assert(background != NULL);

        if (background != NULL)
          {
            mCommon.pRenderInformation->setBackgroundColor(background);
          }

        // we have to return here because otherwise the call
        // at the end will lead to an endless loop
        return;
        break;

      case ListOfColorDefinitions:

        if (!strcmp(pszName, "ListOfColorDefinitions"))
          {
            this->mLastKnownElement = ListOfColorDefinitions;
            mpCurrentHandler = new ListOfColorDefinitionsElement(mParser, mCommon);
          }

        break;

      case ListOfGradientDefinitions:

        if (!strcmp(pszName, "ListOfGradientDefinitions"))
          {
            this->mLastKnownElement = ListOfGradientDefinitions;
            mpCurrentHandler = new ListOfGradientDefinitionsElement(mParser, mCommon);
          }

        break;

      case ListOfLineEndings:

        if (!strcmp(pszName, "ListOfLineEndings"))
          {
            this->mLastKnownElement = ListOfLineEndings;
            mpCurrentHandler = new ListOfLineEndingsElement(mParser, mCommon);
          }

        break;

      case ListOfStyles:

        if (!strcmp(pszName, "ListOfStyles"))
          {
            this->mLastKnownElement = ListOfStyles;
            mpCurrentHandler = new ListOfLocalStylesElement(mParser, mCommon);
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  // if we created a handler in this call, we add it to the stack
  if (mpCurrentHandler)
    {
      this->mParser.pushElementHandler(this->mpCurrentHandler);
    }

  // we call the current handler
  // if we created one, the new one will be called, otherwise
  // the one for ListOfLayouts should be the current one
  // and this method will be called again
  this->mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::LocalRenderInformationElement::end(const XML_Char * pszName)
{
  if (!strcmp(pszName, "RenderInformation"))
    {
      mParser.popElementHandler();
      mCommon.pRenderInformation = NULL;

      //reset handler
      mCurrentElement = START_ELEMENT;
      //call parent handler
      mParser.onEndElement(pszName);
    }
  else
    {
      switch (mCurrentElement)
        {
          case ListOfColorDefinitions:

            if (strcmp(pszName, "ListOfColorDefinitions"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                             pszName, "ListOfColorDefinitions", mParser.getCurrentLineNumber());

            deleteCurrentHandler();
            break;

          case ListOfGradientDefinitions:

            if (strcmp(pszName, "ListOfGradientDefinitions"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                             pszName, "ListOfGradientDefinitions", mParser.getCurrentLineNumber());

            deleteCurrentHandler();
            break;

          case ListOfLineEndings:

            if (strcmp(pszName, "ListOfLineEndings"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                             pszName, "ListOfLineEndings", mParser.getCurrentLineNumber());

            deleteCurrentHandler();
            break;

          case ListOfStyles:

            if (strcmp(pszName, "ListOfStyles"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                             pszName, "ListOfStyles", mParser.getCurrentLineNumber());

            deleteCurrentHandler();
            break;

          case UNKNOWN_ELEMENT:
            mCurrentElement = mLastKnownElement;
            break;

          default:
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "???", mParser.getCurrentLineNumber());
            break;
        }
    }

  return;
}

// BoundingBox Element

CCopasiXMLParser::BoundingBoxElement::BoundingBoxElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::BoundingBoxElement::~BoundingBoxElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::BoundingBoxElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */
  mpCurrentHandler = NULL;
  const char * X;
  const char * Y;
  const char * WIDTH;
  const char * HEIGHT;

  switch (mCurrentElement)
    {
      case BoundingBox:

        if (strcmp(pszName, "BoundingBox"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "BoundingBox", mParser.getCurrentLineNumber());

        break;

      case Position:

        if (!strcmp(pszName, "Position"))
          {
            X = mParser.getAttributeValue("x", papszAttrs);
            Y = mParser.getAttributeValue("y", papszAttrs);
            mCommon.pLineEnding->getBoundingBox()->setPosition(CLPoint(CCopasiXMLInterface::DBL(X), CCopasiXMLInterface::DBL(Y)));
          }

        break;

      case Dimensions:

        if (!strcmp(pszName, "Dimensions"))
          {
            WIDTH = mParser.getAttributeValue("width", papszAttrs);
            HEIGHT = mParser.getAttributeValue("height", papszAttrs);
            mCommon.pLineEnding->getBoundingBox()->setDimensions(CLDimensions(CCopasiXMLInterface::DBL(WIDTH), CCopasiXMLInterface::DBL(HEIGHT)));
          }

        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

void CCopasiXMLParser::BoundingBoxElement::end(const XML_Char * pszName)
{
  switch (mCurrentElement)
    {
      case BoundingBox:

        if (strcmp(pszName, "BoundingBox"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "BoundingBox", mParser.getCurrentLineNumber());

        mParser.popElementHandler();

        //reset handler
        mCurrentElement = START_ELEMENT;
        //call parent handler
        mParser.onEndElement(pszName);
        break;

      case Position:

        if (strcmp(pszName, "Position"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Position", mParser.getCurrentLineNumber());

        break;

      case Dimensions:

        if (strcmp(pszName, "Dimensions"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Dimensions", mParser.getCurrentLineNumber());

        mCurrentElement = BoundingBox;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

SCopasiXMLParserCommon::SCopasiXMLParserCommon():
  pVersion(NULL),
  pModel(NULL),
  CharacterData(),
  mAssignments(),
  pFunctionList(NULL),
  pFunction(NULL),
  pFunctionVariable(NULL),
  FunctionDescription(),
  mPredefinedFunction(),
  mFunctionParameterKeyMap(),
  mpExpression(NULL),
  mKey2ObjectiveFunction(),
  pReaction(NULL),
  pEvent(NULL),
  pEventAssignment(NULL),
  SourceParameterKeys(),
  KeyMap(),
  StateVariableList(),
  pTaskList(NULL),
  pReportList(NULL),
  pPlotList(NULL),
  pReport(NULL),
  pCurrentTask(NULL),
  pCurrentParameter(NULL),
  ParameterGroupStack(),
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
  //pAdditionalGO(NULL),
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
  pListOfCurveElements(NULL),
  mParameterGroupLevel(0),
  taskReferenceMap(),
  reportReferenceMap(),
  pGUI(NULL),
  pDataModel(NULL)
{}
