/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/copasiui3window.h,v $
   $Revision: 1.36 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/19 07:14:50 $
   End CVS Header */

#include <qmainwindow.h>
#include <qtoolbar.h>
#include "qvariant.h"

class QToolButton;
class ListViews;
class DataModelGUI;
class SliderDialog;
class QListViewItem;

class CopasiUI3Window : public QMainWindow
  {
    Q_OBJECT

  public:
    CopasiUI3Window();
    void enable_object_browser_menu();
    void disable_object_browser_menu();
    DataModelGUI* getDataModel();
    void saveFile();

  protected:
    DataModelGUI* dataModel; // to keep track of the data model..
    //QSplitter *splitter; // to hold different views...
    ListViews *listViews; // to create different list views...

  protected slots:
    void slotFileOpen(QString file = QString::null);
    void slotFileSave();
    void slotFileSaveAs(QString str = QString::null);
    void newDoc();
    void slotFilePrint();
    void slotImportSBML();
    void slotExportSBML();
    void slotObjectBrowserDialog();
    void slotTutorialWizard();
    void about();
    void aboutQt();
    void slotQuit();
    void slotConvertToIrreversible();
    void closeEvent(QCloseEvent* ce);
    void slotToggleSliders(const QVariant& variant);
    void slotSimpleSelection();
    void listViewsFolderChanged(QListViewItem* item);

  private:
    int closeFlag;
    int newFlag;
    QString gpsFile;
    QToolButton * msave_button;
    QPopupMenu * mpFileMenu;
    int nsave_menu_id;
    int nsaveas_menu_id;
    int nexport_menu_SBML;
    int nobject_browser;
    bool bobject_browser_open;
    void createToolBar();
    void createMenuBar();
    SliderDialog* sliders;
  };
