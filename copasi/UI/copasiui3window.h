// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/copasiui3window.h,v $
//   $Revision: 1.95.2.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/01/28 21:31:26 $
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

#include <string>

#include <QMainWindow>
#include <QModelIndex>
#include <QMap>

#ifdef COPASI_SBW_INTEGRATION
#include <QApplication>
#include <QEvent>
#include <QMutex>
#include <QWaitCondition>

#define WIN32_LEAN_AND_MEAN
#include <SBW/SBW.h>
#undef DELETE
#undef ERROR
#undef TRUE
#undef FALSE
using namespace SystemsBiologyWorkbench;
#else
class SBWListener;
#endif  // COPASI_SBW_INTEGRATION

#include "../MIRIAM/CMIRIAMResource.h"

//class QToolButton;
class Q3ListViewItem;
class ListViews;
class DataModelGUI;
class SliderDialog;
class QAction;
class ObjectBrowserDialog;
class QComboBox;
class CMIRIAMResources;
class CMIRIAMResourceObject;
class QEvent;
class QActionGroup;
class QThread;

class CopasiUI3Window : public QMainWindow
#ifdef COPASI_SBW_INTEGRATION
    // A SBW listener can catch messages from SBW ... used here to allow COPASI to be shut down
    , public SBWListener
#endif // COPASI_SBW_INTEGRATION

{
  Q_OBJECT

public:
  static CopasiUI3Window * create();
  ~CopasiUI3Window();

  DataModelGUI* getDataModel();

  ListViews* getMainWidget();

  void checkPendingMessages();
  void suspendAutoSave(const bool & suspend);

  /**
   * This is used to import an SBML file from a std::string in the GUI
   * it does all the necessary GUI stuff like asking to save the old
   * document, displaying messages, etc.
   */
  void importSBMLFromString(const std::string & sbmlDocumentText);

  void exportSBMLToString(std::string & SBML);

  QThread * getMainThread() const;

signals:
  void signalLoadFile(QString newFile);

protected:
  virtual void closeEvent(QCloseEvent* e);

  /*
   * This is used for doing drag-and-drop action (16.04.10)
   */
  void dragEnterEvent(QDragEnterEvent *event);
  void dropEvent(QDropEvent *event);

public slots:
  void slotShowSliders(bool flag);

  /**
   * This should only be called by the destructor of the object browser dialog
   * otherwise a memory leak occurs
   */
  void slotObjectBrowserDialogWasClosed();

  void autoSave();

protected slots:
  void slotProcessCommandline();
  void slotFileOpen(QString file = QString::null);
  void slotFileOpenFinished(bool success);
  void slotFileExamplesCopasiFiles(QString file = QString::null);
  void slotFileExamplesSBMLFiles(QString file = QString::null);
  void slotFileSave();
  void slotFileSaveAs(QString str = QString::null);
  void slotFileSaveFinished(bool success);
  void newDoc();
  void slotFilePrint();
  void slotImportSBML(QString file = QString::null);
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
  void slotCloseEventFinished(bool success);
  void slotPreferences();
  void slotConvertToIrreversible();
  void listViewsFolderChanged(const QModelIndex & index);
  void slotOpenRecentFile(QAction * pAction);
  void slotOpenRecentSBMLFile(QAction * pAction);
  bool slotRegistration();
  void slotCheckModel();
  void slotApplyInitialState();
  void slotUpdateInitialState();
  void slotFrameworkChanged(int index);
  void slotCapture();
  void slotUpdateMIRIAM();
  void slotExpandModel();
  void slotFontSelection();

#ifdef WITH_MERGEMODEL
  void slotAddFileOpen(QString file = QString::null);
  void slotAddModel();
  void slotMergeModels();
#endif

  // SBW: handle the custom events
  void customEvent(QEvent *);

  /**
   * This should only be called via signal by the corresponding QAction mpaObjectBrowser.
   * Otherwise the QAction will not be up to date.
   */
  void slotShowObjectBrowserDialog(bool flag);

private:
  CopasiUI3Window();

  void createActions();
  void createToolBar();
  void createMenuBar();

  void CleanUp();

  void updateTitle();

  void setApplicationFont();

  DataModelGUI* mpDataModelGUI; // to keep track of the data model..
  ListViews *mpListView;
  QComboBox * mpBoxSelectFramework;

  int newFlag;
  QString FixedTitle;

  QAction* mpaNew;
  QAction* mpaOpen;
  QAction* mpaOpenCopasiFiles;
  QAction* mpaOpenSBMLFiles;
  QAction* mpaSave;
  QAction* mpaSaveAs;
  QAction* mpaImportSBML;
  QAction* mpaExportSBML;
  QAction* mpaExportODE;
  QAction* mpaQuit;
  QAction* mpaObjectBrowser;
  QAction* mpaSliders;
  QAction* mpaCheckModel;
  QAction* mpaApplyInitialState;
  QAction* mpaUpdateInitialState;
  QAction* mpaCapture;
  QAction* mpaUpdateMIRIAM;
  QAction* mpaExpandModel;
  QAction* mpaFontSelectionDialog;

#ifdef WITH_MERGEMODEL
  QAction* mpaAddModel;
  QAction* mpaMergeModels;
#endif
  SliderDialog* mpSliders;
  ObjectBrowserDialog * mpObjectBrowser;

  bool mSaveAsRequired;
  QTimer *mpAutoSaveTimer;
  bool mSuspendAutoSave;

  //menus
  QMenu * mpMenuExamples;
  QMenu * mpMenuRecentFiles;
  QMap< QAction *, int > mRecentFilesActionMap;
  QActionGroup * mpRecentFilesActionGroup;
  void refreshRecentFileMenu();

  QMenu * mpMenuRecentSBMLFiles;
  QMap< QAction *, int > mRecentSBMLFilesActionMap;
  QActionGroup * mpRecentSBMLFilesActionGroup;
  void refreshRecentSBMLFileMenu();

  QMenu * mpTools;

  CMIRIAMResources * mpMIRIAMResources;

  QThread * mpMainThread;
  QString mNewFile;
  QCloseEvent * mpCloseEvent;
  bool mQuitApplication;

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

  // and another to return the SBML file COAPSI is currently working with
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

#ifdef COPASI_LICENSE_COM
  bool checkRegistration();
#endif // COPASI_LICENSE_COM
};
