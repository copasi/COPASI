/****************************************************************************
 ** Form implementation generated from reading ui file '.\FunctionItemWidget.ui'
 **
 ** Created: Mon Sep 29 00:08:09 2003
 **      by: The User Interface Compiler ($Id: FunctionItemWidget.cpp,v 1.8 2003/10/06 04:07:05 lixu1 Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "FunctionItemWidget.h"
#include "ObjectBrowser.h"
#include "copasi.h"
#include "report/CCopasiObject.h"
#include "report/CCopasiObjectName.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qframe.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qcolor.h>

/*
 *  Constructs a FunctionItemWidget as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
FunctionItemWidget::FunctionItemWidget(QWidget* parent, const char* name, bool modal, WFlags fl)
    : QDialog(parent, name, modal, fl),
    strFunction(NULL)
{
  if (!name)
    setName("FunctionItemWidget");
  FunctionItemWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "FunctionItemWidgetLayout");

  textFunction = new QTextEdit(this, "textFunction");
  textFunction->setColor(QColor(0, 0, 0));

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

  radioDec->setChecked(true);
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
  //qWarning("FunctionItemWidget::slotButtonClear(): Not implemented yet");
  textFunction->clear();
}

void FunctionItemWidget::slotRadioDec()
{
  qWarning("FunctionItemWidget::slotRadioDec(): Not implemented yet");
}

void FunctionItemWidget::slotButton1()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "1");
  textFunction->insert("1");
  index++;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButtonItems()
{
  ObjectBrowser* pSelectedObjects = new ObjectBrowser();
  std::vector<CCopasiObject*>* pSelectedVector = new std::vector<CCopasiObject*>();
  pSelectedObjects->setOutputVector(pSelectedVector);

  if (pSelectedObjects->exec () == QDialog::Rejected)
    {
      pdelete(pSelectedVector);
      return;
    }

  if (pSelectedVector->size() == 0)
    {
      pdelete(pSelectedVector);
      return;
    }

  int i = 0;
  for (; i < pSelectedVector->size(); i++)
    if ((*pSelectedVector)[i])
      break;

  if (i >= pSelectedVector->size()) //no result returned
    {
      pdelete(pSelectedVector);
      return;
    }

  //  if (addNewScanItem((*pSelectedVector)[i]))
  //    ObjectListBox->insertItem ((*pSelectedVector)[i]->getObjectUniqueName().c_str(), nSelectedObjects - 1);

  // wrap the object name;
  objectLinkWrapper((*pSelectedVector)[i]);

  pdelete(pSelectedVector);
}

void FunctionItemWidget::slotButton2()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "2");
  textFunction->insert("2");
  index++;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButton3()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "3");
  textFunction->insert("3");
  index++;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButtonConfirm()
{
  *strFunction = textFunction->text().latin1();
  strFunction = NULL;
  QDialog::done(QDialog::Accepted);
}

void FunctionItemWidget::slotButton5()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "5");
  textFunction->insert("5");
  index++;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButton7()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "7");
  textFunction->insert("7");
  index++;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButton8()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "8");
  textFunction->insert("8");
  index++;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButton9()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "9");
  textFunction->insert("9");
  index++;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButton4()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "4");
  textFunction->insert("4");
  index++;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButton6()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "6");
  textFunction->insert("6");
  index++;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButtonSign()
{
  /* here is the sign function that makes to change only the first sign of the function;
      like a -> a+
       a+/- -> a-/+
  */
  std::string strTemp;
  strTemp = textFunction->text().latin1();
  if ((strTemp[strTemp.length() - 1] != '+') && (strTemp[strTemp.length() - 1] != '-'))
    // add a '+' or a '-' in front of the expression
    {
      textFunction->setText(textFunction->text() + '+');
    }
  else
    // change sign of the expression
    {
      if (strTemp[strTemp.length() - 1] == '+')
        {
          strTemp[strTemp.length() - 1] = '-';
          textFunction->setText(strTemp.c_str());
        }
      else
        {
          strTemp[strTemp.length() - 1] = '+';
          textFunction->setText(strTemp.c_str());
        }
    }
  textFunction->moveCursor(QTextEdit::MoveEnd, false);

  /* here is the sign function that makes to change only the first sign of the function;
      like a -> +a
       +/-a -> -/+a
   
    if (((textFunction->text().latin1())[0] != '+') && ((textFunction->text().latin1())[0] != '-'))
      // add a '+' or a '-' in front of the expression
      {
        int para, index;
        textFunction->getCursorPosition(&para, &index);
        textFunction->setText('+' + textFunction->text());
        index++;
        textFunction->setCursorPosition(para, index);
      }
    else
      // change sign of the expression
      {
        std::string strTemp;
        if ((textFunction->text().latin1())[0] == '+')
          {
            strTemp = textFunction->text().latin1();
            strTemp[0] = '-';
            textFunction->setText(strTemp.c_str());
          }
        else
          {
            strTemp = textFunction->text().latin1();
            strTemp[0] = '+';
            textFunction->setText(strTemp.c_str());
          }
      }
  */
}

void FunctionItemWidget::slotButtonAdd()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "+");
  textFunction->insert("+");
  index++;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButtonSin()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "sin");
  textFunction->insert("sin");
  index += 3;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButtonLn()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "ln");
  textFunction->insert("ln");
  index += 2;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButtonMin()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "-");
  textFunction->insert("-");
  index++;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButtonDiv()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "/");
  textFunction->insert("/");
  index++;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButtonLog()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "log");
  textFunction->insert("log");
  index += 3;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButtonMul()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "*");
  textFunction->insert("*");
  index++;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButtonExp()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "exp");
  textFunction->insert("exp");
  index += 3;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButtonLeftB()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "(");
  textFunction->insert("(");
  index++;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButtonRightB()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + ")");
  textFunction->insert(")");
  index++;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButtonPower()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "^");
  textFunction->insert("^");
  index++;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButtonCos()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "cos");
  textFunction->insert("cos");
  index += 3;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButton0()
{
  int para, index;
  textFunction->getCursorPosition(&para, &index);
  //textFunction->setText(textFunction->text() + "0");
  textFunction->insert("0");
  index++;
  textFunction->setCursorPosition(para, index);
}

void FunctionItemWidget::slotButtonCancel()
{
  //  qWarning("FunctionItemWidget::slotButtonCancel(): Not implemented yet");
  strFunction = NULL;
  QDialog::done(QDialog::Rejected);
}

void FunctionItemWidget::setStrFunction(std::string * targetFunctionPtr)
{
  strFunction = targetFunctionPtr;
  textFunction->setText(strFunction->c_str());
  textFunction->moveCursor(QTextEdit::MoveEnd, false);
}

void FunctionItemWidget::objectLinkWrapper(CCopasiObject * pObject)
{
  std::string lnk;
  lnk = "<";
  lnk = lnk + pObject->getCN().c_str();
  lnk = lnk + ">";
  textFunction->insert(lnk.c_str());

  //  textFunction->setColor(QColor(255,0,0));
  //  textFunction->setColor(QColor(0,0,0));
  //  lnk = "<a href=";
  //  lnk = lnk + pObject->getCN().c_str();
  //  lnk = lnk + ">";
  //  lnk = lnk + pObject->getObjectUniqueName().c_str();
  //  lnk = lnk + "</a>";
  //  textFunction->setText(textFunction->text() + lnk.c_str());
  //  int para, index;
  //  textFunction->getCursorPosition(&para, &index);
  //  index += strlen(lnk.c_str());
  textFunction->moveCursor(QTextEdit::MoveEnd, false);
}
