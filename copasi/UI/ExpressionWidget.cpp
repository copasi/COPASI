/****************************************************************************
 ** Form implementation generated from reading ui file '.\ExpressionWidget.ui'
 **
 ** Created: Fri Sep 19 15:37:59 2003
 **      by: The User Interface Compiler ($Id: ExpressionWidget.cpp,v 1.12 2003/09/23 04:07:43 lixu1 Exp $)
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
#include <qtextbrowser.h>

#include "ExpressionWidget.h"
#include "copasi.h"
#include "listviews.h"
#include "ObjectBrowser.h"
#include "utilities/CGlobals.h"
#include "utilities/CMethodParameter.h"
#include "function/CFunction.h"
#include "function/CFunctionDB.h"
#include "function/CKinFunction.h"
#include "optimization/CExpression.h"

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

  layout18 = new QVBoxLayout(0, 0, 6, "layout18");

  layout17 = new QGridLayout(0, 1, 1, 0, 6, "layout17");

  //    expressionText = new QTextBrowser(this, "expressionText");
  //   expressionText = new QLineEdit(this, "expressionText");
  expressionText = new QTextEdit(this, "expressionText");

  layout17->addWidget(expressionText, 1, 1);

  expressionName = new QLineEdit(this, "expressionName");
  expressionName->setFrameShape(QLineEdit::LineEditPanel);
  expressionName->setFrameShadow(QLineEdit::Sunken);

  layout17->addWidget(expressionName, 0, 1);

  expressionEditlabel = new QLabel(this, "expressionEditlabel");

  layout17->addWidget(expressionEditlabel, 1, 0);

  expressionNameLabel = new QLabel(this, "expressionNameLabel");

  layout17->addWidget(expressionNameLabel, 0, 0);
  layout18->addLayout(layout17);

  bodyField_2 = new QFrame(this, "bodyField_2");
  bodyField_2->setFrameShape(QFrame::HLine);
  bodyField_2->setFrameShadow(QFrame::Sunken);
  bodyField_2->setFrameShape(QFrame::HLine);
  layout18->addWidget(bodyField_2);

  layout16 = new QHBoxLayout(0, 0, 6, "layout16");

  layout15 = new QVBoxLayout(0, 0, 6, "layout15");

  itemsLabel = new QLabel(this, "itemsLabel");
  layout15->addWidget(itemsLabel);

  layout14 = new QGridLayout(0, 1, 1, 0, 6, "layout14");

  downButton = new QPushButton(this, "downButton");
  downButton->setPixmap(image1);
  layout14->addWidget(downButton, 1, 1);

  deleteButton = new QPushButton(this, "deleteButton");
  deleteButton->setPixmap(image0);
  layout14->addWidget(deleteButton, 0, 1);

  addButton = new QPushButton(this, "addButton");
  addButton->setPixmap(image2);
  layout14->addWidget(addButton, 0, 0);

  //manually change to add icon for alignment need
  upButton = new QPushButton(this, "upButton");
  upButton->setPixmap(image3);
  layout14->addWidget(upButton, 1, 0);
  layout15->addLayout(layout14);

  listBoxItems = new QListBox(this, "listBoxItems");
  layout15->addWidget(listBoxItems);
  layout16->addLayout(layout15);

  itemsTable = new QListBox(this, "itemsTable");
  layout16->addWidget(itemsTable);
  layout18->addLayout(layout16);

  bodyField = new QFrame(this, "bodyField");
  bodyField->setFrameShape(QFrame::HLine);
  bodyField->setFrameShadow(QFrame::Sunken);
  bodyField->setFrameShape(QFrame::HLine);
  layout18->addWidget(bodyField);

  layout14_2 = new QHBoxLayout(0, 0, 6, "layout14_2");

  confirmButton = new QPushButton(this, "confirmButton");
  layout14_2->addWidget(confirmButton);

  cancelButton = new QPushButton(this, "cancelButton");
  layout14_2->addWidget(cancelButton);
  layout18->addLayout(layout14_2);

  ExpressionWidgetLayout->addLayout(layout18, 0, 0);
  languageChange();
  clearWState(WState_Polished);

  // tab order
  setTabOrder(expressionName, expressionText);
  setTabOrder(expressionText, addButton);
  setTabOrder(addButton, deleteButton);
  setTabOrder(deleteButton, upButton);
  setTabOrder(upButton, downButton);
  setTabOrder(downButton, listBoxItems);
  setTabOrder(listBoxItems, itemsTable);
  setTabOrder(itemsTable, confirmButton);
  setTabOrder(confirmButton, cancelButton);

  connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
  connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
  connect(upButton, SIGNAL(clicked()), this, SLOT(upButtonClicked()));
  connect(downButton, SIGNAL(clicked()), this, SLOT(downButtonClicked()));

  connect(confirmButton, SIGNAL(clicked()), this, SLOT(slotBtnConfirmClicked()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));
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
  expressionEditlabel->setText(tr("Expression"));
  expressionNameLabel->setText(tr("Expression Name"));
  itemsLabel->setText(tr("Copasi Items"));
  downButton->setText(QString::null);
  deleteButton->setText(QString::null);
  addButton->setText(QString::null);
  upButton->setText(QString::null);
  confirmButton->setText(tr("confirm"));
  cancelButton->setText(tr("cancel"));
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
  if (bUpdated && (QMessageBox::warning(NULL, "Report Definition Save", "Do you want to save the change you have made to this Report Definition ?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes))
    {
      slotBtnConfirmClicked();
      bUpdated = false;
    }
  return true;
}

bool ExpressionWidget::enter(const std::string & key)
{
  objKey = key;
  CExpression* func = (CExpression*)(CCopasiContainer*)CKeyFactory::get(key);
  //TODO: check if it really is a compartment

  if (func)
    return loadFromExpression(func);
  else
    return false;
}

bool ExpressionWidget::loadFromExpression(CExpression*)
{
  bUpdated = false;
  CExpression* func = (CExpression*)(CCopasiContainer*)CKeyFactory::get(objKey);
  expressionName->setText(func->getObjectUniqueName().c_str());
  expressionText->setText(func->
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

                        void ExpressionWidget::slotBtnCancelClicked()
                        {}

                        void ExpressionWidget::slotBtnConfirmClicked()
                        {}
