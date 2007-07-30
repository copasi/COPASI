// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/Attic/ParaPanel.ui.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/07/30 10:44:15 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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

void ParaPanel::enableParameterChoice()
{
  spinBox1->setEnabled(true);
  scalingButtonGroup->setEnabled(true);
}

void ParaPanel::disableParameterChoice()
{
  spinBox1->setEnabled(false);
  scalingButtonGroup->setEnabled(false);
}

void ParaPanel::enableStepNumberChoice()
{
  stepEdit->setEnabled(true);
}

void ParaPanel::disableStepNumberChoice()
{
  stepEdit->setEnabled(false);
}

void ParaPanel::changeFrameRate()
{
  CVisParameters::stepsPerSecond = spinBox1->value();
}

void ParaPanel::setGlobalScaling()
{
  CQLayoutMainWindow * tmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget()->parentWidget()->parentWidget());
  assert(tmp);
  if (tmp) tmp -> setGlobalScaling();
  //((CQLayoutMainWindow *)(this->parentWidget()))->setGlobalScaling();
}

void ParaPanel::setIndividualScaling()
{
  CQLayoutMainWindow * tmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget()->parentWidget()->parentWidget());
  assert(tmp);
  if (tmp) tmp -> setIndividualScaling();

  //((CQLayoutMainWindow *)(this->parentWidget()))->setIndividualScaling();
}

void ParaPanel::setStepNumber(int i)
{
  QString s = QString::number(i, 10);
  stepEdit->setText(s);
}

void ParaPanel::stepEdit_returnPressed()
{
  QValidator* validator = new QIntValidator(0, INT_MAX, this);
  stepEdit->setValidator(validator);

  //if (validator->validate(stepEdit->text()) == QValidator::Acceptable) {
  QString line = stepEdit->text();
  bool ok;
  int val = line.toInt(&ok, 10);
  if (ok)
    {
      CQLayoutMainWindow * tmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget()->parentWidget()->parentWidget());
      assert(tmp);
      if (tmp) tmp -> setValueOnSlider(val);
    }
  //}
}
