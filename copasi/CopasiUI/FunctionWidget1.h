/****************************************************************************
 **  $ CopasiUI/FunctionWidget1.h               
 **  $ Author  : Mrinmayee Kulkarni
 **  
 ** This is the header file for Function Widget1, i.e the Second  level 
 ** widget which shows detailed description of an individual function
 *****************************************************************************/ 
/*
 reimplement UI to automatically change internal components size
 Author: Liang Xu
 */
#ifndef FUNCTION_WIDGET1_H
#define FUNCTION_WIDGET1_H
#include <qtextbrowser.h>
#include <qsplitter.h>
#include <qvariant.h>
#include <qtable.h>
#include "MyTable.h"
#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QButtonGroup;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;
class QTable;

class FunctionWidget1 : public CopasiWidget
  {
    Q_OBJECT

  public:
    FunctionWidget1(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadName(QString setValue);
    int isName(QString setValue);

    QString mName;

    QString *Function_Name;
    QString *new_Name;
    QString *new_Description;
    QString param_Type;
    QString param_Name;
    QString param_Usage;
    QString app_Desc;
    QString app_Low;
    QString app_High;
    int int_Low;
    int int_High;

    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QTextBrowser* textBrowser;
    QFrame* Line2;
    QPushButton* commitChanges;
    QPushButton* cancelChanges;
    QButtonGroup* ButtonGroup1;
    QRadioButton* RadioButton1;
    QRadioButton* RadioButton2;
    QRadioButton* RadioButton3;
    QLabel* TextLabel4;
    QFrame* Line3;
    QLineEdit* LineEdit1;
    QTable* Table2;
    QLabel* TextLabel5;
    QFrame* Line4;
    QTable* Table1;
    QLabel* TextLabel3;
    QFrame* Line1;

  protected slots:
    virtual void slotCancelButtonClicked();
    virtual void slotCommitButtonClicked();
    virtual void slotTableValueChanged(int row, int col);

  signals:
    void signalCancelButtonClicked(const QString &);
    void informUpdated();
    void update();

  protected:
    QGridLayout* FunctionWidget1Layout;
    QHBoxLayout* Layout1;
    QHBoxLayout* Layout2;
  };

#endif // FunctionWidget1
