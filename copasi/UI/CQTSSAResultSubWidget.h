// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/03/21 15:21:13 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQTSSARESULTSUBWIDGET_H
#define CQTSSARESULTSUBWIDGET_H

#include <qvariant.h>

#include "ui_CQTSSAResultSubWidget.h"

#include "CQArrayAnnotationsWidget.h"
#include "CTimeSeriesTable.h"

class CQTSSAResultSubWidget : public CopasiWidget, public Ui::CQTSSAResultSubWidget
{
  Q_OBJECT

public:
  CQTSSAResultSubWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
  ~CQTSSAResultSubWidget();

  void displayOptimizationTab(bool displayOptTab);
  void setStepNumber();
  void discardOldResults();
  void setStepSelectionDisabled(bool set);
  void activateTab(int tab);
  void changeToCSP();
  void changeToILDM();
  virtual void changeToILDMModified();
  void displayCSPDevelopment(bool displayCSPTab);

public slots:
  virtual CTimeSeriesTable * table();
  void changeILDMInterval();
  void changeCSPInterval();
  void hideButtons();
  virtual void changeILDMModifiedInterval();

protected slots:
  virtual void languageChange();

  void saveDataToFile();
  void toggleView();
  virtual void init();


};

#endif // CQTSSARESULTSUBWIDGET_H
