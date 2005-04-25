/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQProgressDialog.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/25 18:13:22 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQProgressDialog.ui'
 **
 ** Created: Mon Apr 25 13:14:32 2005
 **      by: The User Interface Compiler ($Id: CQProgressDialog.h,v 1.1 2005/04/25 18:13:22 shoops Exp $)
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
    QVBoxLayout* CQProgressDialogLayout;
    QSpacerItem* mpSpacer;
    QHBoxLayout* mpBtnLayout;
    QSpacerItem* mpBtnSpacer;

  protected slots:
    virtual void languageChange();

  private:
    unsigned C_INT32 mItemCount;

    QPixmap image0;
    QPixmap image1;
    QPixmap image2;

    void init();
  };

#endif // CQPROGRESSDIALOG_H
