/****************************************************************************
 ** Form implementation generated from reading ui file '.\tabledefinition.ui'
 **
 ** Created: Wed Aug 6 22:43:06 2003
 **      by: The User Interface Compiler ($Id: TableDefinition.cpp,v 1.12 2003/08/08 17:04:23 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qradiobutton.h>
#include <qframe.h>
#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

#include "TableDefinition.h"
#include "listviews.h"
#include "report/CKeyFactory.h"
#include "ScanWidget.h"

#include "./icons/scanwidgetbuttonicon.xpm"

/*
 *  Constructs a TableDefinition as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
TableDefinition::TableDefinition(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl),
    pParent(parent)
{
  QPixmap image0((const char**) image0_data);
  QPixmap image1((const char**) image1_data);
  QPixmap image2((const char**) image2_data);
  QPixmap image3((const char**) image3_data);

  if (!name)
    setName("TableDefinition");
  TableDefinitionLayout = new QGridLayout(this, 1, 1, 11, 6, "TableDefinitionLayout");

  bodyField = new QFrame(this, "bodyField");
  bodyField->setFrameShape(QFrame::HLine);
  bodyField->setFrameShadow(QFrame::Sunken);
  bodyField->setFrameShape(QFrame::HLine);

  TableDefinitionLayout->addMultiCellWidget(bodyField, 2, 2, 0, 1);

  layout14 = new QHBoxLayout(0, 0, 6, "layout14");

  confirmButton = new QPushButton(this, "confirmButton");
  layout14->addWidget(confirmButton);

  cancelButton = new QPushButton(this, "cancelButton");
  layout14->addWidget(cancelButton);

  TableDefinitionLayout->addMultiCellLayout(layout14, 3, 3, 0, 1);

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

  TableDefinitionLayout->addMultiCellLayout(layout7, 1, 1, 0, 1);

  frame5 = new QFrame(this, "frame5");
  frame5->setFrameShape(QFrame::Box);
  frame5->setFrameShadow(QFrame::Sunken);
  frame5Layout = new QGridLayout(frame5, 1, 1, 11, 6, "frame5Layout");

  layout5_2 = new QHBoxLayout(0, 0, 6, "layout5_2");

  targetLabel = new QLabel(frame5, "targetLabel");
  layout5_2->addWidget(targetLabel);

  targetEdit = new QLineEdit(frame5, "targetEdit");
  targetEdit->setFrameShape(QLineEdit::LineEditPanel);
  targetEdit->setFrameShadow(QLineEdit::Sunken);
  layout5_2->addWidget(targetEdit);

  frame5Layout->addLayout(layout5_2, 0, 0);

  titleChecked = new QCheckBox(frame5, "titleChecked");

  frame5Layout->addWidget(titleChecked, 1, 0);

  appendChecked = new QCheckBox(frame5, "appendChecked");

  frame5Layout->addWidget(appendChecked, 2, 0);

  TableDefinitionLayout->addWidget(frame5, 0, 0);

  frame4 = new QFrame(this, "frame4");
  frame4->setFrameShape(QFrame::Box);
  frame4->setFrameShadow(QFrame::Sunken);
  frame4->setLineWidth(1);
  frame4Layout = new QGridLayout(frame4, 1, 1, 11, 6, "frame4Layout");

  seperatorLabel = new QLabel(frame4, "seperatorLabel");

  frame4Layout->addWidget(seperatorLabel, 0, 0);

  seperatorEdit = new QLineEdit(frame4, "seperatorEdit");

  frame4Layout->addWidget(seperatorEdit, 0, 1);

  tabChecked = new QCheckBox(frame4, "tabChecked");

  frame4Layout->addWidget(tabChecked, 1, 1);

  TableDefinitionLayout->addWidget(frame4, 0, 1);
  languageChange();
  clearWState(WState_Polished);

  // tab order
  setTabOrder(targetEdit, titleChecked);
  setTabOrder(titleChecked, appendChecked);
  setTabOrder(appendChecked, seperatorEdit);
  setTabOrder(seperatorEdit, tabChecked);
  setTabOrder(tabChecked, addButton);
  setTabOrder(addButton, deleteButton);
  setTabOrder(deleteButton, upButton);
  setTabOrder(upButton, downButton);
  setTabOrder(downButton, itemsTable);
  setTabOrder(itemsTable, confirmButton);
  setTabOrder(confirmButton, cancelButton);

  connect(tabChecked, SIGNAL(clicked()), this, SLOT(tabButtonClicked()));
  connect(titleChecked, SIGNAL(clicked()), this, SLOT(titleButtonClicked()));
  connect(appendChecked, SIGNAL(clicked()), this, SLOT(appendButtonClicked()));
  connect(confirmButton, SIGNAL(clicked()), this, SLOT(slotBtnConfirmClicked()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));
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
  confirmButton->setText(tr("confirm"));
  cancelButton->setText(tr("cancel"));
  itemsLabel->setText(tr("Items"));
  upButton->setText(QString::null);
  downButton->setText(QString::null);
  deleteButton->setText(QString::null);
  addButton->setText(QString::null);
  targetLabel->setText(tr("Target"));
  titleChecked->setText(tr("Title"));
  appendChecked->setText(tr("Append"));
  seperatorLabel->setText(tr("Seperator"));
  tabChecked->setText(tr("Tab"));
}

/*This function is to load the model for the table*/
void TableDefinition::loadTableDefinition()
{}

void TableDefinition::slotBtnCancelClicked()
{
  //check for the connection int i =0;
}

void TableDefinition::slotBtnConfirmClicked()
{
  //check for the connection int i =0;
}

void TableDefinition::tabButtonClicked()
{
  seperatorEdit->setEnabled(!tabChecked->isChecked());
}

void TableDefinition::titleButtonClicked()
{
  //check for the connection int i =0;
}

void TableDefinition::appendButtonClicked()
{
  //check for the connection int i =0;
}
