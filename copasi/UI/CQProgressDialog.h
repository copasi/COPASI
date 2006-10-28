/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQProgressDialog.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/10/28 00:26:44 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQProgressDialog.ui'
 **
 ** Created: Fri Jul 15 14:54:32 2005
 **      by: The User Interface Compiler ($Id: CQProgressDialog.h,v 1.6 2006/10/28 00:26:44 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQPROGRESSDIALOG_H
#define CQPROGRESSDIALOG_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>
#include "UI/CQProgressItem.h"

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
    QTimer *mpTimer;

    QVBoxLayout* CQProgressDialogLayout;
    QSpacerItem* mpSpacer;
    QHBoxLayout* mpBtnLayout;
    QSpacerItem* mpBtnSpacer;

  protected slots:
    virtual void languageChange();

    void btnStopPressed();
    void btnPausePressed();
    void btnContinuePressed();
    void timerShow();

  private:
    unsigned C_INT32 mItemCount;

    QPixmap image0;
    QPixmap image1;
    QPixmap image2;

    void init();
  };

#endif // CQPROGRESSDIALOG_H
