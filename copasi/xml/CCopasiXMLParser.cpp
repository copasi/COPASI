/**
 * CCopasiXMLParser class.
 * This class parses a Copasi XML file.
 *
 * Created for Copasi by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */

#include "CExpat.h"

#include "copasi.h"

#include "CCopasiXMLParser.h"
#include "CCopasiXMLInterface.h"
#include "utilities/CCopasiMessage.h"
#include "function/CFunction.h"

CCopasiXMLParser::ModelElement::ModelElement(SCopasiXMLParserCommon & common) :
    CXMLElementHandler< SCopasiXMLParserCommon >(common)
{}

CCopasiXMLParser::ModelElement::~ModelElement() {}

void CCopasiXMLParser::ModelElement::start(const XML_Char * C_UNUSED(pszName),
    const XML_Char ** C_UNUSED(papszAttrs))
{}

void CCopasiXMLParser::ModelElement::end(const XML_Char * C_UNUSED(pszName)) {}

CCopasiXMLParser::ListOfTasksElement::ListOfTasksElement(SCopasiXMLParserCommon & common) :
    CXMLElementHandler< SCopasiXMLParserCommon >(common)
{}

CCopasiXMLParser::ListOfTasksElement::~ListOfTasksElement() {}

void CCopasiXMLParser::ListOfTasksElement::start(const XML_Char * C_UNUSED(pszName),
    const XML_Char ** C_UNUSED(papszAttrs))
{}

void CCopasiXMLParser::ListOfTasksElement::end(const XML_Char * C_UNUSED(pszName)) {}

CCopasiXMLParser::ListOfReportsElement::ListOfReportsElement(SCopasiXMLParserCommon & common) :
    CXMLElementHandler< SCopasiXMLParserCommon >(common)
{}

CCopasiXMLParser::ListOfReportsElement::~ListOfReportsElement() {}

void CCopasiXMLParser::ListOfReportsElement::start(const XML_Char * C_UNUSED(pszName),
    const XML_Char ** C_UNUSED(papszAttrs))
{}

void CCopasiXMLParser::ListOfReportsElement::end(const XML_Char * C_UNUSED(pszName)) {}

CCopasiXMLParser::COPASIElement::COPASIElement(SCopasiXMLParserCommon & common) :
    CXMLElementHandler< SCopasiXMLParserCommon >(common)
{}

CCopasiXMLParser::COPASIElement::~COPASIElement() {}

void CCopasiXMLParser::COPASIElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case COPASI:
      if (strcmp(pszName, "COPASI")) fatalError();
      return;

    case ListOfFunctions:
      if (strcmp(pszName, "ListOfFunctions")) fatalError();
      mpCurrentHandler = new ListOfFunctionsElement(mCommon);
      break;

    case Model:
      if (strcmp(pszName, "Model")) fatalError();
      mpCurrentHandler = new ModelElement(mCommon);
      break;

    case ListOfTasks:
      if (strcmp(pszName, "ListOfTasks")) fatalError();
      mpCurrentHandler = new ListOfTasksElement(mCommon);
      break;

    case ListOfReports:
      if (strcmp(pszName, "ListOfReports")) fatalError();
      mpCurrentHandler = new ListOfReportsElement(mCommon);
      break;

    default:
      fatalError();
      break;
    }

  mCommon.ElementHandlerStack.push(mpCurrentHandler);
  mpCurrentHandler->start(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::COPASIElement::end(const XML_Char * pszName)
{
  if (!strcmp(pszName, "COPASI"))
    {
      mCommon.ElementHandlerStack.pop();
      mCurrentElement = -1;
    }

  return;
}

CCopasiXMLParser::ListOfFunctionsElement::ListOfFunctionsElement(SCopasiXMLParserCommon & common) :
    CXMLElementHandler< SCopasiXMLParserCommon >(common)
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
        mpCurrentHandler = new FunctionElement(mCommon);

      /* Push the Function element handler on the stack and call it. */
      mCommon.ElementHandlerStack.push(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
      fatalError();
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
      mCommon.ElementHandlerStack.pop();
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mCommon.ElementHandlerStack.top()->end(pszName);
      break;

    case Function:
      if (strcmp(pszName, "Function")) fatalError();
      mCurrentElement = ListOfFunctions;
      break;

    default:
      fatalError();
      break;
    }

  return;
}

CCopasiXMLParser::FunctionElement::FunctionElement(SCopasiXMLParserCommon & common) :
    CXMLElementHandler< SCopasiXMLParserCommon >(common),
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
  unsigned C_INT32 i = 1; /* Function of Type Base are never instantiated */
  const char * Key;
  const char * Type;
  const char * Name;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case Function:
      if (strcmp(pszName, "Function")) fatalError();

      Key = CCopasiXMLInterface::getAttributeValue("key", papszAttrs);
      Name = CCopasiXMLInterface::getAttributeValue("name", papszAttrs);
      Type = CCopasiXMLInterface::getAttributeValue("type", papszAttrs);

      while (CFunction::XMLType[i] != "" &&
             CFunction::XMLType[i] != Type) i++;
      if (CFunction::XMLType[i] == "") fatalError();

      mCommon.pFunction = CFunction::createFunction((enum CFunction::Type) i);
      mCommon.pFunction->setName(Name);

      /* We have a new function and add it to the list */
      mCommon.pFunctionList->add(mCommon.pFunction, true);
      mCommon.KeyMap[Key] = mCommon.pFunction->getKey();

      break;

    case MathML:
      if (strcmp(pszName, "MathML")) fatalError();

      /* If we do not have a MathML element handler we create one. */
      if (!mpMathMLElement)
        mpMathMLElement = new MathMLElement(mCommon);

      /* Push the MathML element handler on the stack and call it. */
      mpCurrentHandler = mpMathMLElement;
      mCommon.ElementHandlerStack.push(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    case ListOfParameterDescriptions:
      if (strcmp(pszName, "ListOfParameterDescriptions")) fatalError();

      /* If we do not have a ListOfParameterDescriptions element handler we create one. */
      if (!mpListOfParameterDescriptionsElement)
        mpListOfParameterDescriptionsElement = new ListOfParameterDescriptionsElement(mCommon);

      /* Push the ListOfParameterDescriptions element handler on the stack and call it. */
      mpCurrentHandler = mpListOfParameterDescriptionsElement;
      mCommon.ElementHandlerStack.push(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
      fatalError();
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
      mCurrentElement = -1;
      mCommon.ElementHandlerStack.pop();

      /* Tell the parent element we are done. */
      mCommon.ElementHandlerStack.top()->end(pszName);
      break;

    case MathML:
      if (strcmp(pszName, "MathML")) fatalError();
      break;

    case ListOfParameterDescriptions:
      if (strcmp(pszName, "ListOfParameterDescriptions")) fatalError();
      mCurrentElement = Function;
      break;

    default:
      fatalError();
      break;
    }
}

CCopasiXMLParser::MathMLElement::MathMLElement(SCopasiXMLParserCommon & common) :
    CXMLElementHandler< SCopasiXMLParserCommon >(common)
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
        mpCurrentHandler = new TextElement(mCommon);

      /* Push the Function element handler on the stack and call it. */
      mCommon.ElementHandlerStack.push(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
      fatalError();
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
      mCommon.ElementHandlerStack.pop();
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mCommon.ElementHandlerStack.top()->end(pszName);
      break;

    case Text:
      if (strcmp(pszName, "Text")) fatalError();
      mCurrentElement = MathML;

      break;

    default:
      fatalError();
      break;
    }
}

CCopasiXMLParser::TextElement::TextElement(SCopasiXMLParserCommon & common) :
    CXMLElementHandler< SCopasiXMLParserCommon >(common)
{}

CCopasiXMLParser::TextElement::~TextElement()
{}

void CCopasiXMLParser::TextElement::start(const XML_Char *pszName,
    const XML_Char ** C_UNUSED(papszAttrs))
{
  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case Text:
      if (strcmp(pszName, "Text")) fatalError();

      mCommon.pParser->enableCharacterDataHandler(true);
      //    mCommon.pParser->enableCdataSectionHandler(true);
      break;

    default:
      fatalError();
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
      mCommon.ElementHandlerStack.pop();
      mCurrentElement = -1;
      mCommon.pFunction->setDescription(mCommon.pParser->getCharacterData("\n\t ", ""));

      mCommon.pParser->enableCharacterDataHandler(false);
      //    mCommon.pParser->enableCdataSectionHandler(false);

      /* Tell the parent element we are done. */
      mCommon.ElementHandlerStack.top()->end(pszName);
      break;

    default:
      fatalError();
      break;
    }
}

CCopasiXMLParser::ListOfParameterDescriptionsElement::ListOfParameterDescriptionsElement(SCopasiXMLParserCommon & common) :
    CXMLElementHandler< SCopasiXMLParserCommon >(common)
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
        mpCurrentHandler = new ParameterDescriptionElement(mCommon);

      /* Push the ParameterDescription element handler on the stack and call it. */
      mCommon.ElementHandlerStack.push(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
      fatalError();
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

      pUsageRanges = & mCommon.pFunction->getParameters().getUsageRanges();
      UsageDescription.setUsage("SUBSTRATES");
      if ((index = pUsageRanges->getIndex("SUBSTRATE")) != C_INVALID_INDEX)
        {
          UsageDescription.setRange((*pUsageRanges)[index]->getLow(),
                                    (*pUsageRanges)[index]->getHigh());
          mCommon.pFunction->getUsageDescriptions().add(UsageDescription);
        }

      UsageDescription.setUsage("PRODUCTS");
      if ((index = pUsageRanges->getIndex("PRODUCT")) != C_INVALID_INDEX)
        {
          UsageDescription.setRange((*pUsageRanges)[index]->getLow(),
                                    (*pUsageRanges)[index]->getHigh());
          mCommon.pFunction->getUsageDescriptions().add(UsageDescription);
        }

      mCommon.ElementHandlerStack.pop();
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mCommon.ElementHandlerStack.top()->end(pszName);
      break;

    case ParameterDescription:
      if (strcmp(pszName, "ParameterDescription")) fatalError();
      mCurrentElement = ListOfParameterDescriptions;
      break;

    default:
      fatalError();
      break;
    }

  return;
}

CCopasiXMLParser::ParameterDescriptionElement::ParameterDescriptionElement(SCopasiXMLParserCommon & common) :
    CXMLElementHandler< SCopasiXMLParserCommon >(common),
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
  unsigned C_INT32 Role = 0;
  const char * minOccurs;
  unsigned C_INT32 MinOccurs;
  const char * maxOccurs;
  unsigned C_INT32 MaxOccurs;

  std::string Usage[] = {"SUBSTRATE", "PRODUCT", "MODIFIER", "PARAMETER"};
  CFunctionParameter * pParm = NULL;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case ParameterDescription:
      if (strcmp(pszName, "ParameterDescription")) fatalError();
      Key = CCopasiXMLInterface::getAttributeValue("key", papszAttrs);
      Name = CCopasiXMLInterface::getAttributeValue("name", papszAttrs);
      Order = CCopasiXMLInterface::getAttributeValue("order", papszAttrs);
      if (atoi(Order) != mOrder) fatalError();
      mOrder++;
      role = CCopasiXMLInterface::getAttributeValue("role", papszAttrs);
      while (CFunctionParameter::XMLRole[Role] != "" &&
             CFunctionParameter::XMLRole[Role] != role) Role++;
      if (CFunctionParameter::XMLRole[Role] == "") fatalError();

      minOccurs = CCopasiXMLInterface::getAttributeValue("minOccurs",
                  papszAttrs);
      if (minOccurs) MinOccurs = atoi(minOccurs);
      else MinOccurs = 1;

      maxOccurs = CCopasiXMLInterface::getAttributeValue("maxOccurs",
                  papszAttrs);
      if (!maxOccurs) MaxOccurs = 1;
      else if ("unbounded" == maxOccurs) MaxOccurs = (unsigned C_INT32) - 1;
      else MaxOccurs = atoi(maxOccurs);

      pParm = new CFunctionParameter();
      pParm->setName(Name);
      mCommon.KeyMap[Key] = pParm->getKey();
      pParm->setUsage(Usage[Role]);
      if (MaxOccurs == 1 && MinOccurs == 1)
        pParm->setType(CFunctionParameter::FLOAT64);
      else
        pParm->setType(CFunctionParameter::VFLOAT64);
      mCommon.pFunction->getParameters().add(pParm, true);
      break;

    default:
      fatalError();
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
      mCommon.ElementHandlerStack.pop();
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mCommon.ElementHandlerStack.top()->end(pszName);
      break;

    default:
      fatalError();
      break;
    }

  return;
}

void CCopasiXMLParser::ParameterDescriptionElement::reset()
{mOrder = 0;}

CCopasiXMLParser::CCopasiXMLParser() :
    CExpat(),
    mCommon()
{
  create();

  mCommon.ElementHandlerStack.push(new COPASIElement(mCommon));
  mCommon.pParser = this;
  mCommon.pModel = NULL;
  mCommon.pFunctionList = NULL;
  mCommon.pFunction = NULL;

  enableElementHandler(true);
}

CCopasiXMLParser::~CCopasiXMLParser() {}

void CCopasiXMLParser::onStartElement(const XML_Char *pszName,
                                      const XML_Char **papszAttrs)
{
  assert(mCommon.ElementHandlerStack.size() != 0);
  mCommon.ElementHandlerStack.top()->start(pszName, papszAttrs);
}

void CCopasiXMLParser::onEndElement(const XML_Char *pszName)
{
  assert(mCommon.ElementHandlerStack.size() != 0);
  mCommon.ElementHandlerStack.top()->end(pszName);
}

#ifdef XXXX
void CCopasiXMLParser::onStartCdataSection()
{
  long i = mCommon.pParser->getCurrentByteIndex();
}

void CCopasiXMLParser::onEndCdataSection()
{
  long i = mCommon.pParser->getCurrentByteIndex();
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

CCopasiVectorN< CFunction > * CCopasiXMLParser::getFunctionList() const
  {return mCommon.pFunctionList;}

CModel * CCopasiXMLParser::getModel() const
  {return mCommon.pModel;}
