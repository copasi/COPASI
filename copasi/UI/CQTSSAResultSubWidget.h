// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.15 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/04/27 16:00:44 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQTSSARESULTSUBWIDGET_H
#define CQTSSARESULTSUBWIDGET_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQTSSAResultSubWidget.h"

class CTSSATask;
class CTSSAProblem;
class CTSSAMethod;
class CModel;

class CQTSSAResultSubWidget : public CopasiWidget, public Ui::CQTSSAResultSubWidget
{
  Q_OBJECT

public:
  CQTSSAResultSubWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
  ~CQTSSAResultSubWidget();

  CTSSATask* pTSSATask;
  CTSSAProblem* pProblem;
  CTSSAMethod* pMethod;

  CModel* pModel;
  C_INT mpIndex;
  bool mAnnot;
  void displayResult();
  void discardOldResults();

public slots:
  void changeInterval();

protected :

protected slots:
  void slotTableChanged();
  void slotTimeAndStepChanged();
  void changeContents();

  void saveDataToFile();
  virtual void init();


};

#endif // CQTSSARESULTSUBWIDGET_H
