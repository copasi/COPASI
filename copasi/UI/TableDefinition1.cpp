/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/TableDefinition1.cpp,v $
   $Revision: 1.28 $
   $Name:  $
   $Author: mkulkarn $ 
   $Date: 2003/12/11 21:43:22 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file '.\TableDefinition1.ui'
 **
 ** Created: Wed Aug 6 22:43:06 2003
 **      by: The User Interface Compiler ($Id: TableDefinition1.cpp,v 1.28 2003/12/11 21:43:22 mkulkarn Exp $)
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
#include <qlistbox.h>
#include <qcombobox.h>
#include <qstring.h>
#include <qmessagebox.h>

#include "TableDefinition1.h"
#include "ObjectBrowser.h"
#include "listviews.h"
#include "report/CKeyFactory.h"
#include "report/CReportDefinition.h"
#include "report/CCopasiObjectName.h"
#include "report/CCopasiContainer.h"
#include "report/CCopasiStaticString.h"
#include "report/CReport.h"
#include "ScanWidget.h"

#include "./icons/scanwidgetbuttonicon.xpm"

/*
 *  Constructs a TableDefinition1 as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
TableDefinition1::TableDefinition1(QWidget* parent, const char* name, WFlags fl)
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

  itemsTable = new QListBox(this);
  //  ScanItemWidget* parameterTable = new ScanItemWidget(this, "parameterTable");
  //  scrollview->setMinimumWidth(parameterTable->minimumSizeHint().width());
  //  pdelete(parameterTable);
  //  itemsTable->setVScrollBarMode(QScrollView::Auto);
  //  itemsTable->setHScrollBarMode(QScrollView::AlwaysOff); //Disable Horizonal Scroll
  //  itemsTable->setSelectedList(&selectedList);
  //  selectedList.clear();

  //    itemsTable = new QTable(this, "itemsTable");
  //    itemsTable->setNumRows(0);
  //    itemsTable->setNumCols(0);
  layout7->addWidget(itemsTable);

  TableDefinitionLayout->addMultiCellLayout(layout7, 1, 1, 0, 1);

  frame4 = new QFrame(this, "frame4");
  frame4->setFrameShape(QFrame::Box);
  frame4->setFrameShadow(QFrame::Sunken);
  frame4->setLineWidth(1);
  frame4Layout = new QGridLayout(frame4, 1, 1, 11, 6, "frame4Layout");

  tabChecked = new QCheckBox(frame4, "tabChecked");

  frame4Layout->addWidget(tabChecked, 3, 1);

  seperatorEdit = new QLineEdit(frame4, "seperatorEdit");

  frame4Layout->addWidget(seperatorEdit, 2, 1);

  seperatorLabel = new QLabel(frame4, "seperatorLabel");

  frame4Layout->addWidget(seperatorLabel, 2, 0);

  comboTask = new QComboBox(FALSE, frame4, "comboTask");
  comboTask->insertItem("Scan Task");
  comboTask->insertItem("Trajectory Task");
  comboTask->insertItem("SteadyState Task");

  frame4Layout->addWidget(comboTask, 0, 1);

  line4 = new QFrame(frame4, "line4");
  line4->setFrameShape(QFrame::HLine);
  line4->setFrameShadow(QFrame::Sunken);
  line4->setFrameShape(QFrame::HLine);

  frame4Layout->addMultiCellWidget(line4, 1, 1, 0, 1);

  taskLabel = new QLabel(frame4, "taskLabel");

  frame4Layout->addWidget(taskLabel, 0, 0);

  TableDefinitionLayout->addWidget(frame4, 0, 1);

  frame5 = new QFrame(this, "frame5");
  frame5->setFrameShape(QFrame::Box);
  frame5->setFrameShadow(QFrame::Sunken);
  frame5Layout = new QGridLayout(frame5, 1, 1, 11, 6, "frame5Layout");

  commentEdit = new QLineEdit(frame5, "commentEdit");
  commentEdit->setFrameShape(QLineEdit::LineEditPanel);
  commentEdit->setFrameShadow(QLineEdit::Sunken);
  commentEdit->setLineWidth(2);

  frame5Layout->addWidget(commentEdit, 1, 1);

  commentLabel = new QLabel(frame5, "commentLabel");

  frame5Layout->addWidget(commentLabel, 1, 0);

  targetLabel = new QLabel(frame5, "targetLabel");

  frame5Layout->addWidget(targetLabel, 0, 0);

  nameEdit = new QLineEdit(frame5, "nameEdit");
  nameEdit->setFrameShape(QLineEdit::LineEditPanel);
  nameEdit->setFrameShadow(QLineEdit::Sunken);

  frame5Layout->addWidget(nameEdit, 0, 1);

  titleChecked = new QCheckBox(frame5, "titleChecked");

  frame5Layout->addWidget(titleChecked, 2, 1);

  TableDefinitionLayout->addWidget(frame5, 0, 0);
  languageChange();
  clearWState(WState_Polished);

  // tab order
  setTabOrder(nameEdit, commentEdit);
  setTabOrder(commentEdit, titleChecked);
  setTabOrder(titleChecked, comboTask);
  setTabOrder(comboTask, seperatorEdit);
  setTabOrder(seperatorEdit, tabChecked);
  setTabOrder(tabChecked, addButton);
  setTabOrder(addButton, deleteButton);
  setTabOrder(deleteButton, upButton);
  setTabOrder(upButton, downButton);
  setTabOrder(downButton, itemsTable);
  setTabOrder(itemsTable, confirmButton);
  setTabOrder(confirmButton, cancelButton);

  connect(nameEdit, SIGNAL(textChanged(const QString&)), this, SLOT(nameTextChanged(const QString&)));
  connect(commentEdit, SIGNAL(textChanged(const QString&)), this, SLOT(commentTextChanged(const QString&)));
  connect(seperatorEdit, SIGNAL(textChanged(const QString&)), this, SLOT(seperatorTextChanged(const QString&)));

  connect(tabChecked, SIGNAL(clicked()), this, SLOT(tabButtonClicked()));
  connect(titleChecked, SIGNAL(clicked()), this, SLOT(titleButtonClicked()));

  connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
  connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
  connect(upButton, SIGNAL(clicked()), this, SLOT(upButtonClicked()));
  connect(downButton, SIGNAL(clicked()), this, SLOT(downButtonClicked()));

  connect(confirmButton, SIGNAL(clicked()), this, SLOT(slotBtnConfirmClicked()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));

  connect(comboTask, SIGNAL(activated(const QString &)), this, SLOT(comboTaskChanged(const QString &)));
}

/*
 *  Destroys the object and frees any allocated resources
 */
TableDefinition1::~TableDefinition1()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void TableDefinition1::languageChange()
{
  setCaption(tr("Reports"));
  confirmButton->setText(tr("confirm"));
  cancelButton->setText(tr("cancel"));
  itemsLabel->setText(tr("Items"));
  upButton->setText(QString::null);
  downButton->setText(QString::null);
  deleteButton->setText(QString::null);
  addButton->setText(QString::null);
  tabChecked->setText(tr("Tab"));
  seperatorLabel->setText(tr("Seperator"));
  taskLabel->setText(tr("Task"));
  commentLabel->setText(tr("Comment"));
  targetLabel->setText(tr("ReportDefinition"));
  titleChecked->setText(tr("Title"));
}

/*This function is to load the model for the table*/
void TableDefinition1::loadTableDefinition1()
{
  CReportDefinition* pReportDefinition = (CReportDefinition*)CKeyFactory::get(reportKey);
  itemsTable->clear();

  nameEdit->setText(pReportDefinition->getObjectName().c_str());
  commentEdit->setText(pReportDefinition->getComment().c_str());
  titleChecked->setChecked(pReportDefinition->getTitle());

  C_INT32 i;
  // i+=2; is due to skip to show the seperator
  for (i = 0; i < pReportDefinition->getBodyAddr()->size(); i += 2)
    {
      itemsTable->insertItem((*(pReportDefinition->getBodyAddr()))[i].c_str());
    }
  comboTask->setEnabled(true);

  if (pReportDefinition->getSeperator().getStaticString() == "/t")
    {
      seperatorEdit->setEnabled(false);
      tabChecked->setChecked(true);
    }
  else
    {
      seperatorEdit->setEnabled(true);
      tabChecked->setChecked(false);
      seperatorEdit->setText(pReportDefinition->getSeperator().getStaticString().c_str());
    }
  bUpdated = false;
}

void TableDefinition1::setReport(CReport* pNewReport)
{
  mReport = pNewReport;
}

void TableDefinition1::comboTaskChanged(const QString & C_UNUSED(string))
{bUpdated = true;}

void TableDefinition1::slotBtnCancelClicked()
{
  //check for the connection int i =0;
}

void TableDefinition1::slotBtnConfirmClicked()
{
  //check for the connection int i =0;
  CReportDefinition* pReportDefinition = (CReportDefinition*)CKeyFactory::get(reportKey);
  pReportDefinition->getHeaderAddr()->clear();
  pReportDefinition->getBodyAddr()->clear();

  C_INT32 i;
  CCopasiStaticString Seperator;
  if (tabChecked->isChecked())
    Seperator = "\t";
  else
    Seperator = seperatorEdit->text().latin1();

  pReportDefinition->setTitle(titleChecked->isChecked());
  pReportDefinition->
  setComment(CCopasiStaticString(commentEdit->text().latin1()).getCN());

  CCopasiObjectName SeperatorCN(Seperator.getCN());
  CCopasiObjectName Title;
  std::vector< CCopasiContainer * > ListOfContainer;
  CCopasiObject* pSelectedObject;
  for (i = 0; i < itemsTable->numRows(); i++)
    {
      pSelectedObject =
        CCopasiContainer::ObjectFromName(ListOfContainer,
                                         CCopasiObjectName(itemsTable->text(i).latin1()));

      if (pSelectedObject)
        {
          if (pSelectedObject->getObjectParent())
            {
              Title =
                pSelectedObject->getObjectParent()->getCN();
              Title += ",Reference=Name";
              pReportDefinition->getHeaderAddr()->push_back(Title);

              Title =
                CCopasiStaticString("[" + pSelectedObject->getObjectName() + "]").getCN();
            }
          else
            Title =
              CCopasiStaticString(pSelectedObject->getObjectName()).getCN();

          pReportDefinition->getHeaderAddr()->push_back(Title);
          pReportDefinition->getBodyAddr()->push_back(pSelectedObject->getCN());

          pReportDefinition->getHeaderAddr()->push_back(SeperatorCN);
          pReportDefinition->getBodyAddr()->push_back(SeperatorCN);
        }
    }

  if (pReportDefinition->getHeaderAddr()->size())
    {
      pReportDefinition->getHeaderAddr()->pop_back();
      pReportDefinition->getBodyAddr()->pop_back();
    }

  bUpdated = false;
}

void TableDefinition1::nameTextChanged(const QString &)
{
  bUpdated = true;
}

void TableDefinition1::commentTextChanged(const QString &)
{
  bUpdated = true;
}

void TableDefinition1::seperatorTextChanged(const QString &)
{
  bUpdated = true;
}

void TableDefinition1::tabButtonClicked()
{
  bUpdated = true;
  if (tabChecked->isChecked())
    {
      seperatorEdit->setText("");
    }
  seperatorEdit->setEnabled(!tabChecked->isChecked());
}

void TableDefinition1::titleButtonClicked()
{
  //check for the connection int i =0;
  bUpdated = true;
}

void TableDefinition1::addButtonClicked()
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

void TableDefinition1::deleteButtonClicked()
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

void TableDefinition1::upButtonClicked()
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

void TableDefinition1::downButtonClicked()
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

bool TableDefinition1::enter(const std::string & key)
{
  if (!CKeyFactory::get(key)) return false;

  reportKey = key;

  loadTableDefinition1();

  return true;
}

bool TableDefinition1::leave()
{
  //let the user confirm?
  if (bUpdated && (QMessageBox::warning(NULL, "Report Definition Save", "Do you want to save the change you have made to this Report Definition ?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes))
    {
      slotBtnConfirmClicked();
      bUpdated = false;
    }
  return true;
}

bool TableDefinition1::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
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
