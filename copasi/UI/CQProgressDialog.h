// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQProgressDialog.h,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/08/31 14:33:33 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQPROGRESSDIALOG_H
#define CQPROGRESSDIALOG_H

#include <qdialog>

#include "ui_CQProgressDialog.h"
#include "CQIcons.h"

class CQProgressDialog : public QDialog, public Ui::CQProgressDialog
{
  Q_OBJECT

public:
  CQProgressDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
  ~CQProgressDialog();

  bool insertProgressItem(CQProgressItem * pItem);
  bool removeProgressItem(CQProgressItem * pItem);

protected:
  bool mProceed;
  bool mPause;
  QTimer *mpTimer;

protected slots:
  virtual void languageChange();

  void btnStopPressed();
  void btnPausePressed();
  void btnContinuePressed();
  void timerShow();

private:
  unsigned C_INT32 mItemCount;

  void init();
};

#endif // CQPROGRESSDIALOG_H
