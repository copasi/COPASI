// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/utilities.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/04/26 16:10:39 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

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

      XML.setFunctionList(&CCopasiRootContainer::getFunctionList()->loadedFunctions());
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

      dataModel.newModel(XML.getModel(), NULL, NULL, true);

      if (XML.getTaskList())
        {
          CCopasiVectorN<CCopasiTask>* pTaskList = dataModel.getTaskList();
          *pTaskList = *XML.getTaskList();
          dataModel.getTaskList()->setObjectName("TaskList");
          dataModel.add(dataModel.getTaskList(), true);
          dataModel.addDefaultTasks();
//          The code below is from CCopasiDataModel. Since it was not needed for the unittests for far, I have not activated it. 09/10/2012 RG
//
//          // We need to initialize all the task so that results are available
//
//          // We suppress all errors and warnings
//          size_t Size = CCopasiMessage::size();
//
//          CCopasiVectorN< CCopasiTask >::iterator it = mData.pTaskList->begin();
//          CCopasiVectorN< CCopasiTask >::iterator end = mData.pTaskList->end();
//
//          for (; it != end; ++it)
//            {
//              try
//                {
//                  (*it)->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);
//                }
//
//              catch (...) {}
//            }
//
//          // Remove error messages created by the task initialization as this may fail
//          // due to incomplete task specification at this time.
//          while (CCopasiMessage::size() > Size)
//            CCopasiMessage::getLastMessage();

        }

      // the code below is a hack.
      // Normally the add method would make sure that all objects belong to the container they arer added to, 
      // but since this method does not have accesss to the internal elements of the data model, the properties can't be
      // set in the same way as it is done in the load method for CCopasiDataModel
      if (XML.getReportList())
        {
          CReportDefinitionVector* pReportDefinitions = dataModel.getReportDefinitionList();
          *pReportDefinitions = *XML.getReportList();
          dataModel.add(dataModel.getTaskList(), true);
          unsigned int i=0,iMax=pReportDefinitions->size();
          CReportDefinition* pReport=NULL;
          while(i < iMax)
          {
            pReport=(*pReportDefinitions)[i];
            pReport->setObjectParent(pReportDefinitions);
            ++i;
          }
          dataModel.addDefaultReports();
        }

      if (XML.getPlotList())
        {
          COutputDefinitionVector* pPlotList = dataModel.getPlotDefinitionList();
          *pPlotList = *XML.getPlotList();
          dataModel.add(pPlotList, true);
          unsigned int i=0,iMax=pPlotList->size();
          CPlotSpecification* pPlot=NULL;
          while(i < iMax)
          {
            pPlot=(*pPlotList)[i];
            pPlot->setObjectParent(pPlotList);
            ++i;
          }
        }

      //TODO: layouts
      if (XML.getLayoutList())
        {
          CListOfLayouts* pListOfLayouts = dataModel.getListOfLayouts();
          *pListOfLayouts = *XML.getLayoutList();
          // adding does not seem to work
          dataModel.add(pListOfLayouts,true);
          // so I do it manually
          unsigned int i=0,iMax=pListOfLayouts->size();
          CLayout* pLayout=NULL;
          while(i < iMax)
          {
            pLayout=(*pListOfLayouts)[i];
            pLayout->setObjectParent(pListOfLayouts);
            ++i;
          }

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

bool save_cps_model_to_stream(std::ostream& os, CCopasiDataModel* pDataModel)
{
  bool success = true;

  if (pDataModel != NULL &&
      pDataModel->getModel() != NULL)
    {
      CCopasiXML XML;

      XML.setModel(pDataModel->getModel());
      XML.setTaskList(pDataModel->getTaskList());
      XML.setReportList(pDataModel->getReportDefinitionList());
      XML.setPlotList(pDataModel->getPlotDefinitionList());
      XML.setGUI(pDataModel->getGUI());
      XML.setLayoutList(*pDataModel->getListOfLayouts());
      XML.setDatamodel(pDataModel);

      try
        {
          success = XML.save(os, "");
        }
      catch (...)
        {
          return false;
        }
    }
  else
    {
      success = false;
    }

  return success;
}

