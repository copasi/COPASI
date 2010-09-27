// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/DataModelGUI.cpp,v $
//   $Revision: 1.93.2.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/09/27 17:27:47 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

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
#include "tssanalysis/CTSSATask.h"

#ifdef COPASI_TSS
#include "tss/CTSSTask.h"
#endif

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "utilities/CCopasiException.h"
#include "commandline/CConfigurationFile.h"


//*****************************************************************************

DataModelGUI::DataModelGUI(QObject* parent):
    QAbstractItemModel(parent),
    mOutputHandlerPlot()
{
  this->populateData();
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  (*CCopasiRootContainer::getDatamodelList())[0]->addInterface(&mOutputHandlerPlot);

  //mpMathModel = NULL;
  //mMathModelUpdateScheduled = false;
}

//************************************************************

void DataModelGUI::linkDataModelToGUI()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  //math model
  //pdelete(mpMathModel);
  //mpMathModel = new CMathModel();
  //mpMathModel->setModel((*CCopasiRootContainer::getDatamodelList())[0]->getModel());

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

  mTree.findNodeFromId(27)->setObjectKey((*pDataModel->getTaskList())["Time Scale Separation Analysis"]->getKey());
  mTree.findNodeFromId(26)->setObjectKey((*pDataModel->getTaskList())["Lyapunov Exponents"]->getKey());

#ifdef COPASI_NONLIN_DYN
  mTree.findNodeFromId(28)->setObjectKey((*pDataModel->getTaskList())["Cross Section"]->getKey());
#endif

  mTree.findNodeFromId(31)->setObjectKey((*pDataModel->getTaskList())["Scan"]->getKey());
  mTree.findNodeFromId(32)->setObjectKey((*pDataModel->getTaskList())["Optimization"]->getKey());
  mTree.findNodeFromId(33)->setObjectKey((*pDataModel->getTaskList())["Parameter Estimation"]->getKey());
  mTree.findNodeFromId(34)->setObjectKey((*pDataModel->getTaskList())["Sensitivities"]->getKey());

  mTree.findNodeFromId(117)->setObjectKey(pDataModel->getModel()->getKey()); //parameters

  mTree.findNodeFromId(43)->setObjectKey(pDataModel->getReportDefinitionList()->getKey());
  //mTree.findNodeFromId(42)->setObjectKey(mPlotDefinitionList.getKey());
  mTree.findNodeFromId(42)->setObjectKey(pDataModel->getPlotDefinitionList()->getKey());
}

void DataModelGUI::populateData()
{
  mTree.add(C_INVALID_INDEX, 0, "Copasi", "");
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

QVariant DataModelGUI::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (role != Qt::DisplayRole)
    return QVariant();

  IndexedNode *item = static_cast<IndexedNode*>(index.internalPointer());

  return QVariant(getNameWithObjectNo(item));
}

QString DataModelGUI::getNameWithObjectNo(const IndexedNode *node) const
{
  QString name = node->getName();
  CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  switch (node->getId())
    {
      case 5:
        name += " (" + QString::number(CCopasiRootContainer::getFunctionList()->loadedFunctions().size())
                + ")";
        break;
      case 42:
        name += " (" + QString::number((*CCopasiRootContainer::getDatamodelList())[0]->getPlotDefinitionList()->size())
                + ")";
        break;
      case 43:
        name += " (" + QString::number((*CCopasiRootContainer::getDatamodelList())[0]->getReportDefinitionList()->size())
                + ")";
        break;
      case 111:
        name += " (" + QString::number(pModel->getCompartments().size())
                + ")";
        break;
      case 112:
        name += " (" + QString::number(pModel->getMetabolites().size())
                + ")";
        break;
      case 114:
        name += " (" + QString::number(pModel->getReactions().size())
                + ")";
        break;
      case 115:
        name += " (" + QString::number(pModel->getModelValues().size())
                + ")";
        break;
      case 116:
        name += " (" + QString::number(pModel->getEvents().size())
                + ")";
        break;
    }

  return name;
}

void DataModelGUI::updateCompartments()
{
  IndexedNode * parent = mTree.findNodeFromId(111);

  parent->removeChildren();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  if ((*CCopasiRootContainer::getDatamodelList())[0]->getModel() == NULL) return;

  const CCopasiVectorN< CCompartment > & objects = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments();
  C_INT32 j, jmax = objects.size();
  CCompartment *obj;

  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      parent->addChild(C_INVALID_INDEX
// virtual
                       void CTabWidget::objectDeleted()
      {
        std::vector< CopasiWidget * >::iterator it = mPages.begin();
        std::vector< CopasiWidget * >::iterator end = mPages.end();

        for (; it != end; ++it)
          (*it)->enter(mKey);

        return true;
      }

      ,
      FROM_UTF8(obj->getObjectName()),
      obj->getKey());
    }
}

void DataModelGUI::updateMetabolites()
{
  IndexedNode * parent = mTree.findNodeFromId(112);

  parent->removeChildren();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  const CCopasiVector< CMetab > & objects = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getMetabolites();
  C_INT32 j, jmax = objects.size();
  CMetab *metab;

  for (j = 0; j < jmax; j++)
    {
      metab = objects[j];
      parent->addChild(C_INVALID_INDEX
// virtual
                       void CTabWidget::objectDeleted()
      {
        std::vector< CopasiWidget * >::iterator it = mPages.begin();
        std::vector< CopasiWidget * >::iterator end = mPages.end();

        for (; it != end; ++it)
          (*it)->enter(mKey);

        return true;
      }

      ,
      FROM_UTF8(CMetabNameInterface::getDisplayName((*CCopasiRootContainer::getDatamodelList())[0]->getModel(), *metab)),
      metab->getKey());
    }
}

void DataModelGUI::updateReactions()
{
  IndexedNode * parent = mTree.findNodeFromId(114);

  parent->removeChildren();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  const CCopasiVectorN< CReaction > & objects = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getReactions();
  C_INT32 j, jmax = objects.size();
  CReaction *obj;

  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      obj->compile();
      parent->addChild(C_INVALID_INDEX
// virtual
                       void CTabWidget::objectDeleted()
      {
        std::vector< CopasiWidget * >::iterator it = mPages.begin();
        std::vector< CopasiWidget * >::iterator end = mPages.end();

        for (; it != end; ++it)
          (*it)->enter(mKey);

        return true;
      }

      ,
      FROM_UTF8(obj->getObjectName()),
      obj->getKey());
    }
}

void DataModelGUI::updateModelValues()
{
  IndexedNode * parent = mTree.findNodeFromId(115);

  parent->removeChildren();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  const CCopasiVectorN< CModelValue > & objects = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getModelValues();
  C_INT32 j, jmax = objects.size();
  CModelValue *obj;

  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      parent->addChild(C_INVALID_INDEX
// virtual
                       void CTabWidget::objectDeleted()
      {
        std::vector< CopasiWidget * >::iterator it = mPages.begin();
        std::vector< CopasiWidget * >::iterator end = mPages.end();

        for (; it != end; ++it)
          (*it)->enter(mKey);

        return true;
      }

      ,
      FROM_UTF8(obj->getObjectName()),
      obj->getKey());
    }
}

void DataModelGUI::updateFunctions()
{
  IndexedNode * parent = mTree.findNodeFromId(5);

  parent->removeChildren();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  const CCopasiVectorN< CEvaluationTree > & objects = CCopasiRootContainer::getFunctionList()->loadedFunctions();
  C_INT32 j, jmax = objects.size();
  CFunction *obj;

  for (j = 0; j < jmax; j++)
    {
      if ((obj = dynamic_cast<CFunction *>(objects[j])))
        parent->addChild(C_INVALID_INDEX
// virtual
                         void CTabWidget::objectDeleted()
        {
          std::vector< CopasiWidget * >::iterator it = mPages.begin();
          std::vector< CopasiWidget * >::iterator end = mPages.end();

          for (; it != end; ++it)
            (*it)->enter(mKey);

          return true;
        }

      ,
      FROM_UTF8(obj->getObjectName()),
      obj->getKey());
    }
}

void DataModelGUI::updateEvents()
{
  IndexedNode * parent = mTree.findNodeFromId(116);

  parent->removeChildren();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  const CCopasiVectorN< CEvent > & objects =
    (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getEvents();

  C_INT32 j, jmax = objects.size();
  CEvent *obj;

  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      parent->addChild(C_INVALID_INDEX
// virtual
                       void CTabWidget::objectDeleted()
      {
        std::vector< CopasiWidget * >::iterator it = mPages.begin();
        std::vector< CopasiWidget * >::iterator end = mPages.end();

        for (; it != end; ++it)
          (*it)->enter(mKey);

        return true;
      }

      ,
      FROM_UTF8(obj->getObjectName()),
      obj->getKey());
    }
}

void DataModelGUI::updateReportDefinitions()
{
  IndexedNode * parent = mTree.findNodeFromId(43);

  parent->removeChildren();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  const CCopasiVector< CReportDefinition >* objects = (*CCopasiRootContainer::getDatamodelList())[0]->getReportDefinitionList();
  C_INT32 j, jmax = objects->size();
  CReportDefinition *obj;

  for (j = 0; j < jmax; j++)
    {
      obj = (*objects)[j];
      parent->addChild(C_INVALID_INDEX
// virtual
                       void CTabWidget::objectDeleted()
      {
        std::vector< CopasiWidget * >::iterator it = mPages.begin();
        std::vector< CopasiWidget * >::iterator end = mPages.end();

        for (; it != end; ++it)
          (*it)->enter(mKey);

        return true;
      }

      ,
      FROM_UTF8(obj->getObjectName()),
      obj->getKey());
    }
}

void DataModelGUI::updatePlots()
{
  IndexedNode * parent = mTree.findNodeFromId(42);

  parent->removeChildren();
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  //  const CCopasiVector< CPlotSpecification >* objects = mPlotDefinitionList;
  C_INT32 j, jmax = pDataModel->getPlotDefinitionList()->size();
  CPlotSpecification *obj;

  for (j = 0; j < jmax; j++)
    {
      obj = (*pDataModel->getPlotDefinitionList())[j];
      parent->addChild(C_INVALID_INDEX
// virtual
                       void CTabWidget::objectDeleted()
      {
        std::vector< CopasiWidget * >::iterator it = mPages.begin();
        std::vector< CopasiWidget * >::iterator end = mPages.end();

        for (; it != end; ++it)
          (*it)->enter(mKey);

        return true;
      }

      ,
      FROM_UTF8(obj->getObjectName()),
      obj->CCopasiParameter::getKey());
    }

}

//*****************************************************************

const IndexedNode * DataModelGUI::getRootNode() const
{return mTree.getRoot();}

const IndexedNode * DataModelGUI::getNode(int id)
{return mTree.findNodeFromId(id);}
//  {return const_cast<IndexedTree *>(&mTree)->findNodeFromId(id);}

//*****************************************************************
#ifdef WITH_MERGEMODEL

bool DataModelGUI::addModel(const std::string & fileName)
{
  CProgressBar* pProgressBar = new CProgressBar();

  bool success = true;

  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      success = CCopasiRootContainer::addDatamodel()->loadModel(fileName, pProgressBar);
    }

  catch (...)
    {
      success = false;
    }

  if (success)
    {
      CCopasiRootContainer::getConfiguration()->getRecentFiles().addFile(fileName);
    }

  pdelete(pProgressBar);

  return success;
}

#endif

bool DataModelGUI::createModel()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  if (!(*CCopasiRootContainer::getDatamodelList())[0]->newModel(NULL, NULL)) return false;

  mOutputHandlerPlot.setOutputDefinitionVector((*CCopasiRootContainer::getDatamodelList())[0]->getPlotDefinitionList());

  linkDataModelToGUI();
  return true;
}

bool DataModelGUI::loadModel(const std::string & fileName)
{
  CProgressBar* pProgressBar = new CProgressBar();

  bool success = true;

  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      success = (*CCopasiRootContainer::getDatamodelList())[0]->loadModel(fileName, pProgressBar);
    }

  catch (...)
    {
      success = false;
    }

  if (success)
    {
      CCopasiRootContainer::getConfiguration()->getRecentFiles().addFile(fileName);

      // getModel()->setCompileFlag();
      mOutputHandlerPlot.setOutputDefinitionVector((*CCopasiRootContainer::getDatamodelList())[0]->getPlotDefinitionList());

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
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      success = (*CCopasiRootContainer::getDatamodelList())[0]->saveModel(fileName, pProgressBar, overwriteFile);
    }

  catch (...)
    {
      success = false;
    }

  if (success)
    CCopasiRootContainer::getConfiguration()->getRecentFiles().addFile(fileName);

  pdelete(pProgressBar);

  return true;
}

bool DataModelGUI::importSBMLFromString(const std::string & sbmlDocumentText)
{
  CProgressBar* tmpBar = new CProgressBar();
  bool success = false;

  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      success = (*CCopasiRootContainer::getDatamodelList())[0]->importSBMLFromString(sbmlDocumentText, tmpBar);
    }
  catch (CCopasiException except)
    {
      pdelete(tmpBar);
      throw except;
    }

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  mOutputHandlerPlot.setOutputDefinitionVector((*CCopasiRootContainer::getDatamodelList())[0]->getPlotDefinitionList());

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
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      success = (*CCopasiRootContainer::getDatamodelList())[0]->importSBML(fileName, tmpBar);
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

  if (success) CCopasiRootContainer::getConfiguration()->getRecentSBMLFiles().addFile(fileName);

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  mOutputHandlerPlot.setOutputDefinitionVector((*CCopasiRootContainer::getDatamodelList())[0]->getPlotDefinitionList());

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
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      str = (*CCopasiRootContainer::getDatamodelList())[0]->exportSBMLToString(tmpBar, 2, 3);
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
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      success = (*CCopasiRootContainer::getDatamodelList())[0]->exportSBML(fileName, overwriteFile, sbmlLevel, sbmlVersion, exportIncomplete, exportCOPASIMIRIAM, tmpBar);
    }
  catch (CCopasiException except)
    {
      pdelete(tmpBar);
      throw except;
    }

  if (success) CCopasiRootContainer::getConfiguration()->getRecentSBMLFiles().addFile(fileName);

  pdelete(tmpBar);

  return success;
}

bool DataModelGUI::exportMathModel(const std::string & fileName, const std::string & filter, bool overwriteFile)
{
  CProgressBar* pProgressBar = new CProgressBar();
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  bool success = (*CCopasiRootContainer::getDatamodelList())[0]->exportMathModel(fileName, pProgressBar, filter, overwriteFile);

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

//************Model-View Architecture*****************************************

int DataModelGUI::rowCount(const QModelIndex &parent) const
{
  const IndexedNode *parentItem;

  if (parent.column() > 0)
    return 0;

  if (!parent.isValid())
    parentItem = getRootNode();
  else
    parentItem = static_cast<IndexedNode*>(parent.internalPointer());

  return parentItem->childCount();
}

int DataModelGUI::columnCount(const QModelIndex &parent) const
{
  if (parent.isValid())
    return static_cast<IndexedNode*>(parent.internalPointer())->columnCount();
  else
    return getRootNode()->columnCount();
}

Qt::ItemFlags DataModelGUI::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return 0;

  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant DataModelGUI::headerData(int C_UNUSED(section), Qt::Orientation orientation,
                                  int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return QVariant(getRootNode()->getName());

  return QVariant();
}

QModelIndex DataModelGUI::index(int row, int column, const QModelIndex &parent)
const
{
  if (!hasIndex(row, column, parent))
    return QModelIndex();

  IndexedNode *parentItem;

  if (!parent.isValid())
    parentItem = const_cast<IndexedNode*>(getRootNode());
  else
    parentItem = static_cast<IndexedNode*>(parent.internalPointer());

  IndexedNode *childItem = parentItem->child(row);

  if (childItem)
    return createIndex(row, column, childItem);
  else
    return QModelIndex();
}

QModelIndex DataModelGUI::parent(const QModelIndex &index) const
{
  if (!index.isValid())
    return QModelIndex();

  IndexedNode *childItem = static_cast<IndexedNode*>(index.internalPointer());
  const IndexedNode * parentItem = childItem->parent();

  if (parentItem == getRootNode())
    return QModelIndex();

  return createIndex(parentItem->row(), parentItem->column(),
                     const_cast< IndexedNode * >(parentItem));
}

QModelIndex DataModelGUI::findIndexFromId(int id)
{
  QModelIndex index;
  IndexedNode * pNode = mTree.findNodeFromId(id);

  if (pNode == getRootNode())
    return index;

  if (pNode)
    index = createIndex(pNode->row(), pNode->column(), pNode);

  return index;
}

QModelIndex DataModelGUI::findIndexFromKey(const std::string& key)
{
  QModelIndex index;
  IndexedNode * pNode = mTree.findNodeFromKey(key);

  if (pNode == getRootNode())
    return index;

  if (pNode)
    index = createIndex(pNode->row(), pNode->column(), pNode);

  return index;
}

void DataModelGUI::updateAllEntities()
{
  updateCompartments();

  updateMetabolites();

  updateReactions();

  updateModelValues();

  updateEvents();

  updateFunctions();

  updateReportDefinitions();

  updatePlots();

  emit updateCompleteView();
}

bool DataModelGUI::notify(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  if (key == "")
    {
      //just update everything if no key given.
      updateAllEntities();
      emit notifyView(objectType, action, key);
      return true;
    }

  if (action == ListViews::RENAME || action == ListViews::CHANGE)
    {
      if (objectType == ListViews::MODEL)
        {
          assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
          CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
          assert(pDataModel != NULL);

          pDataModel->changed();
        }
      else
        changeRow(key);
    }
  else if (action == ListViews::DELETE)
    {
      if (objectType == ListViews::MODEL)
        {
          updateAllEntities();
          emit notifyView(objectType, action, key);
          return true;
        }
      else
        removeRow(key);
    }
  else if (action == ListViews::ADD)
    {

      switch (objectType)
        {
          case ListViews::MODEL:
            updateAllEntities();
            emit notifyView(objectType, action, key);
            return true;
            break;
          case ListViews::COMPARTMENT:
            insertRow(111, key);
            break;
          case ListViews::METABOLITE:
            insertRow(112, key);
            break;
          case ListViews::REACTION:
            insertRow(114, key);
            break;
          case ListViews::MODELVALUE:
            insertRow(115, key);
            break;
          case ListViews::EVENT:
            insertRow(116, key);
            break;
          case ListViews::PLOT:
            insertRow(42, key);
            break;
          case ListViews::REPORT:
            insertRow(43, key);
            break;
          case ListViews::FUNCTION:
            insertRow(5, key);
            break;
        }
    }

  emit notifyView(objectType, action, key);
  return true;
}

bool DataModelGUI::insertRow(int parentId, const std::string &key)
{
  IndexedNode *parentNode = mTree.findNodeFromId(parentId);

  if (!parentNode)
    return false;

  QModelIndex parentIndex = findIndexFromId(parentId);

  beginInsertRows(parentIndex, parentNode->childCount(), parentNode->childCount());
  std::string objName = CCopasiRootContainer::getKeyFactory()->get(key)->getObjectName();
  parentNode->addChild(C_INVALID_INDEX
// virtual
                       void CTabWidget::objectDeleted()
  {
    std::vector< CopasiWidget * >::iterator it = mPages.begin();
    std::vector< CopasiWidget * >::iterator end = mPages.end();

    for (; it != end; ++it)
      (*it)->enter(mKey);

    return true;
  }

  , FROM_UTF8(objName), key);

  endInsertRows();

  emit dataChanged(parentIndex, parentIndex);

  return true;
}

bool DataModelGUI::removeRow(const std::string &key)
{
  IndexedNode *pNode = mTree.findNodeFromKey(key);

  if (!pNode || !pNode->parent())
    return false;


  QModelIndex parentIndex = findIndexFromId(pNode->parent()->getId());

  beginRemoveRows(parentIndex, pNode->row(), pNode->row());
  const_cast< IndexedNode * >(pNode->parent())->removeChild(key);
  endRemoveRows();

  emit dataChanged(parentIndex, parentIndex);

  return true;
}

void DataModelGUI::changeRow(const std::string &key)
{
  IndexedNode *node = mTree.findNodeFromKey(key);

  if (!node)
    return;

  std::string objName = CCopasiRootContainer::getKeyFactory()->get(key)->getObjectName();
  node->setName(FROM_UTF8(objName));
  QModelIndex index = findIndexFromKey(key);
  emit dataChanged(index, index);
}
