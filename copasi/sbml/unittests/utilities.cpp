// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/utilities.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:42:28 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/xml/CCopasiXML.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/model/CModel.h"
#include "copasi/plot/COutputDefinitionVector.h"
#include "copasi/layout/CListOfLayouts.h"

bool load_cps_model_from_stream(std::istream& is, CCopasiDataModel& dataModel)
{
  CCopasiMessage::clearDeque();

  std::string line;
  is >> line;

  if (!line.find("<?xml") != std::string::npos)
    {
      is.seekg(0, std::ios_base::beg);

      CCopasiXML XML;

      XML.setFunctionList(&CCopasiRootContainer::Root->getFunctionList()->loadedFunctions());
      XML.setDatamodel(&dataModel);

      if (!XML.load(is, std::string("")))
        {
          XML.freeModel();
          XML.freeTaskList();
          XML.freeReportList();
          XML.freePlotList();
          XML.freeGUI();
          XML.freeLayoutList();
          return false;
        }

      dataModel.newModel(XML.getModel(), NULL);

      if (XML.getTaskList())
        {
          CCopasiVectorN<CCopasiTask>* pTaskList = dataModel.getTaskList();
          *pTaskList = *XML.getTaskList();
          dataModel.getTaskList()->setObjectName("TaskList");
          dataModel.add(dataModel.getTaskList(), true);
          dataModel.addDefaultTasks();
        }

      if (XML.getReportList())
        {
          CReportDefinitionVector* pReportDefinitions = dataModel.getReportDefinitionList();
          *pReportDefinitions = *XML.getReportList();
          dataModel.add(dataModel.getTaskList(), true);
          dataModel.addDefaultReports();
        }

      if (XML.getPlotList())
        {
          COutputDefinitionVector* pPlotList = dataModel.getPlotDefinitionList();
          *pPlotList = *XML.getPlotList();
        }

      //TODO: layouts
      if (XML.getLayoutList())
        {
          CListOfLayouts* pListOfLayouts = dataModel.getListOfLayouts();
          *pListOfLayouts = *XML.getLayoutList();
        }
    }
  else
    {
      return false;
    }

  if (dataModel.getModel() != NULL)
    {
      dataModel.getModel()->compileIfNecessary(NULL);
      dataModel.getModel()->updateInitialValues();
    }

  dataModel.changed(false);

  return true;
}

bool import_sbml_model_from_stream(const std::istream& /*is*/, CCopasiDataModel& /*dataModel*/)
{
  // TODO implement me
  return false;
}
