/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CopasiFileDialog.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: stupe $ 
   $Date: 2005/09/19 09:44:12 $
   End CVS Header */

#ifndef COPASI_FILE_DIALOG
#define COPASI_FILE_DIALOG

#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qdir.h>
#include <qpushbutton.h>

#include "CQFileDialogBtnGrp.h"

class CopasiFileDialog : public QFileDialog
  {
    Q_OBJECT
  private:
    CQFileDialogBtnGrp * mpGrp;

  public:
    CopasiFileDialog(QWidget * parent , const char * name , bool modal);

  public slots:
    virtual void slotExampleDir();
    virtual void slotHomeDir();
    QString GetOpenFileName(const QString & startWith = QString::null, const QString & filter = QString::null, QWidget * parent = 0, const char * name = 0, const QString & caption = QString::null, QString * selectedFilter = 0, bool resolveSymlinks = TRUE);
    QString GetSaveFileName(const QString & startWith = QString::null, const QString & filter = QString::null, QWidget * parent = 0, const char * name = 0, const QString & caption = QString::null, QString * selectedFilter = 0, bool resolveSymlinks = TRUE);
  };

#endif
