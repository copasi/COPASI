/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/copasiui3window.h,v $
   $Revision: 1.21 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/05 18:38:04 $
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

  protected:

    DataModel* dataModel; // to keep track of the data model..
    QSplitter *splitter; // to hold different views...
    ListViews *listViews; // to create different list views...

  protected slots:
    void slotFileOpen();
    void slotFileSave();
    void slotFileSaveAs(QString str = QString::null);
    void newDoc();
    void slotFilePrint();
    void slotImportSBML();
    void slotExportSBML();
    void slotObjectBrowser();
    void about();
    void aboutQt();

  private:
    QString gpsFile;
    QToolButton * msave_button;
    QPopupMenu * file;
    int nsave_menu_id;
    int nsaveas_menu_id;
    int nexport_menu_SBML;
    int nobject_browser;
    bool bobject_browser_open;
    void createToolBar();
    void createMenuBar();
  };
