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

#include "ModelParameterSetHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/model/CModel.h"

/**
 * Replace ModelParameterSet with the name type of the handler and implement the
 * three methods below.
 */
ModelParameterSetHandler::ModelParameterSetHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ModelParameterSet),
  mKey()
{
  init();
}

// virtual
ModelParameterSetHandler::~ModelParameterSetHandler()
{}

// virtual
CXMLHandler * ModelParameterSetHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * Name;

  switch (mCurrentElement.first)
    {
      case ModelParameterSet:
        // Element specific code.
        mKey = mpParser->getAttributeValue("key", papszAttrs);
        Name = mpParser->getAttributeValue("name", papszAttrs);

        {
          CModelParameterSet * pModelParameterSet = new CModelParameterSet(Name);
          int index = 1;

          // We need to resolve naming conflicts.
          while (!mpData->pModel->getModelParameterSets().add(pModelParameterSet, true))
            {
              std::ostringstream NewName;
              NewName << Name << "[" << index++ << "]";
              pModelParameterSet->setObjectName(NewName.str());
            }

          mpData->ModelParameterGroupStack.push(pModelParameterSet->toGroup());
          mpData->mKeyMap.addFix(mKey, pModelParameterSet);
        }
        break;

      case MiriamAnnotation:
      case Comment:
      case ModelParameterGroup:
      case ModelParameter:
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      case ListOfUnsupportedAnnotations:
        mpData->mUnsupportedAnnotations.clear();
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
bool ModelParameterSetHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ModelParameterSet:
        finished = true;
        mpData->ModelParameterGroupStack.pop();
        break;

      case MiriamAnnotation:

      {
        CModelParameterSet * pModelParameterSet = mpData->ModelParameterGroupStack.top()->toSet();
        pModelParameterSet->setMiriamAnnotation(mpData->CharacterData, pModelParameterSet->getKey(), mKey);
      }

      mpData->CharacterData = "";
      break;

      case Comment:

        mpData->ModelParameterGroupStack.top()->toSet()->setNotes(mpData->CharacterData);
        mpData->CharacterData = "";
        break;

      case ListOfUnsupportedAnnotations:
        mpData->ModelParameterGroupStack.top()->toSet()->getUnsupportedAnnotations() = mpData->mUnsupportedAnnotations;
        break;

      case ModelParameterGroup:
      case ModelParameter:

        if (mpData->pCurrentModelParameter != NULL)
          {
            mpData->ModelParameterGroupStack.top()->add(mpData->pCurrentModelParameter);
            mpData->pCurrentModelParameter = NULL;
          }

        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ModelParameterSetHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ModelParameterSet, HANDLER_COUNT}},
    {"ModelParameterSet", ModelParameterSet, ModelParameterSet, {MiriamAnnotation, Comment, ListOfUnsupportedAnnotations, ModelParameterGroup, ModelParameter, AFTER, HANDLER_COUNT}},
    {"MiriamAnnotation", MiriamAnnotation, MiriamAnnotation, {Comment, ListOfUnsupportedAnnotations, ModelParameterGroup, ModelParameter, AFTER, HANDLER_COUNT}},
    {"Comment", Comment, Comment, {ListOfUnsupportedAnnotations, ModelParameterGroup, ModelParameter, AFTER, HANDLER_COUNT}},
    {"ListOfUnsupportedAnnotations", ListOfUnsupportedAnnotations, ListOfUnsupportedAnnotations, {ModelParameterGroup, ModelParameter, AFTER, HANDLER_COUNT}},
    {"ModelParameterGroup", ModelParameterGroup, ModelParameterGroup, {ModelParameterGroup, ModelParameter, AFTER, HANDLER_COUNT}},
    {"ModelParameter", ModelParameter, ModelParameter, {ModelParameterGroup, ModelParameter, AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
