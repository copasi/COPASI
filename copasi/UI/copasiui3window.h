// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

#ifndef COPASI_UI3_WINDOW_H
#define COPASI_UI3_WINDOW_H

#include <string>

#include <QMainWindow>
#include <QtCore/QModelIndex>
#include <QtCore/QMap>
#include <QtCore/QPointer>
#include <QUrl>

#include <copasi/config.h>
#include <copasi/sedml/SedmlImportOptions.h>
#include <sedml/common/libsedml-namespace.h>
LIBSEDML_CPP_NAMESPACE_BEGIN
class SedDocument;
LIBSEDML_CPP_NAMESPACE_END

#ifdef COPASI_SBW_INTEGRATION
# include <QApplication>
# include <QtCore/QEvent>
# include <QtCore/QMutex>
# include <QtCore/QWaitCondition>

# ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
# endif // WIN32_LEAN_AND_MEAN
# include <SBW/SBW.h>
# undef DELETE
# undef ERROR
# undef TRUE
# undef FALSE
using namespace SystemsBiologyWorkbench;
#else
class SBWListener;
#endif  // COPASI_SBW_INTEGRATION

//class QToolButton;
class ListViews;
class DataModelGUI;
class SliderDialog;
class CQDependencyDialog;
class QAction;
class ObjectBrowserDialog;
class QComboBox;
class CMIRIAMResources;
class CMIRIAMResourceObject;
class QEvent;
class QActionGroup;
class QThread;
#ifdef COPASI_Versioning
class CModelVersionHierarchy;
#endif

class CQOptPopulation;
class CDataModel;
class CUndoStack;

enum CopasiUIActions
{
  DownloadUrl,
  SelectElement,
  RunTask,
  CreatePlot,
  RemoveReportTargets,
  CheckForUpdates,
  Invalid
};

class CopasiUI3Window : public QMainWindow
#ifdef COPASI_SBW_INTEGRATION
// A SBW listener can catch messages from SBW ... used here to allow COPASI to be shut down
  , public SBWListener
#endif // COPASI_SBW_INTEGRATION

{
  Q_OBJECT

public:
  typedef void (CopasiUI3Window::*DeferredLoadFile)(QString);

  static CopasiUI3Window * create();

  static CopasiUI3Window * getMainWindow();

  static bool isMainThread();

  ~CopasiUI3Window();

  DataModelGUI* getDataModel();

  ListViews* getMainWidget();

  void checkPendingMessages();
  void suspendAutoSave(const bool & suspend);

  /**
   * The slider dialog has to be disabled before
   * a task is run and reenabled afterwards.
   * Actually the methods stores the state
   * when the value true is passed and restores that
   * state when the value false is passed.
   */
  void disableSliders(bool disable);

  /**
   * This is used to import an SBML file from a std::string in the GUI
   * it does all the necessary GUI stuff like asking to save the old
   * document, displaying messages, etc.
   */
  void importSBMLFromString(const std::string & sbmlDocumentText);

  void exportSBMLToString(std::string & SBML);

  // SEDML

  void exportSEDMLToString(std::string & SEDML);

// COMBINE Archive will take care of file management
  /*
  #ifdef COPASI_Provenance
    QString getProvenanceParentOfCurrentVersion();
  #endif
  */

  CQOptPopulation* getPopulationDisplay();
  void setPopulationDisplay(CQOptPopulation* display);

  void addWindow(QMainWindow * pWindow);
  void removeWindow(QMainWindow * pWindow);

  void setMessageShown(const bool & shown);

  const bool & messageShown() const;

  /**
   * Returns the list of current windows
   */
  const QMap< QPointer<QMainWindow>, QPointer<QAction> > & getWindows() const;

signals:
  void signalDefferedLoadFile(QString newFile);
  void signalQuit();
  void signalPreferenceUpdated();

protected:
  virtual void closeEvent(QCloseEvent* e);

  /*
   * This is used for doing drag-and-drop action (16.04.10)
   */
  void dragEnterEvent(QDragEnterEvent *event);
  void dropEvent(QDropEvent *event);

public slots:
  void slotDefferedLoadFile(QString str);
  void slotShowSliders(bool flag);
  void slotShowDependencies(bool flag);
  void slotUpdateHideMainToolbarAction();
  void slotHideMainToolbar(bool flag);
  void slotCopy();
  void slotCheckForUpdate();
  void slotCheckForUpdateFinished(bool flag);
  void slotAutoCheckForUpdates();
  void slotClearSbmlIds();

  /**
   * This should only be called by the destructor of the object browser dialog
   * otherwise a memory leak occurs
   */
  void slotObjectBrowserDialogWasClosed();

  void autoSave();

  void openInitialDocument(const QString & file);

  void slotFileOpen(QString file = QString());
  void slotFileOpenFromUrl(QString url = QString());

  void slotHandleCopasiScheme(const QUrl& url);

public:
  /**
   * performs the next action from the action stack
   */
  void performNextAction();
  /**
   * activates the specified element, which can be a model element specified
   * by display name, cn, or one of the widgetname enumerations of the listviews
   * class
   *
   * @param elementToActivate the element to activate
   */
  void activateElement(const std::string& elementToActivate);

  /**
   * goes through the list of tasks, and removes all report targets specified
   * while informing which ones were removed.
   */
  void removeReportTargets();

protected slots:
  void slotFileOpenFinished(bool success);
  void slotFileOpenFromUrlFinished(bool success);
  void slotFileExamplesCopasiFiles(QString file = QString());
  void slotFileExamplesSBMLFiles(QString file = QString());
  void slotFileSave();
  void slotFileSaveAs(QString str = QString());
  void slotFileSaveFinished(bool success);
  void slotFunctionDBSave(QString str = QString());
  void slotFunctionDBLoad(QString str = QString());
  void slotParameterSetsSave(QString str = QString());
  void slotParameterSetsLoad(QString str = QString());
  void slotNewDoc(QString str = QString());
  void slotFilePrint();
  void slotImportSBML(QString file = QString());
  void slotImportSBMLFinished(bool success);
  void slotImportSBMLFromStringFinished(bool success);
  void slotExportSBML();
  void slotExportSBMLFinished(bool success);
  void slotExportSBMLToStringFinished(bool success);
  void slotExportMathModel();
  void slotExportMathModelFinished(bool success);
  void slotTutorialWizard();
  void about();
  void license();
  void aboutQt();
  void slotQuit();
  void slotQuitFinished(bool success);
  void slotPreferences();
  void slotPreferencesAccepted();
  void slotConvertToIrreversible();
  void slotCreateEventsForTimeseries();

  void listViewsFolderChanged(const QModelIndex & index);
  void slotOpenRecentFile(QAction * pAction);
  void slotOpenRecentSBMLFile(QAction * pAction);
  void slotCheckModel();
  void slotApplyInitialState();
  void slotUpdateInitialState();
  void slotFrameworkChanged(int index);
  void slotCapture();
  void slotUpdateMIRIAM();
  void slotUpdateMIRIAMFinished(bool);
  void slotExpandModel();
  void slotFontSelection();

  void slotCloseAllWindows();
  void slotActivateWindowTriggered(QAction* action);

  void slotAddFileOpen(QString file = QString());
  void slotAddFileOpenFinished(bool success);
  void slotMergeModels();

  // SBW: handle the custom events
  void customEvent(QEvent *);

  /**
   * This should only be called via signal by the corresponding QAction mpaObjectBrowser.
   * Otherwise the QAction will not be up to date.
   */
  void slotShowObjectBrowserDialog(bool flag);

  // SEDML
  void slotFileExamplesSEDMLFiles(QString file = QString());
  void slotImportSEDML(QString file = QString());

  void slotImportSEDMLFinished(bool success);
  void slotImportSEDMLFromStringFinished(bool success);
  void slotExportSEDML();
  void slotExportSEDMLFinished(bool success);
  void slotExportSEDMLToStringFinished(bool success);
  void slotOpenRecentSEDMLFile(QAction * pAction);

  void slotImportCombine(QString file = QString());
  void slotImportCombineFinished(bool success);
  void slotExportCombine(QString str = QString());
  void slotExportCombineFinished(bool success);
  void slotExportShiny(QString str = QString());

  void slotUndo();
  void slotRedo();
  void slotUndoHistory();
  void slotClearUndoHistory();

#ifdef COPASI_Versioning
  void slotBrowseVersion();
  void slotCreateVersion();
#endif

#ifdef COPASI_Provenance
  void slotProvenance();
#endif

  void slotLoadParameterEstimationProtocol();

  void slotShowDebugInfo();

private:
  CopasiUI3Window();

  void createActions();
  QToolBar * createToolBar();
  void createMenuBar();

  void CleanUp();

  void updateTitle();

  void setApplicationFont();

  /**
   * retrieves the import options for SED-ML import
   *
   * @param fileName SED-ML file to check
   * @param shouldCancelImport output parameter indicating whether the
   *                      import should be aborted
   *
   * @return the import options
   */
  SedmlImportOptions getSedMLImportOptions(const QString& fileName, bool & shouldCancelImport);

  /**
   * retrieves the import options for SED-ML import
   *
   * @param pDoc SED-ML document to check
   * @param shouldCancelImport output parameter indicating whether the
   *                      import should be aborted
   *
   * @return the import options
   */
  SedmlImportOptions getSedMLImportOptions(SedDocument* pDoc, bool & shouldCancelImport);

  /**
   * retrieves the import options for SED-ML import for combine archives.
   *
   * @param fileName combine archive file to check
   * @param shouldCancelImport output parameter indicating whether the
   *                      import should be aborted
   *
   * @return the import options
   */
  SedmlImportOptions getSedMLImportOptionsForArchive(const QString & fileName, bool & shouldCancelImport);


  DataModelGUI* mpDataModelGUI; // to keep track of the data model..
  CDataModel* mpDataModel;

  ListViews *mpListView;
  QComboBox * mpBoxSelectFramework;
  QToolBar *mpMainToolbar;

  QString FixedTitle;

  DeferredLoadFile mpDeferredLoadFile;

  QAction* mpaNew;
  QAction* mpaOpen;
  QAction* mpaOpenCopasiFiles;
  QAction* mpaOpenSBMLFiles;
  QAction* mpaOpenFromUrl;
  QAction* mpaSave;
  QAction* mpaSaveAs;
  QAction* mpaFunctionDBSave;
  QAction* mpaFunctionDBLoad;
  QAction* mpaParameterSetsSave;
  QAction* mpaParameterSetsLoad;
  QAction* mpaImportSBML;
  QAction* mpaExportSBML;
  QAction* mpaExportODE;
  QAction* mpaQuit;
  QAction* mpaObjectBrowser;
  QAction* mpaSliders;
  QAction* mpaDependencies;
  QAction* mpaCheckModel;
  QAction* mpaHideMainToolbar;
  QAction* mpaApplyInitialState;
  QAction* mpaUpdateInitialState;
  QAction* mpaCapture;
  QAction* mpaUpdateMIRIAM;
  QAction* mpaExpandModel;
  QAction* mpaFontSelectionDialog;
  QAction* mpaParameterEstimationResult;

  QAction* mpaCopy;
  QAction* mpaCloseAllWindows;
  QAction* mpaShowDebugInfo;

  QAction* mpaImportCombine;
  QAction* mpaExportCombine;
  QAction* mpaExportShiny;

  QAction* mpaAddModel;
  QAction* mpaMergeModels;

  SliderDialog* mpSliders;
  CQDependencyDialog* mpDependencies;
  ObjectBrowserDialog * mpObjectBrowser;

  bool mSaveAsRequired;
  QTimer *mpAutoSaveTimer;
  bool mSuspendAutoSave;

  //menus
  QMenu * mpMenuExamples;
  QMenu * mpMenuRecentFiles;
  QMenu * mpWindowsMenu;
  QMap< QAction *, int > mRecentFilesActionMap;
  QActionGroup * mpRecentFilesActionGroup;
  void refreshRecentFileMenu();
  void refreshWindowsMenu();

  QMenu * mpMenuRecentSBMLFiles;
  QMap< QAction *, int > mRecentSBMLFilesActionMap;
  QActionGroup * mpRecentSBMLFilesActionGroup;
  QActionGroup * mpWindowsActionGroup;
  void refreshRecentSBMLFileMenu();

  QMenu * mpTools;

  CMIRIAMResources * mpMIRIAMResources;

  QThread * mpMainThread;
  QString mNewFile;
  bool mCommitRequired;
  bool mQuitApplication;
  bool mSliderDialogEnabled;
  bool mMessageShown;

  QMap< QPointer<QMainWindow>, QPointer<QAction> > mWindows;

  static CopasiUI3Window * pMainWindow;

  // SEDML
  QMenu * mpMenuSEDMLSupport;
  QAction* mpaImportSEDML;
  QAction* mpaExportSEDML;
  QAction* mpaOpenSEDMLFiles;
  QMenu * mpMenuRecentSEDMLFiles;
  QMap< QAction *, int > mRecentSEDMLFilesActionMap;
  QActionGroup * mpRecentSEDMLFilesActionGroup;
  void refreshRecentSEDMLFileMenu();

  // UNDO Framework
  QAction* mpaUndo;
  QAction* mpaRedo;
  QAction* mpaUndoHistory;
  QAction* mpaClearUndoHistory;

#ifdef COPASI_Versioning
  QAction* mpaCreateVersion;
  QAction* mpaBrowseVersion;
//  COMBINE Archive will take care of file management
//  QString mLastSavedParentOfCurrentModel;
#endif

#ifdef COPASI_Provenance
  QAction* mpaProvenance;
//  COMBINE Archive will take care of file management
  //QString mProvenanceParentOfCurrentModel;
  QString mProvenanceOrigionFileType;
  QString mProvenanceOrigionTime;
  QString mProvenanceOfOrigionOfFile;
#endif

  CQOptPopulation* mpPopulationDisplay;

  bool mAutoUpdateCheck;

  std::deque< std::pair < CopasiUIActions, std::string > > mActionStack;

#ifdef COPASI_SBW_INTEGRATION
public:
  /**
   * This event is triggered by SBW asking COPASI to import an SBML document provided as a string
   */
  class QSBWSBMLEvent : public QEvent
  {
  public:
    /**
     * Constructor
     * @param const std::string & SBMLModel
     */
    QSBWSBMLEvent(const std::string & SBMLModel);

    /**
     * Retrieve the SBML model
     * @return const std::string & SBMLModel
     */
    const std::string & getSBMLModel() const;

  private:
    /**
     * A string holding the SBML model
     */
    std::string mSBML;
  };

  /**
   * This event is triggered by SBW asking COPASI shut down.
   */
  class QSBWShutdownEvent: public QEvent
  {
  public:
    QSBWShutdownEvent();
  };

  // We expose 2 methods to SBW, one to load an SBML file
  SystemsBiologyWorkbench::DataBlockWriter sbwAnalysis(SystemsBiologyWorkbench::Module from,
      SystemsBiologyWorkbench::DataBlockReader reader);

  // and another to return the SBML file COPASI is currently working with
  SystemsBiologyWorkbench::DataBlockWriter sbwGetSBML(SystemsBiologyWorkbench::Module from,
      SystemsBiologyWorkbench::DataBlockReader reader);

  // This method must not be renamed as SBW calls it by name
  void registerMethods(SystemsBiologyWorkbench::MethodTable<CopasiUI3Window> & table);

  // as part of the SBWListener we tell SBW here, that we want to react on the shutdown event
  virtual void onShutdown();

private:
  /**
   * Connect to SBW
   */
  void sbwConnect();

  /**
   * Disconnect to SBW
   */
  void sbwDisconnect();

  /**
   * Register COPASI as a module ins SBW
   */
  void sbwRegister();

  /**
   * Unregister a module in SBW
   * @param const std::string & moduleName
   */
  void sbwUnregister(const std::string & moduleName) const;

  /**
   * Refresh the SBW menu.
   */
  void sbwRefreshMenu();

  /**
   * Retrieve the list of all services from the SBW broker
   * @param const std::string & category
   * @param const bool & recursive
   * @return std::vector< SystemsBiologyWorkbench::DataBlockReader > services
   */
  std::vector< SystemsBiologyWorkbench::DataBlockReader > sbwFindServices(const std::string & category,
      const bool & recursive);

protected slots:
  void sbwSlotMenuTriggered(QAction * pAction);
  void sbwSlotMenuTriggeredFinished(bool success);
  void sbwSlotGetSBMLFinished(bool success);

private:
  /**
   * The SBW module which handles the interaction with the SBW broker
   */
  SystemsBiologyWorkbench::ModuleImpl * mpSBWModule;

  /**
   * A list of SBW analyzer modules
   */
  QStringList mSBWAnalyzerModules;

  /**
   * A list of the corresponding SBW services
   */
  QStringList mSBWAnalyzerServices;

  /**
   * Map between actions and the index of SBW modules and services
   */
  QMap< QAction *, int > mSBWActionMap;

  /**
   * A group containing all actions of the SBW menu
   */
  QActionGroup * mpSBWActionGroup;

  /**
   * The SBW menu
   */
  QMenu * mpSBWMenu;

  /**
   * The SBW Action
   */
  QAction * mpSBWAction;

  /**
   * This variable indicates whether COPASI is to ignore SBW shutdown events
   */
  bool mSBWIgnoreShutdownEvent;

  QMutex mSBWMutex;

  QWaitCondition mSBWWaitSlot;

  bool mSBWCallFinished;

  bool mSBWSuccess;

  std::string mSBWDocumentString;

  QStringList::size_type mSBWActionId;

#endif // COPASI_SBW_INTEGRATION
};

#endif //COPASI_UI3_WINDOW_H
