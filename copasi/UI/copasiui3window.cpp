// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/copasiui3window.cpp,v $
//   $Revision: 1.311 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/03/16 15:32:11 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
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

#include <sbml/SBMLDocument.h>

#include <QEvent>
#include <QMenuBar>
#include <QTimer>
#include <QComboBox>
#include <QToolBar>
#include <QTextEdit>
#include <QThread>
#include <QFontDialog>

#include <vector>
#include <sstream>

#ifdef COPASI_SBW_INTEGRATION
#include <stdlib.h>
#endif // COPASI_SBW_INTEGRATION

#include "AboutDialog.h"
#include "CopasiFileDialog.h"
#include "copasiui3window.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "ObjectBrowserDialog.h"
#include "qtUtilities.h"
#include "SliderDialog.h"
#include "CQMessageBox.h"
#include "CQPreferenceDialog.h"
#include "CQSBMLFileDialog.h"
#include "copasi/UI/qtUtilities.h"
#include "copasiWidget.h"
#include "TaskWidget.h"
#include "resourcesUI/CQIconResource.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "utilities/CCopasiException.h"
#include "utilities/CDirEntry.h"
#include "model/CModel.h"
#include "commandline/COptionParser.h"
#include "commandline/COptions.h"
#include "commandline/CConfigurationFile.h"
#include "commandline/CLocaleString.h"
#include "wizard/wizard.h"
#include "report/CKeyFactory.h"
#include "sbml/SBMLIncompatibility.h"
#include "MIRIAM/CConstants.h"
#include "copasi/utilities/CVersion.h"
#include "model/CModelExpansion.h"
#ifdef WITH_MERGEMODEL
#include "model/CModelMerging.h"
#endif
#include "model/CModelExpansion.h"

#define AutoSaveInterval 10*60*1000

#ifdef DEBUG_UI
#include <QtDebug>
#endif

// static
CopasiUI3Window * CopasiUI3Window::pMainWindow = NULL;

// static
CopasiUI3Window * CopasiUI3Window::getMainWindow()
{
  return pMainWindow;
}

// static
CopasiUI3Window * CopasiUI3Window::create()
{
  CopasiUI3Window * pWindow = NULL;

  pWindow = new CopasiUI3Window;

#ifdef COPASI_SBW_INTEGRATION

  if (pWindow != NULL &&
      COptions::compareValue("SBWRegister", true))
    {
      pWindow->sbwConnect();
      pWindow->sbwRegister();
    }

#endif // COPASI_SBW_INTEGRATION

  pMainWindow = pWindow;

  return pWindow;
}

/**
 *  Constructs a CopasiUI window which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *  @param parent The widget which this window is a child of.
 *  @param name The object name is a text that can be used to identify
 *  this QObject. It's particularly useful in conjunction with the Qt Designer.
 *  You can find an object by name (and type) using child(), and more than one
 *  using queryList().
 *  @param flags Flags for this widget. Refer Qt::WidgetFlags of Qt documentation
 *  for more information about these flags.
 */
CopasiUI3Window::CopasiUI3Window():
    QMainWindow(),
    mpDataModelGUI(NULL),
    mpListView(NULL),
    mpBoxSelectFramework(NULL),
    mpSliders(NULL),
    mpObjectBrowser(NULL),
    mSaveAsRequired(true),
    mpAutoSaveTimer(NULL),
    mSuspendAutoSave(false),
    mpMenuExamples(NULL),
    mpMenuRecentFiles(NULL),
    mRecentFilesActionMap(),
    mpRecentFilesActionGroup(NULL),
    mpMenuRecentSBMLFiles(NULL),
    mRecentSBMLFilesActionMap(),
    mpRecentSBMLFilesActionGroup(NULL),
    mpMIRIAMResources(NULL),
    mpMainThread(QThread::currentThread()),
    mNewFile(),
    mCommitRequired(true),
    mQuitApplication(false),
    mSliderDialogEnabled(false),
    mWindows()

#ifdef COPASI_SBW_INTEGRATION
    , mpSBWModule(NULL)
    , mSBWAnalyzerModules()
    , mSBWAnalyzerServices()
    , mSBWActionMap()
    , mpSBWActionGroup(NULL)
    , mpSBWMenu(NULL)
    , mpSBWAction(NULL)
    , mSBWIgnoreShutdownEvent(true)
#endif // COPASI_SBW_INTEGRATION
{
  // set destructive close
  this->setAttribute(Qt::WA_DeleteOnClose);

#ifndef Darwin
  setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
#endif // not Darwin

  // Set the window caption/title
  FixedTitle = "COPASI ";
  FixedTitle += FROM_UTF8(CVersion::VERSION.getVersion());
  updateTitle();

  createActions();
  createToolBar(); // creates a tool bar
  createMenuBar();  // creates a menu bar

  setIconSize(QSize(18, 20));

  mpaSave->setEnabled(false);
  mpaSaveAs->setEnabled(false);
  mpaExportSBML->setEnabled(false);
  mpaExportODE->setEnabled(false);

  if (!mpDataModelGUI)
    {
      // create the data model
      mpDataModelGUI = new DataModelGUI(this);
    }

  mpListView = new ListViews(this);

  connect(mpListView, SIGNAL(signalFolderChanged(const QModelIndex &)), this, SLOT(listViewsFolderChanged(const QModelIndex &)));

  mpDataModelGUI->registerListView(mpListView);
  mpListView->show();
  this->setCentralWidget(mpListView);

  //create sliders window
  this->mpSliders = new SliderDialog(NULL);
  this->mpSliders->setParentWindow(this);
  size_t id = mpListView->getCurrentItemId();
  this->mpSliders->setCurrentFolderId(id);
  this->mpSliders->resize(320, 350);
  this->mSliderDialogEnabled = this->mpSliders->isEnabled();

  resize(800, 600);
  show();

  mpListView->switchToOtherWidget(0, "");

  // Assure that the changed flag is still false;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  (*CCopasiRootContainer::getDatamodelList())[0]->changed(false);
  this->mpSliders->setChanged(false);

  mpAutoSaveTimer = new QTimer(this);
  mpAutoSaveTimer->start(AutoSaveInterval); // every 10 minutes

  // TODO CRITICAL We need to disable autosave to avoid race conditions.
  // connect(mpAutoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSave()));
  // mpDataModelGUI->notify(ListViews::FUNCTION, ListViews::ADD, "");

  setApplicationFont();

  // drop acceptance
  setAcceptDrops(true);
}

CopasiUI3Window::~CopasiUI3Window()
{
#ifdef COPASI_SBW_INTEGRATION
  sbwDisconnect();
#endif // COPASI_SBW_INTEGRATION

  pdelete(mpListView);
  pdelete(mpDataModelGUI);

  QList< QMainWindow * >::iterator it = mWindows.begin();
  QList< QMainWindow * >::iterator end = mWindows.end();

  for (; it != end; ++it)
    {
      (*it)->close();
    }
}

void CopasiUI3Window::createActions()
{
  //TODO: use the QKeySequence standard shortcuts
  //TODO: add tool tips, status tips etc.

  mpaNew = new QAction(CQIconResource::icon(CQIconResource::fileNew), "&New", this);
  connect(mpaNew, SIGNAL(activated()), this, SLOT(newDoc()));
  mpaNew->setShortcut(Qt::CTRL + Qt::Key_N);

  mpaOpen = new QAction(CQIconResource::icon(CQIconResource::fileOpen), "&Open...", this);
  connect(mpaOpen, SIGNAL(activated()), this, SLOT(slotFileOpen()));
  mpaOpen->setShortcut(Qt::CTRL + Qt::Key_O);

  mpaOpenCopasiFiles = new QAction(CQIconResource::icon(CQIconResource::fileOpen), "COP&ASI Files...", this);
  connect(mpaOpenCopasiFiles, SIGNAL(activated()), this, SLOT(slotFileExamplesCopasiFiles()));
  mpaOpenCopasiFiles->setShortcut(Qt::CTRL + Qt::Key_A);

  mpaOpenSBMLFiles = new QAction(CQIconResource::icon(CQIconResource::fileOpen), "S&BML Files...", this);
  connect(mpaOpenSBMLFiles, SIGNAL(activated()), this, SLOT(slotFileExamplesSBMLFiles()));
  mpaOpenSBMLFiles->setShortcut(Qt::CTRL + Qt::Key_B);

  mpaSave = new QAction(CQIconResource::icon(CQIconResource::fileSave), "&Save", this);
  connect(mpaSave, SIGNAL(activated()), this, SLOT(slotFileSave()));
  mpaSave->setShortcut(Qt::CTRL + Qt::Key_S);

  mpaSaveAs = new QAction(CQIconResource::icon(CQIconResource::fileSaveas), "Save &As...", this);
  connect(mpaSaveAs, SIGNAL(activated()), this, SLOT(slotFileSaveAs()));
  mpaSaveAs->setShortcut(Qt::SHIFT + Qt::CTRL + Qt::Key_S);

  mpaImportSBML = new QAction(CQIconResource::icon(CQIconResource::fileOpen), "&Import SBML...", this);
  connect(mpaImportSBML, SIGNAL(activated()), this, SLOT(slotImportSBML()));
  mpaImportSBML->setShortcut(Qt::CTRL + Qt::Key_I);

  mpaExportSBML = new QAction(CQIconResource::icon(CQIconResource::fileExport), "&Export SBML...", this);
  connect(mpaExportSBML, SIGNAL(activated()), this, SLOT(slotExportSBML()));
  mpaExportSBML->setShortcut(Qt::CTRL + Qt::Key_E);

  mpaExportODE = new QAction(CQIconResource::icon(CQIconResource::fileExport), "Export ODEs...", this);
  connect(mpaExportODE, SIGNAL(activated()), this, SLOT(slotExportMathModel()));
  mpaExportODE->setShortcut(Qt::CTRL + Qt::Key_M);

  mpaQuit = new QAction("&Quit", this);
  connect(mpaQuit, SIGNAL(activated()), this, SLOT(slotQuit()));
  mpaQuit->setShortcut(Qt::CTRL + Qt::Key_Q);

  mpaSliders = new QAction(CQIconResource::icon(CQIconResource::slider), "Show sliders", this);
  mpaSliders->setCheckable(true);
  connect(mpaSliders, SIGNAL(toggled(bool)), this, SLOT(slotShowSliders(bool)));

  mpaObjectBrowser = new QAction("Object &Browser", this);
  mpaObjectBrowser->setCheckable(true);
  connect(mpaObjectBrowser, SIGNAL(toggled(bool)), this, SLOT(slotShowObjectBrowserDialog(bool)));

  mpaCheckModel = new QAction(CQIconResource::icon(CQIconResource::checkMark), "Check model", this);
  connect(mpaCheckModel, SIGNAL(activated()), this, SLOT(slotCheckModel()));

  mpaUpdateMIRIAM = new QAction(CQIconResource::icon(CQIconResource::miriam), "Update MIRIAM", this);
  connect(mpaUpdateMIRIAM, SIGNAL(activated()), this, SLOT(slotUpdateMIRIAM()));

  mpaApplyInitialState = new QAction(CQIconResource::icon(CQIconResource::isToS), "Apply initial state", this);
  connect(mpaApplyInitialState, SIGNAL(activated()), this, SLOT(slotApplyInitialState()));

  mpaUpdateInitialState = new QAction(CQIconResource::icon(CQIconResource::sToIs), "Update initial state from current state", this);
  connect(mpaUpdateInitialState, SIGNAL(activated()), this, SLOT(slotUpdateInitialState()));

  mpaCapture = new QAction(CQIconResource::icon(CQIconResource::captureImage), "Capture the main window", this);
  connect(mpaCapture, SIGNAL(activated()), this, SLOT(slotCapture()));

  mpaExpandModel = new QAction("Create array of compartments (debug version)", this);
  connect(mpaExpandModel, SIGNAL(activated()), this, SLOT(slotExpandModel()));

  mpaFontSelectionDialog = new QAction("Select the Application Font", this);
  connect(mpaFontSelectionDialog, SIGNAL(activated()), this, SLOT(slotFontSelection()));

  //     QAction* mpaObjectBrowser;

#ifdef WITH_MERGEMODEL
  mpaAddModel = new QAction(CQIconResource::icon(CQIconResource::fileAdd), "&Add ...", Qt::SHIFT + Qt::CTRL + Qt::Key_A, this, "addmodel");
  connect(mpaAddModel, SIGNAL(activated()), this, SLOT(slotAddFileOpen()));

  mpaMergeModels = new QAction("&Merge ...", Qt::SHIFT + Qt::CTRL + Qt::Key_M, this, "mergemodel");
  connect(mpaMergeModels, SIGNAL(activated()), this, SLOT(slotMergeModels()));
#endif
}

void CopasiUI3Window::createToolBar()
{
  QToolBar * tb = addToolBar("MainToolBar");

  tb->addAction(mpaNew);
  tb->addAction(mpaOpen);
  tb->addAction(mpaSave);
  tb->addAction(mpaCapture);
  tb->addAction(mpaSliders);
  tb->addAction(mpaCheckModel);
  tb->addAction(mpaApplyInitialState);
  tb->addAction(mpaUpdateInitialState);
  tb->addAction(mpaUpdateMIRIAM);

#ifdef WITH_MERGEMODEL
  tb->addAction(mpaAddModel);
  //tb->addAction(mpaMergeModels);
#endif

  tb->addSeparator();

  mpBoxSelectFramework = new QComboBox(tb);
  QStringList items;
  items << "Concentrations" << "Particle Numbers";
  mpBoxSelectFramework->addItems(items);
  tb->addWidget(mpBoxSelectFramework);

  connect(mpBoxSelectFramework, SIGNAL(activated(int)), this, SLOT(slotFrameworkChanged(int)));
}

void CopasiUI3Window::createMenuBar()
{

  QMenu * pFileMenu = menuBar()->addMenu("&File");

  pFileMenu->addAction(mpaNew);
  pFileMenu->addAction(mpaOpen);

  mpMenuExamples = pFileMenu->addMenu("Examples");
  mpMenuExamples->addAction(mpaOpenCopasiFiles);
  mpMenuExamples->addAction(mpaOpenSBMLFiles);

  pFileMenu->addAction(mpaSave);
  pFileMenu->addAction(mpaSaveAs);

  pFileMenu->addSeparator();

  pFileMenu->addAction(mpaImportSBML);
  pFileMenu->addAction(mpaExportSBML);
  pFileMenu->addAction(mpaExportODE);

#ifdef WITH_MERGEMODEL
  pFileMenu->addAction(mpaAddModel);
  //pFileMenu->addAction(mpaMergeModels);
#endif

  pFileMenu->addSeparator();

  mpMenuRecentFiles = pFileMenu->addMenu("Recent Files");
  refreshRecentFileMenu();

  mpMenuRecentSBMLFiles = pFileMenu->addMenu("Recent SBML Files");
  refreshRecentSBMLFileMenu();

  pFileMenu->addSeparator();

  pFileMenu->addAction(mpaQuit);

  //****** tools menu **************

  mpTools = menuBar()->addMenu("&Tools");

  mpTools->addAction(mpaApplyInitialState);
  mpTools->addAction(mpaUpdateInitialState);
  mpTools->addAction(mpaSliders);
  mpTools->addAction(mpaCapture);
#ifdef WITH_MERGEMODEL
  mpTools->addAction(mpaMergeModels);
#endif

  mpTools->addSeparator();
#ifdef COPASI_DEBUG
  mpTools->addAction(mpaObjectBrowser);
  mpTools->addAction(mpaExpandModel);
  mpTools->addSeparator();
#endif // COPASI_DEBUG

  mpTools->addAction(mpaCheckModel);
  mpTools->addAction("&Convert to irreversible", this, SLOT(slotConvertToIrreversible()));

#ifdef COPASI_SBW_INTEGRATION
  // create and populate SBW menu
  mpSBWMenu = new QMenu("&SBW", this);
  mpSBWAction = mpTools->addMenu(mpSBWMenu);
#endif // COPASI_SBW_INTEGRATION

  mpTools->addSeparator();
  mpTools->addAction(mpaUpdateMIRIAM);
  mpTools->addAction("&Preferences", this, SLOT(slotPreferences()));
  mpTools->addAction(mpaFontSelectionDialog);

  //*******  help menu *****************

  menuBar()->addSeparator();

  QMenu * help = menuBar()->addMenu("&Help");

  help->addAction("Simple &Wizard", this, SLOT(slotTutorialWizard()));
  help->addSeparator();
  help->addAction("&About", this, SLOT(about()), Qt::Key_F1);
  help->addAction("&License", this, SLOT(license()));
  help->addAction("About &Qt", this, SLOT(aboutQt()));
  help->addSeparator();
  // help->addAction("What's &This", this, SLOT(whatsThis()), Qt::SHIFT + Qt::Key_F1);
}

//***** Slots ***************************

void CopasiUI3Window::slotFileSaveAs(QString str)
{
  mpDataModelGUI->commit();

  C_INT32 Answer = QMessageBox::No;
  QString tmp;

  if (str.isEmpty()) str = "untitled.cps";

#ifdef DEBUG_UI
  qDebug() << "Filename on slotFileSaveAs = " << str;
#endif

  while (Answer == QMessageBox::No)
    {
      tmp =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                          str, "COPASI Files (*.cps)",
                                          "Choose a filename to save under");

      if (tmp.isEmpty()) return;

#ifdef DEBUG_UI
      qDebug() << "tmp = " << tmp;
#endif

      // Checks whether the file exists
      Answer = checkSelection(tmp);

      if (Answer == QMessageBox::Cancel) return;
    }

  if (mpDataModelGUI && !tmp.isNull())
    {
      setCursor(Qt::WaitCursor);

      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotFileSaveFinished(bool)));
      mpDataModelGUI->saveModel(TO_UTF8(tmp), true);
    }
}

void CopasiUI3Window::slotFileSaveFinished(bool success)
{
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotFileSaveFinished(bool)));

  if (success)
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      (*CCopasiRootContainer::getDatamodelList())[0]->changed(false);
      this->mpSliders->setChanged(false);
      updateTitle();

      CCopasiMessage msg = CCopasiMessage::getLastMessage();

      if (msg.getNumber() != MCCopasiMessage + 1)
        {
          QString Message("Problem while saving file!\n\n");
          Message += FROM_UTF8(msg.getText());

          msg = CCopasiMessage::getLastMessage();

          while (msg.getNumber() != MCCopasiMessage + 1)
            {
              Message += "\n";
              Message += FROM_UTF8(msg.getText());
              msg = CCopasiMessage::getLastMessage();
            }

          CQMessageBox::warning(this, QString("File Warning"), Message,
                                QMessageBox::Ok, QMessageBox::Ok);
        }

    }
  else
    {
      if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        {
          CQMessageBox::critical(this, "Save File Error",
                                 CCopasiMessage::getAllMessageText().c_str(),
                                 QMessageBox::Ok | QMessageBox::Default,
                                 QMessageBox::NoButton);
          CCopasiMessage::clearDeque();
        }
    }

  unsetCursor();
  refreshRecentFileMenu();

  mSaveAsRequired = false;

  if (mNewFile != "")
    {
      emit signalLoadFile(mNewFile);
      mNewFile = "";
    }
}

void CopasiUI3Window::newDoc()
{
  disconnect(this, SIGNAL(signalLoadFile(QString)), this, SLOT(newDoc()));

  if (mCommitRequired)
    {
      mpDataModelGUI->commit();
    }

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  if (mpDataModelGUI && ((*CCopasiRootContainer::getDatamodelList())[0]->isChanged() || this->mpSliders->isChanged()))
    {
      switch (CQMessageBox::question(this, "COPASI",
                                     "The document contains unsaved changes\n"
                                     "Do you want to save the changes before exiting?",
                                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                     QMessageBox::Save))
        {
          case QMessageBox::Save:
            connect(this, SIGNAL(signalLoadFile(QString)), this, SLOT(newDoc()));

            mNewFile = "newDoc()";
            mCommitRequired = false;
            slotFileSave();
            return;

            break;

          case QMessageBox::Discard:
            break;

          case QMessageBox::Cancel:
          default:
            return;
            break;
        }
    }

  mpDataModelGUI->notify(ListViews::MODEL, ListViews::DELETE,
                         (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getKey());

  mpListView->switchToOtherWidget(0, "");

  // delete the old sliders
  if (this->mpSliders) this->mpSliders->reset();

  mpDataModelGUI->createModel();
  this->mpSliders->setChanged(false);
  mpDataModelGUI->notify(ListViews::MODEL, ListViews::ADD, (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getKey());
  //if (!mbObject_browser_open)
  //mpFileMenu->setItemEnabled(nobject_browser, true);

  mpaSave->setEnabled(true);
  mpaSaveAs->setEnabled(true);
  mpaExportSBML->setEnabled(true);
  mpaExportODE->setEnabled(true);

  updateTitle();
  mpListView->switchToOtherWidget(1, "");
  mSaveAsRequired = true;
  mCommitRequired = true;
}

void CopasiUI3Window::openInitialDocument(const QString & file)
{
  if (file != "")
    {
      slotFileOpen(file);
    }
  else if (!COptions::compareValue("ImportSBML", std::string("")))
    {
      // Import the SBML File
      std::string ImportSBML;
      COptions::getValue("ImportSBML", ImportSBML);
      slotImportSBML(FROM_UTF8(ImportSBML));
    }
  else if (COptions::getNonOptions().size())
    {
      // Look at commandline
      slotFileOpen(FROM_UTF8(COptions::getNonOptions()[0]));
    }
  else
    {
      newDoc();
    }

#ifdef COPASI_SBW_INTEGRATION
  sbwConnect();
#endif // COPASI_SBW_INTEGRATION
}

void CopasiUI3Window::slotFileOpen(QString file)
{
  disconnect(this, SIGNAL(signalLoadFile(QString)), this, SLOT(slotFileOpen(QString)));

  if (mCommitRequired)
    {
      mpDataModelGUI->commit();
    }

  QString newFile = "";

  if (file == "")
    newFile =
      CopasiFileDialog::getOpenFileName(this, "Open File Dialog", QString::null,
                                        "COPASI Files (*.gps *.cps);;All Files (*)",
                                        "Choose a file");
  else
    newFile = file;

  // gives the file information to the datamodel to handle it

  if (!newFile.isNull())
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

      if (mpDataModelGUI && ((*CCopasiRootContainer::getDatamodelList())[0]->isChanged() || this->mpSliders->isChanged()))
        {
          switch (CQMessageBox::question(this, "COPASI",
                                         "The document contains unsaved changes\n"
                                         "Do you want to save the changes before exiting?",
                                         QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                         QMessageBox::Save))
            {
              case QMessageBox::Save:
                connect(this, SIGNAL(signalLoadFile(QString)), this, SLOT(slotFileOpen(QString)));

                mNewFile = newFile;
                mCommitRequired = false;
                slotFileSave();
                return;

                break;

              case QMessageBox::Discard:
                break;

              case QMessageBox::Cancel:
              default:
                return;
                break;
            }
        }

      mpDataModelGUI->notify(ListViews::MODEL, ListViews::DELETE,
                             (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getKey());

      mpListView->switchToOtherWidget(0, "");

      if (this->mpSliders) this->mpSliders->reset();

      this->setCursor(Qt::WaitCursor);

      CCopasiMessage::clearDeque();

      mNewFile = newFile;
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotFileOpenFinished(bool)));
      mpDataModelGUI->loadModel(TO_UTF8(newFile));
    }
}

void CopasiUI3Window::slotFileOpenFinished(bool success)
{
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotFileOpenFinished(bool)));
  unsetCursor();
  mCommitRequired = true;

  if (!success)
    {
      QString Message = "Error while loading file " + mNewFile + QString("!\n\n");
      Message += FROM_UTF8(CCopasiMessage::getAllMessageText(true));

      CQMessageBox::critical(this, QString("File Error"), Message,
                             QMessageBox::Ok, QMessageBox::Ok);
      mpDataModelGUI->createModel();
    }

  CCopasiMessage msg = CCopasiMessage::getLastMessage();

  if (msg.getNumber() != MCCopasiMessage + 1)
    {
      QString Message = "Problem while loading file " + mNewFile + QString("!\n\n");
      Message += FROM_UTF8(msg.getText());

      msg = CCopasiMessage::getLastMessage();

      while (msg.getNumber() != MCCopasiMessage + 1)
        {
          Message += "\n";
          Message += FROM_UTF8(msg.getText());
          msg = CCopasiMessage::getLastMessage();
        }

      CQMessageBox::warning(this, QString("File Warning"), Message,
                            QMessageBox::Ok, QMessageBox::Ok);
    }

  if (strcasecmp(CDirEntry::suffix(TO_UTF8(mNewFile)).c_str(), ".cps") == 0 &&
      CDirEntry::isWritable(TO_UTF8(mNewFile)))
    mSaveAsRequired = false;
  else
    mSaveAsRequired = true;

  if (!(*CCopasiRootContainer::getDatamodelList())[0]->getModel())
    {
      newDoc();
      mSaveAsRequired = true;
    }

  mpDataModelGUI->notify(ListViews::MODEL, ListViews::ADD,
                         (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getKey());

  mpaSave->setEnabled(true);
  mpaSaveAs->setEnabled(true);
  mpaExportSBML->setEnabled(true);
  mpaExportODE->setEnabled(true);

  updateTitle();
  mpListView->switchToOtherWidget(1, "");

  refreshRecentFileMenu();

  mNewFile = "";
}

void CopasiUI3Window::slotFileExamplesCopasiFiles(QString file)
{
  CopasiFileDialog::openExampleDir(); //Sets CopasiFileDialog::LastDir
  slotFileOpen(file);
}

void CopasiUI3Window::slotFileExamplesSBMLFiles(QString file)
{
  CopasiFileDialog::openExampleDir(); //Sets CopasiFileDialog::LastDir
  slotImportSBML(file);
}

#ifdef WITH_MERGEMODEL
void CopasiUI3Window::slotAddFileOpen(QString file)
{
  //DataModelGUI* mdataModel; // to keep track of temporary  data model..

  bool success = true;

  mpDataModelGUI->commit();

  if (!(*CCopasiRootContainer::getDatamodelList())[0]->getModel())
    {
      newDoc();
      mSaveAsRequired = true;
    }

  mpDataModelGUI->notify(ListViews::MODEL, ListViews::ADD,
                         (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getKey());

  QString newFile = "";

  if (file == "")
    newFile =
      CopasiFileDialog::getOpenFileName(this, "Open File Dialog", QString::null,
                                        "COPASI Files (*.gps *.cps);;All Files (*)",
                                        "Choose a file");
  else
    newFile = file;

  // gives the file information to the datamodel to handle it

  if (!newFile.isNull())
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

      mpListView->switchToOtherWidget(0, "");

      if (!mpDataModelGUI)
        mpDataModelGUI = new DataModelGUI(this); // create a new data model

      QCursor oldCursor = this->cursor();
      this->setCursor(Qt::WaitCursor);

      CCopasiMessage::clearDeque();

      try
        {
          success = mpDataModelGUI->addModel(TO_UTF8(newFile));
        }
      catch (...)
        {
          success = false;
        }

      setCursor(oldCursor);

      if (!success)
        {
          QString Message = "Error while loading file " + newFile + QString("!\n\n");
          Message += FROM_UTF8(CCopasiMessage::getLastMessage().getText());

          CQMessageBox::critical(this, QString("File Error"), Message,
                                 QMessageBox::Ok, QMessageBox::Ok);

          assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

          assert((*CCopasiRootContainer::getDatamodelList())[1]->newModel(NULL, NULL));
        }

      CCopasiMessage msg = CCopasiMessage::getLastMessage();

      if (msg.getNumber() != MCCopasiMessage + 1)
        {
          QString Message = "Problem while loading file " + newFile + QString("!\n\n");
          Message += FROM_UTF8(msg.getText());

          msg = CCopasiMessage::getLastMessage();

          while (msg.getNumber() != MCCopasiMessage + 1)
            {
              Message += "\n";
              Message += FROM_UTF8(msg.getText());
              msg = CCopasiMessage::getLastMessage();
            }

          CQMessageBox::warning(this, QString("File Warning"), Message,
                                QMessageBox::Ok, QMessageBox::Ok);
        }

      if (success)  slotAddModel();

      //(*CCopasiRootContainer::getDatamodelList())[1]->getModel()->cleanup();
      CCopasiRootContainer::removeDatamodel(1);

      mSaveAsRequired = true;

      mpaSave->setEnabled(true);
      mpaSaveAs->setEnabled(true);
      mpaExportSBML->setEnabled(true);
      mpaExportODE->setEnabled(true);

      updateTitle();
      mpListView->switchToOtherWidget(1, "");

      refreshRecentFileMenu();
    }
}

#endif

void CopasiUI3Window::slotFileSave()
{
  //  mpDataModelGUI->commit(); --> remove to the line after checking the following condition (07.04.08)

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  std::string FileName = (*CCopasiRootContainer::getDatamodelList())[0]->getFileName();

  if (mSaveAsRequired || FileName == "")
    {
      return slotFileSaveAs(FROM_UTF8(FileName));
    }

  mpDataModelGUI->commit();

  std::ifstream File(CLocaleString::fromUtf8(FileName).c_str());
  std::string Line;
  File >> Line;
  File.close();

  if (!Line.compare(0, 8, "Version=") ||
      strcasecmp(FileName.c_str(), ".gps") == 0)
    {
      /* Ask for permission to overwrite write? */
      /* If no call slotFileSaveAs */
      CQMessageBox MessageBox(QMessageBox::Question,
                              "Confirm File Version Update",
                              "You are to overwrite an existing Gepasi File.\n"
                              "This will render the file unreadable for Gepasi",
                              QMessageBox::Save | QMessageBox::Ok | QMessageBox::Cancel, this);

      MessageBox.setDefaultButton(QMessageBox::Save);
      MessageBox.button(QMessageBox::Save)->setText("Save As");
      MessageBox.button(QMessageBox::Save)->setText("Overwrite");

      int choice = MessageBox.exec();

      switch (choice)
        {
          case QMessageBox::Save:
            return slotFileSaveAs(FROM_UTF8(FileName));
            break;

          case QMessageBox::Ok:
            break;

          case QMessageBox::Cancel:
            return;
            break;
        }
    }

  if (mpDataModelGUI)
    {
      setCursor(Qt::WaitCursor);

      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotFileSaveFinished(bool)));
      mpDataModelGUI->saveModel(FileName, true);
    }
}

void CopasiUI3Window::slotQuit()
{
  if (!CopasiUI3Window::getMainWindow()->isEnabled())
    {
      CQMessageBox::information(this, "COPASI", "COPASI is currently executing tasks.\n"
                                "Please stop them first before closing COPASI.");
      return;
    }

  mQuitApplication = true;

  mpDataModelGUI->commit();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  if (mpDataModelGUI && ((*CCopasiRootContainer::getDatamodelList())[0]->isChanged() || this->mpSliders->isChanged()))
    {
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotQuitFinished(bool)));

      switch (CQMessageBox::question(this, "COPASI",
                                     "The document contains unsaved changes\n"
                                     "Do you want to save the changes before exiting?",
                                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                     QMessageBox::Save))
        {
          case QMessageBox::Save:
            slotFileSave();
            break;

          case QMessageBox::Discard:
            slotQuitFinished(true);
            break;

          case QMessageBox::Cancel:
          default:
            slotQuitFinished(false);
            break;
        }
    }
  else
    {
      slotQuitFinished(true);
    }
}

void CopasiUI3Window::slotQuitFinished(bool success)
{
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotQuitFinished(bool)));

  mQuitApplication &= success;

  if (mQuitApplication)
    {
      CleanUp();
      qApp->quit();
    }
}

void CopasiUI3Window::closeEvent(QCloseEvent* ce)
{
  // We handle this internally.
  ce->ignore();

  slotQuit();

  return;
}

// Cleanup all the temp .cps files created at runtime.
void CopasiUI3Window::CleanUp()
{
  std::string tempDir;
  COptions::getValue("Tmp", tempDir);

  CDirEntry::removeFiles("*.cps", tempDir);
  CDirEntry::remove(tempDir);
}

void CopasiUI3Window::slotFilePrint()
{}

void CopasiUI3Window::about()
{
  QString text =
    QString(AboutDialog::text).arg(FROM_UTF8(CVersion::VERSION.getVersion()));
  AboutDialog* aboutDialog = new AboutDialog(this, text, 76, 30);
  aboutDialog->setWindowTitle(FixedTitle);
  aboutDialog->exec();
}

void CopasiUI3Window::license()
{
  AboutDialog* aboutDialog = new AboutDialog(this, CCopasiRootContainer::getLicenseHTML(), 76, 30);
  aboutDialog->setWindowTitle(FixedTitle);
  aboutDialog->exec();
}

void CopasiUI3Window::aboutQt()
{
  QMessageBox::aboutQt(this, "Qt");
}

void CopasiUI3Window::slotShowObjectBrowserDialog(bool flag)
{

  if (flag /*tools->isItemEnabled(2)*/)
    {
      if (mpObjectBrowser)
        delete mpObjectBrowser;

      mpObjectBrowser = new ObjectBrowserDialog(this, 0, false, 1);
      connect(mpObjectBrowser, SIGNAL(destroyed(QObject *)), this, SLOT(slotObjectBrowserDialogWasClosed()));

      mpObjectBrowser->show();
    }
  else
    {
      if (mpObjectBrowser)
        mpObjectBrowser->hide();
    }
}

void CopasiUI3Window::slotObjectBrowserDialogWasClosed()
{
  mpObjectBrowser = NULL;
  mpaObjectBrowser->setChecked(false);
}

void CopasiUI3Window::slotPreferences()
{
  CQPreferenceDialog * preferenceDialog = new CQPreferenceDialog(this, 0, false);
  preferenceDialog->setAttribute(Qt::WA_DeleteOnClose);
  preferenceDialog->setModal(true);
  preferenceDialog->show();
}

void CopasiUI3Window::slotTutorialWizard()
{
  WizardDialog* tutorialWizard = new WizardDialog();
  tutorialWizard->setCopasiMainWindow(this);
  tutorialWizard->show();
}

void CopasiUI3Window::importSBMLFromString(const std::string& sbmlDocumentText)
{
  if (mCommitRequired)
    {
      mpDataModelGUI->commit();
    }

  if (!sbmlDocumentText.empty())
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

      if (mpDataModelGUI && ((*CCopasiRootContainer::getDatamodelList())[0]->isChanged() || this->mpSliders->isChanged()))
        {
          switch (CQMessageBox::question(this, "COPASI",
                                         "The document contains unsaved changes\n"
                                         "Do you want to save the changes before exiting?",
                                         QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                         QMessageBox::Save))
            {
              case QMessageBox::Save:
                mCommitRequired = false;
                slotFileSave();
                break;

              case QMessageBox::Discard:
                break;

              case QMessageBox::Cancel:
              default:
                return;
                break;
            }
        }

      mpDataModelGUI->notify(ListViews::MODEL, ListViews::DELETE,
                             (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getKey());

      mpListView->switchToOtherWidget(0, "");

      if (!mpDataModelGUI)
        {
          mpDataModelGUI = new DataModelGUI(this); // create a new data model
        }

      setCursor(Qt::WaitCursor);
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotImportSBMLFromStringFinished(bool)));

      mpDataModelGUI->importSBMLFromString(sbmlDocumentText);
    }
}

void CopasiUI3Window::slotImportSBMLFromStringFinished(bool success)
{
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotImportSBMLFromStringFinished(bool)));
  unsetCursor();
  mCommitRequired = true;

  if (!success)
    {
      QString Message = "Error while importing SBML model!\n\n";
      Message += FROM_UTF8(CCopasiMessage::getLastMessage().getText());

      CQMessageBox::critical(this, QString("Import Error"), Message,
                             QMessageBox::Ok, QMessageBox::Ok);
      CCopasiMessage::clearDeque();

      mpDataModelGUI->createModel();
    }

  /* still check for warnings.
   * Maybe events or rules were ignored while reading
   * the file.
   */
  if (success)
    {
      this->checkPendingMessages();
    }

  mpDataModelGUI->notify(ListViews::MODEL, ListViews::ADD,
                         (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getKey());

  //if (!bobject_browser_open)
  //       mpFileMenu->setItemEnabled(nsaveas_menu_id, true);
  //       msave_button->setEnabled(true);
  //       mpFileMenu->setItemEnabled(nsave_menu_id, true);

  mpListView->switchToOtherWidget(1, "");

  updateTitle();

  mSaveAsRequired = true;
}

void CopasiUI3Window::slotImportSBML(QString file)
{
  disconnect(this, SIGNAL(signalLoadFile(QString)), this, SLOT(slotImportSBML(QString)));

  if (mCommitRequired)
    {
      mpDataModelGUI->commit();
    }

  QString SBMLFile;

  if (file == "")
    SBMLFile =
      CopasiFileDialog::getOpenFileName(this, "Open File Dialog",
                                        QString::null, "XML Files (*.xml);;All Files (*)",
                                        "Choose a file");
  else
    SBMLFile = file;

  if (!SBMLFile.isNull())
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

      if (mpDataModelGUI && ((*CCopasiRootContainer::getDatamodelList())[0]->isChanged() || this->mpSliders->isChanged()))
        {
          switch (CQMessageBox::question(this, "COPASI",
                                         "The document contains unsaved changes\n"
                                         "Do you want to save the changes before exiting?",
                                         QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                         QMessageBox::Save))
            {
              case QMessageBox::Save:
                connect(this, SIGNAL(signalLoadFile(QString)), this, SLOT(slotImportSBML(QString)));

                mNewFile = SBMLFile;
                mCommitRequired = false;

                slotFileSave();
                return;
                break;

              case QMessageBox::Discard:
                break;

              case QMessageBox::Cancel:
              default:
                return;
                break;
            }
        }

      mpDataModelGUI->notify(ListViews::MODEL, ListViews::DELETE,
                             (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getKey());

      mpListView->switchToOtherWidget(0, "");

      if (this->mpSliders) this->mpSliders->reset();

      if (!mpDataModelGUI)
        {
          mpDataModelGUI = new DataModelGUI(this); // create a new data model
        }

      setCursor(Qt::WaitCursor);
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotImportSBMLFinished(bool)));

      mNewFile = SBMLFile;
      mpDataModelGUI->importSBML(TO_UTF8(SBMLFile));
    }
}

void CopasiUI3Window::slotImportSBMLFinished(bool success)
{
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotImportSBMLFinished(bool)));
  unsetCursor();
  mCommitRequired = true;

  if (!success)
    {
      QString Message = "Error while loading file " + mNewFile + QString("!\n\n");
      Message += FROM_UTF8(CCopasiMessage::getLastMessage().getText());

      CQMessageBox::critical(this, QString("File Error"), Message,
                             QMessageBox::Ok, QMessageBox::Ok);

      mpDataModelGUI->createModel();
    }
  else
    // We check in all case for warnings. This will help also for unsuccessful imports
    this->checkPendingMessages();

  mpDataModelGUI->notify(ListViews::MODEL, ListViews::ADD,
                         (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getKey());

  mpaSave->setEnabled(true);
  mpaSaveAs->setEnabled(true);
  mpaExportSBML->setEnabled(true);
  mpaExportODE->setEnabled(true);

  mpListView->switchToOtherWidget(1, "");

  refreshRecentSBMLFileMenu();

  updateTitle();

  mSaveAsRequired = true;

  mNewFile = "";
}

void CopasiUI3Window::slotExportSBML()
{
  mpDataModelGUI->commit();

  C_INT32 Answer = QMessageBox::No;
  QString tmp;
  bool exportIncomplete = false;
  int sbmlLevel = 2;
  int sbmlVersion = 4;

  while (Answer == QMessageBox::No)
    {
      QString Default = QString::null;
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

      if ((*CCopasiRootContainer::getDatamodelList())[0]->getFileName() != "")
        Default
        = FROM_UTF8(CDirEntry::dirName((*CCopasiRootContainer::getDatamodelList())[0]->getFileName())
                    + CDirEntry::Separator
                    + CDirEntry::baseName((*CCopasiRootContainer::getDatamodelList())[0]->getFileName())
                    + ".xml");
      else
        {
          Default = "untitled.xml";
        }

      // if there already is an SBML model, we present the user with the Level
      // and Version of that document as the selected Level and Version to
      // export to.
      if ((*CCopasiRootContainer::getDatamodelList())[0]->getCurrentSBMLDocument() != NULL)
        {
          sbmlLevel = (*CCopasiRootContainer::getDatamodelList())[0]->getCurrentSBMLDocument()->getLevel();
          sbmlVersion = (*CCopasiRootContainer::getDatamodelList())[0]->getCurrentSBMLDocument()->getVersion();
        }

      std::pair<QString, std::pair<unsigned C_INT32, unsigned C_INT32> > nameAndVersion =
        CQSBMLFileDialog::getSaveFileName(this, "Export SBML Dialog", Default,
                                          "Choose a filename and SBML version for SBML export.",
                                          sbmlLevel,
                                          sbmlVersion);
      tmp = nameAndVersion.first;
      sbmlLevel = nameAndVersion.second.first;
      sbmlVersion = nameAndVersion.second.second;

      if (tmp.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(tmp);

      if (Answer == QMessageBox::Cancel) return;
    }

  if (mpDataModelGUI && !tmp.isNull())
    {
      setCursor(Qt::WaitCursor);
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotExportSBMLFinished(bool)));
      mpDataModelGUI->exportSBML(TO_UTF8(tmp), true, sbmlLevel, sbmlVersion, exportIncomplete);
    }
}

void CopasiUI3Window::slotExportSBMLFinished(bool /* success */)
{
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotExportSBMLFinished(bool)));
  unsetCursor();

  checkPendingMessages();
  refreshRecentSBMLFileMenu();
}

void CopasiUI3Window::slotExportMathModel()
{
  mpDataModelGUI->commit();

  C_INT32 Answer = QMessageBox::No;
  QString tmp;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  QString *userFilter = new QString;

  while (Answer == QMessageBox::No)
    {
      QString Default = QString::null;

      if (pDataModel->getFileName() != "")
        Default
        = FROM_UTF8(CDirEntry::dirName(pDataModel->getFileName())
                    + CDirEntry::Separator
                    + CDirEntry::baseName(pDataModel->getFileName()));
      else
        Default = "untitled.c";

      tmp =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                          Default,
                                          "C Files (*.c);;Berkeley Madonna Files (*.mmd);;XPPAUT (*.ode)",
                                          "Choose an export format", userFilter);

      if (tmp.isEmpty()) return;

#ifdef DEBUG_UI
      qDebug() << "user's filter pointer = " << *userFilter;
#endif

      // Checks whether the file exists
      Answer = checkSelection(tmp);

      if (Answer == QMessageBox::Cancel) return;
    }

  if (mpDataModelGUI && !tmp.isNull())
    {
      setCursor(Qt::WaitCursor);
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotExportMathModelFinished(bool)));
      mpDataModelGUI->exportMathModel(TO_UTF8(tmp), TO_UTF8(*userFilter), true);
    }
}

void CopasiUI3Window::slotExportMathModelFinished(bool success)
{
  unsetCursor();
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotExportMathModelFinished(bool)));

  if (!success &&
      CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
    {
      CQMessageBox::critical(this, "Export Error",
                             CCopasiMessage::getAllMessageText().c_str(),
                             QMessageBox::Ok | QMessageBox::Default,
                             QMessageBox::NoButton);
      CCopasiMessage::clearDeque();
    }

}

void CopasiUI3Window::slotConvertToIrreversible()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CModel* model = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  if (!model) return;

  mpDataModelGUI->commit();
  mpListView->switchToOtherWidget(114, "");

  CCopasiMessage::clearDeque();

  if (!model->convert2NonReversible())
    {
      // Display error messages.
      CQMessageBox::information(this, "Conversion Failed",
                                CCopasiMessage::getAllMessageText().c_str(),
                                QMessageBox::Ok | QMessageBox::Default,
                                QMessageBox::NoButton);
      CCopasiMessage::clearDeque();
    }

  mpDataModelGUI->notify(ListViews::MODEL, ListViews::CHANGE, "");
}

void CopasiUI3Window::slotShowSliders(bool flag)
{
  mpaSliders->setChecked(flag);
  this->mpSliders->setHidden(!flag);
}

DataModelGUI* CopasiUI3Window::getDataModel()
{return mpDataModelGUI;}

void CopasiUI3Window::listViewsFolderChanged(const QModelIndex &)
{
  size_t id = mpListView->getCurrentItemId();
  this->mpSliders->setCurrentFolderId(id);
}

ListViews* CopasiUI3Window::getMainWidget()
{
  return mpListView;
}

void CopasiUI3Window::checkPendingMessages()
{
  CCopasiMessage msg_pending = CCopasiMessage::getLastMessage();

  if (msg_pending.getNumber() != MCCopasiMessage + 1)
    {
      QString text;
      QString filteredText;
      unsigned int numMessages = 0;
      unsigned int numFilteredMessages = 0;

      while (msg_pending.getNumber() != MCCopasiMessage + 1)
        {
          if (msg_pending.getType() & 128)
            {
              ++numFilteredMessages;
              filteredText += "\n";
              filteredText += FROM_UTF8(msg_pending.getText());
            }
          else
            {
              ++numMessages;
              text += "\n";
              text += FROM_UTF8(msg_pending.getText());
            }

          msg_pending = CCopasiMessage::getLastMessage();
        }

      if (numFilteredMessages != 0)
        {
          if (text.isEmpty())
            text = "There were no serious issues encountered during the import of SBML. "
                   "However some minor issues have occurred, which can be viewed in the Minor "
                   "Issues tab.";

          CQMessageBox box(QMessageBox::Information,
                           QString("COPASI Message"), text, QMessageBox::Ok, this);
          box.setDefaultButton(QMessageBox::Ok);
          box.setFilteredText(filteredText);
          box.exec();
        }
      else
        {
          CQMessageBox::information(this, QString("COPASI Message"), text,
                                    QMessageBox::Ok, QMessageBox::Ok);
        }
    }
}

void CopasiUI3Window::updateTitle()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  QString FileName = FROM_UTF8((*CCopasiRootContainer::getDatamodelList())[0]->getFileName());

#ifdef WIN32 // Windows allows mixing of '/' and '\' as separator.
  FileName.replace("\\", "/");
#endif

  if (FileName.length() > 40)
    {
#ifdef WIN32
      QRegExp mask("^(([A-Z]:/)?[^/]+/).*(/[^/]+/[^/]+$)");
#else
      QRegExp mask("^((/*)[^/]+/).*(/[^/]+/[^/]+$)");
#endif

      mask.indexIn(FileName);
      FileName = mask.cap(1) + "..." + mask.cap(3);
    }

  std::string BaseName;

  if (!FileName.isEmpty())
    BaseName = CDirEntry::baseName(TO_UTF8(FileName)) + " - ";

  setWindowTitle(FROM_UTF8(BaseName) + FixedTitle + " " + FileName);
}

void CopasiUI3Window::autoSave()
{
  // TODO CRITICAL This needs to be moved into a sub thread so
  // that a progress dialog can be displayed and the user can interrupt.
  if (!mSuspendAutoSave)
    {
      mSuspendAutoSave = true;
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      (*CCopasiRootContainer::getDatamodelList())[0]->autoSave();
      mSuspendAutoSave = false;
    }

  mpAutoSaveTimer->setInterval(AutoSaveInterval); // restart the timer
}

void CopasiUI3Window::suspendAutoSave(const bool & suspend)
{
  mSuspendAutoSave = suspend;

  if (!mSuspendAutoSave)
    mpAutoSaveTimer->setInterval(AutoSaveInterval); // restart the timer
}

void CopasiUI3Window::slotOpenRecentFile(QAction * pAction)
{
  int index = mRecentFilesActionMap[pAction];

  std::string FileName =
    *CCopasiRootContainer::getConfiguration()->getRecentFiles().getGroup("Recent Files")->getValue(index).pSTRING;

  slotFileOpen(FROM_UTF8(FileName));
}

void CopasiUI3Window::slotOpenRecentSBMLFile(QAction * pAction)
{
  int index = mRecentSBMLFilesActionMap[pAction];

  std::string FileName =
    *CCopasiRootContainer::getConfiguration()->getRecentSBMLFiles().getGroup("Recent Files")->getValue(index).pSTRING;

  slotImportSBML(FROM_UTF8(FileName));
}

void CopasiUI3Window::refreshRecentFileMenu()
{
  mpMenuRecentFiles->clear();

  mRecentFilesActionMap.clear();

  if (mpRecentFilesActionGroup != NULL)
    {
      disconnect(mpRecentFilesActionGroup, SIGNAL(triggered(QAction *)), this, SLOT(slotOpenRecentFile(QAction *)));
      mpRecentFilesActionGroup->deleteLater();
      mpRecentFilesActionGroup = NULL;
    }

  mpRecentFilesActionGroup = new QActionGroup(this);
  connect(mpRecentFilesActionGroup, SIGNAL(triggered(QAction *)), this, SLOT(slotOpenRecentFile(QAction *)));

  QAction * pAction;

  CCopasiParameterGroup::index_iterator it =
    CCopasiRootContainer::getConfiguration()->getRecentFiles().getGroup("Recent Files")->beginIndex();
  CCopasiParameterGroup::index_iterator end =
    CCopasiRootContainer::getConfiguration()->getRecentFiles().getGroup("Recent Files")->endIndex();

  C_INT Index = 0;

  for (; it != end; ++it, ++Index)
    {
      pAction = new QAction(FROM_UTF8(*(*it)->getValue().pSTRING), mpRecentFilesActionGroup);
      mpMenuRecentFiles->addAction(pAction);
      mRecentFilesActionMap[pAction] = Index;
    }
}

void CopasiUI3Window::refreshRecentSBMLFileMenu()
{
  mpMenuRecentSBMLFiles->clear();

  mRecentSBMLFilesActionMap.clear();

  if (mpRecentSBMLFilesActionGroup != NULL)
    {
      disconnect(mpRecentSBMLFilesActionGroup, SIGNAL(triggered(QAction *)), this, SLOT(slotOpenRecentSBMLFile(QAction *)));
      mpRecentSBMLFilesActionGroup->deleteLater();
      mpRecentSBMLFilesActionGroup = NULL;
    }

  mpRecentSBMLFilesActionGroup = new QActionGroup(this);
  connect(mpRecentSBMLFilesActionGroup, SIGNAL(triggered(QAction *)), this, SLOT(slotOpenRecentSBMLFile(QAction *)));

  QAction * pAction;

  CCopasiParameterGroup::index_iterator it =
    CCopasiRootContainer::getConfiguration()->getRecentSBMLFiles().getGroup("Recent Files")->beginIndex();
  CCopasiParameterGroup::index_iterator end =
    CCopasiRootContainer::getConfiguration()->getRecentSBMLFiles().getGroup("Recent Files")->endIndex();

  C_INT Index = 0;

  for (; it != end; ++it, ++Index)
    {
      pAction = new QAction(FROM_UTF8(*(*it)->getValue().pSTRING), mpRecentSBMLFilesActionGroup);
      mpMenuRecentSBMLFiles->addAction(pAction);
      mRecentSBMLFilesActionMap[pAction] = Index;
    }
}

void CopasiUI3Window::exportSBMLToString(std::string & SBML)
{
  mpDataModelGUI->commit();

  if (mpDataModelGUI)
    {
      setCursor(Qt::WaitCursor);
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotExportSBMLToStringFinished(bool)));

      mpDataModelGUI->exportSBMLToString(SBML);
    }
}

void CopasiUI3Window::slotExportSBMLToStringFinished(bool success)
{
  unsetCursor();
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotExportSBMLToStringFinished(bool)));

  if (!success)
    {
      QString Message = "Error while exporting SBML model!\n\n";
      Message += FROM_UTF8(CCopasiMessage::getLastMessage().getText());

      CQMessageBox::critical(this, QString("File Error"), Message,
                             QMessageBox::Ok, QMessageBox::Ok);
      CCopasiMessage::clearDeque();
    }
}

QThread * CopasiUI3Window::getMainThread() const
{
  return mpMainThread;
}

void CopasiUI3Window::addWindow(QMainWindow * pWindow)
{
  mWindows.append(pWindow);
}

void CopasiUI3Window::removeWindow(QMainWindow * pWindow)
{
  mWindows.remove(pWindow);
}

#include "model/CModelAnalyzer.h"
void CopasiUI3Window::slotCheckModel()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CModelAnalyzer MA((*CCopasiRootContainer::getDatamodelList())[0]->getModel());

  std::ostringstream ss;
  // MA.writeReport(ss, true, false);
  MA.writeReport(ss, true, true);

  QTextEdit* pTE = new QTextEdit(FROM_UTF8(ss.str()));
  pTE->setReadOnly(true);
  pTE->resize(512, 640);
  pTE->show();
}

void CopasiUI3Window::slotUpdateMIRIAM()
{
  bool success = true;

  QCursor oldCursor = cursor();
  setCursor(Qt::WaitCursor);

  CCopasiMessage::clearDeque();

  if (!mpDataModelGUI)
    mpDataModelGUI = new DataModelGUI(this); // create a new data model

  try
    {
      success = mpDataModelGUI->updateMIRIAM(
                  CCopasiRootContainer::getConfiguration()->getRecentMIRIAMResources());
    }
  catch (...)
    {
      success = false;
    }

  if (!success)
    {
      setCursor(oldCursor);
      QString Message = "Error while updating MIRIAM" + QString("!\n\n");
      Message += FROM_UTF8(CCopasiMessage::getLastMessage().getText());
      CQMessageBox::critical(this, QString("MIRIAM Error"), Message,
                             QMessageBox::Ok, QMessageBox::Ok);
      CCopasiMessage::clearDeque();
    }

  /* still check for warnings.
   * Maybe events or rules were ignored while reading
   * the file.
   */
  if (success)
    {
      CCopasiRootContainer::getConfiguration()->save();
      CMIRIAMResourceObject::setMIRIAMResources(
        &CCopasiRootContainer::getConfiguration()->getRecentMIRIAMResources());
      mpDataModelGUI->updateMIRIAMResourceContents();
      this->checkPendingMessages();
    }

  CCopasiMessage::clearDeque();
  mpListView->switchToOtherWidget(0, "");
  setCursor(oldCursor);
}

void CopasiUI3Window::slotApplyInitialState()
{
  mpDataModelGUI->commit();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CModel *pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  if (pModel != NULL)
    {
      pModel->compileIfNecessary(NULL);
      pModel->applyInitialValues();
      pModel->updateNonSimulatedValues();

      mpDataModelGUI->notify(ListViews::STATE, ListViews::CHANGE, (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getKey());
    }
}

void CopasiUI3Window::slotUpdateInitialState()
{
  mpDataModelGUI->commit();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CModel *pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  if (pModel != NULL)
    {
      pModel->compileIfNecessary(NULL);
      pModel->setInitialState(pModel->getState());
      pModel->updateInitialValues();

      mpDataModelGUI->notify(ListViews::STATE, ListViews::CHANGE, (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getKey());
    }
}

void CopasiUI3Window::slotFrameworkChanged(int index)
{
  mpDataModelGUI->commit();

  mpDataModelGUI->setFramework(index);
  mpSliders->setFramework(index);
}

void CopasiUI3Window::slotCapture()
{
  QPixmap pixmap = QPixmap::grabWidget(mpListView->getCurrentWidget());

  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      fileName = CopasiFileDialog::getSaveFileName(this,
                 "Save File Dialog", "untitled.png", "PNG Files (*.png)", "Save Capture as PNG file");

      if (fileName.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  pixmap.save(fileName, "PNG");
}

void CopasiUI3Window::slotFontSelection()
{
  bool ok;

  QFont Font = QFontDialog::getFont(&ok, qApp->font(), this);

  if (ok)
    {
      qApp->setFont(Font);

      QString ApplicationFont = Font.family() + "; " + QString::number(Font.pointSize());
      CCopasiRootContainer::getConfiguration()->setApplicationFont(TO_UTF8(ApplicationFont));

      TaskWidget *pTaskWidget = dynamic_cast< TaskWidget * >(mpListView->getCurrentWidget());

      if (pTaskWidget != NULL)
        {
          pTaskWidget->adjustTable();
        }
    }

  return;
}

void CopasiUI3Window::setApplicationFont()
{
  std::string ApplicationFont = CCopasiRootContainer::getConfiguration()->getApplicationFont();

  if (ApplicationFont == "")
    {
      return;
    }

  QFont Font = qApp->font();
  QString qApplicationFont = Font.family() + "; " + QString::number(Font.pointSize());

  if (ApplicationFont == TO_UTF8(qApplicationFont))
    {
      // We are using the default
      CCopasiRootContainer::getConfiguration()->setApplicationFont("");
      return;
    }

  // The user has chosen another font
  QString FontFamily = FROM_UTF8(ApplicationFont);
  FontFamily.remove(QRegExp("; [0-9]*"));
  int FontSize = FROM_UTF8(ApplicationFont).remove(0, FontFamily.length() + 2).toInt();

  qApp->setFont(QFont(FontFamily, FontSize));
}

#include "UI/CQExpandModelData.h"
void CopasiUI3Window::slotExpandModel()
{

  CQExpandModelData *widget = new CQExpandModelData;
  widget->exec();

  mpDataModelGUI->notify(ListViews::MODEL, ListViews::CHANGE, "");
}

#ifdef WITH_MERGEMODEL

#include "UI/CQMergingData.h"
void CopasiUI3Window::slotAddModel()
{

  CModel *pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();
  CModel *mModel = (*CCopasiRootContainer::getDatamodelList())[1]->getModel();
  CModelAdd add(pModel, mModel);
  add.simpleCall();

  mpDataModelGUI->notify(ListViews::MODEL, ListViews::CHANGE, "");
}

void CopasiUI3Window::slotMergeModels()
{
  mpDataModelGUI->notify(ListViews::MODEL, ListViews::CHANGE, "");

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  CModel *pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  if (pModel->getMetabolites().size() == 0)
    CQMessageBox::critical(this, QString("File Error"),
                           QString("Error. Could not merge!"),
                           QMessageBox::Ok, QMessageBox::Ok);
  else
    {

      CQMergingData *widget = new CQMergingData;
      widget->exec();

      mpDataModelGUI->notify(ListViews::MODEL, ListViews::CHANGE, "");
    }
}
#endif

#ifdef COPASI_SBW_INTEGRATION
// Create 2 custom events, one containing the filename to an SBML document to be loaded
// into COPASI
CopasiUI3Window::QSBWSBMLEvent::QSBWSBMLEvent(const std::string & SBMLModel):
    QEvent((QEvent::Type)65433),
    mSBML(SBMLModel)
{}

const std::string & CopasiUI3Window::QSBWSBMLEvent::getSBMLModel() const
{return mSBML;}

CopasiUI3Window::QSBWShutdownEvent::QSBWShutdownEvent():
    QEvent((QEvent::Type)65434)
{}

void CopasiUI3Window::registerMethods(SystemsBiologyWorkbench::MethodTable< CopasiUI3Window > & table)
{
  table.addMethod(&CopasiUI3Window::sbwAnalysis,
                  "void doAnalysis(string)",
                  false,
                  "Imports a given SBML Model into CopasiUI.");

  table.addMethod(&CopasiUI3Window::sbwGetSBML,
                  "string getSBML()",
                  false,
                  "Retrieves the currently in CopasiUI loaded model in SBML format.");
}

//virtual
void CopasiUI3Window::onShutdown()
{
  QApplication::postEvent(this, new QSBWShutdownEvent());
}

void CopasiUI3Window::customEvent(QEvent * event)
{
  // handle the file event, that is import the SBML file
  switch ((int) event->type())
    {
      case 65433:

        try
          {
            QSBWSBMLEvent *sbwEvent = static_cast< QSBWSBMLEvent *>(event);
            importSBMLFromString(sbwEvent->getSBMLModel());
          }
        catch (...)
          {}

        break;

      case 65434:

        if (!mSBWIgnoreShutdownEvent)
          slotQuit();

        mSBWIgnoreShutdownEvent = true;
        break;
    }
}

void CopasiUI3Window::sbwConnect()
{
  pdelete(mpSBWModule);

  try
    {
      // Let us define how COPASI will look to the rest of SBW
      std::string FullName("COPASI " + CVersion::VERSION.getVersion());

      // By belonging to the Analysis category, we tell all other modules that
      // COPASI can take SBML files and do *something* with them
      std::string Category("Analysis");
      std::string Description("COPASI Analyzer - Imports an SBML model into CopasiUI");

      mpSBWModule =
        new SystemsBiologyWorkbench::ModuleImpl(FullName, FullName,
                                                SystemsBiologyWorkbench::UniqueModule,
                                                Description);


      mpSBWModule->addServiceObject(FullName, FullName, Category, this, Description);

      // this lets SBW ask COPASI to shut down
      SBW::addListener(this);

      // here we start the SBW services and give over to QT's main loop
      mpSBWModule->enableModuleServices();
    }

  catch (...)
    {
      pdelete(mpSBWModule);
    }


  // Update the SBW Menu
  sbwRefreshMenu();
}

void CopasiUI3Window::sbwDisconnect()
{
  if (mpSBWModule != NULL)
    {
      try
        {
          SBWLowLevel::disconnect();
          delete mpSBWModule;
        }

      catch (...)
        {}

      mpSBWModule = NULL;
    }
}

void CopasiUI3Window::sbwRegister()
{
  if (mpSBWModule != NULL)
    {
      try
        {
          // Set the commandline so that SBW knows how to call us.
          std::string Self;
          COptions::getValue("Self", Self);

          mpSBWModule->setCommandLine(Self);
          mpSBWModule->registerModule();

          sbwRefreshMenu();
        }

      catch (...)
        {}
    }
}

void CopasiUI3Window::sbwUnregister(const std::string & moduleName) const
{
  try
    {
      SystemsBiologyWorkbench::Module Module = SBW::getModuleInstance("BROKER");
      SystemsBiologyWorkbench::Service Service = Module.findServiceByName("BROKER");

      DataBlockWriter Arguments;
      Arguments.add(moduleName);
      Service.getMethod("void unregisterModule(string)").call(Arguments);
    }

  catch (...)
    {}
}

// get a list of all SBW analyzers and stick them into a menu
void CopasiUI3Window::sbwRefreshMenu()
{
  if (mpSBWMenu == NULL) return;

  bool Visible = true;
  bool IsSBWRegistered = false;

  mSBWAnalyzerModules.clear();
  mSBWAnalyzerServices.clear();
  mpSBWMenu->clear();
  mSBWActionMap.clear();

  if (mpSBWActionGroup != NULL)
    {
      disconnect(mpSBWActionGroup, SIGNAL(triggered(QAction *)), this, SLOT(sbwSlotMenuTriggered(QAction *)));
      mpSBWActionGroup->deleteLater();
      mpSBWActionGroup = NULL;
    }

  mpSBWActionGroup = new QActionGroup(this);
  connect(mpSBWActionGroup, SIGNAL(triggered(QAction *)), this, SLOT(sbwSlotMenuTriggered(QAction *)));

  QAction * pAction;

  try
    {
      std::vector<DataBlockReader> Services = sbwFindServices("Analysis", true);
      std::vector<DataBlockReader>::const_iterator it = Services.begin();
      std::vector<DataBlockReader>::const_iterator end = Services.end();

      QMap< QString, int > SortedNames;
      QStringList ModuleList;
      QStringList ServiceList;

      std::string Self;
      COptions::getValue("Self", Self);

      int i = 0;

      for (; it != end; ++it)
        {
          SystemsBiologyWorkbench::ServiceDescriptor Service(*it);
          SystemsBiologyWorkbench::ModuleDescriptor Module = Service.getModuleDescriptor();

          std::string ModuleName = Module.getName();
          std::string ServiceName = Service.getName();
          std::string MenuName = Service.getDisplayName();

          // Check whether the registered service is provided by COPASI
          if (ServiceName.compare(0, 6, "COPASI") == 0)
            {
              std::string CommandLine = Module.getCommandLine();

              // Check whether the registered module points to current CopasiUI
              if (CommandLine.compare(0, Self.length(), Self) == 0)
                {
                  // Check whether the versions match
                  if (ServiceName != "COPASI " + CVersion::VERSION.getVersion())
                    {
                      // We transparently update the registration information
                      sbwUnregister(ModuleName);
                      return sbwRegister();
                    }

                  IsSBWRegistered = true;
                  continue;
                }
              else
                {
                  // Check whether the CommandLine is still valid
                  std::string::size_type Length = CommandLine.find(" -sbwmodule");

                  if (Length != std::string::npos)
                    {
                      CommandLine = CommandLine.substr(0, Length);
                    }

                  if (!CDirEntry::exist(CommandLine))
                    {
                      sbwUnregister(ModuleName);
                      continue;
                    }
                }
            }

          SortedNames[FROM_UTF8(MenuName)] = i++;
          ModuleList.append(FROM_UTF8(ModuleName));
          ServiceList.append(FROM_UTF8(ServiceName));
        }

      // Add the option to register in SBW
      if (!IsSBWRegistered)
        {
          pAction = new QAction("Register", mpSBWActionGroup);
          mpSBWMenu->addAction(pAction);
          mSBWActionMap[pAction] = SortedNames.size();

          mpSBWMenu->addSeparator();
        }

      QMap< QString, int >::const_iterator itMap = SortedNames.begin();
      QMap< QString, int >::const_iterator endMap = SortedNames.end();

      for (i = 0; itMap != endMap; ++itMap, i++)
        {
          mSBWAnalyzerModules.append(ModuleList[itMap.value()]);
          mSBWAnalyzerServices.append(ServiceList[itMap.value()]);

          pAction = new QAction(itMap.key(), mpSBWActionGroup);
          mpSBWMenu->addAction(pAction);
          mSBWActionMap[pAction] = i;
        }

      if (mSBWAnalyzerModules.empty())
        Visible = false;
    }

  catch (...)
    {
      Visible = false;
    }

  if (!Visible)
    mpTools->removeAction(mpSBWAction);

  return;
}

void CopasiUI3Window::sbwSlotMenuTriggered(QAction * pAction)
{
  mpDataModelGUI->commit();

  mSBWActionId = mSBWActionMap[pAction];

  if (mSBWActionId == mSBWAnalyzerModules.size())
    {
      sbwRegister();
    }
  else
    {
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(sbwSlotMenuTriggeredFinished(bool)));
      exportSBMLToString(mSBWDocumentString);
    }
}


void CopasiUI3Window::sbwSlotMenuTriggeredFinished(bool success)
{
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(sbwSlotMenuTriggeredFinished(bool)));

  if (success)
    {
      try
        {
          int nModule = SBWLowLevel::getModuleInstance(mSBWAnalyzerModules[mSBWActionId].ascii());
          int nService = SBWLowLevel::moduleFindServiceByName(nModule, mSBWAnalyzerServices[mSBWActionId].ascii());
          int nMethod = SBWLowLevel::serviceGetMethod(nModule, nService, "void doAnalysis(string)");

          DataBlockWriter args;
          args << mSBWDocumentString;
          SBWLowLevel::methodSend(nModule, nService, nMethod, args);
        }

      catch (SBWException * pE)
        {
          CQMessageBox::critical(this, "SBW Error",
                                 FROM_UTF8(pE->getMessage()),
                                 QMessageBox::Ok | QMessageBox::Default,
                                 QMessageBox::NoButton);
        }
    }

  mSBWDocumentString = "";
}

std::vector< DataBlockReader > CopasiUI3Window::sbwFindServices(const std::string & category,
    const bool & recursive)
{
  std::vector< DataBlockReader > result;

  try
    {
      DataBlockWriter oArguments;
      oArguments.add(category);
      oArguments.add(recursive);

      Module oModule = SBW::getModuleInstance("BROKER");
      Service oService = oModule.findServiceByName("BROKER");
      oService.getMethod("{}[] findServices(string, boolean)").call(oArguments) >> result;
    }

  catch (...)
    {
      result.clear();
    }

  return result;
}

// Here we get an SBML document
SystemsBiologyWorkbench::DataBlockWriter CopasiUI3Window::sbwAnalysis(SystemsBiologyWorkbench::Module /*from*/, SystemsBiologyWorkbench::DataBlockReader reader)
{
  try
    {
      std::string sSBMLModel;
      reader >> sSBMLModel;

      QSBWSBMLEvent *event = new QSBWSBMLEvent(sSBMLModel);
      QApplication::postEvent(this, event);
    }

  catch (...)
    {
      throw new SystemsBiologyWorkbench::SBWApplicationException("Error in doAnalysis");
    }

  // and yes ... every SBW method has to return something
  return SystemsBiologyWorkbench::DataBlockWriter();
}

SystemsBiologyWorkbench::DataBlockWriter CopasiUI3Window::sbwGetSBML(SystemsBiologyWorkbench::Module /*from*/, SystemsBiologyWorkbench::DataBlockReader /*reader*/)
{
  connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(sbwSlotGetSBMLFinished(bool)));

  QMutexLocker Locker(&mSBWMutex);
  mSBWCallFinished = false;

  mpDataModelGUI->exportSBMLToString(mSBWDocumentString);

  if (!mSBWCallFinished)
    {
      mSBWWaitSlot.wait(&mSBWMutex);
    }

  SystemsBiologyWorkbench::DataBlockWriter result;

  if (mSBWSuccess)
    {
      try
        {
          // write the current model as SBML and return it
          result << mSBWDocumentString;
          mSBWDocumentString = "";

          return result;
        }

      catch (...)
        {
          throw new SystemsBiologyWorkbench::SBWApplicationException("Error getting the SBML.");
        }
    }

  throw new SystemsBiologyWorkbench::SBWApplicationException("Error getting the SBML.");

  // This will never be reached.
  return result;
}

void CopasiUI3Window::sbwSlotGetSBMLFinished(bool success)
{
  QMutexLocker Locker(&mSBWMutex);

  mSBWCallFinished = true;
  mSBWSuccess = success;

  mSBWWaitSlot.wakeAll();
}
#else
//void CopasiUI3Window::slotSBWMenuTriggered(QAction * /* pAction */) {}
void CopasiUI3Window::customEvent(QEvent * /* event */) {}

#endif // COPASI_SBW_INTEGRATION
#include <QUrl>
void CopasiUI3Window::dragEnterEvent(QDragEnterEvent *event)
{
  if (event->mimeData()->hasFormat("text/uri-list"))
    event->acceptProposedAction();
}

void CopasiUI3Window::dropEvent(QDropEvent *event)
{
  QList<QUrl> urls = event->mimeData()->urls();

  if (urls.isEmpty())
    return;

  QString fileName = urls.first().toLocalFile();

  if (fileName.isEmpty())
    return;

  slotFileOpen(fileName);
}
/**
 * The slider dialog has to be disabled before
 * a task is run and reenabled afterwards.
 * Actually the methods stores the state
 * when the value true is passed and restores that
 * state when the value false is passed.
 */
void CopasiUI3Window::disableSliders(bool disable)
{
  if (disable)
    {
      this->mSliderDialogEnabled = this->mpSliders->isEnabled();
      this->mpSliders->setEnabled(false);
    }
  else
    {
      this->mpSliders->setEnabled(this->mSliderDialogEnabled);
      this->mpSliders->updateAllSliders();
    }
}


