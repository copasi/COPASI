// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
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
#include <copasi/UI/copasiWidget.h>

#include <copasi/commandline/COptions.h>

#ifdef DELETE
#  undef DELETE
#endif

//*****************************************************************************

DataModelGUI::DataModelGUI(QObject * parent, CDataModel * pDataModel)
  : QObject(parent)
  , mpOutputHandlerPlot(NULL)
  , mpDataModel(pDataModel)
  , mListViews()
  , mFramework(0)
  , mRunningThreads()
  , mSBMLImportString()
  , mpSBMLExportString(NULL)
  , mFileName()
  , mDownloadUrl()
  , mDownloadDestination()
  , mDownloadActive(false)
  , mOverWrite(false)
  , mSBMLLevel(2)
  , mSBMLVersion(4)
  , mSBMLExportIncomplete(true)
  , mSBMLExportCOPASIMIRIAM(true)
  , mExportFormat()
  , mpMiriamResources(NULL)
  , mDownloadedBytes(0)
  , mDownloadedTotalBytes(0)
  , mDownloadThread()
  , mUpdateItem(C_INVALID_INDEX)
  , mSEDMLImportString()
  , mpSEDMLExportString(NULL)
  , mSEDMLLevel(1)
  , mSEDMLVersion(1)
  , mSEDMLExportIncomplete(true)
  , mSEDMLExportCOPASIMIRIAM(true)
  , mOptions()
  , mIgnoreNextFile(false)
  , mSaveMIRIAM(false)
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
  mRunningThreads["addModel"].pProgressBar = CProgressBar::create();
  mRunningThreads["addModel"].success = false;

  mFileName = fileName;

  CQThread *pThread = new CQThread(this, &DataModelGUI::addModelRun);
  connect(pThread, SIGNAL(finished()), this, SLOT(addModelFinished()));
  mRunningThreads["addModel"].pThread = pThread;
  pThread->start();
}

void DataModelGUI::addModelRun()
{
  mRunningThreads["addModel"].success = mpDataModel->addModel(mFileName, mRunningThreads["addModel"].pProgressBar);
}

void DataModelGUI::addModelFinished()
{
  if (mRunningThreads["addModel"].success)
    {
      //notify(ListViews::ObjectType::MODEL, ListViews::CHANGE, "");
      addRecentFile(mFileName);
      //linkDataModelToGUI();
    }

  disconnect(mRunningThreads["addModel"].pThread, SIGNAL(finished()), this, SLOT(addModelFinished()));
  threadFinished("addModel");
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
  mRunningThreads["loadModel"].pProgressBar = CProgressBar::create();
  mRunningThreads["loadModel"].success = false;

  mFileName = fileName;

  CQThread *pThread = new CQThread(this, &DataModelGUI::loadModelRun);
  connect(pThread, SIGNAL(finished()), this, SLOT(loadModelFinished()));
  mRunningThreads["loadModel"].pThread = pThread;
  pThread->start();
}

void DataModelGUI::downloadFileFromUrl(const std::string & url, const std::string& destination, bool withProgress)
{
  mRunningThreads["downloadFileFromUrl"].success = false;
  mDownloadActive = true;

  QNetworkAccessManager *manager = new QNetworkAccessManager(this);
  manager->setStrictTransportSecurityEnabled(true);
  manager->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);

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
      mRunningThreads["downloadFileFromUrl"].pProgressBar = CProgressBar::create();
      mRunningThreads["downloadFileFromUrl"].pProgressBar->setName("Download file...");
      mDownloadedBytes = 0; mDownloadedTotalBytes = 100; mDownloadThread = "downloadFileFromUrl";
      mUpdateItem = ((CProcessReport*)mRunningThreads["downloadFileFromUrl"].pProgressBar)->addItem("Download file", mDownloadedBytes, &mDownloadedTotalBytes);
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
      mRunningThreads["loadModel"].success = mpDataModel->loadFromFile(mFileName, mRunningThreads["loadModel"].pProgressBar, false);
    }

  catch (...)
    {
      mRunningThreads["loadModel"].success = false;
    }
}

void DataModelGUI::loadModelFinished()
{
  if (mRunningThreads["loadModel"].success)
    {
      addRecentFile(mFileName);

      mpOutputHandlerPlot->setOutputDefinitionVector(mpDataModel->getPlotDefinitionList());
      linkDataModelToGUI();
    }

  disconnect(mRunningThreads["loadModel"].pThread, SIGNAL(finished()), this, SLOT(loadModelFinished()));
  threadFinished("loadModel");
}

void DataModelGUI::saveModel(const std::string & fileName, bool overwriteFile)
{
  mRunningThreads["saveModel"].pProgressBar = CProgressBar::create();
  mRunningThreads["saveModel"].success = false;

  mFileName = fileName;
  mOverWrite = overwriteFile;

  CQThread *pThread = new CQThread(this, &DataModelGUI::saveModelRun);
  connect(pThread, SIGNAL(finished()), this, SLOT(saveModelFinished()));
  mRunningThreads["saveModel"].pThread = pThread;
  pThread->start();
}

void DataModelGUI::saveModelRun()
{
  try
    {
      assert(mpDataModel != NULL);
      mRunningThreads["saveModel"].success = mpDataModel->saveModel(mFileName, mRunningThreads["saveModel"].pProgressBar, mOverWrite);
    }

  catch (...)
    {
      mRunningThreads["saveModel"].success = false;
    }
}

CDataModel * DataModelGUI::getDataModel()
{
  return mpDataModel;
}

void DataModelGUI::saveModelFinished()
{
  if (mRunningThreads["saveModel"].success)
    {
      addRecentFile(mFileName);
    }

  disconnect(mRunningThreads["saveModel"].pThread, SIGNAL(finished()), this, SLOT(saveModelFinished()));

  threadFinished("saveModel");
}

void DataModelGUI::importSBMLFromString(const std::string & sbmlDocumentText)
{
  mRunningThreads["importSBMLFromString"].pProgressBar = CProgressBar::create();
  mRunningThreads["importSBMLFromString"].success = false;

  mSBMLImportString = sbmlDocumentText;

  CQThread *pThread = new CQThread(this, &DataModelGUI::importSBMLFromStringRun);
  mRunningThreads["importSBMLFromString"].pThread = pThread;
  connect(pThread, SIGNAL(finished()), this, SLOT(importSBMLFromStringFinished()));
  pThread->start();
}

void DataModelGUI::importSBMLFromStringRun()
{
  try
    {
      assert(mpDataModel != NULL);
      mRunningThreads["importSBMLFromString"].success = mpDataModel->importSBMLFromString(mSBMLImportString, mRunningThreads["importSBMLFromString"].pProgressBar, false);
    }

  catch (...)
    {
      mRunningThreads["importSBMLFromString"].success = false;
    }
}

void DataModelGUI::importSBMLFromStringFinished()
{
  mSBMLImportString = "";

  if (mRunningThreads["importSBMLFromString"].success)
    {
      // can't run this in a separate thread because it uses GUI routines
      // TODO maybe put the main part of this routine in a separate thread after
      // TODO asking the user
      this->importCellDesigner();
      mpOutputHandlerPlot->setOutputDefinitionVector(mpDataModel->getPlotDefinitionList());
      linkDataModelToGUI();
    }

  disconnect(mRunningThreads["importSBMLFromString"].pThread, SIGNAL(finished()), this, SLOT(importSBMLFromStringFinished()));
  threadFinished("importSBMLFromString");
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
    emit notify(ListViews::ObjectType::FUNCTION, ListViews::DELETE, CRegisteredCommonName());
}

void DataModelGUI::saveModelParameterSets(const std::string & fileName)
{
  mpDataModel->saveModelParameterSets(fileName);
}

void DataModelGUI::loadModelParameterSets(const std::string & fileName)
{
  if (mpDataModel->loadModelParameterSets(fileName, nullptr))
    {
      emit notify(ListViews::ObjectType::MODELPARAMETERSET, ListViews::ADD, CRegisteredCommonName());
    }
}

void DataModelGUI::importSBML(const std::string & fileName)
{
  mRunningThreads["importSBML"].pProgressBar = CProgressBar::create();
  mRunningThreads["importSBML"].success = false;

  mFileName = fileName;
  CQThread *pThread = new CQThread(this, &DataModelGUI::importSBMLRun);
  connect(pThread, SIGNAL(finished()), this, SLOT(importSBMLFinished()));
  mRunningThreads["importSBML"].pThread = pThread;
  pThread->start();
}

void DataModelGUI::importSBMLRun()
{
  try
    {
      assert(mpDataModel != NULL);
      mRunningThreads["importSBML"].success = mpDataModel->importSBML(mFileName, mRunningThreads["importSBML"].pProgressBar, false);
    }

  catch (...)
    {
      mRunningThreads["importSBML"].success = false;
    }
}

void DataModelGUI::importSBMLFinished()
{
  if (mRunningThreads["importSBML"].success)
    {
      this->importCellDesigner();
      addRecentFile(mFileName);

      mpOutputHandlerPlot->setOutputDefinitionVector(mpDataModel->getPlotDefinitionList());
      linkDataModelToGUI();
    }

  disconnect(mRunningThreads["importSBML"].pThread, SIGNAL(finished()), this, SLOT(importSBMLFinished()));
  threadFinished("importSBML");
}

void DataModelGUI::exportSBMLToString(std::string & sbmlDocumentText)
{
  mRunningThreads["exportSBMLToString"].pProgressBar = CProgressBar::create();
  mRunningThreads["exportSBMLToString"].success = false;

  mpSBMLExportString = & sbmlDocumentText;

  CQThread *pThread = new CQThread(this, &DataModelGUI::exportSBMLToStringRun);
  connect(pThread, SIGNAL(finished()), this, SLOT(exportSBMLToStringFinished()));
  mRunningThreads["exportSBMLToString"].pThread = pThread;
  pThread->start();
}

void DataModelGUI::exportSBMLToStringRun()
{
  try
    {
      assert(mpDataModel != NULL);
      *mpSBMLExportString = mpDataModel->exportSBMLToString(mRunningThreads["exportSBMLToString"].pProgressBar, 2, 4);
      mRunningThreads["exportSBMLToString"].success = true;
    }

  catch (...)
    {
      mRunningThreads["exportSBMLToString"].success = false;
    }
}

void DataModelGUI::exportSBMLToStringFinished()
{
  disconnect(mRunningThreads["exportSBMLToString"].pThread, SIGNAL(finished()), this, SLOT(exportSBMLToStringFinished()));
  threadFinished("exportSBMLToString");
}

bool DataModelGUI::isBusy() const
{
  if (mDownloadActive)
    return true;

  for (const std::pair< const std::string, sThreadData > &data: mRunningThreads)
    if (data.second.pProgressBar != nullptr)
      return true;

  return false;
}

void DataModelGUI::threadFinished(const std::string & thread)
{
  std::map< std::string, sThreadData >::iterator found = mRunningThreads.find(thread);
  bool success = false;

  if (found != mRunningThreads.end())
    {
      if (found->second.pThread != nullptr)
        {
          found->second.pThread->deleteLater();
          found->second.pThread = nullptr;
        }

      if (found->second.pProgressBar != nullptr)
        {
          found->second.pProgressBar->finish();
          found->second.pProgressBar->deleteLater();
          found->second.pProgressBar = nullptr;
        }

      success = found->second.success;
    }

  emit finished(thread, success);
}

void DataModelGUI::exportSBML(const std::string & fileName, bool overwriteFile, int sbmlLevel, int sbmlVersion, bool exportIncomplete, bool exportCOPASIMIRIAM)
{
  mRunningThreads["exportSBML"].pProgressBar = CProgressBar::create();
  mRunningThreads["exportSBML"].success = false;

  mFileName = fileName;
  mOverWrite = overwriteFile;
  mSBMLLevel = sbmlLevel;
  mSBMLVersion = sbmlVersion;
  mSBMLExportIncomplete = exportIncomplete;
  mSBMLExportCOPASIMIRIAM = exportCOPASIMIRIAM;

  CQThread *pThread = new CQThread(this, &DataModelGUI::exportSBMLRun);
  connect(pThread, SIGNAL(finished()), this, SLOT(exportSBMLFinished()));
  mRunningThreads["exportSBML"].pThread = pThread;
  pThread->start();
}

void DataModelGUI::exportSBMLRun()
{
  try
    {
      assert(mpDataModel != NULL);
      mRunningThreads["exportSBML"].success = mpDataModel->exportSBML(mFileName, mOverWrite, mSBMLLevel, mSBMLVersion, mSBMLExportIncomplete, mSBMLExportCOPASIMIRIAM, mRunningThreads["exportSBML"].pProgressBar);
    }

  catch (...)
    {
      mRunningThreads["exportSBML"].success = false;
    }
}

void DataModelGUI::exportSBMLFinished()
{
  if (mRunningThreads["exportSBML"].success)
    {
      addRecentFile(mFileName);
    }

  disconnect(mRunningThreads["exportSBML"].pThread, SIGNAL(finished()), this, SLOT(exportSBMLFinished()));
  threadFinished("exportSBML");
}

void DataModelGUI::exportMathModel(const std::string & fileName, const std::string & filter, bool overwriteFile)
{
  mRunningThreads["exportMathModel"].pProgressBar = CProgressBar::create();
  mRunningThreads["exportMathModel"].success = false;

  mFileName = fileName;
  mOverWrite = overwriteFile;
  mExportFormat = filter;

  CQThread *pThread = new CQThread(this, &DataModelGUI::exportMathModelRun);
  connect(pThread, SIGNAL(finished()), this, SLOT(exportMathModelFinished()));
  mRunningThreads["exportMathModel"].pThread = pThread;
  pThread->start();
}

void DataModelGUI::exportMathModelRun()
{
  try
    {
      assert(mpDataModel != NULL);
      mRunningThreads["exportMathModel"].success = mpDataModel->exportMathModel(mFileName, mRunningThreads["exportMathModel"].pProgressBar, mExportFormat, mOverWrite);
    }

  catch (...)
    {
      mRunningThreads["exportMathModel"].success = false;
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
  disconnect(mRunningThreads["exportMathModel"].pThread, SIGNAL(finished()), this, SLOT(exportMathModelFinished()));
  threadFinished("exportMathModel");
}

void DataModelGUI::miriamDownloadFinished(QNetworkReply* reply)
{
  bool success = true;
  mDownloadedBytes = 100;
  mRunningThreads["updateMIRIAM"].pProgressBar->progressItem(mUpdateItem);
  mRunningThreads["updateMIRIAM"].pProgressBar->finishItem(mUpdateItem);

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
          success = miriamResources.updateMIRIAMResourcesFromFile(mRunningThreads["updateMIRIAM"].pProgressBar, filename);
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

  pdelete(mRunningThreads["updateMIRIAM"].pProgressBar);

  // notify UI to pick up
  emit finished("updateMIRIAM", success);
}

void DataModelGUI::downloadFinished(QNetworkReply *reply)
{
  mDownloadedBytes = 100;
  bool withProgress = mRunningThreads["downloadFileFromUrl"].pProgressBar != NULL;

  if (withProgress) mRunningThreads["downloadFileFromUrl"].pProgressBar->finishItem(mUpdateItem);

  std::string redirectUrl = reply == NULL ? std::string("") :
                            TO_UTF8(reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl().toString());

  if (!redirectUrl.empty())
    {
      if (withProgress)
        {
          mRunningThreads["downloadFileFromUrl"].pProgressBar->finish();
          mRunningThreads["downloadFileFromUrl"].pProgressBar->deleteLater();
          mRunningThreads["downloadFileFromUrl"].pProgressBar = NULL;
        }

      reply->deleteLater();
      downloadFileFromUrl(redirectUrl, mDownloadDestination, withProgress);
      return;
    }

  if (reply != NULL
      && reply->error() == QNetworkReply::NoError
      && reply->bytesAvailable() > 0)
    {
      QFile downloadedFile(mDownloadDestination.c_str());

      if (downloadedFile.open(QFile::WriteOnly))
        {
          downloadedFile.write(reply->readAll());
          downloadedFile.flush();
          downloadedFile.close();
          mRunningThreads["downloadFileFromUrl"].success = true;
        }
    }
  else
    {
      QString errorString = reply->errorString();
      CCopasiMessage(CCopasiMessage::ERROR, TO_UTF8_UNTRIMMED(errorString));
    }

  reply->deleteLater();
  mDownloadActive = false;
  threadFinished("downloadFileFromUrl");
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

  if (mRunningThreads[mDownloadThread].pProgressBar != NULL
      && !mRunningThreads[mDownloadThread].pProgressBar->progressItem(mUpdateItem))
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
  manager->setRedirectPolicy(QNetworkRequest::SameOriginRedirectPolicy);

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
  mRunningThreads["updateMIRIAM"].pProgressBar = CProgressBar::create();
  mRunningThreads["updateMIRIAM"].pProgressBar->setName("MIRIAM Resources Update...");
  mDownloadedBytes = 0; mDownloadedTotalBytes = 100; mDownloadThread = "Download MIRIAM info";
  mUpdateItem = ((CProcessReport*)mRunningThreads["updateMIRIAM"].pProgressBar)->addItem("Download MIRIAM info", mDownloadedBytes, &mDownloadedTotalBytes);

  connect(manager, SIGNAL(finished(QNetworkReply*)),
          this, SLOT(miriamDownloadFinished(QNetworkReply*)));

  QNetworkReply* reply = manager->get(QNetworkRequest(QUrl("https://copasi.org/static/miriam.xml")));
  connect(reply, SIGNAL(downloadProgress(qint64, qint64)),
          this, SLOT(miriamDownloadProgress(qint64, qint64)));

  return success;
}

//************** QApplication ***********************************************

void DataModelGUI::detachOutputHandler()
{
  mpDataModel->removeInterface(mpOutputHandlerPlot);
}

void DataModelGUI::attachOutputHandler()
{
  mpDataModel->addInterface(mpOutputHandlerPlot);

  mpOutputHandlerPlot->setOutputDefinitionVector(mpDataModel->getPlotDefinitionList());

  linkDataModelToGUI();
}

//************Model-View Architecture*****************************************
bool DataModelGUI::notify(ListViews::ObjectType objectType, ListViews::Action action, const CRegisteredCommonName & cn)
{
  // The GUI is inactive whenever a progress bar exist. We wait with updates
  // until then.
  if (isBusy())
    return false;

  // update all initial value
  if (action != ListViews::RENAME && // not needed after rename
      !(action == ListViews::CHANGE && objectType == ListViews::ObjectType::TASK) && // not needed after task change
      !(action == ListViews::ADD && objectType == ListViews::ObjectType::MODEL) // not needed when model was loaded
     )
    {
      // This cannot be determined by only looking at the first list view.
      // It depends on whether the changed parameter set is the current object in any listview.
      // Furthermore if a list view displays another model than the ancestor of the changed parameter set it must be fully refreshed.
      const CModel * pParameterSetAncestor = nullptr;

      for (ListViews * pListView: mListViews)
        {
          CDataModel * pDataModel = pListView->getDataModel();
          CopasiWidget * currentWidget = pListView->getCurrentWidget();
          if (currentWidget == nullptr)
            continue;

          ListViews::ObjectType currentWidgetType = currentWidget->getObjectType();
          const CDataObject * pDataObject = currentWidget->getObject();
          if (pDataObject == nullptr)
            continue;

          CModelParameterSet * pActiveParameterSet = pDataModel != nullptr ? &pDataModel->getModel()->getActiveModelParameterSet() : nullptr;

          if (currentWidgetType == ListViews::ObjectType::MODELPARAMETERSET
              && pDataObject != nullptr
              && pDataObject == pActiveParameterSet)
            {
              pParameterSetAncestor = pListView->getDataModel()->getModel();
              break;
            }
        }

      refreshInitialValues(pParameterSetAncestor);
    }

  emit notifyView(objectType, action, cn);

  return true;
}

void DataModelGUI::notifyChanges(const CUndoData::CChangeSet & changes)
{
  // The GUI is inactive whenever a progress bar exist. We wait with updates
  // until then.
  std::string CN;

  if (!isBusy())
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

              case CUndoData::Type::__SIZE:
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

          notify(ObjectType, Action, CCommonName(MappedCN));
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

          if (CN.find("CN=Root,FunctionDB=FunctionDB") == 0
              || CN.find("CN=Root,Vector=Units list") == 0)
            emit this->signalSwitchWidget(Id, CCommonName(CN), TabIndex);
          else
            emit this->signalSwitchWidget(Id, CCommonName(CN), TabIndex);
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

void DataModelGUI::refreshInitialValues(const CModel * pParameterSetAncestor)
{
  std::set< ListViews * >::iterator it = mListViews.begin();
  std::set< ListViews * >::iterator end = mListViews.end();

  for (; it != end; ++it)
    {
      CModel * pModel = (*it)->getDataModel()->getModel();
      pModel->updateInitialValues(static_cast< CCore::Framework >(mFramework), pModel != pParameterSetAncestor);
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

      case CDataModel::ContentType::OMEX:
      case CDataModel::ContentType::__SIZE:
        break;
    }

  saveConfiguration(false);
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
  mRunningThreads["exportShinyArchive"].pProgressBar = CProgressBar::create();
  mRunningThreads["exportShinyArchive"].success = false;

  mFileName = fileName;
  mOverWrite = overwriteFile;

  CQThread *pThread = new CQThread(this, &DataModelGUI::exportShinyArchiveRun);
  connect(pThread, SIGNAL(finished()), this, SLOT(exportShinyFinished()));
  mRunningThreads["exportShinyArchive"].pThread = pThread;
  pThread->start();
}

void DataModelGUI::exportShinyArchiveRun()
{
  try
    {
      assert(mpDataModel != NULL);
      mRunningThreads["exportShinyArchive"].success =
        mpDataModel->exportShinyArchive(mFileName,
                                        true,
                                        true,
                                        mOverWrite,
                                        mRunningThreads["exportShinyArchive"].pProgressBar);
    }

  catch (...)
    {
      mRunningThreads["exportShinyArchive"].success = false;
    }
}

void DataModelGUI::exportShinyFinished()
{
  disconnect(mRunningThreads["exportShinyArchive"].pThread, SIGNAL(finished()), this, SLOT(exportShinyFinished()));
  threadFinished("exportShinyArchive");
}

void DataModelGUI::openCombineArchive(const std::string & fileName, const SedmlImportOptions * pOptions)
{
  mRunningThreads["openCombineArchive"].pProgressBar = CProgressBar::create();
  mRunningThreads["openCombineArchive"].success = false;

  mFileName = fileName;

  if (pOptions)
    mOptions = *pOptions;
  else
    mOptions = SedmlImportOptions();

  CQThread *pThread = new CQThread(this, &DataModelGUI::openCombineArchiveRun);
  connect(pThread, SIGNAL(finished()), this, SLOT(openCombineArchiveFinished()));
  mRunningThreads["openCombineArchive"].pThread = pThread;
  pThread->start();
}

void DataModelGUI::exportCombineArchive(const std::string & fileName, bool overwriteFile)
{
  mRunningThreads["exportCombineArchive"].pProgressBar = CProgressBar::create();
  mRunningThreads["exportCombineArchive"].success = false;

  mFileName = fileName;
  mOverWrite = overwriteFile;

  CQThread *pThread = new CQThread(this, &DataModelGUI::exportCombineArchiveRun);
  connect(pThread, SIGNAL(finished()), this, SLOT(exportCombineFinished()));
  mRunningThreads["exportCombineArchive"].pThread = pThread;
  pThread->start();
}

void DataModelGUI::openCombineArchiveRun()
{
  try
    {
      assert(mpDataModel != NULL);
      mRunningThreads["openCombineArchive"].success = mpDataModel->openCombineArchive(mFileName, mRunningThreads["openCombineArchive"].pProgressBar, true, &mOptions);
    }

  catch (...)
    {
      mRunningThreads["openCombineArchive"].success = false;
    }
}

void DataModelGUI::exportCombineArchiveRun()
{
  try
    {
      assert(mpDataModel != NULL);
      mRunningThreads["exportCombineArchive"].success =
        mpDataModel->exportCombineArchive(mFileName,
                                          true,
                                          true,
                                          true,
                                          true,
                                          mOverWrite,
                                          mRunningThreads["exportCombineArchive"].pProgressBar);
    }

  catch (...)
    {
      mRunningThreads["exportCombineArchive"].success = false;
    }
}

void DataModelGUI::openCombineArchiveFinished()
{
  if (mRunningThreads["openCombineArchive"].success)
    {

      mpOutputHandlerPlot->setOutputDefinitionVector(mpDataModel->getPlotDefinitionList());
      linkDataModelToGUI();
    }

  disconnect(mRunningThreads["openCombineArchive"].pThread, SIGNAL(finished()), this, SLOT(openCombineArchiveFinished()));
  threadFinished("openCombineArchive");
}

void DataModelGUI::exportCombineFinished()
{
  disconnect(mRunningThreads["exportCombineArchive"].pThread, SIGNAL(finished()), this, SLOT(exportSBMLFinished()));
  threadFinished("exportCombineArchive");
}

void DataModelGUI::importSEDML(const std::string & fileName, const SedmlImportOptions * pOptions)
{
  mRunningThreads["importSEDML"].pProgressBar = CProgressBar::create();
  mRunningThreads["importSEDML"].success = false;

  mFileName = fileName;

  if (pOptions)
    mOptions = *pOptions;
  else
    mOptions = SedmlImportOptions();

  CQThread *pThread = new CQThread(this, &DataModelGUI::importSEDMLRun);
  connect(pThread, SIGNAL(finished()), this, SLOT(importSEDMLFinished()));
  mRunningThreads["importSEDML"].pThread = pThread;
  pThread->start();
}

void DataModelGUI::importSEDMLRun()
{
  try
    {
      assert(mpDataModel != NULL);
      mRunningThreads["importSEDML"].success = mpDataModel->importSEDML(mFileName, mRunningThreads["importSEDML"].pProgressBar, false, &mOptions);
    }

  catch (...)
    {
      mRunningThreads["importSEDML"].success = false;
    }
}

void DataModelGUI::importSEDMLFinished()
{
  if (mRunningThreads["importSEDML"].success)
    {
      addRecentFile(mFileName);
      mpOutputHandlerPlot->setOutputDefinitionVector(mpDataModel->getPlotDefinitionList());
      linkDataModelToGUI();
    }

  disconnect(mRunningThreads["importSEDML"].pThread, SIGNAL(finished()), this, SLOT(importSEDMLFinished()));
  threadFinished("importSEDML");
}

void DataModelGUI::exportSEDML(const std::string & fileName, bool overwriteFile, int sedmlLevel, int sedmlVersion, bool exportIncomplete, bool exportCOPASIMIRIAM)
{
  mRunningThreads["exportSEDML"].pProgressBar = CProgressBar::create();
  mRunningThreads["exportSEDML"].success = false;

  mFileName = fileName;
  mOverWrite = overwriteFile;
  mSEDMLLevel = sedmlLevel;
  mSEDMLVersion = sedmlVersion;
  mSEDMLExportIncomplete = exportIncomplete;
  mSEDMLExportCOPASIMIRIAM = exportCOPASIMIRIAM;

  CQThread *pThread = new CQThread(this, &DataModelGUI::exportSEDMLRun);
  connect(pThread, SIGNAL(finished()), this, SLOT(exportSEDMLFinished()));
  mRunningThreads["exportSEDML"].pThread = pThread;
  pThread->start();
}

void DataModelGUI::exportSEDMLFinished()
{
  if (mRunningThreads["exportSEDML"].success)
    {
      addRecentFile(mFileName);
    }

  disconnect(mRunningThreads["exportSEDML"].pThread, SIGNAL(finished()), this, SLOT(exportSEDMLFinished()));
  threadFinished("exportSEDML");
}

void DataModelGUI::exportSEDMLToString(std::string & sedmlDocumentText)
{
  mRunningThreads["exportSEDMLToString"].pProgressBar = CProgressBar::create();
  mRunningThreads["exportSEDMLToString"].success = false;

  mpSEDMLExportString = & sedmlDocumentText;

  CQThread *pThread = new CQThread(this, &DataModelGUI::exportSEDMLToStringRun);
  connect(pThread, SIGNAL(finished()), this, SLOT(exportSEDMLToStringFinished()));
  mRunningThreads["exportSEDMLToString"].pThread = pThread;
  pThread->start();
}

void DataModelGUI::exportSEDMLToStringRun()
{
  try
    {
      assert(mpDataModel != NULL);
      *mpSEDMLExportString = mpDataModel->exportSEDMLToString(mRunningThreads["exportSEDMLToString"].pProgressBar, 1, 1);
      mRunningThreads["exportSEDMLToString"].success = true;
    }

  catch (...)
    {
      mRunningThreads["exportSEDMLToString"].success = false;
    }
}

void DataModelGUI::exportSEDMLToStringFinished()
{
  disconnect(mRunningThreads["exportSEDMLToString"].pThread, SIGNAL(finished()), this, SLOT(exportSEDMLToStringFinished()));
  threadFinished("exportSEDMLToString");
}

void DataModelGUI::exportSEDMLRun()
{
  try
    {
      assert(mpDataModel != NULL);
      mRunningThreads["exportSEDML"].success = mpDataModel->exportSEDML(mFileName, mOverWrite, mSEDMLLevel, mSEDMLVersion, mSEDMLExportIncomplete, mSEDMLExportCOPASIMIRIAM, nullptr);
    }

  catch (...)
    {
      mRunningThreads["exportSEDML"].success = false;
    }
}

void DataModelGUI::saveConfiguration(bool saveMIRIAM)
{
  mSaveMIRIAM = saveMIRIAM;

  CQThread *pThread = new CQThread(this, &DataModelGUI::saveConfigurationRun);
  connect(pThread, SIGNAL(finished()), this, SLOT(slotSaveConfigurationFinished()));
  mRunningThreads["saveConfiguration"].pThread = pThread;
  mRunningThreads["saveConfiguration"].success = false;

  pThread->start();
}

void DataModelGUI::saveConfigurationRun()
{
  try
    {
      mRunningThreads["saveConfiguration"].success = CRootContainer::getConfiguration()->save(mSaveMIRIAM);
    }

  catch (...)
    {
      mRunningThreads["saveConfiguration"].success = false;
    }
}

void DataModelGUI::slotSaveConfigurationFinished()
{
  disconnect(mRunningThreads["saveConfiguration"].pThread, SIGNAL(finished()), this, SLOT(slotSaveConfigurationFinished()));
  threadFinished("saveConfiguration");
}
