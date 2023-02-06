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

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <sbml/SBMLDocument.h>

#include <QMimeData>
#include <QSettings>
#include <QClipboard>
#include <QInputDialog>

#include <QtCore/QEvent>
#include <QMenuBar>
#include <QtCore/QTimer>
#include <QComboBox>
#include <QToolBar>
#include <QTextEdit>
#include <QtCore/QThread>
#include <QFontDialog>
#include <QtCore/QDateTime>

#include <QByteArray>
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QUrlQuery>
#endif
#include <QRegExp>
#include <QDesktopServices>
#include <QActionGroup>

#include <vector>
#include <sstream>

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
#include "copasi/UI/CQTabWidget.h"
#include "copasiWidget.h"
#include "TaskWidget.h"
#include "copasi/resourcesUI/CQIconResource.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/utilities/CDirEntry.h"
#include "copasi/model/CModel.h"
#include "copasi/commandline/COptionParser.h"
#include "copasi/commandline/COptions.h"
#include "copasi/commandline/CConfigurationFile.h"
#include "copasi/commandline/CLocaleString.h"
#include "copasi/wizard/wizard.h"
#include "copasi/sbml/SBMLIncompatibility.h"
#include "copasi/MIRIAM/CConstants.h"
#include "copasi/utilities/CVersion.h"
#include "copasi/model/CModelExpansion.h"
#include "copasi/UI/CQCheckModelWindow.h"
#include <copasi/UI/CQBrowserPane.h>

#include "copasi/model/CModelExpansion.h"

#include <copasi/UI/CWindowInterface.h>

#include "CQSEDMLFileDialog.h"
#include "CQSEDMLImportDialog.h"
#include <copasi/sedml/SEDMLUtils.h>
#include <sedml/SedReader.h>

# include "copasi/undoUI/CQUndoDialog.h"
# include "copasi/core/CCore.h"
# include "copasi/undo/CUndoStack.h"
#include <copasi/report/COutputAssistant.h>

#include <copasi/utilities/utility.h>

#ifdef COPASI_SBW_INTEGRATION
#include <stdlib.h>
#endif // COPASI_SBW_INTEGRATION

#include <sedml/SedDocument.h>

#include <copasi/UI/CQOptPopulation.h>

#include <copasi/UI/CQParameterEstimationResult.h>

#include <qwt_global.h>

#define AutoSaveInterval 10*60*1000

#ifdef DEBUG_UI
#include <QtCore/QtDebug>
#endif

#ifdef COPASI_Versioning
#include "copasi/versioningUI/CBrowseModelVersionDialog.h"
#include "copasi/versioningUI/CCreateModelVersionDialog.h"
#endif

#ifdef COPASI_Provenance
#include "CProvenanceDialog.h"
#include "Provenance/CProvenanceXMLWriter.h"
#include "CEntityProvenanceDialog.h"
#endif

#include "copasi/UI/CQDependencyDialog.h"
#include "qtUtilities.h"

#include "copasi/math/CJitCompiler.h"

// static
CopasiUI3Window *CopasiUI3Window::pMainWindow = NULL;

QMainWindow * getWindowForAction(const QMap< QPointer<QMainWindow>, QPointer<QAction> > & map, const QAction * pAction)
{
  QMap< QPointer<QMainWindow>, QPointer<QAction> >::const_iterator it = map.begin();
  QMap< QPointer<QMainWindow>, QPointer<QAction> >::const_iterator end = map.end();

  for (; it != end; ++it)
    if (it.value() == pAction)
      {
        return it.key();
      }

  return NULL;
}

// static
CopasiUI3Window *CopasiUI3Window::getMainWindow()
{
  return pMainWindow;
}

// static
bool CopasiUI3Window::isMainThread()
{
  return pMainWindow == NULL || pMainWindow->mpMainThread == QThread::currentThread();
}

// static
CopasiUI3Window *CopasiUI3Window::create()
{
  CopasiUI3Window *pWindow = NULL;
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
 * Utility function for guessing whether the file might
 * be an SBML file. If so it should contain an SBML tag in the
 * first couple of lines.
 */
bool isProbablySBML(QString & fileName)
{
  return isProbablySBML(std::string(TO_UTF8(fileName)));
}

/**
 * Utility function for guessing whether the file might
 * be an SEDML file. If so it should contain an SEDML tag in the
 * first couple of lines.
 */
bool isProbablySEDML(QString & fileName)
{
  return containsTag(std::string(TO_UTF8(fileName)), "sedML", 5);
}

bool isArchive(const QString & fileName)
{
  bool result = false;
  std::ifstream in;
  in.open(fileName.toStdString().c_str(), std::ifstream::in);

  char buffer[5];
  in.read(buffer, 4);
  buffer[4] = '\x00';

  if (in.good())
    {
      result = result || (buffer[0] == 'P' && buffer[1] == 'K' && buffer[2] == '\x03' && buffer[3] == '\x04');
      result = result || (buffer[0] == 'P' && buffer[1] == 'K' && buffer[2] == '\x05' && buffer[3] == '\x06');
      result = result || (buffer[0] == 'P' && buffer[1] == 'K' && buffer[2] == '\x07' && buffer[3] == '\x08');
    }

  in.close();
  return result;
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
  mpDataModel(NULL),
  mpListView(NULL),
  mpBoxSelectFramework(NULL),
  mpMainToolbar(NULL),
  FixedTitle(),
  mpDeferredLoadFile(NULL),
  mpaNew(NULL),
  mpaOpen(NULL),
  mpaOpenCopasiFiles(NULL),
  mpaOpenSBMLFiles(NULL),
  mpaOpenFromUrl(NULL),
  mpaSave(NULL),
  mpaSaveAs(NULL),
  mpaFunctionDBSave(NULL),
  mpaFunctionDBLoad(NULL),
  mpaParameterSetsSave(NULL),
  mpaParameterSetsLoad(NULL),
  mpaImportSBML(NULL),
  mpaExportSBML(NULL),
  mpaExportODE(NULL),
  mpaQuit(NULL),
  mpaObjectBrowser(NULL),
  mpaSliders(NULL),
  mpaDependencies(NULL),
  mpaCheckModel(NULL),
  mpaHideMainToolbar(NULL),
  mpaApplyInitialState(NULL),
  mpaUpdateInitialState(NULL),
  mpaCapture(NULL),
  mpaUpdateMIRIAM(NULL),
  mpaExpandModel(NULL),
  mpaFontSelectionDialog(NULL),
  mpaParameterEstimationResult(NULL),
  mpaCopy(NULL),
  mpaCloseAllWindows(NULL),
  mpaShowDebugInfo(NULL),

  mpaImportCombine(NULL),
  mpaExportCombine(NULL),
  mpaExportShiny(NULL),

  mpaAddModel(NULL),
  mpaMergeModels(NULL),

  mpSliders(NULL),
  mpDependencies(NULL),
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
  mpWindowsActionGroup(NULL),
  mpMIRIAMResources(NULL),
  mpMainThread(QThread::currentThread()),
  mNewFile(),
  mCommitRequired(true),
  mQuitApplication(false),
  mSliderDialogEnabled(false),
  mMessageShown(false),
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

  , mpMenuSEDMLSupport(NULL)
  , mpMenuRecentSEDMLFiles(NULL)
  , mRecentSEDMLFilesActionMap()
  , mpRecentSEDMLFilesActionGroup(NULL)

  , mpaUndo(NULL)
  , mpaRedo(NULL)
  , mpaUndoHistory(NULL)
  , mpaClearUndoHistory(NULL)

#ifdef COPASI_Versioning
  , mpaCreateVersion(NULL)
  , mpaBrowseVersion(NULL)
//  COMBINE Archive will take care of file management
//  QString mLastSavedParentOfCurrentModel;
#endif

#ifdef COPASI_Provenance
  //, mProvenanceParentOfCurrentModel(QString(""))
  , mProvenanceOrigionFileType(QString("Created"))
  , mProvenanceOrigionTime(QDateTime::currentDateTimeUtc().toString())
  , mProvenanceOfOrigionOfFile(QString(""))
#endif
  , mpPopulationDisplay(NULL)
  , mAutoUpdateCheck(false)
  , mActionStack()
{
  // There can only be one
  pMainWindow = this;

  // set destructive close
  this->setAttribute(Qt::WA_DeleteOnClose);
  // Add this window to the list of windows
  mWindows.insert(pMainWindow, NULL);

#ifndef Darwin
  setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
#endif // not Darwin
  createActions();
  mpMainToolbar = createToolBar(); // creates a tool bar
  createMenuBar();  // creates a menu bar
  setIconSize(QSize(18, 20));
  mpaSave->setEnabled(false);
  mpaSaveAs->setEnabled(false);
  mpaExportSBML->setEnabled(false);
  mpaExportODE->setEnabled(false);
  mpaExportSEDML->setEnabled(false);

  mpDataModel = CRootContainer::addDatamodel();
  mpDataModelGUI = new DataModelGUI(this, mpDataModel);
  mpListView = new ListViews(this, mpDataModelGUI, mpDataModel);
  // Set the window caption/title
  FixedTitle = "COPASI ";
  FixedTitle += FROM_UTF8(CVersion::VERSION.getVersion());
  updateTitle();
  connect(mpListView, SIGNAL(signalFolderChanged(const QModelIndex &)), this, SLOT(listViewsFolderChanged(const QModelIndex &)));
  mpDataModelGUI->registerListView(mpListView);
  mpListView->show();
  this->setCentralWidget(mpListView);
  ListViews::WidgetType id = mpListView->getCurrentItemId();

  QSettings settings(FROM_UTF8(COptions::getConfigDir() + "/" + "ui_settings.ini"), QSettings::IniFormat, this);

  QSize mainWindowSize = settings.value("mainwindow/size", QSize(800, 600)).toSize();

  resize(mainWindowSize);
  show();
  mpListView->switchToOtherWidget(ListViews::WidgetType::COPASI, std::string());
  // Assure that the changed flag is still false;
  assert(mpDataModel != NULL);
  mpDataModel->changed(false);
  mpAutoSaveTimer = new QTimer(this);
  mpAutoSaveTimer->start(AutoSaveInterval); // every 10 minutes
  // TODO CRITICAL We need to disable autosave to avoid race conditions.
  // connect(mpAutoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSave()));
  // mpDataModelGUI->notify(ListViews::ObjectType::FUNCTION, ListViews::ADD, "");
  //create sliders window
  mpSliders = new SliderDialog(mpListView);
  mpSliders->setParentWindow(this);
  mpSliders->setCurrentFolderId(id);
  QSize sliderSize = settings.value("slider/size", QSize(320, 350)).toSize();
  mpSliders->resize(sliderSize);
  mpSliders->hide();
  mpSliders->setChanged(false);
  mSliderDialogEnabled = mpSliders->isEnabled();
  mpDependencies = new CQDependencyDialog(mpListView);
  mpDependencies->setParentWindow(this);
  mpDependencies->hide();
  setApplicationFont();
  // drop acceptance
  setAcceptDrops(true);
  mpListView->mpTreeView->setFocus();

  QTimer::singleShot(10, this, SLOT(slotAutoCheckForUpdates()));
  connect(this, SIGNAL(signalDefferedLoadFile(QString)), this, SLOT(slotDefferedLoadFile(QString)));
}

CopasiUI3Window::~CopasiUI3Window()
{
#ifdef COPASI_SBW_INTEGRATION
  sbwDisconnect();
#endif // COPASI_SBW_INTEGRATION
  QMap< QPointer<QMainWindow>, QPointer<QAction> >::iterator it = mWindows.begin();
  QMap< QPointer<QMainWindow>, QPointer<QAction> >::iterator end = mWindows.end();

  for (; it != end; ++it)
    {
      QPointer<QMainWindow> current = it.key();

      if (current == NULL)  continue;

      if (current != this)
        {
          current->close();
          // at this point the iterator becomes invalid as close will remove the elements from the window.
          it = mWindows.begin();
          end = mWindows.end();
        }
    }

  pdelete(mpSliders);
  pdelete(mpDependencies);
  mpDataModelGUI->deregisterListView(mpListView);
  pdelete(mpDataModelGUI);
  pdelete(mpListView);
}

void CopasiUI3Window::createActions()
{
  //TODO: use the QKeySequence standard shortcuts
  //TODO: add tool tips, status tips etc.
  mpaNew = new QAction(CQIconResource::icon(CQIconResource::fileNew), "&New", this);
  connect(mpaNew, SIGNAL(triggered()), this, SLOT(slotNewDoc()));
  mpaNew->setShortcut(Qt::CTRL + Qt::Key_N);
  mpaOpen = new QAction(CQIconResource::icon(CQIconResource::fileOpen), "&Open...", this);
  connect(mpaOpen, SIGNAL(triggered()), this, SLOT(slotFileOpen()));
  mpaOpen->setShortcut(Qt::CTRL + Qt::Key_O);
  mpaOpenCopasiFiles = new QAction(CQIconResource::icon(CQIconResource::fileOpen), "COP&ASI Files...", this);
  connect(mpaOpenCopasiFiles, SIGNAL(triggered()), this, SLOT(slotFileExamplesCopasiFiles()));
  // mpaOpenCopasiFiles->setShortcut(Qt::CTRL + Qt::Key_1);
  mpaOpenSBMLFiles = new QAction(CQIconResource::icon(CQIconResource::fileOpen), "S&BML Files...", this);
  connect(mpaOpenSBMLFiles, SIGNAL(triggered()), this, SLOT(slotFileExamplesSBMLFiles()));
  // mpaOpenSBMLFiles->setShortcut(Qt::CTRL + Qt::Key_2);
  mpaOpenFromUrl = new QAction(CQIconResource::icon(CQIconResource::fileOpen), "Open from &Url...", this);
  connect(mpaOpenFromUrl, SIGNAL(triggered()), this, SLOT(slotFileOpenFromUrl()));
  mpaSave = new QAction(CQIconResource::icon(CQIconResource::fileSave), "&Save", this);
  connect(mpaSave, SIGNAL(triggered()), this, SLOT(slotFileSave()));
  mpaSave->setShortcut(Qt::CTRL + Qt::Key_S);
  mpaSaveAs = new QAction(CQIconResource::icon(CQIconResource::fileSaveas), "Save &As...", this);
  connect(mpaSaveAs, SIGNAL(triggered()), this, SLOT(slotFileSaveAs()));
  mpaSaveAs->setShortcut(QKeySequence(Qt::SHIFT, Qt::CTRL, Qt::Key_S));
  mpaImportSBML = new QAction(CQIconResource::icon(CQIconResource::fileOpen), "&Import SBML...", this);
  connect(mpaImportSBML, SIGNAL(triggered()), this, SLOT(slotImportSBML()));
  mpaImportSBML->setShortcut(Qt::CTRL + Qt::Key_I);
  mpaExportSBML = new QAction(CQIconResource::icon(CQIconResource::fileExport), "&Export SBML...", this);
  connect(mpaExportSBML, SIGNAL(triggered()), this, SLOT(slotExportSBML()));
  mpaExportSBML->setShortcut(Qt::CTRL + Qt::Key_E);
  mpaExportODE = new QAction(CQIconResource::icon(CQIconResource::fileExport), "Export ODEs...", this);
  connect(mpaExportODE, SIGNAL(triggered()), this, SLOT(slotExportMathModel()));
  mpaExportODE->setShortcut(Qt::CTRL + Qt::Key_M);
  mpaQuit = new QAction("&Quit", this);
  connect(mpaQuit, SIGNAL(triggered()), this, SLOT(slotQuit()));
  mpaQuit->setShortcut(Qt::CTRL + Qt::Key_Q);

  mpaCopy = new QAction("&Copy", this);
  mpaCopy->setShortcut(QKeySequence::Copy);
  connect(mpaCopy, SIGNAL(triggered()), this, SLOT(slotCopy()));

  mpaSliders = new QAction(CQIconResource::icon(CQIconResource::slider), "Show sliders", this);
  mpaSliders->setCheckable(true);
  connect(mpaSliders, SIGNAL(toggled(bool)), this, SLOT(slotShowSliders(bool)));
  mpaHideMainToolbar = new QAction("Hide Main Toolbar", this);
  mpaHideMainToolbar->setCheckable(true);
  connect(mpaHideMainToolbar, SIGNAL(toggled(bool)), this, SLOT(slotHideMainToolbar(bool)));
  mpaDependencies = new QAction("Show dependencies", this);
  mpaDependencies->setCheckable(true);
  connect(mpaDependencies, SIGNAL(toggled(bool)), this, SLOT(slotShowDependencies(bool)));
  mpaObjectBrowser = new QAction("Object &Browser", this);
  mpaObjectBrowser->setCheckable(true);
  connect(mpaObjectBrowser, SIGNAL(toggled(bool)), this, SLOT(slotShowObjectBrowserDialog(bool)));
  mpaCheckModel = new QAction(CQIconResource::icon(CQIconResource::checkMark), "Check model", this);
  connect(mpaCheckModel, SIGNAL(triggered()), this, SLOT(slotCheckModel()));
  mpaUpdateMIRIAM = new QAction(CQIconResource::icon(CQIconResource::miriam), "Update MIRIAM", this);
  connect(mpaUpdateMIRIAM, SIGNAL(triggered()), this, SLOT(slotUpdateMIRIAM()));

  mpaImportCombine = new QAction(CQIconResource::icon(CQIconResource::fileOpen), "&Import Combine Archive", this);
  connect(mpaImportCombine, SIGNAL(triggered()), this, SLOT(slotImportCombine()));
  mpaExportCombine = new QAction(CQIconResource::icon(CQIconResource::fileExport), "&Export Combine Archive", this);
  connect(mpaExportCombine, SIGNAL(triggered()), this, SLOT(slotExportCombine()));

  mpaExportShiny = new QAction(CQIconResource::icon(CQIconResource::fileExport), "&Export Shiny Archive", this);
  connect(mpaExportShiny, SIGNAL(triggered()), this, SLOT(slotExportShiny()));

#ifdef COPASI_Provenance
  mpaProvenance = new QAction("Provenance", this);
  connect(mpaProvenance, SIGNAL(activated()), this, SLOT(slotProvenance()));
#endif
  mpaApplyInitialState = new QAction(CQIconResource::icon(CQIconResource::isToS), "Apply initial state", this);
  connect(mpaApplyInitialState, SIGNAL(triggered()), this, SLOT(slotApplyInitialState()));
  mpaUpdateInitialState = new QAction(CQIconResource::icon(CQIconResource::sToIs), "Update initial state from current state", this);
  connect(mpaUpdateInitialState, SIGNAL(triggered()), this, SLOT(slotUpdateInitialState()));
  mpaCapture = new QAction(CQIconResource::icon(CQIconResource::captureImage), "Capture the main window", this);
  connect(mpaCapture, SIGNAL(triggered()), this, SLOT(slotCapture()));
  mpaExpandModel = new QAction("Create array of compartments", this);
  connect(mpaExpandModel, SIGNAL(triggered()), this, SLOT(slotExpandModel()));
  mpaFontSelectionDialog = new QAction("Select the Application Font", this);
  connect(mpaFontSelectionDialog, SIGNAL(triggered()), this, SLOT(slotFontSelection()));

  mpaOpenSEDMLFiles = new QAction(CQIconResource::icon(CQIconResource::fileOpen), "S&ED-ML Files...", this);
  connect(mpaOpenSEDMLFiles, SIGNAL(triggered()), this, SLOT(slotFileExamplesSEDMLFiles()));
  // mpaOpenSEDMLFiles->setShortcut(Qt::CTRL + Qt::Key_3);
  mpaImportSEDML = new QAction(CQIconResource::icon(CQIconResource::fileOpen), "&Import SED-ML...", this);
  connect(mpaImportSEDML, SIGNAL(triggered()), this, SLOT(slotImportSEDML()));
  // mpaImportSEDML->setShortcut(Qt::CTRL + Qt::Key_X);
  mpaExportSEDML = new QAction(CQIconResource::icon(CQIconResource::fileExport), "&Export SED-ML...", this);
  connect(mpaExportSEDML, SIGNAL(triggered()), this, SLOT(slotExportSEDML()));
  // mpaExportSEDML->setShortcut(Qt::CTRL + Qt::Key_Z);

  //     QAction* mpaObjectBrowser;

  mpaAddModel = new QAction(CQIconResource::icon(CQIconResource::fileAdd), "&Add to model...", this);
  mpaAddModel->setShortcut(QKeySequence(Qt::SHIFT, Qt::CTRL, Qt::Key_A));
  connect(mpaAddModel, SIGNAL(triggered()), this, SLOT(slotAddFileOpen()));
  mpaMergeModels = new QAction("&Merge added model...", this);
  mpaMergeModels->setShortcut(QKeySequence(Qt::SHIFT, Qt::CTRL, Qt::Key_M));
  connect(mpaMergeModels, SIGNAL(triggered()), this, SLOT(slotMergeModels()));

  mpaCloseAllWindows = new QAction("Close all windows below:", this);
  connect(mpaCloseAllWindows, SIGNAL(triggered()), this, SLOT(slotCloseAllWindows()));
  mpaShowDebugInfo = new QAction("Display Debug Information", this);
  connect(mpaShowDebugInfo, SIGNAL(triggered()), this, SLOT(slotShowDebugInfo()));
  mpaFunctionDBLoad =  new QAction(CQIconResource::icon(CQIconResource::fileOpen), "Load Function DB...", this);
  connect(mpaFunctionDBLoad, SIGNAL(triggered()), this, SLOT(slotFunctionDBLoad()));
  mpaFunctionDBSave =  new QAction(CQIconResource::icon(CQIconResource::fileSaveas), "Save Function DB...", this);
  connect(mpaFunctionDBSave, SIGNAL(triggered()), this, SLOT(slotFunctionDBSave()));
  mpaParameterSetsLoad = new QAction(CQIconResource::icon(CQIconResource::fileOpen), "Load Parameter Sets...", this);
  connect(mpaParameterSetsLoad, SIGNAL(triggered()), this, SLOT(slotParameterSetsLoad()));
  mpaParameterSetsSave = new QAction(CQIconResource::icon(CQIconResource::fileSaveas), "Save ParameterSets...", this);
  connect(mpaParameterSetsSave, SIGNAL(triggered()), this, SLOT(slotParameterSetsSave()));

  // UNDO framework
  mpaUndo = new QAction("Undo", this);
  mpaUndo->setShortcut(QKeySequence::Undo);
  connect(mpaUndo, SIGNAL(triggered()), this, SLOT(slotUndo()));
  mpaRedo = new QAction("Redo", this);
  mpaRedo->setShortcut(QKeySequence::Redo);
  connect(mpaRedo, SIGNAL(triggered()), this, SLOT(slotRedo()));
  mpaUndoHistory = new QAction("&Undo History", this);
  connect(mpaUndoHistory, SIGNAL(triggered()), this, SLOT(slotUndoHistory()));
  mpaClearUndoHistory = new QAction("&Clear Undo History", this);
  connect(mpaClearUndoHistory, SIGNAL(triggered()), this, SLOT(slotClearUndoHistory()));

#ifdef COPASI_Versioning
  mpaCreateVersion = new QAction("Create", this);
  connect(mpaCreateVersion, SIGNAL(triggered()), this, SLOT(slotCreateVersion()));
  mpaBrowseVersion = new QAction("Browse", this);
  connect(mpaBrowseVersion, SIGNAL(triggered()), this, SLOT(slotBrowseVersion()));
#endif
  mpaParameterEstimationResult = new QAction("Load Parameter Estimation Protocol", this);
  connect(mpaParameterEstimationResult, SIGNAL(triggered()), this, SLOT(slotLoadParameterEstimationProtocol()));
}

void
CopasiUI3Window::slotLoadParameterEstimationProtocol()
{
  CQParameterEstimationResult *dlg = new CQParameterEstimationResult(this, mpDataModel);
  dlg->exec();
  dlg->deleteLater();
}

#include <copasi/UI/objectdebug.h>
void CopasiUI3Window::slotShowDebugInfo()
{
  ObjectDebug* dlg = new ObjectDebug(this);
  dlg->exec();
  dlg->deleteLater();
}

void CopasiUI3Window::slotFunctionDBSave(QString dbFile)
{
  if (mCommitRequired)
    {
      mpDataModelGUI->commit();
    }

  if (dbFile.isEmpty())
    {
      C_INT32 Answer = QMessageBox::No;

      while (Answer == QMessageBox::No)
        {
          dbFile =
            CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                              CopasiFileDialog::getDefaultFileName(".cpk"), "COPASI Function DB (*.cpk)",
                                              "Choose a file");

          if (dbFile.isEmpty()) return;

          // Checks whether the file exists
          Answer = checkSelection(this, dbFile);

          if (Answer == QMessageBox::Cancel) return;
        }
    }

  mpDataModelGUI->saveFunctionDB(TO_UTF8(dbFile));
}

void CopasiUI3Window::slotFunctionDBLoad(QString dbFile)
{
  if (mCommitRequired)
    {
      mpDataModelGUI->commit();
    }

  if (dbFile.isEmpty())
    {
      dbFile =
        CopasiFileDialog::getOpenFileName(this, "Open File Dialog",
                                          QString(), "COPASI Function DB (*.cpk)",
                                          "Choose a file");
    }

  if (!dbFile.isEmpty())
    {
      mpDataModelGUI->loadFunctionDB(TO_UTF8(dbFile));
    }
}

void
CopasiUI3Window::slotParameterSetsSave(QString dbFile)
{
  if (mCommitRequired)
    {
      mpDataModelGUI->commit();
    }

  if (dbFile.isEmpty())
    {
      C_INT32 Answer = QMessageBox::No;

      while (Answer == QMessageBox::No)
        {
          dbFile =
            CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                              CopasiFileDialog::getDefaultFileName(".cpmp"), "COPASI Parameter Sets (*.cpmp)",
                                              "Choose a file");

          if (dbFile.isEmpty()) return;

          // Checks whether the file exists
          Answer = checkSelection(this, dbFile);

          if (Answer == QMessageBox::Cancel) return;
        }
    }

  mpDataModelGUI->saveModelParameterSets(TO_UTF8(dbFile));
}

void
CopasiUI3Window::slotParameterSetsLoad(QString dbFile)
{
  if (mCommitRequired)
    {
      mpDataModelGUI->commit();
    }

  if (dbFile.isEmpty())
    {
      dbFile =
        CopasiFileDialog::getOpenFileName(this, "Open File Dialog",
                                          QString(), "COPASI Parameter Sets (*.cpmp)",
                                          "Choose a file");
    }

  if (!dbFile.isEmpty())
    {
      mpDataModelGUI->loadModelParameterSets(TO_UTF8(dbFile));
    }
}

QToolBar *CopasiUI3Window::createToolBar()
{
  QToolBar *tb = addToolBar("MainToolBar");
  tb->addAction(mpaNew);
  tb->addAction(mpaOpen);
  tb->addAction(mpaSave);
  tb->addAction(mpaCapture);
  tb->addAction(mpaSliders);
  tb->addAction(mpaCheckModel);
  tb->addAction(mpaApplyInitialState);
  tb->addAction(mpaUpdateInitialState);
  tb->addAction(mpaUpdateMIRIAM);
#ifdef COPASI_Provenance
  tb->addAction(mpaProvenance);
#endif

  tb->addAction(mpaAddModel);
  //tb->addAction(mpaMergeModels);

  tb->addSeparator();
  mpBoxSelectFramework = new QComboBox(tb);
  QStringList items;
  items << "Concentrations" << "Particle Numbers";
  mpBoxSelectFramework->addItems(items);
  tb->addWidget(mpBoxSelectFramework);
  connect(mpBoxSelectFramework, SIGNAL(activated(int)), this, SLOT(slotFrameworkChanged(int)));
  setUnifiedTitleAndToolBarOnMac(true);
  return tb;
}

void CopasiUI3Window::createMenuBar()
{
  QMenu *pFileMenu = menuBar()->addMenu("&File");
  pFileMenu->addAction(mpaNew);
  pFileMenu->addAction(mpaOpen);
  pFileMenu->addAction(mpaOpenFromUrl);
  mpMenuExamples = pFileMenu->addMenu("Examples");
  mpMenuExamples->addAction(mpaOpenCopasiFiles);
  mpMenuExamples->addAction(mpaOpenSBMLFiles);
  mpMenuExamples->addAction(mpaOpenSEDMLFiles);

  pFileMenu->addAction(mpaSave);
  pFileMenu->addAction(mpaSaveAs);

  pFileMenu->addAction(mpaAddModel);
  //pFileMenu->addAction(mpaMergeModels);

  pFileMenu->addSeparator();
  pFileMenu->addAction(mpaImportSBML);
  pFileMenu->addAction(mpaExportSBML);
  pFileMenu->addAction(mpaExportODE);

  pFileMenu->addSeparator();
  pFileMenu->addAction(mpaImportCombine);
  pFileMenu->addAction(mpaExportCombine);
  pFileMenu->addAction(mpaExportShiny);

  pFileMenu->addSeparator();
  mpMenuSEDMLSupport = pFileMenu->addMenu("SED-ML Support");
  mpMenuSEDMLSupport->addAction(mpaImportSEDML);
  mpMenuSEDMLSupport->addAction(mpaExportSEDML);
  mpMenuRecentSEDMLFiles = mpMenuSEDMLSupport->addMenu("Recent SED-ML Files");
  refreshRecentSEDMLFileMenu();

  pFileMenu->addSeparator();
  pFileMenu->addAction(mpaFunctionDBLoad);
  pFileMenu->addAction(mpaFunctionDBSave);
  pFileMenu->addSeparator();
  pFileMenu->addAction(mpaParameterSetsLoad);
  pFileMenu->addAction(mpaParameterSetsSave);
  pFileMenu->addSeparator();
  mpMenuRecentFiles = pFileMenu->addMenu("Recent Files");
  refreshRecentFileMenu();
  mpMenuRecentSBMLFiles = pFileMenu->addMenu("Recent SBML Files");
  refreshRecentSBMLFileMenu();
  pFileMenu->addSeparator();
  pFileMenu->addAction(mpaQuit);
  //********** edit menu ************
  QMenu *pEditMenu = menuBar()->addMenu("&Edit");
  pEditMenu->addAction(mpaCopy);
  pEditMenu->addSeparator();
  pEditMenu->addAction(mpaUndo);
  pEditMenu->addAction(mpaRedo);
  pEditMenu->addAction(mpaUndoHistory);
  pEditMenu->addSeparator();
  pEditMenu->addAction(mpaClearUndoHistory);

  //********** Version menu ************
#ifdef COPASI_Versioning
  QMenu *pVersionMenu = menuBar()->addMenu("&Version");
  pVersionMenu->addAction(mpaCreateVersion);
  pVersionMenu->addAction(mpaBrowseVersion);
#endif
  //****** tools menu **************
  mpTools = menuBar()->addMenu("&Tools");
  mpTools->addAction(mpaApplyInitialState);
  mpTools->addAction(mpaUpdateInitialState);
  mpTools->addAction(mpaSliders);
  mpTools->addAction(mpaDependencies);
  mpTools->addAction(mpaCapture);

  mpTools->addAction(mpaMergeModels);

  mpTools->addSeparator();
  mpTools->addAction(mpaExpandModel);

#ifdef COPASI_DEBUG
  mpTools->addAction(mpaObjectBrowser);
  mpTools->addAction(mpaShowDebugInfo);
  mpTools->addSeparator();
#endif // COPASI_DEBUG

  mpTools->addAction(mpaCheckModel);
  mpTools->addAction("&Convert to irreversible", this, SLOT(slotConvertToIrreversible()));
  mpTools->addAction("Create &Events For Timeseries Experiment", this, SLOT(slotCreateEventsForTimeseries()));
  mpTools->addAction("&Remove SBML Ids from model", this, SLOT(slotClearSbmlIds()));
  mpTools->addAction(mpaParameterEstimationResult);
#ifdef COPASI_SBW_INTEGRATION
  // create and populate SBW menu
  mpSBWMenu = new QMenu("&SBW", this);
  mpSBWAction = mpTools->addMenu(mpSBWMenu);
#endif // COPASI_SBW_INTEGRATION
  mpTools->addSeparator();
  mpTools->addAction(mpaUpdateMIRIAM);
  mpTools->addAction("&Preferences", this, SLOT(slotPreferences()));
  mpTools->addAction(mpaFontSelectionDialog);
#ifdef COPASI_Provenance
  mpTools->addAction(mpaProvenance);
#endif
  //****** windows menu **************
  mpWindowsMenu =  menuBar()->addMenu("&Window");
  connect(mpWindowsMenu, SIGNAL(aboutToShow()), this, SLOT(slotUpdateHideMainToolbarAction()));
  refreshWindowsMenu();

  //*******  help menu *****************
  menuBar()->addSeparator();
  QMenu *help = menuBar()->addMenu("&Help");
  help->addAction("Simple &Wizard", this, SLOT(slotTutorialWizard()));
  help->addSeparator();
  help->addAction("&Check for Update", this, SLOT(slotCheckForUpdate()));
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
  C_INT32 Answer = QMessageBox::No;
  QString tmp;

  if (str.isEmpty()) str = CopasiFileDialog::getDefaultFileName(".cps");

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
      Answer = checkSelection(this, tmp);

      if (Answer == QMessageBox::Cancel) return;
    }

  if (mpDataModelGUI && !tmp.isNull())
    {
      mpDataModelGUI->commit();

      setCursor(Qt::WaitCursor);
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotFileSaveFinished(bool)));
      mpDataModelGUI->saveModel(TO_UTF8(tmp), true);
#ifdef COPASI_Provenance
      CProvenanceXMLWriter *ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime, mpVersionHierarchy->getVersionsPathToCurrentModel());
      ProvenanceXMLWriter->updateCurrentSessionProvenance();
      //mProvenanceParentOfCurrentModel = mpVersionHierarchy->getParentOfCurrentModel();
      ProvenanceXMLWriter->updateOrigionOfProvenance(mProvenanceOfOrigionOfFile);
#endif
    }
}

void CopasiUI3Window::slotFileSaveFinished(bool success)
{
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotFileSaveFinished(bool)));

  if (success)
    {
      assert(mpDataModel != NULL);
      mpDataModel->changed(false);
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

  if (!mNewFile.isEmpty())
    {
      QString FileToLoad = mNewFile;
      mNewFile.clear();

      if (mpDeferredLoadFile != NULL)
        emit signalDefferedLoadFile(FileToLoad);
    }
}

void CopasiUI3Window::slotNewDoc(QString str)
{
  if (mCommitRequired)
    {
      mpDataModelGUI->commit();
    }

  assert(CRootContainer::getDatamodelList()->size() > 0);

  if (mpDataModelGUI &&
      (mpDataModel->isChanged() ||
       this->mpSliders->isChanged()))
    {
      switch (CQMessageBox::question(this, "COPASI",
                                     "The document contains unsaved changes\n"
                                     "Do you want to save the changes before exiting?",
                                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                     QMessageBox::Save))
        {
          case QMessageBox::Save:
            mpDeferredLoadFile = &CopasiUI3Window::slotNewDoc;
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

#ifdef COPASI_Provenance
  // Update Main Body Provenance
  CProvenanceXMLWriter provenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime);
  provenanceXMLWriter.updateMainBodyProvenace();
#endif
  //#ifdef COPASI_Versioning
  //   mpVersionHierarchy->restoreLastSavedVersioningHierarchy(mLastSavedParentOfCurrentModel);
  //#endif
  mpListView->switchToOtherWidget(ListViews::WidgetType::COPASI, std::string());
  mpDataModelGUI->notify(ListViews::ObjectType::MODEL, ListViews::DELETE,
                         mpDataModel->getModel()->getCN());

  // delete the old sliders
  if (this->mpSliders) this->mpSliders->reset();

  mpDataModelGUI->createModel();
  this->mpSliders->setChanged(false);
  mpDataModelGUI->notify(ListViews::ObjectType::MODEL, ListViews::ADD, mpDataModel->getModel()->getCN());
  //if (!mbObject_browser_open)
  //mpFileMenu->setItemEnabled(nobject_browser, true);
  mpaSave->setEnabled(true);
  mpaSaveAs->setEnabled(true);
  mpaExportSBML->setEnabled(true);
  mpaExportODE->setEnabled(true);
  mpaExportSEDML->setEnabled(true);

  updateTitle();
  mpListView->switchToOtherWidget(ListViews::WidgetType::Model, mpDataModel->getModel()->getCN(), 0);

  mSaveAsRequired = true;
  mCommitRequired = true;
#ifdef COPASI_Provenance
  //mProvenanceParentOfCurrentModel = QString("");
  mProvenanceOrigionFileType = QString("Created");
  mProvenanceOfOrigionOfFile = QString("");
  mProvenanceOrigionTime = QDateTime::currentDateTime().toString();
#endif
}

void CopasiUI3Window::openInitialDocument(const QString &file)
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

  else if (!COptions::compareValue("ImportSEDML", std::string("")))
    {
      // Import the SEDML File
      std::string ImportSEDML;
      COptions::getValue("ImportSEDML", ImportSEDML);
      slotImportSEDML(FROM_UTF8(ImportSEDML));
    }

  else if (COptions::getNonOptions().size())
    {
      // Look at commandline
      slotFileOpen(FROM_UTF8(COptions::getNonOptions()[0]));
    }
  else
    {
      slotNewDoc();
    }

#ifdef COPASI_SBW_INTEGRATION
  sbwConnect();
#endif // COPASI_SBW_INTEGRATION
}

void CopasiUI3Window::slotDefferedLoadFile(QString str)
{
  if (str.isEmpty())
    mpDeferredLoadFile = NULL;

  if (mpDeferredLoadFile == NULL)
    return;

  (this->*mpDeferredLoadFile)(str);

  mpDeferredLoadFile = NULL;
}

void CopasiUI3Window::slotFileOpen(QString file)
{
  if (mCommitRequired)
    {
      mpDataModelGUI->commit();
    }

  QString newFile = "";

  if (file == "")
    newFile =
      CopasiFileDialog::getOpenFileName(this, "Open File Dialog", QString(),
                                        "COPASI Files (*.gps *.cps);;All Files (*)",
                                        "Choose a file");
  else
    newFile = file;

  QUrl url(newFile);

  if (url.scheme() == "http" || url.scheme() == "https")
    {
      // download from url
      slotFileOpenFromUrl(file);
      return;
    }
  else if (url.scheme() == "copasi")
    {
      // handle copasi scheme
      slotHandleCopasiScheme(url);
      return;
    }

  // gives the file information to the datamodel to handle it

  if (!newFile.isNull())
    {

      if (isArchive(newFile))
        {
          slotImportCombine(newFile);
          return;
        }

      if (isProbablySEDML(newFile))
        {
          slotImportSEDML(newFile);
          return;
        }

      if (isProbablySBML(newFile))
        {
          slotImportSBML(newFile);
          return;
        }

      assert(CRootContainer::getDatamodelList()->size() > 0);

      if (mpDataModelGUI &&
          (mpDataModel->isChanged() ||
           this->mpSliders->isChanged()))
        {
          switch (CQMessageBox::question(this, "COPASI",
                                         "The document contains unsaved changes\n"
                                         "Do you want to save the changes before exiting?",
                                         QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                         QMessageBox::Save))
            {
              case QMessageBox::Save:
                mpDeferredLoadFile = &CopasiUI3Window::slotFileOpen;
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

#ifdef COPASI_Provenance
      // Update Main Body Provenace
      //CProvenanceXMLWriter* ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime, mProvenanceParentOfCurrentModel, mpVersionHierarchy->getParentOfCurrentModel());
      CProvenanceXMLWriter *ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime);
      ProvenanceXMLWriter->updateMainBodyProvenace();
#endif
      //#ifdef COPASI_Versioning
      //mpVersionHierarchy->restoreLastSavedVersioningHierarchy(mLastSavedParentOfCurrentModel);
      //#endif
      mpDataModelGUI->notify(ListViews::ObjectType::MODEL, ListViews::DELETE,
                             mpDataModel->getModel()->getCN());
      mpListView->clearCurrentWidget();
      mpListView->switchToOtherWidget(ListViews::WidgetType::COPASI, std::string());

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
#ifdef COPASI_Provenance
  //mProvenanceParentOfCurrentModel = mpVersionHierarchy->getParentOfCurrentModel();
  mProvenanceOrigionFileType = QString("Opened");
  mProvenanceOrigionTime = QDateTime::currentDateTime().toString();
#endif
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotFileOpenFinished(bool)));
  unsetCursor();
  mCommitRequired = true;
  CCopasiMessage msg = CCopasiMessage::getLastMessage();

  if (msg.getNumber() == MCXML + 3 &&
      (msg.getText().find("'sbml'") != std::string::npos || msg.getText().find(":sbml'") != std::string::npos))
    {
      // someone attempted to open an SBML file but failed, instead of displaying the message
      //   XML (3): Unknown element 'sbml' encountered at line '3'.
      // we just open the SBML file!
      if (CQMessageBox::question(this, QString("Import SBML?"), QString("You tried to open an SBML file. COPASI is not able to open SBML files but is able to import it. Would you like to import it?"),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
        {
          emit slotImportSBML(mNewFile);
          return;
        }

      slotNewDoc();
      return;
    }

  if (msg.getNumber() == 6303 &&
      (msg.getText().find("'sedML'") != std::string::npos || msg.getText().find(":sedML'") != std::string::npos))
    {
      // someone attempted to open an SEDML file but failed, instead of displaying the message
      //   XML (3): Unknown element 'sedml' encountered at line '3'.
      // we just open the SEDML file!
      if (CQMessageBox::question(this, QString("Import SED-ML?"), QString("You tried to open an SED-ML file. COPASI is not able to open SED-ML files but is able to import it. Would you like to import it?"),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
        {
          emit slotImportSEDML(mNewFile);
          return;
        }

      slotNewDoc();
      return;
    }

  if (msg.getNumber() == 6313 && isArchive(mNewFile))
    {
      // this might be a combine archive, lets ask to import it
      if (CQMessageBox::question(this, QString("Import Combine Archive?"), QString("You tried to open a COMBINE archive, would you like to import it?"),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
        {
          emit slotImportCombine(mNewFile);
          return;
        }

      slotNewDoc();
      return;
    }

  if (!success)
    {
      QString Message = "Error while loading file " + mNewFile + QString("!\n\n");
      Message += FROM_UTF8(CCopasiMessage::getAllMessageText(true));
      CQMessageBox::critical(this, QString("File Error"), Message,
                             QMessageBox::Ok, QMessageBox::Ok);
      mpDataModelGUI->createModel();
    }

  QString Message = QString();

  if (msg.getNumber() != MCCopasiMessage + 1)
    {
      Message = "Problem while loading file " + mNewFile + QString("!\n\n");
      Message += FROM_UTF8(msg.getText());
      msg = CCopasiMessage::getLastMessage();

      while (msg.getNumber() != MCCopasiMessage + 1)
        {
          Message += "\n";
          Message += FROM_UTF8(msg.getText());
          msg = CCopasiMessage::getLastMessage();
        }
    }

  if (strcasecmp(CDirEntry::suffix(TO_UTF8(mNewFile)).c_str(), ".cps") == 0 &&
      CDirEntry::isWritable(TO_UTF8(mNewFile)))
    mSaveAsRequired = false;
  else
    mSaveAsRequired = true;

  if (!mpDataModel->getModel())
    {
      slotNewDoc();
      mSaveAsRequired = true;
    }

  mpDataModelGUI->notify(ListViews::ObjectType::MODEL, ListViews::ADD,
                         mpDataModel->getModel()->getCN());
  mpaSave->setEnabled(true);
  mpaSaveAs->setEnabled(true);
  mpaExportSBML->setEnabled(true);
  mpaExportODE->setEnabled(true);
  mpaExportSEDML->setEnabled(true);

  updateTitle();
  mpListView->switchToOtherWidget(ListViews::WidgetType::Model, mpDataModel->getModel()->getCN(), 0);

  refreshRecentFileMenu();
  mNewFile.clear();

  if (!Message.isNull())

    CQMessageBox::warning(this, QString("File Warning"), Message,
                          QMessageBox::Ok, QMessageBox::Ok);

  performNextAction();
}

void CopasiUI3Window::slotFileExamplesCopasiFiles(QString file)
{
  CopasiFileDialog::openExampleDir(this); //Sets CopasiFileDialog::LastDir
  slotFileOpen(file);
}

void CopasiUI3Window::slotFileExamplesSBMLFiles(QString file)
{
  CopasiFileDialog::openExampleDir(this); //Sets CopasiFileDialog::LastDir
  slotImportSBML(file);
}

void CopasiUI3Window::slotAddFileOpen(QString file)
{
  if (mCommitRequired)
    {
      mpDataModelGUI->commit();
    }

  QString newFile = "";

  if (file.isEmpty())
    newFile =
      CopasiFileDialog::getOpenFileName(this, "Open File Dialog", QString(),
                                        "All Supported Files(*.gps *.cps *.sbml *.xml);;COPASI Files (*.gps *.cps);;SBML Files (*.xml *.sbml);;All Files (*)",
                                        "Choose a file");
  else
    newFile = file;

  if (!newFile.isEmpty())
    {
      assert(CRootContainer::getDatamodelList()->size() > 0);
      //mpListView->switchToOtherWidget(0, std::string());
      this->setCursor(Qt::WaitCursor);
      CCopasiMessage::clearDeque();
      mNewFile = newFile;
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotAddFileOpenFinished(bool)));
      mpDataModelGUI->addModel(TO_UTF8(newFile));
    }
}

void CopasiUI3Window::slotAddFileOpenFinished(bool success)
{
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotAddFileOpenFinished(bool)));
  unsetCursor();
  mCommitRequired = true;

  if (!success)
    {
      QString Message = "Error while loading file " + mNewFile + QString("!\n\n");
      Message += FROM_UTF8(CCopasiMessage::getAllMessageText(true));
      CQMessageBox::critical(this, QString("File Error"), Message,
                             QMessageBox::Ok, QMessageBox::Ok);
    }

  CCopasiMessage msg = CCopasiMessage::getLastMessage();

  // TODO potentially include handling of SBML files here.

  if (msg.getNumber() != MCCopasiMessage + 1)
    {
      QString Message = "Problem while merging file " + mNewFile + QString("!\n\n");
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

  mpDataModel->changed();
  mpaSave->setEnabled(true);
  mpaSaveAs->setEnabled(true);
  mpaExportSBML->setEnabled(true);
  mpaExportODE->setEnabled(true);
  mpaExportSEDML->setEnabled(true);

  refreshRecentFileMenu();
  mNewFile.clear();
  mpDataModelGUI->notify(ListViews::ObjectType::MODEL, ListViews::CHANGE, std::string());
}

void CopasiUI3Window::slotFileSave()
{
  //  mpDataModelGUI->commit(); --> remove to the line after checking the following condition (07.04.08)
  assert(CRootContainer::getDatamodelList()->size() > 0);
  std::string FileName = mpDataModel->getFileName();

  if (mSaveAsRequired || FileName == "")
    {
      return slotFileSaveAs(FROM_UTF8(FileName));
    }

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
            mNewFile.clear();
            return;
            break;
        }
    }

  if (mpDataModelGUI)
    {
      mpDataModelGUI->commit();

      setCursor(Qt::WaitCursor);
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotFileSaveFinished(bool)));
      mpDataModelGUI->saveModel(FileName, true);
#ifdef COPASI_Provenance
      //update Current Session Provenance and Origion of Provenance
      //CProvenanceXMLWriter* ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime, mProvenanceParentOfCurrentModel, mpVersionHierarchy->getParentOfCurrentModel(), mpVersionHierarchy->getVersionsPathToCurrentModel());
      CProvenanceXMLWriter *ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime, mpVersionHierarchy->getVersionsPathToCurrentModel());
      ProvenanceXMLWriter->updateCurrentSessionProvenance();
      //mProvenanceParentOfCurrentModel = mpVersionHierarchy->getParentOfCurrentModel();
      ProvenanceXMLWriter->updateOrigionOfProvenance(mProvenanceOfOrigionOfFile);
#endif
      //#ifdef COPASI_Versioning
      //  mLastSavedParentOfCurrentModel = mpVersionHierarchy->getParentOfCurrentModel();
      //#endif
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
  assert(CRootContainer::getDatamodelList()->size() > 0);

  if (mpDataModelGUI &&
      (mpDataModel->isChanged() ||
       this->mpSliders->isChanged()))
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

#ifdef COPASI_Provenance
  //CProvenanceXMLWriter* ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime, mProvenanceParentOfCurrentModel, mpVersionHierarchy->getParentOfCurrentModel());
  CProvenanceXMLWriter ProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime);
  ProvenanceXMLWriter.updateMainBodyProvenace();
#endif
  //#ifdef COPASI_Versioning
  //   mpVersionHierarchy->restoreLastSavedVersioningHierarchy(mLastSavedParentOfCurrentModel);
  //#endif
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

void CopasiUI3Window::closeEvent(QCloseEvent *ce)
{
  // We handle this internally.
  ce->ignore();
  slotQuit();
  return;
}

// Cleanup all the temp .cps files created at runtime.
void CopasiUI3Window::CleanUp()
{
  emit signalQuit();
  std::string tempDir;
  COptions::getValue("Tmp", tempDir);
  CDirEntry::removeFiles("*.cps", tempDir);
  CDirEntry::remove(tempDir);

  // store window sizes
  QSettings settings(FROM_UTF8(COptions::getConfigDir() + "/" + "ui_settings.ini"), QSettings::IniFormat, this);
  settings.setValue("mainwindow/size", size());

  if (mpSliders != NULL)
    settings.setValue("slider/size", mpSliders->size());

  settings.sync();
}

void CopasiUI3Window::slotFilePrint()
{}

void CopasiUI3Window::about()
{
  QString text = AboutDialog::getDefaultVersionText();

  AboutDialog *aboutDialog = new AboutDialog(this, text, 76, 30);
  aboutDialog->setWindowTitle(FixedTitle);
  aboutDialog->exec();
}

void CopasiUI3Window::license()
{
  AboutDialog *aboutDialog = new AboutDialog(this, CRootContainer::getLicenseHTML(), 76, 30);
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
  CQPreferenceDialog *preferenceDialog = new CQPreferenceDialog(this);
  connect(preferenceDialog, SIGNAL(accepted()), this, SLOT(slotPreferencesAccepted()));

  preferenceDialog->setAttribute(Qt::WA_DeleteOnClose);
  preferenceDialog->setModal(true);
  preferenceDialog->show();
}

void CopasiUI3Window::slotPreferencesAccepted()
{
  emit signalPreferenceUpdated();
  // save settings
  CRootContainer::getConfiguration()->save();
}

void CopasiUI3Window::slotTutorialWizard()
{
  WizardDialog *tutorialWizard = new WizardDialog();
  tutorialWizard->setCopasiMainWindow(this);
  tutorialWizard->show();
}

void CopasiUI3Window::importSBMLFromString(const std::string &sbmlDocumentText)
{
  if (mCommitRequired)
    {
      mpDataModelGUI->commit();
    }

  if (!sbmlDocumentText.empty())
    {
      assert(CRootContainer::getDatamodelList()->size() > 0);

      if (mpDataModelGUI &&
          (mpDataModel->isChanged() ||
           this->mpSliders->isChanged()))
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

#ifdef COPASI_Provenance
      //Update Main Body Provenance
      //CProvenanceXMLWriter* ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime, mProvenanceParentOfCurrentModel, mpVersionHierarchy->getParentOfCurrentModel());
      CProvenanceXMLWriter *ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime);
      ProvenanceXMLWriter->updateMainBodyProvenace();
#endif
      //#ifdef COPASI_Versioning
      //   mpVersionHierarchy->restoreLastSavedVersioningHierarchy(mLastSavedParentOfCurrentModel);
      //#endif
      mpDataModelGUI->notify(ListViews::ObjectType::MODEL, ListViews::DELETE,
                             mpDataModel->getModel()->getCN());
      mpListView->switchToOtherWidget(ListViews::WidgetType::COPASI, std::string());
      setCursor(Qt::WaitCursor);
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotImportSBMLFromStringFinished(bool)));
      mpDataModelGUI->importSBMLFromString(sbmlDocumentText);
    }
}

void CopasiUI3Window::slotImportSBMLFromStringFinished(bool success)
{
#ifdef COPASI_Provenance
  //mProvenanceParentOfCurrentModel = QString("");
  mProvenanceOrigionFileType = QString("Imported");
  mProvenanceOrigionTime = QDateTime::currentDateTime().toString();
#endif
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

  mpDataModelGUI->notify(ListViews::ObjectType::MODEL, ListViews::ADD,
                         mpDataModel->getModel()->getCN());
  //if (!bobject_browser_open)
  //       mpFileMenu->setItemEnabled(nsaveas_menu_id, true);
  //       msave_button->setEnabled(true);
  //       mpFileMenu->setItemEnabled(nsave_menu_id, true);
  mpListView->switchToOtherWidget(ListViews::WidgetType::Model, mpDataModel->getModel()->getCN(), 0);

  updateTitle();
  mSaveAsRequired = true;
}

void CopasiUI3Window::slotImportSBML(QString file)
{
  if (mCommitRequired)
    {
      mpDataModelGUI->commit();
    }

  QString SBMLFile;

  if (file == "")
    SBMLFile =
      CopasiFileDialog::getOpenFileName(this, "Open File Dialog",
                                        QString(), "SBML Files (*.xml *.sbml);;All Files (*)",
                                        "Choose a file");
  else
    SBMLFile = file;

  if (!SBMLFile.isNull())
    {
      assert(mpDataModel != NULL);

      if (mpDataModelGUI &&
          (mpDataModel->isChanged() ||
           this->mpSliders->isChanged()))
        {
          switch (CQMessageBox::question(this, "COPASI",
                                         "The document contains unsaved changes\n"
                                         "Do you want to save the changes before exiting?",
                                         QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                         QMessageBox::Save))
            {
              case QMessageBox::Save:
                mpDeferredLoadFile = &CopasiUI3Window::slotImportSBML;
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

#ifdef COPASI_Provenance
      // Update Main Body Provenance
      //CProvenanceXMLWriter* ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime, mProvenanceParentOfCurrentModel, mpVersionHierarchy->getParentOfCurrentModel());
      CProvenanceXMLWriter *ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime);
      ProvenanceXMLWriter->updateMainBodyProvenace();
#endif
      //#ifdef COPASI_Versioning
      //   mpVersionHierarchy->restoreLastSavedVersioningHierarchy(mLastSavedParentOfCurrentModel);
      //#endif
      mpDataModelGUI->notify(ListViews::ObjectType::MODEL, ListViews::DELETE,
                             mpDataModel->getModel()->getCN());
      mpListView->switchToOtherWidget(ListViews::WidgetType::COPASI, std::string());

      if (this->mpSliders) this->mpSliders->reset();

      setCursor(Qt::WaitCursor);
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotImportSBMLFinished(bool)));
      mNewFile = SBMLFile;
      mpDataModelGUI->importSBML(TO_UTF8(SBMLFile));
    }
}

void CopasiUI3Window::slotImportSBMLFinished(bool success)
{
#ifdef COPASI_Provenance
  //mProvenanceParentOfCurrentModel = QString("");
  mProvenanceOrigionFileType = QString("Imported");
  mProvenanceOrigionTime = QDateTime::currentDateTime().toString();
#endif
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

  mpDataModelGUI->notify(ListViews::ObjectType::MODEL, ListViews::ADD,
                         mpDataModel->getModel()->getCN());
  mpaSave->setEnabled(true);
  mpaSaveAs->setEnabled(true);
  mpaExportSBML->setEnabled(true);
  mpaExportODE->setEnabled(true);
  mpListView->switchToOtherWidget(ListViews::WidgetType::Model, mpDataModel->getModel()->getCN(), 0);

  refreshRecentSBMLFileMenu();
  updateTitle();
  mSaveAsRequired = true;
  mNewFile.clear();
  performNextAction();
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
      assert(mpDataModel != NULL);

      // if there already is an SBML model, we present the user with the Level
      // and Version of that document as the selected Level and Version to
      // export to.
      if (mpDataModel->getCurrentSBMLDocument() != NULL)
        {
          sbmlLevel = mpDataModel->getCurrentSBMLDocument()->getLevel();
          sbmlVersion = mpDataModel->getCurrentSBMLDocument()->getVersion();
        }

      std::pair<QString, std::pair<unsigned C_INT32, unsigned C_INT32> > nameAndVersion =
        CQSBMLFileDialog::getSaveFileName(this, "Export SBML Dialog", CopasiFileDialog::getDefaultFileName(".xml"),
                                          "Choose a filename and SBML version for SBML export.",
                                          sbmlLevel,
                                          sbmlVersion);
      tmp = nameAndVersion.first;
      sbmlLevel = nameAndVersion.second.first;
      sbmlVersion = nameAndVersion.second.second;

      if (tmp.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(this, tmp);

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
  assert(mpDataModel != NULL);
  QString *userFilter = new QString;

  while (Answer == QMessageBox::No)
    {
      tmp =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                          CopasiFileDialog::getDefaultFileName(".c"),
                                          "C Files (*.c);;Berkeley Madonna Files (*.mmd);;XPPAUT (*.ode)",
                                          "Choose an export format", userFilter);

      if (tmp.isEmpty()) return;

#ifdef DEBUG_UI
      qDebug() << "user's filter pointer = " << *userFilter;
#endif
      // Checks whether the file exists
      Answer = checkSelection(this, tmp);

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
void CopasiUI3Window::slotCreateEventsForTimeseries()
{
  if (mpDataModel == NULL) return;

  CModel *pModel = mpDataModel->getModel();

  if (pModel == NULL) return;

  mpDataModelGUI->commit();
  mpListView->switchToOtherWidget(ListViews::WidgetType::Events, std::string());
  CCopasiMessage::clearDeque();

  if (!pModel->createEventsForTimeseries())
    {
      // Display error messages.
      CQMessageBox::information(this, "Event Creation Failed",
                                CCopasiMessage::getAllMessageText().c_str(),
                                QMessageBox::Ok,
                                QMessageBox::Ok);
      CCopasiMessage::clearDeque();
    }

  // show any warning messages that occured
  if (CCopasiMessage::size() != 0)
    {
      // Display warnings messages.
      CQMessageBox::information(this, "Event Creation succeeded with warnings",
                                CCopasiMessage::getAllMessageText().c_str(),
                                QMessageBox::Ok,
                                QMessageBox::Ok);
      CCopasiMessage::clearDeque();
    }

  mpDataModel->changed();
  mpDataModelGUI->notify(ListViews::ObjectType::MODEL, ListViews::CHANGE, std::string());
}

void CopasiUI3Window::slotConvertToIrreversible()
{
  assert(mpDataModel != NULL);
  CModel *pModel = mpDataModel->getModel();

  if (!pModel) return;

  mpDataModelGUI->commit();
  mpListView->switchToOtherWidget(ListViews::WidgetType::Reactions, std::string());
  CCopasiMessage::clearDeque();

  if (!pModel->convert2NonReversible())
    {
      // Display error messages.
      CQMessageBox::information(this, "Conversion Failed",
                                CCopasiMessage::getAllMessageText().c_str(),
                                QMessageBox::Ok | QMessageBox::Default,
                                QMessageBox::NoButton);
      CCopasiMessage::clearDeque();
    }

  mpDataModel->changed();
  mpDataModelGUI->notify(ListViews::ObjectType::MODEL, ListViews::CHANGE, std::string());
}

void CopasiUI3Window::slotShowSliders(bool flag)
{
  mpaSliders->setChecked(flag);
  this->mpSliders->setHidden(!flag);

  if (flag)
    addWindow(this->mpSliders);
  else
    removeWindow(this->mpSliders);
}

void CopasiUI3Window::slotUpdateHideMainToolbarAction()
{
  if (mpMainToolbar != NULL &&
      mpaHideMainToolbar != NULL)
    {
      mpaHideMainToolbar->setChecked(mpMainToolbar->isHidden());
    }
}

void CopasiUI3Window::slotHideMainToolbar(bool flag)
{
  if (flag)
    mpMainToolbar->hide();
  else
    mpMainToolbar->show();
}

void CopasiUI3Window::slotCopy()
{
  QWidget* pWidget = focusWidget();

  if (pWidget == NULL)
    return;

  QAbstractItemView* pView = qobject_cast<QAbstractItemView*>(pWidget);

  if (pView != NULL)
    {
      QApplication::clipboard()->setText(toTsvString(pView));
      return;
    }

  QTextEdit* pEdit = qobject_cast<QTextEdit*>(pWidget);

  if (pEdit != NULL)
    {
      if (pEdit->textCursor().selectedText().isEmpty())
        pEdit->selectAll();

      pEdit->copy();
      return;
    }

  QLineEdit* pLineEdit = qobject_cast<QLineEdit*>(pWidget);

  if (pLineEdit != NULL)
    {
      if (pLineEdit->selectedText().isEmpty())
        pLineEdit->selectAll();

      pLineEdit->copy();
      return;
    }
}

void CopasiUI3Window::slotShowDependencies(bool flag)
{
  mpaDependencies->setChecked(flag);
  this->mpDependencies->setHidden(!flag);

  if (flag)
    {
      addWindow(this->mpDependencies);

      if (mpDependencies->getCurrentKey() != mpListView->getCurrentItemRegisteredCN())
        mpDependencies->loadFrom(mpListView->getCurrentItemRegisteredCN());
    }
  else
    removeWindow(this->mpDependencies);
}

DataModelGUI *CopasiUI3Window::getDataModel()
{return mpDataModelGUI;}

void CopasiUI3Window::listViewsFolderChanged(const QModelIndex &)
{
  ListViews::WidgetType id = mpListView->getCurrentItemId();
  this->mpSliders->setCurrentFolderId(id);

  if (mpDependencies->isVisible())
    mpDependencies->loadFrom(mpListView->getCurrentItemRegisteredCN());

  refreshWindowsMenu();
}

ListViews *CopasiUI3Window::getMainWidget()
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
  QString FileName = FROM_UTF8(mpDataModel->getFileName());
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
#ifdef COPASI_Provenance
  mProvenanceOfOrigionOfFile = FROM_UTF8(CDirEntry::baseName(TO_UTF8(FileName)));
#endif
}

void CopasiUI3Window::autoSave()
{
  // TODO CRITICAL This needs to be moved into a sub thread so
  // that a progress dialog can be displayed and the user can interrupt.
  if (!mSuspendAutoSave)
    {
      mSuspendAutoSave = true;
      assert(mpDataModel != NULL);
      mpDataModel->autoSave();
      mSuspendAutoSave = false;
    }

  mpAutoSaveTimer->setInterval(AutoSaveInterval); // restart the timer
}

void CopasiUI3Window::suspendAutoSave(const bool &suspend)
{
  mSuspendAutoSave = suspend;

  if (!mSuspendAutoSave)
    mpAutoSaveTimer->setInterval(AutoSaveInterval); // restart the timer
}

void CopasiUI3Window::slotOpenRecentFile(QAction *pAction)
{
  int index = mRecentFilesActionMap[pAction];
  std::string FileName =
    CRootContainer::getConfiguration()->getRecentFiles().getGroup("Recent Files")->getValue< std::string >(index);
  slotFileOpen(FROM_UTF8(FileName));
}

void CopasiUI3Window::slotOpenRecentSBMLFile(QAction *pAction)
{
  int index = mRecentSBMLFilesActionMap[pAction];
  std::string FileName =
    CRootContainer::getConfiguration()->getRecentSBMLFiles().getGroup("Recent Files")->getValue< std::string >(index);
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
  QAction *pAction;
  CCopasiParameterGroup::index_iterator it =
    CRootContainer::getConfiguration()->getRecentFiles().getGroup("Recent Files")->beginIndex();
  CCopasiParameterGroup::index_iterator end =
    CRootContainer::getConfiguration()->getRecentFiles().getGroup("Recent Files")->endIndex();
  C_INT Index = 0;

  for (; it != end; ++it, ++Index)
    {
      std::string recentFile = (*it)->getValue< std::string >();

      if (!CDirEntry::exist(recentFile))
        continue;

      pAction = new QAction(FROM_UTF8(recentFile), mpRecentFilesActionGroup);
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
  QAction *pAction;
  CCopasiParameterGroup::index_iterator it =
    CRootContainer::getConfiguration()->getRecentSBMLFiles().getGroup("Recent Files")->beginIndex();
  CCopasiParameterGroup::index_iterator end =
    CRootContainer::getConfiguration()->getRecentSBMLFiles().getGroup("Recent Files")->endIndex();
  C_INT Index = 0;

  for (; it != end; ++it, ++Index)
    {
      std::string recentFile = (*it)->getValue< std::string >();

      if (!CDirEntry::exist(recentFile))
        continue;

      pAction = new QAction(FROM_UTF8(recentFile), mpRecentSBMLFilesActionGroup);
      mpMenuRecentSBMLFiles->addAction(pAction);
      mRecentSBMLFilesActionMap[pAction] = Index;
    }
}

void CopasiUI3Window::exportSBMLToString(std::string &SBML)
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

const QMap< QPointer<QMainWindow>, QPointer<QAction> > &CopasiUI3Window::getWindows() const
{
  return mWindows;
}

CQOptPopulation *
CopasiUI3Window::getPopulationDisplay()
{
  if (mpPopulationDisplay == NULL)
    {
      mpPopulationDisplay = new CQOptPopulation(mpDataModel, this);
    }

  return mpPopulationDisplay;
}

void CopasiUI3Window::setPopulationDisplay(CQOptPopulation *display)
{
  mpPopulationDisplay = display;
}

void CopasiUI3Window::addWindow(QMainWindow *pWindow)
{
  if (mWindows.contains(pWindow))
    {
      return;
    }

  mWindows.insert(pWindow, NULL);

  refreshWindowsMenu();
}

void CopasiUI3Window::removeWindow(QMainWindow *pWindow)
{

  QMap< QPointer<QMainWindow>, QPointer<QAction> >::iterator found = mWindows.find(pWindow);

  if (found == mWindows.end())
    {
      return;
    }

  mWindows.erase(found);

  refreshWindowsMenu();
}

void CopasiUI3Window::refreshWindowsMenu()
{
  // (I assume a QActionGroup was used, so only one window will be activated at a time)
  if (mpWindowsActionGroup != NULL)
    {
      disconnect(mpWindowsActionGroup, SIGNAL(triggered(QAction *)), this, SLOT(slotActivateWindowTriggered(QAction *)));
      mpWindowsActionGroup->deleteLater();
      mpWindowsActionGroup = NULL;
    }

  mpWindowsActionGroup = new QActionGroup(this);
  connect(mpWindowsActionGroup, SIGNAL(triggered(QAction *)), this, SLOT(slotActivateWindowTriggered(QAction *)));
  // Re-initialize items the menus will always have
  mpWindowsMenu->clear();

  // COPASI main window

  QAction *pAction = new QAction(pMainWindow->windowTitle(), mpWindowsActionGroup);
  mWindows[pMainWindow] = pAction;
  mpWindowsMenu->addAction(pAction);

  if (mWindows.count() > 1)
    {
      mpWindowsMenu->addSeparator();
      mpWindowsMenu->addAction(mpaCloseAllWindows);
      mpWindowsMenu->addSeparator();
    }

  // . . . for the secondary windows, also . . .
  QMap< QPointer<QMainWindow>, QPointer<QAction> >::iterator it = mWindows.begin();
  QMap< QPointer<QMainWindow>, QPointer<QAction> >::iterator end = mWindows.end();

  for (; it != end; ++it)
    {
      QMainWindow *mainWindow = it.key();

      if (mainWindow == pMainWindow ||
          mainWindow == NULL)
        {
          continue;
        }

      CWindowInterface *window = dynamic_cast<CWindowInterface *>(mainWindow);
      QMenu *menu = window->getWindowMenu();
      menu->clear();
      menu->addAction(pAction);
      menu->addSeparator();
      menu->addAction(mpaCloseAllWindows);
      menu->addSeparator();
    }

  // Add secondary windows to the Window menus
  for (it = mWindows.begin(); it != end; ++it)
    {
      QMainWindow *mActionWindow = it.key();

      if (mActionWindow == pMainWindow ||
          mActionWindow == NULL)
        {
          continue;
        }

      pAction = new QAction(mActionWindow->windowTitle(), mpWindowsActionGroup);
      it.value() = pAction;
      mpWindowsMenu->addAction(pAction);

      QMap< QPointer<QMainWindow>, QPointer<QAction> >::iterator jt = mWindows.begin();

      for (; jt != end; ++jt)
        {
          QMainWindow *mainWindow = jt.key();

          if (mainWindow == pMainWindow ||
              mainWindow == NULL)
            {
              continue;
            }

          CWindowInterface *window = dynamic_cast<CWindowInterface *>(mainWindow);
          QMenu *menu = window->getWindowMenu();
          menu->addAction(pAction);
        }
    }

  mpWindowsMenu->addSeparator();
  mpWindowsMenu->addAction(mpaHideMainToolbar);
}

void CopasiUI3Window::slotCloseAllWindows()
{
  // all except main window (index == 0)
  QMap< QPointer<QMainWindow>, QPointer<QAction> >::iterator it = mWindows.begin();
  QMap< QPointer<QMainWindow>, QPointer<QAction> >::iterator end = mWindows.end();
  QList< QPointer<QMainWindow> > ToBeClosed;

  for (; it != end; ++it)
    {
      QMainWindow *mainWindow = it.key();

      if (mainWindow == pMainWindow ||
          mainWindow == NULL)
        {
          continue;
        }

      ToBeClosed.append(mainWindow);
    }

  QList< QPointer<QMainWindow> >::iterator itToBeClosed = ToBeClosed.begin();
  QList< QPointer<QMainWindow> >::iterator endToBeClosed = ToBeClosed.end();

  for (; itToBeClosed != endToBeClosed; ++itToBeClosed)
    {
      (*itToBeClosed)->close();
    }

  refreshWindowsMenu();
}

void CopasiUI3Window::slotActivateWindowTriggered(QAction *action)
{
  QMainWindow *window = getWindowForAction(mWindows, action);

  if (window != NULL)
    {
      window ->setWindowState((windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
      window ->raise(); // necessary for macOS
      window ->activateWindow();
    }
}

void CopasiUI3Window::setMessageShown(const bool &shown)
{
  mMessageShown = shown;
}

const bool &CopasiUI3Window::messageShown() const
{
  return mMessageShown;
}

#include "copasi/model/CModelAnalyzer.h"
void CopasiUI3Window::slotCheckModel()
{
  assert(mpDataModel != NULL);
  CModelAnalyzer *analyzer = new CModelAnalyzer(mpDataModel->getModel());
  CQCheckModelWindow *checkModelWindow = new CQCheckModelWindow(this);
  checkModelWindow->setAnalyzer(analyzer);
  checkModelWindow->show();
}

void CopasiUI3Window::slotUpdateMIRIAMFinished(bool success)
{
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotUpdateMIRIAMFinished(bool)));
  QCursor oldCursor = cursor();
  setCursor(Qt::WaitCursor);

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
      CRootContainer::getConfiguration()->save();
      CMIRIAMResourceObject::setMIRIAMResources(
        &CRootContainer::getConfiguration()->getRecentMIRIAMResources());
      mpDataModelGUI->updateMIRIAMResourceContents();
      this->checkPendingMessages();
    }

  CCopasiMessage::clearDeque();
  mpListView->switchToOtherWidget(ListViews::WidgetType::COPASI, std::string());
  setCursor(oldCursor);
}

void CopasiUI3Window::slotUpdateMIRIAM()
{
  bool success = true;
  CCopasiMessage::clearDeque();
  connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotUpdateMIRIAMFinished(bool)));

  try
    {
      success = mpDataModelGUI->updateMIRIAM(
                  CRootContainer::getConfiguration()->getRecentMIRIAMResources());
    }
  catch (...)
    {
      success = false;
    }
}

void CopasiUI3Window::slotApplyInitialState()
{
  mpDataModelGUI->commit();
  assert(mpDataModel != NULL);
  CModel *pModel = mpDataModel->getModel();

  if (pModel != NULL)
    {
      pModel->compileIfNecessary(NULL);
      pModel->applyInitialValues();
      mpDataModelGUI->notify(ListViews::ObjectType::STATE, ListViews::CHANGE, pModel->getCN());
    }
}

void CopasiUI3Window::slotUpdateInitialState()
{
  mpDataModelGUI->commit();
  assert(mpDataModel != NULL);
  CModel *pModel = mpDataModel->getModel();

  if (pModel != NULL)
    {
      pModel->compileIfNecessary(NULL);
      pModel->stateToIntialState();
      mpDataModelGUI->notify(ListViews::ObjectType::STATE, ListViews::CHANGE, mpDataModel->getModel()->getCN());
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
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  QPixmap pixmap = mpListView->getCurrentWidget()->grab();
#else
  QPixmap pixmap = QPixmap::grabWidget(mpListView->getCurrentWidget());
#endif
  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      fileName = CopasiFileDialog::getSaveFileName(this,
                 "Save File Dialog", CopasiFileDialog::getDefaultFileName(".png"), "PNG Files (*.png)", "Save Capture as PNG file");

      if (fileName.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(this, fileName);

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
      CRootContainer::getConfiguration()->setApplicationFont(TO_UTF8(Font.toString()));
      CRootContainer::getConfiguration()->save();

      qApp->setFont(Font);
      // The stylesheet (set in CQCopasiApplication.cpp) is apparently overriding
      // in newer versions of Qt
      // This appears to reload the font from setFont into the style.
      // Two calls so that the tabwidget labels are correct
      qApp->setStyleSheet(" * {font : }");
      qApp->setStyleSheet(" * {font : }");

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
  std::string ApplicationFont = CRootContainer::getConfiguration()->getApplicationFont();

  if (ApplicationFont == "")
    {
      return;
    }

  QFont Font = qApp->font();

  if (ApplicationFont == TO_UTF8(Font.toString()))
    {
      // We are using the default
      CRootContainer::getConfiguration()->setApplicationFont("");
      return;
    }

  // The user has chosen another font
  Font.fromString(FROM_UTF8(ApplicationFont));
  qApp->setFont(Font);
  // This appears to load the fonts, etc. from the previous configuration.
  // Two calls so that the tabwidget labels are correct
  qApp->setStyleSheet(" * {font : }");
  qApp->setStyleSheet(" * {font : }");
}

void CopasiUI3Window::slotAutoCheckForUpdates()
{

  if (CRootContainer::getConfiguration()->getCheckForUpdates().needToConfirmCheckForUpdate())
    {
      QMessageBox::StandardButton result = CQMessageBox::question(this, "Enable check for updates?",
                                           "This version of COPASI can notify you in case a new version of COPASI is available. You can change the frequency of the checks (default weekly), or enable/disable the check later in the Preferences dialog. To manually check for an update use 'Help\\Check for Update' at any time.\n\nWould you like to enable the automatic update feature?",
                                           QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No,
                                           QMessageBox::StandardButton::No);

      CRootContainer::getConfiguration()->getCheckForUpdates().setEnabled(result == QMessageBox::StandardButton::Yes);
      CRootContainer::getConfiguration()->getCheckForUpdates().setConfirmedCheckForUpdate(true);
      CRootContainer::getConfiguration()->save();
    }

  if (!CRootContainer::getConfiguration()->getCheckForUpdates().checkRequired()) return;

  mAutoUpdateCheck = true;
  slotCheckForUpdate();
}

#include "copasi/UI/CQExpandModelData.h"
void CopasiUI3Window::slotExpandModel()
{
  CQExpandModelData *widget = new CQExpandModelData(this, mpDataModel->getModel());
  widget->exec();
  mpDataModelGUI->notify(ListViews::ObjectType::MODEL, ListViews::CHANGE, std::string());
}

#include "copasi/UI/CQMergingData.h"

void CopasiUI3Window::slotMergeModels()
{
  mpDataModelGUI->notify(ListViews::ObjectType::MODEL, ListViews::CHANGE, std::string());
  assert(mpDataModel != NULL);
  CModel *pModel = mpDataModel->getModel();
  CQMergingData *widget = new CQMergingData(NULL, pModel, Qt::WindowFlags());
  widget->exec();
  mpDataModelGUI->notify(ListViews::ObjectType::MODEL, ListViews::CHANGE, std::string());
}

#ifdef COPASI_SBW_INTEGRATION
// Create 2 custom events, one containing the filename to an SBML document to be loaded
// into COPASI
CopasiUI3Window::QSBWSBMLEvent::QSBWSBMLEvent(const std::string &SBMLModel):
  QEvent((QEvent::Type)65433),
  mSBML(SBMLModel)
{}

const std::string &CopasiUI3Window::QSBWSBMLEvent::getSBMLModel() const
{return mSBML;}

CopasiUI3Window::QSBWShutdownEvent::QSBWShutdownEvent():
  QEvent((QEvent::Type)65434)
{}

void CopasiUI3Window::registerMethods(SystemsBiologyWorkbench::MethodTable< CopasiUI3Window > &table)
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

void CopasiUI3Window::customEvent(QEvent *event)
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

void CopasiUI3Window::sbwUnregister(const std::string &moduleName) const
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
          QAction *pAction = new QAction("Register", mpSBWActionGroup);
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
          QAction *pAction = new QAction(itMap.key(), mpSBWActionGroup);
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

void CopasiUI3Window::sbwSlotMenuTriggered(QAction *pAction)
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
          int nModule = SBWLowLevel::getModuleInstance(TO_UTF8(mSBWAnalyzerModules[mSBWActionId]));
          int nService = SBWLowLevel::moduleFindServiceByName(nModule, TO_UTF8(mSBWAnalyzerServices[mSBWActionId]));
          int nMethod = SBWLowLevel::serviceGetMethod(nModule, nService, "void doAnalysis(string)");
          DataBlockWriter args;
          args << mSBWDocumentString;
          SBWLowLevel::methodSend(nModule, nService, nMethod, args);
        }
      catch (SBWException *pE)
        {
          CQMessageBox::critical(this, "SBW Error",
                                 FROM_UTF8(pE->getMessage()),
                                 QMessageBox::Ok | QMessageBox::Default,
                                 QMessageBox::NoButton);
        }
    }

  mSBWDocumentString = "";
}

std::vector< DataBlockReader > CopasiUI3Window::sbwFindServices(const std::string &category,
    const bool &recursive)
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
#include <QtCore/QUrl>
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
  if (mpSliders == NULL)
    return;

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

void CopasiUI3Window::slotFileExamplesSEDMLFiles(QString file)
{
  CopasiFileDialog::openExampleDir(this); //Sets CopasiFileDialog::LastDir
  slotImportSEDML(file);
}
void CopasiUI3Window::slotImportSEDMLFromStringFinished(bool success)
{
#ifdef COPASI_Provenance
  //mProvenanceParentOfCurrentModel = QString("");
  mProvenanceOrigionFileType = QString("Imported");
  mProvenanceOrigionTime = QDateTime::currentDateTime().toString();
#endif
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotImportSEDMLFromStringFinished(bool)));
  unsetCursor();
  mCommitRequired = true;

  if (!success)
    {
      QString Message = "Error while importing SED-ML model!\n\n";
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

  mpDataModelGUI->notify(ListViews::ObjectType::MODEL, ListViews::ADD,
                         mpDataModel->getModel()->getCN());
  //if (!bobject_browser_open)
  //       mpFileMenu->setItemEnabled(nsaveas_menu_id, true);
  //       msave_button->setEnabled(true);
  //       mpFileMenu->setItemEnabled(nsave_menu_id, true);
  mpListView->switchToOtherWidget(ListViews::WidgetType::Model, mpDataModel->getModel()->getCN(), 0);

  updateTitle();
  mSaveAsRequired = true;
}

void CopasiUI3Window::slotImportSEDMLFinished(bool success)
{
#ifdef COPASI_Provenance
  //mProvenanceParentOfCurrentModel = QString("");
  mProvenanceOrigionFileType = QString("Imported");
  mProvenanceOrigionTime = QDateTime::currentDateTime().toString();
#endif
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotImportSEDMLFinished(bool)));
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

  mpDataModelGUI->notify(ListViews::ObjectType::MODEL, ListViews::ADD,
                         mpDataModel->getModel()->getCN());
  mpaSave->setEnabled(true);
  mpaSaveAs->setEnabled(true);
  mpaExportSEDML->setEnabled(true);
  //  mpaExportODE->setEnabled(true);
  mpListView->switchToOtherWidget(ListViews::WidgetType::Model, mpDataModel->getModel()->getCN(), 0);

  refreshRecentSEDMLFileMenu();
  updateTitle();
  mSaveAsRequired = true;
  mNewFile.clear();
}
void CopasiUI3Window::slotImportSEDML(QString file)
{
  if (mCommitRequired)
    {
      mpDataModelGUI->commit();
    }

  QString SEDMLFile;

  if (file == "")
    SEDMLFile =
      CopasiFileDialog::getOpenFileName(this, "Open File Dialog",
                                        QString(), "SED-ML files (*.sedml *.xml);;All Files (*)",
                                        "Choose a file");
  else
    SEDMLFile = file;

  if (!SEDMLFile.isNull())
    {
      assert(CRootContainer::getDatamodelList()->size() > 0);

      if (mpDataModelGUI &&
          (mpDataModel->isChanged() ||
           this->mpSliders->isChanged()))
        {
          switch (CQMessageBox::question(this, "COPASI",
                                         "The document contains unsaved changes\n"
                                         "Do you want to save the changes before exiting?",
                                         QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                         QMessageBox::Save))
            {
              case QMessageBox::Save:
                mpDeferredLoadFile = &CopasiUI3Window::slotImportSEDML;
                mNewFile = SEDMLFile;
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

      // check the SED-ML file, for whether it is complex, if so ask the user to choose what to import:

      bool shoudlReturn;
      SedmlImportOptions options = getSedMLImportOptions(SEDMLFile, shoudlReturn);

      if (shoudlReturn)
        return;

#ifdef COPASI_Provenance
      //Update Main Body Provenance
      //CProvenanceXMLWriter* ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime, mProvenanceParentOfCurrentModel, mpVersionHierarchy->getParentOfCurrentModel());
      CProvenanceXMLWriter *ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime);
      ProvenanceXMLWriter->updateMainBodyProvenace();
#endif
      //#ifdef COPASI_Versioning
      //   mpVersionHierarchy->restoreLastSavedVersioningHierarchy(mLastSavedParentOfCurrentModel);
      //#endif
      mpDataModelGUI->notify(ListViews::ObjectType::MODEL, ListViews::DELETE,
                             mpDataModel->getModel()->getCN());
      mpListView->switchToOtherWidget(ListViews::WidgetType::COPASI, std::string());

      if (this->mpSliders) this->mpSliders->reset();

      setCursor(Qt::WaitCursor);
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotImportSEDMLFinished(bool)));
      mNewFile = SEDMLFile;
      mpDataModelGUI->importSEDML(TO_UTF8(SEDMLFile), &options);
    }
}

SedmlImportOptions CopasiUI3Window::getSedMLImportOptions(const QString & fileName, bool & shouldCancelImport)
{
  auto * doc = readSedMLFromFile(TO_UTF8(fileName));
  auto options = getSedMLImportOptions(doc, shouldCancelImport);
  pdelete(doc);
  return options;
}

SedmlImportOptions CopasiUI3Window::getSedMLImportOptions(SedDocument * pDoc, bool & shouldCancelImport)
{
  shouldCancelImport = false;

  SedmlInfo info(pDoc);
  SedmlImportOptions options;

  if (info.isComplex())
    {
      CQSEDMLImportDialog * dlg = new CQSEDMLImportDialog(this);
      dlg->loadSedML(info);
      int result = dlg->exec();

      if (result == QDialog::Rejected)
        {
          shouldCancelImport = true;
          return options;
        }

      options = dlg->getOptions();
    }

  return options;
}

SedmlImportOptions CopasiUI3Window::getSedMLImportOptionsForArchive(const QString & fileName, bool & shouldCancelImport)
{
  SedmlImportOptions result;

  auto sedml_string = SEDMLUtils::getSedMLStringForArchive(TO_UTF8(fileName));
  auto * doc = readSedMLFromString(sedml_string.c_str());

  result = getSedMLImportOptions(doc, shouldCancelImport);
  pdelete(doc);
  return result;
}

void CopasiUI3Window::refreshRecentSEDMLFileMenu()
{
  mpMenuRecentSEDMLFiles->clear();
  mRecentSEDMLFilesActionMap.clear();

  if (mpRecentSEDMLFilesActionGroup != NULL)
    {
      disconnect(mpRecentSEDMLFilesActionGroup, SIGNAL(triggered(QAction *)), this, SLOT(slotOpenRecentSEDMLFile(QAction *)));
      mpRecentSEDMLFilesActionGroup->deleteLater();
      mpRecentSEDMLFilesActionGroup = NULL;
    }

  mpRecentSEDMLFilesActionGroup = new QActionGroup(this);
  connect(mpRecentSEDMLFilesActionGroup, SIGNAL(triggered(QAction *)), this, SLOT(slotOpenRecentSEDMLFile(QAction *)));
  QAction *pAction;
  CCopasiParameterGroup::index_iterator it =
    CRootContainer::getConfiguration()->getRecentSEDMLFiles().getGroup("Recent Files")->beginIndex();
  CCopasiParameterGroup::index_iterator end =
    CRootContainer::getConfiguration()->getRecentSEDMLFiles().getGroup("Recent Files")->endIndex();
  C_INT Index = 0;

  for (; it != end; ++it, ++Index)
    {
      pAction = new QAction(FROM_UTF8((*it)->getValue< std::string >()), mpRecentSEDMLFilesActionGroup);
      mpMenuRecentSEDMLFiles->addAction(pAction);
      mRecentSEDMLFilesActionMap[pAction] = Index;
    }
}

//TODO
void CopasiUI3Window::exportSEDMLToString(std::string &SEDML)
{
  mpDataModelGUI->commit();

  if (mpDataModelGUI)
    {
      setCursor(Qt::WaitCursor);
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotExportSEDMLToStringFinished(bool)));
      mpDataModelGUI->exportSEDMLToString(SEDML);
    }
}

void CopasiUI3Window::slotExportSEDMLToStringFinished(bool success)
{
  unsetCursor();
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotExportSEDMLToStringFinished(bool)));

  if (!success)
    {
      QString Message = "Error while exporting SED-ML model!\n\n";
      Message += FROM_UTF8(CCopasiMessage::getLastMessage().getText());
      CQMessageBox::critical(this, QString("File Error"), Message,
                             QMessageBox::Ok, QMessageBox::Ok);
      CCopasiMessage::clearDeque();
    }
}

void CopasiUI3Window::slotExportSEDMLFinished(bool /* success */)
{
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotExportSEDMLFinished(bool)));
  unsetCursor();
  checkPendingMessages();
  refreshRecentSEDMLFileMenu();
}

void CopasiUI3Window::slotExportSEDML()
{
  mpDataModelGUI->commit();
  C_INT32 Answer = QMessageBox::No;
  QString tmp;
  bool exportIncomplete = false;
  int sedmlLevel = 1;
  int sedmlVersion = 4;

  while (Answer == QMessageBox::No)
    {
      // if there already is an SBML model, we present the user with the Level
      // and Version of that document as the selected Level and Version to
      // export to.
      if (mpDataModel->getCurrentSEDMLDocument() != NULL)
        {
          sedmlLevel = mpDataModel->getCurrentSEDMLDocument()->getLevel();
          sedmlVersion = mpDataModel->getCurrentSEDMLDocument()->getVersion();
        }

      std::pair<QString, std::pair<unsigned C_INT32, unsigned C_INT32> > nameAndVersion =
        CQSEDMLFileDialog::getSaveFileName(this, "Export SED-ML Dialog", CopasiFileDialog::getDefaultFileName(".sedml"),
                                           "Choose a filename and SED-ML version for SED-ML export.",
                                           sedmlLevel,
                                           sedmlVersion);
      tmp = nameAndVersion.first;
      sedmlLevel = nameAndVersion.second.first;
      sedmlVersion = nameAndVersion.second.second;

      if (tmp.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(this, tmp);

      if (Answer == QMessageBox::Cancel) return;
    }

  if (mpDataModelGUI && !tmp.isNull())
    {
      setCursor(Qt::WaitCursor);
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotExportSEDMLFinished(bool)));
      mpDataModelGUI->exportSEDML(TO_UTF8(tmp), true, sedmlLevel, sedmlVersion, exportIncomplete);
    }
}

void CopasiUI3Window::slotOpenRecentSEDMLFile(QAction *pAction)
{
  int index = mRecentSEDMLFilesActionMap[pAction];
  std::string FileName =
    CRootContainer::getConfiguration()->getRecentSEDMLFiles().getGroup("Recent Files")->getValue< std::string >(index);
  slotImportSEDML(FROM_UTF8(FileName));
}

void CopasiUI3Window::slotImportCombine(QString file)
{
  if (mCommitRequired)
    {
      mpDataModelGUI->commit();
    }

  QString combineArchiveFile;

  if (file == "")
    combineArchiveFile =
      CopasiFileDialog::getOpenFileName(this, "Open File Dialog",
                                        QString(), "Combine Archive Files (*.omex *.sbex *.sedx);;All Files (*)",
                                        "Choose a file");
  else
    combineArchiveFile = file;

  if (!combineArchiveFile.isNull())
    {
      assert(CRootContainer::getDatamodelList()->size() > 0);

      if (mpDataModelGUI &&
          (mpDataModel->isChanged() ||
           this->mpSliders->isChanged()))
        {
          switch (CQMessageBox::question(this, "COPASI",
                                         "The document contains unsaved changes\n"
                                         "Do you want to save the changes before exiting?",
                                         QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                         QMessageBox::Save))
            {
              case QMessageBox::Save:
                mpDeferredLoadFile = &CopasiUI3Window::slotImportCombine;
                mNewFile = combineArchiveFile;
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

      bool shoudlReturn;
      SedmlImportOptions options = getSedMLImportOptionsForArchive(combineArchiveFile, shoudlReturn);

      if (shoudlReturn)
        return;

#ifdef COPASI_Provenance
      // Update Main Body Provenance
      //CProvenanceXMLWriter* ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime, mProvenanceParentOfCurrentModel, mpVersionHierarchy->getParentOfCurrentModel());
      CProvenanceXMLWriter *ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime);
      ProvenanceXMLWriter->updateMainBodyProvenace();
#endif
      //#ifdef COPASI_Versioning
      //   mpVersionHierarchy->restoreLastSavedVersioningHierarchy(mLastSavedParentOfCurrentModel);
      //#endif
      mpDataModelGUI->notify(ListViews::ObjectType::MODEL, ListViews::DELETE,
                             mpDataModel->getModel()->getCN());
      mpListView->switchToOtherWidget(ListViews::WidgetType::COPASI, std::string());

      if (this->mpSliders) this->mpSliders->reset();

      setCursor(Qt::WaitCursor);
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotImportCombineFinished(bool)));
      mNewFile = combineArchiveFile;
      mpDataModelGUI->openCombineArchive(TO_UTF8(combineArchiveFile), &options);
    }
}
void CopasiUI3Window::slotImportCombineFinished(bool success)
{
#ifdef COPASI_Provenance
  //mProvenanceParentOfCurrentModel = QString("");
  mProvenanceOrigionFileType = QString("Imported");
  mProvenanceOrigionTime = QDateTime::currentDateTime().toString();
#endif
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotImportCombineFinished(bool)));
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

  mpDataModelGUI->notify(ListViews::ObjectType::MODEL, ListViews::ADD,
                         mpDataModel->getModel()->getCN());
  mpaSave->setEnabled(true);
  mpaSaveAs->setEnabled(true);
  mpaExportSBML->setEnabled(true);
  mpaExportODE->setEnabled(true);
  mpListView->switchToOtherWidget(ListViews::WidgetType::Model, mpDataModel->getModel()->getCN(), 0);

  refreshRecentSBMLFileMenu();
  updateTitle();
  mSaveAsRequired = true;
  mNewFile.clear();
  performNextAction();
}

void CopasiUI3Window::slotExportShiny(QString str)
{
  mpDataModelGUI->commit();
  C_INT32 Answer = QMessageBox::No;
  QString tmp;

  if (str.isEmpty()) str = CopasiFileDialog::getDefaultFileName(".zip");

#ifdef DEBUG_UI
  qDebug() << "Filename on slotFileSaveAs = " << str;
#endif

  while (Answer == QMessageBox::No)
    {
      tmp =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                          str, "Archive Files (*.zip)",
                                          "Choose a filename to save under");

      if (tmp.isEmpty()) return;

#ifdef DEBUG_UI
      qDebug() << "tmp = " << tmp;
#endif
      // Checks whether the file exists
      Answer = checkSelection(this, tmp);

      if (Answer == QMessageBox::Cancel) return;
    }

  if (mpDataModelGUI && !tmp.isNull())
    {
      setCursor(Qt::WaitCursor);
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotExportCombineFinished(bool)));
      mpDataModelGUI->exportShinyArchive(TO_UTF8(tmp), true);
#ifdef COPASI_Provenance
      //CProvenanceXMLWriter* ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime, mProvenanceParentOfCurrentModel, mpVersionHierarchy->getParentOfCurrentModel(), mpVersionHierarchy->getVersionsPathToCurrentModel());
      CProvenanceXMLWriter *ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime, mpVersionHierarchy->getVersionsPathToCurrentModel());
      ProvenanceXMLWriter->updateCurrentSessionProvenance();
      //mProvenanceParentOfCurrentModel = mpVersionHierarchy->getParentOfCurrentModel();
      ProvenanceXMLWriter->updateOrigionOfProvenance(mProvenanceOfOrigionOfFile);
#endif
    }
}

void CopasiUI3Window::slotExportCombine(QString str)
{
  mpDataModelGUI->commit();
  C_INT32 Answer = QMessageBox::No;
  QString tmp;

  if (str.isEmpty()) str = CopasiFileDialog::getDefaultFileName(".omex");

#ifdef DEBUG_UI
  qDebug() << "Filename on slotFileSaveAs = " << str;
#endif

  while (Answer == QMessageBox::No)
    {
      tmp =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                          str, "Combine Archive Files (*.omex *.sbex *.sedx)",
                                          "Choose a filename to save under");

      if (tmp.isEmpty()) return;

#ifdef DEBUG_UI
      qDebug() << "tmp = " << tmp;
#endif
      // Checks whether the file exists
      Answer = checkSelection(this, tmp);

      if (Answer == QMessageBox::Cancel) return;
    }

  if (mpDataModelGUI && !tmp.isNull())
    {
      setCursor(Qt::WaitCursor);
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotExportCombineFinished(bool)));
      mpDataModelGUI->exportCombineArchive(TO_UTF8(tmp), true);
#ifdef COPASI_Provenance
      //CProvenanceXMLWriter* ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime, mProvenanceParentOfCurrentModel, mpVersionHierarchy->getParentOfCurrentModel(), mpVersionHierarchy->getVersionsPathToCurrentModel());
      CProvenanceXMLWriter *ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime, mpVersionHierarchy->getVersionsPathToCurrentModel());
      ProvenanceXMLWriter->updateCurrentSessionProvenance();
      //mProvenanceParentOfCurrentModel = mpVersionHierarchy->getParentOfCurrentModel();
      ProvenanceXMLWriter->updateOrigionOfProvenance(mProvenanceOfOrigionOfFile);
#endif
    }
}
void CopasiUI3Window::slotExportCombineFinished(bool success)
{
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotExportCombineFinished(bool)));

  if (success)
    {
      assert(mpDataModel != NULL);
      mpDataModel->changed(false);
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

  if (!mNewFile.isEmpty())
    {
      QString FileToLoad = mNewFile;
      mNewFile.clear();

      if (mpDeferredLoadFile != NULL)
        emit signalDefferedLoadFile(FileToLoad);
    }
}

void CopasiUI3Window::slotClearUndoHistory()
{
  CUndoStack * pUndoStack = mpDataModel->getUndoStack();

  if (pUndoStack == NULL || !pUndoStack->canUndo())
    return;

  if (QMessageBox::question(this, "Clear Undo history?",
                            "Do you want to clear the undo history? This will prevent "
                            "all previous operations to be undone.",
                            QMessageBox::Yes,
                            QMessageBox::No | QMessageBox::Default) == QMessageBox::Yes)
    {
      pUndoStack->clear();
    }
}
void CopasiUI3Window::slotUndo()
{
  mpDataModelGUI->notifyChanges(mpDataModel->getUndoStack()->setCurrentIndex(mpDataModel->getUndoStack()->currentIndex() - 1));
}

void CopasiUI3Window::slotRedo()
{
  mpDataModelGUI->notifyChanges(mpDataModel->getUndoStack()->setCurrentIndex(mpDataModel->getUndoStack()->currentIndex() + 1));
}

void CopasiUI3Window::slotUndoHistory()
{
  CQUndoDialog * pDialog = new CQUndoDialog(mpDataModel, this);

  if (pDialog->exec() == QDialog::Accepted)
    {
      mpDataModelGUI->notifyChanges(pDialog->getChangeSet());
    }

  delete pDialog;
}

void CopasiUI3Window::slotFileOpenFromUrl(QString url)
{
  // ensure we have url
  if (url.isNull())
    {

      url = QInputDialog::getText(
              this,
              QString("Enter URL to open"),
              QString("Please specify a URL to open (can be any supported format)"),
              QLineEdit::Normal,
              QString("http://www.ebi.ac.uk/biomodels/model/download/BIOMD0000000001")

            );

      if (url.isNull())
        return;
    }

  QUrl qUrl(url);

  if (qUrl.scheme() == "copasi")
    {
      slotHandleCopasiScheme(qUrl);
      return;
    }

  // create temp filename
  std::string TmpFileName;
  COptions::getValue("Tmp", TmpFileName);
  TmpFileName = CDirEntry::createTmpName(TmpFileName, ".tmp");

  // open url
  connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotFileOpenFromUrlFinished(bool)));
  mpDataModelGUI->downloadFileFromUrl(TO_UTF8(url), TmpFileName);
}

void CopasiUI3Window::activateElement(const std::string& activate)
{
  // resolve display name first
  const CDataObject* obj = mpDataModel->findObjectByDisplayName(activate);

  if (obj != NULL)
    {
      mpListView->switchToOtherWidget(ListViews::WidgetType::NotFound, obj->getCN());
    }
  else
    {
      // see whether it is a task name
      ListViews::WidgetType id = ListViews::WidgetName.toEnum(activate, ListViews::WidgetType::NotFound);

      if (id != ListViews::WidgetType::NotFound)
        {
          mpListView->switchToOtherWidget(id, CCommonName(""));
        }
      else
        {
          // try cn
          obj = dynamic_cast<const CDataObject*>(CRootContainer::getRoot()->getObject(activate));

          if (obj == NULL)
            obj = dynamic_cast<const CDataObject*>(mpDataModel->getObject(activate));

          if (obj == NULL)
            obj = dynamic_cast<const CDataObject*>(mpDataModel->getModel()->getObject(activate));

          if (obj != NULL)
            mpListView->switchToOtherWidget(ListViews::WidgetType::NotFound, obj->getCN());
        }
    }
}

void CopasiUI3Window::removeReportTargets()
{
  if (!mpDataModel->getTaskList())
    return;

  auto& taskList = *mpDataModel->getTaskList();
  std::stringstream str;

  for (auto & task : taskList)
    {
      std::string target = task.getReport().getTarget();

      if (!target.empty())
        {
          str << "  task: " << task.getObjectName() << " target: " << target << std::endl;
          task.getReport().setTarget("");
        }
    }

  std::string removedReports = str.str();

  if (removedReports.empty())
    return;

  CQMessageBox::information(this, "Removed Report targets",
                            QString("The following report targets have been removed\n\n%1")
                            .arg(FROM_UTF8(removedReports)));
}

std::string mapTaskNameToWidgetName(const std::string& name)
{
  ListViews::WidgetType id = ListViews::WidgetName.toEnum(name, ListViews::WidgetType::NotFound);

  if (id != ListViews::WidgetType::NotFound)
    return name;

  if (name == "Time-Course")
    return "Time Course";

  if (name == "Scan")
    return "Parameter Scan";

  if (name == "Time-Course Sensitivities")
    return "Time Course Sensitivities";

  if (name == "Moieties")
    return "Mass Conservation";

  if (name == "Elementary Flux Modes")
    return "Elementary Modes";

  return name;
}

void CopasiUI3Window::performNextAction()
{
  if (mActionStack.empty())
    return;

  auto next = mActionStack.front();
  mActionStack.pop_front();

  switch (next.first)
    {
      case DownloadUrl:
      {
        slotFileOpenFromUrl(FROM_UTF8(next.second));
        return;
      }

      case CreatePlot:
      {
        C_INT32 id = COutputAssistant::findItemByName(next.second, true);

        if (id != -1)
          {
            const auto& description = COutputAssistant::getItem(id);
            size_t taskIndex = mpDataModel->getTaskList()->
                               getIndex(CTaskEnum::TaskName[description.mTaskType]);

            auto* result = COutputAssistant::createDefaultOutput(id, &((*mpDataModel->getTaskList())[taskIndex]), mpDataModel);
            mpDataModelGUI->notify(ListViews::ObjectType::PLOT, ListViews::ADD, result->getCN());
          }

        break;
      }

      case RunTask:
      {
        size_t taskIndex = C_INVALID_INDEX;
        auto& taskList = *mpDataModel->getTaskList();

        if (next.second == "scheduled")
          {
            // find scheduled task to activate
            for (size_t i = 0; i <= taskList.size(); ++i)
              {
                if (taskList[i].isScheduled())
                  {
                    taskIndex = i;
                    break;
                  }
              }
          }
        else if (next.second == "true")
          {
            // run active task
            TaskWidget* pTaskWidget = dynamic_cast<TaskWidget*>(mpListView->getCurrentWidget());

            if (pTaskWidget != NULL && pTaskWidget->getTask())
              {
                taskIndex = taskList.getIndex(pTaskWidget->getTask()->getObjectName());
              }
          }
        else
          {
            // the specified name should be a task name
            taskIndex = taskList.getIndex(next.second);
          }

        if (taskIndex != C_INVALID_INDEX)
          {
            std::string taskName = taskList[taskIndex].getObjectName();
            // select task
            activateElement(mapTaskNameToWidgetName(taskName));

            // wait for activation
            for (int i = 0; i < 5; ++i)
              {
                qApp->processEvents();
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
                QThread::msleep(100);
#endif
              }

            // press run
            TaskWidget* pTaskWidget = dynamic_cast<TaskWidget*>(mpListView->getCurrentWidget());

            if (pTaskWidget != NULL)
              {
                pTaskWidget->runBtnClicked();
              }
          }

        break;
      }

      case SelectElement:
      {
        activateElement(next.second);
        break;
      }

      case RemoveReportTargets:
      {
        removeReportTargets();
        break;
      }

      case CheckForUpdates:
      {
        slotCheckForUpdate();
        break;
      }

      default:
        break;
    }

  if (!mActionStack.empty())
    {
      for (int i = 0; i < 3; ++i)
        {
          qApp->processEvents();
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
          QThread::msleep(100);
#endif
        }

      performNextAction();
    }
}

void CopasiUI3Window::slotHandleCopasiScheme(const QUrl& url)
{
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)

  if (url.scheme() != "copasi")
    return;

  mActionStack.clear();

  // find out what to do

  QUrlQuery query(url);

  std::string downloadUrl = TO_UTF8(query.queryItemValue("downloadUrl", QUrl::FullyDecoded));

  if (!downloadUrl.empty())
    {
      mActionStack.push_back(std::make_pair(DownloadUrl, downloadUrl));
    }

  std::string createPlot = TO_UTF8(query.queryItemValue("createPlot", QUrl::FullyDecoded));

  if (!createPlot.empty())
    {
      mActionStack.push_back(std::make_pair(CreatePlot, createPlot));
    }

  std::string activate = TO_UTF8(query.queryItemValue("activate", QUrl::FullyDecoded));

  if (!activate.empty())
    {
      mActionStack.push_back(std::make_pair(SelectElement, activate));
    }

  std::string runTask = TO_UTF8(query.queryItemValue("runTask", QUrl::FullyDecoded));

  if (!runTask.empty())
    {
      mActionStack.push_back(std::make_pair(RunTask, runTask));
    }

  performNextAction();
#endif
}

void CopasiUI3Window::slotCheckForUpdate()
{
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)

  // if the datamodel is already performing an action (loading / importing)
  // we need to delay checking for updates
  if (mpDataModelGUI->isBusy())
    {
      mActionStack.push_back(std::make_pair(CheckForUpdates, ""));
      return;
    }

  // check whether user has not opted out checking for updates
  std::string TmpFileName;
  COptions::getValue("Tmp", TmpFileName);
  TmpFileName = CDirEntry::createTmpName(TmpFileName, ".json");

  connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotCheckForUpdateFinished(bool)));

  std::string url = TO_UTF8(QString("http://latest.copasi.org?version=%1.%2.%3").arg(CVersion::VERSION.getVersionMajor()).arg(CVersion::VERSION.getVersionMinor()).arg(CVersion::VERSION.getVersionDevel()));
  mpDataModelGUI->downloadFileFromUrl(url, TmpFileName, false);

  // we have several options to figure out what the latest version is
  // implement it ourselves
  //mpDataModelGUI->downloadFileFromUrl("https://update.bioquant.uni-heidelberg.de|virginia|ucon/", TmpFileName, false);
  //
  // use is.gd -> we get basic access information of the link + country the request came from
  // mpDataModelGUI->downloadFileFromUrl("https://is.gd/latest_copasi", TmpFileName, false);
  //
  // use bit.do -> does not count links at all :(
  //mpDataModelGUI->downloadFileFromUrl("http://bit.do/latest_copasi", TmpFileName, false);
  //
  // use tiny.cc -> unfortunately we only get a counter of whether the link was accessed
  //mpDataModelGUI->downloadFileFromUrl("https://tiny.cc/latest_copasi", TmpFileName, false);
  //
  // use bit.ly -> unfortunately url tracking from applications seems to be a paid feature
  //mpDataModelGUI->downloadFileFromUrl("http://bit.ly/latest_copasi", TmpFileName, false);
  //
  // use directly the github api -> we won't have any information about whether the update feature is used
  //mpDataModelGUI->downloadFileFromUrl("https://api.github.com/repos/copasi/COPASI/releases/latest", TmpFileName, false);
#endif
}

bool getVersionFromFile(const std::string& fileName, CVersion & latest)
{

  latest = CVersion::VERSION;

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  QFile file(fileName.c_str());

  if (!file.open(QIODevice::ReadOnly))
    return false;

  QByteArray data = file.readAll();
  file.close();
  file.remove();
  QJsonDocument doc = QJsonDocument::fromJson(data);

  if (doc.isEmpty())
    return false;

  if (!doc.isObject())
    return false;

  std:: string Version = TO_UTF8(doc.object().value(QString::fromUtf8("name")).toString());

  if (Version.empty()) return false;

  latest.setVersion(Version.substr(7));
#endif
  return true;
}

void CopasiUI3Window::slotCheckForUpdateFinished(bool success)
{
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotCheckForUpdateFinished(bool)));

  CVersion Latest;

  if (success)
    {
      success &= getVersionFromFile(mpDataModelGUI->getLastDownloadDestination(), Latest);
    }

  if (success)
    {
      CRootContainer::getConfiguration()->getCheckForUpdates().setChecked();

      if (mAutoUpdateCheck &&
          CRootContainer::getConfiguration()->getCheckForUpdates().skipVersion(Latest))
        {
          mAutoUpdateCheck = false;
          CRootContainer::getConfiguration()->save();

          return;
        }

      std::string latestVersion = Latest.getVersion();
      std::string currentVersion = CVersion::VERSION.getVersion();

      if (Latest > CVersion::VERSION)
        {
          CQMessageBox Question(QMessageBox::Question,
                                FROM_UTF8(std::string("Software Update")),
                                FROM_UTF8(std::string("The following software is available for download:\n  COPASI %1\n\nDo you want to download it?")).arg(FROM_UTF8(latestVersion)),
                                QMessageBox::NoButton,
                                this
                               );

          QPushButton *pIgnore = NULL;

          if (mAutoUpdateCheck)
            {
              pIgnore = Question.addButton(QMessageBox::Ignore);
              pIgnore->setText(FROM_UTF8(std::string("Skip Version")));
            }

          QPushButton *pAccept = Question.addButton(QMessageBox::Ok);
          QPushButton *pReject = Question.addButton(QMessageBox::Cancel);

          Question.setDefaultButton(pAccept);

          Question.exec();
          QAbstractButton * pClicked = Question.clickedButton();

          if (pClicked == pAccept)
            {
              QDesktopServices::openUrl(QUrl("http://copasi.org/Download/"));
            }
          else if (pClicked == pIgnore && pIgnore != NULL)
            {
              CRootContainer::getConfiguration()->getCheckForUpdates().setSkipVersion(Latest);
            }
        }
      else if (!mAutoUpdateCheck)
        {
          if (Latest == CVersion::VERSION)
            {
              CQMessageBox::information(this, FROM_UTF8(std::string("Software Update")),
                                        QString("You are running the latest version:\n  COPASI %1.").arg(FROM_UTF8(currentVersion)));
            }
          else
            {
              CQMessageBox::information(this, FROM_UTF8(std::string("Software Update")),
                                        QString("You are running a pre-release version:\n  COPASI %1.").arg(FROM_UTF8(currentVersion)));
            }
        }

      mAutoUpdateCheck = false;
      CRootContainer::getConfiguration()->save();
    }
  else if (mpDataModelGUI->getLastDownloadUrl() != "https://api.github.com/repos/copasi/COPASI/releases/latest")
    {
      connect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotCheckForUpdateFinished(bool)));
      mpDataModelGUI->downloadFileFromUrl("https://api.github.com/repos/copasi/COPASI/releases/latest", mpDataModelGUI->getLastDownloadDestination(), false);
    }
  else
    {
      mAutoUpdateCheck = false;
    }
}

void CopasiUI3Window::slotClearSbmlIds()
{
  if (!mpDataModel || !mpDataModel->getModel()) return;

  mpDataModel->getModel()->clearSbmlIds();
}

void CopasiUI3Window::slotFileOpenFromUrlFinished(bool success)
{
  disconnect(mpDataModelGUI, SIGNAL(finished(bool)), this, SLOT(slotFileOpenFromUrlFinished(bool)));

  if (success)
    {
      QString tempFileName = FROM_UTF8(mpDataModelGUI->getLastDownloadDestination());

      mActionStack.push_front(std::make_pair(RemoveReportTargets, ""));

      if (isArchive(tempFileName))
        {
          mpDataModelGUI->setIgnoreNextFile(true);
          slotImportCombine(tempFileName);
        }
      else if (isProbablySEDML(tempFileName))
        {
          mpDataModelGUI->setIgnoreNextFile(true);
          slotImportSBML(tempFileName);
        }
      else if (isProbablySBML(tempFileName))
        {
          mpDataModelGUI->setIgnoreNextFile(true);
          slotImportSBML(tempFileName);
        }
      else
        {
          mpDataModelGUI->setIgnoreNextFile(true);
          slotFileOpen(tempFileName);
        }

      mSaveAsRequired = true;
    }
  else
    {
      std::stringstream str;
      str << "COPASI failed to download the file from " << std::endl
          << std::endl
          << mpDataModelGUI->getLastDownloadUrl() << std::endl
          << std::endl
          << CCopasiMessage::getAllMessageText();

      CQMessageBox::critical(this, "Download Failed",
                             str.str().c_str(),
                             QMessageBox::Ok | QMessageBox::Default,
                             QMessageBox::NoButton);
    }
}

#ifdef COPASI_Versioning
void CopasiUI3Window::slotCreateVersion() //Slot Version Create
{
  // save a new version
  if (mpDataModel->getModel() != NULL)
    {
      slotFileSave();

      CCreateModelVersionDialog *CreateVersionDialog = new CCreateModelVersionDialog(this);
      CreateVersionDialog->setWindowTitle("Create Version Information");
      CreateVersionDialog->exec();

      //if(mpVersionHierarchy->getPathFile() == QString(""))
      //{
      //    mpVersionHierarchy->setPathFile(FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()));
      //}
      if (CreateVersionDialog->isDataCaptured())
        {
          CModelVersionHierarchy * pVersionHierarchy = mpDataModel->getModelVersionHierarchy();
          int i = pVersionHierarchy->addVersion(TO_UTF8(CreateVersionDialog->getVersion()),
                                                TO_UTF8(CreateVersionDialog->getGivenName()),
                                                TO_UTF8(CreateVersionDialog->getFamilyName()),
                                                TO_UTF8(CreateVersionDialog->getOrganization()),
                                                TO_UTF8(CreateVersionDialog->getEmail()),
                                                TO_UTF8(CreateVersionDialog->getComments()));

          if (i == 1)
            {
              CQMessageBox::critical(this, QString("Error"), "Version name must be unique",
                                     QMessageBox::Ok, QMessageBox::Ok);
            }
          else if (i == 2)
            {
              CQMessageBox::critical(this, QString("Error"), "Version name is obligatory",
                                     QMessageBox::Ok, QMessageBox::Ok);
            }
          // if create is successful add the current model to the combined archive
          else
            {
              // Save a new version to Versioning folder
              if (i == 3) // warning about updating Versioning XML file
                {
                  CQMessageBox::information(this, QString("Warning"), "Problem while updating version hierarchy XML file",
                                            QMessageBox::Ok, QMessageBox::Ok);
                }

              QString dataFile;
              bool PathForVersioningExists = false;
              PathForVersioningExists = true;
              // Make directory for Versioning
              QString path =  FROM_UTF8(pVersionHierarchy->getDiretory()) + "/" + CreateVersionDialog->getVersion();
              QDir dir(path);

              if (!dir.exists())
                {
                  dir.mkpath(path);
                  // Set the path for the Versioning XML
                  dataFile = FROM_UTF8(pVersionHierarchy->getDiretory()) + "/" + CreateVersionDialog->getVersion() + "/" + CreateVersionDialog->getVersion();
                }

              if (PathForVersioningExists)
                {
                  mpDataModelGUI->saveModel(dataFile.toStdString(), true);
#ifdef COPASI_Provenance
                  //   Update Provenace and store it - Clear Undo Stack
                  //mProvenanceParentOfCurrentModel = mpVersionHierarchy->getParentOfCurrentModel();
                  //CProvenanceXMLWriter* ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime, mProvenanceParentOfCurrentModel, mpVersionHierarchy->getParentOfCurrentModel(), mpVersionHierarchy->getVersionsPathToCurrentModel());
                  CProvenanceXMLWriter *ProvenanceXMLWriter = new CProvenanceXMLWriter(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceOrigionFileType, mProvenanceOrigionTime, pVersionHierarchy->getVersionsPathToCurrentModel());
                  ProvenanceXMLWriter->updateVersionProvenanceXMLFile(CreateVersionDialog->getVersion());
                  mpUndoStack->clear();
#endif
                }
            }
        }
      else
        {
          CQMessageBox::critical(this, QString("Error"), "Path and Directory for creating Version does not exist. Please save the file before creating versions",
                                 QMessageBox::Ok, QMessageBox::Ok);
        }

      QDir destination;
      QString dataFile = FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()) + "/ProvenanceMainBody.xml";
      destination.remove(dataFile);
      CreateVersionDialog->~CCreateModelVersionDialog();
    }
  else
    {
      CQMessageBox::critical(this, QString("Error"), "No current model exists",
                             QMessageBox::Ok, QMessageBox::Ok);
    }
}
void CopasiUI3Window::slotBrowseVersion() // Slot Version Browse
{
  CBrowseModelVersionDialog *ModelVersionDialog = new  CBrowseModelVersionDialog(this, mpDataModelGUI, mpDataModel
#ifdef COPASI_Provenance
      //      , FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mProvenanceParentOfCurrentModel
      , FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory())
#endif
                                                                                );
  ModelVersionDialog->setWindowTitle("Model Versions");
  ModelVersionDialog->exec();
  // The end of session maintance will be done by COMBINE Archive
  //#ifdef COPASI_Provenance
  //mProvenanceParentOfCurrentModel = ModelVersionDialog->getProvenanceParentOfCurrentModel();
  //#endif
  //mLastSavedParentOfCurrentModel = ModelVersionDialog->getLastSavedParentOfCurrentModel();
  ModelVersionDialog->~CBrowseModelVersionDialog();
}
#endif

#ifdef COPASI_Provenance
void CopasiUI3Window::slotProvenance()
{
  //CProvenanceDialog* ProvenanceDialog = new CProvenanceDialog(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mpVersionHierarchy->getVersionsPathToCurrentModel(), mProvenanceParentOfCurrentModel, mpVersionHierarchy->getParentOfCurrentModel());
  CProvenanceDialog *ProvenanceDialog = new CProvenanceDialog(this, mpUndoStack, FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory()), mpVersionHierarchy->getVersionsPathToCurrentModel());
  ProvenanceDialog->setWindowTitle("Provenance");
  ProvenanceDialog->exec();
}

//QString CopasiUI3Window::getProvenanceParentOfCurrentVersion()
//{
//  return (mProvenanceParentOfCurrentModel);
//}

#endif
