/****************************************************************************
 **  $ CopasiUI/CompartmentsWidget1.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Compartments Widget1, i.e the Second level 
 ** of Compartments.
 *****************************************************************************/

#ifndef COMPARTMENTS_WIDGET1_H
#define COMPARTMENTS_WIDGET1_H

#include <qsplitter.h>
#include <qvariant.h>

class QVBoxLayout;

class QHBoxLayout;

class QGridLayout;

class QAction;

class QActionGroup;

class QToolBar;

class QPopupMenu;

class QLabel;

class QLineEdit;

class QComboBox;

class QListBox;

class QListBoxItem;

class QPushButton;

class QFrame;

class CModel;

class CompartmentsWidget1 : public QWidget
  {
    Q_OBJECT

  protected:
    QPushButton* cancelChanges;
    QPushButton* commitChanges;
    CModel *mModel;

  public:
    CompartmentsWidget1(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadCompartments(CModel *model);
    void loadName(QString setValue);
    int isName(QString setValue);
    QLineEdit* LineEdit1;
    QLineEdit* LineEdit3;
    QLineEdit* LineEdit4;
    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QLabel* TextLabel3;
    QLabel* TextLabel4;
    //QComboBox* ComboBox1;

    QListBox* ListBox1;
    QFrame* Frame1;
    QFrame* Frame2;
    QFrame* Frame3;
    QFrame* Frame4a;
    QFrame* Frame4b;
    QFrame* Frame4c;
    QFrame* Frame4d;
    QFrame* Frame4;
    QFrame* Frame4_1;
    QFrame* Frame4_2;
    QFrame* Frame4_3;
  };

#endif // CompartmentsWidget
