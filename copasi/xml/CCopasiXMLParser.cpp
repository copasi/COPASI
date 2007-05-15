// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/CCopasiXMLParser.cpp,v $
//   $Revision: 1.153 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/05/15 12:37:05 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CCopasiXMLParser class.
 * This class parses a Copasi XML file.
 *
 * Created for Copasi by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */

#include "copasi.h"

#include "CExpat.h"

#include "CCopasiXMLParser.h"
#include "CCopasiXMLInterface.h"
#include "utilities/CCopasiMessage.h"
#include "function/CFunction.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "report/CReportDefinitionVector.h"
#include "report/CReportDefinition.h"

#include "utilities/CVersion.h"
#include "utilities/CCopasiParameter.h"
#include "utilities/CCopasiParameterGroup.h"
#include "utilities/CSlider.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CMCATask.h"
#ifdef COPASI_SSA
#include "ssa/CSSATask.h"
#endif
#ifdef COPASI_TSS
#include "tss/CTSSTask.h"
#endif
#ifdef COPASI_DEBUG
# include "tssanalysis/CTSSATask.h"
#endif
#include "scan/CScanTask.h"
#include "elementaryFluxModes/CEFMTask.h"
#include "optimization/COptTask.h"
#include "parameterFitting/CFitTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "lyap/CLyapTask.h"
#include "sensitivities/CSensTask.h"
#include "plot/COutputDefinitionVector.h"
#include "plot/CPlotSpecification.h"
#include "plot/CPlotItem.h"
#include "CopasiDataModel/CCopasiDataModel.h"

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
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case TEMPLATE:
      if (strcmp(pszName, "TEMPLATE"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "TEMPLATE", mParser.getCurrentLineNumber());
      return;

    case etc:
      if (strcmp(pszName, "etc"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "etc", mParser.getCurrentLineNumber());

      /* If we do not have a etc element handler we create one. */
      if (!mpCurrentHandler)
        mpetcElement = new etcElement(mParser, mCommon);

      mpCurrentHandler = mpetcElement;
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

void CCopasiXMLParser::TEMPLATEElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
    case TEMPLATE:
      if (strcmp(pszName, "TEMPLATE"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "TEMPLATE", mParser.getCurrentLineNumber());
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case etc:
      if (strcmp(pszName, "etc"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "etc", mParser.getCurrentLineNumber());

      mCurrentElement = TEMPLATE;
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

#endif // COPASI_TEMPLATE

CCopasiXMLParser::CCopasiXMLParser(CVersion & version) :
    CExpat(),
    mCommon(),
    mElementHandlerStack(),
    mUnknownElement(*this, this->mCommon),
    mCharacterDataElement(*this, this->mCommon)
{
  create();

  mElementHandlerStack.push(new COPASIElement(*this, mCommon));

  //  mCommon.pParser = this;
  mCommon.pVersion = & version;
  mCommon.pModel = NULL;
  mCommon.pFunctionList = NULL;
  mCommon.pFunction = NULL;
  mCommon.pReportList = NULL;
  mCommon.pReport = NULL;
  mCommon.mParameterGroupLevel = -1;
  mCommon.pGUI = NULL;

  enableElementHandler(true);
}

CCopasiXMLParser::~CCopasiXMLParser() {}

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

void CCopasiXMLParser::setFunctionList(CCopasiVectorN< CEvaluationTree > * pFunctionList)
{mCommon.pFunctionList = pFunctionList;}

CCopasiVectorN< CEvaluationTree > * CCopasiXMLParser::getFunctionList() const
  {return mCommon.pFunctionList;}

void CCopasiXMLParser::setModel(CModel * pModel) {mCommon.pModel = pModel;}

CModel * CCopasiXMLParser::getModel() const
  {return mCommon.pModel;}

void CCopasiXMLParser::setReportList(CReportDefinitionVector * pReportList)
{mCommon.pReportList = pReportList;}

CReportDefinitionVector * CCopasiXMLParser::getReportList() const
  {return mCommon.pReportList;}

//Mrinmayee

void CCopasiXMLParser::setTaskList(CCopasiVectorN< CCopasiTask > * pTaskList)
{mCommon.pTaskList = pTaskList;}

CCopasiVectorN< CCopasiTask > * CCopasiXMLParser::getTaskList() const
  {return mCommon.pTaskList;}

void CCopasiXMLParser::setPlotList(COutputDefinitionVector * pPlotList)
{mCommon.pPlotList = pPlotList;}

COutputDefinitionVector * CCopasiXMLParser::getPlotList() const
  {return mCommon.pPlotList;}

void CCopasiXMLParser::setGUI(SCopasiXMLGUI * pGUI)
{mCommon.pGUI = pGUI;}

SCopasiXMLGUI * CCopasiXMLParser::getGUI() const
  {return mCommon.pGUI;}

const CCopasiParameterGroup * CCopasiXMLParser::getCurrentGroup() const
  {return dynamic_cast< const CCopasiParameterGroup * >(mCommon.pCurrentParameter);}

const CCopasiObject * CCopasiXMLParser::getObjectFromName(const std::string & cn) const
  {
    const CCopasiObject * pObject = NULL;
    CCopasiObjectName CN = CCopasiObjectName(cn).getRemainder();

    if (mCommon.pModel &&
        (pObject = mCommon.pModel->getObject(CN))) return pObject;

    if (mCommon.pTaskList &&
        (pObject = mCommon.pTaskList->getObject(CN))) return pObject;

    if (mCommon.pFunctionList &&
        (pObject = mCommon.pFunctionList->getObject(CN))) return pObject;

    return NULL;
  }

CCopasiXMLParser::UnknownElement::UnknownElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::UnknownElement::~UnknownElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::UnknownElement::start(const XML_Char * /* pszName */,
    const XML_Char ** /* papszAttrs */)
{
  /* We count the level of subelements of the Unknown Elelement */
  mCurrentElement++;
  if (!mCurrentElement) mLineNumber = mParser.getCurrentLineNumber();
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
        CCopasiMessage(CCopasiMessage::RAW, MCXML + 3,
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

CCopasiXMLParser::COPASIElement::~COPASIElement() {pdelete(mpCurrentHandler);}

void CCopasiXMLParser::COPASIElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  const char * versionMajor;
  C_INT32 VersionMajor;
  const char * versionMinor;
  C_INT32 VersionMinor;
  const char * versionDevel;
  C_INT32 VersionDevel;

  switch (mCurrentElement)
    {
    case COPASI:
      if (strcmp(pszName, "COPASI"))
        {
          // We may have a configuration file which starts with a parameter group
          if (strcmp(pszName, "ParameterGroup"))
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                           pszName, "COPASI", mParser.getCurrentLineNumber());

          mpCurrentHandler = new ParameterGroupElement(mParser, mCommon);
          break;
        }

      versionMajor = mParser.getAttributeValue("versionMajor", papszAttrs, "0");
      VersionMajor = atoi(versionMajor);
      versionMinor = mParser.getAttributeValue("versionMinor", papszAttrs, "0");
      VersionMinor = atoi(versionMinor);
      versionDevel = mParser.getAttributeValue("versionDevel", papszAttrs, "0");
      VersionDevel = atoi(versionDevel);

      mCommon.pVersion->setVersion(VersionMajor, VersionMinor, VersionDevel, "");

      return;

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
        if (mCommon.pGUI)
          mpCurrentHandler = new GUIElement(mParser, mCommon);
        else
          mParser.pushElementHandler(&mParser.mUnknownElement);
      break;

    case SBMLReference:
      if (!strcmp(pszName, "SBMLReference"))
        mpCurrentHandler = new SBMLReferenceElement(mParser, mCommon);
      break;

    default:
      mParser.pushElementHandler(&mParser.mUnknownElement);
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
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;
    }
  else
    pdelete(mpCurrentHandler);

  return;
}

CCopasiXMLParser::ListOfFunctionsElement::ListOfFunctionsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfFunctionsElement::~ListOfFunctionsElement()
{
  pdelete(mpCurrentHandler);
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
        mCommon.pFunctionList = new CCopasiVectorN< CEvaluationTree >;
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
        unsigned C_INT32 i, imax = mCommon.pFunctionList->size();
        for (i = imax - 1; i != C_INVALID_INDEX; i--)
          {
            CFunction * pFunction =
              dynamic_cast<CFunction *>((*mCommon.pFunctionList)[i]);

            if (pFunction && !pFunction->compile())
              {
                CCopasiMessage(CCopasiMessage::RAW, MCXML + 6,
                               pFunction->getObjectName().c_str(),
                               mParser.getCurrentLineNumber());
                mCommon.pFunctionList->CCopasiVector< CEvaluationTree >::remove(i);
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
  const char * Key;
  const char * type;
  CEvaluationTree::Type Type;
  const char * Name;
  const char * Reversible;
  unsigned C_INT32 index;
  CFunction * pFunction;

  mpCurrentHandler = NULL;
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case Function:
      if (strcmp(pszName, "Function"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Function", mParser.getCurrentLineNumber());

      Key = mParser.getAttributeValue("key", papszAttrs);
      Name = mParser.getAttributeValue("name", papszAttrs);
      type = mParser.getAttributeValue("type", papszAttrs);
      Type = (CEvaluationTree::Type)toEnum(type, CEvaluationTree::XMLType);
      Reversible = mParser.getAttributeValue("reversible", papszAttrs, false);
      if (!Reversible) // We may have an old file format using positive
        Reversible = mParser.getAttributeValue("positive", papszAttrs, false);

      mCommon.mExistingFunction = false;
      mCommon.pFunction = CEvaluationTree::create(Type);
      pFunction = dynamic_cast<CFunction *>(mCommon.pFunction);

      mCommon.pFunction->setObjectName(Name);

      if (pFunction)
        {
          if (!strcmp(Reversible, "true"))
            pFunction->setReversible(TriTrue);
          else if (!strcmp(Reversible, "false"))
            pFunction->setReversible(TriFalse);
          else
            pFunction->setReversible(TriUnspecified);
        }

      /* We have a new function and add it to the list */
      index = mCommon.pFunctionList->getIndex(Name);
      if (index != C_INVALID_INDEX) // A function with that name exists.
        {
          switch ((*mCommon.pFunctionList)[index]->getType())
            {
            case CEvaluationTree::MassAction:
              if (Type == CEvaluationTree::MassAction)
                {
                  pdelete(mCommon.pFunction);
                  mCommon.pFunction = (*mCommon.pFunctionList)[index];
                  mCommon.mExistingFunction = true;
                }
              else
                {
                  std::string tmp(Name);
                  tmp += "[" + CEvaluationTree::TypeName[Type] + "]";
                  index = mCommon.pFunctionList->getIndex(tmp);
                  if (index != C_INVALID_INDEX)
                    mCommon.pFunctionList->remove(tmp);

                  mCommon.pFunction->setObjectName(tmp);
                  mCommon.pFunctionList->add(mCommon.pFunction, true);
                }
              break;

            case CEvaluationTree::PreDefined:
              if (Type == CEvaluationTree::PreDefined)
                {
                  pdelete(mCommon.pFunction);
                  mCommon.pFunction = (*mCommon.pFunctionList)[index];
                  mCommon.mExistingFunction = true;
                }
              else
                {
                  std::string tmp(Name);
                  tmp += "[" + CEvaluationTree::TypeName[Type] + "]";
                  index = mCommon.pFunctionList->getIndex(tmp);
                  if (index != C_INVALID_INDEX)
                    mCommon.pFunctionList->remove(tmp);

                  mCommon.pFunction->setObjectName(tmp);
                  mCommon.pFunctionList->add(mCommon.pFunction, true);
                }
              break;

            case CEvaluationTree::UserDefined:
            case CEvaluationTree::Function:
            case CEvaluationTree::Expression:
              mCommon.pFunctionList->remove(Name);
              mCommon.pFunctionList->add(mCommon.pFunction, true);
              break;
            }
        }
      else
        mCommon.pFunctionList->add(mCommon.pFunction, true);

      mCommon.KeyMap.addFix(Key , mCommon.pFunction);
      return;

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
      mLastKnownElement = mCurrentElement - 1;
      mCurrentElement = UNKNOWN_ELEMENT;
      mpCurrentHandler = &mParser.mUnknownElement;
      break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);
}

void CCopasiXMLParser::FunctionElement::end(const XML_Char *pszName)
{
  // It is possible that we have an Expression but no ListOfParameterDescriptions,
  // i.e., mCurrentElement = Expression and pszName = Function may occur
  // and is valid.
  if (mCurrentElement == Expression && !strcmp(pszName, "Function"))
    mCurrentElement = Function;

  if (mCurrentElement == MathML && !strcmp(pszName, "Function"))
    mCurrentElement = Function;

  switch (mCurrentElement)
    {
    case Function:
      if (strcmp(pszName, "Function"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "Function", mParser.getCurrentLineNumber());

      mCurrentElement = START_ELEMENT;
      mParser.popElementHandler();

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Expression:
      if (strcmp(pszName, "Expression"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "Expression", mParser.getCurrentLineNumber());
      if (!mCommon.mExistingFunction)
        mCommon.pFunction->setInfix(mCommon.CharacterData);

      mCurrentElement = Expression;
      break;

    case ListOfParameterDescriptions:
      if (strcmp(pszName, "ListOfParameterDescriptions"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "ListOfParameterDescriptions", mParser.getCurrentLineNumber());
      mCurrentElement = Function;
      break;

    case MathML:
      if (strcmp(pszName, "MathML"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "MathML", mParser.getCurrentLineNumber());
      if (!mCommon.mExistingFunction)
        mCommon.pFunction->setInfix(mCommon.FunctionDescription);

      mCurrentElement = Expression;
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

CCopasiXMLParser::MathMLElement::MathMLElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::MathMLElement::~MathMLElement()
{
  pdelete(mpCurrentHandler);
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
      mCommon.FunctionDescription = mCommon.CharacterData;
      mCommon.CharacterData = "";
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
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::ListOfParameterDescriptionsElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case ListOfParameterDescriptions:
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
  pdelete(mpCurrentHandler);
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
      MinOccurs = atoi(minOccurs);

      maxOccurs = mParser.getAttributeValue("maxOccurs", papszAttrs , "1");
      if ("unbounded" == maxOccurs) MaxOccurs = (unsigned C_INT32) - 1;
      else MaxOccurs = atoi(maxOccurs);

      if (mCommon.mExistingFunction)
        {
          mCommon.KeyMap.addFix(Key, pFunction->getVariables()[Name]);
        }
      else
        {
          // If we are here we have a user defined function.
          // We need to check whether the variable exists within the function.
          CFunctionParameter::DataType DataType;
          unsigned C_INT32 Index =
            pFunction->getVariables().findParameterByName(Name, DataType);

          if (Index == C_INVALID_INDEX)
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 8, Name,
                           pFunction->getObjectName().c_str(),
                           mParser.getCurrentLineNumber());

          if (Order >= pFunction->getVariables().size())
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 12, Order, Name,
                           pFunction->getObjectName().c_str(),
                           mParser.getCurrentLineNumber());

          // Assure that the order is correct
          if (Order != Index)
            pFunction->getVariables().swap(Order, Index);

          pParm = pFunction->getVariables()[Order];
          pParm->setObjectName(Name);
          pParm->setUsage(Role);

          if (MaxOccurs == 1 && MinOccurs == 1)
            pParm->setType(CFunctionParameter::FLOAT64);
          else
            pParm->setType(CFunctionParameter::VFLOAT64);

          mCommon.KeyMap.addFix(Key, pParm);
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
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::ModelElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * Key;
  const char * Name;
  const char * timeUnit;
  CModel::TimeUnit TimeUnit;
  const char * volumeUnit;
  CModel::VolumeUnit VolumeUnit;
  const char * quantityUnit;
  CModel::QuantityUnit QuantityUnit;
  const char * StateVariable;
  CModel::ModelType ModelType;
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case Model:
      if (strcmp(pszName, "Model"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Model", mParser.getCurrentLineNumber());

      Key = mParser.getAttributeValue("key", papszAttrs);
      Name = mParser.getAttributeValue("name", papszAttrs);

      timeUnit = mParser.getAttributeValue("timeUnit", papszAttrs);
      TimeUnit =
        (CModel::TimeUnit)toEnum(timeUnit, CModel::TimeUnitNames);
      if (TimeUnit == -1)
        {
          if (strcmp(timeUnit, "m"))
            fatalError();

          TimeUnit = CModel::min;
        }

      volumeUnit = mParser.getAttributeValue("volumeUnit", papszAttrs);
      VolumeUnit =
        (CModel::VolumeUnit)toEnum(volumeUnit, CModel::VolumeUnitNames);
      if (VolumeUnit == -1) fatalError();

      quantityUnit = mParser.getAttributeValue("quantityUnit", papszAttrs);
      QuantityUnit =
        (CModel::QuantityUnit) toEnum(quantityUnit, CModel::QuantityUnitNames);
      if (QuantityUnit == -1)
        QuantityUnit =
          (CModel::QuantityUnit) toEnum(quantityUnit, CModel::QuantityUnitOldXMLNames);
      if (QuantityUnit == -1) fatalError();

      ModelType = (CModel::ModelType)
                  toEnum(mParser.getAttributeValue("type", papszAttrs, "deterministic"), CModel::ModelTypeNames);
      if (ModelType == -1) fatalError();

      StateVariable = mParser.getAttributeValue("stateVariable", papszAttrs, "");

      if (!mCommon.pModel) mCommon.pModel = new CModel();
      mCommon.KeyMap.addFix(Key, mCommon.pModel);
      mCommon.pModel->setTitle(Name);
      mCommon.pModel->setTimeUnit(TimeUnit);
      mCommon.pModel->setVolumeUnit(VolumeUnit);
      mCommon.pModel->setQuantityUnit(QuantityUnit);
      mCommon.pModel->setModelType(ModelType);
      return;
      break;

    case Comment:
      if (!strcmp(pszName, "Comment"))
        mpCurrentHandler = new CommentElement(mParser, mCommon);
      break;

    case ListOfCompartments:
      if (!strcmp(pszName, "ListOfCompartments"))
        mpCurrentHandler = new ListOfCompartmentsElement(mParser, mCommon);
      break;

    case ListOfMetabolites:
      if (!strcmp(pszName, "ListOfMetabolites"))
        mpCurrentHandler = new ListOfMetabolitesElement(mParser, mCommon);
      break;

    case ListOfModelValues:
      if (!strcmp(pszName, "ListOfModelValues"))
        mpCurrentHandler = new ListOfModelValuesElement(mParser, mCommon);
      break;

    case ListOfReactions:
      if (!strcmp(pszName, "ListOfReactions"))
        mpCurrentHandler = new ListOfReactionsElement(mParser, mCommon);
      break;

    case StateTemplate:
      if (!strcmp(pszName, "StateTemplate"))
        mpCurrentHandler = new StateTemplateElement(mParser, mCommon);
      break;

    case InitialState:
      if (!strcmp(pszName, "InitialState"))
        mpCurrentHandler = new InitialStateElement(mParser, mCommon);
      break;

    default:
      mLastKnownElement = mCurrentElement - 1;
      mCurrentElement = UNKNOWN_ELEMENT;
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
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
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Comment:
      if (strcmp(pszName, "Comment"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "Comment", mParser.getCurrentLineNumber());

      mCommon.pModel->setComments(mCommon.CharacterData);
      mCommon.CharacterData = "";

      pdelete(mpCurrentHandler);
      break;

    case ListOfCompartments:
      if (strcmp(pszName, "ListOfCompartments"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "ListOfCompartments", mParser.getCurrentLineNumber());
      pdelete(mpCurrentHandler);
      break;

    case ListOfMetabolites:
      if (strcmp(pszName, "ListOfMetabolites"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "ListOfMetabolites", mParser.getCurrentLineNumber());
      pdelete(mpCurrentHandler);
      break;

    case ListOfModelValues:
      if (strcmp(pszName, "ListOfModelValues"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "ListOfModelValues", mParser.getCurrentLineNumber());
      pdelete(mpCurrentHandler);
      break;

    case ListOfReactions:
      if (strcmp(pszName, "ListOfReactions"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "ListOfReactions", mParser.getCurrentLineNumber());
      pdelete(mpCurrentHandler);
      break;

    case StateTemplate:
      if (strcmp(pszName, "StateTemplate"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "StateTemplate", mParser.getCurrentLineNumber());
      pdelete(mpCurrentHandler);
      break;

    case InitialState:
      if (strcmp(pszName, "InitialState"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "InitialState", mParser.getCurrentLineNumber());
      pdelete(mpCurrentHandler);
      mCurrentElement = Model;
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

CCopasiXMLParser::CommentElement::CommentElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
    mXhtml(),
    mLevel(0)
{}

CCopasiXMLParser::CommentElement::~CommentElement()
{
  pdelete(mpCurrentHandler);
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

      pdelete(mpCurrentHandler);

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
  pdelete(mpCurrentHandler);
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
      mCommon.pModel->getCompartments().resize(0);
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
  const char * Key;
  const char * Name;
  const char * simulationType;
  CModelEntity::Status SimulationType;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case Compartment:
      if (strcmp(pszName, "Compartment"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Compartment", mParser.getCurrentLineNumber());

      Key = mParser.getAttributeValue("key", papszAttrs);
      Name = mParser.getAttributeValue("name", papszAttrs);
      simulationType = mParser.getAttributeValue("simulationType", papszAttrs, "fixed");
      SimulationType = (CModelEntity::Status)toEnum(simulationType, CModelEntity::XMLStatus);

      mpCompartment = new CCompartment();
      mCommon.KeyMap.addFix(Key, mpCompartment);

      mpCompartment->setObjectName(Name);
      mpCompartment->setStatus(SimulationType);

      mCommon.pModel->getCompartments().add(mpCompartment, true);
      return;

    case Expression:
      if (!strcmp(pszName, "Expression"))
        mpCurrentHandler = &mParser.mCharacterDataElement;
      break;

    case InitialExpression:
      if (!strcmp(pszName, "InitialExpression"))
        mpCurrentHandler = &mParser.mCharacterDataElement;
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

void CCopasiXMLParser::CompartmentElement::end(const XML_Char *pszName)
{
  // It is possible that we have an Expression but no InitialExpression,
  // i.e., mCurrentElement = Expression and pszName = Compartment may occur
  // and is valid.
  if (mCurrentElement == Expression && !strcmp(pszName, "Compartment"))
    mCurrentElement = Compartment;

  switch (mCurrentElement)
    {
    case Compartment:
      if (strcmp(pszName, "Compartment"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "Compartment", mParser.getCurrentLineNumber());
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Expression:
      if (strcmp(pszName, "Expression"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "Expression", mParser.getCurrentLineNumber());
      mpCompartment->setExpression(mCommon.CharacterData);

      // Remove error messages created by setExpression as this may fail
      // due to incomplete model specification at this time.
      if (CCopasiMessage::peekLastMessage().getNumber() == MCFunction + 3)
        CCopasiMessage::getLastMessage();
      break;

    case InitialExpression:
      if (strcmp(pszName, "InitialExpression"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "InitialExpression", mParser.getCurrentLineNumber());
      mpCompartment->setInitialExpression(mCommon.CharacterData);

      // Remove error messages created by setExpression as this may fail
      // due to incomplete model specification at this time.
      if (CCopasiMessage::peekLastMessage().getNumber() == MCFunction + 3)
        CCopasiMessage::getLastMessage();

      mCurrentElement = Compartment;
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

CCopasiXMLParser::ListOfMetabolitesElement::ListOfMetabolitesElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfMetabolitesElement::~ListOfMetabolitesElement()
{
  pdelete(mpCurrentHandler);
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
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::MetaboliteElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  CCompartment * pCompartment = NULL;
  const char * Key;
  const char * Name;
  const char * simulationType;
  CModelEntity::Status SimulationType;
  const char reactions[] = "reactions";
  const char * Compartment;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case Metabolite:
      if (strcmp(pszName, "Metabolite"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Metabolite", mParser.getCurrentLineNumber());

      Key = mParser.getAttributeValue("key", papszAttrs);
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

      SimulationType = (CModelEntity::Status)toEnum(simulationType, CModelEntity::XMLStatus);
      Compartment = mParser.getAttributeValue("compartment", papszAttrs);

      mpMetabolite = new CMetab();
      mCommon.KeyMap.addFix(Key, mpMetabolite);
      mpMetabolite->setObjectName(Name);
      mpMetabolite->setStatus(SimulationType);

      pCompartment =
        dynamic_cast< CCompartment* >(mCommon.KeyMap.get(Compartment));

      if (!pCompartment) fatalError();

      pCompartment->addMetabolite(mpMetabolite);
      mCommon.pModel->getMetabolites().add(mpMetabolite);
      return;

    case Expression:
      if (!strcmp(pszName, "Expression"))
        mpCurrentHandler = &mParser.mCharacterDataElement;
      break;

    case InitialExpression:
      if (!strcmp(pszName, "InitialExpression"))
        mpCurrentHandler = &mParser.mCharacterDataElement;
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

void CCopasiXMLParser::MetaboliteElement::end(const XML_Char *pszName)
{
  // It is possible that we have an Expression but no InitialExpression,
  // i.e., mCurrentElement = Expression and pszName = Metabolite may occur
  // and is valid.
  if (mCurrentElement == Expression && !strcmp(pszName, "Metabolite"))
    mCurrentElement = Metabolite;

  switch (mCurrentElement)
    {
    case Metabolite:
      if (strcmp(pszName, "Metabolite"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "Metabolite", mParser.getCurrentLineNumber());
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Expression:
      if (strcmp(pszName, "Expression"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "Expression", mParser.getCurrentLineNumber());
      mpMetabolite->setExpression(mCommon.CharacterData);

      // Remove error messages created by setExpression as this may fail
      // due to incomplete model specification at this time.
      if (CCopasiMessage::peekLastMessage().getNumber() == MCFunction + 3)
        CCopasiMessage::getLastMessage();
      break;

    case InitialExpression:
      if (strcmp(pszName, "InitialExpression"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "InitialExpression", mParser.getCurrentLineNumber());
      mpMetabolite->setInitialExpression(mCommon.CharacterData);

      // Remove error messages created by setExpression as this may fail
      // due to incomplete model specification at this time.
      if (CCopasiMessage::peekLastMessage().getNumber() == MCFunction + 3)
        CCopasiMessage::getLastMessage();

      mCurrentElement = Metabolite;
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

CCopasiXMLParser::ListOfModelValuesElement::ListOfModelValuesElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfModelValuesElement::~ListOfModelValuesElement()
{
  pdelete(mpCurrentHandler);
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
    mpMathMLElement(NULL)
{}

CCopasiXMLParser::ModelValueElement::~ModelValueElement()
{
  pdelete(mpMathMLElement);
}

void CCopasiXMLParser::ModelValueElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * Key;
  const char * Name;
  const char * simulationType;
  CModelEntity::Status SimulationType;

  mpCurrentHandler = NULL;
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case ModelValue:
      if (strcmp(pszName, "ModelValue"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "ModelValue", mParser.getCurrentLineNumber());

      Key = mParser.getAttributeValue("key", papszAttrs);
      Name = mParser.getAttributeValue("name", papszAttrs);
      simulationType = mParser.getAttributeValue("simulationType", papszAttrs, false);

      // We need to handle old files which used the attribute status.
      if (!simulationType)
        {
          simulationType = mParser.getAttributeValue("status", papszAttrs, false);
          if (!simulationType) // status and simulationType are both missing
            simulationType = mParser.getAttributeValue("simulationType", papszAttrs);
        }

      SimulationType = (CModelEntity::Status)toEnum(simulationType, CModelEntity::XMLStatus);

      mpMV = new CModelValue();
      mCommon.KeyMap.addFix(Key, mpMV);
      mpMV->setObjectName(Name);
      mpMV->setStatus(SimulationType);

      mCommon.pModel->getModelValues().add(mpMV, true);
      return;

    case Expression:
      if (!strcmp(pszName, "Expression"))
        mpCurrentHandler = &mParser.mCharacterDataElement;
      break;

    case InitialExpression:
      if (!strcmp(pszName, "InitialExpression"))
        mpCurrentHandler = &mParser.mCharacterDataElement;
      break;

    case MathML:       // Old file format support
      if (!strcmp(pszName, "MathML"))
        {
          /* If we do not have a MathML element handler we create one. */
          if (!mpMathMLElement)
            mpMathMLElement = new MathMLElement(mParser, mCommon);

          mpCurrentHandler = mpMathMLElement;
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

void CCopasiXMLParser::ModelValueElement::end(const XML_Char *pszName)
{
  // It is possible that we have an Expression but no InitialExpression,
  // i.e., mCurrentElement = Expression and pszName = ModelValue may occur
  // and is valid.
  if (mCurrentElement == Expression && !strcmp(pszName, "ModelValue"))
    mCurrentElement = ModelValue;

  switch (mCurrentElement)
    {
    case ModelValue:
      if (strcmp(pszName, "ModelValue"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "ModelValue", mParser.getCurrentLineNumber());
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Expression:
      if (strcmp(pszName, "Expression"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "Expression", mParser.getCurrentLineNumber());
      mpMV->setExpression(mCommon.CharacterData);

      // Remove error messages created by setExpression as this may fail
      // due to incomplete model specification at this time.
      if (CCopasiMessage::peekLastMessage().getNumber() == MCFunction + 3)
        CCopasiMessage::getLastMessage();
      break;

    case InitialExpression:
      if (strcmp(pszName, "InitialExpression"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "InitialExpression", mParser.getCurrentLineNumber());
      mpMV->setInitialExpression(mCommon.CharacterData);

      // Remove error messages created by setExpression as this may fail
      // due to incomplete model specification at this time.
      if (CCopasiMessage::peekLastMessage().getNumber() == MCFunction + 3)
        CCopasiMessage::getLastMessage();

      mCurrentElement = ModelValue;
      break;

    case MathML:       // Old file format support
      if (strcmp(pszName, "MathML"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "MathML", mParser.getCurrentLineNumber());
      mpMV->setExpression(mCommon.FunctionDescription);

      // Remove error messages created by setExpression as this may fail
      // due to incomplete model specification at this time.
      if (CCopasiMessage::peekLastMessage().getNumber() == MCFunction + 3)
        CCopasiMessage::getLastMessage();

      mCurrentElement = ModelValue;
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
  pdelete(mpCurrentHandler);
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
      mCommon.pModel->getReactions().resize(0);
      break;

    case Reaction:
      if (strcmp(pszName, "Reaction"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Reaction", mParser.getCurrentLineNumber());

      /* If we do not have a function element handler we create one. */
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
  const char * Key;
  const char * Name;
  const char * Compartment; // Default Compartment_00
  const char * reversible;
  bool Reversible;
  const char * SBMLId;

  mCurrentElement++; /* We should always be on the next element */
  mpCurrentHandler = NULL;

  switch (mCurrentElement)
    {
    case Reaction:
      if (strcmp(pszName, "Reaction"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Reaction", mParser.getCurrentLineNumber());
      Key = mParser.getAttributeValue("key", papszAttrs);
      Name = mParser.getAttributeValue("name", papszAttrs);
      Compartment = mParser.getAttributeValue("compartment", papszAttrs,
                                              "Compartment_00");

      reversible = mParser.getAttributeValue("reversible", papszAttrs);
      Reversible = mParser.toBool(reversible);

      mCommon.pReaction = new CReaction();
      mCommon.KeyMap.addFix(Key, mCommon.pReaction);
      mCommon.pReaction->setObjectName(Name);
      mCommon.pReaction->setReversible(Reversible);
      SBMLId = mParser.getAttributeValue("sbmlid", papszAttrs, "");
      if (SBMLId != "")
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

      return;
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
      mLastKnownElement = mCurrentElement - 1;
      mCurrentElement = UNKNOWN_ELEMENT;
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
      break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::ReactionElement::end(const XML_Char *pszName)
{
  if (!strcmp(pszName, "Reaction"))
    mCurrentElement = Reaction;

  switch (mCurrentElement)
    {
    case Reaction:
      if (strcmp(pszName, "Reaction"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "Reaction", mParser.getCurrentLineNumber());
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
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
      mCurrentElement = Reaction;
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

CCopasiXMLParser::ListOfSubstratesElement::ListOfSubstratesElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfSubstratesElement::~ListOfSubstratesElement()
{
  pdelete(mpCurrentHandler);
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
  pdelete(mpCurrentHandler);
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
  pdelete(mpCurrentHandler);
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
  pdelete(mpCurrentHandler);
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
  pdelete(mpCurrentHandler);
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
  pdelete(mpCurrentHandler);
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
  pdelete(mpCurrentHandler);
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
  pdelete(mpCurrentHandler);
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

      mCommon.KeyMap.addFix(Key,
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
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::KineticLawElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * Function;
  CFunction * pFunction;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case KineticLaw:
      if (strcmp(pszName, "KineticLaw"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "KineticLaw", mParser.getCurrentLineNumber());

      Function = mParser.getAttributeValue("function", papszAttrs);

      pFunction =
        dynamic_cast< CFunction* >(mCommon.KeyMap.get(Function));

      if (!pFunction)
        {
          CCopasiMessage(CCopasiMessage::RAW, MCXML + 7, Function,
                         mCommon.pReaction->getObjectName().c_str(),
                         mParser.getCurrentLineNumber());
          pFunction = CCopasiDataModel::Global->mpUndefined;
        }

      mCommon.pReaction->setFunction(pFunction);
      break;

    case ListOfCallParameters:
      if (strcmp(pszName, "ListOfCallParameters"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "ListOfCallParameters", mParser.getCurrentLineNumber());

      if (mCommon.pReaction->getFunction() == CCopasiDataModel::Global->mpUndefined)
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
      if (mCommon.pReaction->getFunction() == CCopasiDataModel::Global->mpUndefined)
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
  pdelete(mpCurrentHandler);
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
  pdelete(mpCurrentHandler);
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

      mpFunctionParameter =
        dynamic_cast< CFunctionParameter* >(mCommon.KeyMap.get(FunctionParameter));
      if (!mpFunctionParameter) fatalError();

      mCommon.SourceParameterKeys.clear();
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
      if (mCommon.SourceParameterKeys.size() > 0)
        {
          mCommon.pReaction->
          setParameterMappingVector(mpFunctionParameter->getObjectName(),
                                    mCommon.SourceParameterKeys);
          mCommon.SourceParameterKeys.clear();
        }

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
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::SourceParameterElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  const char * Reference;
  CCopasiObject * pObject;
  CCopasiParameter * pParameter;
  CModel * pModel;
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
        mCommon.SourceParameterKeys.push_back(pParameter->getKey());
      else if ((pME = dynamic_cast<CModelEntity*>(pObject)))
        mCommon.SourceParameterKeys.push_back(pME->getKey());
      else if ((pModel = dynamic_cast<CModel *>(pObject)))
        mCommon.SourceParameterKeys.push_back(pModel->getKey());
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
  pdelete(mpCurrentHandler);
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
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::StateTemplateVariableElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  // const char * Key;
  const char * ObjectReference;
  CCopasiObject * pObject;
  //CMetab * pMetabolite;
  //CCompartment * pCompartment;
  //CModelValue * pMV;
  CModelEntity * pME;
  CModel * pModel;

  //  std::map< std::string, std::string >::const_iterator ObjectKey;
  //  std::pair< std::string, std::string > Map;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case StateTemplateVariable:
      if (strcmp(pszName, "StateTemplateVariable"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "StateTemplateVariable", mParser.getCurrentLineNumber());

      ObjectReference = mParser.getAttributeValue("objectReference",
                        papszAttrs);
      pObject = mCommon.KeyMap.get(ObjectReference);

      /*if ((pMetabolite = dynamic_cast< CMetab * >(pObject)))
        mCommon.StateVariableList.push_back(pMetabolite->getKey());
      else if ((pCompartment = dynamic_cast< CCompartment * >(pObject)))
        mCommon.StateVariableList.push_back(pCompartment->getKey());
      else if ((pMV = dynamic_cast< CModelValue * >(pObject)))
        mCommon.StateVariableList.push_back(pMV->getKey());
      else if ((pModel = dynamic_cast< CModel * >(pObject)))
        mCommon.StateVariableList.push_back(pModel->getKey());
      else fatalError();*/

      if ((pME = dynamic_cast< CModelEntity * >(pObject)))
        mCommon.StateVariableList.push_back(pME->getKey());
      else if ((pModel = dynamic_cast< CModel * >(pObject)))
        mCommon.StateVariableList.push_back(pModel->getKey());
      else fatalError();

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
  pdelete(mpCurrentHandler);
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
  std::vector< std::string >::iterator it;
  std::vector< std::string >::iterator end;
  double Value;
  CModelEntity * pME;

  const CStateTemplate & Template = mCommon.pModel->getStateTemplate();
  CState IState = mCommon.pModel->getInitialState();
  C_FLOAT64 * pValues = IState.beginIndependent() - 1;
  unsigned C_INT32 Index;

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

          pME = dynamic_cast< CModelEntity* >(GlobalKeys.get(*it));
          Index = Template.getIndex(pME);

          if (pME && Index != C_INVALID_INDEX)
            {
              pValues[Index] = Value;
              continue;
            }

          fatalError();
        }

      if (it != end || !Values.fail() || !Values.eof())
        fatalError();

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
  pdelete(mpCurrentHandler);
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
      /*std::cout << "Number of Channels in current plot item: " << mCommon.pCurrentPlotItem->getChannels().size() << std::endl;
      unsigned int counter;
      for(counter=0; counter <  mCommon.pCurrentPlotItem->getChannels().size(); counter++){
        std::cout << "Channel " << counter << ": " << mCommon.pCurrentPlotItem->getChannels()[counter] << std::endl;
      }*/
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
  pdelete(mpCurrentHandler);
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
      //std::cout << "Adding new Channel to PlotItem: " << mCommon.pCurrentChannelSpec << std::endl;
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
  pdelete(mpCurrentHandler);
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
      //std::cout << "Creating new DataChannelSpec with name: " << name << std::endl;
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
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
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

CCopasiXMLParser::PlotItemElement::PlotItemElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common): CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::PlotItemElement::~PlotItemElement()
{}

void CCopasiXMLParser::PlotItemElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  mpCurrentHandler = NULL;
  std::string name;
  std::string sType;

  mLineNumber = (unsigned int) - 1;

  switch (mCurrentElement)
    {
    case PlotItem:
      if (strcmp(pszName, "PlotItem"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "PlotItem", mParser.getCurrentLineNumber());
      // create a new CPlotSpecification element depending on the type
      name = mParser.getAttributeValue("name", papszAttrs);
      sType = mParser.getAttributeValue("type", papszAttrs);
      mCommon.pCurrentPlotItem = mCommon.pCurrentPlot->createItem(name, (CPlotItem::Type) toEnum(sType.c_str(), CPlotItem::XMLType));
      //std::cout << "Created Item for Plot @" << mCommon.pCurrentPlot << ": " << mCommon.pCurrentPlotItem << std::endl;
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
          mLineNumber = mParser.getCurrentLineNumber();
          if (!mpCurrentHandler)
            {
              mpCurrentHandler = new ListOfChannelsElement(mParser, mCommon);
            }
        }
      break;

    default:
      mLastKnownElement = mCurrentElement - 1;
      mCurrentElement = UNKNOWN_ELEMENT;
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
      break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::PlotItemElement::end(const XML_Char *pszName)
{
  CCopasiParameter* p;
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
          if (p)
            {
              switch (mCommon.pCurrentParameter->getType())
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
                      p->setValue(std::string(""));
                  }
                  break;

                case CCopasiParameter::FILE:
                  p->setValue(* mCommon.pCurrentParameter->getValue().pFILE);
                  break;

                case CCopasiParameter::CN:
                  p->setValue(* mCommon.pCurrentParameter->getValue().pCN);
                  break;

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

CCopasiXMLParser::PlotSpecificationElement::PlotSpecificationElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common): CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::PlotSpecificationElement::~PlotSpecificationElement()
{}

void CCopasiXMLParser::PlotSpecificationElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  mpCurrentHandler = NULL;
  mLineNumber = (unsigned int) - 1;

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
      mCommon.pCurrentPlot->setType((CPlotItem::Type) toEnum(sType, CPlotItem::XMLType));
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
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
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
              switch (mCommon.pCurrentParameter->getType())
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
                      p->setValue(std::string(""));
                  }
                  break;

                case CCopasiParameter::FILE:
                  p->setValue(* mCommon.pCurrentParameter->getValue().pFILE);
                  break;

                case CCopasiParameter::CN:
                  p->setValue(* mCommon.pCurrentParameter->getValue().pCN);
                  break;

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
              switch (mCommon.pCurrentParameter->getType())
                {
                case CCopasiParameter::GROUP:
                  * (CCopasiParameterGroup *) p =
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

  pdelete(mpCurrentHandler);
  return;
}

CCopasiXMLParser::ListOfTasksElement::ListOfTasksElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfTasksElement::~ListOfTasksElement()
{
  pdelete(mpCurrentHandler);
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
          mCommon.pTaskList = new CCopasiVectorN<CCopasiTask>;
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

      if (mCommon.pCurrentTask)
        {
          mCommon.pTaskList->add(mCommon.pCurrentTask);
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

CCopasiXMLParser::TaskElement::TaskElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common): CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common), mpReportElement(NULL), mpProblemElement(NULL), mpMethodElement(NULL)
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
      Type = (CCopasiTask::Type)toEnum(type, CCopasiTask::XMLType);
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
          break;
        case CCopasiTask::parameterFitting:
          mCommon.pCurrentTask = new CFitTask(Type, mCommon.pTaskList);
          break;
        case CCopasiTask::mca:
          mCommon.pCurrentTask = new CMCATask(mCommon.pTaskList);
          break;
        case CCopasiTask::lyap:
          mCommon.pCurrentTask = new CLyapTask(mCommon.pTaskList);
          break;
        case CCopasiTask::sens:
          mCommon.pCurrentTask = new CSensTask(mCommon.pTaskList);
          break;
#ifdef COPASI_SSA
        case CCopasiTask::ssa:
          mCommon.pCurrentTask = new CSSATask(mCommon.pTaskList);
          break;
#endif // COPASI_SSA
#ifdef COPASI_TSS
        case CCopasiTask::tss:
          mCommon.pCurrentTask = new CTSSTask(mCommon.pTaskList);
          break;
#endif // COPASI_TSS
#ifdef COPASI_DEBUG
        case CCopasiTask::tssAnalysis:
          mCommon.pCurrentTask = new CTSSATask(mCommon.pTaskList);
          break;
#endif // COPASI_DEBUG
        default:
          mParser.pushElementHandler(&mParser.mUnknownElement);
          mParser.onStartElement(pszName, papszAttrs);

          CCopasiMessage(CCopasiMessage::RAW, MCXML + 5,
                         type, mParser.getCurrentLineNumber());
          break;
        }

      if (mCommon.pCurrentTask)
        {
          mCommon.pCurrentTask->setScheduled(Scheduled);
          mCommon.pCurrentTask->setUpdateModel(UpdateModel);
          mCommon.pCurrentTask->getProblem()->setModel(mCommon.pModel);
        }
      if (Key && mCommon.pCurrentTask)
        {
          mCommon.KeyMap.addFix(Key, mCommon.pCurrentTask);
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
              mpProblemElement = new ProblemElement(mParser, mCommon);
            }
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
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
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
      if (!mCommon.pCurrentTask)
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

CCopasiXMLParser::ProblemElement::ProblemElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common), mpInitialStateHandler(NULL), mpParameterGroupHandler(NULL), mpParameterHandler(NULL)
{}

CCopasiXMLParser::ProblemElement::~ProblemElement()
{
  pdelete(mpInitialStateHandler);
  pdelete(mpParameterGroupHandler);
  pdelete(mpParameterHandler);
}

void CCopasiXMLParser::ProblemElement::start(const XML_Char *pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; // We should always be on the next element
  mpCurrentHandler = NULL;
  mLineNumber = (unsigned int) - 1;

  switch (mCurrentElement)
    {
    case Problem:
      if (!strcmp(pszName, "Problem"))
      {}
      return;
      break;

    case Parameter:
      if (!strcmp(pszName, "Parameter"))
        {
          mLineNumber = mParser.getCurrentLineNumber();

          if (!mpParameterHandler)
            {
              mpParameterHandler = new ParameterElement(mParser, mCommon);
            }
          mpCurrentHandler = mpParameterHandler;
        }
      break;

    case ParameterGroup:
      if (!strcmp(pszName, "ParameterGroup"))
        {
          mLineNumber = mParser.getCurrentLineNumber();

          if (!mpParameterGroupHandler)
            {
              mpParameterGroupHandler = new ParameterGroupElement(mParser, mCommon);
            }
          mpCurrentHandler = mpParameterGroupHandler;
        }
      break;

    case InitialState:
      if (!strcmp(pszName, "InitialState"))
        {
          if (!mpInitialStateHandler)
            {
              mpInitialStateHandler = new ProblemInitialStateElement(mParser, mCommon);
            }
          mpCurrentHandler = mpInitialStateHandler;
        }
      break;

    default:
      mLastKnownElement = mCurrentElement - 1;
      mCurrentElement = UNKNOWN_ELEMENT;
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
      break;
    }

  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);
}

void CCopasiXMLParser::ProblemElement::end(const XML_Char *pszName)
{
  CCopasiParameter* p;
  switch (mCurrentElement)
    {
    case Problem:
      if (strcmp(pszName, "Problem"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Problem", mParser.getCurrentLineNumber());
      mCurrentElement = START_ELEMENT;
      mParser.popElementHandler();
      mParser.onEndElement(pszName);
      break;

    case Parameter:
      if (strcmp(pszName, "Parameter"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "Parameter", mParser.getCurrentLineNumber());
      // add the parameter in mCommon.pCurrentParameter to the Problem of
      // the current task.
      p = mCommon.pCurrentTask->getProblem()->getParameter(mCommon.pCurrentParameter->getObjectName());
      if (p)
        {
          switch (mCommon.pCurrentParameter->getType())
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
                  p->setValue(std::string(""));
              }
              break;

            case CCopasiParameter::FILE:
              p->setValue(* mCommon.pCurrentParameter->getValue().pFILE);
              break;

            case CCopasiParameter::CN:
              p->setValue(* mCommon.pCurrentParameter->getValue().pCN);
              break;

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
      mCurrentElement = Problem;
      break;

    case ParameterGroup:
      if (strcmp(pszName, "ParameterGroup"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "ParameterGroup", mParser.getCurrentLineNumber());
      // add the parameter in mCommon.pCurrentParameter to the Problem of
      // the current task.
      p = mCommon.pCurrentTask->getProblem()->getParameter(mCommon.pCurrentParameter->getObjectName());
      if (p)
        {
          switch (mCommon.pCurrentParameter->getType())
            {
            case CCopasiParameter::GROUP:
              * (CCopasiParameterGroup *) p =
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
      mCurrentElement = Problem;
      break;

    case InitialState:
      if (strcmp(pszName, "InitialState"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "InitialState", mParser.getCurrentLineNumber());
      // get the string that corresponds to initial state from
      // mComon.Comment, parse it to get the individual values and set
      // the values.
      // !!!!!!!!!!!!!!!!
      mCommon.CharacterData = "";
      mCurrentElement = Problem;
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

CCopasiXMLParser::ProblemInitialStateElement::ProblemInitialStateElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ProblemInitialStateElement::~ProblemInitialStateElement()
{}

void CCopasiXMLParser::ProblemInitialStateElement::start(const XML_Char* pszName,
    const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case InitialState:
      if (strcmp(pszName, "InitialState"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "InitialState", mParser.getCurrentLineNumber());
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

void CCopasiXMLParser::ProblemInitialStateElement::end(const XML_Char* pszName)
{
  switch (mCurrentElement)
    {
    case InitialState:
      if (strcmp(pszName, "InitialState"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "InitialState", mParser.getCurrentLineNumber());
      mCommon.CharacterData = mParser.getCharacterData("\x0a\x0d\t ", "");
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

CCopasiXMLParser::ParameterGroupElement::ParameterGroupElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
    oldGroup(NULL),
    mpParameterHandler(NULL),
    mpParameterGroupHandler(NULL),
    level(-1)
{}

CCopasiXMLParser::ParameterGroupElement::~ParameterGroupElement()
{
  pdelete(mpParameterHandler);
  pdelete(mpParameterGroupHandler);
  pdelete(oldGroup);
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
      if (!strcmp(pszName, "ParameterGroup"))
        {
          name = mParser.getAttributeValue("name", papszAttrs);
          mCommon.ParameterGroupStack.push(new CCopasiParameterGroup(name));
          return;
        }
      break;

    case Parameter:
      if (!strcmp(pszName, "Parameter"))
        {
          if (!mpParameterHandler)
            {
              mpParameterHandler = new ParameterElement(mParser, mCommon);
            }
          mpCurrentHandler = mpParameterHandler;
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
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
      break;
    }
  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);
}

void CCopasiXMLParser::ParameterGroupElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
    case ParameterGroup:
      if (strcmp(pszName, "ParameterGroup"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "ParameterGroup", mParser.getCurrentLineNumber());

      mCommon.pCurrentParameter = mCommon.ParameterGroupStack.top();
      mCommon.ParameterGroupStack.pop();
      mCurrentElement = START_ELEMENT;

      mParser.popElementHandler();
      mParser.onEndElement(pszName);

      break;

    case Parameter:
      if (!strcmp(pszName, "Parameter") && !strcmp(pszName, "ParameterGroup"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "Parameter", mParser.getCurrentLineNumber());

      mCommon.ParameterGroupStack.top()->addParameter(* mCommon.pCurrentParameter);
      pdelete(mCommon.pCurrentParameter);

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

  std::string name;
  std::string sType;
  std::string sValue;

  void * pValue = NULL;
  CCopasiParameter::Type type;

  double d;
  int i;
  unsigned int ui;
  bool b;

  switch (mCurrentElement)
    {
    case Parameter:
      if (strcmp(pszName, "Parameter"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Parameter", mParser.getCurrentLineNumber());
      // Parameter has attributes name, type and value
      name = mParser.getAttributeValue("name", papszAttrs);
      sType = mParser.getAttributeValue("type", papszAttrs);
      sValue = mParser.getAttributeValue("value", papszAttrs);
      if (sType == "float")
        {
          type = CCopasiParameter::DOUBLE;
          d = CCopasiXMLInterface::DBL(sValue.c_str());
          pValue = &d;
        }
      else if (sType == "unsignedFloat")
        {
          type = CCopasiParameter::UDOUBLE;
          d = CCopasiXMLInterface::DBL(sValue.c_str());
          pValue = &d;
        }
      else if (sType == "integer")
        {
          type = CCopasiParameter::INT;
          i = atoi(sValue.c_str());
          pValue = &i;
        }
      else if (sType == "unsignedInteger")
        {
          type = CCopasiParameter::UINT;
          ui = atoi(sValue.c_str());
          pValue = &ui;
        }
      else if (sType == "bool")
        {
          type = CCopasiParameter::BOOL;
          if (sValue == "0" || sValue == "false")
            {
              b = false;
            }
          else
            {
              b = true;
            }
          pValue = &b;
        }
      else if (sType == "string")
        {
          type = CCopasiParameter::STRING;
          pValue = &sValue;
        }
      else if (sType == "key")
        {
          type = CCopasiParameter::KEY;
          pValue = &sValue;
        }
      else if (sType == "file")
        {
          type = CCopasiParameter::FILE;
          pValue = &sValue;
        }
      else if (sType == "cn")
        {
          type = CCopasiParameter::CN;
          pValue = &sValue;
        }
      else
        {
          fatalError();
        }
      mCommon.pCurrentParameter = new CCopasiParameter(name, type, pValue);
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

CCopasiXMLParser::MethodElement::MethodElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common), mpParameterHandler(NULL), mpParameterGroupHandler(NULL)
{}

CCopasiXMLParser::MethodElement::~MethodElement()
{
  pdelete(mpParameterHandler);
  pdelete(mpParameterGroupHandler);
}

void CCopasiXMLParser::MethodElement::start(const XML_Char *pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; // We should always be on the next element
  mpCurrentHandler = NULL;
  mLineNumber = (unsigned int) - 1;

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
            (CCopasiMethod::SubType) toEnum(sType.c_str(), CCopasiMethod::XMLSubType);

          if (type != CCopasiMethod::unset)
            {
              mCommon.pCurrentTask->setMethodType(type);
            }
          else
            {
              fatalError();
            }
          mCommon.pCurrentTask->getMethod()->setObjectName(name);
        }
      return;
      break;

    case Parameter:
      if (!strcmp(pszName, "Parameter"))
        {
          mLineNumber = mParser.getCurrentLineNumber();

          if (!mpParameterHandler)
            {
              mpParameterHandler = new ParameterElement(mParser, mCommon);
            }
          mpCurrentHandler = mpParameterHandler;
        }
      break;

    case ParameterGroup:
      if (!strcmp(pszName, "ParameterGroup"))
        {
          mLineNumber = mParser.getCurrentLineNumber();

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
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
      break;
    }
  if (mpCurrentHandler)
    mParser.pushElementHandler(mpCurrentHandler);

  mParser.onStartElement(pszName, papszAttrs);
}

void CCopasiXMLParser::MethodElement::end(const XML_Char *pszName)
{
  CCopasiParameter* p;
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

    case Parameter:
      if (strcmp(pszName, "Parameter"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "Parameter", mParser.getCurrentLineNumber());
      // add the parameter in mCommon.pCurrentParameter to the Problem of
      // the current task.

      p = mCommon.pCurrentTask->getMethod()->getParameter(mCommon.pCurrentParameter->getObjectName());
      if (p)
        {
          switch (mCommon.pCurrentParameter->getType())
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
                  p->setValue(std::string(""));
              }
              break;

            case CCopasiParameter::FILE:
              p->setValue(* mCommon.pCurrentParameter->getValue().pFILE);
              break;

            case CCopasiParameter::CN:
              p->setValue(* mCommon.pCurrentParameter->getValue().pCN);
              break;

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
          mCommon.pCurrentTask->getMethod()->addParameter(*mCommon.pCurrentParameter);
        }

      pdelete(mCommon.pCurrentParameter);
      mCurrentElement = Method;
      break;

    case ParameterGroup:
      if (strcmp(pszName, "ParameterGroup"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "ParameterGroup", mParser.getCurrentLineNumber());
      // add the parameter in mCommon.pCurrentParameter to the Problem of
      // the current task.
      p = mCommon.pCurrentTask->getProblem()->getParameter(mCommon.pCurrentParameter->getObjectName());
      if (p)
        {
          switch (mCommon.pCurrentParameter->getType())
            {
            case CCopasiParameter::GROUP:
              * (CCopasiParameterGroup *) p =
                * (CCopasiParameterGroup *) mCommon.pCurrentParameter;
              break;

            case CCopasiParameter::INT:
            case CCopasiParameter::UINT:
            case CCopasiParameter::DOUBLE:
            case CCopasiParameter::UDOUBLE:
            case CCopasiParameter::BOOL:
            case CCopasiParameter::STRING:
            case CCopasiParameter::KEY:
            case CCopasiParameter::FILE:
            case CCopasiParameter::CN:
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
      mCurrentElement = Method;
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
  pdelete(mpCurrentHandler);
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

  std::map<std::string , std::vector < std::pair < std::vector <CRegisteredObjectName >*, unsigned C_INT32 > > >::iterator outerIt;

  std::vector<std::pair < std::vector <CRegisteredObjectName >*, unsigned C_INT32 > >::iterator innerIt2;

  std::vector<CRegisteredObjectName>* nameVector;

  unsigned int reportIndex;

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
    mpCommentElement(NULL),
    mpHeaderElement(NULL),
    mpBodyElement(NULL),
    mpFooterElement(NULL),
    mpTableElement(NULL),
    tableFound(false),
    otherFound(false)
{}

CCopasiXMLParser::ReportElement::~ReportElement()
{
  pdelete(mpCommentElement);
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
      type = (CCopasiTask::Type)toEnum(mParser.getAttributeValue("taskType", papszAttrs),
                                       CCopasiTask::XMLType);

      Separator = mParser.getAttributeValue("separator", papszAttrs, "\t");
      Precision = mParser.getAttributeValue("precision", papszAttrs, "6");

      // create a new report
      mCommon.pReport = new CReportDefinition();
      mCommon.pReport->setObjectName(Name);
      mCommon.pReport->setTaskType(type);
      mCommon.pReport->setSeparator(CCopasiReportSeparator(Separator));
      mCommon.pReport->setPrecision(atoi(Precision));

      /* We have a new report and add it to the list */
      mCommon.pReportList->add(mCommon.pReport, true);
      mCommon.KeyMap.addFix(Key, mCommon.pReport);
      return;
      break;

    case Comment:
      if (!strcmp(pszName, "Comment"))
        {
          /* If we do not have a Comment element handler we create one. */
          if (!mpCommentElement)
            mpCommentElement = new CommentElement(mParser, mCommon);

          /* Push the Comment element handler on the stack and call it. */
          mpCurrentHandler = mpCommentElement;
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
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
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
    mpCommentElement(NULL),
    mpObjectElement(NULL)
{}

CCopasiXMLParser::HeaderElement::~HeaderElement()
{
  pdelete(mpCommentElement);
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
          /* If we do not have a comment element handler we create one. */
          if (!mpCommentElement)
            mpCommentElement = new CommentElement(mParser, mCommon);

          mpCurrentHandler = mpCommentElement;
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
      mParser.pushElementHandler(&mParser.mUnknownElement);
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
          mCommon.reportReferenceMap[mCommon.CharacterData] = std::vector<std::pair <std::vector<CRegisteredObjectName>*, unsigned C_INT32> >();
        }
      mCommon.reportReferenceMap[mCommon.CharacterData].push_back(std::make_pair(mCommon.pReport->getHeaderAddr(), mCommon.pReport->getHeaderAddr()->size()));
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
    mpCommentElement(NULL),
    mpObjectElement(NULL)
{}

CCopasiXMLParser::BodyElement::~BodyElement()
{
  pdelete(mpCommentElement);
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
          /* If we do not have a comment element handler we create one. */
          if (!mpCommentElement)
            mpCommentElement = new CommentElement(mParser, mCommon);

          mpCurrentHandler = mpCommentElement;
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
      mParser.pushElementHandler(&mParser.mUnknownElement);
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
          mCommon.reportReferenceMap[mCommon.CharacterData] = std::vector<std::pair <std::vector<CRegisteredObjectName>*, unsigned C_INT32> >();
        }
      mCommon.reportReferenceMap[mCommon.CharacterData].push_back(std::make_pair(mCommon.pReport->getBodyAddr(), mCommon.pReport->getBodyAddr()->size()));
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
    mpCommentElement(NULL),
    mpObjectElement(NULL)
{}

CCopasiXMLParser::FooterElement::~FooterElement()
{
  pdelete(mpCommentElement);
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
          /* If we do not have a comment element handler we create one. */
          if (!mpCommentElement)
            mpCommentElement = new CommentElement(mParser, mCommon);

          mpCurrentHandler = mpCommentElement;
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
      mParser.pushElementHandler(&mParser.mUnknownElement);
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
          mCommon.reportReferenceMap[mCommon.CharacterData] = std::vector<std::pair <std::vector<CRegisteredObjectName>*, unsigned C_INT32> >();
        }
      mCommon.reportReferenceMap[mCommon.CharacterData].push_back(std::make_pair(mCommon.pReport->getFooterAddr(), mCommon.pReport->getFooterAddr()->size()));
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
  pdelete(mpCurrentHandler);
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
  pdelete(mpCurrentHandler);
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

CCopasiXMLParser::GUIElement::GUIElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::GUIElement::~GUIElement()
{
  pdelete(mpCurrentHandler);
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
      mParser.pushElementHandler(&mParser.mUnknownElement);
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
    pdelete(mpCurrentHandler);

  return;
}

CCopasiXMLParser::ListOfSlidersElement::ListOfSlidersElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfSlidersElement::~ListOfSlidersElement()
{
  pdelete(mpCurrentHandler);
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
      if (!mCommon.pGUI->pSliderList)
        mCommon.pGUI->pSliderList = new CCopasiVector< CSlider >;
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
  pdelete(mpCurrentHandler);
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
      ObjectType = (CSlider::Type) toEnum(objectType, CSlider::TypeName);
      tmp = mParser.getAttributeValue("objectValue", papszAttrs);
      ObjectValue = CCopasiXMLInterface::DBL(tmp);
      tmp = mParser.getAttributeValue("minValue", papszAttrs);
      MinValue = CCopasiXMLInterface::DBL(tmp);
      tmp = mParser.getAttributeValue("maxValue", papszAttrs);
      MaxValue = CCopasiXMLInterface::DBL(tmp);
      tmp = mParser.getAttributeValue("tickNumber", papszAttrs, "1000");
      TickNumber = atoi(tmp);
      tmp = mParser.getAttributeValue("tickFactor", papszAttrs, "100");
      TickFactor = atoi(tmp);

      scaling = mParser.getAttributeValue("scaling", papszAttrs, "linear");

      // This is always the case if the XML is conforming to the schema.

      if (mCommon.KeyMap.get(AssociatedEntityKey))
        {
          pSlider = new CSlider;
          mCommon.KeyMap.addFix(Key, pSlider);
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
          mCommon.pGUI->pSliderList->add(pSlider, true);
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
  pdelete(mpCurrentHandler);
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
      if (CCopasiDataModel::Global)
        CCopasiDataModel::Global->setSBMLFileName(File);

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
  pdelete(mpCurrentHandler);
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
