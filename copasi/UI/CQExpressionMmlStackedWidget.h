// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQEXPRESSIONMML_STACKEDWIDGET_H
#define CQEXPRESSIONMML_STACKEDWIDGET_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQExpressionMmlStackedWidget.h"

class CQExpressionMmlStackedWidget : public QStackedWidget, public Ui::CQExpressionMmlStackedWidget
{
  Q_OBJECT

public:
  CQExpressionMmlStackedWidget(QWidget* parent = 0);
  ~CQExpressionMmlStackedWidget();

  void setReadOnly(const bool & readOnly);

  QString getText();

public slots:
  void updateWidget();

signals:
  void signalCheckValidity(bool);

protected:
  void init();

protected slots:

  void slotGoExpressionWidget();
  void slotGoMmlWidget();

private:
  QString MMLStr;

  void saveTeX(const QString filename);
  void savePNG(const QString filename);
  void saveMML(const QString filename);

private slots:
  void slotSaveExpression();
};

#endif // CQEXPRESSIONMML_STACKEDWIDGET_H
