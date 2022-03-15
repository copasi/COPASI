// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

#include "FunctionHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/function/CFunction.h"
#include "copasi/function/CExpression.h"

/**
 * Replace Function with the name type of the handler and implement the
 * three methods below.
 */
FunctionHandler::FunctionHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Function),
  mKey(),
  mInfix(),
  mExistingFunctionIndex()
{
  init();
}

// virtual
FunctionHandler::~FunctionHandler()
{}

// virtual
CXMLHandler * FunctionHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  const char * type;
  CEvaluationTree::Type Type;
  const char * Name;
  const char * Reversible;
  size_t Index;

  CEvaluationTree* pEvaluationTree = NULL;

  switch (mCurrentElement.first)
    {
      case Function:
        mKey = mpParser->getAttributeValue("key", papszAttrs);
        Name = mpParser->getAttributeValue("name", papszAttrs);
        type = mpParser->getAttributeValue("type", papszAttrs);
        Type = toEnum(type, CEvaluationTree::XMLType, CEvaluationTree::UserDefined);

        Reversible = mpParser->getAttributeValue("reversible", papszAttrs, false);

        if (!Reversible) // We may have an old file format using positive
          Reversible = mpParser->getAttributeValue("positive", papszAttrs, "unspecified");

        mpData->mPredefinedFunction = false;
        mpData->mFunctionParameterKeyMap.clear();
        mExistingFunctionIndex.clear();

        pEvaluationTree = CEvaluationTree::create(Type);

        if (Type == CEvaluationTree::Expression)
          {
            mpData->pFunction = NULL;

            mpData->mpExpression = static_cast< CExpression * >(pEvaluationTree);
            mpData->mKey2ObjectiveFunction[mKey] = mpData->mpExpression;
          }
        else
          {
            mpData->mpExpression = NULL;

            mpData->pFunction = static_cast<CFunction *>(pEvaluationTree);
            mpData->pFunction->setObjectName(Name);

            if (!strcmp(Reversible, "true"))
              mpData->pFunction->setReversible(TriTrue);
            else if (!strcmp(Reversible, "false"))
              mpData->pFunction->setReversible(TriFalse);
            else
              mpData->pFunction->setReversible(TriUnspecified);

            Index = mpData->pFunctionList->getIndex(Name);

            if (Index != C_INVALID_INDEX) // A function with that name exists.
              {
                mExistingFunctionIndex.insert(Index);

                switch ((*mpData->pFunctionList)[Index].getType())
                  {
                    case CEvaluationTree::MassAction:

                      if (Type == CEvaluationTree::MassAction)
                        {
                          pdelete(mpData->pFunction);
                          mpData->pFunction = &mpData->pFunctionList->operator[](Index);
                          mpData->mPredefinedFunction = true;
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
                              Index = mpData->pFunctionList->getIndex(NewName);

                              if (Index == C_INVALID_INDEX)
                                break;

                              mExistingFunctionIndex.insert(Index);
                            }

                          mpData->pFunction->setObjectName(NewName);
                        }

                      break;

                    case CEvaluationTree::PreDefined:

                      if (Type == CEvaluationTree::PreDefined)
                        {
                          pdelete(mpData->pFunction);
                          mpData->pFunction = &mpData->pFunctionList->operator[](Index);
                          mpData->mPredefinedFunction = true;
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
                              Index = mpData->pFunctionList->getIndex(NewName);

                              if (Index == C_INVALID_INDEX)
                                break;

                              mExistingFunctionIndex.insert(Index);
                            }

                          mpData->pFunction->setObjectName(NewName);
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
                          Index = mpData->pFunctionList->getIndex(NewName);

                          if (Index == C_INVALID_INDEX)
                            break;

                          mExistingFunctionIndex.insert(Index);
                        }

                      mpData->pFunction->setObjectName(NewName);
                    }

                    break;

                    default:
                      break;
                  }
              }
          }

        break;

      case MiriamAnnotation:
      case Comment:
      case Expression:
      case MathML:
      case Text:
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      case ListOfParameterDescriptions:
        mpData->mFunctionParameterKeyMap.clear();
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
bool FunctionHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Function:
        finished = true;

        if (mpData->pFunction != NULL)
          {
            if (!mpData->mPredefinedFunction)
              {
                // TODO We need to check whether any existing function with the same
                // name is identical

                std::set< size_t >::const_iterator it = mExistingFunctionIndex.begin();
                std::set< size_t >::const_iterator end = mExistingFunctionIndex.end();

                for (; it != end; ++it)
                  {
                    CFunction * pFunction = &mpData->pFunctionList->operator[](*it);

                    if (*pFunction == *mpData->pFunction)
                      {
                        pdelete(mpData->pFunction);
                        mpData->pFunction = &mpData->pFunctionList->operator[](*it);

                        break;
                      }
                  }

                /* We have a new function and add it to the list */
                if (it == end)
                  {
                    mpData->pFunctionList->add(mpData->pFunction, true);
                  }
              }

            addFix(mKey, mpData->pFunction);

            std::map< size_t, std::string >::const_iterator it = mpData->mFunctionParameterKeyMap.begin();
            std::map< size_t, std::string >::const_iterator end = mpData->mFunctionParameterKeyMap.end();

            for (size_t Index = 0; it != end; ++it, ++Index)
              {
                addFix(it->second, mpData->pFunction->getVariables()[Index]);
              }
          }

        break;

      case MiriamAnnotation:

        if (mpData->pFunction != NULL)
          {
            mpData->pFunction->setMiriamAnnotation(mpData->CharacterData, mpData->pFunction->getKey(), mKey);
            mpData->CharacterData = "";
          }

        break;

      case Comment:

        if (mpData->pFunction != NULL)
          {
            mpData->pFunction->setNotes(mpData->CharacterData);
            mpData->CharacterData = "";
          }

        break;

      case ListOfUnsupportedAnnotations:

        if (mpData->pFunction != NULL)
          {
            mpData->pFunction->getUnsupportedAnnotations() = mpData->mUnsupportedAnnotations;
          }

        break;

      case Expression:
      case MathML:
      case Text:
        mInfix = mpData->CharacterData;

        if (mpData->mpExpression != NULL)
          {
            mpData->mpExpression->setInfix(mInfix);
          }

        break;

      case ListOfParameterDescriptions:
        // We need to remove all parameters which have been temporarily added to the list of variables
      {
        CFunction * pFunction = dynamic_cast<CFunction *>(mpData->pFunction);

        if (pFunction)
          {
            CFunctionParameters & Variables = pFunction->getVariables();
            size_t i = Variables.size() - 1;

            for (; i != C_INVALID_INDEX && Variables[i]->getUsage() == CFunctionParameter::Role::TEMPORARY; i--)
              Variables.remove(Variables[i]->getObjectName());
          }

        size_t Size = CCopasiMessage::size();

        if (mpData->pFunction != NULL &&
            !mpData->mPredefinedFunction)
          {
            mpData->pFunction->setInfix(mInfix);
          }
        else if (mpData->mpExpression != NULL)
          {
            mpData->mpExpression->setInfix(mInfix);
          }

        // Remove error messages created by setInfix as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          CCopasiMessage::getLastMessage();
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
CXMLHandler::sProcessLogic * FunctionHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Function, HANDLER_COUNT}},
    {"Function", Function, Function, {MiriamAnnotation, Comment, ListOfUnsupportedAnnotations, Expression, MathML, Text, HANDLER_COUNT}},
    {"MiriamAnnotation", MiriamAnnotation, MiriamAnnotation, {Comment, ListOfUnsupportedAnnotations, Expression, MathML, Text, HANDLER_COUNT}},
    {"Comment", Comment, Comment, {ListOfUnsupportedAnnotations, Expression, MathML, Text, HANDLER_COUNT}},
    {"ListOfUnsupportedAnnotations", ListOfUnsupportedAnnotations, ListOfUnsupportedAnnotations, {Expression, MathML, Text, HANDLER_COUNT}},
    {"Expression", Expression, CharacterData, {ListOfParameterDescriptions, AFTER, HANDLER_COUNT}},
    {"MathML", MathML, CharacterData, {Text, ListOfParameterDescriptions, AFTER, HANDLER_COUNT}},
    {"Text", Text, CharacterData, {ListOfParameterDescriptions, AFTER, HANDLER_COUNT}},
    {"ListOfParameterDescriptions", ListOfParameterDescriptions, ListOfParameterDescriptions, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
