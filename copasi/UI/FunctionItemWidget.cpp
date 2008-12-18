// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/FunctionItemWidget.cpp,v $
//   $Revision: 1.18 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:57:54 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "FunctionItemWidget.h"

#include <qvariant.h>
/*
 *  Constructs a FunctionItemWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
FunctionItemWidget::FunctionItemWidget(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
    : QDialog(parent, name, modal, fl)
{
  setupUi(this);
}

/*
 *  Destroys the object and frees any allocated resources
 */
FunctionItemWidget::~FunctionItemWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void FunctionItemWidget::languageChange()
{
  retranslateUi(this);
}

void FunctionItemWidget::slotButtonClear()
{
  qWarning("FunctionItemWidget::slotButtonClear(): Not implemented yet");
}

void FunctionItemWidget::slotRadioDec()
{
  qWarning("FunctionItemWidget::slotRadioDec(): Not implemented yet");
}

void FunctionItemWidget::slotButton1()
{
  qWarning("FunctionItemWidget::slotButton1(): Not implemented yet");
}

void FunctionItemWidget::slotButtonItems()
{
  qWarning("FunctionItemWidget::slotButtonItems(): Not implemented yet");
}

void FunctionItemWidget::slotButton2()
{
  qWarning("FunctionItemWidget::slotButton2(): Not implemented yet");
}

void FunctionItemWidget::slotButton3()
{
  qWarning("FunctionItemWidget::slotButton3(): Not implemented yet");
}

void FunctionItemWidget::slotButtonConfirm()
{
  qWarning("FunctionItemWidget::slotButtonConfirm(): Not implemented yet");
}

void FunctionItemWidget::slotButton5()
{
  qWarning("FunctionItemWidget::slotButton5(): Not implemented yet");
}

void FunctionItemWidget::slotButton7()
{
  qWarning("FunctionItemWidget::slotButton7(): Not implemented yet");
}

void FunctionItemWidget::slotButton8()
{
  qWarning("FunctionItemWidget::slotButton8(): Not implemented yet");
}

void FunctionItemWidget::slotButton9()
{
  qWarning("FunctionItemWidget::slotButton9(): Not implemented yet");
}

void FunctionItemWidget::slotButton4()
{
  qWarning("FunctionItemWidget::slotButton4(): Not implemented yet");
}

void FunctionItemWidget::slotButton6()
{
  qWarning("FunctionItemWidget::slotButton6(): Not implemented yet");
}

void FunctionItemWidget::slotButtonSign()
{
  qWarning("FunctionItemWidget::slotButtonSign(): Not implemented yet");
}

void FunctionItemWidget::slotButtonAdd()
{
  qWarning("FunctionItemWidget::slotButtonAdd(): Not implemented yet");
}

void FunctionItemWidget::slotButtonSin()
{
  qWarning("FunctionItemWidget::slotButtonSin(): Not implemented yet");
}

void FunctionItemWidget::slotButtonLn()
{
  qWarning("FunctionItemWidget::slotButtonLn(): Not implemented yet");
}

void FunctionItemWidget::slotButtonMin()
{
  qWarning("FunctionItemWidget::slotButtonMin(): Not implemented yet");
}

void FunctionItemWidget::slotButtonDiv()
{
  qWarning("FunctionItemWidget::slotButtonDiv(): Not implemented yet");
}

void FunctionItemWidget::slotButtonLog()
{
  qWarning("FunctionItemWidget::slotButtonLog(): Not implemented yet");
}

void FunctionItemWidget::slotButtonMul()
{
  qWarning("FunctionItemWidget::slotButtonMul(): Not implemented yet");
}

void FunctionItemWidget::slotButtonExp()
{
  qWarning("FunctionItemWidget::slotButtonExp(): Not implemented yet");
}

void FunctionItemWidget::slotButtonLeftB()
{
  qWarning("FunctionItemWidget::slotButtonLeftB(): Not implemented yet");
}

void FunctionItemWidget::slotButtonRightB()
{
  qWarning("FunctionItemWidget::slotButtonRightB(): Not implemented yet");
}

void FunctionItemWidget::slotButtonPower()
{
  qWarning("FunctionItemWidget::slotButtonPower(): Not implemented yet");
}

void FunctionItemWidget::slotButtonCos()
{
  qWarning("FunctionItemWidget::slotButtonCos(): Not implemented yet");
}

void FunctionItemWidget::slotButton0()
{
  qWarning("FunctionItemWidget::slotButton0(): Not implemented yet");
}

void FunctionItemWidget::slotButtonCancel()
{
  qWarning("FunctionItemWidget::slotButtonCancel(): Not implemented yet");
}
