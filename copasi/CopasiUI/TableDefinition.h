/****************************************************************************
 **  $ CopasiUI/TableDefinition.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the TableDefinition 
 *****************************************************************************/

#ifndef TABLEDEFINITION_H
#define TABLEDEFINITION_H

#include <qvariant.h>
#include <qwidget.h>
#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QLabel;
class QLineEdit;
class QListBox;
class QListBoxItem;
class QPushButton;
class CModel;

class TableDefinition : public CopasiWidget
  {
    Q_OBJECT

  public:
    TableDefinition (QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~TableDefinition ();
    CModel *mModel;
    void loadTableDefinition();

    QLineEdit* LineEdit4;
    QLineEdit* LineEdit1;
    QLabel* TextLabel2;
    QLabel* TextLabel2_2;
    QLabel* TextLabel1;
    QFrame* Line4;
    QFrame* Line4_2;
    QListBox* ListBox1;
    QLabel* TextLabel3;
    QLineEdit* LineEdit3;
    QPushButton* commitChanges;
    QPushButton* cancelChanges;
    QFrame* Line4_3;

  public slots:
    virtual void slotBtnCancelClicked();
    virtual void slotBtnOKClicked();

  protected:
    QGridLayout* TableDefinitionLayout;
    QHBoxLayout* Layout5;
  };

#endif // TableDefinition.h
