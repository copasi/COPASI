/****************************************************************************
 ** Form interface generated from reading ui file '.\FunctionItemWidget.ui'
 **
 ** Created: Mon Sep 29 00:08:09 2003
 **      by: The User Interface Compiler ($Id: FunctionItemWidget.h,v 1.1 2003/09/29 04:12:31 lixu1 Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef FUNCTIONITEMWIDGET_H
#define FUNCTIONITEMWIDGET_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QTextEdit;
class QPushButton;
class QFrame;
class QButtonGroup;
class QRadioButton;

class FunctionItemWidget : public QDialog
  {
    Q_OBJECT

  public:
    FunctionItemWidget(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
    ~FunctionItemWidget();

    QTextEdit* textFunction;
    QPushButton* button7;
    QPushButton* button0;
    QPushButton* button1;
    QPushButton* button6;
    QPushButton* button3;
    QPushButton* button8;
    QPushButton* button2;
    QPushButton* buttonItems;
    QPushButton* button4;
    QPushButton* buttonSign;
    QPushButton* button5;
    QPushButton* button9;
    QPushButton* buttonRightB;
    QPushButton* buttonDiv;
    QPushButton* buttonCos;
    QPushButton* buttonAdd;
    QPushButton* buttonLog;
    QPushButton* buttonLeftB;
    QPushButton* buttonMul;
    QPushButton* buttonExp;
    QPushButton* buttonMin;
    QPushButton* buttonLn;
    QPushButton* buttonSin;
    QPushButton* buttonPower;
    QFrame* line1;
    QButtonGroup* radioGroup;
    QRadioButton* radioDec;
    QRadioButton* radioHex;
    QRadioButton* radioBin;
    QRadioButton* radioOct;
    QPushButton* buttonClear;
    QFrame* line1_2;

  public slots:
    virtual void slotButtonClear();
    virtual void slotRadioDec();
    virtual void slotButton1();
    virtual void slotButtonItems();
    virtual void slotButton2();
    virtual void slotButton3();
    virtual void slotButton0();
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

  protected:
    QGridLayout* FunctionItemWidgetLayout;
    QGridLayout* radioGroupLayout;

  protected slots:
    virtual void languageChange();
  };

#endif // FUNCTIONITEMWIDGET_H
