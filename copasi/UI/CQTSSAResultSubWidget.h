// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
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

  const CModel* pModel;
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
