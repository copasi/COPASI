/****************************************************************************
 ** Form implementation generated from reading ui file '.\tabledefinition.ui'
 **
 ** Created: Wed Aug 6 22:43:06 2003
 **      by: The User Interface Compiler ($Id: TableDefinition.cpp,v 1.5 2003/08/07 03:12:05 lixu1 Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qframe.h>
#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

#include "TableDefinition.h"
#include "listviews.h"
#include "report/CKeyFactory.h"

/*
 *  Constructs a TableDefinition as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
TableDefinition::TableDefinition(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl),
    pParent(parent)
{
  if (!name)
    setName("TableDefinition");
  TableDefinitionLayout = new QGridLayout(this, 1, 1, 11, 6, "TableDefinitionLayout");

  targetLabel = new QLabel(this, "targetLabel");

  TableDefinitionLayout->addWidget(targetLabel, 0, 0);

  appendChecked = new QCheckBox(this, "appendChecked");

  TableDefinitionLayout->addWidget(appendChecked, 0, 2);

  targetEdit = new QLineEdit(this, "targetEdit");

  TableDefinitionLayout->addWidget(targetEdit, 0, 1);

  targetField = new QFrame(this, "targetField");
  targetField->setFrameShape(QFrame::HLine);
  targetField->setFrameShadow(QFrame::Sunken);
  targetField->setFrameShape(QFrame::HLine);

  TableDefinitionLayout->addMultiCellWidget(targetField, 1, 1, 0, 2);

  titleLabel = new QLabel(this, "titleLabel");

  TableDefinitionLayout->addWidget(titleLabel, 2, 0);

  seperatorLabel = new QLabel(this, "seperatorLabel");

  TableDefinitionLayout->addWidget(seperatorLabel, 3, 0);

  titleEdit = new QLineEdit(this, "titleEdit");

  TableDefinitionLayout->addMultiCellWidget(titleEdit, 2, 2, 1, 2);

  seperatorEdit = new QLineEdit(this, "seperatorEdit");

  TableDefinitionLayout->addMultiCellWidget(seperatorEdit, 3, 3, 1, 2);

  titleField = new QFrame(this, "titleField");
  titleField->setFrameShape(QFrame::HLine);
  titleField->setFrameShadow(QFrame::Sunken);
  titleField->setFrameShape(QFrame::HLine);

  TableDefinitionLayout->addMultiCellWidget(titleField, 4, 4, 0, 2);

  layout7 = new QHBoxLayout(0, 0, 6, "layout7");

  layout6 = new QVBoxLayout(0, 0, 6, "layout6");

  itemsLabel = new QLabel(this, "itemsLabel");
  layout6->addWidget(itemsLabel);

  layout5 = new QGridLayout(0, 1, 1, 0, 6, "layout5");

  upButton = new QPushButton(this, "upButton");

  layout5->addWidget(upButton, 1, 0);

  downButton = new QPushButton(this, "downButton");

  layout5->addWidget(downButton, 1, 1);

  deleteButton = new QPushButton(this, "deleteButton");

  layout5->addWidget(deleteButton, 0, 1);

  addButton = new QPushButton(this, "addButton");

  layout5->addWidget(addButton, 0, 0);
  layout6->addLayout(layout5);
  QSpacerItem* spacer = new QSpacerItem(90, 262, QSizePolicy::Minimum, QSizePolicy::Expanding);
  layout6->addItem(spacer);
  layout7->addLayout(layout6);

  itemsTable = new QTable(this, "itemsTable");
  itemsTable->setNumRows(0);
  itemsTable->setNumCols(0);
  layout7->addWidget(itemsTable);

  TableDefinitionLayout->addMultiCellLayout(layout7, 5, 5, 0, 2);
  languageChange();

  // tab order
  setTabOrder(targetEdit, appendChecked);
  setTabOrder(appendChecked, titleEdit);
  setTabOrder(titleEdit, seperatorEdit);
  setTabOrder(seperatorEdit, addButton);
  setTabOrder(addButton, upButton);
  setTabOrder(upButton, deleteButton);
  setTabOrder(deleteButton, downButton);
  setTabOrder(downButton, itemsTable);
}

/*
 *  Destroys the object and frees any allocated resources
 */
TableDefinition::~TableDefinition()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void TableDefinition::languageChange()
{
  setCaption(tr("Reports"));
  targetLabel->setText(tr("Target"));
  appendChecked->setText(tr("Append"));
  titleLabel->setText(tr("Title"));
  seperatorLabel->setText(tr("Seperator"));
  itemsLabel->setText(tr("Items"));
  upButton->setText(QString::null);
  downButton->setText(QString::null);
  deleteButton->setText(QString::null);
  addButton->setText(QString::null);
}
