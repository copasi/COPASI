/****************************************************************************
 ** Form implementation generated from reading ui file '.\tabledefinition.ui'
 **
 ** Created: Wed Aug 6 22:43:06 2003
 **      by: The User Interface Compiler ($Id: TableDefinition.cpp,v 1.6 2003/08/07 03:41:18 lixu1 Exp $)
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
#include "scanwidget.h"

#include "./icons/scanwidgetbuttonicon.xpm"

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

  QPixmap image0((const char**) image0_data);
  QPixmap image1((const char**) image1_data);
  QPixmap image2((const char**) image2_data);
  QPixmap image3((const char**) image3_data);

  TableDefinitionLayout = new QGridLayout(this, 1, 1, 11, 6, "TableDefinitionLayout");

  targetLabel = new QLabel(this, "targetLabel");

  TableDefinitionLayout->addWidget(targetLabel, 0, 0);

  appendChecked = new QCheckBox(this, "appendChecked");

  TableDefinitionLayout->addWidget(appendChecked, 0, 2);

  targetEdit = new QLineEdit(this, "targetEdit");
  targetEdit->setFrameShape(QLineEdit::LineEditPanel);
  targetEdit->setFrameShadow(QLineEdit::Sunken);

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
  upButton->setText(trUtf8(""));
  upButton->setPixmap(image3);
  layout5->addWidget(upButton, 1, 0);

  deleteButton = new QPushButton(this, "deleteButton");
  deleteButton->setText(trUtf8(""));
  deleteButton->setPixmap(image0);
  layout5->addWidget(deleteButton, 0, 1);

  downButton = new QPushButton(this, "downButton");
  downButton->setText(trUtf8(""));
  downButton->setPixmap(image1);
  layout5->addWidget(downButton, 1, 1);

  addButton = new QPushButton(this, "addButton");
  addButton->setText(trUtf8(""));
  addButton->setPixmap(image2);
  layout5->addWidget(addButton, 0, 0);

  layout6->addLayout(layout5);
  QSpacerItem* spacer = new QSpacerItem(90, 262, QSizePolicy::Minimum, QSizePolicy::Expanding);
  layout6->addItem(spacer);
  layout7->addLayout(layout6);

  itemsTable = new ScanScrollView(this, 0, 0);
  //  ScanItemWidget* parameterTable = new ScanItemWidget(this, "parameterTable");
  //  scrollview->setMinimumWidth(parameterTable->minimumSizeHint().width());
  //  pdelete(parameterTable);
  itemsTable->setVScrollBarMode(QScrollView::Auto);
  itemsTable->setHScrollBarMode(QScrollView::AlwaysOff); //Disable Horizonal Scroll
  itemsTable->setSelectedList(&selectedList);
  selectedList.clear();

  //    itemsTable = new QTable(this, "itemsTable");
  //    itemsTable->setNumRows(0);
  //    itemsTable->setNumCols(0);
  layout7->addWidget(itemsTable);

  TableDefinitionLayout->addMultiCellLayout(layout7, 5, 5, 0, 2);

  bodyField = new QFrame(this, "bodyField");
  bodyField->setFrameShape(QFrame::HLine);
  bodyField->setFrameShadow(QFrame::Sunken);
  bodyField->setFrameShape(QFrame::HLine);

  TableDefinitionLayout->addMultiCellWidget(bodyField, 6, 6, 0, 2);

  layout14 = new QHBoxLayout(0, 0, 6, "layout14");

  confirmButton = new QPushButton(this, "confirmButton");
  layout14->addWidget(confirmButton);

  cancelButton = new QPushButton(this, "cancelButton");
  layout14->addWidget(cancelButton);

  TableDefinitionLayout->addMultiCellLayout(layout14, 7, 7, 0, 2);
  languageChange();
  clearWState(WState_Polished);

  // tab order
  setTabOrder(targetEdit, appendChecked);
  setTabOrder(appendChecked, titleEdit);
  setTabOrder(titleEdit, seperatorEdit);
  setTabOrder(seperatorEdit, addButton);
  setTabOrder(addButton, deleteButton);
  setTabOrder(deleteButton, upButton);
  setTabOrder(upButton, downButton);
  setTabOrder(downButton, itemsTable);
  setTabOrder(itemsTable, confirmButton);
  setTabOrder(confirmButton, cancelButton);
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
  confirmButton->setText(tr("confirm"));
  cancelButton->setText(tr("cancel"));
}
