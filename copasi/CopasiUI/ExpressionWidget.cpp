/****************************************************************************
 ** Form implementation generated from reading ui file '.\ExpressionWidget.ui'
 **
 ** Created: Fri Sep 19 15:37:59 2003
 **      by: The User Interface Compiler ($Id: ExpressionWidget.cpp,v 1.7 2003/09/19 20:53:48 lixu1 Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include <qvariant.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qlabel.h> 
//#include <qtable.h>
#include <qlistbox.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

#include "ExpressionWidget.h"
#include "copasi.h"
#include "listviews.h"
#include "ObjectBrowser.h"
#include "utilities/CGlobals.h"
#include "utilities/CMethodParameter.h"
#include "function/CFunction.h"
#include "function/CFunctionDB.h"
#include "function/CKinFunction.h"
#include "report/CKeyFactory.h"
#include "./icons/scanwidgetbuttonicon.xpm"

/*
 *  Constructs a ExpressionWidget as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
ExpressionWidget::ExpressionWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl),
    bUpdated(false)
{
  QPixmap image0((const char**) image0_data);
  QPixmap image1((const char**) image1_data);
  QPixmap image2((const char**) image2_data);
  QPixmap image3((const char**) image3_data);

  if (!name)
    setName("ExpressionWidget");
  ExpressionWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "ExpressionWidgetLayout");

  bodyField = new QFrame(this, "bodyField");
  bodyField->setFrameShape(QFrame::HLine);
  bodyField->setFrameShadow(QFrame::Sunken);
  bodyField->setFrameShape(QFrame::HLine);

  ExpressionWidgetLayout->addMultiCellWidget(bodyField, 2, 2, 0, 1);

  layout14 = new QHBoxLayout(0, 0, 6, "layout14");

  confirmButton = new QPushButton(this, "confirmButton");
  layout14->addWidget(confirmButton);

  cancelButton = new QPushButton(this, "cancelButton");
  layout14->addWidget(cancelButton);

  ExpressionWidgetLayout->addMultiCellLayout(layout14, 3, 3, 0, 1);

  layout6 = new QVBoxLayout(0, 0, 6, "layout6");

  itemsLabel = new QLabel(this, "itemsLabel");
  layout6->addWidget(itemsLabel);

  layout5 = new QGridLayout(0, 1, 1, 0, 6, "layout5");

  //manually change to add icon for alignment need
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

  layout5->addWidget(addButton, 0, 0);
  layout6->addLayout(layout5);
  QSpacerItem* spacer = new QSpacerItem(90, 262, QSizePolicy::Minimum, QSizePolicy::Expanding);
  layout6->addItem(spacer);

  ExpressionWidgetLayout->addLayout(layout6, 1, 0);

  //  itemsTable = new QTable(this, "itemsTable");
  //  itemsTable->setNumRows(0);
  //  itemsTable->setNumCols(0);
  itemsTable = new QListBox(this, "itemsTable");

  ExpressionWidgetLayout->addWidget(itemsTable, 1, 1);

  frame5 = new QFrame(this, "frame5");
  frame5->setFrameShape(QFrame::Box);
  frame5->setFrameShadow(QFrame::Sunken);
  frame5Layout = new QGridLayout(frame5, 1, 1, 11, 6, "frame5Layout");

  expressionName = new QLineEdit(frame5, "expressionName");
  expressionName->setFrameShape(QLineEdit::LineEditPanel);
  expressionName->setFrameShadow(QLineEdit::Sunken);

  frame5Layout->addWidget(expressionName, 0, 1);

  expressionNameLabel = new QLabel(frame5, "expressionNameLabel");

  frame5Layout->addWidget(expressionNameLabel, 0, 0);

  textEdit2 = new QTextEdit(frame5, "textEdit2");

  frame5Layout->addMultiCellWidget(textEdit2, 1, 2, 1, 1);

  expressionEditlabel = new QLabel(frame5, "expressionEditlabel");

  frame5Layout->addWidget(expressionEditlabel, 1, 0);
  QSpacerItem* spacer_2 = new QSpacerItem(60, 31, QSizePolicy::Minimum, QSizePolicy::Expanding);
  frame5Layout->addItem(spacer_2, 2, 0);

  ExpressionWidgetLayout->addMultiCellWidget(frame5, 0, 0, 0, 1);
  languageChange();
  clearWState(WState_Polished);
}

/*
 *  Destroys the object and frees any allocated resources
 */
ExpressionWidget::~ExpressionWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ExpressionWidget::languageChange()
{
  setCaption(tr("Expression"));
  confirmButton->setText(tr("confirm"));
  cancelButton->setText(tr("cancel"));
  itemsLabel->setText(tr("Items"));
  upButton->setText(QString::null);
  downButton->setText(QString::null);
  deleteButton->setText(QString::null);
  addButton->setText(QString::null);
  expressionNameLabel->setText(tr("Expresion Name"));
  expressionEditlabel->setText(tr("Expression"));
}

bool ExpressionWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  switch (objectType)
    {
    case ListViews::MODEL:
      break;

    default:
      break;
    }
  return true;
}

bool ExpressionWidget::leave()
{
  //let the user confirm?
  return true;
}

bool ExpressionWidget::enter(const std::string & key)
{
  objKey = key;
  CFunction* func = (CFunction*)(CCopasiContainer*)CKeyFactory::get(key);
  //TODO: check if it really is a compartment

  if (func)
    return loadFromExpression(func);
  else
    return false;
}

bool ExpressionWidget::loadFromExpression(CFunction*)
{
  return true;
}

void ExpressionWidget::addButtonClicked()
{
  ObjectBrowser* pSelectedObjects = new ObjectBrowser();
  std::vector<CCopasiObject*>* pSelectedVector = new std::vector<CCopasiObject*>();
  pSelectedObjects->setOutputVector(pSelectedVector);

  if (pSelectedObjects->exec () == QDialog::Rejected)
    {
      pdelete(pSelectedVector);
      return;
    }

  if (pSelectedVector->size() == 0)
    {
      pdelete(pSelectedVector);
      return;
    }

  int i = 0;
  for (; i < pSelectedVector->size(); i++)
    if ((*pSelectedVector)[i])
      break;

  if (i >= pSelectedVector->size()) //no result returned
    {
      pdelete(pSelectedVector);
      return;
    }

  if (itemsTable->findItem((*pSelectedVector)[i]->getCN().c_str()) == NULL)
    {
      itemsTable->insertItem((*pSelectedVector)[i]->getCN().c_str());
      //      selectedList.push_back((*pSelectedVector)[i]);
      bUpdated = true;
    }

  pdelete(pSelectedVector);
  //  if (addNewScanItem((*pSelectedVector)[i]))
  //    ObjectListBox->insertItem ((*pSelectedVector)[i]->getObjectUniqueName().c_str(), nSelectedObjects - 1);
}

void ExpressionWidget::deleteButtonClicked()
{
  QListBoxItem* selectedItem = itemsTable->selectedItem ();
  UINT32 selectedIndex = itemsTable->index(selectedItem);
  if (selectedItem)
    {
      //      std::vector<CCopasiObject*>::iterator it = selectedList.begin();
      //      selectedList.erase(selectedIndex + it, selectedIndex + it + 1);
      //      int pp = selectedList.size();
      itemsTable->removeItem(selectedIndex);
      bUpdated = true;
    }
}

void ExpressionWidget::upButtonClicked()
{
  QListBoxItem* selectedItem = itemsTable->selectedItem ();
  UINT32 selectedIndex = itemsTable->index(selectedItem);
  if ((selectedItem) && (selectedIndex != 0))
    {
      //swap in selectedList
      //      CCopasiObject* pDownObject = selectedList[selectedIndex];
      // check for valid of the update object pointer array
      // QString pDownItemStr1(pDownObject->getObjectUniqueName().c_str());
      //     CCopasiObject* pUpperObject = selectedList[selectedIndex - 1];
      //      selectedList[selectedIndex] = pUpperObject;
      //      selectedList[selectedIndex - 1] = pDownObject;

      //swap in ListBox
      QString pDownItemStr(itemsTable->item(selectedIndex)->text());
      QString pUpperItemStr(itemsTable->item(selectedIndex - 1)->text());
      itemsTable->changeItem (pUpperItemStr, selectedIndex);
      itemsTable->changeItem (pDownItemStr, selectedIndex - 1);
      bUpdated = true;
    }
}

void ExpressionWidget::downButtonClicked()
{
  QListBoxItem* selectedItem = itemsTable->selectedItem ();
  UINT32 selectedIndex = itemsTable->index(selectedItem);
  if ((selectedItem) && (itemsTable->item(selectedIndex + 1)))
    {
      //swap in selectedList
      //      CCopasiObject* pDownObject = selectedList[selectedIndex + 1];
      // check for valid of the update object pointer array
      // QString pDownItemStr1(pDownObject->getObjectUniqueName().c_str());
      //      CCopasiObject* pUpperObject = selectedList[selectedIndex];
      //      selectedList[selectedIndex + 1] = pUpperObject;
      //      selectedList[selectedIndex] = pDownObject;

      //swap in ListBox
      QString pDownItemStr(itemsTable->item(selectedIndex + 1)->text());
      QString pUpperItemStr(itemsTable->item(selectedIndex)->text());
      itemsTable->changeItem (pUpperItemStr, selectedIndex + 1);
      itemsTable->changeItem (pDownItemStr, selectedIndex);
      bUpdated = true;
    }
}
