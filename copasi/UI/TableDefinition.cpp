/****************************************************************************
 ** Form implementation generated from reading ui file '.\tabledefinition.ui'
 **
 ** Created: Wed Aug 6 22:43:06 2003
 **      by: The User Interface Compiler ($Id: TableDefinition.cpp,v 1.14 2003/08/10 03:19:36 lixu1 Exp $)
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

#include "TableDefinition.h"
#include "ObjectBrowser.h"
#include "listviews.h"
#include "report/CKeyFactory.h"
#include "report/CReportDefinition.h"
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

  itemsTable = new QListBox(this);
  //  ScanItemWidget* parameterTable = new ScanItemWidget(this, "parameterTable");
  //  scrollview->setMinimumWidth(parameterTable->minimumSizeHint().width());
  //  pdelete(parameterTable);
  //  itemsTable->setVScrollBarMode(QScrollView::Auto);
  //  itemsTable->setHScrollBarMode(QScrollView::AlwaysOff); //Disable Horizonal Scroll
  //  itemsTable->setSelectedList(&selectedList);
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

void TableDefinition::setReport(CReport* pNewReport)
{
  mReport = pNewReport;
}

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

void TableDefinition::addButtonClicked()
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

  if (itemsTable->findItem((*pSelectedVector)[i]->getObjectUniqueName().c_str()) == NULL)
    {
      itemsTable->insertItem((*pSelectedVector)[i]->getObjectUniqueName().c_str());
      selectedList.push_back((*pSelectedVector)[i]);
    }

  pdelete(pSelectedVector);
  //  if (addNewScanItem((*pSelectedVector)[i]))
  //    ObjectListBox->insertItem ((*pSelectedVector)[i]->getObjectUniqueName().c_str(), nSelectedObjects - 1);
}

void TableDefinition::deleteButtonClicked()
{
  QListBoxItem* selectedItem = itemsTable->selectedItem ();
  UINT32 selectedIndex = itemsTable->index(selectedItem);
  if (selectedItem)
    {
      std::vector<CCopasiObject*>::iterator it = selectedList.begin();
      selectedList.erase(selectedIndex + it, selectedIndex + it + 1);
      itemsTable->removeItem(selectedIndex);
    }
  /*  int pp = selectedList.size();
    if (activeObject < 0 || activeObject >= selectedList.size() / 2)  // not a valid entry
      return;
   
    emit hide_me();
   
    ((ScanItemWidget*)selectedList[1])->setFirstWidget(false);
   
    CMethodParameterList* pScanObject = ((ScanItemWidget*)(selectedList[activeObject * 2 + 1]))->getScanObject();
    //  if (!CKeyFactory::get(scanTaskKey))
    //   return;
    CScanTask* scanTask = (CScanTask*)(CCopasiContainer*)CKeyFactory::get(scanTaskKey);
    if (scanTask->getProblem()->getListSize() > 0)  // for reloading
      scanTask->getProblem()->removeScanItem(pScanObject->getName().c_str());
    scrollview->removeChild(selectedList[2*activeObject]);
    scrollview->removeChild(selectedList[2*activeObject + 1]);
   
    ObjectListBox->removeItem (activeObject);
   
    int i = activeObject + 1;
    int offsetY = ((ScanItemWidget*)selectedList[1])->minimumSizeHint().height() + nTitleHeight;
   
    for (; i < selectedList.size() / 2; i++)
      {
        scrollview->moveChild(selectedList[2*i], 0, (i - 1)*offsetY);
        scrollview->moveChild(selectedList[2*i + 1], 0, (i - 1)*offsetY + nTitleHeight);
      }
   
    std::vector<QWidget*>::iterator it = selectedList.begin();
    std::vector<QWidget*>::iterator BeginDel;
    std::vector<QWidget*>::iterator ToDel;
    while (it < selectedList.end())
      {
        if (it - selectedList.begin() == 2*activeObject)
          {
            BeginDel = it;
            pdelete (*it);
            ToDel = ++it;
            pdelete (*ToDel);
            ++ToDel;
            selectedList.erase(BeginDel, ToDel);
            break;
          }
        it++;
        it++;
      }
   
    activeObject--;
    if ((activeObject >= 0) && (scanTask->getProblem()->getListSize() > 0))
      {
        CCopasiObject* pScanObject = ((ScanItemWidget*)(selectedList[activeObject * 2 + 1]))->getScanObject();
        ScanLineEdit* activeTitle = (ScanLineEdit*)(selectedList[activeObject * 2]);
        activeTitle->setPaletteBackgroundColor(QColor(0, 0, 255));
        //      activeTitle->setText(pObject->getObjectUniqueName().c_str());
        activeTitle->setText(pScanObject->getCN().c_str());
      }
    nSelectedObjects--;
    scrollview->resizeContents(0, offsetY*selectedList.size() / 2);
   
    if ((selectedList.size() > 0) && (scanTask->getProblem()->getListSize() > 0))
      {
        ((ScanItemWidget*)selectedList[1])->setFirstWidget(true);
      }
   
    emit show_me();
   
    if (activeObject >= 0)
      ListBoxClicked(ObjectListBox->item(activeObject));
   
    // to verify the size of the mparameterlist in ScanProblem
    // scanTask->getProblem()->paraCount();
  */
}

void TableDefinition::upButtonClicked()
{
  /*
    if (activeObject <= 0 || activeObject >= selectedList.size() / 2)  // not a valid entry
      return;
   
    emit hide_me();
    ((ScanItemWidget*)selectedList[1])->setFirstWidget(false);
   
    CMethodParameterList* pScanObjectDown = ((ScanItemWidget*)selectedList[2 * activeObject + 1])->getScanObject();
    CMethodParameterList* pScanObjectUp = ((ScanItemWidget*)selectedList[2 * activeObject - 1])->getScanObject();
    CScanTask* scanTask = (CScanTask*)(CCopasiContainer*)CKeyFactory::get(scanTaskKey);
    ((ScanItemWidget*)selectedList[2*activeObject + 1])->setScanObject(scanTask->getProblem()->getScanItem(activeObject - 1));
    ((ScanItemWidget*)selectedList[2*activeObject - 1])->setScanObject(scanTask->getProblem()->getScanItem(activeObject));
    ((ScanItemWidget*)selectedList[2*activeObject + 1])->updateObject();
    ((ScanItemWidget*)selectedList[2*activeObject - 1])->updateObject();
    activeObject--;
   
    //deactivate
    //lower one
    ScanLineEdit* activeTitle = (ScanLineEdit*)(selectedList[(activeObject + 1) * 2]);
    activeTitle->setPaletteBackgroundColor(QColor(160, 160, 255));
    activeTitle->setText(pScanObjectUp->getName().c_str());
   
    //activate
    //upper one
    activeTitle = (ScanLineEdit*)(selectedList[activeObject * 2]);
    activeTitle->setPaletteBackgroundColor(QColor(0, 0, 255));
    activeTitle->setText(pScanObjectDown->getName().c_str());
   
    //Update ListBox
    QString tmp = ObjectListBox->text (activeObject);
    ObjectListBox->changeItem (NULL, ObjectListBox->text(activeObject + 1) , activeObject);
    ObjectListBox->changeItem (NULL, tmp, activeObject + 1);
   
    scanTask->getProblem()->swapScanItem(activeObject + 1, activeObject);
   
    ((ScanItemWidget*)selectedList[1])->setFirstWidget(true);
    emit show_me();
    if (activeObject >= 0)
      ListBoxClicked(ObjectListBox->item(activeObject));
  */
}

void TableDefinition::downButtonClicked()
{
  /*
    if (activeObject < 0 || activeObject >= selectedList.size() / 2 - 1)  // not a valid entry
      return;
   
    emit hide_me();
   
    ((ScanItemWidget*)selectedList[1])->setFirstWidget(false);
   
    activeObject++;
    CMethodParameterList* pObjectDown = ((ScanItemWidget*)selectedList[2 * activeObject + 1])->getScanObject();
    CMethodParameterList* pObjectUp = ((ScanItemWidget*)selectedList[2 * activeObject - 1])->getScanObject();
    CScanTask* scanTask = (CScanTask*)(CCopasiContainer*)CKeyFactory::get(scanTaskKey);
    ((ScanItemWidget*)selectedList[2*activeObject + 1])->setScanObject(scanTask->getProblem()->getScanItem(activeObject - 1));
    ((ScanItemWidget*)selectedList[2*activeObject - 1])->setScanObject(scanTask->getProblem()->getScanItem(activeObject));
    ((ScanItemWidget*)selectedList[2*activeObject + 1])->updateObject();
    ((ScanItemWidget*)selectedList[2*activeObject - 1])->updateObject();
   
    //upper one
    ScanLineEdit* activeTitle = (ScanLineEdit*)(selectedList[(activeObject - 1) * 2]);
    activeTitle->setPaletteBackgroundColor(QColor(160, 160, 255));
    activeTitle->setText(pObjectDown->getName().c_str());
   
    //bottom one
    activeTitle = (ScanLineEdit*)(selectedList[activeObject * 2]);
    activeTitle->setPaletteBackgroundColor(QColor(0, 0, 255));
    activeTitle->setText(pObjectUp->getName().c_str());
   
    //Update ListBox
    QString tmp = ObjectListBox->text (activeObject);
    ObjectListBox->changeItem (NULL, ObjectListBox->text(activeObject - 1) , activeObject);
    ObjectListBox->changeItem (NULL, tmp, activeObject - 1);
   
    scanTask->getProblem()->swapScanItem(activeObject - 1, activeObject);
   
    ((ScanItemWidget*)selectedList[1])->setFirstWidget(true);
   
    emit show_me();
    if (activeObject >= 0)
      ListBoxClicked(ObjectListBox->item(activeObject));
  */
}
