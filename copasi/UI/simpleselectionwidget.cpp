/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/simpleselectionwidget.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/28 12:42:38 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'simpleselectionwidget.ui'
 **
 ** Created: Thu Oct 28 14:09:04 2004
 **      by: The User Interface Compiler ($Id: simpleselectionwidget.cpp,v 1.4 2004/10/28 12:42:38 gauges Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "simpleselectionwidget.h"

#include <qvariant.h>
#include <vector>
#include <qpushbutton.h>
#include <qsplitter.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlistbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "model/CModel.h"
#include "report/CCopasiObject.h"
#include "simpleselectionwidget.ui.h"

/*
 *  Constructs a SimpleSelectionWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
SimpleSelectionWidget::SimpleSelectionWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("SimpleSelectionWidget");
  SimpleSelectionWidgetLayout = new QHBoxLayout(this, 11, 6, "SimpleSelectionWidgetLayout");

  splitter2 = new QSplitter(this, "splitter2");
  splitter2->setOrientation(QSplitter::Horizontal);

  itemTree = new QListView(splitter2, "itemTree");
  itemTree->addColumn(tr("Column 1"));
  itemTree->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, itemTree->sizePolicy().hasHeightForWidth()));
  itemTree->setSelectionMode(QListView::Extended);

  QWidget* privateLayoutWidget = new QWidget(splitter2, "layout4");
  layout4 = new QHBoxLayout(privateLayoutWidget, 11, 6, "layout4");

  selectedItemsBox = new QListBox(privateLayoutWidget, "selectedItemsBox");
  selectedItemsBox->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 3, 0, selectedItemsBox->sizePolicy().hasHeightForWidth()));
  selectedItemsBox->setSelectionMode(QListBox::Extended);
  layout4->addWidget(selectedItemsBox);

  layout3 = new QVBoxLayout(0, 0, 6, "layout3");
  spacer4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
  layout3->addItem(spacer4);

  addButton = new QPushButton(privateLayoutWidget, "addButton");
  addButton->setEnabled(FALSE);
  layout3->addWidget(addButton);

  deleteButton = new QPushButton(privateLayoutWidget, "deleteButton");
  deleteButton->setEnabled(FALSE);
  layout3->addWidget(deleteButton);
  spacer5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
  layout3->addItem(spacer5);

  moveUpButton = new QPushButton(privateLayoutWidget, "moveUpButton");
  moveUpButton->setEnabled(FALSE);
  layout3->addWidget(moveUpButton);

  moveDownButton = new QPushButton(privateLayoutWidget, "moveDownButton");
  moveDownButton->setEnabled(FALSE);
  layout3->addWidget(moveDownButton);
  spacer6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
  layout3->addItem(spacer6);
  layout4->addLayout(layout3);
  SimpleSelectionWidgetLayout->addWidget(splitter2);
  languageChange();
  resize(QSize(615, 371).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(moveUpButton, SIGNAL(clicked()), this, SLOT(moveUpButton_clicked()));
  connect(moveDownButton, SIGNAL(clicked()), this, SLOT(moveDownButton_clicked()));

  // tab order
  setTabOrder(itemTree, selectedItemsBox);
  setTabOrder(selectedItemsBox, addButton);
  setTabOrder(addButton, deleteButton);
  setTabOrder(deleteButton, moveUpButton);
  setTabOrder(moveUpButton, moveDownButton);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
SimpleSelectionWidget::~SimpleSelectionWidget()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void SimpleSelectionWidget::languageChange()
{
  setCaption(tr("Form1"));
  itemTree->header()->setLabel(0, tr("Column 1"));
  addButton->setText(tr("Add"));
  deleteButton->setText(tr("Delete"));
  moveUpButton->setText(tr("Move Up"));
  moveDownButton->setText(tr("Move Down"));
}
