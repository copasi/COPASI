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
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "utilities/CMethodParameter.h"

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
      fatalError();
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
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case etc:
      if (strcmp(pszName, "etc")) fatalError();
      mCurrentElement = TEMPLATE;
      break;

    default:
      fatalError();
      break;
    }

  return;
}

#endif // COPASI_TEMPLATE

CCopasiXMLParser::CCopasiXMLParser() :
    CExpat(),
    mCommon(),
    mElementHandlerStack()
{
  create();

  mElementHandlerStack.push(new COPASIElement(*this, mCommon));
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

void CCopasiXMLParser::pushElementHandler(CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon > * elementHandler)
{mElementHandlerStack.push(elementHandler);}

void CCopasiXMLParser::popElementHandler()
{mElementHandlerStack.pop();}

CCopasiVectorN< CFunction > * CCopasiXMLParser::getFunctionList() const
  {return mCommon.pFunctionList;}

CModel * CCopasiXMLParser::getModel() const
  {return mCommon.pModel;}

CCopasiXMLParser::COPASIElement::COPASIElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
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
      mpCurrentHandler = new ListOfFunctionsElement(mParser, mCommon);
      break;

    case Model:
      if (strcmp(pszName, "Model")) fatalError();
      mpCurrentHandler = new ModelElement(mParser, mCommon);
      break;

    case ListOfTasks:
      if (strcmp(pszName, "ListOfTasks")) fatalError();
      mpCurrentHandler = new ListOfTasksElement(mParser, mCommon);
      break;

    case ListOfReports:
      if (strcmp(pszName, "ListOfReports")) fatalError();
      mpCurrentHandler = new ListOfReportsElement(mParser, mCommon);
      break;

    default:
      fatalError();
      break;
    }

  mParser.pushElementHandler(mpCurrentHandler);
  mpCurrentHandler->start(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::COPASIElement::end(const XML_Char * pszName)
{
  if (!strcmp(pszName, "COPASI"))
    {
      mParser.popElementHandler();
      mCurrentElement = -1;
    }

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
      mParser.popElementHandler();
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
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

      mCommon.pFunction = CFunction::createFunction(Type);
      mCommon.pFunction->setName(Name);
      if (mParser.toBool(Positive))
        mCommon.pFunction->setReversible(TriTrue);
      else
        mCommon.pFunction->setReversible(TriFalse);

      /* We have a new function and add it to the list */
      mCommon.pFunctionList->add(mCommon.pFunction, true);
      mCommon.KeyMap[Key] = mCommon.pFunction->getKey();

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
      mCommon.pFunction->setDescription(mCommon.FunctionDescription);
      mCurrentElement = -1;
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
      mParser.popElementHandler();
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
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

CCopasiXMLParser::TextElement::TextElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
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
      mParser.popElementHandler();
      mCurrentElement = -1;
      mCommon.FunctionDescription = mCommon.pParser->getCharacterData("\n\t ", "");

      mCommon.pParser->enableCharacterDataHandler(false);
      //    mCommon.pParser->enableCdataSectionHandler(false);

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
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

      mParser.popElementHandler();
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
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
  CFunctionParameter::Role Role;
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
      Key = mParser.getAttributeValue("key", papszAttrs);
      Name = mParser.getAttributeValue("name", papszAttrs);

      Order = mParser.getAttributeValue("order", papszAttrs);
      if (atoi(Order) != mOrder) fatalError();
      mOrder++;

      role = mParser.getAttributeValue("role", papszAttrs);
      Role = (CFunctionParameter::Role) mParser.toEnum(role, CFunctionParameter::RoleName);
      if (Role == -1) fatalError();

      minOccurs = mParser.getAttributeValue("minOccurs", papszAttrs, "1");
      MinOccurs = atoi(minOccurs);

      maxOccurs = mParser.getAttributeValue("maxOccurs", papszAttrs , "1");
      if ("unbounded" == maxOccurs) MaxOccurs = (unsigned C_INT32) - 1;
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
      mParser.popElementHandler();
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
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
        (CModel::VolumeUnit) mParser.toEnum(timeUnit, CModel::VolumeUnitName);
      if (VolumeUnit == -1) fatalError();

      quantityUnit = mParser.getAttributeValue("quantityUnit", papszAttrs);
      QuantityUnit =
        (CModel::QuantityUnit) mParser.toEnum(timeUnit, CModel::QuantityUnitName);
      if (QuantityUnit == -1) fatalError();

      StateVariable = mParser.getAttributeValue("stateVariable", papszAttrs);

      if (!mCommon.pModel) mCommon.pModel = new CModel();
      mCommon.KeyMap[Key] = mCommon.pModel->getKey();
      mCommon.pModel->setTitle(Name);
      mCommon.pModel->setTimeUnit(TimeUnit);
      mCommon.pModel->setVolumeUnit(VolumeUnit);
      mCommon.pModel->setQuantityUnit(QuantityUnit);

      break;

    case Comment:
      if (strcmp(pszName, "Comment")) fatalError();

      /* If we do not have a function element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new CommentElement(mParser, mCommon);

      /* Push the Comment element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    case ListOfCompartments:
      if (strcmp(pszName, "ListOfCompartments")) fatalError();

      /* If we do not have a function element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new ListOfCompartmentsElement(mParser, mCommon);

      /* Push the ListOfCompartments element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    case ListOfMetabolites:
      if (strcmp(pszName, "ListOfMetabolites")) fatalError();

      /* If we do not have a function element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new ListOfMetabolitesElement(mParser, mCommon);

      /* Push the ListOfMetabolites element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    case ListOfReactions:
      if (strcmp(pszName, "ListOfReactions")) fatalError();

      /* If we do not have a function element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new ListOfReactionsElement(mParser, mCommon);

      /* Push the ListOfReactions element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

#ifdef XXXX
    case StateTemplate:
      if (strcmp(pszName, "StateTemplate")) fatalError();

      /* If we do not have a function element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new StateTemplateElement(mParser, mCommon);

      /* Push the StateTemplate element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    case InitialState:
      if (strcmp(pszName, "InitialState")) fatalError();

      /* If we do not have a function element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new InitialStateElement(mParser, mCommon);

      /* Push the InitialState element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;
#endif // XXXX
    default:
      fatalError();
      break;
    }

  return;
}

void CCopasiXMLParser::ModelElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
    case Model:
      if (strcmp(pszName, "Model")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Comment:
      if (strcmp(pszName, "Comment")) fatalError();
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
    const XML_Char ** C_UNUSED(papszAttrs))
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
      fatalError();
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
      mCommon.pModel->setComments(mParser.getCharacterData());
      mParser.popElementHandler();
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Ignore:
      mCurrentElement = Comment;
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
      fatalError();
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
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Compartment:
      if (strcmp(pszName, "Compartment")) fatalError();
      mCurrentElement = ListOfCompartments;
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
      mCommon.KeyMap[Key] = pCompartment->getKey();
      pCompartment->setName(Name);

      mCommon.pModel->getCompartments().add(pCompartment, true);
      break;

    default:
      fatalError();
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
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
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
      fatalError();
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
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Metabolite:
      if (strcmp(pszName, "Metabolite")) fatalError();
      mCurrentElement = ListOfMetabolites;
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
  const char * StateVariable;
  std::map< std::string, std::string >::const_iterator CompartmentKey;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case Metabolite:
      if (strcmp(pszName, "Metabolite")) fatalError();

      Key = mParser.getAttributeValue("key", papszAttrs);
      Name = mParser.getAttributeValue("name", papszAttrs);
      Compartment = mParser.getAttributeValue("compartment", papszAttrs);
      StateVariable = mParser.getAttributeValue("stateVariable", papszAttrs);

      pMetabolite = new CMetab();
      mCommon.KeyMap[Key] = pMetabolite->getKey();
      pMetabolite->setName(Name);

      CompartmentKey = mCommon.KeyMap.find(Compartment);
      if (CompartmentKey == mCommon.KeyMap.end()) fatalError();
      pCompartment =
        (CCompartment*)(CCopasiContainer*)CKeyFactory::get(CompartmentKey->second);
      pCompartment->add(pMetabolite);

      break;

    default:
      fatalError();
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
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    default:
      fatalError();
      break;
    }

  return;
}

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
      fatalError();
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
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Reaction:
      if (strcmp(pszName, "Reaction")) fatalError();
      mCurrentElement = ListOfReactions;
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
  std::map< std::string, std::string >::const_iterator CompartmentKey;

  mCurrentElement++; /* We should always be on the next element */

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
      mCommon.KeyMap[Key] = mCommon.pReaction->getKey();
      mCommon.pReaction->setName(Name);
      mCommon.pReaction->setReversible(Reversible);

      if (strcmp(Compartment, "Compartment_00"))
        {
          CompartmentKey = mCommon.KeyMap.find(Compartment);
          if (CompartmentKey == mCommon.KeyMap.end()) fatalError();
          pCompartment =
            (CCompartment*)(CCopasiContainer*)CKeyFactory::get(CompartmentKey->second);
          mCommon.pReaction->setCompartment(pCompartment);
        }

      break;

    case ListOfSubstrates:
      if (strcmp(pszName, "ListOfSubstrates")) fatalError();

      /* If we do not have a function element handler we create one. */
      if (!mpListOfSubstratesElement)
        mpListOfSubstratesElement = new ListOfSubstratesElement(mParser, mCommon);

      /* Push the ListOfSubstrates element handler on the stack and call it. */
      mpCurrentHandler = mpListOfSubstratesElement;
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    case ListOfProducts:
      if (strcmp(pszName, "ListOfProducts")) fatalError();

      /* If we do not have a ListOfProducts element handler we create one. */
      if (!mpListOfProductsElement)
        mpListOfProductsElement = new ListOfProductsElement(mParser, mCommon);

      /* Push the ListOfProducts element handler on the stack and call it. */
      mpCurrentHandler = mpListOfProductsElement;
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    case ListOfModifiers:
      if (strcmp(pszName, "ListOfModifiers")) fatalError();

      /* If we do not have a ListOfModifiers element handler we create one. */
      if (!mpListOfModifiersElement)
        mpListOfModifiersElement = new ListOfModifiersElement(mParser, mCommon);

      /* Push the ListOfModifiers element handler on the stack and call it. */
      mpCurrentHandler = mpListOfModifiersElement;
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    case ListOfConstants:
      if (strcmp(pszName, "ListOfConstants")) fatalError();

      /* If we do not have a ListOfConstants element handler we create one. */
      if (!mpListOfConstantsElement)
        mpListOfConstantsElement = new ListOfConstantsElement(mParser, mCommon);

      /* Push the ListOfConstants element handler on the stack and call it. */
      mpCurrentHandler = mpListOfConstantsElement;
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    case KineticLaw:
      if (strcmp(pszName, "KineticLaw")) fatalError();

      /* If we do not have a KineticLaw element handler we create one. */
      if (!mpKineticLawElement)
        mpKineticLawElement = new KineticLawElement(mParser, mCommon);

      /* Push the KineticLaw element handler on the stack and call it. */
      mpCurrentHandler = mpKineticLawElement;
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;

    default:
      fatalError();
      break;
    }

  return;
}

void CCopasiXMLParser::ReactionElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
    case Reaction:
      if (strcmp(pszName, "Reaction")) fatalError();
      mParser.popElementHandler();
      mCurrentElement = -1;

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
      fatalError();
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
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Substrate:
      if (strcmp(pszName, "Substrate")) fatalError();
      mCurrentElement = ListOfSubstrates;
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
  std::map< std::string, std::string >::const_iterator MetaboliteKey;
  CMetab * pMetabolite;

  const char * Stoichiometry;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case Substrate:
      if (strcmp(pszName, "Substrate")) fatalError();
      Metabolite = mParser.getAttributeValue("metabolite", papszAttrs);
      Stoichiometry = mParser.getAttributeValue("stoichiometry", papszAttrs);

      MetaboliteKey = mCommon.KeyMap.find(Metabolite);
      if (MetaboliteKey == mCommon.KeyMap.end()) fatalError();
      pMetabolite =
        (CMetab*)(CCopasiContainer*)CKeyFactory::get(MetaboliteKey->second);

      mCommon.pReaction->addSubstrate(pMetabolite, atof(Stoichiometry));
      break;

    default:
      fatalError();
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
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
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
      fatalError();
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
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Product:
      if (strcmp(pszName, "Product")) fatalError();
      mCurrentElement = ListOfProducts;
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
  std::map< std::string, std::string >::const_iterator MetaboliteKey;
  CMetab * pMetabolite;

  const char * Stoichiometry;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case Product:
      if (strcmp(pszName, "Product")) fatalError();
      Metabolite = mParser.getAttributeValue("metabolite", papszAttrs);
      Stoichiometry = mParser.getAttributeValue("stoichiometry", papszAttrs);

      MetaboliteKey = mCommon.KeyMap.find(Metabolite);
      if (MetaboliteKey == mCommon.KeyMap.end()) fatalError();
      pMetabolite =
        (CMetab*)(CCopasiContainer*)CKeyFactory::get(MetaboliteKey->second);

      mCommon.pReaction->addProduct(pMetabolite, atof(Stoichiometry));
      break;

    default:
      fatalError();
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
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
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
      fatalError();
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
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Modifier:
      if (strcmp(pszName, "Modifier")) fatalError();
      mCurrentElement = ListOfModifiers;
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
  std::map< std::string, std::string >::const_iterator MetaboliteKey;
  CMetab * pMetabolite;

  const char * Stoichiometry;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case Modifier:
      if (strcmp(pszName, "Modifier")) fatalError();
      Metabolite = mParser.getAttributeValue("metabolite", papszAttrs);
      Stoichiometry = mParser.getAttributeValue("stoichiometry", papszAttrs);

      MetaboliteKey = mCommon.KeyMap.find(Metabolite);
      if (MetaboliteKey == mCommon.KeyMap.end()) fatalError();
      pMetabolite =
        (CMetab*)(CCopasiContainer*)CKeyFactory::get(MetaboliteKey->second);

      mCommon.pReaction->addModifier(pMetabolite, atof(Stoichiometry));
      break;

    default:
      fatalError();
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
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
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
      fatalError();
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
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case Constant:
      if (strcmp(pszName, "Constant")) fatalError();
      mCurrentElement = ListOfConstants;
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

  CParameter * pParameter;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case Constant:
      if (strcmp(pszName, "Constant")) fatalError();

      Key = mParser.getAttributeValue("key", papszAttrs);
      Name = mParser.getAttributeValue("name", papszAttrs);
      Value = mParser.getAttributeValue("value", papszAttrs);

      pParameter = new CParameter();
      mCommon.KeyMap[Key] = pParameter->getKey();
      pParameter->setName(Name);
      pParameter->setValue(atof(Value));

      mCommon.pReaction->getParameters().add(pParameter, true);

      break;

    default:
      fatalError();
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
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
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
  std::map< std::string, std::string >::const_iterator FunctionKey;
  CFunction * pFunction;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case KineticLaw:
      if (strcmp(pszName, "KineticLaw")) fatalError();

      Function = mParser.getAttributeValue("function", papszAttrs);

      FunctionKey = mCommon.KeyMap.find(Function);
      if (FunctionKey == mCommon.KeyMap.end()) fatalError();
      pFunction =
        (CFunction*)(CCopasiContainer*)CKeyFactory::get(FunctionKey->second);

      mCommon.pReaction->setFunction(pFunction);
      break;

#ifdef XXXX
    case ListOfCallParameters:
      if (strcmp(pszName, "ListOfCallParameters")) fatalError();

      /* If we do not have a etc element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new ListOfCallParametersElement(mParser, mCommon);

      /* Push the etc element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;
#endif // XXXX

    default:
      fatalError();
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
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case ListOfCallParameters:
      if (strcmp(pszName, "ListOfCallParameters")) fatalError();
      mCurrentElement = KineticLaw;
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
      fatalError();
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
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case CallParameter:
      if (strcmp(pszName, "CallParameter")) fatalError();
      mCurrentElement = ListOfCallParameters;
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
  std::map< std::string, std::string >::const_iterator FunctionParameterKey;

  mCurrentElement++; /* We should always be on the next element */

  switch (mCurrentElement)
    {
    case CallParameter:
      if (strcmp(pszName, "CallParameter")) fatalError();

      FunctionParameter =
        mParser.getAttributeValue("functionParameter", papszAttrs);
      FunctionParameterKey = mCommon.KeyMap.find(FunctionParameter);
      if (FunctionParameterKey == mCommon.KeyMap.end()) fatalError();
      mpFunctionParameter =
        (CFunctionParameter*)(CCopasiContainer*)CKeyFactory::get(FunctionParameterKey->second);

      mCommon.SourceParameterKeys.clear();
      break;

#ifdef XXXX
    case SourceParameter:
      if (strcmp(pszName, "SourceParameter")) fatalError();

      /* If we do not have a SourceParameter element handler we create one. */
      if (!mpCurrentHandler)
        mpCurrentHandler = new SourceParameterElement(mParser, mCommon);

      /* Push the SourceParameter element handler on the stack and call it. */
      mParser.pushElementHandler(mpCurrentHandler);
      mpCurrentHandler->start(pszName, papszAttrs);
      break;
#endif // XXXX

    default:
      fatalError();
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
#ifdef XXXX
      if (mCommon.SourceParameterKeys.size() > 0)
        {
          mCommon.pReaction->setParameterKeys(mpFunctionParameter->getName(),
                                              mCommon.SourceParameterKeys);
          mCommon.SourceParameterKeys.clear();
        }
#endif // XXXX
      mParser.popElementHandler();
      mCurrentElement = -1;

      /* Tell the parent element we are done. */
      mParser.onEndElement(pszName);
      break;

    case SourceParameter:
      if (strcmp(pszName, "SourceParameter")) fatalError();
      mCurrentElement = CallParameter;
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

CCopasiXMLParser::ListOfTasksElement::~ListOfTasksElement() {}

void CCopasiXMLParser::ListOfTasksElement::start(const XML_Char * C_UNUSED(pszName),
    const XML_Char ** C_UNUSED(papszAttrs))
{}

void CCopasiXMLParser::ListOfTasksElement::end(const XML_Char * C_UNUSED(pszName)) {}

CCopasiXMLParser::ListOfReportsElement::ListOfReportsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ListOfReportsElement::~ListOfReportsElement() {}

void CCopasiXMLParser::ListOfReportsElement::start(const XML_Char * C_UNUSED(pszName),
    const XML_Char ** C_UNUSED(papszAttrs))
{}

void CCopasiXMLParser::ListOfReportsElement::end(const XML_Char * C_UNUSED(pszName)) {}
