/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CopasiFileDialog.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/08/22 14:07:14 $
   End CVS Header */

#ifndef COPASI_FILE_DIALOG
#define COPASI_FILE_DIALOG

#include <qfiledialog.h>
#include <qpushbutton.h>

class CopasiFileDialog : public QFileDialog
  {
    Q_OBJECT
  private:
    QPushButton *exampleDirButton;
    QPushButton *homeDirButton;
    QPushButton *copasiDirButton;

  public:
    CopasiFileDialog(QWidget * parent , const char * name , bool modal);
    void addLocation(QWidget*);
  public slots:
    virtual void slotExampleDir();
    virtual void slotHomeDir();
    virtual void slotCopasiDir();
  };

#endif
