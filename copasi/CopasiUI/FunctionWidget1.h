/****************************************************************************
 **  $ CopasiUI/FunctionWidget1.h               
 **  $ Author  : Mrinmayee Kulkarni
 **  
 ** This is the header file for Function Widget1, i.e the Second  level 
 ** widget which shows detailed description of an individual function
 *****************************************************************************/
#ifndef FUNCTION_WIDGET1_H
#define FUNCTION_WIDGET1_H

#include <qsplitter.h>
#include <qvariant.h>
#include <qtable.h>
#include "MyTable.h"

class QVBoxLayout;

class QHBoxLayout;

class QGridLayout;

class QAction;

class QActionGroup;

class QToolBar;

class QPopupMenu;

class QButtonGroup;

class QLabel;

class QLineEdit;

class QComboBox;

class QListBoxItem;

class QPushButton;

class QRadioButton;

class QFrame;

class CModel;

class FunctionWidget1 : public QWidget
  {
    Q_OBJECT

  protected:
    QPushButton* cancelChanges;
    QPushButton* commitChanges;
    CModel *mModel;
    QTable *Table1;
    QTable *Table2;

  public:
    FunctionWidget1(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadFunction(CModel *model);
    void loadName(QString setValue);
    int isName(QString setValue);

    QString *Function_Name;
    QButtonGroup* ButtonGroup1;
    QButtonGroup* ButtonGroup2;
    QButtonGroup* ButtonGroup3;

    QRadioButton* RadioButton1;
    QRadioButton* RadioButton2;
    QRadioButton* RadioButton3;
    QRadioButton* RadioButton4;
    QRadioButton* RadioButton5;

    QLineEdit* LineEdit1;
    QLineEdit* LineEdit2;
    QLineEdit* LineEdit4;
    QLineEdit* LineEdit5;
    QLineEdit* LineEdit7;
    QLineEdit* LineEdit8;
    QLineEdit* LineEdit9;

    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QLabel* TextLabel3;
    QLabel* TextLabel4;
    QLabel* TextLabel7;
    QLabel* TextLabel8;
    QLabel* TextLabel9;

    QFrame* Frame1;
    QFrame* Frame2;
    QFrame* Frame3;
    QFrame* Frame4;
    QFrame* Frame5;
    QFrame* Frame6;
    QFrame* Frame7;
    QFrame* Frame0;

  protected slots:
    virtual void slotCancelButtonClicked();
    virtual void slotCommitButtonClicked();

  signals:
    void signalCancelButtonClicked(QString &);
  };

#endif // FunctionWidget1
