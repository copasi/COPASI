/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/CCopasiXMLParser.cpp,v $
   $Revision: 1.89 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/09 14:50:35 $
   End CVS Header */

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

#include "utilities/CCopasiParameter.h"
#include "utilities/CCopasiParameterGroup.h"
#include "utilities/CSlider.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CMCATask.h"
#include "scan/CScanTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "plot/COutputDefinitionVector.h"
#include "plot/CPlotSpecification.h"
#include "plot/CPlotItem.h"

#define START_ELEMENT   -1
#define UNKNOWN_ELEMENT -2

#ifdef COPASI_TEMPLATE
CCopasiXMLParser::TEMPLATEElement::TEMPLATEElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::TEMPLATEElement::~TEMPLATEElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::TEMPLATEElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case TEMPLATE:
      if (strcmp(pszName, "TEMPLATE")) fatalError();
      break;

#ifdef XXXX
    case etc:
      if (strcmp(pszName, "etc")) fatalError();

      /* If we do not have a etc element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new etcElement(mParser, mCommon);

      /* Push the etc element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;
#endif // XXXX

    default:
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
      break;
    }

  return;
}

void CCopasiXMLParser::TEMPLATEElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
    case TEMPLATE:
      if (strcmp(pszName, "TEMPLATE")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case etc:
      if (strcmp(pszName, "etc")) fatalError();
      mCurrentElement = TEMPLATE;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
      break;
    }

  return;
}

#endif // COPASI_TEMPLATE

CCopasiXMLParser::CCopasiXMLParser(CVersion & version) :
    CExpat(),
    mCommon(),
    mElementHandlerStack(),
    mUnknownElement(*this, this->mCommon)
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
  assert(mElementHandlerStack.size() != 0);
  mElementHandlerStack.top()->end(pszName);
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

CCopasiVectorN< CFunction > * CCopasiXMLParser::getFunctionList() const
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

void CCopasiXMLParser::UnknownElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
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
        CCopasiMessage Message(CCopasiMessage::RAW, MCXML + 3,
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

  switch (mCurrentElement)
    {
    case COPASI:
      if (strcmp(pszName, "COPASI")) fatalError();

      versionMajor = mParser.getAttributeValue("versionMajor", papszAttrs, "0");
      VersionMajor = atoi(versionMajor);
      versionMinor = mParser.getAttributeValue("versionMinor", papszAttrs, "0");
      VersionMinor = atoi(versionMinor);

      mCommon.pVersion->setVersion(VersionMajor, VersionMinor, 0);

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
      if (strcmp(pszName, "ListOfFunctions")) fatalError();
      if (!mCommon.pFunctionList)
        mCommon.pFunctionList = new CCopasiVectorN< CFunction >;
      break;

    case Function:
      if (strcmp(pszName, "Function")) fatalError();

      /* If we do not have a function element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new FunctionElement(mParser, mCommon);

      /* Push the Function element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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
      if (strcmp(pszName, "ListOfFunctions")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Function:
      if (strcmp(pszName, "Function")) fatalError();
      mCurrentElement = ListOfFunctions;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
  CFunction::Type Type;
  const char * Name;
  const char * Positive;
  unsigned C_INT32 index;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case Function:
      if (strcmp(pszName, "Function")) fatalError();

      Key = mParser.getAttributeValue("key", papszAttrs);
      Name = mParser.getAttributeValue("name", papszAttrs);
      type = mParser.getAttributeValue("type", papszAttrs);
      Type = (CFunction::Type) mParser.toEnum(type, CFunction::XMLType);
      Positive = mParser.getAttributeValue("positive", papszAttrs);

      mCommon.mExistingFunction = false;
      mCommon.pFunction = CFunction::createFunction(Type);
      mCommon.pFunction->setName(Name);
      if (mParser.toBool(Positive))
        mCommon.pFunction->setReversible(TriTrue);
      else
        mCommon.pFunction->setReversible(TriFalse);

      /* We have a new function and add it to the list */
      index = mCommon.pFunctionList->getIndex(Name);
      if (index != C_INVALID_INDEX) // A function with that name exists.
        {
          switch ((*mCommon.pFunctionList)[index]->getType())
            {
            case CFunction::MassAction:
              if (Type == CFunction::MassAction)
                {
                  pdelete(mCommon.pFunction);
                  mCommon.pFunction = (*mCommon.pFunctionList)[index];
                  mCommon.mExistingFunction = true;
                }
              else
                {
                  std::string tmp(Name);
                  tmp += "[" + CFunction::TypeName[Type] + "]";
                  index = mCommon.pFunctionList->getIndex(tmp);
                  if (index != C_INVALID_INDEX)
                    mCommon.pFunctionList->remove(tmp);

                  mCommon.pFunction->setName(tmp);
                  mCommon.pFunctionList->add(mCommon.pFunction, true);
                }
              break;

            case CFunction::PreDefined:
              if (Type == CFunction::PreDefined)
                {
                  pdelete(mCommon.pFunction);
                  mCommon.pFunction = (*mCommon.pFunctionList)[index];
                  mCommon.mExistingFunction = true;
                }
              else
                {
                  std::string tmp(Name);
                  tmp += "[" + CFunction::TypeName[Type] + "]";
                  index = mCommon.pFunctionList->getIndex(tmp);
                  if (index != C_INVALID_INDEX)
                    mCommon.pFunctionList->remove(tmp);

                  mCommon.pFunction->setName(tmp);
                  mCommon.pFunctionList->add(mCommon.pFunction, true);
                }
              break;

            case CFunction::UserDefined:
            case CFunction::Expression:
            case CFunction::Base:
              mCommon.pFunctionList->remove(Name);
              mCommon.pFunctionList->add(mCommon.pFunction, true);
              break;
            }
        }
      else
        mCommon.pFunctionList->add(mCommon.pFunction, true);

      mCommon.KeyMap.addFix(Key , mCommon.pFunction);

      break;

    case MathML:
      if (strcmp(pszName, "MathML")) fatalError();

      /* If we do not have a MathML element handler we create one. */
      if (!mpMathMLElement)
        mpMathMLElement = new MathMLElement(mParser, mCommon);

      /* Push the MathML element handler on the stack and call it. */
      mpCurrentHandler = mpMathMLElement;
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    case ListOfParameterDescriptions:
      if (strcmp(pszName, "ListOfParameterDescriptions")) fatalError();

      /* If we do not have a ListOfParameterDescriptions element handler we create one. */
      if (!mpListOfParameterDescriptionsElement)
        mpListOfParameterDescriptionsElement = new ListOfParameterDescriptionsElement(mParser, mCommon);

      /* Push the ListOfParameterDescriptions element handler on the stack and call it. */
      mpCurrentHandler = mpListOfParameterDescriptionsElement;
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
      break;
    }

  return;
}

void CCopasiXMLParser::FunctionElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
    case Function:
      if (strcmp(pszName, "Function")) fatalError();
      if (!mCommon.mExistingFunction)
        mCommon.pFunction->setDescription(mCommon.FunctionDescription);

      mCurrentElement = START_ELEMENT;
      mParser.popElementHandler();

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case MathML:
      if (strcmp(pszName, "MathML")) fatalError();
      break;

    case ListOfParameterDescriptions:
      if (strcmp(pszName, "ListOfParameterDescriptions")) fatalError();
      mCurrentElement = Function;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "MathML")) fatalError();
      break;

    case Text:
      if (strcmp(pszName, "Text")) fatalError();

      /* If we do not have a function element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new TextElement(mParser, mCommon);

      /* Push the Function element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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
      if (strcmp(pszName, "MathML")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Text:
      if (strcmp(pszName, "Text")) fatalError();
      mCommon.FunctionDescription = mCommon.Comment;
      mCommon.Comment = "";
      mCurrentElement = MathML;

      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
      break;
    }
}

CCopasiXMLParser::TextElement::TextElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::TextElement::~TextElement()
{}

void CCopasiXMLParser::TextElement::start(const XML_Char *pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case Text:
      if (strcmp(pszName, "Text")) fatalError();

      mParser.enableCharacterDataHandler(true);
      break;

    default:
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
      break;
    }

  return;
}

void CCopasiXMLParser::TextElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
    case Text:
      if (strcmp(pszName, "Text")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;
      mCommon.Comment = mParser.getCharacterData("\x0a\x0d\t ", "");

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "ListOfParameterDescriptions")) fatalError();
      if (mpCurrentHandler) mpCurrentHandler->reset();

      break;

    case ParameterDescription:
      if (strcmp(pszName, "ParameterDescription")) fatalError();

      /* If we do not have a ParameterDescription element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new ParameterDescriptionElement(mParser, mCommon);

      /* Push the ParameterDescription element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
      break;
    }

  return;
}

void CCopasiXMLParser::ListOfParameterDescriptionsElement::end(const XML_Char *pszName)
{
  CUsageRange UsageDescription;
  const CCopasiVectorN< CUsageRange > * pUsageRanges = NULL;
  unsigned C_INT32 index;

  switch (mCurrentElement)
    {
    case ListOfParameterDescriptions:
      if (strcmp(pszName, "ListOfParameterDescriptions")) fatalError();

      if (!mCommon.mExistingFunction)
        {
          pUsageRanges = & mCommon.pFunction->getParameters().getUsageRanges();
          UsageDescription.setUsage("SUBSTRATE");
          if ((index = pUsageRanges->getIndex("SUBSTRATE")) != C_INVALID_INDEX)
            {
              UsageDescription.setRange((*pUsageRanges)[index]->getLow(),
                                        (*pUsageRanges)[index]->getHigh());
              mCommon.pFunction->getUsageDescriptions().add(UsageDescription);
            }

          UsageDescription.setUsage("PRODUCT");
          if ((index = pUsageRanges->getIndex("PRODUCT")) != C_INVALID_INDEX)
            {
              UsageDescription.setRange((*pUsageRanges)[index]->getLow(),
                                        (*pUsageRanges)[index]->getHigh());
              mCommon.pFunction->getUsageDescriptions().add(UsageDescription);
            }

          UsageDescription.setUsage("MODIFIER");
          if ((index = pUsageRanges->getIndex("MODIFIER")) != C_INVALID_INDEX)
            {
              UsageDescription.setRange((*pUsageRanges)[index]->getLow(),
                                        (*pUsageRanges)[index]->getHigh());
              mCommon.pFunction->getUsageDescriptions().add(UsageDescription);
            }
        }
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case ParameterDescription:
      if (strcmp(pszName, "ParameterDescription")) fatalError();
      mCurrentElement = ListOfParameterDescriptions;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
  const char * Order;
  const char * role; /*substrate, product, modifier, constant, other*/
  //CFunctionParameter::Role Role;
  std::string Role;
  const char * minOccurs;
  unsigned C_INT32 MinOccurs;
  const char * maxOccurs;
  unsigned C_INT32 MaxOccurs;

  //std::string Usage[] = {"SUBSTRATE", "PRODUCT", "MODIFIER", "PARAMETER"};
  CFunctionParameter * pParm = NULL;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case ParameterDescription:
      if (strcmp(pszName, "ParameterDescription")) fatalError();
      Key = mParser.getAttributeValue("key", papszAttrs);
      Name = mParser.getAttributeValue("name", papszAttrs);

      Order = mParser.getAttributeValue("order", papszAttrs);
      if ((unsigned C_INT32) atoi(Order) != mOrder) fatalError();
      mOrder++;

      role = mParser.getAttributeValue("role", papszAttrs);
      //Role = (CFunctionParameter::Role) mParser.toEnum(role, CFunctionParameter::RoleName);
      //if (Role == -1) fatalError();
      Role = CFunctionParameter::convertXMLRoleNameToInternal(role);
      if (Role == "") fatalError();

      minOccurs = mParser.getAttributeValue("minOccurs", papszAttrs, "1");
      MinOccurs = atoi(minOccurs);

      maxOccurs = mParser.getAttributeValue("maxOccurs", papszAttrs , "1");
      if ("unbounded" == maxOccurs) MaxOccurs = (unsigned C_INT32) - 1;
      else MaxOccurs = atoi(maxOccurs);

      if (mCommon.mExistingFunction)
        {
          mCommon.KeyMap.addFix(Key, mCommon.pFunction->getParameters()[Name]);
        }
      else
        {
          pParm = new CFunctionParameter();
          pParm->setName(Name);
          pParm->setUsage(Role);

          if (MaxOccurs == 1 && MinOccurs == 1)
            pParm->setType(CFunctionParameter::FLOAT64);
          else
            pParm->setType(CFunctionParameter::VFLOAT64);

          mCommon.pFunction->getParameters().add(pParm, true);
          mCommon.KeyMap.addFix(Key, pParm);
        }
      break;

    default:
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
      if (strcmp(pszName, "ParameterDescription")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case Model:
      if (strcmp(pszName, "Model")) fatalError();

      Key = mParser.getAttributeValue("key", papszAttrs);
      Name = mParser.getAttributeValue("name", papszAttrs);

      timeUnit = mParser.getAttributeValue("timeUnit", papszAttrs);
      TimeUnit =
        (CModel::TimeUnit) mParser.toEnum(timeUnit, CModel::TimeUnitName);
      if (TimeUnit == -1) fatalError();

      volumeUnit = mParser.getAttributeValue("volumeUnit", papszAttrs);
      VolumeUnit =
        (CModel::VolumeUnit) mParser.toEnum(volumeUnit, CModel::VolumeUnitName);
      if (VolumeUnit == -1) fatalError();

      quantityUnit = mParser.getAttributeValue("quantityUnit", papszAttrs);
      QuantityUnit =
        (CModel::QuantityUnit) mParser.toEnum(quantityUnit, CModel::QuantityUnitName);
      if (QuantityUnit == -1) fatalError();

      StateVariable = mParser.getAttributeValue("stateVariable", papszAttrs);

      if (!mCommon.pModel) mCommon.pModel = new CModel();
      mCommon.KeyMap.addFix(Key, mCommon.pModel);
      mCommon.pModel->setTitle(Name);
      mCommon.pModel->setTimeUnit(TimeUnit);
      mCommon.pModel->setVolumeUnit(VolumeUnit);
      mCommon.pModel->setQuantityUnit(QuantityUnit);
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
      if (strcmp(pszName, "Model")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Comment:
      if (strcmp(pszName, "Comment")) fatalError();

      mCommon.pModel->setComments(mCommon.Comment);
      mCommon.Comment = "";

      pdelete(mpCurrentHandler);
      break;

    case ListOfCompartments:
      if (strcmp(pszName, "ListOfCompartments")) fatalError();
      pdelete(mpCurrentHandler);
      break;

    case ListOfMetabolites:
      if (strcmp(pszName, "ListOfMetabolites")) fatalError();
      pdelete(mpCurrentHandler);
      break;

    case ListOfModelValues:
      if (strcmp(pszName, "ListOfModelValues")) fatalError();
      pdelete(mpCurrentHandler);
      break;

    case ListOfReactions:
      if (strcmp(pszName, "ListOfReactions")) fatalError();
      pdelete(mpCurrentHandler);
      break;

    case StateTemplate:
      if (strcmp(pszName, "StateTemplate")) fatalError();
      pdelete(mpCurrentHandler);
      break;

    case InitialState:
      if (strcmp(pszName, "InitialState")) fatalError();
      pdelete(mpCurrentHandler);
      mCurrentElement = Model;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
      break;
    }

  return;
}

CCopasiXMLParser::CommentElement::CommentElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::CommentElement::~CommentElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::CommentElement::start(const XML_Char *pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case Comment:
      if (strcmp(pszName, "Comment")) fatalError();
      mParser.enableCharacterDataHandler();
      break;

    case Ignore:
      break;

    default:
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
      break;
    }

  return;
}

void CCopasiXMLParser::CommentElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
    case Comment:
      if (strcmp(pszName, "Comment")) fatalError();
      mCommon.Comment = mParser.getCharacterData();

      {
        // remove leading whitepsaces
        std::string::size_type pos = mCommon.Comment.find_first_not_of("\x0a\x0d\t ");
        if (pos != 0) mCommon.Comment.erase(0, pos);

        // remove trailing whitepsace
        pos = mCommon.Comment.find_last_not_of("\x0a\x0d\t ");
        if (pos < mCommon.Comment.length())
          mCommon.Comment = mCommon.Comment.substr(0, pos + 1);
      }

      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      pdelete(mpCurrentHandler);

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Ignore:
      mCurrentElement = Comment;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "ListOfCompartments")) fatalError();
      mCommon.pModel->getCompartments().resize(0);
      break;

    case Compartment:
      if (strcmp(pszName, "Compartment")) fatalError();

      /* If we do not have a function element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new CompartmentElement(mParser, mCommon);

      /* Push the Compartment element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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
      if (strcmp(pszName, "ListOfCompartments")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Compartment:
      if (strcmp(pszName, "Compartment")) fatalError();
      mCurrentElement = ListOfCompartments;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
      break;
    }

  return;
}

CCopasiXMLParser::CompartmentElement::CompartmentElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::CompartmentElement::~CompartmentElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::CompartmentElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  CCompartment * pCompartment;
  const char * Key;
  const char * Name;
  const char * StateVariable;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case Compartment:
      if (strcmp(pszName, "Compartment")) fatalError();

      Key = mParser.getAttributeValue("key", papszAttrs);
      Name = mParser.getAttributeValue("name", papszAttrs);
      StateVariable = mParser.getAttributeValue("stateVariable", papszAttrs);

      pCompartment = new CCompartment();
      mCommon.KeyMap.addFix(Key, pCompartment);
      pCompartment->setObjectName(Name);

      mCommon.pModel->getCompartments().add(pCompartment, true);
      break;

    default:
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
      break;
    }

  return;
}

void CCopasiXMLParser::CompartmentElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
    case Compartment:
      if (strcmp(pszName, "Compartment")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "ListOfMetabolites")) fatalError();
      break;

    case Metabolite:
      if (strcmp(pszName, "Metabolite")) fatalError();

      /* If we do not have a function element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new MetaboliteElement(mParser, mCommon);

      /* Push the Metabolite element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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
      if (strcmp(pszName, "ListOfMetabolites")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Metabolite:
      if (strcmp(pszName, "Metabolite")) fatalError();
      mCurrentElement = ListOfMetabolites;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
      break;
    }

  return;
}

CCopasiXMLParser::MetaboliteElement::MetaboliteElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::MetaboliteElement::~MetaboliteElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::MetaboliteElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  CMetab * pMetabolite;
  CCompartment * pCompartment = NULL;
  const char * Key;
  const char * Name;
  const char * Compartment;
  const char * status;
  CMetab::Status Status;
  const char * StateVariable;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case Metabolite:
      if (strcmp(pszName, "Metabolite")) fatalError();

      Key = mParser.getAttributeValue("key", papszAttrs);
      Name = mParser.getAttributeValue("name", papszAttrs);
      Compartment = mParser.getAttributeValue("compartment", papszAttrs);
      status = mParser.getAttributeValue("status", papszAttrs);
      Status = (CMetab::Status) mParser.toEnum(status, CMetab::XMLStatus);
      StateVariable = mParser.getAttributeValue("stateVariable", papszAttrs);

      pMetabolite = new CMetab();
      mCommon.KeyMap.addFix(Key, pMetabolite);
      pMetabolite->setObjectName(Name);
      pMetabolite->setStatus(Status);

      pCompartment =
        dynamic_cast< CCompartment* >(mCommon.KeyMap.get(Compartment));
      if (!pCompartment) fatalError();

      pCompartment->addMetabolite(pMetabolite);
      mCommon.pModel->getMetabolites().add(pMetabolite);
      break;

    default:
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
      break;
    }

  return;
}

void CCopasiXMLParser::MetaboliteElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
    case Metabolite:
      if (strcmp(pszName, "Metabolite")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "ListOfModelValues")) fatalError();
      break;

    case ModelValue:
      if (strcmp(pszName, "ModelValue")) fatalError();

      /* If we do not have a function element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new ModelValueElement(mParser, mCommon);

      /* Push the Metabolite element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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
      if (strcmp(pszName, "ListOfModelValues")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case ModelValue:
      if (strcmp(pszName, "ModelValue")) fatalError();
      mCurrentElement = ListOfModelValues;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
      break;
    }

  return;
}

CCopasiXMLParser::ModelValueElement::ModelValueElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ModelValueElement::~ModelValueElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::ModelValueElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  CModelValue * pMV;
  const char * Key;
  const char * Name;
  const char * status;
  CModelEntity::Status Status;
  const char * StateVariable;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case ModelValue:
      if (strcmp(pszName, "ModelValue")) fatalError();

      Key = mParser.getAttributeValue("key", papszAttrs);
      Name = mParser.getAttributeValue("name", papszAttrs);
      status = mParser.getAttributeValue("status", papszAttrs);
      Status = (CMetab::Status) mParser.toEnum(status, CModelEntity::XMLStatus);
      StateVariable = mParser.getAttributeValue("stateVariable", papszAttrs);

      pMV = new CModelValue();
      mCommon.KeyMap.addFix(Key, pMV);
      pMV->setObjectName(Name);
      pMV->setStatus(Status);

      mCommon.pModel->getModelValues().add(pMV, true);
      break;

    default:
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
      break;
    }

  return;
}

void CCopasiXMLParser::ModelValueElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
    case ModelValue:
      if (strcmp(pszName, "ModelValue")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "ListOfReactions")) fatalError();
      mCommon.pModel->getReactions().resize(0);
      break;

    case Reaction:
      if (strcmp(pszName, "Reaction")) fatalError();

      /* If we do not have a function element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new ReactionElement(mParser, mCommon);

      /* Push the Reaction element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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
      if (strcmp(pszName, "ListOfReactions")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Reaction:
      if (strcmp(pszName, "Reaction")) fatalError();
      mCurrentElement = ListOfReactions;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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

  mCurrentElement++; /* We should always be on the next element */
  mpCurrentHandler = NULL;

  switch (mCurrentElement)
    {
    case Reaction:
      if (strcmp(pszName, "Reaction")) fatalError();
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
  switch (mCurrentElement)
    {
    case Reaction:
      if (strcmp(pszName, "Reaction")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case ListOfSubstrates:
      if (strcmp(pszName, "ListOfSubstrates")) fatalError();
      break;

    case ListOfProducts:
      if (strcmp(pszName, "ListOfProducts")) fatalError();
      break;

    case ListOfModifiers:
      if (strcmp(pszName, "ListOfModifiers")) fatalError();
      break;

    case ListOfConstants:
      if (strcmp(pszName, "ListOfConstants")) fatalError();
      break;

    case KineticLaw:
      if (strcmp(pszName, "KineticLaw")) fatalError();
      mCurrentElement = Reaction;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "ListOfSubstrates")) fatalError();
      break;

    case Substrate:
      if (strcmp(pszName, "Substrate")) fatalError();

      /* If we do not have a Substrate element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new SubstrateElement(mParser, mCommon);

      /* Push the Substrate element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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
      if (strcmp(pszName, "ListOfSubstrates")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Substrate:
      if (strcmp(pszName, "Substrate")) fatalError();
      mCurrentElement = ListOfSubstrates;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "Substrate")) fatalError();
      Metabolite = mParser.getAttributeValue("metabolite", papszAttrs);
      Stoichiometry = mParser.getAttributeValue("stoichiometry", papszAttrs);

      pMetabolite = dynamic_cast< CMetab * >(mCommon.KeyMap.get(Metabolite));
      if (!pMetabolite) fatalError();

      mCommon.pReaction->addSubstrate(pMetabolite->getKey(),
                                      atof(Stoichiometry));
      break;

    default:
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
      if (strcmp(pszName, "Substrate")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "ListOfProducts")) fatalError();
      break;

    case Product:
      if (strcmp(pszName, "Product")) fatalError();

      /* If we do not have a Product element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new ProductElement(mParser, mCommon);

      /* Push the Product element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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
      if (strcmp(pszName, "ListOfProducts")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Product:
      if (strcmp(pszName, "Product")) fatalError();
      mCurrentElement = ListOfProducts;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "Product")) fatalError();
      Metabolite = mParser.getAttributeValue("metabolite", papszAttrs);
      Stoichiometry = mParser.getAttributeValue("stoichiometry", papszAttrs);

      pMetabolite = dynamic_cast< CMetab * >(mCommon.KeyMap.get(Metabolite));
      if (!pMetabolite) fatalError();

      mCommon.pReaction->addProduct(pMetabolite->getKey(),
                                    atof(Stoichiometry));
      break;

    default:
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
      if (strcmp(pszName, "Product")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "ListOfModifiers")) fatalError();
      break;

    case Modifier:
      if (strcmp(pszName, "Modifier")) fatalError();

      /* If we do not have a Modifier element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new ModifierElement(mParser, mCommon);

      /* Push the Modifier element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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
      if (strcmp(pszName, "ListOfModifiers")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Modifier:
      if (strcmp(pszName, "Modifier")) fatalError();
      mCurrentElement = ListOfModifiers;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "Modifier")) fatalError();
      Metabolite = mParser.getAttributeValue("metabolite", papszAttrs);
      Stoichiometry = mParser.getAttributeValue("stoichiometry", papszAttrs);

      pMetabolite = dynamic_cast< CMetab * >(mCommon.KeyMap.get(Metabolite));
      if (!pMetabolite) fatalError();

      mCommon.pReaction->addModifier(pMetabolite->getKey(),
                                     atof(Stoichiometry));
      break;

    default:
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
      if (strcmp(pszName, "Modifier")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "ListOfConstants")) fatalError();
      mCommon.pReaction->getParameters().clear();
      break;

    case Constant:
      if (strcmp(pszName, "Constant")) fatalError();

      /* If we do not have a Constant element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new ConstantElement(mParser, mCommon);

      /* Push the Constant element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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
      if (strcmp(pszName, "ListOfConstants")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Constant:
      if (strcmp(pszName, "Constant")) fatalError();
      mCurrentElement = ListOfConstants;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "Constant")) fatalError();

      Key = mParser.getAttributeValue("key", papszAttrs);
      Name = mParser.getAttributeValue("name", papszAttrs);
      Value = mParser.getAttributeValue("value", papszAttrs);

      mCommon.pReaction->
      getParameters().addParameter(Name,
                                   CCopasiParameter::DOUBLE,
                                   (C_FLOAT64) atof(Value));

      mCommon.KeyMap.addFix(Key,
                            mCommon.pReaction->getParameters().getParameter(Name));

      break;

    default:
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
      if (strcmp(pszName, "Constant")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "KineticLaw")) fatalError();

      Function = mParser.getAttributeValue("function", papszAttrs);

      pFunction =
        dynamic_cast< CFunction* >(mCommon.KeyMap.get(Function));
      if (!pFunction) fatalError();

      mCommon.pReaction->setFunction(pFunction);
      break;

    case ListOfCallParameters:
      if (strcmp(pszName, "ListOfCallParameters")) fatalError();

      /* If we do not have a etc element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new ListOfCallParametersElement(mParser, mCommon);

      /* Push the etc element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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
      if (strcmp(pszName, "KineticLaw")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case ListOfCallParameters:
      if (strcmp(pszName, "ListOfCallParameters")) fatalError();
      mCurrentElement = KineticLaw;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "ListOfCallParameters")) fatalError();
      break;

    case CallParameter:
      if (strcmp(pszName, "CallParameter")) fatalError();

      /* If we do not have a CallParameter element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new CallParameterElement(mParser, mCommon);

      /* Push the CallParameter element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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
      if (strcmp(pszName, "ListOfCallParameters")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case CallParameter:
      if (strcmp(pszName, "CallParameter")) fatalError();
      mCurrentElement = ListOfCallParameters;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "CallParameter")) fatalError();

      FunctionParameter =
        mParser.getAttributeValue("functionParameter", papszAttrs);

      mpFunctionParameter =
        dynamic_cast< CFunctionParameter* >(mCommon.KeyMap.get(FunctionParameter));
      if (!mpFunctionParameter) fatalError();

      mCommon.SourceParameterKeys.clear();
      break;

    case SourceParameter:
      if (strcmp(pszName, "SourceParameter")) fatalError();

      /* If we do not have a SourceParameter element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new SourceParameterElement(mParser, mCommon);

      /* Push the SourceParameter element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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
      if (strcmp(pszName, "CallParameter")) fatalError();
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
      if (strcmp(pszName, "SourceParameter")) fatalError();
      mCurrentElement = CallParameter;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
  //CMetab * pMetabolite;
  CModelEntity * pME;
  switch (mCurrentElement)
    {
    case SourceParameter:
      if (strcmp(pszName, "SourceParameter")) fatalError();

      Reference =
        mParser.getAttributeValue("reference", papszAttrs);

      pObject = mCommon.KeyMap.get(Reference);

      /*if ((pParameter = dynamic_cast< CCopasiParameter * >(pObject)))
        mCommon.SourceParameterKeys.push_back(pParameter->getKey());
      else if ((pMetabolite = dynamic_cast< CMetab * >(pObject)))
        mCommon.SourceParameterKeys.push_back(pMetabolite->getKey());
      else fatalError();*/

      if ((pParameter = dynamic_cast< CCopasiParameter * >(pObject)))
        mCommon.SourceParameterKeys.push_back(pParameter->getKey());
      else if ((pME = dynamic_cast<CModelEntity*>(pObject)))
        mCommon.SourceParameterKeys.push_back(pME->getKey());
      else fatalError();

      break;

    default:
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
      if (strcmp(pszName, "SourceParameter")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "StateTemplate")) fatalError();

      mCommon.StateVariableList.clear();
      break;

    case StateTemplateVariable:
      if (strcmp(pszName, "StateTemplateVariable")) fatalError();

      /* If we do not have a StateTemplateVariable element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new StateTemplateVariableElement(mParser, mCommon);

      /* Push the StateTemplateVariable element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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
      if (strcmp(pszName, "StateTemplate")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case StateTemplateVariable:
      if (strcmp(pszName, "StateTemplateVariable")) fatalError();
      mCurrentElement = StateTemplate;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
  const char * Key;
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
      if (strcmp(pszName, "StateTemplateVariable")) fatalError();

      Key = mParser.getAttributeValue("key", papszAttrs);
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
      if (strcmp(pszName, "StateTemplateVariable")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "InitialState")) fatalError();

      Type = mParser.getAttributeValue("type", papszAttrs, "initialState");
      if (strcmp(Type, "initialState")) fatalError();

      mParser.enableCharacterDataHandler();
      break;

    default:
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
      break;
    }

  return;
}

void CCopasiXMLParser::InitialStateElement::end(const XML_Char *pszName)
{
  //std::istringstream Values;
  //const char* s;
  std::vector< std::string >::iterator it;
  std::vector< std::string >::iterator end;
  //double Value;
  CModel * pModel;
  CModelEntity * pME;

  switch (mCurrentElement)
    {
    case InitialState:
      if (strcmp(pszName, "InitialState")) fatalError();

      /*Values.str(mParser.getCharacterData("\x0a\x0d\t ", " "));

      it = mCommon.StateVariableList.begin();
      end = mCommon.StateVariableList.end();

      for (Values >> Value; it != end && !Values.fail(); ++it, Values >> Value)
        {
          //handles compartments, metabs, and model values
          pME = dynamic_cast< CModelEntity* >(GlobalKeys.get(*it));
          if (pME)
            {
              pME->setInitialValue(Value);
              pME->setValue(Value);
              continue;
            }

          pModel = dynamic_cast< CModel* >(GlobalKeys.get(*it));
          if (pModel)
            {
              pModel->setTime(Value);
              continue;
            }

          fatalError();
        }

      if (it != end || !Values.fail() || !Values.eof()) fatalError();*/

      {
        std::string Data = mParser.getCharacterData("\x0a\x0d\t ", " ");

        const char * ptr = Data.c_str();
        char * endptr = NULL;

        it = mCommon.StateVariableList.begin();
        end = mCommon.StateVariableList.end();

        for (; it != end; ++it)
          {
            C_FLOAT64 d = strtod(ptr, &endptr);
            if (ptr == endptr) break;
            ptr = endptr;

            //handles compartments, metabs, and model values
            pME = dynamic_cast< CModelEntity* >(GlobalKeys.get(*it));
            if (pME)
              {
                pME->setInitialValue(d);
                pME->setValue(d);
                continue;
              }

            pModel = dynamic_cast< CModel* >(GlobalKeys.get(*it));
            if (pModel)
              {
                pModel->setTime(d);
                continue;
              }

            fatalError();
          }

        if (it != end) fatalError();
      }

      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "ListOfPlotItems")) fatalError();
      break;

    case PlotItem:
      if (strcmp(pszName, "PlotItem")) fatalError();
      // If we do not have a plot specification element handler, we create one
      if (!mpCurrentHandler)
        {
          mpCurrentHandler = new PlotItemElement(mParser, mCommon);
        }
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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
      if (strcmp(pszName, "ListOfPlotItems")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;
      mParser.onEndElement(pszName);
      break;

    case PlotItem:
      if (strcmp(pszName, "PlotItem")) fatalError();
      /*std::cout << "Number of Channels in current plot item: " << mCommon.pCurrentPlotItem->getChannels().size() << std::endl;
      unsigned int counter;
      for(counter=0; counter <  mCommon.pCurrentPlotItem->getChannels().size(); counter++){
        std::cout << "Channel " << counter << ": " << mCommon.pCurrentPlotItem->getChannels()[counter] << std::endl;
      }*/
      mCommon.pCurrentPlotItem = mCommon.pCurrentPlot;
      mCurrentElement = ListOfPlotItems;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "ListOfChannels")) fatalError();
      break;

    case ChannelSpec:
      if (strcmp(pszName, "ChannelSpec")) fatalError();
      if (!mpCurrentHandler)
        {
          mpCurrentHandler = new ChannelSpecElement(mParser, mCommon);
        }
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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
      if (strcmp(pszName, "ListOfChannels")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;
      mParser.onEndElement(pszName);
      break;

    case ChannelSpec:
      if (strcmp(pszName, "ChannelSpec")) fatalError();
      mCommon.pCurrentPlotItem->getChannels().push_back(*(mCommon.pCurrentChannelSpec));
      //std::cout << "Adding new Channel to PlotItem: " << mCommon.pCurrentChannelSpec << std::endl;
      delete mCommon.pCurrentChannelSpec;
      mCommon.pCurrentChannelSpec = NULL;
      mCurrentElement = ListOfChannels;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "ListOfPlots")) fatalError();
      if (!mCommon.pPlotList)
        {
          mCommon.pPlotList = new COutputDefinitionVector;
        }
      break;

    case PlotSpecification:
      if (strcmp(pszName, "PlotSpecification")) fatalError();
      // If we do not have a plot specification element handler, we create one
      if (!mpCurrentHandler)
        {
          mpCurrentHandler = new PlotSpecificationElement(mParser, mCommon);
        }
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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
      if (strcmp(pszName, "ListOfPlots")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;
      mParser.onEndElement(pszName);
      break;

    case PlotSpecification:
      if (strcmp(pszName, "PlotSpecification")) fatalError();
      // add mCommon.pCurrentPlot to the listOfPlots and set
      // mCommon.pCurrentPlot to NULL
      mCommon.pPlotList->add(*mCommon.pCurrentPlot);
      delete mCommon.pCurrentPlot;
      mCommon.pCurrentPlot = NULL;
      mCommon.pCurrentPlotItem = NULL;
      mCurrentElement = ListOfPlots;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "ChannelSpec")) fatalError();
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
          min = atof(sMin);
          mCommon.pCurrentChannelSpec->min = min;
        }
      sMax = mParser.getAttributeValue("max", papszAttrs, false);
      if (sMax == NULL)
        {
          mCommon.pCurrentChannelSpec->maxAutoscale = true;
        }
      else
        {
          max = atof(sMax);
          mCommon.pCurrentChannelSpec->max = max;
        }
      return;
      break;

    default:
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
      if (strcmp(pszName, "ChannelSpec")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;
      mParser.onEndElement(pszName);
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "PlotItem")) fatalError();
      // create a new CPlotSpecification element depending on the type
      name = mParser.getAttributeValue("name", papszAttrs);
      sType = mParser.getAttributeValue("type", papszAttrs);
      mCommon.pCurrentPlotItem = mCommon.pCurrentPlot->createItem(name, CPlotItem::XMLNameToEnum(sType));
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
      if (strcmp(pszName, "PlotItem")) fatalError();
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
                  p->setValue(*((C_INT32*)mCommon.pCurrentParameter->getValue()));
                  break;

                case CCopasiParameter::UINT:
                  p->setValue(*((unsigned C_INT32*)mCommon.pCurrentParameter->getValue()));
                  break;

                case CCopasiParameter::DOUBLE:
                  p->setValue(*((C_FLOAT64*)mCommon.pCurrentParameter->getValue()));
                  break;

                case CCopasiParameter::UDOUBLE:
                  p->setValue(*((C_FLOAT64*)mCommon.pCurrentParameter->getValue()));
                  break;

                case CCopasiParameter::BOOL:
                  p->setValue(*((bool*)mCommon.pCurrentParameter->getValue()));
                  break;

                case CCopasiParameter::STRING:
                  p->setValue(*((std::string*)mCommon.pCurrentParameter->getValue()));
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
              CCopasiMessage Message(CCopasiMessage::RAW, MCXML + 4,
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
      break;

    default:
      fatalError();
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
  const char * name;
  const char * sType;
  const char * active;

  switch (mCurrentElement)
    {
    case PlotSpecification:
      if (strcmp(pszName, "PlotSpecification")) fatalError();
      // create a new CPlotSpecification element depending on the type
      mCommon.pCurrentPlot = new CPlotSpecification();
      mCommon.pCurrentPlotItem = mCommon.pCurrentPlot;
      name = mParser.getAttributeValue("name", papszAttrs);
      mCommon.pCurrentPlot->setObjectName(name);
      sType = mParser.getAttributeValue("type", papszAttrs);
      mCommon.pCurrentPlot->setType(CPlotItem::XMLNameToEnum(sType));
      active = mParser.getAttributeValue("active", papszAttrs, "true");

      mCommon.pCurrentPlot->setActive(mParser.toBool(active));
      return;
      break;

    case Parameter:
      if (!strcmp(pszName, "Parameter"))
        {
          if (!mpCurrentHandler)
            {
              mpCurrentHandler = new ParameterElement(mParser, mCommon);
            }
        }
      break;

    case ParameterGroup:
      if (!strcmp(pszName, "ParameterGroup"))
        {
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
          mCurrentElement = PlotSpecification;
        }
      break;

    case ParameterGroup:
      if (strcmp(pszName, "ParameterGroup"))
        {
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
      break;

    default:
      fatalError();
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
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::ListOfTasksElement::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case ListOfTasks:
      if (strcmp(pszName, "ListOfTasks")) fatalError();
      if (!mCommon.pTaskList)
        {
          mCommon.pTaskList = new CCopasiVectorN<CCopasiTask>;
        }
      break;

    case Task:
      if (strcmp(pszName, "Task")) fatalError();
      /* If we do not have a task element handler, we create one */
      if (!mpCurrentHandler)
        {
          mpCurrentHandler = new TaskElement(mParser, mCommon);
        }
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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
      if (strcmp(pszName, "ListOfTasks")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;
      mParser.onEndElement(pszName);
      break;

    case Task:
      if (strcmp(pszName, "Task")) fatalError();

      if (mCommon.pCurrentTask)
        {
          mCommon.pTaskList->add(mCommon.pCurrentTask);
          mCommon.pCurrentTask = NULL;
        }

      mCurrentElement = ListOfTasks;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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

  switch (mCurrentElement)
    {
    case Task:
      if (strcmp(pszName, "Task")) fatalError();

      mCommon.pCurrentTask = NULL;

      Key = mParser.getAttributeValue("key", papszAttrs, false);
      type = mParser.getAttributeValue("type", papszAttrs);
      Type = (CCopasiTask::Type)mParser.toEnum(type, CCopasiTask::XMLType);
      Scheduled = mParser.toBool(mParser.getAttributeValue("scheduled", papszAttrs, "false"));

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
        case CCopasiTask::mca:
          mCommon.pCurrentTask = new CMCATask(mCommon.pTaskList);
          break;
        default:
          mParser.pushElementHandler(&mParser.mUnknownElement);
          mParser.onStartElement(pszName, papszAttrs);

          CCopasiMessage Message(CCopasiMessage::RAW, MCXML + 5,
                                 type, mParser.getCurrentLineNumber());
          break;
        }

      if (Key && mCommon.pCurrentTask)
        {
          mCommon.pCurrentTask->setScheduled(Scheduled);
          mCommon.pCurrentTask->getProblem()->setModel(mCommon.pModel);
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
      if (strcmp(pszName, "Task")) fatalError();
      if (!mCommon.pCurrentTask)
        CCopasiMessage::getLastMessage();

      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;
      mParser.onEndElement(pszName);
      break;

    case Report:
      if (strcmp(pszName, "Report")) fatalError();
      // do nothing, the pointer to the correct report definition can
      // only be set after the report definitions have been read.
      break;

    case Problem:
      if (strcmp(pszName, "Problem")) fatalError();
      break;

    case Method:
      if (strcmp(pszName, "Method")) fatalError();
      mCurrentElement = Task;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
  std::string sAppend;
  bool append;
  std::string reference;

  switch (mCurrentElement)
    {
    case Report:
      if (strcmp(pszName, "Report")) fatalError();
      reference = mParser.getAttributeValue("reference", papszAttrs);
      target = mParser.getAttributeValue("target", papszAttrs);

      sAppend = mParser.toBool(mParser.getAttributeValue("append", papszAttrs, "false"));
      append = mParser.toBool(sAppend.c_str());
      mCommon.pCurrentTask->getReport().setAppend(append);
      mCommon.pCurrentTask->getReport().setTarget(target);
      if (mCommon.taskReferenceMap.find(reference) == mCommon.taskReferenceMap.end())
        {
          mCommon.taskReferenceMap[reference] = std::vector<CCopasiTask*>();
        }
      mCommon.taskReferenceMap[reference].push_back(mCommon.pCurrentTask);
      break;

    default:
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
      if (strcmp(pszName, "Report")) fatalError();
      mCurrentElement = START_ELEMENT;
      mParser.popElementHandler();
      mParser.onEndElement(pszName);
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "Problem")) fatalError();
      mCurrentElement = START_ELEMENT;
      mParser.popElementHandler();
      mParser.onEndElement(pszName);
      break;

    case Parameter:
      if (strcmp(pszName, "Parameter")) fatalError();
      // add the parameter in mCommon.pCurrentParameter to the Problem of
      // the current task.
      p = mCommon.pCurrentTask->getProblem()->getParameter(mCommon.pCurrentParameter->getObjectName());
      if (p)
        {
          switch (mCommon.pCurrentParameter->getType())
            {
            case CCopasiParameter::INT:
              p->setValue(*((C_INT32*)mCommon.pCurrentParameter->getValue()));
              break;

            case CCopasiParameter::UINT:
              p->setValue(*((unsigned C_INT32*)mCommon.pCurrentParameter->getValue()));
              break;

            case CCopasiParameter::DOUBLE:
              p->setValue(*((C_FLOAT64*)mCommon.pCurrentParameter->getValue()));
              break;

            case CCopasiParameter::UDOUBLE:
              p->setValue(*((C_FLOAT64*)mCommon.pCurrentParameter->getValue()));
              break;

            case CCopasiParameter::BOOL:
              p->setValue(*((bool*)mCommon.pCurrentParameter->getValue()));
              break;

            case CCopasiParameter::STRING:
              p->setValue(*((std::string*)mCommon.pCurrentParameter->getValue()));
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
          CCopasiMessage Message(CCopasiMessage::RAW, MCXML + 4,
                                 mCommon.pCurrentParameter->getObjectName().c_str(),
                                 mLineNumber);
        }
      pdelete(mCommon.pCurrentParameter);
      mCurrentElement = Problem;
      break;

    case ParameterGroup:
      if (strcmp(pszName, "ParameterGroup")) fatalError();
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
            case CCopasiParameter::INVALID:
              break;

            default:
              fatalError();
              break;
            }
        }
      else
        {
          CCopasiMessage Message(CCopasiMessage::RAW, MCXML + 4,
                                 mCommon.pCurrentParameter->getObjectName().c_str(),
                                 mLineNumber);
        }
      pdelete(mCommon.pCurrentParameter);
      mCurrentElement = Problem;
      break;

    case InitialState:
      if (strcmp(pszName, "InitialState")) fatalError();
      // get the string that corresponds to initial state from
      // mComon.Comment, parse it to get the individual values and set
      // the values.
      // !!!!!!!!!!!!!!!!
      mCommon.Comment = "";
      mCurrentElement = Problem;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "InitialState")) fatalError();
      mParser.enableCharacterDataHandler(true);
      break;

    default:
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
      if (strcmp(pszName, "InitialState")) fatalError();
      mCommon.Comment = mParser.getCharacterData("\x0a\x0d\t ", "");
      mCurrentElement = START_ELEMENT;
      mParser.popElementHandler();
      mParser.onEndElement(pszName);
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "ParameterGroup")) fatalError();

      mCommon.pCurrentParameter = mCommon.ParameterGroupStack.top();
      mCommon.ParameterGroupStack.pop();
      mCurrentElement = START_ELEMENT;

      mParser.popElementHandler();
      mParser.onEndElement(pszName);

      break;

    case Parameter:
      if (!strcmp(pszName, "Parameter") && !strcmp(pszName, "ParameterGroup")) fatalError();

      mCommon.ParameterGroupStack.top()->addParameter(* mCommon.pCurrentParameter);
      pdelete(mCommon.pCurrentParameter);

      mCurrentElement = ParameterGroup;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "Parameter")) fatalError();
      // Parameter has attributes name, type and value
      name = mParser.getAttributeValue("name", papszAttrs);
      sType = mParser.getAttributeValue("type", papszAttrs);
      sValue = mParser.getAttributeValue("value", papszAttrs);
      if (sType == "float")
        {
          type = CCopasiParameter::DOUBLE;
          double d = atof(sValue.c_str());
          pValue = &d;
        }
      else if (sType == "unsignedFloat")
        {
          type = CCopasiParameter::UDOUBLE;
          d = atof(sValue.c_str());
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
      if (strcmp(pszName, "Parameter")) fatalError();
      mCurrentElement = START_ELEMENT;
      mParser.popElementHandler();
      mParser.onEndElement(pszName);
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
          CCopasiMethod::SubType type = CCopasiMethod::XMLNameToEnum(sType.c_str());
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
      if (strcmp(pszName, "Method")) fatalError();
      mCurrentElement = START_ELEMENT;
      mParser.popElementHandler();
      mParser.onEndElement(pszName);
      break;

    case Parameter:
      if (strcmp(pszName, "Parameter")) fatalError();
      // add the parameter in mCommon.pCurrentParameter to the Problem of
      // the current task.

      p = mCommon.pCurrentTask->getMethod()->getParameter(mCommon.pCurrentParameter->getObjectName());
      if (p)
        {
          switch (mCommon.pCurrentParameter->getType())
            {
            case CCopasiParameter::INT:
              p->setValue(*((C_INT32*)mCommon.pCurrentParameter->getValue()));
              break;

            case CCopasiParameter::UINT:
              p->setValue(*((unsigned C_INT32*)mCommon.pCurrentParameter->getValue()));
              break;

            case CCopasiParameter::DOUBLE:
              p->setValue(*((C_FLOAT64*)mCommon.pCurrentParameter->getValue()));
              break;

            case CCopasiParameter::UDOUBLE:
              p->setValue(*((C_FLOAT64*)mCommon.pCurrentParameter->getValue()));
              break;

            case CCopasiParameter::BOOL:
              p->setValue(*((bool*)mCommon.pCurrentParameter->getValue()));
              break;

            case CCopasiParameter::STRING:
              p->setValue(*((std::string*)mCommon.pCurrentParameter->getValue()));
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
          CCopasiMessage Message(CCopasiMessage::RAW, MCXML + 4,
                                 mCommon.pCurrentParameter->getObjectName().c_str(),
                                 mLineNumber);
        }
      pdelete(mCommon.pCurrentParameter);
      mCurrentElement = Method;
      break;

    case ParameterGroup:
      if (strcmp(pszName, "ParameterGroup")) fatalError();
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
            case CCopasiParameter::INVALID:
              break;

            default:
              fatalError();
              break;
            }
        }
      else
        {
          CCopasiMessage Message(CCopasiMessage::RAW, MCXML + 4,
                                 mCommon.pCurrentParameter->getObjectName().c_str(),
                                 mLineNumber);
        }
      pdelete(mCommon.pCurrentParameter);
      mCurrentElement = Method;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "ListOfReports")) fatalError();
      if (!mCommon.pReportList)
        mCommon.pReportList = new CReportDefinitionVector;
      break;

    case Report:
      if (strcmp(pszName, "Report")) fatalError();

      /* If we do not have a report element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new ReportElement(mParser, mCommon);

      /* Push the report element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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

  std::map<std::string , std::vector < std::pair < std::vector <CRegisteredObjectName >*, unsigned int > > >::iterator outerIt;

  std::vector<std::pair < std::vector <CRegisteredObjectName >*, unsigned int > >::iterator innerIt2;

  std::vector<CRegisteredObjectName>* nameVector;

  unsigned int reportIndex;

  switch (mCurrentElement)
    {
    case ListOfReports:
      if (strcmp(pszName, "ListOfReports")) fatalError();
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
      break;

    default:
      fatalError();
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
  CCopasiTask::Type type;

  mCurrentElement++; /* We should always be on the next element */
  mpCurrentHandler = NULL;

  switch (mCurrentElement)
    {
    case Report:
      if (strcmp(pszName, "Report")) fatalError();

      // We have not found anything yet.
      tableFound = false;
      otherFound = false;

      Key = mParser.getAttributeValue("key", papszAttrs);
      Name = mParser.getAttributeValue("name", papszAttrs);
      type = (CCopasiTask::Type)mParser.toEnum(mParser.getAttributeValue("taskType", papszAttrs),
             CCopasiTask::XMLType);
      Separator = mParser.getAttributeValue("separator", papszAttrs, "\t");

      // create a new report
      mCommon.pReport = new CReportDefinition();
      mCommon.pReport->setObjectName(Name);
      mCommon.pReport->setTaskType(type);
      mCommon.pReport->setSeparator(CCopasiReportSeparator(Separator));

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
      (mCurrentElement == Header || mCurrentElement == Body))
    mCurrentElement = Report;

  switch (mCurrentElement)
    {
    case Report:
      if (strcmp(pszName, "Report")) fatalError();
      mCurrentElement = START_ELEMENT;
      mParser.popElementHandler();

      // Tell the parent element we are done.
      mParser.onEndElement(pszName);
      break;

    case Comment:
      if (strcmp(pszName, "Comment")) fatalError();
      // check parameter type CCopasiStaticString
      mCommon.pReport->setComment(mCommon.Comment);
      mCommon.Comment = "";
      break;

    case Header:
      if (strcmp(pszName, "Header")) fatalError();
      break;

    case Body:
      if (strcmp(pszName, "Body")) fatalError();
      break;

    case Footer:
      if (strcmp(pszName, "Footer")) fatalError();
      mCurrentElement = Report;
      break;

    case Table:
      if (strcmp(pszName, "Table")) fatalError();
      mCurrentElement = Report;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
      break;
    }
}

CCopasiXMLParser::HeaderElement::HeaderElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::HeaderElement::~HeaderElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::HeaderElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */
  mpCurrentHandler = NULL;

  switch (mCurrentElement)
    {
    case Header:
      if (strcmp(pszName, "Header")) fatalError();
      return;
      break;

    case Text:
      if (!strcmp(pszName, "html"))
        {
          /* If we do not have a text element handler we create one. */
          if (!mpCurrentHandler)
            mpCurrentHandler = new TextElement(mParser, mCommon);
        }
      break;

    case Object:
      if (!strcmp(pszName, "Object"))
        {
          /* If we do not have an Object element handler we create one. */
          if (!mpCurrentHandler)
            mpCurrentHandler = new ObjectElement(mParser, mCommon);
        }
      break;

    case Report:
      if (!strcmp(pszName, "Report"))
        {
          /* If we do not have an Object element handler we create one. */
          if (!mpCurrentHandler)
            mpCurrentHandler = new TextElement(mParser, mCommon);
        }
      /* Push the Text element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
      break;
    }
  /* Push the Text element handler on the stack and call it. */
  if (mpCurrentHandler)
    {
      mParser.pushElementHandler(mpCurrentHandler);
    }
  mpCurrentHandler->start(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::HeaderElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
    case Header:
      if (strcmp(pszName, "Header")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Text:
      if (strcmp(pszName, "html")) fatalError();
      mCommon.pReport->getHeaderAddr()->push_back(CCopasiStaticString(mCommon.Comment).getCN());
      mCurrentElement = Header;
      break;

    case Object:
      if (strcmp(pszName, "Object")) fatalError();
      mCommon.pReport->getHeaderAddr()->push_back(CCopasiObjectName(mCommon.Comment));
      mCurrentElement = Header;
      break;

    case Report:
      if (strcmp(pszName, "Report")) fatalError();
      // add the key that is stored in mCommon.Comment to the map
      if (mCommon.reportReferenceMap.find(mCommon.Comment) == mCommon.reportReferenceMap.end())
        {
          mCommon.reportReferenceMap[mCommon.Comment] = std::vector<std::pair <std::vector<CRegisteredObjectName>*, unsigned int> >();
        }
      mCommon.reportReferenceMap[mCommon.Comment].push_back(std::make_pair(mCommon.pReport->getHeaderAddr(), mCommon.pReport->getHeaderAddr()->size()));
      mCommon.pReport->getHeaderAddr()->push_back(CCopasiObjectName(""));
      mCurrentElement = Header;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
      break;
    }
}

CCopasiXMLParser::BodyElement::BodyElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::BodyElement::~BodyElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::BodyElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */
  mpCurrentHandler = NULL;

  switch (mCurrentElement)
    {
    case Body:
      if (strcmp(pszName, "Body")) fatalError();
      return;
      break;

    case Text:
      if (!strcmp(pszName, "html"))
        {
          /* If we do not have a text element handler we create one. */
          if (!mpCurrentHandler)
            mpCurrentHandler = new TextElement(mParser, mCommon);
        }
      break;

    case Object:
      if (!strcmp(pszName, "Object"))
        {
          /* If we do not have an Object element handler we create one. */
          if (!mpCurrentHandler)
            mpCurrentHandler = new ObjectElement(mParser, mCommon);
        }
      break;

    case Report:
      if (!strcmp(pszName, "Report"))
        {
          /* If we do not have an Object element handler we create one. */
          if (!mpCurrentHandler)
            mpCurrentHandler = new TextElement(mParser, mCommon);
        }
      /* Push the Text element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
      break;
    }
  /* Push the Text element handler on the stack and call it. */
  if (mpCurrentHandler)
    {
      mParser.pushElementHandler(mpCurrentHandler);
    }
  mpCurrentHandler->start(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::BodyElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
    case Body:
      if (strcmp(pszName, "Body")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Text:
      if (strcmp(pszName, "html")) fatalError();
      mCommon.pReport->getBodyAddr()->push_back(CCopasiStaticString(mCommon.Comment).getCN());
      mCurrentElement = Body;
      break;

    case Object:
      if (strcmp(pszName, "Object")) fatalError();
      mCommon.pReport->getBodyAddr()->push_back(CCopasiObjectName(mCommon.Comment));
      mCurrentElement = Body;
      break;

    case Report:
      if (strcmp(pszName, "Report")) fatalError();
      // add the key that is stored in mCommon.Comment to the map
      if (mCommon.reportReferenceMap.find(mCommon.Comment) == mCommon.reportReferenceMap.end())
        {
          mCommon.reportReferenceMap[mCommon.Comment] = std::vector<std::pair <std::vector<CRegisteredObjectName>*, unsigned int> >();
        }
      mCommon.reportReferenceMap[mCommon.Comment].push_back(std::make_pair(mCommon.pReport->getBodyAddr(), mCommon.pReport->getBodyAddr()->size()));
      mCommon.pReport->getBodyAddr()->push_back(CCopasiObjectName(""));
      mCurrentElement = Body;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
      break;
    }
}

CCopasiXMLParser::FooterElement::FooterElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::FooterElement::~FooterElement()
{
  pdelete(mpCurrentHandler);
}

void CCopasiXMLParser::FooterElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */
  mpCurrentHandler = NULL;

  switch (mCurrentElement)
    {
    case Footer:
      if (strcmp(pszName, "Footer")) fatalError();
      return;
      break;

    case Text:
      if (!strcmp(pszName, "html"))
        {
          /* If we do not have a text element handler we create one. */
          if (!mpCurrentHandler)
            mpCurrentHandler = new TextElement(mParser, mCommon);
        }
      break;

    case Object:
      if (!strcmp(pszName, "Object"))
        {
          /* If we do not have an Object element handler we create one. */
          if (!mpCurrentHandler)
            mpCurrentHandler = new ObjectElement(mParser, mCommon);
        }
      break;

    case Report:
      if (!strcmp(pszName, "Report"))
        {
          /* If we do not have an Object element handler we create one. */
          if (!mpCurrentHandler)
            mpCurrentHandler = new TextElement(mParser, mCommon);
        }
      /* Push the Text element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
      break;
    }
  /* Push the Text element handler on the stack and call it. */
  if (mpCurrentHandler)
    {
      mParser.pushElementHandler(mpCurrentHandler);
    }
  mpCurrentHandler->start(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::FooterElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
    case Footer:
      if (strcmp(pszName, "Footer")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Text:
      if (strcmp(pszName, "html")) fatalError();
      mCommon.pReport->getFooterAddr()->push_back(CCopasiStaticString(mCommon.Comment).getCN());
      mCurrentElement = Footer;
      break;

    case Object:
      if (strcmp(pszName, "Object")) fatalError();
      mCommon.pReport->getFooterAddr()->push_back(CCopasiObjectName(mCommon.Comment));
      mCurrentElement = Footer;
      break;

    case Report:
      if (strcmp(pszName, "Report")) fatalError();
      // add the key that is stored in mCommon.Comment to the map
      if (mCommon.reportReferenceMap.find(mCommon.Comment) == mCommon.reportReferenceMap.end())
        {
          mCommon.reportReferenceMap[mCommon.Comment] = std::vector<std::pair <std::vector<CRegisteredObjectName>*, unsigned int> >();
        }
      mCommon.reportReferenceMap[mCommon.Comment].push_back(std::make_pair(mCommon.pReport->getFooterAddr(), mCommon.pReport->getFooterAddr()->size()));
      mCommon.pReport->getFooterAddr()->push_back(CCopasiObjectName(""));
      mCurrentElement = Footer;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "Table")) fatalError();
      printTitle = mParser.getAttributeValue("printTitle", papszAttrs, "false");
      mCommon.pReport->setTitle(mParser.toBool(printTitle));
      break;

    case Object:
      if (strcmp(pszName, "Object")) fatalError();
      if (!mpCurrentHandler)
        {
          mpCurrentHandler = new ObjectElement(mParser, mCommon);
        }
      mParser.pushElementHandler(mpCurrentHandler);
      mParser.onStartElement(pszName, papszAttrs);
      break;

    default:
      mParser.pushElementHandler(&mParser.mUnknownElement);
      mParser.onStartElement(pszName, papszAttrs);
      break;
    }
  return;
}

void CCopasiXMLParser::TableElement::end(const XML_Char *pszName)
{
  const CCopasiObject * pObject = NULL;
  switch (mCurrentElement)
    {
    case Table:
      if (strcmp(pszName, "Table")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Object:
      if (strcmp(pszName, "Object")) fatalError();
      mCommon.pReport->getTableAddr()->push_back(mCommon.Comment);
      mCommon.Comment = "";
      mCurrentElement = Table;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "Object")) fatalError();

      cn = mParser.getAttributeValue("cn", papszAttrs);
      mCommon.Comment = cn;
      break;

    default:
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
      if (strcmp(pszName, "Object")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      // Tell the parent element we are done.
      mParser.onEndElement(pszName);
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "GUI")) fatalError();
      return;
      break;

    case ListOfSliders:
      if (!strcmp(pszName, "ListOfSliders"))
        mpCurrentHandler = new ListOfSlidersElement(mParser, mCommon);
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
      if (strcmp(pszName, "ListOfSliders")) fatalError();
      if (!mCommon.pGUI->pSliderList)
        mCommon.pGUI->pSliderList = new CCopasiVector< CSlider >;
      break;

    case Slider:
      if (strcmp(pszName, "Slider")) fatalError();

      /* If we do not have a Slider element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new SliderElement(mParser, mCommon);

      /* Push the Slider element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
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
      if (strcmp(pszName, "ListOfSliders")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Slider:
      if (strcmp(pszName, "Slider")) fatalError();
      mCurrentElement = ListOfSliders;
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
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
      if (strcmp(pszName, "Slider")) fatalError();
      Key = mParser.getAttributeValue("key", papszAttrs);
      AssociatedEntityKey = mParser.getAttributeValue("associatedEntityKey", papszAttrs);
      ObjectCN = mParser.getAttributeValue("objectCN", papszAttrs);
      objectType = mParser.getAttributeValue("objectType", papszAttrs);
      ObjectType = (CSlider::Type) mParser.toEnum(objectType, CSlider::TypeName);
      tmp = mParser.getAttributeValue("objectValue", papszAttrs);
      ObjectValue = atof(tmp);
      tmp = mParser.getAttributeValue("minValue", papszAttrs);
      MinValue = atof(tmp);
      tmp = mParser.getAttributeValue("maxValue", papszAttrs);
      MaxValue = atof(tmp);
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
      if (strcmp(pszName, "Slider")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = START_ELEMENT;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case UNKNOWN_ELEMENT:
      break;

    default:
      fatalError();
      break;
    }

  return;
}
