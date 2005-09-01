/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CopasiFileDialog.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/09/01 17:03:03 $
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
  };

#endif
