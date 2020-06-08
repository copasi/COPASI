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

#include "copasi/copasi.h"

#include "ParameterGroupHandler.h"

#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/utilities/CCopasiParameterGroup.h"
#include "copasi/utilities/CCopasiTask.h"

/**
 * Replace ParameterGroup with the name type of the handler and implement the
 * three methods below.
 */
ParameterGroupHandler::ParameterGroupHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ParameterGroup),
  mDerivedElement(),
  mParameterGroupStack(),
  mNonUniqueParameters()
{
  init();

  mNonUniqueParameters["ScanItems"].insert("ScanItem");

  mNonUniqueParameters["OptimizationItemList"].insert("OptimizationItem");
  mNonUniqueParameters["OptimizationItemList"].insert("FitItem");

  mNonUniqueParameters["OptimizationConstraintList"].insert("OptimizationItem");
  mNonUniqueParameters["OptimizationConstraintList"].insert("FitItem");

  mNonUniqueParameters["Affected Experiments"].insert("Experiment Key");
  mNonUniqueParameters["Affected Cross Validation Experiments"].insert("Experiment Key");

  mNonUniqueParameters["ListOfVariables"].insert("Variables");

  mNonUniqueParameters["Deterministic Reactions"].insert("Reaction");

  mNonUniqueParameters["ListOfParameters"].insert("ParameterCN");
  mNonUniqueParameters["ListOfTargets"].insert("TargetCN");
}

// virtual
ParameterGroupHandler::~ParameterGroupHandler()
{}

// virtual
CXMLHandler * ParameterGroupHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  std::string name;

  switch (mCurrentElement.first)
    {
      case ParameterGroup:
        if (mParameterGroupStack.size() != mLevel + 1)
          {
            name = mpParser->getAttributeValue("name", papszAttrs);
            mParameterGroupStack.push(new CCopasiParameterGroup(name));
          }

        break;

      case Parameter:
      case ParameterText:
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool ParameterGroupHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ParameterGroup:
        finished = (mLevel == 0);

        mpData->pCurrentParameter = mParameterGroupStack.top();
        mParameterGroupStack.pop();
        break;

      case Parameter:

        // We need to fix the "Key" parameter of each "Experiment" of the the "Parameter Estimation" problem,
        // since they are handled by the elevation of the problem to CFitProblem.
        if (mpData->pCurrentTask != NULL &&
            mpData->pCurrentTask->getType() == CTaskEnum::Task::parameterFitting &&
            (mpData->pCurrentParameter->getObjectName() == "Key" ||
             mpData->pCurrentParameter->getObjectName() == "Experiment Key"))
          {
            if (mpData->UnmappedKeyParameters.size() > 0 &&
                mpData->UnmappedKeyParameters[mpData->UnmappedKeyParameters.size() - 1] == mpData->pCurrentParameter->getKey())
              mpData->UnmappedKeyParameters.erase(mpData->UnmappedKeyParameters.begin() + mpData->UnmappedKeyParameters.size() - 1);
          }

        break;

      case ParameterText:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  // If we are not finished we need to add the current parameter to the group at the top of the stack
  if (!finished)
    {
      CCopasiParameter * pParameter = NULL;

      // Derived elements like methods and problems have already parameters:
      if (mDerivedElement != "" &&
          isUniqueParameter())
        {
          pParameter =
            mParameterGroupStack.top()->getParameter(mpData->pCurrentParameter->getObjectName());
        }

      if (pParameter != NULL)
        {
          CCopasiParameter::Type OriginalType = pParameter->getType();
          *pParameter = *mpData->pCurrentParameter;

          if (mpData->UnmappedKeyParameters.size() > 0 &&
              mpData->UnmappedKeyParameters[mpData->UnmappedKeyParameters.size() - 1] == mpData->pCurrentParameter->getKey())
            {
              if (OriginalType == CCopasiParameter::Type::KEY)
                {
                  mpData->UnmappedKeyParameters[mpData->UnmappedKeyParameters.size() - 1] = pParameter->getKey();
                }
              else
                {
                  mpData->UnmappedKeyParameters.erase(mpData->UnmappedKeyParameters.begin() + mpData->UnmappedKeyParameters.size() - 1);
                }
            }

          pdelete(mpData->pCurrentParameter);
        }
      else
        {
          mParameterGroupStack.top()->addParameter(mpData->pCurrentParameter);
          mpData->pCurrentParameter = NULL;
        }
    }
  else if (mDerivedElement != "")
    {
      mElementName2Type.erase(mDerivedElement);
      mDerivedElement = "";
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ParameterGroupHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ParameterGroup, HANDLER_COUNT}},
    {"ParameterGroup", ParameterGroup, ParameterGroup, {ParameterGroup, Parameter, ParameterText, AFTER, HANDLER_COUNT}},
    {"Parameter", Parameter, Parameter, {ParameterGroup, Parameter, ParameterText, AFTER, HANDLER_COUNT}},
    {"ParameterText", ParameterText, ParameterText, {ParameterGroup, Parameter, ParameterText, AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}

void ParameterGroupHandler::setDerivedElement(const XML_Char * pszName, CCopasiParameterGroup * pDerivedElement)
{
  assert(mLevel == 0);

  if (mElementName2Type.find(pszName) == mElementName2Type.end())
    {
      mDerivedElement = pszName;
      mElementName2Type[mDerivedElement] = std::make_pair(ParameterGroup, ParameterGroup);
    }

  mParameterGroupStack.push(pDerivedElement);
}

bool ParameterGroupHandler::isUniqueParameter() const
{
  std::map< std::string, std::set< std::string > >::const_iterator found = mNonUniqueParameters.find(mParameterGroupStack.top()->getObjectName());

  if (found == mNonUniqueParameters.end()) return true;

  return (found->second.find(mpData->pCurrentParameter->getObjectName()) == found->second.end());
}
