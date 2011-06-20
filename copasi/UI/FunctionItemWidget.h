// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/FunctionItemWidget.h,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2011/06/20 16:07:10 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef FUNCTIONITEMWIDGET_H
#define FUNCTIONITEMWIDGET_H

#include <QVariant>

#include <Q3ButtonGroup>
#include <QTextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QBoxLayout>
#include <QGridLayout>
#include <QFrame>

class Ui_FunctionItemWidget
{
public:
  QGridLayout *gridLayout;
  QTextEdit *textFunction;
  Q3ButtonGroup *radioGroup;
  QGridLayout *gridLayout1;
  QRadioButton *radioDec;
  QRadioButton *radioHex;
  QRadioButton *radioBin;
  QRadioButton *radioOct;
  QPushButton *buttonAdd;
  QPushButton *button5;
  QPushButton *button9;
  QPushButton *button1;
  QPushButton *button6;
  QPushButton *button3;
  QPushButton *button8;
  QPushButton *button0;
  QPushButton *buttonLn;
  QPushButton *buttonSin;
  QPushButton *buttonDiv;
  QPushButton *buttonMul;
  QPushButton *buttonRightB;
  QPushButton *buttonPower;
  QPushButton *buttonLeftB;
  QPushButton *buttonMin;
  QPushButton *buttonExp;
  QPushButton *button7;
  QPushButton *buttonItems;
  QPushButton *button2;
  QPushButton *button4;
  QPushButton *buttonLog;
  QPushButton *buttonSign;
  QPushButton *buttonCos;
  QGridLayout *gridLayout2;
  QPushButton *buttonConfirm;
  QPushButton *buttonCancel;
  QFrame *line1;
  QFrame *line1_3;
  QPushButton *buttonClear;

  void setupUi(QDialog *FunctionItemWidget)
  {
    if (FunctionItemWidget->objectName().isEmpty())
      FunctionItemWidget->setObjectName(QString::fromUtf8("FunctionItemWidget"));

    FunctionItemWidget->resize(372, 373);
    gridLayout = new QGridLayout(FunctionItemWidget);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    textFunction = new QTextEdit(FunctionItemWidget);
    textFunction->setObjectName(QString::fromUtf8("textFunction"));

    gridLayout->addWidget(textFunction, 0, 0, 1, 4);

    radioGroup = new Q3ButtonGroup(FunctionItemWidget);
    radioGroup->setObjectName(QString::fromUtf8("radioGroup"));
    radioGroup->setExclusive(true);
    radioGroup->setColumnLayout(0, Qt::Vertical);
    radioGroup->layout()->setSpacing(6);
    radioGroup->layout()->setMargin(11);
    gridLayout1 = new QGridLayout(radioGroup->layout());
    gridLayout1->setAlignment(Qt::AlignTop);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    radioDec = new QRadioButton(radioGroup);
    radioDec->setObjectName(QString::fromUtf8("radioDec"));
    radioDec->setEnabled(true);

    gridLayout1->addWidget(radioDec, 0, 1, 1, 1);

    radioHex = new QRadioButton(radioGroup);
    radioHex->setObjectName(QString::fromUtf8("radioHex"));
    radioHex->setEnabled(false);

    gridLayout1->addWidget(radioHex, 0, 0, 1, 1);

    radioBin = new QRadioButton(radioGroup);
    radioBin->setObjectName(QString::fromUtf8("radioBin"));
    radioBin->setEnabled(false);

    gridLayout1->addWidget(radioBin, 0, 3, 1, 1);

    radioOct = new QRadioButton(radioGroup);
    radioOct->setObjectName(QString::fromUtf8("radioOct"));
    radioOct->setEnabled(false);

    gridLayout1->addWidget(radioOct, 0, 2, 1, 1);

    gridLayout->addWidget(radioGroup, 1, 0, 1, 3);

    buttonAdd = new QPushButton(FunctionItemWidget);
    buttonAdd->setObjectName(QString::fromUtf8("buttonAdd"));

    gridLayout->addWidget(buttonAdd, 6, 0, 1, 1);

    button5 = new QPushButton(FunctionItemWidget);
    button5->setObjectName(QString::fromUtf8("button5"));

    gridLayout->addWidget(button5, 3, 1, 1, 1);

    button9 = new QPushButton(FunctionItemWidget);
    button9->setObjectName(QString::fromUtf8("button9"));

    gridLayout->addWidget(button9, 4, 1, 1, 1);

    button1 = new QPushButton(FunctionItemWidget);
    button1->setObjectName(QString::fromUtf8("button1"));

    gridLayout->addWidget(button1, 2, 1, 1, 1);

    button6 = new QPushButton(FunctionItemWidget);
    button6->setObjectName(QString::fromUtf8("button6"));

    gridLayout->addWidget(button6, 3, 2, 1, 1);

    button3 = new QPushButton(FunctionItemWidget);
    button3->setObjectName(QString::fromUtf8("button3"));

    gridLayout->addWidget(button3, 2, 3, 1, 1);

    button8 = new QPushButton(FunctionItemWidget);
    button8->setObjectName(QString::fromUtf8("button8"));

    gridLayout->addWidget(button8, 4, 0, 1, 1);

    button0 = new QPushButton(FunctionItemWidget);
    button0->setObjectName(QString::fromUtf8("button0"));

    gridLayout->addWidget(button0, 4, 2, 1, 1);

    buttonLn = new QPushButton(FunctionItemWidget);
    buttonLn->setObjectName(QString::fromUtf8("buttonLn"));

    gridLayout->addWidget(buttonLn, 6, 2, 1, 1);

    buttonSin = new QPushButton(FunctionItemWidget);
    buttonSin->setObjectName(QString::fromUtf8("buttonSin"));

    gridLayout->addWidget(buttonSin, 7, 3, 1, 1);

    buttonDiv = new QPushButton(FunctionItemWidget);
    buttonDiv->setObjectName(QString::fromUtf8("buttonDiv"));

    gridLayout->addWidget(buttonDiv, 7, 1, 1, 1);

    buttonMul = new QPushButton(FunctionItemWidget);
    buttonMul->setObjectName(QString::fromUtf8("buttonMul"));

    gridLayout->addWidget(buttonMul, 6, 1, 1, 1);

    buttonRightB = new QPushButton(FunctionItemWidget);
    buttonRightB->setObjectName(QString::fromUtf8("buttonRightB"));

    gridLayout->addWidget(buttonRightB, 8, 1, 1, 1);

    buttonPower = new QPushButton(FunctionItemWidget);
    buttonPower->setObjectName(QString::fromUtf8("buttonPower"));

    gridLayout->addWidget(buttonPower, 8, 2, 1, 1);

    buttonLeftB = new QPushButton(FunctionItemWidget);
    buttonLeftB->setObjectName(QString::fromUtf8("buttonLeftB"));

    gridLayout->addWidget(buttonLeftB, 8, 0, 1, 1);

    buttonMin = new QPushButton(FunctionItemWidget);
    buttonMin->setObjectName(QString::fromUtf8("buttonMin"));

    gridLayout->addWidget(buttonMin, 7, 0, 1, 1);

    buttonExp = new QPushButton(FunctionItemWidget);
    buttonExp->setObjectName(QString::fromUtf8("buttonExp"));

    gridLayout->addWidget(buttonExp, 6, 3, 1, 1);

    button7 = new QPushButton(FunctionItemWidget);
    button7->setObjectName(QString::fromUtf8("button7"));

    gridLayout->addWidget(button7, 3, 3, 1, 1);

    buttonItems = new QPushButton(FunctionItemWidget);
    buttonItems->setObjectName(QString::fromUtf8("buttonItems"));

    gridLayout->addWidget(buttonItems, 2, 0, 1, 1);

    button2 = new QPushButton(FunctionItemWidget);
    button2->setObjectName(QString::fromUtf8("button2"));

    gridLayout->addWidget(button2, 2, 2, 1, 1);

    button4 = new QPushButton(FunctionItemWidget);
    button4->setObjectName(QString::fromUtf8("button4"));

    gridLayout->addWidget(button4, 3, 0, 1, 1);

    buttonLog = new QPushButton(FunctionItemWidget);
    buttonLog->setObjectName(QString::fromUtf8("buttonLog"));

    gridLayout->addWidget(buttonLog, 7, 2, 1, 1);

    buttonSign = new QPushButton(FunctionItemWidget);
    buttonSign->setObjectName(QString::fromUtf8("buttonSign"));

    gridLayout->addWidget(buttonSign, 4, 3, 1, 1);

    buttonCos = new QPushButton(FunctionItemWidget);
    buttonCos->setObjectName(QString::fromUtf8("buttonCos"));

    gridLayout->addWidget(buttonCos, 8, 3, 1, 1);

    gridLayout2 = new QGridLayout();
    gridLayout2->setSpacing(6);
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    buttonConfirm = new QPushButton(FunctionItemWidget);
    buttonConfirm->setObjectName(QString::fromUtf8("buttonConfirm"));

    gridLayout2->addWidget(buttonConfirm, 0, 0, 1, 1);

    buttonCancel = new QPushButton(FunctionItemWidget);
    buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));

    gridLayout2->addWidget(buttonCancel, 0, 1, 1, 1);

    gridLayout->addLayout(gridLayout2, 10, 0, 1, 4);

    line1 = new QFrame(FunctionItemWidget);
    line1->setObjectName(QString::fromUtf8("line1"));
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);

    gridLayout->addWidget(line1, 5, 0, 1, 4);

    line1_3 = new QFrame(FunctionItemWidget);
    line1_3->setObjectName(QString::fromUtf8("line1_3"));
    line1_3->setFrameShape(QFrame::HLine);
    line1_3->setFrameShadow(QFrame::Sunken);

    gridLayout->addWidget(line1_3, 9, 0, 1, 4);

    buttonClear = new QPushButton(FunctionItemWidget);
    buttonClear->setObjectName(QString::fromUtf8("buttonClear"));

    gridLayout->addWidget(buttonClear, 1, 3, 1, 1);

    QWidget::setTabOrder(textFunction, radioHex);
    QWidget::setTabOrder(radioHex, radioDec);
    QWidget::setTabOrder(radioDec, radioOct);
    QWidget::setTabOrder(radioOct, radioBin);
    QWidget::setTabOrder(radioBin, buttonClear);
    QWidget::setTabOrder(buttonClear, buttonItems);
    QWidget::setTabOrder(buttonItems, button1);
    QWidget::setTabOrder(button1, button2);
    QWidget::setTabOrder(button2, button3);
    QWidget::setTabOrder(button3, button4);
    QWidget::setTabOrder(button4, button5);
    QWidget::setTabOrder(button5, button6);
    QWidget::setTabOrder(button6, button7);
    QWidget::setTabOrder(button7, button8);
    QWidget::setTabOrder(button8, button9);
    QWidget::setTabOrder(button9, button0);
    QWidget::setTabOrder(button0, buttonSign);
    QWidget::setTabOrder(buttonSign, buttonAdd);
    QWidget::setTabOrder(buttonAdd, buttonMul);
    QWidget::setTabOrder(buttonMul, buttonLn);
    QWidget::setTabOrder(buttonLn, buttonExp);
    QWidget::setTabOrder(buttonExp, buttonMin);
    QWidget::setTabOrder(buttonMin, buttonDiv);
    QWidget::setTabOrder(buttonDiv, buttonLog);
    QWidget::setTabOrder(buttonLog, buttonSin);
    QWidget::setTabOrder(buttonSin, buttonLeftB);
    QWidget::setTabOrder(buttonLeftB, buttonRightB);
    QWidget::setTabOrder(buttonRightB, buttonPower);
    QWidget::setTabOrder(buttonPower, buttonCos);
    QWidget::setTabOrder(buttonCos, buttonConfirm);
    QWidget::setTabOrder(buttonConfirm, buttonCancel);

    retranslateUi(FunctionItemWidget);
    QObject::connect(radioDec, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotRadioDec()));
    QObject::connect(buttonItems, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButtonItems()));
    QObject::connect(button0, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButton0()));
    QObject::connect(button1, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButton1()));
    QObject::connect(button2, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButton2()));
    QObject::connect(button3, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButton3()));
    QObject::connect(button4, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButton4()));
    QObject::connect(button5, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButton5()));
    QObject::connect(button6, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButton6()));
    QObject::connect(button7, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButton7()));
    QObject::connect(button9, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButton9()));
    QObject::connect(buttonSign, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButtonSign()));
    QObject::connect(buttonAdd, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButtonAdd()));
    QObject::connect(buttonMul, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButtonMul()));
    QObject::connect(buttonLn, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButtonLn()));
    QObject::connect(buttonExp, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButtonExp()));
    QObject::connect(buttonMin, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButtonMin()));
    QObject::connect(buttonDiv, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButtonDiv()));
    QObject::connect(buttonLog, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButtonLog()));
    QObject::connect(buttonSin, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButtonSin()));
    QObject::connect(buttonLeftB, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButtonLeftB()));
    QObject::connect(buttonRightB, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButtonRightB()));
    QObject::connect(buttonPower, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButtonPower()));
    QObject::connect(buttonCos, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButtonCos()));
    QObject::connect(button8, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButton8()));
    QObject::connect(buttonClear, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButtonClear()));
    QObject::connect(buttonConfirm, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButtonConfirm()));
    QObject::connect(buttonCancel, SIGNAL(clicked()), FunctionItemWidget, SLOT(slotButtonCancel()));

    QMetaObject::connectSlotsByName(FunctionItemWidget);
  } // setupUi

  void retranslateUi(QDialog *FunctionItemWidget)
  {
    FunctionItemWidget->setWindowTitle(QApplication::translate("FunctionItemWidget", "function editor", 0, QApplication::UnicodeUTF8));
    radioGroup->setTitle(QApplication::translate("FunctionItemWidget", "Bin/Oct/Dec/Hex", 0, QApplication::UnicodeUTF8));
    radioDec->setText(QApplication::translate("FunctionItemWidget", "Decimal", 0, QApplication::UnicodeUTF8));
    radioHex->setText(QApplication::translate("FunctionItemWidget", "Hex", 0, QApplication::UnicodeUTF8));
    radioBin->setText(QApplication::translate("FunctionItemWidget", "Bin", 0, QApplication::UnicodeUTF8));
    radioOct->setText(QApplication::translate("FunctionItemWidget", "Octal", 0, QApplication::UnicodeUTF8));
    buttonAdd->setText(QApplication::translate("FunctionItemWidget", "+", 0, QApplication::UnicodeUTF8));
    button5->setText(QApplication::translate("FunctionItemWidget", "5", 0, QApplication::UnicodeUTF8));
    button9->setText(QApplication::translate("FunctionItemWidget", "9", 0, QApplication::UnicodeUTF8));
    button1->setText(QApplication::translate("FunctionItemWidget", "1", 0, QApplication::UnicodeUTF8));
    button6->setText(QApplication::translate("FunctionItemWidget", "6", 0, QApplication::UnicodeUTF8));
    button3->setText(QApplication::translate("FunctionItemWidget", "3", 0, QApplication::UnicodeUTF8));
    button8->setText(QApplication::translate("FunctionItemWidget", "8", 0, QApplication::UnicodeUTF8));
    button0->setText(QApplication::translate("FunctionItemWidget", "0", 0, QApplication::UnicodeUTF8));
    buttonLn->setText(QApplication::translate("FunctionItemWidget", "ln", 0, QApplication::UnicodeUTF8));
    buttonSin->setText(QApplication::translate("FunctionItemWidget", "sin", 0, QApplication::UnicodeUTF8));
    buttonDiv->setText(QApplication::translate("FunctionItemWidget", "/", 0, QApplication::UnicodeUTF8));
    buttonMul->setText(QApplication::translate("FunctionItemWidget", "*", 0, QApplication::UnicodeUTF8));
    buttonRightB->setText(QApplication::translate("FunctionItemWidget", ")", 0, QApplication::UnicodeUTF8));
    buttonPower->setText(QApplication::translate("FunctionItemWidget", "^", 0, QApplication::UnicodeUTF8));
    buttonLeftB->setText(QApplication::translate("FunctionItemWidget", "(", 0, QApplication::UnicodeUTF8));
    buttonMin->setText(QApplication::translate("FunctionItemWidget", "-", 0, QApplication::UnicodeUTF8));
    buttonExp->setText(QApplication::translate("FunctionItemWidget", "exp", 0, QApplication::UnicodeUTF8));
    button7->setText(QApplication::translate("FunctionItemWidget", "7", 0, QApplication::UnicodeUTF8));
    buttonItems->setText(QApplication::translate("FunctionItemWidget", "Items", 0, QApplication::UnicodeUTF8));
    button2->setText(QApplication::translate("FunctionItemWidget", "2", 0, QApplication::UnicodeUTF8));
    button4->setText(QApplication::translate("FunctionItemWidget", "4", 0, QApplication::UnicodeUTF8));
    buttonLog->setText(QApplication::translate("FunctionItemWidget", "log", 0, QApplication::UnicodeUTF8));
    buttonSign->setText(QApplication::translate("FunctionItemWidget", "+/-", 0, QApplication::UnicodeUTF8));
    buttonCos->setText(QApplication::translate("FunctionItemWidget", "cos", 0, QApplication::UnicodeUTF8));
    buttonConfirm->setText(QApplication::translate("FunctionItemWidget", "Confirm", 0, QApplication::UnicodeUTF8));
    buttonCancel->setText(QApplication::translate("FunctionItemWidget", "Cancel", 0, QApplication::UnicodeUTF8));
    buttonClear->setText(QApplication::translate("FunctionItemWidget", "Clear", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(FunctionItemWidget);
  } // retranslateUi
};

namespace Ui
{
class FunctionItemWidget: public Ui_FunctionItemWidget {};
} // namespace Ui

class FunctionItemWidget : public QDialog, public Ui::FunctionItemWidget
{
  Q_OBJECT

public:
  FunctionItemWidget(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
  ~FunctionItemWidget();

public slots:
  virtual void slotButtonClear();
  virtual void slotRadioDec();
  virtual void slotButton1();
  virtual void slotButtonItems();
  virtual void slotButton2();
  virtual void slotButton3();
  virtual void slotButtonConfirm();
  virtual void slotButton5();
  virtual void slotButton7();
  virtual void slotButton8();
  virtual void slotButton9();
  virtual void slotButton4();
  virtual void slotButton6();
  virtual void slotButtonSign();
  virtual void slotButtonAdd();
  virtual void slotButtonSin();
  virtual void slotButtonLn();
  virtual void slotButtonMin();
  virtual void slotButtonDiv();
  virtual void slotButtonLog();
  virtual void slotButtonMul();
  virtual void slotButtonExp();
  virtual void slotButtonLeftB();
  virtual void slotButtonRightB();
  virtual void slotButtonPower();
  virtual void slotButtonCos();
  virtual void slotButton0();
  virtual void slotButtonCancel();

protected slots:
};

#endif // FUNCTIONITEMWIDGET_H
