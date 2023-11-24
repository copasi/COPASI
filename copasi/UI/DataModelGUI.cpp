// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

#include <cmath>

#include "copasi/copasi.h"

#include "DataModelGUI.h"
#include "CQThread.h"
#include "qtUtilities.h"
#include "CProgressBar.h"
#include "listviews.h"
#include "CQMessageBox.h"
#include "CQBrowserPaneDM.h"
#include "copasi/plotUI/COutputHandlerPlot.h"

#include "copasi/function/CFunctionDB.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CMetabNameInterface.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/plotUI/COutputHandlerPlot.h"
#include "copasi/plot/COutputDefinitionVector.h"
#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/scan/CScanTask.h"
#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/steadystate/CMCATask.h"
#include "copasi/lna/CLNATask.h"
#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/tssanalysis/CTSSATask.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/core/CVector.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/commandline/CConfigurationFile.h"
#include "copasi/utilities/CCopasiTree.h"

//#include "copasi/model/CModelMerging.h"

#define USE_LAYOUT 1
#define USE_RENDER 1

#include <sbml/SBMLDocument.h>
#include <sbml/packages/render/sbml/RenderPoint.h>
#include <sbml/packages/render/sbml/Text.h>
#include <sbml/packages/layout/sbml/LineSegment.h>

#include "copasi/layout/CLayout.h"
#include "copasi/layout/CListOfLayouts.h"
#include "copasi/layout/SBMLDocumentLoader.h"
#include "copasi/sbml/CCellDesignerImporter.h"
#include "copasi/sbml/SBMLUtils.h"

#include <sbml/packages/layout/extension/LayoutModelPlugin.h>

#include <QInputDialog>
#include <QNetworkProxy>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>

#include <copasi/UI/CQCopasiApplication.h>

#include <copasi/commandline/COptions.h>

#ifdef DELETE
#  undef DELETE
#endif

//*****************************************************************************

DataModelGUI::DataModelGUI(QObject * parent, CDataModel * pDataModel):
  QObject(parent),
  mpOutputHandlerPlot(NULL),
  mpDataModel(pDataModel),
  mListViews(),
  mFramework(0),
  mpThread(NULL),
  mpProgressBar(NULL),
  mSuccess(false),
  mSBMLImportString(),
  mpSBMLExportString(NULL),
  mFileName(),
  mDownloadUrl(),
  mDownloadDestination(),
  mOverWrite(false),
  mSBMLLevel(2),
  mSBMLVersion(4),
  mSBMLExportIncomplete(true),
  mSBMLExportCOPASIMIRIAM(true),
  mExportFormat(),
  mpMiriamResources(NULL),
  mDownloadedBytes(0),
  mDownloadedTotalBytes(0),
  mUpdateItem(C_INVALID_INDEX)
  , mSEDMLImportString()
  , mpSEDMLExportString(NULL)
  , mSEDMLLevel(1)
  , mSEDMLVersion(1)
  , mSEDMLExportIncomplete(true)
  , mSEDMLExportCOPASIMIRIAM(true)
  , mOptions()
  , mIgnoreNextFile(false)
{
  mpOutputHandlerPlot = new COutputHandlerPlot();
  mpDataModel->addInterface(mpOutputHandlerPlot);
}

DataModelGUI::~DataModelGUI()
{
  pdelete(mpOutputHandlerPlot);
}

//************************************************************

void DataModelGUI::linkDataModelToGUI()
{
  assert(mpDataModel != NULL);

  std::set< ListViews * >::iterator it = mListViews.begin();
  std::set< ListViews * >::iterator end = mListViews.end();

  for (; it != end; ++it)
    {
      (*it)->resetCache();
    }

  mpDataModel->deleteOldData();
}

//*****************************************************************

//*****************************************************************

void DataModelGUI::addModel(const std::string & fileName)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mFileName = fileName;

  mpThread = new CQThread(this, &DataModelGUI::addModelRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(addModelFinished()));
  mpThread->start();
}

void DataModelGUI::addModelRun()
{
  mSuccess = mpDataModel->addModel(mFileName, mpProgressBar);
}

void DataModelGUI::addModelFinished()
{
  if (mSuccess)
    {
      //notify(ListViews::ObjectType::MODEL, ListViews::CHANGE, "");
      addRecentFile(mFileName);
      //linkDataModelToGUI();
    }

  disconnect(mpThread, SIGNAL(finished()), this, SLOT(addModelFinished()));

  threadFinished();
}

bool DataModelGUI::createModel()
{
  assert(mpDataModel != NULL);

  if (!mpDataModel->newModel(NULL, false)) return false;

  mpOutputHandlerPlot->setOutputDefinitionVector(mpDataModel->getPlotDefinitionList());

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

void DataModelGUI::downloadFileFromUrl(const std::string & url, const std::string& destination, bool withProgress)
{

  mSuccess = true;

  QNetworkAccessManager *manager = new QNetworkAccessManager(this);

  QString server = FROM_UTF8(CRootContainer::getConfiguration()->getProxyServer());

  // if we have a proxy server use it
  if (!server.isEmpty())
    {
      int port = CRootContainer::getConfiguration()->getProxyPort();
      QString user = FROM_UTF8(CRootContainer::getConfiguration()->getProxyUser());
      QString pass = FROM_UTF8(CRootContainer::getConfiguration()->getProxyPassword());

      // if we have a username, but no password stored (which would be in clear text), then
      // ask for password.
      if (!user.isEmpty() && pass.isEmpty())
        {
          bool flag = false;
          QString temp = QInputDialog::getText(
                           (QWidget*)((CQCopasiApplication*)qApp)->getMainWindow(),
                           QString("Enter proxy password"),
                           QString("You specified a proxy username, but no password, please enter the proxy password"),
                           QLineEdit::Password,
                           QString(""),
                           &flag
                         );

          if (flag)
            pass = temp;
        }

      manager->setProxy(QNetworkProxy(QNetworkProxy::HttpProxy, server, port, user, pass));
    }

  if (withProgress)
    {
      // start progress dialog
      mpProgressBar = CProgressBar::create();
      mpProgressBar->setName("Download file...");
      mDownloadedBytes = 0; mDownloadedTotalBytes = 100;
      mUpdateItem = ((CProcessReport*)mpProgressBar)->addItem("Download file", mDownloadedBytes, &mDownloadedTotalBytes);
    }

  mDownloadDestination = destination;
  mDownloadUrl = url;

  connect(manager, SIGNAL(finished(QNetworkReply*)),
          this, SLOT(downloadFinished(QNetworkReply*)));

  QNetworkReply* reply = manager->get(QNetworkRequest(QUrl(FROM_UTF8(url))));
  connect(reply, SIGNAL(downloadProgress(qint64, qint64)),
          this, SLOT(miriamDownloadProgress(qint64, qint64)));
}

void DataModelGUI::loadModelRun()
{
  try
    {
      assert(mpDataModel != NULL);
      mSuccess = mpDataModel->loadFromFile(mFileName, mpProgressBar, false);
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
      addRecentFile(mFileName);

      mpOutputHandlerPlot->setOutputDefinitionVector(mpDataModel->getPlotDefinitionList());
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
      assert(mpDataModel != NULL);
      mSuccess = mpDataModel->saveModel(mFileName, mpProgressBar, mOverWrite);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

CDataModel * DataModelGUI::getDataModel()
{
  return mpDataModel;
}

void DataModelGUI::saveModelFinished()
{
  if (mSuccess)
    {
      addRecentFile(mFileName);
    }

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
      assert(mpDataModel != NULL);
      mSuccess = mpDataModel->importSBMLFromString(mSBMLImportString, mpProgressBar, false);
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
      // can't run this in a separate thread because it uses GUI routines
      // TODO maybe put the main part of this routine in a separate thread after
      // TODO asking the user
      this->importCellDesigner();
      mpOutputHandlerPlot->setOutputDefinitionVector(mpDataModel->getPlotDefinitionList());
      linkDataModelToGUI();
    }

  disconnect(mpThread, SIGNAL(finished()), this, SLOT(importSBMLFromStringFinished()));

  threadFinished();
}

void  DataModelGUI::saveFunctionDB(const std::string & fileName)
{
  CFunctionDB* pFunctionDB = CRootContainer::getFunctionList();

  if (pFunctionDB == NULL) return;

  pFunctionDB->save(fileName);
}

void  DataModelGUI::loadFunctionDB(const std::string & fileName)
{
  CFunctionDB* pFunctionDB = CRootContainer::getFunctionList();

  if (pFunctionDB == NULL) return;

  if (pFunctionDB->load(fileName))
    emit notify(ListViews::ObjectType::FUNCTION, ListViews::DELETE, std::string());
}

void DataModelGUI::saveModelParameterSets(const std::string & fileName)
{
  mpDataModel->saveModelParameterSets(fileName);
}

void DataModelGUI::loadModelParameterSets(const std::string & fileName)
{
  if (mpDataModel->loadModelParameterSets(fileName, mpProgressBar))
    {
      emit notify(ListViews::ObjectType::MODELPARAMETERSET, ListViews::ADD, std::string());
    }
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
      assert(mpDataModel != NULL);
      mSuccess = mpDataModel->importSBML(mFileName, mpProgressBar, false);
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
      this->importCellDesigner();
      addRecentFile(mFileName);

      mpOutputHandlerPlot->setOutputDefinitionVector(mpDataModel->getPlotDefinitionList());
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
      assert(mpDataModel != NULL);
      *mpSBMLExportString = mpDataModel->exportSBMLToString(mpProgressBar, 2, 4);
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

bool
DataModelGUI::isBusy() const
{
  return mpThread != NULL;
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
      assert(mpDataModel != NULL);
      mSuccess = mpDataModel->exportSBML(mFileName, mOverWrite, mSBMLLevel, mSBMLVersion, mSBMLExportIncomplete, mSBMLExportCOPASIMIRIAM, mpProgressBar);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::exportSBMLFinished()
{
  if (mSuccess)
    {
      addRecentFile(mFileName);
    }

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
      assert(mpDataModel != NULL);
      mSuccess = mpDataModel->exportMathModel(mFileName, mpProgressBar, mExportFormat, mOverWrite);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

const std::string & DataModelGUI::getFileName() const
{
  return mFileName;
}

const std::string& DataModelGUI::getLastDownloadUrl() const
{
  return mDownloadUrl;
}

const std::string& DataModelGUI::getLastDownloadDestination() const
{
  return mDownloadDestination;
}

void DataModelGUI::exportMathModelFinished()
{
  disconnect(mpThread, SIGNAL(finished()), this, SLOT(exportMathModelFinished()));

  threadFinished();
}

void DataModelGUI::miriamDownloadFinished(QNetworkReply* reply)
{
  bool success = true;
  mDownloadedBytes = 100;
  mpProgressBar->progressItem(mUpdateItem);
  mpProgressBar->finishItem(mUpdateItem);

  CMIRIAMResources & miriamResources = *mpMiriamResources;

  if (reply != NULL && reply->error() == QNetworkReply::NoError && reply->bytesAvailable() > 0)
    {
      std::string filename;
      COptions::getValue("ConfigDir", filename);
      filename += "/miriam.xml";

      QFile *miriamFile = new QFile(filename.c_str());

      if (miriamFile->open(QFile::WriteOnly))
        {
          miriamFile->write(reply->readAll());
          miriamFile->flush();
          miriamFile->close();
          success = miriamResources.updateMIRIAMResourcesFromFile(mpProgressBar, filename);
        }

      delete miriamFile;
    }
  else
    {
      QString errorString = reply->errorString();
      CCopasiMessage(CCopasiMessage::ERROR, TO_UTF8_UNTRIMMED(errorString));
      success = false;
    }

  reply->deleteLater();

  pdelete(mpProgressBar);

  // notify UI to pick up
  emit finished(success);
}

void DataModelGUI::downloadFinished(QNetworkReply *reply)
{
  mSuccess = false;
  mDownloadedBytes = 100;
  bool withProgress = mpProgressBar != NULL;

  if (withProgress) mpProgressBar->finishItem(mUpdateItem);

  std::string redirectUrl = reply == NULL ? std::string("") :
                            TO_UTF8(reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl().toString());

  if (!redirectUrl.empty())
    {
      if (withProgress)
        {
          mpProgressBar->finish();
          mpProgressBar->deleteLater();
          mpProgressBar = NULL;
        }

      reply->deleteLater();
      downloadFileFromUrl(redirectUrl, mDownloadDestination, withProgress);
      return;
    }

  if (reply != NULL && reply->error() == QNetworkReply::NoError && reply->bytesAvailable() > 0)
    {
      QFile downloadedFile(mDownloadDestination.c_str());

      if (downloadedFile.open(QFile::WriteOnly))
        {
          downloadedFile.write(reply->readAll());
          downloadedFile.flush();
          downloadedFile.close();
          mSuccess = true;
        }
    }
  else
    {
      QString errorString = reply->errorString();
      CCopasiMessage(CCopasiMessage::ERROR, TO_UTF8_UNTRIMMED(errorString));
    }

  reply->deleteLater();

  threadFinished();
}

void DataModelGUI::miriamDownloadProgress(qint64 received, qint64 total)
{
  if (total != -1)
    {
      mDownloadedBytes = 100 * double(received) / double(total);
    }
  else
    {
      ++mDownloadedBytes;
    }

  if (mpProgressBar != NULL && !mpProgressBar->progressItem(mUpdateItem))
    {
      QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());

      if (reply != NULL) reply->abort();
    }
}

bool DataModelGUI::updateMIRIAM(CMIRIAMResources & miriamResources)
{
  bool success = true;

  mpMiriamResources = &miriamResources;

  QNetworkAccessManager *manager = new QNetworkAccessManager(this);

  QString server = FROM_UTF8(CRootContainer::getConfiguration()->getProxyServer());

  // if we have a proxy server use it
  if (!server.isEmpty())
    {
      int port = CRootContainer::getConfiguration()->getProxyPort();
      QString user = FROM_UTF8(CRootContainer::getConfiguration()->getProxyUser());
      QString pass = FROM_UTF8(CRootContainer::getConfiguration()->getProxyPassword());

      // if we have a username, but no password stored (which would be in clear text), then
      // ask for password.
      if (!user.isEmpty() && pass.isEmpty())
        {
          bool flag = false;
          QString temp = QInputDialog::getText(
                           (QWidget*)((CQCopasiApplication*)qApp)->getMainWindow(),
                           QString("Enter proxy password"),
                           QString("You specified a proxy username, but no password, please enter the proxy password"),
                           QLineEdit::Password,
                           QString(""),
                           &flag
                         );

          if (flag)
            pass = temp;
        }

      manager->setProxy(QNetworkProxy(QNetworkProxy::HttpProxy, server, port, user, pass));
    }

  // start progress dialog
  mpProgressBar = CProgressBar::create();
  mpProgressBar->setName("MIRIAM Resources Update...");
  mDownloadedBytes = 0; mDownloadedTotalBytes = 100;
  mUpdateItem = ((CProcessReport*)mpProgressBar)->addItem("Download MIRIAM info", mDownloadedBytes, &mDownloadedTotalBytes);

  connect(manager, SIGNAL(finished(QNetworkReply*)),
          this, SLOT(miriamDownloadFinished(QNetworkReply*)));

  QNetworkReply* reply = manager->get(QNetworkRequest(QUrl("https://copasi.org/static/miriam.xml")));
  connect(reply, SIGNAL(downloadProgress(qint64, qint64)),
          this, SLOT(miriamDownloadProgress(qint64, qint64)));

  return success;
}

//************** QApplication ***********************************************

//************Model-View Architecture*****************************************

bool DataModelGUI::notify(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  // The GUI is inactive whenever a progress bar exist. We wait with updates
  // until then.
  if (mpProgressBar != NULL) return false;

  // update all initial value
  if (action != ListViews::RENAME && // not needed after rename
      !(action == ListViews::ADD && objectType == ListViews::ObjectType::MODEL) // not needed when model was loaded
     )
    {
      refreshInitialValues();
    }

  emit notifyView(objectType, action, cn);

  return true;
}

void DataModelGUI::notifyChanges(const CUndoData::CChangeSet & changes)
{
  // The GUI is inactive whenever a progress bar exist. We wait with updates
  // until then.
  std::string CN;

  if (mpProgressBar == NULL)
    {
      CObjectInterface::ContainerList List;
      List.push_back(mpDataModel);

      // We loop through all the changes and call notify
      CUndoData::CChangeSet::const_iterator it = changes.begin();
      CUndoData::CChangeSet::const_iterator end = changes.end();

      ListViews::Action Action = ListViews::Action::CHANGE;
      std::string CN;
      std::string MappedCN;

      for (; it != end; ++it)
        {
          switch (it->type)
            {
              case CUndoData::Type::INSERT:
                Action = ListViews::Action::ADD;
                CN = it->objectAfter;
                break;

              case CUndoData::Type::CHANGE:
                Action = ListViews::Action::CHANGE;
                CN = it->objectBefore;
                break;

              case CUndoData::Type::REMOVE:
                Action = ListViews::Action::DELETE;
                CN = it->objectBefore;
                break;
            }

          ListViews::ObjectType ObjectType = ListViews::DataObjectType.toEnum(it->objectType, ListViews::ObjectType::STATE);
          MappedCN = CN;

          if (ObjectType == ListViews::ObjectType::MIRIAM)
            {
              MappedCN = CN.substr(0, CN.find(",CMIRIAMInfo=CMIRIAMInfoObject"));
            }
          else if (ObjectType == ListViews::ObjectType::STATE)
            {
              if (it->objectType == "Creator" ||
                  it->objectType == "Reference" ||
                  it->objectType == "BiologicalDescription" ||
                  it->objectType == "Modification")
                {
                  ObjectType = ListViews::ObjectType::MIRIAM;
                  MappedCN = CN.substr(0, CN.find(",CMIRIAMInfo=CMIRIAMInfoObject"));
                }
            }

          notify(ObjectType, Action, MappedCN);
        }

      std::pair< const CUndoData *, bool > LastExecution = mpDataModel->getUndoStack()->getLastExecution();

      if (LastExecution.first != NULL)
        {
          const CData & MetaData = LastExecution.first->getMetaData();

          ListViews::WidgetType Id = ListViews::WidgetName.toEnum(MetaData.getProperty("Widget Type").toString(), ListViews::WidgetType::NotFound);
          int TabIndex = MetaData.isSetProperty("Widget Tab") ? MetaData.getProperty("Widget Tab").toInt() : -1;

          if (LastExecution.second) // redo
            {
              CN = MetaData.getProperty("Widget Object CN (after)").toString();
            }
          else // undo
            {
              CN = MetaData.getProperty("Widget Object CN (before)").toString();
            }

          emit this->signalSwitchWidget(Id, CN, TabIndex);
        }
    }
}

void DataModelGUI::registerListView(ListViews * pListView)
{
  mListViews.insert(pListView);
}

void DataModelGUI::deregisterListView(ListViews * pListView)
{
  mListViews.erase(pListView);
}

void DataModelGUI::refreshInitialValues()
{
  std::set< ListViews * >::iterator it = mListViews.begin();
  std::set< ListViews * >::iterator end = mListViews.end();

  for (; it != end; ++it)
    {
      CModel * pModel = (*it)->getDataModel()->getModel();
      pModel->updateInitialValues(static_cast< CCore::Framework >(mFramework));
    }
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

void DataModelGUI::setIgnoreNextFile(bool ignore)
{
  mIgnoreNextFile = ignore;
}

void DataModelGUI::addRecentFile(const std::string & file)
{
  if (mIgnoreNextFile)
    {
      mIgnoreNextFile = false;
      return;
    }

  switch (mpDataModel->getContentType())
    {
      case CDataModel::ContentType::COPASI:
      case CDataModel::ContentType::GEPASI:
        CRootContainer::getConfiguration()->getRecentFiles().addFile(file);
        break;

      case CDataModel::ContentType::SBML:
        CRootContainer::getConfiguration()->getRecentSBMLFiles().addFile(file);
        break;

      case CDataModel::ContentType::SEDML:
        CRootContainer::getConfiguration()->getRecentSEDMLFiles().addFile(file);
        break;
    }

  CRootContainer::getConfiguration()->save();
}

/**
 * This method tries to import CellDesigner annotations.
 */
void DataModelGUI::importCellDesigner()
{
  // add code to check for CellDesigner annotations
  // ask the user if the annotations should be imported
  assert(mpDataModel != NULL);

  if (mpDataModel != NULL)
    {
      SBMLDocument* pSBMLDocument = mpDataModel->getCurrentSBMLDocument();

      if (pSBMLDocument != NULL &&
          pSBMLDocument->getModel() != NULL &&
          pSBMLDocument->getModel()->getAnnotation() != NULL)
        {
          // check for the CellDesigner namespace
          std::pair<bool, std::string> foundNamespace = CCellDesignerImporter::findCellDesignerNamespace(pSBMLDocument);

          if (foundNamespace.first == true)
            {
              const XMLNode* pAnno = CCellDesignerImporter::findCellDesignerAnnotation(pSBMLDocument, pSBMLDocument->getModel()->getAnnotation());

              // first we check if there are supported cell designer annotations
              if (pAnno != NULL)
                {
                  // check if the file contains the correct version
                  double version = CCellDesignerImporter::determineVersion(pAnno);

                  if (version < 4.0)
                    {
                      CCopasiMessage(CCopasiMessage::RAW, "CellDesigner annotation was found in the file, but the version is not supported.\nPlease open the file in the latest version of CellDesigner and save it again.");
                    }
                  else
                    {
                      bool importCD = false;
                      // if we don't have a layout import it!
                      LayoutModelPlugin* mplugin = (LayoutModelPlugin*)pSBMLDocument->getModel()->getPlugin("layout");

                      if (mplugin == NULL || (mplugin != NULL && mplugin->getNumLayouts() == 0))
                        importCD = true;

                      // ask the user if the CellDesigner annotation should be imported
                      if (importCD || CQMessageBox::question(ListViews::ancestor(this), "CellDesigner import", "A CellDesigner diagram was found in this file.\nDo you want to import the diagram?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
                        {
                          // do the import
                          CCellDesignerImporter cd_importer(pSBMLDocument);

                          if (cd_importer.getLayout() == NULL)
                            {
                              CCopasiMessage(CCopasiMessage::WARNING, "Sorry, CellDesigner annotations could not be imported.");
                            }
                          else
                            {
                              // now we have to import the created layout
                              // create the model map
                              std::string s1, s2;
                              std::map<std::string, std::string> modelmap;
                              std::map<const CDataObject*, SBase*>::const_iterator it;
                              std::map<const CDataObject*, SBase*>::const_iterator itEnd = mpDataModel->getCopasi2SBMLMap().end();

                              for (it = mpDataModel->getCopasi2SBMLMap().begin(); it != itEnd; ++it)
                                {
                                  s1 = SBMLUtils::getIdFromSBase(it->second);

                                  if (it->first)
                                    {
                                      s2 = it->first->getKey();
                                    }
                                  else
                                    {
                                      s2 = "";
                                    }

                                  if ((s1 != "") && (s2 != ""))
                                    {
                                      modelmap[s1] = s2;
                                    }
                                }

                              // the layout map and the id to key map can be empty
                              std::map<std::string, std::string> layoutmap;
                              std::map<std::string, std::string> idToKeyMap;
                              CLayout* pLayout = SBMLDocumentLoader::createLayout(*cd_importer.getLayout(), modelmap, layoutmap, idToKeyMap);

                              // add the layout to the DataModel
                              if (pLayout != NULL && mpDataModel->getListOfLayouts() != NULL)
                                {
                                  // the addLayout methods expects a map as the second argument which currently is
                                  // ignored, so we just pass an empty one
                                  // TODO maybe the methods actually expects one of the maps above (layoutmap or idToKeyMap), but
                                  // TODO this is not documented in CListOfLayouts
                                  std::map<std::string, std::string> tmp;
                                  mpDataModel->getListOfLayouts()->addLayout(pLayout, tmp);
                                }
                              else
                                {
                                  CCopasiMessage(CCopasiMessage::WARNING, "Sorry, Layout from CellDesigner annotations could not be created.");
                                }
                            }
                        }
                    }
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::RAW, "CellDesigner annotation was found in the file, but the version is not supported.\nPlease open the file in the latest version of CellDesigner and save it again.");
                }
            }
        }
    }
}

void DataModelGUI::exportShinyArchive(const std::string & fileName, bool overwriteFile)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mFileName = fileName;
  mOverWrite = overwriteFile;

  mpThread = new CQThread(this, &DataModelGUI::exportShinyArchiveRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(exportShinyFinished()));
  mpThread->start();
}

void DataModelGUI::exportShinyArchiveRun()
{
  try
    {
      assert(mpDataModel != NULL);
      mSuccess = mpDataModel->exportShinyArchive(mFileName,
                 true,
                 true,
                 mOverWrite,
                 mpProgressBar);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::exportShinyFinished()
{

  disconnect(mpThread, SIGNAL(finished()), this, SLOT(exportShinyFinished()));

  threadFinished();
}

void DataModelGUI::openCombineArchive(const std::string & fileName, const SedmlImportOptions * pOptions)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mFileName = fileName;

  if (pOptions)
    mOptions = *pOptions;
  else
    mOptions = SedmlImportOptions();

  mpThread = new CQThread(this, &DataModelGUI::openCombineArchiveRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(importCombineFinished()));
  mpThread->start();
}

void DataModelGUI::exportCombineArchive(const std::string & fileName, bool overwriteFile)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mFileName = fileName;
  mOverWrite = overwriteFile;

  mpThread = new CQThread(this, &DataModelGUI::exportCombineArchiveRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(exportCombineFinished()));
  mpThread->start();
}

void DataModelGUI::openCombineArchiveRun()
{
  try
    {
      assert(mpDataModel != NULL);
      mSuccess = mpDataModel->openCombineArchive(mFileName, mpProgressBar, true, &mOptions);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::exportCombineArchiveRun()
{
  try
    {
      assert(mpDataModel != NULL);
      mSuccess = mpDataModel->exportCombineArchive(mFileName,
                 true,
                 true,
                 true,
                 true,
                 mOverWrite,
                 mpProgressBar);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::importCombineFinished()
{
  if (mSuccess)
    {

      mpOutputHandlerPlot->setOutputDefinitionVector(mpDataModel->getPlotDefinitionList());
      linkDataModelToGUI();
    }

  disconnect(mpThread, SIGNAL(finished()), this, SLOT(importCombineFinished()));

  threadFinished();
}

void DataModelGUI::exportCombineFinished()
{

  disconnect(mpThread, SIGNAL(finished()), this, SLOT(exportSBMLFinished()));

  threadFinished();
}

void DataModelGUI::importSEDML(const std::string & fileName, const SedmlImportOptions * pOptions)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mFileName = fileName;

  if (pOptions)
    mOptions = *pOptions;
  else
    mOptions = SedmlImportOptions();

  mpThread = new CQThread(this, &DataModelGUI::importSEDMLRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(importSEDMLFinished()));
  mpThread->start();
}

void DataModelGUI::importSEDMLRun()
{
  try
    {
      assert(mpDataModel != NULL);
      mSuccess = mpDataModel->importSEDML(mFileName, mpProgressBar, false, &mOptions);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::importSEDMLFinished()
{
  if (mSuccess)
    {
      addRecentFile(mFileName);
      mpOutputHandlerPlot->setOutputDefinitionVector(mpDataModel->getPlotDefinitionList());
      linkDataModelToGUI();
    }

  disconnect(mpThread, SIGNAL(finished()), this, SLOT(importSEDMLFinished()));

  threadFinished();
}

void DataModelGUI::exportSEDML(const std::string & fileName, bool overwriteFile, int sedmlLevel, int sedmlVersion, bool exportIncomplete, bool exportCOPASIMIRIAM)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mFileName = fileName;
  mOverWrite = overwriteFile;
  mSEDMLLevel = sedmlLevel;
  mSEDMLVersion = sedmlVersion;
  mSEDMLExportIncomplete = exportIncomplete;
  mSEDMLExportCOPASIMIRIAM = exportCOPASIMIRIAM;

  mpThread = new CQThread(this, &DataModelGUI::exportSEDMLRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(exportSEDMLFinished()));
  mpThread->start();
}

void DataModelGUI::exportSEDMLFinished()
{
  if (mSuccess)
    {
      addRecentFile(mFileName);
    }

  disconnect(mpThread, SIGNAL(finished()), this, SLOT(exportSEDMLFinished()));

  threadFinished();
}

void DataModelGUI::exportSEDMLToString(std::string & sedmlDocumentText)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mpSEDMLExportString = & sedmlDocumentText;

  mpThread = new CQThread(this, &DataModelGUI::exportSEDMLToStringRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(exportSEDMLToStringFinished()));
  mpThread->start();
}

void DataModelGUI::exportSEDMLToStringRun()
{
  try
    {
      assert(mpDataModel != NULL);
      *mpSEDMLExportString = mpDataModel->exportSEDMLToString(mpProgressBar, 1, 1);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::exportSEDMLToStringFinished()
{
  disconnect(mpThread, SIGNAL(finished()), this, SLOT(exportSEDMLToStringFinished()));

  threadFinished();
}

void DataModelGUI::exportSEDMLRun()
{
  try
    {
      assert(mpDataModel != NULL);
      mSuccess = mpDataModel->exportSEDML(mFileName, mOverWrite, mSEDMLLevel, mSEDMLVersion, mSEDMLExportIncomplete, mSEDMLExportCOPASIMIRIAM, mpProgressBar);
    }

  catch (...)
    {
      mSuccess = false;
    }
}
