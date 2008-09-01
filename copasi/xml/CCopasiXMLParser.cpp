// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/CCopasiXMLParser.cpp,v $
//   $Revision: 1.184 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/09/01 17:01:32 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
#ifdef COPASI_TSS
#include "tss/CTSSTask.h"
#endif
#ifdef COPASI_TSSA
# include "tssanalysis/CTSSATask.h"
#endif // COPASI_TSSA
#include "scan/CScanTask.h"
#include "elementaryFluxModes/CEFMTask.h"
#include "optimization/COptTask.h"
#include "parameterFitting/CFitTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "lyap/CLyapTask.h"
#include "sensitivities/CSensTask.h"
#include "moieties/CMoietiesTask.h"
#include "plot/COutputDefinitionVector.h"
#include "plot/CPlotSpecification.h"
#include "plot/CPlotItem.h"
#include "CopasiDataModel/CCopasiDataModel.h"

#ifdef WITH_LAYOUT
#include "layout/CListOfLayouts.h"
#endif //WITH_LAYOUT

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
    mCharacterDataElement(*this, this->mCommon),
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
  mCommon.pReportList = NULL;
  mCommon.pReport = NULL;
  mCommon.mParameterGroupLevel = -1;
  mCommon.pGUI = NULL;

  mCommon.pPlotList = NULL;

#ifdef WITH_LAYOUT
  mCommon.pLayoutList = NULL;
  mCommon.pCurrentLayout = NULL;
  mCommon.pCompartmentGlyph = NULL;
  mCommon.pMetaboliteGlyph = NULL;
  mCommon.pReactionGlyph = NULL;
  mCommon.pTextGlyph = NULL;
  mCommon.pAdditionalGO = NULL;
  mCommon.pCurve = NULL;
  mCommon.pLineSegment = NULL;
  mCommon.pMetaboliteReferenceGlyph = NULL;

#endif //WITH_LAYOUT

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

#ifdef WITH_LAYOUT
void CCopasiXMLParser::setLayoutList(CListOfLayouts * pLayoutList)
{mCommon.pLayoutList = pLayoutList;}

CListOfLayouts * CCopasiXMLParser::getLayoutList() const
  {return mCommon.pLayoutList;}
#endif //WITH_LAYOUT

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

void CCopasiXMLParser::UnknownElement::start(const XML_Char * /*pszName*/ ,
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

#ifdef WITH_LAYOUT
    case ListOfLayouts:
      if (!strcmp(pszName, "ListOfLayouts"))
        mpCurrentHandler = new ListOfLayoutsElement(mParser, mCommon);
      break;
#endif //WITH_LAYOUT

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
      mCurrentElement = START_ELEMENT;
    }
  else if (!strcmp(pszName, "GUI") && mCommon.pGUI == NULL)
    CCopasiMessage::getLastMessage();
  else
    pdelete(mpCurrentHandler);

  //TODO why no case statement with error checking (like in other elements)?

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

      mKey = mParser.getAttributeValue("key", papszAttrs);
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
            case CEvaluationTree::Boolean:
              mCommon.pFunctionList->remove(Name);
              mCommon.pFunctionList->add(mCommon.pFunction, true);
              break;
            }
        }
      else
        mCommon.pFunctionList->add(mCommon.pFunction, true);

      mCommon.KeyMap.addFix(mKey , mCommon.pFunction);
      return;

    case MiriamAnnotation:
      if (!strcmp(pszName, "MiriamAnnotation"))
        mpCurrentHandler = &mParser.mMiriamAnnotationElement;
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
  if (mCurrentElement == MiriamAnnotation && !strcmp(pszName, "Function"))
    mCurrentElement = Function;

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

    case MiriamAnnotation:
      if (strcmp(pszName, "MiriamAnnotation"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "MiriamAnnotation", mParser.getCurrentLineNumber());

      mCommon.pFunction->setMiriamAnnotation(mCommon.CharacterData, mKey);
      mCommon.CharacterData = "";
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
      if (std::string("unbounded") == std::string(maxOccurs)) MaxOccurs = (unsigned C_INT32) - 1;
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
            {
              CCopasiMessage(CCopasiMessage::WARNING, MCXML + 8, Name,
                             pFunction->getObjectName().c_str(),
                             mParser.getCurrentLineNumber());
              break;
            }

          if (Order >= pFunction->getVariables().size())
            {
              CCopasiMessage(CCopasiMessage::WARNING, MCXML + 12, Order, Name,
                             pFunction->getObjectName().c_str(),
                             mParser.getCurrentLineNumber());
              Order = Index;
            }

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
  // We must not delete any staticly allocated element handlers
  if (mpCurrentHandler != &mParser.mCharacterDataElement &&
      mpCurrentHandler != &mParser.mCommentElement &&
      mpCurrentHandler != &mParser.mMiriamAnnotationElement)
    pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::ModelElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * Name;
  const char * timeUnit;
  CModel::TimeUnit TimeUnit;
  const char * volumeUnit;
  CModel::VolumeUnit VolumeUnit;
  const char * quantityUnit;
  CModel::QuantityUnit QuantityUnit;
  const char * StateVariable;
  CModel::ModelType ModelType;

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
      mCommon.KeyMap.addFix(mKey, mCommon.pModel);
      mCommon.pModel->setTitle(Name);
      mCommon.pModel->setTimeUnit(TimeUnit);
      mCommon.pModel->setVolumeUnit(VolumeUnit);
      mCommon.pModel->setQuantityUnit(QuantityUnit);
      mCommon.pModel->setModelType(ModelType);
      return;
      break;

    case MiriamAnnotation:
      if (!strcmp(pszName, "MiriamAnnotation"))
        mpCurrentHandler = &mParser.mMiriamAnnotationElement;
      break;

    case Comment:
      if (!strcmp(pszName, "Comment"))
        mpCurrentHandler = &mParser.mCommentElement;
      break;

    case InitialExpression:
      if (!strcmp(pszName, "InitialExpression"))
        mpCurrentHandler = &mParser.mCharacterDataElement;
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

    case ListOfEvents:
      if (!strcmp(pszName, "ListOfEvents"))
        mpCurrentHandler = new ListOfEventsElement(mParser, mCommon);
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

    case MiriamAnnotation:
      if (strcmp(pszName, "MiriamAnnotation"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "MiriamAnnotation", mParser.getCurrentLineNumber());

      mCommon.pModel->setMiriamAnnotation(mCommon.CharacterData, mKey);
      mCommon.CharacterData = "";
      break;

    case Comment:
      if (strcmp(pszName, "Comment"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "Comment", mParser.getCurrentLineNumber());

      mCommon.pModel->setComments(mCommon.CharacterData);
      mCommon.CharacterData = "";
      break;

    case InitialExpression:
      if (strcmp(pszName, "InitialExpression"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "InitialExpression", mParser.getCurrentLineNumber());
      {
        unsigned C_INT32 Size = CCopasiMessage::size();

        mCommon.pModel->setInitialExpression(mCommon.CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          CCopasiMessage::getLastMessage();
      }
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

    case ListOfEvents:
      if (strcmp(pszName, "ListOfEvents"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "ListOfEvents", mParser.getCurrentLineNumber());
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
  const char * Name;
  const char * simulationType;
  CModelEntity::Status SimulationType;

  mpCurrentHandler = NULL;
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
      SimulationType = (CModelEntity::Status)toEnum(simulationType, CModelEntity::XMLStatus);

      mpCompartment = new CCompartment();
      mCommon.KeyMap.addFix(mKey, mpCompartment);

      mpCompartment->setObjectName(Name);
      mpCompartment->setStatus(SimulationType);

      mCommon.pModel->getCompartments().add(mpCompartment, true);
      return;

    case MiriamAnnotation:
      if (!strcmp(pszName, "MiriamAnnotation"))
        mpCurrentHandler = &mParser.mMiriamAnnotationElement;
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
  if (mCurrentElement == MiriamAnnotation && !strcmp(pszName, "Compartment"))
    mCurrentElement = Compartment;

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

    case MiriamAnnotation:
      if (strcmp(pszName, "MiriamAnnotation"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "MiriamAnnotation", mParser.getCurrentLineNumber());

      mpCompartment->setMiriamAnnotation(mCommon.CharacterData, mKey);
      mCommon.CharacterData = "";
      break;

    case Expression:
      if (strcmp(pszName, "Expression"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "Expression", mParser.getCurrentLineNumber());
      {
        unsigned C_INT32 Size = CCopasiMessage::size();

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
        unsigned C_INT32 Size = CCopasiMessage::size();

        mpCompartment->setInitialExpression(mCommon.CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          CCopasiMessage::getLastMessage();
      }

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

      SimulationType = (CModelEntity::Status)toEnum(simulationType, CModelEntity::XMLStatus);
      Compartment = mParser.getAttributeValue("compartment", papszAttrs);

      mpMetabolite = new CMetab();
      mCommon.KeyMap.addFix(mKey, mpMetabolite);
      mpMetabolite->setObjectName(Name);
      mpMetabolite->setStatus(SimulationType);

      pCompartment =
        dynamic_cast< CCompartment* >(mCommon.KeyMap.get(Compartment));

      if (!pCompartment) fatalError();

      pCompartment->addMetabolite(mpMetabolite);
      mCommon.pModel->getMetabolites().add(mpMetabolite);
      return;

    case MiriamAnnotation:
      if (!strcmp(pszName, "MiriamAnnotation"))
        mpCurrentHandler = &mParser.mMiriamAnnotationElement;
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
  if (mCurrentElement == MiriamAnnotation && !strcmp(pszName, "Metabolite"))
    mCurrentElement = Metabolite;

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

    case MiriamAnnotation:
      if (strcmp(pszName, "MiriamAnnotation"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "MiriamAnnotation", mParser.getCurrentLineNumber());

      mpMetabolite->setMiriamAnnotation(mCommon.CharacterData, mKey);
      mCommon.CharacterData = "";
      break;

    case Expression:
      if (strcmp(pszName, "Expression"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "Expression", mParser.getCurrentLineNumber());
      {
        unsigned C_INT32 Size = CCopasiMessage::size();

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
        unsigned C_INT32 Size = CCopasiMessage::size();

        mpMetabolite->setInitialExpression(mCommon.CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          CCopasiMessage::getLastMessage();
      }

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

//****** TODO: ModelValues

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

      SimulationType = (CModelEntity::Status)toEnum(simulationType, CModelEntity::XMLStatus);

      mpMV = new CModelValue();
      mCommon.KeyMap.addFix(mKey, mpMV);
      mpMV->setObjectName(Name);
      mpMV->setStatus(SimulationType);

      mCommon.pModel->getModelValues().add(mpMV, true);
      return;

    case MiriamAnnotation:
      if (!strcmp(pszName, "MiriamAnnotation"))
        mpCurrentHandler = &mParser.mMiriamAnnotationElement;
      break;

    case Expression:
      if (!strcmp(pszName, "Expression"))
        mpCurrentHandler = &mParser.mCharacterDataElement;
      break;

    case InitialExpression:
      if (!strcmp(pszName, "InitialExpression"))
        mpCurrentHandler = &mParser.mCharacterDataElement;
      break;

    case MathML:                                           // Old file format support
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
  if (mCurrentElement == MiriamAnnotation && !strcmp(pszName, "ModelValue"))
    mCurrentElement = ModelValue;

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

    case MiriamAnnotation:
      if (strcmp(pszName, "MiriamAnnotation"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "MiriamAnnotation", mParser.getCurrentLineNumber());

      mpMV->setMiriamAnnotation(mCommon.CharacterData, mKey);
      mCommon.CharacterData = "";

      //      mCurrentElement = ModelValue;
      break;

    case Expression:
      if (strcmp(pszName, "Expression"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "Expression", mParser.getCurrentLineNumber());
      {
        unsigned C_INT32 Size = CCopasiMessage::size();

        mpMV->setExpression(mCommon.CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.

        while (CCopasiMessage::size() > Size)
          CCopasiMessage::getLastMessage();
      }

      //      mCurrentElement = ModelValue;
      break;

    case InitialExpression:
      if (strcmp(pszName, "InitialExpression"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "InitialExpression", mParser.getCurrentLineNumber());
      {
        unsigned C_INT32 Size = CCopasiMessage::size();

        mpMV->setInitialExpression(mCommon.CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          CCopasiMessage::getLastMessage();
      }

      mCurrentElement = ModelValue;
      break;

    case MathML:                                           // Old file format support
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

//****** TODO: Event

CCopasiXMLParser::ListOfEventsElement::ListOfEventsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfEventsElement::~ListOfEventsElement()
{
  pdelete(mpCurrentHandler);
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
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::EventElement::~EventElement()
{}

void CCopasiXMLParser::EventElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * Name;

  mpCurrentHandler = NULL;
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case Event:
      if (strcmp(pszName, "Event"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Event", mParser.getCurrentLineNumber());

      mKey = mParser.getAttributeValue("key", papszAttrs);
      Name = mParser.getAttributeValue("name", papszAttrs);

      mpEvent = new CEvent();
      mCommon.KeyMap.addFix(mKey, mpEvent);
      mpEvent->setObjectName(Name);

      mCommon.pModel->getEvents().add(mpEvent, true);
      return;

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
          if (!mpCurrentHandler)
            {
              mpCurrentHandler = new ListOfAssignmentsElement(mParser, mCommon);

              mCommon.mAssignments.reserve(100);
              mCommon.mAssignments.resize(0);
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

void CCopasiXMLParser::EventElement::end(const XML_Char *pszName)
{
  // It is possible that we have an Expression but no InitialExpression,
  // i.e., mCurrentElement = Expression and pszName = ModelValue may occur
  // and is valid.
  //  if (mCurrentElement == Expression && !strcmp(pszName, "ModelValue"))
  //    mCurrentElement = ModelValue;

  switch (mCurrentElement)
    {
    case Event:
      if (strcmp(pszName, "Event"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "Event", mParser.getCurrentLineNumber());
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case TriggerExpression:
      if (strcmp(pszName, "TriggerExpression"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "TriggerExpression", mParser.getCurrentLineNumber());
      {
        unsigned C_INT32 Size = CCopasiMessage::size();

        if (!mpEvent->setExpressionTrigger(mCommon.CharacterData)) fatalError();

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          {
            CCopasiMessage msg = CCopasiMessage::getLastMessage();
          }

        //        while (CCopasiMessage::size() > Size)
        //          CCopasiMessage::getLastMessage();
      }

      mCurrentElement = Event;
      break;

    case DelayExpression:
      if (strcmp(pszName, "DelayExpression"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "DelayExpression", mParser.getCurrentLineNumber());
      {
        unsigned C_INT32 Size = CCopasiMessage::size();

        mpEvent->setExpressionDelay(mCommon.CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          {
            CCopasiMessage msg = CCopasiMessage::getLastMessage();
          }

        //        while (CCopasiMessage::size() > Size)
        //          CCopasiMessage::getLastMessage();
      }

      mCurrentElement = Event;
      break;

    case ListOfAssignments:
      if (strcmp(pszName, "ListOfAssignments"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "ListOfAssignments", mParser.getCurrentLineNumber());

      {
        unsigned C_INT32 Size = CCopasiMessage::size();

        CCopasiMessage msg = CCopasiMessage::getLastMessage();

        while (CCopasiMessage::size() > Size)
          {
            msg = CCopasiMessage::getLastMessage();
          }
      }

      mpEvent->clearAssignment();

      unsigned C_INT32 idx;
      for (idx = 0; idx < mCommon.mAssignments.size(); idx++)
        {
          CCopasiMessage msg = CCopasiMessage::getLastMessage();

          mpEvent->addAssignment(mCommon.mAssignments[idx].first, mCommon.mAssignments[idx].second);

          msg = CCopasiMessage::getLastMessage();
        }

      //   mpEvent->addAssignment(mCommon.mAssignmentPair.first, mCommon.mAssignmentPair.second);
      {
        unsigned C_INT32 Size = CCopasiMessage::size();

        CCopasiMessage msg = CCopasiMessage::getLastMessage();

        while (CCopasiMessage::size() > Size)
          {
            msg = CCopasiMessage::getLastMessage();
          }
      }

      // Remove error messages created by setExpression as this may fail
      // due to incomplete model specification at this time.
      //      if (CCopasiMessage::peekLastMessage().getNumber() == MCFunction + 3)
      //        CCopasiMessage::getLastMessage();
      /*
            if (!strcmp(pszName, "ListOfAssignments"))
         {
              mCurrentElement = Event;
         }
      */
      mCurrentElement = Event;

      /*
            if (strcmp(pszName, "ListOfAssignments"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                             pszName, "ListOfAssignments", mParser.getCurrentLineNumber());
            mpMV->setExpression(mCommon.FunctionDescription);

            // Remove error messages created by setExpression as this may fail
            // due to incomplete model specification at this time.
            if (CCopasiMessage::peekLastMessage().getNumber() == MCFunction + 3)
              CCopasiMessage::getLastMessage();

            mCurrentElement = Event;
      */
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

      mKey = mParser.getAttributeValue("targetkey", papszAttrs);

      pME = dynamic_cast<const CModelEntity*>(mCommon.KeyMap.get(mKey));
      if (pME == NULL) fatalError();
      mAssignmentPair.first = pME->getKey();

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
  // It is possible that we have an Expression but no InitialExpression,
  // i.e., mCurrentElement = Expression and pszName = ModelValue may occur
  // and is valid.
  //  if (mCurrentElement == Expression && !strcmp(pszName, "ModelValue"))
  //    mCurrentElement = ModelValue;

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
        unsigned C_INT32 Size = CCopasiMessage::size();

        mAssignmentPair.second = mCommon.CharacterData;

        mCommon.mAssignments.push_back(mAssignmentPair);

        //        mpMV->setExpression(mCommon.CharacterData);

        CCopasiMessage msg = CCopasiMessage::getLastMessage();

        while (CCopasiMessage::size() > Size)
          {
            msg = CCopasiMessage::getLastMessage();
          }

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        //        while (CCopasiMessage::size() > Size)
        //          CCopasiMessage::getLastMessage();
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
      mKey = mParser.getAttributeValue("key", papszAttrs);
      Name = mParser.getAttributeValue("name", papszAttrs);
      Compartment = mParser.getAttributeValue("compartment", papszAttrs,
                                              "Compartment_00");

      reversible = mParser.getAttributeValue("reversible", papszAttrs);
      Reversible = mParser.toBool(reversible);

      mCommon.pReaction = new CReaction();
      mCommon.KeyMap.addFix(mKey, mCommon.pReaction);
      mCommon.pReaction->setObjectName(Name);
      mCommon.pReaction->setReversible(Reversible);
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

      return;
      break;

    case MiriamAnnotation:
      if (!strcmp(pszName, "MiriamAnnotation"))
        mpCurrentHandler = &mParser.mMiriamAnnotationElement;
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

    case MiriamAnnotation:
      if (strcmp(pszName, "MiriamAnnotation"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "MiriamAnnotation", mParser.getCurrentLineNumber());

      mCommon.pReaction->setMiriamAnnotation(mCommon.CharacterData, mKey);
      mCommon.CharacterData = "";
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
          mCommon.pFunction = CCopasiDataModel::Global->mpUndefined;
        }

      // This must be deferred till the end since we need to check for consistency
      // of the parameters first (Bug 832)
      // mCommon.pReaction->setFunction(pFunction);
      break;

    case ListOfCallParameters:
      if (strcmp(pszName, "ListOfCallParameters"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "ListOfCallParameters", mParser.getCurrentLineNumber());

      if (mCommon.pFunction == CCopasiDataModel::Global->mpUndefined)
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

      mCommon.pFunctionVariable =
        dynamic_cast< CFunctionParameter* >(mCommon.KeyMap.get(FunctionParameter));
      if (!mCommon.pFunctionVariable) fatalError();

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
  pdelete(mpCurrentHandler);
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
  std::vector< CModelEntity * >::iterator it;
  std::vector< CModelEntity * >::iterator end;
  double Value;

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

          Index = Template.getIndex(*it);

          if (Index != C_INVALID_INDEX)
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

CCopasiXMLParser::PlotItemElement::PlotItemElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
    mpParameterElement(NULL),
    mpParameterGroupElement(NULL),
    mpListOfChannelsElement(NULL)

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

#ifdef WITH_LAYOUT

//******** Curve **********

CCopasiXMLParser::CurveElement::CurveElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common): CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::CurveElement::~CurveElement()
{}

void CCopasiXMLParser::CurveElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  //  mpCurrentHandler = NULL;
  mLineNumber = (unsigned int) - 1;

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
                mCommon.KeyMap.addFix(key, mCommon.pReactionGlyph);*/
      }
      return;
      break;

    case ListOfCurveSegments:
      if (strcmp(pszName, "ListOfCurveSegments"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "ListOfCurveSegments", mParser.getCurrentLineNumber());
      return;
      break;

    case CurveSegment:
      if (strcmp(pszName, "CurveSegment"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "CurveSegment", mParser.getCurrentLineNumber());
      {
        //workload
        const char * type;
        type = mParser.getAttributeValue("xsi:type", papszAttrs);

        if (!mCommon.pLineSegment)
          mCommon.pLineSegment = new CLLineSegment;

        mCommon.pLineSegment->setIsBezier(type == "CubicBezier");
      }
      return;
      break;

    case Start:
      if (strcmp(pszName, "Start"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Start", mParser.getCurrentLineNumber());
      {//workload
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
      if (strcmp(pszName, "End"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "End", mParser.getCurrentLineNumber());
      {//workload
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
          mCommon.pCurve->addCurveSegment(*mCommon.pLineSegment);
          //tell the handler where to continue
          mCurrentElement = ListOfCurveSegments;
          break;

        case Start:
          break;

        case End:
          //tell the handler where to continue
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

CCopasiXMLParser::CompartmentGlyphElement::CompartmentGlyphElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common): CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::CompartmentGlyphElement::~CompartmentGlyphElement()
{}

void CCopasiXMLParser::CompartmentGlyphElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  mpCurrentHandler = NULL;
  mLineNumber = (unsigned int) - 1;

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

        CCompartment * pComp = dynamic_cast< CCompartment * >(mCommon.KeyMap.get(compartment));
        if (!pComp) fatalError();
        mCommon.pCompartmentGlyph->setModelObjectKey(pComp->getKey());

        mCommon.pCurrentLayout->addCompartmentGlyph(mCommon.pCompartmentGlyph);
        mCommon.KeyMap.addFix(key, mCommon.pCompartmentGlyph);
      }
      return;
      break;

    case BoundingBox:
      if (strcmp(pszName, "BoundingBox"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "BoundingBox", mParser.getCurrentLineNumber());
      //mpCurrentHandler = new BoundingBoxElement(mParser, mCommon);
      return;
      break;

    case Position:
      if (strcmp(pszName, "Position"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Position", mParser.getCurrentLineNumber());
      {//workload
        const char * attr;
        attr = mParser.getAttributeValue("x", papszAttrs);
        mCommon.pCompartmentGlyph->setX(CCopasiXMLInterface::DBL(attr));
        attr = mParser.getAttributeValue("y", papszAttrs);
        mCommon.pCompartmentGlyph->setY(CCopasiXMLInterface::DBL(attr));
        return;
      }
      break;

    case Dimensions:
      if (strcmp(pszName, "Dimensions"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Dimensions", mParser.getCurrentLineNumber());
      {//workload
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
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
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
  pdelete(mpCurrentHandler);
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
      if (strcmp(pszName, "CompartmentGlyph"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "CompartmentGlyph", mParser.getCurrentLineNumber());

      //only one type of tags may occur here, so if the handler exists
      //it must be the correct one
      if (!mpCurrentHandler)
        mpCurrentHandler = new CompartmentGlyphElement(mParser, mCommon);

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

CCopasiXMLParser::MetaboliteGlyphElement::MetaboliteGlyphElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common): CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::MetaboliteGlyphElement::~MetaboliteGlyphElement()
{}

void CCopasiXMLParser::MetaboliteGlyphElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  mpCurrentHandler = NULL;
  mLineNumber = (unsigned int) - 1;

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
        metabolite = mParser.getAttributeValue("metabolite", papszAttrs);

        mCommon.pMetaboliteGlyph = new CLMetabGlyph(name);

        CMetab * pMetab = dynamic_cast< CMetab * >(mCommon.KeyMap.get(metabolite));
        if (!pMetab) fatalError();
        mCommon.pMetaboliteGlyph->setModelObjectKey(pMetab->getKey());

        mCommon.pCurrentLayout->addMetaboliteGlyph(mCommon.pMetaboliteGlyph);
        mCommon.KeyMap.addFix(key, mCommon.pMetaboliteGlyph);
      }
      return;
      break;

    case BoundingBox:
      if (strcmp(pszName, "BoundingBox"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "BoundingBox", mParser.getCurrentLineNumber());
      return;
      break;

    case Position:
      if (strcmp(pszName, "Position"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Position", mParser.getCurrentLineNumber());
      {//workload
        const char * attr;
        attr = mParser.getAttributeValue("x", papszAttrs);
        mCommon.pMetaboliteGlyph->setX(CCopasiXMLInterface::DBL(attr));
        attr = mParser.getAttributeValue("y", papszAttrs);
        mCommon.pMetaboliteGlyph->setY(CCopasiXMLInterface::DBL(attr));
        return;
      }
      break;

    case Dimensions:
      if (strcmp(pszName, "Dimensions"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Dimensions", mParser.getCurrentLineNumber());
      {//workload
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
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
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
  pdelete(mpCurrentHandler);
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
      //only one type of tags may occur here, so we can throw an exception.
      //No need to silently ignore unknown tags here.
      if (strcmp(pszName, "MetaboliteGlyph"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "MetaboliteGlyph", mParser.getCurrentLineNumber());

      //only one type of tags may occur here, so if the handler exists
      //it must be the correct one
      if (!mpCurrentHandler)
        mpCurrentHandler = new MetaboliteGlyphElement(mParser, mCommon);

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
      if (strcmp(pszName, "MetaboliteGlyph"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "MetaboliteGlyph", mParser.getCurrentLineNumber());

      //tell the handler where to continue
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

CCopasiXMLParser::MetaboliteReferenceGlyphElement::MetaboliteReferenceGlyphElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common)
    : CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::MetaboliteReferenceGlyphElement::~MetaboliteReferenceGlyphElement()
{}

void CCopasiXMLParser::MetaboliteReferenceGlyphElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  mpCurrentHandler = NULL;
  mLineNumber = (unsigned int) - 1;

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

        CLMetabGlyph * pMetabGlyph = dynamic_cast< CLMetabGlyph * >(mCommon.KeyMap.get(metaboliteGlyph));
        if (!pMetabGlyph) fatalError();
        mCommon.pMetaboliteReferenceGlyph->setMetabGlyphKey(pMetabGlyph->getKey());

        //interpret role string
        C_INT32 i;
        for (i = 0; (CLMetabReferenceGlyph::XMLRole[i] != "") && (CLMetabReferenceGlyph::XMLRole[i] != role); ++i);

        if (CLMetabReferenceGlyph::XMLRole[i] == "")
          mCommon.pMetaboliteReferenceGlyph->setRole(CLMetabReferenceGlyph::UNDEFINED);
        else
          mCommon.pMetaboliteReferenceGlyph->setRole(CLMetabReferenceGlyph::Role(i));

        mCommon.pReactionGlyph->addMetabReferenceGlyph(mCommon.pMetaboliteReferenceGlyph);
        mCommon.KeyMap.addFix(key, mCommon.pMetaboliteReferenceGlyph);
      }
      return;
      break;

    case BoundingBox:
      if (strcmp(pszName, "BoundingBox"))
        {
          //CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
          //               pszName, "BoundingBox", mParser.getCurrentLineNumber());
          mCurrentElement = Dimensions;
        }
      else
        return;
      break;

    case Position:
      if (strcmp(pszName, "Position"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Position", mParser.getCurrentLineNumber());
      {//workload
        const char * attr;
        attr = mParser.getAttributeValue("x", papszAttrs);
        mCommon.pMetaboliteReferenceGlyph->setX(CCopasiXMLInterface::DBL(attr));
        attr = mParser.getAttributeValue("y", papszAttrs);
        mCommon.pMetaboliteReferenceGlyph->setY(CCopasiXMLInterface::DBL(attr));
        return;
      }
      break;

    case Dimensions:
      if (strcmp(pszName, "Dimensions"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Dimensions", mParser.getCurrentLineNumber());
      {//workload
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
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
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
  pdelete(mpCurrentHandler);
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
      //only one type of tags may occur here, so we can throw an exception.
      //No need to silently ignore unknown tags here.
      if (strcmp(pszName, "MetaboliteReferenceGlyph"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "MetaboliteReferenceGlyph", mParser.getCurrentLineNumber());

      //only one type of tags may occur here, so if the handler exists
      //it must be the correct one
      if (!mpCurrentHandler)
        mpCurrentHandler = new MetaboliteReferenceGlyphElement(mParser, mCommon);

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
      if (strcmp(pszName, "MetaboliteReferenceGlyph"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "MetaboliteReferenceGlyph", mParser.getCurrentLineNumber());

      //tell the handler where to continue
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

CCopasiXMLParser::ReactionGlyphElement::ReactionGlyphElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common): CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ReactionGlyphElement::~ReactionGlyphElement()
{}

void CCopasiXMLParser::ReactionGlyphElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  mpCurrentHandler = NULL;
  mLineNumber = (unsigned int) - 1;

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

        CReaction * pReaction = dynamic_cast< CReaction * >(mCommon.KeyMap.get(reaction));
        if (!pReaction) fatalError();
        mCommon.pReactionGlyph->setModelObjectKey(pReaction->getKey());

        mCommon.pCurrentLayout->addReactionGlyph(mCommon.pReactionGlyph);
        mCommon.KeyMap.addFix(key, mCommon.pReactionGlyph);
      }
      return;
      break;

    case BoundingBox:
      if (strcmp(pszName, "BoundingBox"))
        {
          //CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
          //               pszName, "BoundingBox", mParser.getCurrentLineNumber());
          mCurrentElement = Dimensions;
        }
      else
        return;
      break;

    case Position:
      if (strcmp(pszName, "Position"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Position", mParser.getCurrentLineNumber());
      {//workload
        const char * attr;
        attr = mParser.getAttributeValue("x", papszAttrs);
        mCommon.pReactionGlyph->setX(CCopasiXMLInterface::DBL(attr));
        attr = mParser.getAttributeValue("y", papszAttrs);
        mCommon.pReactionGlyph->setY(CCopasiXMLInterface::DBL(attr));
        return;
      }
      break;

    case Dimensions:
      if (strcmp(pszName, "Dimensions"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Dimensions", mParser.getCurrentLineNumber());
      {//workload
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
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
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
          //tell the handler where to continue
          mCurrentElement = BoundingBox;
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
  pdelete(mpCurrentHandler);
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
      //only one type of tags may occur here, so we can throw an exception.
      //No need to silently ignore unknown tags here.
      if (strcmp(pszName, "ReactionGlyph"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "ReactionGlyph", mParser.getCurrentLineNumber());

      //only one type of tags may occur here, so if the handler exists
      //it must be the correct one
      if (!mpCurrentHandler)
        mpCurrentHandler = new ReactionGlyphElement(mParser, mCommon);

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
      if (strcmp(pszName, "ReactionGlyph"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "ReactionGlyph", mParser.getCurrentLineNumber());

      //tell the handler where to continue
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

CCopasiXMLParser::TextGlyphElement::TextGlyphElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common): CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::TextGlyphElement::~TextGlyphElement()
{}

void CCopasiXMLParser::TextGlyphElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  mpCurrentHandler = NULL;
  mLineNumber = (unsigned int) - 1;

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

        CLGraphicalObject * pGO = dynamic_cast<CLGraphicalObject *>(mCommon.KeyMap.get(graphicalObject));
        if (pGO)
          mCommon.pTextGlyph->setGraphicalObjectKey(pGO->getKey());

        if (text)
          mCommon.pTextGlyph->setText(text);
        else if (originOfText)
          {
            CCopasiObject * pObj = mCommon.KeyMap.get(originOfText);
            CModelEntity * pME = dynamic_cast<CModelEntity *>(pObj);
            CReaction * pR = dynamic_cast<CReaction *>(pObj);
            if (pME)
              mCommon.pTextGlyph->setModelObjectKey(pME->getKey());
            else if (pR)
              mCommon.pTextGlyph->setModelObjectKey(pR->getKey());
            else
              fatalError();
            //TODO: When we have a way to handle references to metab references, this needs to be adapted.
          }

        mCommon.pCurrentLayout->addTextGlyph(mCommon.pTextGlyph);
        mCommon.KeyMap.addFix(key, mCommon.pTextGlyph);
      }
      return;
      break;

    case BoundingBox:
      if (strcmp(pszName, "BoundingBox"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "BoundingBox", mParser.getCurrentLineNumber());
      return;
      break;

    case Position:
      if (strcmp(pszName, "Position"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Position", mParser.getCurrentLineNumber());
      {//workload
        const char * attr;
        attr = mParser.getAttributeValue("x", papszAttrs);
        mCommon.pTextGlyph->setX(CCopasiXMLInterface::DBL(attr));
        attr = mParser.getAttributeValue("y", papszAttrs);
        mCommon.pTextGlyph->setY(CCopasiXMLInterface::DBL(attr));
        return;
      }
      break;

    case Dimensions:
      if (strcmp(pszName, "Dimensions"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Dimensions", mParser.getCurrentLineNumber());
      {//workload
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
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
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
  pdelete(mpCurrentHandler);
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
      //only one type of tags may occur here, so we can throw an exception.
      //No need to silently ignore unknown tags here.
      if (strcmp(pszName, "TextGlyph"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "TextGlyph", mParser.getCurrentLineNumber());

      //only one type of tags may occur here, so if the handler exists
      //it must be the correct one
      if (!mpCurrentHandler)
        mpCurrentHandler = new TextGlyphElement(mParser, mCommon);

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
      if (strcmp(pszName, "TextGlyph"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "TextGlyph", mParser.getCurrentLineNumber());

      //tell the handler where to continue
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

CCopasiXMLParser::AdditionalGOElement::AdditionalGOElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common): CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::AdditionalGOElement::~AdditionalGOElement()
{}

void CCopasiXMLParser::AdditionalGOElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  mpCurrentHandler = NULL;
  mLineNumber = (unsigned int) - 1;

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

        mCommon.pAdditionalGO = new CLGraphicalObject(name);

        mCommon.pCurrentLayout->addGraphicalObject(mCommon.pAdditionalGO);
        mCommon.KeyMap.addFix(key, mCommon.pAdditionalGO);
      }
      return;
      break;

    case BoundingBox:
      if (strcmp(pszName, "BoundingBox"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "BoundingBox", mParser.getCurrentLineNumber());
      return;
      break;

    case Position:
      if (strcmp(pszName, "Position"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Position", mParser.getCurrentLineNumber());
      {//workload
        const char * attr;
        attr = mParser.getAttributeValue("x", papszAttrs);
        mCommon.pAdditionalGO->setX(CCopasiXMLInterface::DBL(attr));
        attr = mParser.getAttributeValue("y", papszAttrs);
        mCommon.pAdditionalGO->setY(CCopasiXMLInterface::DBL(attr));
        return;
      }
      break;

    case Dimensions:
      if (strcmp(pszName, "Dimensions"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Dimensions", mParser.getCurrentLineNumber());
      {//workload
        const char * attr;
        attr = mParser.getAttributeValue("width", papszAttrs);
        mCommon.pAdditionalGO->setWidth(CCopasiXMLInterface::DBL(attr));
        attr = mParser.getAttributeValue("height", papszAttrs);
        mCommon.pAdditionalGO->setHeight(CCopasiXMLInterface::DBL(attr));
        return;
      }
      break;

    default:
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
  pdelete(mpCurrentHandler);
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
      //only one type of tags may occur here, so we can throw an exception.
      //No need to silently ignore unknown tags here.
      if (strcmp(pszName, "AdditionalGraphicalObject"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "AdditionalGraphicalObject", mParser.getCurrentLineNumber());

      //only one type of tags may occur here, so if the handler exists
      //it must be the correct one
      if (!mpCurrentHandler)
        mpCurrentHandler = new AdditionalGOElement(mParser, mCommon);

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
      if (strcmp(pszName, "AdditionalGraphicalObject"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "AdditionalGraphicalObject", mParser.getCurrentLineNumber());

      //tell the handler where to continue
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

CCopasiXMLParser::LayoutElement::LayoutElement(CCopasiXMLParser& parser, SCopasiXMLParserCommon & common): CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::LayoutElement::~LayoutElement()
{}

void CCopasiXMLParser::LayoutElement::start(const XML_Char *pszName, const XML_Char** papszAttrs)
{
  mCurrentElement++; /* We should always be on hte next element */
  mpCurrentHandler = NULL;
  mLineNumber = (unsigned int) - 1;

  switch (mCurrentElement)
    {
    case Layout:
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
        mCommon.KeyMap.addFix(key, mCommon.pCurrentLayout);
        mCommon.pCurrentLayout->setObjectName(name);
      }
      return;
      break;

    case Dimensions:
      if (!strcmp(pszName, "Dimensions"))
        {//workload
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
        mpCurrentHandler = new ListOfCompartmentGlyphsElement(mParser, mCommon);
      break;

    case ListOfMetabGlyphs:
      if (!strcmp(pszName, "ListOfMetabGlyphs"))
        mpCurrentHandler = new ListOfMetabGlyphsElement(mParser, mCommon);
      break;

    case ListOfReactionGlyphs:
      if (!strcmp(pszName, "ListOfReactionGlyphs"))
        mpCurrentHandler = new ListOfReactionGlyphsElement(mParser, mCommon);
      break;

    case ListOfTextGlyphs:
      if (!strcmp(pszName, "ListOfTextGlyphs"))
        mpCurrentHandler = new ListOfTextGlyphsElement(mParser, mCommon);
      break;

    case ListOfAdditionalGOs:
      if (!strcmp(pszName, "ListOfAdditionalGraphicalObjects"))
        mpCurrentHandler = new ListOfAdditionalGOsElement(mParser, mCommon);
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
          pdelete(mpCurrentHandler);
          break;

        case ListOfCompartmentGlyphs:
          if (strcmp(pszName, "ListOfCompartmentGlyphs"))
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "ListOfCompartmentGlyphs", mParser.getCurrentLineNumber());
          pdelete(mpCurrentHandler);
          break;

        case ListOfMetabGlyphs:
          if (strcmp(pszName, "ListOfMetabGlyphs"))
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "ListOfMetabGlyphs", mParser.getCurrentLineNumber());
          pdelete(mpCurrentHandler);
          break;

        case ListOfReactionGlyphs:
          if (strcmp(pszName, "ListOfReactionGlyphs"))
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "ListOfReactionGlyphs", mParser.getCurrentLineNumber());
          pdelete(mpCurrentHandler);
          break;

        case ListOfTextGlyphs:
          if (strcmp(pszName, "ListOfTextGlyphs"))
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "ListOfTextGlyphs", mParser.getCurrentLineNumber());
          pdelete(mpCurrentHandler);
          break;

        case ListOfAdditionalGOs:
          if (strcmp(pszName, "ListOfAdditionalGraphicalObjects"))
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "ListOfAdditionalGraphicalObjects", mParser.getCurrentLineNumber());
          pdelete(mpCurrentHandler);
          break;

        case UNKNOWN_ELEMENT:
          //mCurrentElement = mLastKnownElement;
          mCurrentElement = Layout;
          break;

        default:
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "???", mParser.getCurrentLineNumber());
          break;
        }
    }
  //  pdelete(mpCurrentHandler); //TODO ??? is not done in ModelElement
  return;
}

CCopasiXMLParser::ListOfLayoutsElement::ListOfLayoutsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfLayoutsElement::~ListOfLayoutsElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::ListOfLayoutsElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case ListOfLayouts:
      if (strcmp(pszName, "ListOfLayouts"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "ListOfLayouts", mParser.getCurrentLineNumber());

      //workload
      if (!mCommon.pLayoutList)
        {
          mCommon.pLayoutList = new CListOfLayouts;
        }
      break;

    case Layout:
      //only one type of tags may occur here, so we can throw an exception.
      //No need to silently ignore unknown tags here.
      if (strcmp(pszName, "Layout"))
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                       pszName, "Layout", mParser.getCurrentLineNumber());

      //only one type of tags may occur here, so if the handler exists
      //it must be the correct one
      if (!mpCurrentHandler)
        mpCurrentHandler = new LayoutElement(mParser, mCommon);

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
#endif //WITH_LAYOUT

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
#ifdef COPASI_TSS
        case CCopasiTask::tss:
          mCommon.pCurrentTask = new CTSSTask(mCommon.pTaskList);
          break;
#endif // COPASI_TSS
#ifdef COPASI_TSSA
        case CCopasiTask::tssAnalysis:
          mCommon.pCurrentTask = new CTSSATask(mCommon.pTaskList);
          break;
#endif // COPASI_TSSA
        case CCopasiTask::moieties:
          mCommon.pCurrentTask = new CMoietiesTask(Type, mCommon.pTaskList);
          break;
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
      mCommon.reportReferenceMap[mCommon.CharacterData].push_back(std::pair<std::vector<CRegisteredObjectName>*, unsigned C_INT32>(mCommon.pReport->getHeaderAddr(), mCommon.pReport->getHeaderAddr()->size()));
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
      mCommon.reportReferenceMap[mCommon.CharacterData].push_back(std::pair<std::vector<CRegisteredObjectName>*, unsigned C_INT32>(mCommon.pReport->getBodyAddr(), mCommon.pReport->getBodyAddr()->size()));
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
      mCommon.reportReferenceMap[mCommon.CharacterData].push_back(std::pair<std::vector<CRegisteredObjectName>*, unsigned C_INT32>(mCommon.pReport->getFooterAddr(), mCommon.pReport->getFooterAddr()->size()));
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

CCopasiXMLParser::MiriamAnnotationElement::MiriamAnnotationElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
    mRDF(),
    mLevel(0)
{}

CCopasiXMLParser::MiriamAnnotationElement::~MiriamAnnotationElement()
{
  pdelete(mpCurrentHandler);
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

      pdelete(mpCurrentHandler);

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
