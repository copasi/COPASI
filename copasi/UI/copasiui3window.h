/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/copasiui3window.h,v $
   $Revision: 1.27 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/07/02 08:23:34 $
   End CVS Header */

#include <qmainwindow.h>
#include <qtoolbar.h>

#include "listviews.h"

class QToolButton;
class CopasiUI3Window : public QMainWindow
  {
    Q_OBJECT

  public:
    CopasiUI3Window();
    void enabled_object_browser_menu();
    void disable_object_browser_menu();
    DataModel* getDataModel();

  protected:
    DataModel* dataModel; // to keep track of the data model..
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
    void slotObjectBrowser();
    void about();
    void aboutQt();

    void slotQuit();
    void closeEvent(QCloseEvent* ce);

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
  };
