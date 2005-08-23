/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CopasiFileDialog.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: stupe $ 
   $Date: 2005/08/23 00:48:48 $
   End CVS Header */

#ifndef COPASI_FILE_DIALOG
#define COPASI_FILE_DIALOG

#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qdir.h>
#include <qpushbutton.h>

class CopasiFileDialog : public QFileDialog
  {
    Q_OBJECT
  private:
    QPushButton *exampleDirButton;
    QPushButton *homeDirButton;
    QPushButton *copasiDirButton;
    QDir *directoryValue;

  public:
    CopasiFileDialog(QWidget * parent , const char * name , bool modal);
    void addLocation(QWidget*);
  public slots:
    virtual void slotExampleDir();
    virtual void slotHomeDir();
    virtual void slotCopasiDir();
  };

#endif
