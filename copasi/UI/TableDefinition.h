/****************************************************************************
 ** Form interface generated from reading ui file '.\tabledefinition.ui'
 **
 ** Created: Wed Aug 6 22:43:06 2003
 **      by: The User Interface Compiler ($Id: TableDefinition.h,v 1.3 2003/08/07 03:12:05 lixu1 Exp $)
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
class QTable;

class TableDefinition : public CopasiWidget
  {
    Q_OBJECT

  public:
    TableDefinition(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~TableDefinition();

    QLabel* targetLabel;
    QCheckBox* appendChecked;
    QLineEdit* targetEdit;
    QFrame* targetField;
    QLabel* titleLabel;
    QLabel* seperatorLabel;
    QLineEdit* titleEdit;
    QLineEdit* seperatorEdit;
    QFrame* titleField;
    QLabel* itemsLabel;
    QPushButton* upButton;
    QPushButton* downButton;
    QPushButton* deleteButton;
    QPushButton* addButton;
    QTable* itemsTable;

  protected:
    QGridLayout* TableDefinitionLayout;
    QHBoxLayout* layout7;
    QVBoxLayout* layout6;
    QGridLayout* layout5;
    QWidget* pParent;

  protected slots:
    virtual void languageChange();
  };

#endif // TABLEDEFINITION_H
