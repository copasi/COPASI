// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Qt headers
#include <QtCore/QString>
#include <QWidget>

// global headers
#include <assert.h>

// global copasi headers
#include "copasi/copasi.h"

// local copasi headers
#include "NodeSizePanel.h"
#include "CQLayoutMainWindow.h"

void NodeSizePanel::setMinAndMaxValues()
{
  CQLayoutMainWindow * tmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget());
  assert(tmp);
  QString s1 = lineEdit1->text();
  bool ok1;
  C_INT32 val1 = s1.toInt(&ok1, 10);
  QString s2 = lineEdit2->text();
  bool ok2;
  C_INT32 val2 = s2.toInt(&ok2, 10);

  if ((tmp) && (ok1) && (ok2) && (val1 < val2))
    tmp->setMinAndMaxValue(val1, val2);

  close();
}

void NodeSizePanel::cancel()
{
  close();
}

void NodeSizePanel::setMinValue()
{
  CQLayoutMainWindow * tmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget());
  assert(tmp);
  QString s = lineEdit1->text();
  bool ok;
  C_INT32 val = s.toInt(&ok, 10);

  if ((tmp) && (ok))
    tmp->setMinValue(val);
}

void NodeSizePanel::setMaxValue()
{
  CQLayoutMainWindow * tmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget());
  assert(tmp);
  QString s = lineEdit1->text();
  bool ok;
  C_INT32 val = s.toInt(&ok, 10);

  if ((tmp) && (ok))
    tmp->setMaxValue(val);
}

NodeSizePanel::NodeSizePanel(QWidget* parent , bool modal , Qt::WindowFlags fl):
  QDialog(parent, fl)
{
  setupUi(this);
  this->setModal(modal);
  CQLayoutMainWindow * tmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget());
  assert(tmp);

  if (tmp)
    {
      C_INT32 minV = (C_INT32)(tmp->getMinNodeSize());
      C_INT32 maxV = (C_INT32)(tmp->getMaxNodeSize());
      lineEdit1->setText(QString::number(minV));
      lineEdit2->setText(QString::number(maxV));
    }
}
