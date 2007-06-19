// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/copasiui3window.h,v $
//   $Revision: 1.64 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/06/19 16:35:28 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <string>

#include <qmainwindow.h>
#include <qdialog.h>
#include <qtoolbar.h>
#include "qvariant.h"

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

class CopasiUI3Window : public QMainWindow
  {
    Q_OBJECT

  public:
    static CopasiUI3Window * create();
    ~CopasiUI3Window();
    void enable_object_browser_menu();
    void disable_object_browser_menu();
    DataModelGUI* getDataModel();
    void saveFile();
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
    //QSplitter *splitter; // to hold different views...
    ListViews *listViews; // to create different list views...

  public slots:
    void slotToggleSliders();
    void slotObjectBrowserDialog();
    void slotPreferences();
    void autoSave();

  protected slots:
    void slotFileOpen(QString file = QString::null);
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

  private:
    int newFlag;
    QString FixedTitle;
    QToolButton * msave_button;
    QPopupMenu * mpFileMenu, * tools;

    int nsave_menu_id;
    int nsaveas_menu_id;
    int nexport_menu_SBML;
    int nexport_menu_MathModel;
    int nobject_browser;
    bool bobject_browser_open;
    void createToolBar();
    void createMenuBar();
    void CleanUp();
    SliderDialog* sliders;
    int mShowSlidersMenuEntry;
    QToolButton* mpToggleSliderDialogButton;
    bool mSaveAsRequired;
    void updateTitle();
    QTimer *mpAutoSaveTimer;
    bool mSuspendAutoSave;

    QPopupMenu * mpMenuRecentFiles;
    void refreshRecentFileMenu();

    QPopupMenu * mpMenuRecentSBMLFiles;
    void refreshRecentSBMLFileMenu();

#ifdef COPASI_LICENSE_COM
    bool checkRegistration();
#endif // COPASI_LICENSE_COM
  };
