// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/DataModelGUI.cpp,v $
//   $Revision: 1.83 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:48:27 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "DataModelGUI.h"
#include "DataModel.txt.h"
#include "qtUtilities.h"
#include "utilities/CVector.h"
#include "CProgressBar.h"
#include "listviews.h"

#include "function/CFunctionDB.h"
#include "model/CModel.h"
#include "model/CModelValue.h"
#include "model/CMetabNameInterface.h"
#include "plotUI/COutputHandlerPlot.h"
#include "plot/COutputDefinitionVector.h"
#include "report/CReportDefinitionVector.h"
#include "scan/CScanTask.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CMCATask.h"
#include "trajectory/CTrajectoryTask.h"

#ifdef COPASI_TSSA
#include "tssanalysis/CTSSATask.h"
#endif // COPASI_TSSA

#ifdef COPASI_TSS
#include "tss/CTSSTask.h"
#endif

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "utilities/CCopasiException.h"
#include "commandline/CConfigurationFile.h"

//*****************************************************************************

DataModelGUI::DataModelGUI():
    mOutputHandlerPlot()
{
  this->populateData();
  assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
  (*CCopasiRootContainer::Root->getDatamodelList())[0]->addInterface(&mOutputHandlerPlot);

  //mpMathModel = NULL;
  //mMathModelUpdateScheduled = false;
}

//************************************************************

void DataModelGUI::linkDataModelToGUI()
{
  assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::Root->getDatamodelList())[0];
  assert(pDataModel != NULL);
  //math model
  //pdelete(mpMathModel);
  //mpMathModel = new CMathModel();
  //mpMathModel->setModel((*CCopasiRootContainer::Root->getDatamodelList())[0]->getModel());

  //connect the folder tree with the backend objects
  mTree.findNodeFromId(1)->setObjectKey(pDataModel->getModel()->getKey());
  mTree.findNodeFromId(21)->setObjectKey((*pDataModel->getTaskList())["Steady-State"]->getKey());
  mTree.findNodeFromId(221)->setObjectKey((*pDataModel->getTaskList())["Elementary Flux Modes"]->getKey());
  mTree.findNodeFromId(222)->setObjectKey((*pDataModel->getTaskList())["Moieties"]->getKey());
  mTree.findNodeFromId(2221)->setObjectKey((*pDataModel->getTaskList())["Moieties"]->getKey());
  mTree.findNodeFromId(23)->setObjectKey((*pDataModel->getTaskList())["Time-Course"]->getKey());
  mTree.findNodeFromId(24)->setObjectKey((*pDataModel->getTaskList())["Metabolic Control Analysis"]->getKey());

#ifdef COPASI_TSS
  mTree.findNodeFromId(25)->setObjectKey((*pDataModel->getTaskList())["Time Scale Separation"]->getKey());
#endif

#ifdef COPASI_TSSA
  mTree.findNodeFromId(27)->setObjectKey((*pDataModel->getTaskList())["Time Scale Separation Analysis"]->getKey());
#endif // COPASI_TSSA

  mTree.findNodeFromId(26)->setObjectKey((*pDataModel->getTaskList())["Lyapunov Exponents"]->getKey());

  mTree.findNodeFromId(31)->setObjectKey((*pDataModel->getTaskList())["Scan"]->getKey());
  mTree.findNodeFromId(32)->setObjectKey((*pDataModel->getTaskList())["Optimization"]->getKey());
  mTree.findNodeFromId(33)->setObjectKey((*pDataModel->getTaskList())["Parameter Estimation"]->getKey());

  mTree.findNodeFromId(34)->setObjectKey((*pDataModel->getTaskList())["Sensitivities"]->getKey());

  mTree.findNodeFromId(117)->setObjectKey(pDataModel->getModel()->getKey()); //parameters

  mTree.findNodeFromId(43)->setObjectKey(pDataModel->getReportDefinitionList()->getKey());
  //mTree.findNodeFromId(42)->setObjectKey(mPlotDefinitionList.getKey());
  mTree.findNodeFromId(42)->setObjectKey(pDataModel->getPlotDefinitionList()->getKey());

  ListViews::setDataModel(this);
}

void DataModelGUI::populateData()
{
  std::stringstream in;
  in.str(DataModeltxt);

  std::string str1;
  std::string delimiter("\x0a\x0d");
  char c;

  while (!in.eof())
    {
      str1 = "";
      while (!in.fail())
        {
          in.get(c);
          if (delimiter.find(c) != std::string::npos) break;
          str1 += c;
        }

      if (str1 == "") break;

      QString data(FROM_UTF8(str1));

      int first = data.find(':');
      int second = data.find(':', first + 1);
      int parentId = data.mid(0, first).toInt();
      int myId = data.mid(first + 1, second - first - 1).toInt();
      QString str = data.mid(second + 1, data.length() - second - 1);

      mTree.add(parentId, myId, str, "");
    }
}

void DataModelGUI::updateCompartments()
{
  IndexedNode * parent = mTree.findNodeFromId(111);

  parent->removeChildren();

  assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
  if ((*CCopasiRootContainer::Root->getDatamodelList())[0]->getModel() == NULL) return;
  const CCopasiVectorN< CCompartment > & objects = (*CCopasiRootContainer::Root->getDatamodelList())[0]->getModel()->getCompartments();
  C_INT32 j, jmax = objects.size();
  CCompartment *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      parent->addChild(-1,
                        FROM_UTF8(obj->getObjectName()),
                        obj->getKey());
    }
}

void DataModelGUI::updateMetabolites()
{
  IndexedNode * parent = mTree.findNodeFromId(112);

  parent->removeChildren();

  assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
  const CCopasiVector< CMetab > & objects = (*CCopasiRootContainer::Root->getDatamodelList())[0]->getModel()->getMetabolites();
  C_INT32 j, jmax = objects.size();
  CMetab *metab;
  for (j = 0; j < jmax; j++)
    {
      metab = objects[j];
      parent->addChild(-1,
                        FROM_UTF8(CMetabNameInterface::getDisplayName((*CCopasiRootContainer::Root->getDatamodelList())[0]->getModel(), *metab)),
                        metab->getKey());
    }
}

void DataModelGUI::updateReactions()
{
  IndexedNode * parent = mTree.findNodeFromId(114);

  parent->removeChildren();

  assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
  const CCopasiVectorN< CReaction > & objects = (*CCopasiRootContainer::Root->getDatamodelList())[0]->getModel()->getReactions();
  C_INT32 j, jmax = objects.size();
  CReaction *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      obj->compile();
      parent->addChild(-1,
                        FROM_UTF8(obj->getObjectName()),
                        obj->getKey());
    }
}

void DataModelGUI::updateModelValues()
{
  IndexedNode * parent = mTree.findNodeFromId(115);

  parent->removeChildren();

  assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
  const CCopasiVectorN< CModelValue > & objects = (*CCopasiRootContainer::Root->getDatamodelList())[0]->getModel()->getModelValues();
  C_INT32 j, jmax = objects.size();
  CModelValue *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      parent->addChild(-1,
                        FROM_UTF8(obj->getObjectName()),
                        obj->getKey());
    }
}

void DataModelGUI::updateFunctions()
{
  IndexedNode * parent = mTree.findNodeFromId(5);

  parent->removeChildren();

  assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
  const CCopasiVectorN< CEvaluationTree > & objects = CCopasiRootContainer::Root->getFunctionList()->loadedFunctions();
  C_INT32 j, jmax = objects.size();
  CFunction *obj;
  for (j = 0; j < jmax; j++)
    {
      if ((obj = dynamic_cast<CFunction *>(objects[j])))
        parent->addChild(-1,
                          FROM_UTF8(obj->getObjectName()),
                          obj->getKey());
    }
}

void DataModelGUI::updateEvents()
{
  IndexedNode * parent = mTree.findNodeFromId(116);

  parent->removeChildren();

  assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
  const CCopasiVectorN< CEvent > & objects = (*CCopasiRootContainer::Root->getDatamodelList())[0]->getModel()->getEvents();
  C_INT32 j, jmax = objects.size();
  CEvent *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      obj->compile();
      parent->addChild(-1,
                        FROM_UTF8(obj->getObjectName()),
                        obj->getKey());
    }
}

void DataModelGUI::updateReportDefinitions()
{
  IndexedNode * parent = mTree.findNodeFromId(43);

  parent->removeChildren();

  assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
  const CCopasiVector< CReportDefinition >* objects = (*CCopasiRootContainer::Root->getDatamodelList())[0]->getReportDefinitionList();
  C_INT32 j, jmax = objects->size();
  CReportDefinition *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = (*objects)[j];
      parent->addChild(-1,
                        FROM_UTF8(obj->getObjectName()),
                        obj->getKey());
    }
}

void DataModelGUI::updatePlots()
{
  IndexedNode * parent = mTree.findNodeFromId(42);

  parent->removeChildren();
  assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::Root->getDatamodelList())[0];
  assert(pDataModel != NULL);

  //  const CCopasiVector< CPlotSpecification >* objects = mPlotDefinitionList;
  C_INT32 j, jmax = pDataModel->getPlotDefinitionList()->size();
  CPlotSpecification *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = (*pDataModel->getPlotDefinitionList())[j];
      parent->addChild(-1,
                        FROM_UTF8(obj->getObjectName()),
                        obj->CCopasiParameter::getKey());
    }
}

//*****************************************************************

const IndexedNode * DataModelGUI::getRootNode() const
  {return mTree.getRoot();}

const IndexedNode * DataModelGUI::getNode(const int & id) const
  {return mTree.findNodeFromId(id);}
//  {return const_cast<IndexedTree *>(&mTree)->findNodeFromId(id);}

//*****************************************************************

bool DataModelGUI::createModel()
{
  assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
  if (!(*CCopasiRootContainer::Root->getDatamodelList())[0]->newModel(NULL, NULL)) return false;

  mOutputHandlerPlot.setOutputDefinitionVector((*CCopasiRootContainer::Root->getDatamodelList())[0]->getPlotDefinitionList());

  linkDataModelToGUI();
  return true;
}

bool DataModelGUI::loadModel(const std::string & fileName)
{
  CProgressBar* pProgressBar = new CProgressBar();

  bool success = true;

  try
    {
      assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
      success = (*CCopasiRootContainer::Root->getDatamodelList())[0]->loadModel(fileName, pProgressBar);
    }

  catch (...)
    {
      success = false;
    }

  if (success)
    {
      CCopasiRootContainer::Root->getConfiguration()->getRecentFiles().addFile(fileName);

      // getModel()->setCompileFlag();
      mOutputHandlerPlot.setOutputDefinitionVector((*CCopasiRootContainer::Root->getDatamodelList())[0]->getPlotDefinitionList());

      linkDataModelToGUI();
    }

  pdelete(pProgressBar);

  return success;
}

bool DataModelGUI::saveModel(const std::string & fileName, bool overwriteFile)
{
  CProgressBar* pProgressBar = new CProgressBar();

  bool success = true;

  try
    {
      assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
      success = (*CCopasiRootContainer::Root->getDatamodelList())[0]->saveModel(fileName, pProgressBar, overwriteFile);
    }

  catch (...)
    {
      success = false;
    }

  if (success)
    CCopasiRootContainer::Root->getConfiguration()->getRecentFiles().addFile(fileName);

  pdelete(pProgressBar);

  return true;
}

bool DataModelGUI::importSBMLFromString(const std::string & sbmlDocumentText)
{
  CProgressBar* tmpBar = new CProgressBar();
  bool success = false;
  try
    {
      assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
      success = (*CCopasiRootContainer::Root->getDatamodelList())[0]->importSBMLFromString(sbmlDocumentText, tmpBar);
    }
  catch (CCopasiException except)
    {
      pdelete(tmpBar);
      throw except;
    }

  assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
  mOutputHandlerPlot.setOutputDefinitionVector((*CCopasiRootContainer::Root->getDatamodelList())[0]->getPlotDefinitionList());

  pdelete(tmpBar);

  linkDataModelToGUI();
  return success;
}

bool DataModelGUI::importSBML(const std::string & fileName)
{
  CProgressBar* tmpBar = new CProgressBar();
  bool success = false;
  try
    {
      assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
      success = (*CCopasiRootContainer::Root->getDatamodelList())[0]->importSBML(fileName, tmpBar);
    }

  catch (CCopasiException except)
    {
      pdelete(tmpBar);
      throw except;
    }

  catch (...)
    {
      pdelete(tmpBar);
      fatalError();
    }

  if (success) CCopasiRootContainer::Root->getConfiguration()->getRecentSBMLFiles().addFile(fileName);

  assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
  mOutputHandlerPlot.setOutputDefinitionVector((*CCopasiRootContainer::Root->getDatamodelList())[0]->getPlotDefinitionList());

  pdelete(tmpBar);

  linkDataModelToGUI();
  return success;
}

std::string DataModelGUI::exportSBMLToString()
{
  CProgressBar* tmpBar = new CProgressBar();
  std::string str;
  try
    {
      assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
      str = (*CCopasiRootContainer::Root->getDatamodelList())[0]->exportSBMLToString(tmpBar, 2, 3);
    }
  catch (CCopasiException except)
    {
      pdelete(tmpBar);
      throw except;
    }

  pdelete(tmpBar);

  return str;
}

bool DataModelGUI::exportSBML(const std::string & fileName, bool overwriteFile, int sbmlLevel, int sbmlVersion, bool exportIncomplete, bool exportCOPASIMIRIAM)
{
  CProgressBar* tmpBar = new CProgressBar();
  bool success = false;
  try
    {
      assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
      success = (*CCopasiRootContainer::Root->getDatamodelList())[0]->exportSBML(fileName, overwriteFile, sbmlLevel, sbmlVersion, exportIncomplete, exportCOPASIMIRIAM, tmpBar);
    }
  catch (CCopasiException except)
    {
      pdelete(tmpBar);
      throw except;
    }

  if (success) CCopasiRootContainer::Root->getConfiguration()->getRecentSBMLFiles().addFile(fileName);

  pdelete(tmpBar);

  return success;
}

bool DataModelGUI::exportMathModel(const std::string & fileName, const std::string & filter, bool overwriteFile)
{
  CProgressBar* pProgressBar = new CProgressBar();
  assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
  bool success = (*CCopasiRootContainer::Root->getDatamodelList())[0]->exportMathModel(fileName, pProgressBar, filter, overwriteFile);

  pdelete(pProgressBar);
  return success;
}

bool DataModelGUI::updateMIRIAM(CMIRIAMResources & miriamResources)
{
  bool success = true;
  CProgressBar* pProgressBar = new CProgressBar();
  //try
  //{
  success = miriamResources.updateMIRIAMResources(pProgressBar);
  //}
  //catch (...)
  //{
  //success = false;
  //}

  pdelete(pProgressBar);
  return success;
}

//************** QApplication ***********************************************

void DataModelGUI::setQApp(QApplication* app)
{mpApp = app;}

QApplication* DataModelGUI::getQApp() const
  {return mpApp;}
