/****************************************************************************
 ** Form interface generated from reading ui file '.\tabledefinition.ui'
 **
 ** Created: Wed Aug 6 22:43:06 2003
 **      by: The User Interface Compiler ($Id: TableDefinition.h,v 1.7 2003/08/08 15:32:03 lixu1 Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef TABLEDEFINITION_H
#define TABLEDEFINITION_H

#include "copasi.h"
#include <qvariant.h>
#include <qwidget.h>
#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QCheckBox;
class QLineEdit;
class QFrame;
class QPushButton;
//class QTable;
class QRadioButton;
class ScanScrollView;
class CModel;

class TableDefinition : public CopasiWidget
  {
    Q_OBJECT

  public:
    TableDefinition(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~TableDefinition();
    CModel *mModel;
    ScanScrollView* itemsTable;
    void loadTableDefinition();

    QFrame* bodyField;
    QPushButton* confirmButton;
    QPushButton* cancelButton;
    QLabel* itemsLabel;
    QPushButton* upButton;
    QPushButton* downButton;
    QPushButton* deleteButton;
    QPushButton* addButton;
    QFrame* frame5;
    QLabel* targetLabel;
    QLineEdit* targetEdit;
    QCheckBox* titleChecked;
    QCheckBox* appendChecked;
    QFrame* frame4;
    QLabel* seperatorLabel;
    QLineEdit* seperatorEdit;
    QCheckBox* tabChecked;

  protected:
    QGridLayout* TableDefinitionLayout;
    QHBoxLayout* layout14;
    QHBoxLayout* layout7;
    QVBoxLayout* layout6;
    QGridLayout* layout5;
    QGridLayout* frame5Layout;
    QHBoxLayout* layout5_2;
    QGridLayout* frame4Layout;

    QWidget* pParent;
    std::vector<QWidget*> selectedList;

  protected slots:
    virtual void radioButtonClicked();

    virtual void languageChange();
    virtual void slotBtnCancelClicked();
    virtual void slotBtnOKClicked();
  };

#endif // TABLEDEFINITION_H
