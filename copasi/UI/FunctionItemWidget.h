/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/FunctionItemWidget.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:47 $
   End CVS Header */

/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description: 
Date: 09/29
Comment : FunctionItemWidget for editing of the optimization function
Contact: Please contact lixu1@vt.edu.
 *********************************************************/

#ifndef FUNCTIONITEMWIDGET_H
#define FUNCTIONITEMWIDGET_H

#include <qvariant.h>
#include <qdialog.h>
#include <string>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QTextEdit;
class QButtonGroup;
class QRadioButton;
class QPushButton;
class QFrame;
class CCopasiObject;

class FunctionItemWidget : public QDialog
  {
    Q_OBJECT

  public:
    FunctionItemWidget(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
    ~FunctionItemWidget();

    QTextEdit* textFunction;
    QButtonGroup* radioGroup;
    QRadioButton* radioDec;
    QRadioButton* radioHex;
    QRadioButton* radioBin;
    QRadioButton* radioOct;
    QPushButton* buttonAdd;
    QPushButton* button5;
    QPushButton* button9;
    QPushButton* button1;
    QPushButton* button6;
    QPushButton* button3;
    QPushButton* button8;
    QPushButton* button0;
    QPushButton* buttonLn;
    QPushButton* buttonSin;
    QPushButton* buttonDiv;
    QPushButton* buttonMul;
    QPushButton* buttonRightB;
    QPushButton* buttonPower;
    QPushButton* buttonLeftB;
    QPushButton* buttonMin;
    QPushButton* buttonExp;
    QPushButton* button7;
    QPushButton* buttonItems;
    QPushButton* button2;
    QPushButton* button4;
    QPushButton* buttonLog;
    QPushButton* buttonSign;
    QPushButton* buttonCos;
    QPushButton* buttonConfirm;
    QPushButton* buttonCancel;
    QFrame* line1;
    QFrame* line1_3;
    QPushButton* buttonClear;

    /*
     external interface to initialize the output str point
    */
    void setStrFunction(std::string * targetFunctionPtr);

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

  protected:
    QGridLayout* FunctionItemWidgetLayout;
    QGridLayout* radioGroupLayout;
    QGridLayout* layout1;
    std::string* strFunction;
    /*
     wrapper a object to object cn
    */
    void objectLinkWrapper(CCopasiObject * pObject);

  protected slots:
    virtual void languageChange();
  };

#endif // FUNCTIONITEMWIDGET_H
