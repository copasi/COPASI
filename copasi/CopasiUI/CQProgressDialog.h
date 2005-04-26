/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQProgressDialog.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/26 14:29:21 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQProgressDialog.ui'
 **
 ** Created: Tue Apr 26 09:30:16 2005
 **      by: The User Interface Compiler ($Id: CQProgressDialog.h,v 1.2 2005/04/26 14:29:21 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQPROGRESSDIALOG_H
#define CQPROGRESSDIALOG_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>
#include "CQProgressItem.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QFrame;

class CQProgressDialog : public QDialog
  {
    Q_OBJECT

  public:
    CQProgressDialog(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
    ~CQProgressDialog();

    QPushButton* mpBtnPause;
    QPushButton* mpBtnContinue;
    QPushButton* mpBtnStop;
    QFrame* mpLine;

    bool insertProgressItem(CQProgressItem * pItem);
    bool removeProgressItem(CQProgressItem * pItem);

  protected:
    bool mProceed;
    bool mPause;

    QVBoxLayout* CQProgressDialogLayout;
    QSpacerItem* mpSpacer;
    QHBoxLayout* mpBtnLayout;
    QSpacerItem* mpBtnSpacer;

  protected slots:
    virtual void languageChange();

    void btnStopPressed();
    void btnPausePressed();
    void btnContinuePressed();

  private:
    unsigned C_INT32 mItemCount;

    QPixmap image0;
    QPixmap image1;
    QPixmap image2;

    void init();
  };

#endif // CQPROGRESSDIALOG_H
