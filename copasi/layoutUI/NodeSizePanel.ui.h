// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/Attic/NodeSizePanel.ui.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/10/27 16:52:19 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and destroy().
 ** These will automatically be called by the form's constructor and
 ** destructor.
 *****************************************************************************/
#include "copasi.h"
#include "copasi/layoutUI/CQLayoutMainWindow.h"

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

void NodeSizePanel::init()
{
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
