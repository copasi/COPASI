/****************************************************************************
 ** Form interface generated from reading ui file '.\function.ui'
 **
 ** Created: Wed May 29 16:39:16 2002
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
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

class QGroupBox;

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

    QGroupBox* GroupBox1;
    QGroupBox* GroupBox2;
    QGroupBox* GroupBox3
    ;
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

    QComboBox* ComboBox1;

    QFrame* Frame1;
    QFrame* Frame2;
    QFrame* Frame3;
    QFrame* Frame4;
    QFrame* Frame5;
    QFrame* Frame6;
    QFrame* Frame7;
  };

#endif // FunctionWidget

/*#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QRadioButton;
class QTable;
 
class Form1 : public QWidget
{ 
    Q_OBJECT
 
public:
    Form1(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~Form1();
 
    QLineEdit* LineEdit1;
    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QLineEdit* LineEdit2;
    QTable* Table1;
    QTable* Table2;
    QLabel* TextLabel3;
    QLabel* TextLabel4;
    QRadioButton* RadioButton1;
    QRadioButton* RadioButton2;
    QRadioButton* RadioButton3;
 
 
};
 
#endif // FORM1_H
 */
