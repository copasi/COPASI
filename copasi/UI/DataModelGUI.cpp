// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/DataModelGUI.cpp,v $
//   $Revision: 1.93.2.22 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/02/07 15:39:45 $
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
#include "CQThread.h"
#include "qtUtilities.h"
#include "utilities/CVector.h"
#include "CProgressBar.h"
#include "listviews.h"
#include "CQMessageBox.h"

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
    mTree(),
    mpApp(NULL),
    mOutputHandlerPlot(),
    mListViews(),
    mFramework(0),
    mUpdateVector(),
    mChangedObjects(),
    mpThread(NULL),
    mpProgressBar(NULL),
    mSuccess(false),
    mSBMLImportString(),
    mpSBMLExportString(NULL),
    mFileName(),
    mOverWrite(false),
    mSBMLLevel(2),
    mSBMLVersion(4),
    mSBMLExportIncomplete(true),
    mSBMLExportCOPASIMIRIAM(true),
    mExportFormat()
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
  mTree.add(C_INVALID_INDEX, 0, "COPASI", "");
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

  IndexedNode *item = getItem(index);

  return QVariant(getNameWithObjectNo(item));
}

size_t DataModelGUI::getId(const QModelIndex &index) const
{
  if (!index.isValid())
    return -1;

  IndexedNode *node = getItem(index);

  return node->getId();
}

std::string DataModelGUI::getKey(const QModelIndex &index) const
{
  if (!index.isValid())
    return "";

  IndexedNode *node = getItem(index);

  return node->getObjectKey();
}


QString DataModelGUI::getNameWithObjectNo(const IndexedNode *node) const
{
  QString name = node->getName();
  CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();
  size_t noOfObjects = C_INVALID_INDEX;

  switch (node->getId())
    {
      case 5:
        noOfObjects = CCopasiRootContainer::getFunctionList()->loadedFunctions().size();
        break;
      case 42:
        noOfObjects = (*CCopasiRootContainer::getDatamodelList())[0]->getPlotDefinitionList()->size();
        break;
      case 43:
        noOfObjects = (*CCopasiRootContainer::getDatamodelList())[0]->getReportDefinitionList()->size();
        break;
      case 111:
        noOfObjects = pModel->getCompartments().size();
        break;
      case 112:
        noOfObjects = pModel->getMetabolites().size();
        break;
      case 114:
        noOfObjects = pModel->getReactions().size();
        break;
      case 115:
        noOfObjects = pModel->getModelValues().size();
        break;
      case 116:
        noOfObjects = pModel->getEvents().size();
        break;
    }

  if (noOfObjects != C_INVALID_INDEX)
    name += " (" + QString::number(noOfObjects) + ")";

  return name;
}

void DataModelGUI::updateCompartments()
{
  IndexedNode * parent = mTree.findNodeFromId(111);

  parent->removeChildren();

  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL) return;

  CCopasiVector< CCompartment >::iterator it = pModel->getCompartments().begin();
  CCopasiVector< CCompartment >::iterator end = pModel->getCompartments().end();

  QMap< QString, QMap< QString, CCopasiObject * > > Sorted;

  for (; it != end; ++it)
    {
      QMap< QString, CCopasiObject * > Insert;
      QString DisplayName = FROM_UTF8((*it)->getObjectName());

      QMap< QString, QMap< QString, CCopasiObject * > >::iterator found =
        Sorted.find(DisplayName.toLower());

      if (found != Sorted.end())
        {
          Insert = found.value();
        }

      Insert[DisplayName] = *it;
      Sorted[DisplayName.toLower()] = Insert;
    }

  QMap< QString, QMap< QString, CCopasiObject * > >::iterator itSorted = Sorted.begin();
  QMap< QString, QMap< QString, CCopasiObject * > >::iterator endSorted = Sorted.end();

  for (; itSorted != endSorted; ++itSorted)
    {
      QMap< QString, CCopasiObject * >::iterator itCase = itSorted.value().begin();
      QMap< QString, CCopasiObject * >::iterator endCase = itSorted.value().end();

      for (; itCase != endCase; ++itCase)
        {
          parent->addChild(C_INVALID_INDEX, itCase.key(), itCase.value()->getKey());
        }
    }
}

void DataModelGUI::updateMetabolites()
{
  IndexedNode * parent = mTree.findNodeFromId(112);

  parent->removeChildren();

  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL) return;

  CCopasiVector< CMetab >::iterator it = pModel->getMetabolites().begin();
  CCopasiVector< CMetab >::iterator end = pModel->getMetabolites().end();

  QMap< QString, QMap< QString, CCopasiObject * > > Sorted;

  for (; it != end; ++it)
    {
      QMap< QString, CCopasiObject * > Insert;
      QString DisplayName = FROM_UTF8(CMetabNameInterface::getDisplayName(pModel, **it));

      QMap< QString, QMap< QString, CCopasiObject * > >::iterator found =
        Sorted.find(DisplayName.toLower());

      if (found != Sorted.end())
        {
          Insert = found.value();
        }

      Insert[DisplayName] = *it;
      Sorted[DisplayName.toLower()] = Insert;
    }

  QMap< QString, QMap< QString, CCopasiObject * > >::iterator itSorted = Sorted.begin();
  QMap< QString, QMap< QString, CCopasiObject * > >::iterator endSorted = Sorted.end();

  for (; itSorted != endSorted; ++itSorted)
    {
      QMap< QString, CCopasiObject * >::iterator itCase = itSorted.value().begin();
      QMap< QString, CCopasiObject * >::iterator endCase = itSorted.value().end();

      for (; itCase != endCase; ++itCase)
        {
          parent->addChild(C_INVALID_INDEX, itCase.key(), itCase.value()->getKey());
        }
    }
}

void DataModelGUI::updateReactions()
{
  IndexedNode * parent = mTree.findNodeFromId(114);

  parent->removeChildren();

  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL) return;

  CCopasiVector< CReaction >::iterator it = pModel->getReactions().begin();
  CCopasiVector< CReaction >::iterator end = pModel->getReactions().end();

  QMap< QString, QMap< QString, CCopasiObject * > > Sorted;

  for (; it != end; ++it)
    {
      QMap< QString, CCopasiObject * > Insert;
      QString DisplayName = FROM_UTF8((*it)->getObjectName());

      QMap< QString, QMap< QString, CCopasiObject * > >::iterator found =
        Sorted.find(DisplayName.toLower());

      if (found != Sorted.end())
        {
          Insert = found.value();
        }

      Insert[DisplayName] = *it;
      Sorted[DisplayName.toLower()] = Insert;
    }

  QMap< QString, QMap< QString, CCopasiObject * > >::iterator itSorted = Sorted.begin();
  QMap< QString, QMap< QString, CCopasiObject * > >::iterator endSorted = Sorted.end();

  for (; itSorted != endSorted; ++itSorted)
    {
      QMap< QString, CCopasiObject * >::iterator itCase = itSorted.value().begin();
      QMap< QString, CCopasiObject * >::iterator endCase = itSorted.value().end();

      for (; itCase != endCase; ++itCase)
        {
          parent->addChild(C_INVALID_INDEX, itCase.key(), itCase.value()->getKey());
        }
    }
}

void DataModelGUI::updateModelValues()
{
  IndexedNode * parent = mTree.findNodeFromId(115);

  parent->removeChildren();

  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL) return;

  CCopasiVector< CModelValue >::iterator it = pModel->getModelValues().begin();
  CCopasiVector< CModelValue >::iterator end = pModel->getModelValues().end();

  QMap< QString, QMap< QString, CCopasiObject * > > Sorted;

  for (; it != end; ++it)
    {
      QMap< QString, CCopasiObject * > Insert;
      QString DisplayName = FROM_UTF8((*it)->getObjectName());

      QMap< QString, QMap< QString, CCopasiObject * > >::iterator found =
        Sorted.find(DisplayName.toLower());

      if (found != Sorted.end())
        {
          Insert = found.value();
        }

      Insert[DisplayName] = *it;
      Sorted[DisplayName.toLower()] = Insert;
    }

  QMap< QString, QMap< QString, CCopasiObject * > >::iterator itSorted = Sorted.begin();
  QMap< QString, QMap< QString, CCopasiObject * > >::iterator endSorted = Sorted.end();

  for (; itSorted != endSorted; ++itSorted)
    {
      QMap< QString, CCopasiObject * >::iterator itCase = itSorted.value().begin();
      QMap< QString, CCopasiObject * >::iterator endCase = itSorted.value().end();

      for (; itCase != endCase; ++itCase)
        {
          parent->addChild(C_INVALID_INDEX, itCase.key(), itCase.value()->getKey());
        }
    }
}

void DataModelGUI::updateFunctions()
{
  IndexedNode * parent = mTree.findNodeFromId(5);

  parent->removeChildren();

  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CCopasiVector< CFunction >::iterator it = CCopasiRootContainer::getFunctionList()->loadedFunctions().begin();
  CCopasiVector< CFunction >::iterator end = CCopasiRootContainer::getFunctionList()->loadedFunctions().end();

  QMap< QString, QMap< QString, CCopasiObject * > > Sorted;

  for (; it != end; ++it)
    {
      QMap< QString, CCopasiObject * > Insert;
      QString DisplayName = FROM_UTF8((*it)->getObjectName());

      QMap< QString, QMap< QString, CCopasiObject * > >::iterator found =
        Sorted.find(DisplayName.toLower());

      if (found != Sorted.end())
        {
          Insert = found.value();
        }

      Insert[DisplayName] = *it;
      Sorted[DisplayName.toLower()] = Insert;
    }

  QMap< QString, QMap< QString, CCopasiObject * > >::iterator itSorted = Sorted.begin();
  QMap< QString, QMap< QString, CCopasiObject * > >::iterator endSorted = Sorted.end();

  for (; itSorted != endSorted; ++itSorted)
    {
      QMap< QString, CCopasiObject * >::iterator itCase = itSorted.value().begin();
      QMap< QString, CCopasiObject * >::iterator endCase = itSorted.value().end();

      for (; itCase != endCase; ++itCase)
        {
          parent->addChild(C_INVALID_INDEX, itCase.key(), itCase.value()->getKey());
        }
    }
}

void DataModelGUI::updateEvents()
{
  IndexedNode * parent = mTree.findNodeFromId(116);

  parent->removeChildren();

  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL) return;

  CCopasiVector< CEvent >::iterator it = pModel->getEvents().begin();
  CCopasiVector< CEvent >::iterator end = pModel->getEvents().end();

  QMap< QString, QMap< QString, CCopasiObject * > > Sorted;

  for (; it != end; ++it)
    {
      QMap< QString, CCopasiObject * > Insert;
      QString DisplayName = FROM_UTF8((*it)->getObjectName());

      QMap< QString, QMap< QString, CCopasiObject * > >::iterator found =
        Sorted.find(DisplayName.toLower());

      if (found != Sorted.end())
        {
          Insert = found.value();
        }

      Insert[DisplayName] = *it;
      Sorted[DisplayName.toLower()] = Insert;
    }

  QMap< QString, QMap< QString, CCopasiObject * > >::iterator itSorted = Sorted.begin();
  QMap< QString, QMap< QString, CCopasiObject * > >::iterator endSorted = Sorted.end();

  for (; itSorted != endSorted; ++itSorted)
    {
      QMap< QString, CCopasiObject * >::iterator itCase = itSorted.value().begin();
      QMap< QString, CCopasiObject * >::iterator endCase = itSorted.value().end();

      for (; itCase != endCase; ++itCase)
        {
          parent->addChild(C_INVALID_INDEX, itCase.key(), itCase.value()->getKey());
        }
    }
}

void DataModelGUI::updateReportDefinitions()
{
  IndexedNode * parent = mTree.findNodeFromId(43);

  parent->removeChildren();

  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CCopasiVector< CReportDefinition >::iterator it = pDataModel->getReportDefinitionList()->begin();
  CCopasiVector< CReportDefinition >::iterator end = pDataModel->getReportDefinitionList()->end();

  QMap< QString, QMap< QString, CCopasiObject * > > Sorted;

  for (; it != end; ++it)
    {
      QMap< QString, CCopasiObject * > Insert;
      QString DisplayName = FROM_UTF8((*it)->getObjectName());

      QMap< QString, QMap< QString, CCopasiObject * > >::iterator found =
        Sorted.find(DisplayName.toLower());

      if (found != Sorted.end())
        {
          Insert = found.value();
        }

      Insert[DisplayName] = *it;
      Sorted[DisplayName.toLower()] = Insert;
    }

  QMap< QString, QMap< QString, CCopasiObject * > >::iterator itSorted = Sorted.begin();
  QMap< QString, QMap< QString, CCopasiObject * > >::iterator endSorted = Sorted.end();

  for (; itSorted != endSorted; ++itSorted)
    {
      QMap< QString, CCopasiObject * >::iterator itCase = itSorted.value().begin();
      QMap< QString, CCopasiObject * >::iterator endCase = itSorted.value().end();

      for (; itCase != endCase; ++itCase)
        {
          parent->addChild(C_INVALID_INDEX, itCase.key(), itCase.value()->getKey());
        }
    }
}

void DataModelGUI::updatePlots()
{
  IndexedNode * parent = mTree.findNodeFromId(42);

  parent->removeChildren();

  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CCopasiVector< CPlotSpecification >::iterator it = pDataModel->getPlotDefinitionList()->begin();
  CCopasiVector< CPlotSpecification >::iterator end = pDataModel->getPlotDefinitionList()->end();

  QMap< QString, QMap< QString, CCopasiObject * > > Sorted;

  for (; it != end; ++it)
    {
      QMap< QString, CCopasiObject * > Insert;
      QString DisplayName = FROM_UTF8((*it)->getObjectName());

      QMap< QString, QMap< QString, CCopasiObject * > >::iterator found =
        Sorted.find(DisplayName.toLower());

      if (found != Sorted.end())
        {
          Insert = found.value();
        }

      Insert[DisplayName] = *it;
      Sorted[DisplayName.toLower()] = Insert;
    }

  QMap< QString, QMap< QString, CCopasiObject * > >::iterator itSorted = Sorted.begin();
  QMap< QString, QMap< QString, CCopasiObject * > >::iterator endSorted = Sorted.end();

  for (; itSorted != endSorted; ++itSorted)
    {
      QMap< QString, CCopasiObject * >::iterator itCase = itSorted.value().begin();
      QMap< QString, CCopasiObject * >::iterator endCase = itSorted.value().end();

      for (; itCase != endCase; ++itCase)
        {
          parent->addChild(C_INVALID_INDEX, itCase.key(), itCase.value()->getKey());
        }
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

void DataModelGUI::loadModel(const std::string & fileName)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mFileName = fileName;

  mpThread = new CQThread(this, &DataModelGUI::loadModelRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(loadModelFinished()));
  mpThread->start();
}

void DataModelGUI::loadModelRun()
{
  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      mSuccess = (*CCopasiRootContainer::getDatamodelList())[0]->loadModel(mFileName, mpProgressBar);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::loadModelFinished()
{
  if (mSuccess)
    {
      CCopasiRootContainer::getConfiguration()->getRecentFiles().addFile(mFileName);

      mOutputHandlerPlot.setOutputDefinitionVector((*CCopasiRootContainer::getDatamodelList())[0]->getPlotDefinitionList());
      linkDataModelToGUI();
    }

  disconnect(mpThread, SIGNAL(finished()), this, SLOT(loadModelFinished()));

  threadFinished();
}


void DataModelGUI::saveModel(const std::string & fileName, bool overwriteFile)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mFileName = fileName;
  mOverWrite = overwriteFile;

  mpThread = new CQThread(this, &DataModelGUI::saveModelRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(saveModelFinished()));
  mpThread->start();
}

void DataModelGUI::saveModelRun()
{
  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      mSuccess = (*CCopasiRootContainer::getDatamodelList())[0]->saveModel(mFileName, mpProgressBar, mOverWrite);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::saveModelFinished()
{
  if (mSuccess)
    CCopasiRootContainer::getConfiguration()->getRecentFiles().addFile(mFileName);

  disconnect(mpThread, SIGNAL(finished()), this, SLOT(saveModelFinished()));

  threadFinished();
}


void DataModelGUI::importSBMLFromString(const std::string & sbmlDocumentText)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mSBMLImportString = sbmlDocumentText;

  mpThread = new CQThread(this, &DataModelGUI::importSBMLFromStringRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(importSBMLFromStringFinished()));
  mpThread->start();
}

void DataModelGUI::importSBMLFromStringRun()
{
  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      mSuccess = (*CCopasiRootContainer::getDatamodelList())[0]->importSBMLFromString(mSBMLImportString, mpProgressBar);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::importSBMLFromStringFinished()
{
  mSBMLImportString = "";

  if (mSuccess)
    {
      mOutputHandlerPlot.setOutputDefinitionVector((*CCopasiRootContainer::getDatamodelList())[0]->getPlotDefinitionList());
      linkDataModelToGUI();
    }

  disconnect(mpThread, SIGNAL(finished()), this, SLOT(importSBMLFromStringFinished()));

  threadFinished();
}

void DataModelGUI::importSBML(const std::string & fileName)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mFileName = fileName;

  mpThread = new CQThread(this, &DataModelGUI::importSBMLRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(importSBMLFinished()));
  mpThread->start();
}

void DataModelGUI::importSBMLRun()
{
  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      mSuccess = (*CCopasiRootContainer::getDatamodelList())[0]->importSBML(mFileName, mpProgressBar);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::importSBMLFinished()
{
  if (mSuccess)
    {
      CCopasiRootContainer::getConfiguration()->getRecentSBMLFiles().addFile(mFileName);

      mOutputHandlerPlot.setOutputDefinitionVector((*CCopasiRootContainer::getDatamodelList())[0]->getPlotDefinitionList());
      linkDataModelToGUI();
    }

  disconnect(mpThread, SIGNAL(finished()), this, SLOT(importSBMLFinished()));

  threadFinished();
}


void DataModelGUI::exportSBMLToString(std::string & sbmlDocumentText)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mpSBMLExportString = & sbmlDocumentText;

  mpThread = new CQThread(this, &DataModelGUI::exportSBMLToStringRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(exportSBMLToStringFinished()));
  mpThread->start();
}

void DataModelGUI::exportSBMLToStringRun()
{
  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      *mpSBMLExportString = (*CCopasiRootContainer::getDatamodelList())[0]->exportSBMLToString(mpProgressBar, 2, 3);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::exportSBMLToStringFinished()
{
  disconnect(mpThread, SIGNAL(finished()), this, SLOT(exportSBMLToStringFinished()));

  threadFinished();
}

void DataModelGUI::threadFinished()
{
  if (mpThread != NULL)
    {
      mpThread->deleteLater();
      mpThread = NULL;
    }

  if (mpProgressBar != NULL)
    {
      mpProgressBar->finish();
      mpProgressBar->deleteLater();
      mpProgressBar = NULL;
    }

  emit finished(mSuccess);
}

void DataModelGUI::exportSBML(const std::string & fileName, bool overwriteFile, int sbmlLevel, int sbmlVersion, bool exportIncomplete, bool exportCOPASIMIRIAM)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mFileName = fileName;
  mOverWrite = overwriteFile;
  mSBMLLevel = sbmlLevel;
  mSBMLVersion = sbmlVersion;
  mSBMLExportIncomplete = exportIncomplete;
  mSBMLExportCOPASIMIRIAM = exportCOPASIMIRIAM;

  mpThread = new CQThread(this, &DataModelGUI::exportSBMLRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(exportSBMLFinished()));
  mpThread->start();
}

void DataModelGUI::exportSBMLRun()
{
  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      mSuccess = (*CCopasiRootContainer::getDatamodelList())[0]->exportSBML(mFileName, mOverWrite, mSBMLLevel, mSBMLVersion, mSBMLExportIncomplete, mSBMLExportCOPASIMIRIAM, mpProgressBar);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::exportSBMLFinished()
{
  if (mSuccess)
    CCopasiRootContainer::getConfiguration()->getRecentSBMLFiles().addFile(mFileName);

  disconnect(mpThread, SIGNAL(finished()), this, SLOT(exportSBMLFinished()));

  threadFinished();
}

void DataModelGUI::exportMathModel(const std::string & fileName, const std::string & filter, bool overwriteFile)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mFileName = fileName;
  mOverWrite = overwriteFile;
  mExportFormat = filter;

  mpThread = new CQThread(this, &DataModelGUI::exportMathModelRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(exportMathModelFinished()));
  mpThread->start();
}

void DataModelGUI::exportMathModelRun()
{
  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      mSuccess = (*CCopasiRootContainer::getDatamodelList())[0]->exportMathModel(mFileName, mpProgressBar, mExportFormat, mOverWrite);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::exportMathModelFinished()
{
  disconnect(mpThread, SIGNAL(finished()), this, SLOT(exportMathModelFinished()));

}

bool DataModelGUI::updateMIRIAM(CMIRIAMResources & miriamResources)
{
  bool success = true;
  CProgressBar* pProgressBar = CProgressBar::create();
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
  if (parent.column() > 0)
    return 0;

  const IndexedNode *parentItem = getItem(parent);

  return (int) parentItem->childCount();
}

int DataModelGUI::columnCount(const QModelIndex &C_UNUSED(parent)) const
{
  return (int) getRootNode()->columnCount();
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

QModelIndex DataModelGUI::index(int row, int column, const QModelIndex &parent) const
{
  if (!hasIndex(row, column, parent))
    return QModelIndex();

  IndexedNode * parentItem = getItem(parent);
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

  IndexedNode *childItem = getItem(index);
  IndexedNode *parentItem = dynamic_cast<IndexedNode *>(const_cast<IndexedNode *>(childItem->parent()));

  if (parentItem == getRootNode() || !parentItem || !(mTree.isNodeFromTree(parentItem)))
    return QModelIndex();

  return createIndex((int) parentItem->row(), (int) parentItem->column(),
                     const_cast< IndexedNode * >(parentItem));
}

QModelIndex DataModelGUI::findIndexFromId(size_t id)
{
  QModelIndex index;
  IndexedNode * pNode = mTree.findNodeFromId(id);

  if (pNode == getRootNode())
    return index;

  if (pNode)
    index = createIndex((int) pNode->row(), (int) pNode->column(), pNode);

  return index;
}

QModelIndex DataModelGUI::findIndexFromKey(const std::string& key)
{
  QModelIndex index;
  IndexedNode * pNode = mTree.findNodeFromKey(key);

  if (pNode == getRootNode())
    return index;

  if (pNode)
    index = createIndex((int) pNode->row(), (int) pNode->column(), pNode);

  return index;
}

void DataModelGUI::updateAllEntities()
{
  // The GUI is inactive whenever a progress bar exist. We wait with updates
  // until then.
  if (mpProgressBar != NULL) return;

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
  // The GUI is inactive whenever a progress bar exist. We wait with updates
  // until then.
  if (mpProgressBar != NULL) return false;

  std::set< ListViews * >::iterator it = mListViews.begin();
  std::set< ListViews * >::iterator end = mListViews.end();

  for (; it != end; ++it)
    {
      (*it)->storeCurrentItem();
    }


  // update all initial value
  if (action != ListViews::RENAME)
    refreshInitialValues();

  if (key == "")
    {
      //just update everything if no key given.
      updateAllEntities();
      emit notifyView(objectType, action, key);
      return true;
    }

  switch (action)
    {
      case ListViews::RENAME:
      case ListViews::CHANGE:
      {
        switch (objectType)
          {
            case ListViews::MODEL:
            {
              assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
              CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
              assert(pDataModel != NULL);

              pDataModel->changed();
            }
            break;

            case ListViews::STATE:
              break;

            case ListViews::COMPARTMENT:
              updateCompartments();
              emit updateCompleteView();
              break;

            case ListViews::METABOLITE:
              updateMetabolites();
              emit updateCompleteView();
              break;

            case ListViews::REACTION:
              updateReactions();
              emit updateCompleteView();
              break;

            case ListViews::MODELVALUE:
              updateModelValues();
              emit updateCompleteView();
              break;

            case ListViews::EVENT:
              updateEvents();
              emit updateCompleteView();
              break;

            case ListViews::PLOT:
              updatePlots();
              emit updateCompleteView();
              break;

            case ListViews::REPORT:
              updateReportDefinitions();
              emit updateCompleteView();
              break;

            case ListViews::FUNCTION:
              updateFunctions();
              emit updateCompleteView();
              break;

            default:
              break;
          }
      }
      break;

      case ListViews::DELETE:
      {
        if (objectType == ListViews::MODEL)
          {
            updateAllEntities();
          }
        else
          {
            removeRow(key);
          }
      }
      break;

      case ListViews::ADD:
      {

        switch (objectType)
          {
            case ListViews::MODEL:
              updateAllEntities();
              break;

            case ListViews::COMPARTMENT:
              insertRow(111, key);
              updateCompartments();
              emit updateCompleteView();
              break;

            case ListViews::METABOLITE:
              insertRow(112, key);
              updateCompartments();
              updateMetabolites();
              emit updateCompleteView();
              break;

            case ListViews::REACTION:
              insertRow(114, key);
              updateCompartments();
              updateMetabolites();
              updateReactions();
              emit updateCompleteView();
              break;

            case ListViews::MODELVALUE:
              insertRow(115, key);
              updateModelValues();
              emit updateCompleteView();
              break;

            case ListViews::EVENT:
              insertRow(116, key);
              updateEvents();
              emit updateCompleteView();
              break;

            case ListViews::PLOT:
              insertRow(42, key);
              updatePlots();
              emit updateCompleteView();
              break;

            case ListViews::REPORT:
              insertRow(43, key);
              updateReportDefinitions();
              emit updateCompleteView();
              break;

            case ListViews::FUNCTION:
              insertRow(5, key);
              updateFunctions();
              emit updateCompleteView();
              break;

            case ListViews::LAYOUT:
            case ListViews::MIRIAM:
            case ListViews::STATE:
              break;
          }
      }
      break;
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

  beginInsertRows(parentIndex, (int) parentNode->childCount(), (int) parentNode->childCount());
  std::string objName = CCopasiRootContainer::getKeyFactory()->get(key)->getObjectName();
  parentNode->addChild(C_INVALID_INDEX, FROM_UTF8(objName), key);

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

  beginRemoveRows(parentIndex, (int) pNode->row(), (int) pNode->row());
  const_cast< IndexedNode * >(pNode->parent())->removeChild(key);
  endRemoveRows();

  emit dataChanged(parentIndex, parentIndex);

  return true;
}

IndexedNode * DataModelGUI::getItem(const QModelIndex &index) const
{
  if (index.isValid())
    {
      IndexedNode *node = static_cast<IndexedNode*>(index.internalPointer());

      if (node) return node;
    }

  return const_cast<IndexedNode*>(getRootNode());
}

void DataModelGUI::registerListView(ListViews * pListView)
{
  pListView->setDataModel(this);
  mListViews.insert(pListView);
}

void DataModelGUI::deregisterListView(ListViews * pListView)
{
  pListView->setDataModel(NULL);
  mListViews.erase(pListView);
}

void DataModelGUI::buildChangedObjects()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();
  pModel->compileIfNecessary(NULL);

  mChangedObjects.clear();

  CModelEntity ** ppEntity = pModel->getStateTemplate().getEntities();
  CModelEntity ** ppEntityEnd = pModel->getStateTemplate().endFixed();

  CMetab * pMetab;
  std::set< const CCopasiObject * > Objects;

  // The objects which are changed are all initial values of of all model entities including
  // fixed and unused once. Additionally, all kinetic parameters are possibly changed.
  // This is basically all the parameters in the parameter overview whose value is editable.

  // :TODO: Theoretically, it is possible that also task parameters influence the initial
  // state of a model but that is currently not handled.

  for (; ppEntity != ppEntityEnd; ++ppEntity)
    {
      // If we have an initial expression we have no initial values
      if ((*ppEntity)->getInitialExpression() != "" ||
          (*ppEntity)->getStatus() == CModelEntity::ASSIGNMENT)
        continue;

      // Metabolites have two initial values
      if (mFramework == 0 &&
          (pMetab = dynamic_cast< CMetab * >(*ppEntity)) != NULL)
        {
          // The concentration is assumed to be fix accept when this would lead to circular dependencies,
          // for the parent's compartment's initial volume.
          if (pMetab->isInitialConcentrationChangeAllowed() &&
              !isnan(pMetab->getInitialConcentration()))
            mChangedObjects.insert(pMetab->getInitialConcentrationReference());
          else
            mChangedObjects.insert(pMetab->getInitialValueReference());
        }
      else
        mChangedObjects.insert((*ppEntity)->getInitialValueReference());
    }

  // The reaction parameters
  CCopasiVector< CReaction >::const_iterator itReaction = pModel->getReactions().begin();
  CCopasiVector< CReaction >::const_iterator endReaction = pModel->getReactions().end();
  size_t i, imax;

  for (; itReaction != endReaction; ++itReaction)
    {
      const CCopasiParameterGroup & Group = (*itReaction)->getParameters();

      for (i = 0, imax = Group.size(); i < imax; i++)
        mChangedObjects.insert(Group.getParameter(i)->getObject(CCopasiObjectName("Reference=Value")));
    }

  // Fix for Issue 1170: We need to add elements of the stoichiometry, reduced stoichiometry,
  // and link matrices.
  const CArrayAnnotation * pMatrix = NULL;
  pMatrix = dynamic_cast<const CArrayAnnotation *>(pModel->getObject(std::string("Array=Stoichiometry(ann)")));

  if (pMatrix != NULL)
    pMatrix->appendElementReferences(mChangedObjects);

  pMatrix = dynamic_cast<const CArrayAnnotation *>(pModel->getObject(std::string("Array=Reduced stoichiometry(ann)")));

  if (pMatrix != NULL)
    pMatrix->appendElementReferences(mChangedObjects);

  pMatrix = dynamic_cast<const CArrayAnnotation *>(pModel->getObject(std::string("Array=Link matrix(ann)")));

  if (pMatrix != NULL)
    pMatrix->appendElementReferences(mChangedObjects);

  try
    {
      mUpdateVector = pModel->buildInitialRefreshSequence(mChangedObjects);
    }

  catch (...)
    {
      QString Message = "Error while updating the initial values!\n\n";
      Message += FROM_UTF8(CCopasiMessage::getLastMessage().getText());

      CQMessageBox::critical(NULL, QString("COPASI Error"), Message,
                             QMessageBox::Ok, QMessageBox::Ok);
      CCopasiMessage::clearDeque();

      mUpdateVector.clear();
      return;
    }
}

void DataModelGUI::refreshInitialValues()
{
  buildChangedObjects();

  std::vector< Refresh * >::iterator it = mUpdateVector.begin();
  std::vector< Refresh * >::iterator end = mUpdateVector.end();

  for (; it != end; ++it)
    (**it)();
}

void DataModelGUI::setFramework(int framework)
{
  mFramework = framework;

  std::set< ListViews * >::iterator it = mListViews.begin();
  std::set< ListViews * >::iterator end = mListViews.end();

  for (; it != end; ++it)
    {
      (*it)->setFramework(mFramework);
    }
}

void DataModelGUI::updateMIRIAMResourceContents()
{
  std::set< ListViews * >::iterator it = mListViews.begin();
  std::set< ListViews * >::iterator end = mListViews.end();

  for (; it != end; ++it)
    {
      (*it)->updateMIRIAMResourceContents();
    }
}

void DataModelGUI::commit()
{
  std::set< ListViews * >::iterator it = mListViews.begin();
  std::set< ListViews * >::iterator end = mListViews.end();

  for (; it != end; ++it)
    {
      (*it)->commit();
    }
}

