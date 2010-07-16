// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/07/14 11:09:51 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQEXPRESSIONMML_STACKEDWIDGET_H
#define CQEXPRESSIONMML_STACKEDWIDGET_H

#include <qvariant.h>

#include "ui_CQExpressionMmlStackedWidget.h"

#include <QStackedWidget>

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

#include "CQExpressionWidget.h"
#include "CQMmlScrollView.h"

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
  virtual void languageChange();

  void slotGoExpressionWidget();
  void slotGoMmlWidget();

private:
  QString MMLStr;

  void saveTeX(const QString filename);
  void saveMML(const QString filename);

private slots:
  void slotSaveExpression();
};

#endif // CQEXPRESSIONMML_STACKEDWIDGET_H
