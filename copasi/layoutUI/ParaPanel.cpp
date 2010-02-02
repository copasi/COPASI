// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/ParaPanel.cpp,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/02/02 16:45:22 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Qt headers
#include <QString>
#include <QValidator>

// local copasi headers
#include "CQLayoutMainWindow.h"
#include "ParaPanel.h"

CQParaPanel::CQParaPanel(QWidget* parent , const char* name):
    QWidget(parent, name)
{
  setupUi(this);
}

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
