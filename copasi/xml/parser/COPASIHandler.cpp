// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "COPASIHandler.h"
#include "CXMLParser.h"

#include "utilities/CVersion.h"
#include "utilities/CCopasiParameter.h"
#include "report/CCopasiRootContainer.h"
#include "report/CReportDefinitionVector.h"
#include "plot/COutputDefinitionVector.h"
#include "function/CFunction.h"

COPASIHandler::COPASIHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::COPASI)
{
  init();
}

// virtual
COPASIHandler::~COPASIHandler()
{}

// virtual
CXMLHandler * COPASIHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  const char * versionMajor;
  C_INT32 VersionMajor;
  const char * versionMinor;
  C_INT32 VersionMinor;
  const char * versionDevel;
  C_INT32 VersionDevel;
  bool CopasiSourcesModified = true;

  switch (mCurrentElement.first)
    {
      case COPASI:
        versionMajor = mpParser->getAttributeValue("versionMajor", papszAttrs, "0");
        VersionMajor = strToInt(versionMajor);
        versionMinor = mpParser->getAttributeValue("versionMinor", papszAttrs, "0");
        VersionMinor = strToInt(versionMinor);
        versionDevel = mpParser->getAttributeValue("versionDevel", papszAttrs, "0");
        VersionDevel = strToInt(versionDevel);
        CopasiSourcesModified = mpParser->toBool(mpParser->getAttributeValue("copasiSourcesModified", papszAttrs, "true"));

        mpData->pVersion->setVersion(VersionMajor, VersionMinor, VersionDevel, CopasiSourcesModified);

        break;

      case ParameterGroup:
      case ListOfFunctions:
      case Model:
      case ListOfLayouts:
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      case ListOfTasks:
        if (mpData->pTaskList != NULL)
          mpData->pTaskList->clear();
        else
          mpData->pTaskList = new CCopasiVectorN<CCopasiTask>("TaskList");

        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      case ListOfReports:
        if (mpData->pReportList != NULL)
          mpData->pReportList->clear();
        else
          mpData->pReportList = new CReportDefinitionVector();

        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      case ListOfPlots:
        if (mpData->pPlotList != NULL)
          mpData->pPlotList->clear();
        else
          mpData->pPlotList = new COutputDefinitionVector();

        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      case GUI:
        if (!mpData->pGUI)
          mCurrentElement = std::make_pair(UNKNOWN, UNKNOWN);

        pHandlerToCall = getHandler(mCurrentElement.second);

        break;

      case SBMLReference:
        if (mpData->pDataModel)
          mpData->pDataModel->setSBMLFileName(mpParser->getAttributeValue("file", papszAttrs));

        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      case ListOfUnitDefinitions:
        if (mpData->pUnitDefinitionImportList != NULL)
          mpData->pUnitDefinitionImportList->clear();
        else
          mpData->pUnitDefinitionImportList = new CUnitDefinitionDB("importUnitDefintionsList");

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
bool COPASIHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case COPASI:
      {
        // We need to handle the unmapped parameters of type key.
        std::vector< std::string >::iterator it = mpData->UnmappedKeyParameters.begin();
        std::vector< std::string >::iterator end = mpData->UnmappedKeyParameters.end();

        for (; it != end; ++it)
          {
            CCopasiParameter * pParameter =
              dynamic_cast< CCopasiParameter * >(CCopasiRootContainer::getKeyFactory()->get(*it));

            if (pParameter != NULL &&
                pParameter->getType() == CCopasiParameter::KEY)
              {
                CCopasiObject * pObject =
                  mpData->mKeyMap.get(pParameter->getValue< std::string >());

                if (pObject != NULL)
                  pParameter->setValue(pObject->getKey());
                else
                  pParameter->setValue(std::string(""));
              }
          }

        // We need to remove the no longer needed expression "Objective Function" from the function list.
        if (mpData->pFunctionList != NULL &&
            mpData->pFunctionList->getIndex("Objective Function") != C_INVALID_INDEX)
          {
            mpData->pFunctionList->remove("Objective Function");
          }
      }

      finished = true;
      break;

      case ParameterGroup:
        finished = true;
        break;

      case ListOfFunctions:
      case Model:
      case ListOfTasks:
      case ListOfReports:
      case ListOfPlots:
      case ListOfLayouts:
      case SBMLReference:
      case ListOfUnitDefinitions:
        break;

      case GUI:
        if (mpData->pGUI == NULL)
          {
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
CXMLHandler::sProcessLogic * COPASIHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {COPASI, ParameterGroup, HANDLER_COUNT}},
    {"COPASI", COPASI, COPASI, {ListOfFunctions, Model, ListOfTasks, ListOfReports, ListOfPlots, GUI, ListOfLayouts, SBMLReference, ListOfUnitDefinitions, AFTER, HANDLER_COUNT}},
    {"ListOfFunctions", ListOfFunctions, ListOfFunctions, {Model, ListOfTasks, ListOfReports, ListOfPlots, GUI, ListOfLayouts, SBMLReference, ListOfUnitDefinitions, AFTER, HANDLER_COUNT}},
    {"Model", Model, Model, {ListOfTasks, ListOfReports, ListOfPlots, GUI, ListOfLayouts, SBMLReference, ListOfUnitDefinitions, AFTER, HANDLER_COUNT}},
    {"ListOfTasks", ListOfTasks, ListOfTasks, {ListOfReports, ListOfPlots, GUI, ListOfLayouts, SBMLReference, ListOfUnitDefinitions, AFTER, HANDLER_COUNT}},
    {"ListOfReports", ListOfReports, ListOfReports, {ListOfPlots, GUI, ListOfLayouts, SBMLReference, ListOfUnitDefinitions, AFTER, HANDLER_COUNT}},
    {"ListOfPlots", ListOfPlots, ListOfPlots, {GUI, ListOfLayouts, SBMLReference, ListOfUnitDefinitions, AFTER, HANDLER_COUNT}},
    {"GUI", GUI, GUI, {ListOfLayouts, SBMLReference, ListOfUnitDefinitions, AFTER, HANDLER_COUNT}},
    {"ListOfLayouts", ListOfLayouts, ListOfLayouts, {SBMLReference, ListOfUnitDefinitions, AFTER, HANDLER_COUNT}},
    {"SBMLReference", SBMLReference, SBMLReference, {ListOfUnitDefinitions, AFTER, HANDLER_COUNT}},
    {"ListOfUnitDefinitions", ListOfUnitDefinitions, ListOfUnitDefinitions, {AFTER, HANDLER_COUNT}},
    {"ParameterGroup", ParameterGroup, ParameterGroup, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
