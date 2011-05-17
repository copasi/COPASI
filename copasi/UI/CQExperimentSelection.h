// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQExperimentSelection.h,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/17 13:10:18 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQEXPERIMENTSELECTION_H
#define CQEXPERIMENTSELECTION_H

#include <QVariant>
#include <QDialog>

#include "ui_CQExperimentSelection.h"

class QComboBox;
class CExperimentSet;

class CQExperimentSelection : public QDialog, public Ui::CQExperimentSelection
{
  Q_OBJECT

public:
  CQExperimentSelection(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
  ~CQExperimentSelection();

  virtual void load(QComboBox * pBox, const CExperimentSet * pExperimentSet);

protected:
  QComboBox * mpBox;

protected slots:

  void slotBtnOK();
  void slotBtnCancel();
  void slotBtnAll();
  void slotBtnNone();


private:
  void init();

};

#endif // CQEXPERIMENTSELECTION_H
