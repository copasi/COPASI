// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/copasiui3window.h,v $
//   $Revision: 1.82 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/05/07 10:12:05 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <string>

#include <QMainWindow>

#ifdef COPASI_SBW_INTEGRATION
#include <QApplication>
#include <QEvent>

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
class QCustomEvent;

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
   * This is used to import an sbml file from a std::string in the gui
   * it does all the necessaray GUI stuff like asking to save the old
   * document, displaying messages, etc.
   */
  void importSBMLFromString(const std::string & sbmlDocumentText);

  std::string exportSBMLToString();

public slots:
  void slotShowSliders(bool flag);

  /**
   * This should only be called by the destructor of the object browser dialog
   * otherwise a memory leak occurs
   */
  void slotObjectBrowserDialogWasClosed();

  void autoSave();

protected slots:
  void slotFileOpen(QString file = QString::null);
  void slotFileExamplesCopasiFiles(QString file = QString::null);
  void slotFileExamplesSBMLFiles(QString file = QString::null);
  bool slotFileSave();
  bool slotFileSaveAs(QString str = QString::null);
  void newDoc();
  void slotFilePrint();
  void slotImportSBML(QString file = QString::null);
  void slotExportSBML();
  void slotExportMathModel();
  void slotTutorialWizard();
  void about();
  void license();
  void aboutQt();
  void slotQuit();
  void slotPreferences();
  void slotConvertToIrreversible();
  void closeEvent(QCloseEvent* e);
  void listViewsFolderChanged(Q3ListViewItem* item);
  void slotOpenRecentFile(int index);
  void slotOpenRecentSBMLFile(int index);
  bool slotRegistration();
  void slotCheckModel();
  void slotApplyInitialState();
  void slotUpdateInitialState();
  void slotFrameworkChanged(int index);
  void slotCapture();
  void slotUpdateMIRIAM();

  // SBW: handle the custom events
  void customEvent(QCustomEvent *);
  // SBW: start an analyzer when selected from the SBW menu
  void startSBWAnalyzer(int nId);

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

  DataModelGUI* dataModel; // to keep track of the data model..
  ListViews *listViews;
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
  QAction *mpaCapture;
  QAction* mpaUpdateMIRIAM;

  SliderDialog* mpSliders;
  ObjectBrowserDialog * mpObjectBrowser;

  bool mSaveAsRequired;
  QTimer *mpAutoSaveTimer;
  bool mSuspendAutoSave;

  //menus
  QMenu * mpMenuRecentFiles;
  QMenu * mpMenuExamples;
  void refreshRecentFileMenu();

  QMenu * mpMenuRecentSBMLFiles;
  void refreshRecentSBMLFileMenu();

  QMenu * mpTools;

  CMIRIAMResources * mpMIRIAMResources;

#ifdef COPASI_SBW_INTEGRATION
public:
  /**
   * This event is triggered by SBW asking COPASI to import an SBML document provided as a string
   */
  class QSBWSBMLEvent : public QCustomEvent
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
  class QSBWShutdownEvent: public QCustomEvent
  {
  public:
    QSBWShutdownEvent();
  };

  // We expose 2 methods to SBW, one to load an SBML file
  SystemsBiologyWorkbench::DataBlockWriter doAnalysis(SystemsBiologyWorkbench::Module from,
      SystemsBiologyWorkbench::DataBlockReader reader);

  // and another to return the SBML file COAPSI is currently working with
  SystemsBiologyWorkbench::DataBlockWriter getSBML(SystemsBiologyWorkbench::Module from,
      SystemsBiologyWorkbench::DataBlockReader reader);

  // those methods are registered here
  static void registerMethods(SystemsBiologyWorkbench::MethodTable<CopasiUI3Window> & table);

  // as part of the SBWListener we tell SBW here, that we want to react on the shutdown event
  virtual void onShutdown();

private:
  /**
   * Connect to SBW
   */
  void connectSBW();

  /**
   * Register COPASI as a module ins SBW
   */
  void registerSBW();

  /**
   * Refresh the SBW menu.
   */
  void refreshSBWMenu();

  /**
   * Retrieve the list of all services from the SBW broker
   * @param const std::string & category
   * @param const bool & recursive
   * @return std::vector< SystemsBiologyWorkbench::DataBlockReader > services
   */
  std::vector< SystemsBiologyWorkbench::DataBlockReader > findServices(const std::string & category,
      const bool & recursive);

  /**
   * The SBW module which handles the interaction with the SBW broker
   */
  SystemsBiologyWorkbench::ModuleImpl * mpSBWModule;

  /**
   * A list of SBW analyzer modules
   */
  QStringList mAnalyzerModules;

  /**
   * A list of the corresponding SBW services
   */
  QStringList mAnalyzerServices;

  /**
   * The SBW menu
   */
  QMenu * mpMenuSBW;

  /**
   * The id of the SBW menu
   */
  int mIdMenuSBW;

  /**
   * This variable indicates whether COPASI is to ignore SBW shutdown events
   */
  bool mIgnoreSBWShutdownEvent;

#endif // COPASI_SBW_INTEGRATION

#ifdef COPASI_LICENSE_COM
  bool checkRegistration();
#endif // COPASI_LICENSE_COM
};
