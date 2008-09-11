// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/Attic/ParaPanel.ui.h,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/09/11 10:31:33 $
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
#include "copasi/layoutUI/CVisParameters.h"
#include "copasi/layoutUI/CQLayoutMainWindow.h"

#include <qstring.h>
#include <qvalidator.h>

void CQParaPanel::enableModeChoice()
{
  mpScalingButtonGroup_2->setEnabled(true);
}

void CQParaPanel::disableModeChoice()
{
  mpScalingButtonGroup_2->setEnabled(false);
}

void CQParaPanel::enableParameterChoice()
{
  mpSpinBox1->setEnabled(true);
  mpScalingButtonGroup->setEnabled(true);
}

void CQParaPanel::disableParameterChoice()
{
  mpSpinBox1->setEnabled(false);
  mpScalingButtonGroup->setEnabled(false);
}

void CQParaPanel::enableStepNumberChoice()
{
  mpStepEdit->setEnabled(true);
}

void CQParaPanel::disableStepNumberChoice()
{
  mpStepEdit->setEnabled(false);
}

void CQParaPanel::changeFrameRate()
{
  CQLayoutMainWindow * tmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget()->parentWidget()->parentWidget()->parentWidget());
  assert(tmp);
  if (tmp) tmp -> setStepsPerSecond(mpSpinBox1->value());
}

void CQParaPanel::setGlobalScaling()
{
  CQLayoutMainWindow * tmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget()->parentWidget()->parentWidget()->parentWidget());
  assert(tmp);
  if (tmp) tmp -> setGlobalScaling();
}

void CQParaPanel::setIndividualScaling()
{
  CQLayoutMainWindow * tmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget()->parentWidget()->parentWidget()->parentWidget());
  assert(tmp);
  if (tmp) tmp -> setIndividualScaling();
}

void CQParaPanel::setStepNumber(int i)
{
  QString s = QString::number(i, 10);
  mpStepEdit->setText(s);
}

void CQParaPanel::stepEdit_returnPressed()
{
  QValidator* pValidator = new QIntValidator(0, INT_MAX, this);
  mpStepEdit->setValidator(pValidator);

  QString line = mpStepEdit->text();
  bool ok;
  int val = line.toInt(&ok, 10);
  if (ok)
    {
      CQLayoutMainWindow * tmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget()->parentWidget()->parentWidget()->parentWidget());
      assert(tmp);
      if (tmp) tmp -> setValueOnSlider(val);
    }
}

void CQParaPanel::setSizeMode()
{
  CQLayoutMainWindow * tmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget()->parentWidget()->parentWidget()->parentWidget());
  assert(tmp);
  if (tmp) tmp -> setSizeMode();
}

void CQParaPanel::setColorMode()
{
  CQLayoutMainWindow * tmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget()->parentWidget()->parentWidget()->parentWidget());
  assert(tmp);
  if (tmp) tmp -> setColorMode();
}
