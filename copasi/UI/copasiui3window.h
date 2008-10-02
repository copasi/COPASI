// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/copasiui3window.h,v $
//   $Revision: 1.75 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/10/02 16:32:34 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <string>

#include <qmainwindow.h>
#include <qdialog.h>
#include <qtoolbar.h>
#include "qvariant.h"

#ifdef COPASI_SBW_INTEGRATION

#include <qapplication.h>
#include <qevent.h>

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

class QToolButton;
class QListViewItem;
class ListViews;
class DataModelGUI;
class SliderDialog;
class CQTrajectoryWidget;
class SteadyStateWidget;
class ScanWidget;
class QPushButton;
class QLabel;
class QHBox;
class QScrollView;
class QAction;
class ObjectBrowserDialog;
class QComboBox;
class CMIRIAMResources;
class CMIRIAMResourceObject;

class CopasiUI3Window : public QMainWindow
#ifdef COPASI_SBW_INTEGRATION
      // A SBW listener can catch messages from SBW ... used here to allow copasi to be shut down
      , public SBWListener
#endif // COPASI_SBW_INTEGRATION

  {
    Q_OBJECT

#ifdef COPASI_SBW_INTEGRATION

    // Create 2 custom events, one containing the filename to an SBML document to be loaded
    // into copasi
  class QSBWSBMLEvent : public QCustomEvent
      {
      public:
        QSBWSBMLEvent(const std::string& sSBMLModel)
            : QCustomEvent(65433), _sSBML(sSBMLModel) {}
        std::string sbmlString() const {return _sSBML;}
      private:
        std::string _sSBML;
      };

    // And another asking COPASI nicely to shut down
  class QSBWShutdownEvent: public QCustomEvent
      {
      public:
        QSBWShutdownEvent() : QCustomEvent(65434) {}};
  public:

    // We expose to methods to SBW, one to load an SBML file
    SystemsBiologyWorkbench::DataBlockWriter doAnalysis(SystemsBiologyWorkbench::Module /*from*/, SystemsBiologyWorkbench::DataBlockReader reader);
    // and another to return the SBML file COAPSI is currently working with
    SystemsBiologyWorkbench::DataBlockWriter getSBML(SystemsBiologyWorkbench::Module /*from*/, SystemsBiologyWorkbench::DataBlockReader reader);
    // those methods are registered here
    static void registerMethods(SystemsBiologyWorkbench::MethodTable<CopasiUI3Window> &table)
    {
      table.addMethod(&CopasiUI3Window::doAnalysis, "void doAnalysis(string)", false, "Starts up the CopasiUI and loads the given Model.");
      table.addMethod(&CopasiUI3Window::getSBML, "string getSBML()", false, "returns the currently loaded Copasi model.");
    }

    // as part of the SBWListener we tell SBW here, that we want to react on the shutdown event
    virtual void onShutdown() {QApplication::postEvent(this, new QSBWShutdownEvent());}

#endif // COPASI_SBW_INTEGRATION

  public:
    static CopasiUI3Window * create();
    ~CopasiUI3Window();
    //void enable_object_browser_menu();
    //void disable_object_browser_menu();
    DataModelGUI* getDataModel();
    //void saveFile();

    CQTrajectoryWidget* getTrajectoryWidget();
    SteadyStateWidget* getSteadyStateWidget();
    ScanWidget* getScanWidget();

    void checkPendingMessages();
    void suspendAutoSave(const bool & suspend);
    void importSBMLFromString(const std::string& sbmlDocumentText);
    std::string exportSBMLToString();

  protected:
    CopasiUI3Window();
    DataModelGUI* dataModel; // to keep track of the data model..
    ListViews *listViews;
    QComboBox * mpBoxSelectFramework;

  public slots:
    void slotShowSliders(bool flag);

    /**
     * This should only be called by the destructor of the object browser dialog
     * otherwise a memory leak occurs
     */
    void slotObjectBrowserDialogWasClosed();

    void slotPreferences();
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
    void slotConvertToIrreversible();
    void closeEvent(QCloseEvent* e);
    void listViewsFolderChanged(QListViewItem* item);
    void slotOpenRecentFile(int index);
    void slotOpenRecentSBMLFile(int index);
    bool slotRegistration();
    void slotCheckModel();
    void slotApplyInitialState();
    void slotUpdateInitialState();
    void slotFrameworkChanged(int index);
    void slotCapture();
    // handle the custom events
    void customEvent(QCustomEvent *);
    // start an analyzer when selected from the SBW menu
    void startSBWAnalyzer(int nId);
    void slotUpdateMIRIAM();

    /**
     * This should only be called via signal by the corresponding QAction mpaObjectBrowser.
     * Otherwise the QAction will not be up to date.
     */
    void slotShowObjectBrowserDialog(bool flag);

  private:
#ifdef COPASI_SBW_INTEGRATION

    // a list of SBW Analyzer Modules
    QStringList _oAnalyzerModules;
    // and corresponding services
    QStringList _oAnalyzerServices;

    // the SBW menu
    QPopupMenu * mpMenuSBW;

    // method to populate the SBW menu
    void refreshSBWMenu();

    std::vector< SystemsBiologyWorkbench::DataBlockReader > findServices(std::string var0, bool var1);

#endif // COPASI_SBW_INTEGRATION

    int newFlag;
    QString FixedTitle;
    //QToolButton * msave_button;
    //QPopupMenu * tools;

    //int nsave_menu_id;
    //int nsaveas_menu_id;
    //int nexport_menu_SBML;
    //int nexport_menu_MathModel;
    //int nobject_browser;
    //bool mbObject_browser_open;

    void createActions();
    void createToolBar();
    void createMenuBar();

    QAction* mpaNew;
    QAction* mpaOpen;
    QAction* mpaOpenCopasiFiles;
    QAction* mpaOpenSBMLFiles;
    QAction* mpaSave;
    QAction* mpaSaveAs;
    QAction* mpaImportSBML;
    QAction* mpaExportSBML;
    QAction* mpaExportODE;
    QAction* mpaObjectBrowser;
    QAction* mpaSliders;
    QAction* mpaCheckModel;
    QAction* mpaApplyInitialState;
    QAction* mpaUpdateInitialState;
    QAction *mpaCapture;
    QAction* mpaUpdateMIRIAM;

    void CleanUp();

    SliderDialog* mpSliders;
    ObjectBrowserDialog * mpObjectBrowser;

    bool mSaveAsRequired;
    void updateTitle();
    QTimer *mpAutoSaveTimer;
    bool mSuspendAutoSave;

    QPopupMenu * mpMenuExamples;

    QPopupMenu * mpMenuRecentFiles;
    void refreshRecentFileMenu();

    QPopupMenu * mpMenuRecentSBMLFiles;
    void refreshRecentSBMLFileMenu();

    CMIRIAMResources * mpMIRIAMResources;

#ifdef COPASI_LICENSE_COM
    bool checkRegistration();
#endif // COPASI_LICENSE_COM
  };
