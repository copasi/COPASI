/****************************************************************************
 ** Form implementation generated from reading ui file '.\FunctionItemWidget.ui'
 **
 ** Created: Mon Sep 29 00:08:09 2003
 **      by: The User Interface Compiler ($Id: FunctionItemWidget.cpp,v 1.2 2003/10/04 15:16:33 lixu1 Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "FunctionItemWidget.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qframe.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a FunctionItemWidget as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
FunctionItemWidget::FunctionItemWidget(QWidget* parent, const char* name, bool modal, WFlags fl)
    : QDialog(parent, name, modal, fl)
{
  if (!name)
    setName("FunctionItemWidget");
  FunctionItemWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "FunctionItemWidgetLayout");

  textFunction = new QTextEdit(this, "textFunction");

  FunctionItemWidgetLayout->addMultiCellWidget(textFunction, 0, 0, 0, 3);

  radioGroup = new QButtonGroup(this, "radioGroup");
  radioGroup->setExclusive(TRUE);
  radioGroup->setColumnLayout(0, Qt::Vertical);
  radioGroup->layout()->setSpacing(6);
  radioGroup->layout()->setMargin(11);
  radioGroupLayout = new QGridLayout(radioGroup->layout());
  radioGroupLayout->setAlignment(Qt::AlignTop);

  radioDec = new QRadioButton(radioGroup, "radioDec");
  radioDec->setEnabled(TRUE);

  radioGroupLayout->addWidget(radioDec, 0, 1);

  radioHex = new QRadioButton(radioGroup, "radioHex");
  radioHex->setEnabled(FALSE);

  radioGroupLayout->addWidget(radioHex, 0, 0);

  radioBin = new QRadioButton(radioGroup, "radioBin");
  radioBin->setEnabled(FALSE);

  radioGroupLayout->addWidget(radioBin, 0, 3);

  radioOct = new QRadioButton(radioGroup, "radioOct");
  radioOct->setEnabled(FALSE);

  radioGroupLayout->addWidget(radioOct, 0, 2);

  FunctionItemWidgetLayout->addMultiCellWidget(radioGroup, 1, 1, 0, 2);

  buttonAdd = new QPushButton(this, "buttonAdd");
  buttonAdd->setPaletteForegroundColor(QColor(170, 0, 0));

  FunctionItemWidgetLayout->addWidget(buttonAdd, 6, 0);

  button5 = new QPushButton(this, "button5");

  FunctionItemWidgetLayout->addWidget(button5, 3, 1);

  button9 = new QPushButton(this, "button9");

  FunctionItemWidgetLayout->addWidget(button9, 4, 1);

  button1 = new QPushButton(this, "button1");

  FunctionItemWidgetLayout->addWidget(button1, 2, 1);

  button6 = new QPushButton(this, "button6");

  FunctionItemWidgetLayout->addWidget(button6, 3, 2);

  button3 = new QPushButton(this, "button3");

  FunctionItemWidgetLayout->addWidget(button3, 2, 3);

  button8 = new QPushButton(this, "button8");

  FunctionItemWidgetLayout->addWidget(button8, 4, 0);

  button0 = new QPushButton(this, "button0");

  FunctionItemWidgetLayout->addWidget(button0, 4, 2);

  buttonLn = new QPushButton(this, "buttonLn");
  buttonLn->setPaletteForegroundColor(QColor(170, 0, 0));

  FunctionItemWidgetLayout->addWidget(buttonLn, 6, 2);

  buttonSin = new QPushButton(this, "buttonSin");
  buttonSin->setPaletteForegroundColor(QColor(170, 0, 0));

  FunctionItemWidgetLayout->addWidget(buttonSin, 7, 3);

  buttonDiv = new QPushButton(this, "buttonDiv");
  buttonDiv->setPaletteForegroundColor(QColor(170, 0, 0));

  FunctionItemWidgetLayout->addWidget(buttonDiv, 7, 1);

  buttonMul = new QPushButton(this, "buttonMul");
  buttonMul->setPaletteForegroundColor(QColor(170, 0, 0));

  FunctionItemWidgetLayout->addWidget(buttonMul, 6, 1);

  buttonRightB = new QPushButton(this, "buttonRightB");
  buttonRightB->setPaletteForegroundColor(QColor(170, 0, 0));

  FunctionItemWidgetLayout->addWidget(buttonRightB, 8, 1);

  buttonPower = new QPushButton(this, "buttonPower");
  buttonPower->setPaletteForegroundColor(QColor(170, 0, 0));

  FunctionItemWidgetLayout->addWidget(buttonPower, 8, 2);

  buttonLeftB = new QPushButton(this, "buttonLeftB");
  buttonLeftB->setPaletteForegroundColor(QColor(170, 0, 0));

  FunctionItemWidgetLayout->addWidget(buttonLeftB, 8, 0);

  buttonMin = new QPushButton(this, "buttonMin");
  buttonMin->setPaletteForegroundColor(QColor(170, 0, 0));

  FunctionItemWidgetLayout->addWidget(buttonMin, 7, 0);

  buttonExp = new QPushButton(this, "buttonExp");
  buttonExp->setPaletteForegroundColor(QColor(170, 0, 0));

  FunctionItemWidgetLayout->addWidget(buttonExp, 6, 3);

  button7 = new QPushButton(this, "button7");

  FunctionItemWidgetLayout->addWidget(button7, 3, 3);

  buttonItems = new QPushButton(this, "buttonItems");

  FunctionItemWidgetLayout->addWidget(buttonItems, 2, 0);

  button2 = new QPushButton(this, "button2");

  FunctionItemWidgetLayout->addWidget(button2, 2, 2);

  button4 = new QPushButton(this, "button4");

  FunctionItemWidgetLayout->addWidget(button4, 3, 0);

  buttonLog = new QPushButton(this, "buttonLog");
  buttonLog->setPaletteForegroundColor(QColor(170, 0, 0));

  FunctionItemWidgetLayout->addWidget(buttonLog, 7, 2);

  buttonSign = new QPushButton(this, "buttonSign");

  FunctionItemWidgetLayout->addWidget(buttonSign, 4, 3);

  buttonCos = new QPushButton(this, "buttonCos");
  buttonCos->setPaletteForegroundColor(QColor(170, 0, 0));

  FunctionItemWidgetLayout->addWidget(buttonCos, 8, 3);

  layout1 = new QGridLayout(0, 1, 1, 0, 6, "layout1");

  buttonConfirm = new QPushButton(this, "buttonConfirm");

  layout1->addWidget(buttonConfirm, 0, 0);

  buttonCancel = new QPushButton(this, "buttonCancel");

  layout1->addWidget(buttonCancel, 0, 1);

  FunctionItemWidgetLayout->addMultiCellLayout(layout1, 10, 10, 0, 3);

  line1 = new QFrame(this, "line1");
  line1->setFrameShape(QFrame::HLine);
  line1->setFrameShadow(QFrame::Sunken);
  line1->setFrameShape(QFrame::HLine);

  FunctionItemWidgetLayout->addMultiCellWidget(line1, 5, 5, 0, 3);

  line1_3 = new QFrame(this, "line1_3");
  line1_3->setFrameShape(QFrame::HLine);
  line1_3->setFrameShadow(QFrame::Sunken);
  line1_3->setFrameShape(QFrame::HLine);

  FunctionItemWidgetLayout->addMultiCellWidget(line1_3, 9, 9, 0, 3);

  buttonClear = new QPushButton(this, "buttonClear");
  buttonClear->setPaletteForegroundColor(QColor(170, 0, 0));

  FunctionItemWidgetLayout->addWidget(buttonClear, 1, 3);
  languageChange();
  resize(QSize(372, 373).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(radioDec, SIGNAL(clicked()), this, SLOT(slotRadioDec()));
  connect(buttonItems, SIGNAL(clicked()), this, SLOT(slotButtonItems()));
  connect(button0, SIGNAL(clicked()), this, SLOT(slotButton0()));
  connect(button1, SIGNAL(clicked()), this, SLOT(slotButton1()));
  connect(button2, SIGNAL(clicked()), this, SLOT(slotButton2()));
  connect(button3, SIGNAL(clicked()), this, SLOT(slotButton3()));
  connect(button4, SIGNAL(clicked()), this, SLOT(slotButton4()));
  connect(button5, SIGNAL(clicked()), this, SLOT(slotButton5()));
  connect(button6, SIGNAL(clicked()), this, SLOT(slotButton6()));
  connect(button7, SIGNAL(clicked()), this, SLOT(slotButton7()));
  connect(button9, SIGNAL(clicked()), this, SLOT(slotButton9()));
  connect(buttonSign, SIGNAL(clicked()), this, SLOT(slotButtonSign()));
  connect(buttonAdd, SIGNAL(clicked()), this, SLOT(slotButtonAdd()));
  connect(buttonMul, SIGNAL(clicked()), this, SLOT(slotButtonMul()));
  connect(buttonLn, SIGNAL(clicked()), this, SLOT(slotButtonLn()));
  connect(buttonExp, SIGNAL(clicked()), this, SLOT(slotButtonExp()));
  connect(buttonMin, SIGNAL(clicked()), this, SLOT(slotButtonMin()));
  connect(buttonDiv, SIGNAL(clicked()), this, SLOT(slotButtonDiv()));
  connect(buttonLog, SIGNAL(clicked()), this, SLOT(slotButtonLog()));
  connect(buttonSin, SIGNAL(clicked()), this, SLOT(slotButtonSin()));
  connect(buttonLeftB, SIGNAL(clicked()), this, SLOT(slotButtonLeftB()));
  connect(buttonRightB, SIGNAL(clicked()), this, SLOT(slotButtonRightB()));
  connect(buttonPower, SIGNAL(clicked()), this, SLOT(slotButtonPower()));
  connect(buttonCos, SIGNAL(clicked()), this, SLOT(slotButtonCos()));
  connect(button8, SIGNAL(clicked()), this, SLOT(slotButton8()));
  connect(buttonClear, SIGNAL(clicked()), this, SLOT(slotButtonClear()));
  connect(buttonConfirm, SIGNAL(clicked()), this, SLOT(slotButtonConfirm()));
  connect(buttonCancel, SIGNAL(clicked()), this, SLOT(slotButtonCancel()));

  // tab order
  setTabOrder(textFunction, radioHex);
  setTabOrder(radioHex, radioDec);
  setTabOrder(radioDec, radioOct);
  setTabOrder(radioOct, radioBin);
  setTabOrder(radioBin, buttonClear);
  setTabOrder(buttonClear, buttonItems);
  setTabOrder(buttonItems, button1);
  setTabOrder(button1, button2);
  setTabOrder(button2, button3);
  setTabOrder(button3, button4);
  setTabOrder(button4, button5);
  setTabOrder(button5, button6);
  setTabOrder(button6, button7);
  setTabOrder(button7, button8);
  setTabOrder(button8, button9);
  setTabOrder(button9, button0);
  setTabOrder(button0, buttonSign);
  setTabOrder(buttonSign, buttonAdd);
  setTabOrder(buttonAdd, buttonMul);
  setTabOrder(buttonMul, buttonLn);
  setTabOrder(buttonLn, buttonExp);
  setTabOrder(buttonExp, buttonMin);
  setTabOrder(buttonMin, buttonDiv);
  setTabOrder(buttonDiv, buttonLog);
  setTabOrder(buttonLog, buttonSin);
  setTabOrder(buttonSin, buttonLeftB);
  setTabOrder(buttonLeftB, buttonRightB);
  setTabOrder(buttonRightB, buttonPower);
  setTabOrder(buttonPower, buttonCos);
  setTabOrder(buttonCos, buttonConfirm);
  setTabOrder(buttonConfirm, buttonCancel);
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
  setCaption(tr("function editor"));
  radioGroup->setTitle(tr("Bin/Oct/Dec/Hex"));
  radioDec->setText(tr("Decimal"));
  radioHex->setText(tr("Hex"));
  radioBin->setText(tr("Bin"));
  radioOct->setText(tr("Octal"));
  buttonAdd->setText(tr("+"));
  button5->setText(tr("5"));
  button9->setText(tr("9"));
  button1->setText(tr("1"));
  button6->setText(tr("6"));
  button3->setText(tr("3"));
  button8->setText(tr("8"));
  button0->setText(tr("0"));
  buttonLn->setText(tr("ln"));
  buttonSin->setText(tr("sin"));
  buttonDiv->setText(tr("/"));
  buttonMul->setText(tr("*"));
  buttonRightB->setText(tr(")"));
  buttonPower->setText(tr("^"));
  buttonLeftB->setText(tr("("));
  buttonMin->setText(tr("-"));
  buttonExp->setText(tr("exp"));
  button7->setText(tr("7"));
  buttonItems->setText(tr("Items"));
  button2->setText(tr("2"));
  button4->setText(tr("4"));
  buttonLog->setText(tr("log"));
  buttonSign->setText(tr("+/-"));
  buttonCos->setText(tr("cos"));
  buttonConfirm->setText(tr("Confirm"));
  buttonCancel->setText(tr("Cancel"));
  buttonClear->setText(tr("Clear"));
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
