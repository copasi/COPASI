/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/copasiui3window.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:46 $
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
