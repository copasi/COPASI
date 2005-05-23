/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/copasiui3window.h,v $
   $Revision: 1.47 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/23 21:13:40 $
   End CVS Header */

#include <qmainwindow.h>
#include <qtoolbar.h>
#include "qvariant.h"

class QToolButton;
class ListViews;
class DataModelGUI;
class SliderDialog;
class QListViewItem;
class TrajectoryWidget;
class SteadyStateWidget;

class CopasiUI3Window : public QMainWindow
  {
    Q_OBJECT

  public:
    CopasiUI3Window();
    ~CopasiUI3Window();
    void enable_object_browser_menu();
    void disable_object_browser_menu();
    DataModelGUI* getDataModel();
    void saveFile();
    TrajectoryWidget* getTrajectoryWidget();
    SteadyStateWidget* getSteadyStateWidget();
    void checkPendingMessages();

  protected:
    DataModelGUI* dataModel; // to keep track of the data model..
    //QSplitter *splitter; // to hold different views...
    ListViews *listViews; // to create different list views...

  public slots:
    void slotToggleSliders();
    void slotObjectBrowserDialog();

  protected slots:
    void slotFileOpen(QString file = QString::null);
    void slotFileSave();
    void slotFileSaveAs(QString str = QString::null);
    void newDoc();
    void slotFilePrint();
    void slotImportSBML();
    void slotExportSBML();
    void slotTutorialWizard();
    void about();
    void aboutQt();
    void slotQuit();
    void slotConvertToIrreversible();
    void closeEvent(QCloseEvent* ce);
    void listViewsFolderChanged(QListViewItem* item);

  private:
    int closeFlag;
    int newFlag;
    QString FixedTitle;
    QToolButton * msave_button;
    QPopupMenu * mpFileMenu, * tools;

    int nsave_menu_id;
    int nsaveas_menu_id;
    int nexport_menu_SBML;
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
  };
