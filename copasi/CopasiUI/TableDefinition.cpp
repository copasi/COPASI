/*******************************************************************
 **  $ CopasiUI/TableDefinition.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the Table Definition
 ********************************************************************/
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtoolbar.h>
#include <qwidget.h>
#include <qframe.h>
#include <qlistbox.h>
#include "copasi.h"
#include "utilities/CCopasiVector.h"
#include "TableDefinition.h"
#include "model/CModel.h"
#include "utilities/CMethodParameter.h"
#include "listviews.h"
#include "./icons/scanwidgetbuttonicon.xpm" 
/*
 *  Constructs a TableDefinition which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
TableDefinition::TableDefinition(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl)
{
  if (!name)
    setName("TableDefinition");

  QPixmap image0((const char**) image0_data);
  QPixmap image1((const char**) image1_data);
  QPixmap image2((const char**) image2_data);
  QPixmap image3((const char**) image3_data);
  setCaption(trUtf8("TableDefinition"));
  TableDefinitionLayout = new QGridLayout(this, 1, 1, 11, 6, "TableDefinitionLayout");

  LineEdit1 = new QLineEdit(this, "LineEdit1");

  TableDefinitionLayout->addWidget(LineEdit1, 0, 1);

  TextLabel2 = new QLabel(this, "TextLabel2");
  TextLabel2->setText(trUtf8("Title"));

  TableDefinitionLayout->addWidget(TextLabel2, 2, 0);

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setText(trUtf8("Seperator"));

  TableDefinitionLayout->addWidget(TextLabel1, 0, 0);

  ListBox1 = new QListBox(this, "ListBox1");

  TableDefinitionLayout->addMultiCellWidget(ListBox1, 5, 6, 1, 1);
  QSpacerItem* spacer = new QSpacerItem(131, 270, QSizePolicy::Minimum, QSizePolicy::Expanding);
  TableDefinitionLayout->addItem(spacer, 6, 0);

  Layout7 = new QVBoxLayout(0, 0, 6, "Layout7");
  TextLabel3 = new QLabel(this, "TextLabel3");
  TextLabel3->setText(trUtf8("Items"));
  Layout7->addWidget(TextLabel3);

  Layout6 = new QGridLayout(0, 1, 1, 0, 6, "Layout6");

  deleteButton = new QPushButton(this, "deleteButton");
  deleteButton->setText(trUtf8(""));
  deleteButton->setPixmap(image0);

  Layout6->addWidget(deleteButton, 0, 1);

  downButton = new QPushButton(this, "downButton");
  downButton->setText(trUtf8(""));
  downButton->setPixmap(image1);

  Layout6->addWidget(downButton, 1, 1);

  addButton = new QPushButton(this, "addButton");
  addButton->setText(trUtf8(""));
  addButton->setPixmap(image2);

  Layout6->addWidget(addButton, 0, 0);

  upButton = new QPushButton(this, "upButton");
  upButton->setText(trUtf8(""));
  upButton->setPixmap(image3);

  Layout6->addWidget(upButton, 1, 0);
  Layout7->addLayout(Layout6);
  TableDefinitionLayout->addLayout(Layout7, 5, 0);

  //TableDefinitionLayout->addWidget(TextLabel3, 5, 0);
  LineEdit3 = new QLineEdit(this, "LineEdit3");
  LineEdit3->setFrameShape(QLineEdit::LineEditPanel);
  LineEdit3->setFrameShadow(QLineEdit::Sunken);

  TableDefinitionLayout->addWidget(LineEdit3, 2, 1);

  Layout5 = new QHBoxLayout(0, 0, 6, "Layout5");

  commitChanges = new QPushButton(this, "commitChanges");
  commitChanges->setText(trUtf8("Commit"));
  Layout5->addWidget(commitChanges);

  cancelChanges = new QPushButton(this, "cancelChanges");
  cancelChanges->setText(trUtf8("Cancel"));
  Layout5->addWidget(cancelChanges);

  TableDefinitionLayout->addMultiCellLayout(Layout5, 8, 8, 0, 1);

  Line4_3 = new QFrame(this, "Line4_3");
  Line4_3->setFrameShape(QFrame::HLine);
  Line4_3->setFrameShadow(QFrame::Sunken);
  Line4_3->setFrameShape(QFrame::HLine);

  TableDefinitionLayout->addMultiCellWidget(Line4_3, 7, 7, 0, 1);

  // signals and slots connections
  connect(commitChanges, SIGNAL(clicked()), this, SLOT(slotBtnOKClicked()));
  connect(cancelChanges, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
TableDefinition::~TableDefinition()
{
  // no need to delete child widgets, Qt does it all for us
}

/*This function is to load the model for the table*/
void TableDefinition::loadTableDefinition()
{}

void TableDefinition::slotBtnCancelClicked()
{}

void TableDefinition::slotBtnOKClicked()
{}
