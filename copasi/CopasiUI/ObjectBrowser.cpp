/****************************************************************************
 ** Form implementation generated from reading ui file '.\ObjectBrowser.ui'
 **
 ** Created: Tue Apr 22 13:27:37 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#include "ObjectBrowser.h"
#include "ObjectBrowserItem.h"

#include <qvariant.h>
#include <qheader.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "./icons/objectAll.xpm"
#include "./icons/objectParts.xpm"
#include "./icons/objectNone.xpm"

QPixmap *pObjectAll = 0;   // to store the image of locked icon folder
QPixmap *pObjectParts = 0;   // to store the image of closed icon folder
QPixmap *pObjectNone = 0;     // to store the image of open icon folder

/*
 *  Constructs a ObjectBrowser which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
ObjectBrowser::ObjectBrowser(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("ObjectBrowser");
  resize(516, 321);
  setCaption(trUtf8("TabListView"));
  ObjectBrowserLayout = new QGridLayout(this, 1, 1, 11, 6, "ObjectBrowserLayout");

  cancelButton = new QPushButton(this, "cancelButton");
  cancelButton->setText(trUtf8("Cancel"));

  ObjectBrowserLayout->addWidget(cancelButton, 1, 2);

  nextButton = new QPushButton(this, "nextButton");
  nextButton->setText(trUtf8("Next"));

  ObjectBrowserLayout->addWidget(nextButton, 1, 1);

  backButton = new QPushButton(this, "backButton");
  backButton->setText(trUtf8("Back"));

  ObjectBrowserLayout->addWidget(backButton, 1, 0);

  ObjectListView = new QListView(this, "ObjectListView");
  ObjectListView->addColumn(trUtf8("Object Browser"));
  ObjectListView->header()->setClickEnabled(FALSE, ObjectListView->header()->count() - 1);

  ObjectListView->setAcceptDrops(FALSE);
  ObjectListView->setResizeMode(QListView::LastColumn);
  ObjectListView->setTreeStepSize(19);

  ObjectBrowserLayout->addMultiCellWidget(ObjectListView, 0, 0, 0, 2);

  pObjectAll = new QPixmap((const char**)ptrObjectAll);
  pObjectNone = new QPixmap((const char**)ptrObjectNone);
  pObjectParts = new QPixmap((const char**)ptrObjectParts);

  // signals and slots connections
  connect(backButton, SIGNAL(clicked()), this, SLOT(backClicked()));
  connect(nextButton, SIGNAL(clicked()), this, SLOT(nextClicked()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
  connect(ObjectListView, SIGNAL(clicked(QListViewItem*)), this, SLOT(listviewChecked(QListViewItem*)));
  //  connect(ObjectListView, SIGNAL(doubleClicked(QListViewItem*)), this, SLOT(listviewChecked(QListViewItem*)));

  // tab order
  setTabOrder(ObjectListView, backButton);
  setTabOrder(backButton, nextButton);
  setTabOrder(nextButton, cancelButton);

  objectItemList = new objectList();
  loadData();
}

/*
 *  Destroys the object and frees any allocated resources
 */
ObjectBrowser::~ObjectBrowser()
{
  // no need to delete child widgets, Qt does it all for us
}

void ObjectBrowser::cancelClicked()
{
  qWarning("ObjectBrowser::cancelClicked(): Not implemented yet!");
}

void ObjectBrowser::listviewChecked(QListViewItem* pCurrent)
{
  if (pCurrent == NULL)
    return;
  clickToReverseCheck((ObjectBrowserItem*)pCurrent);
  updateUI();
}

void ObjectBrowser::clickToReverseCheck(ObjectBrowserItem* pCurrent)
{
  if (pCurrent->isChecked() == ALLCHECKED)
    {
      if (pCurrent->isChecked())
        pCurrent->reverseChecked();
      setUncheck(pCurrent->child());
      return;
    }
  //else no check or partly checked
  if (!pCurrent->isChecked())
    pCurrent->reverseChecked();
  setCheck(pCurrent->child());
  return;
}

void ObjectBrowser::setUncheck(ObjectBrowserItem* pCurrent)
{
  if (pCurrent == NULL)
    return;
  if (pCurrent->isChecked())
    pCurrent->reverseChecked();
  if (pCurrent->child() != NULL)
    setUncheck(pCurrent->child());
  if (pCurrent->sibling() != NULL)
    setUncheck(pCurrent->sibling());
}

void ObjectBrowser::setCheck(ObjectBrowserItem* pCurrent)
{
  if (pCurrent == NULL)
    return;
  if (!pCurrent->isChecked())
    pCurrent->reverseChecked();
  if (pCurrent->child() != NULL)
    setCheck(pCurrent->child());
  if (pCurrent->sibling() != NULL)
    setCheck(pCurrent->sibling());
}

void ObjectBrowser::backClicked()
{
  qWarning("ObjectBrowser::backClicked(): Not implemented yet!");
}

void ObjectBrowser::nextClicked()
{
  qWarning("ObjectBrowser::nextClicked(): Not implemented yet!");
}

void ObjectBrowser::loadData()
{
  /* //testing data
      ObjectBrowserItem * item_2 = new ObjectBrowserItem(ObjectListView, 0 , NULL, objectItemList);
      item_2->setOpen(TRUE);
      ObjectBrowserItem * item_3 = new ObjectBrowserItem(item_2, 0 , NULL, objectItemList);
      ObjectBrowserItem * item_4 = new ObjectBrowserItem(item_3, 0 , NULL, objectItemList);
      ObjectBrowserItem * item_5 = new ObjectBrowserItem(item_4, 0 , NULL, objectItemList);
      ObjectBrowserItem * item_6 = new ObjectBrowserItem(item_5, 0 , NULL, objectItemList);
      ObjectBrowserItem * item = new ObjectBrowserItem(item_6, 0 , NULL, objectItemList);
      item->setText(0, trUtf8("Initial Volumn"));
      item = new ObjectBrowserItem(item_6, item, NULL, objectItemList);
      item->setText(0, trUtf8("Transient Volumn"));
      item = new ObjectBrowserItem(item_6, item, NULL, objectItemList);
      item->setText(0, trUtf8("Metabolite List"));
      item_6->setText(0, trUtf8("Compartment_1"));
      ObjectBrowserItem * item_7 = new ObjectBrowserItem(item_5, item_6, NULL, objectItemList);
      item = new ObjectBrowserItem(item_7, item_6, NULL, objectItemList);
      item->setText(0, trUtf8("Initial Volumn"));
      item = new ObjectBrowserItem(item_7, item, NULL, objectItemList);
      item->setText(0, trUtf8("Transient Volumn"));
      item = new ObjectBrowserItem(item_7, item, NULL, objectItemList);
      item->setText(0, trUtf8("Metabolite List"));
      item_7->setText(0, trUtf8("Compartment_2"));
      ObjectBrowserItem * item_8 = new ObjectBrowserItem(item_5, item_7, NULL, objectItemList);
      item = new ObjectBrowserItem(item_8, item_7, NULL, objectItemList);
      item->setText(0, trUtf8("Initial Volumn"));
      item = new ObjectBrowserItem(item_8, item, NULL, objectItemList);
      item->setText(0, trUtf8("Transient Volumn"));
      item = new ObjectBrowserItem(item_8, item, NULL, objectItemList);
      item->setText(0, trUtf8("Metabolite List"));
      item_8->setText(0, trUtf8("Compartment_3"));
      item_5->setText(0, trUtf8("Compartment List"));
      ObjectBrowserItem * item_9 = new ObjectBrowserItem(item_4, item_5, NULL, objectItemList);
      ObjectBrowserItem * item_10 = new ObjectBrowserItem(item_9, item_5, NULL, objectItemList);
      item = new ObjectBrowserItem(item_10, item_5, NULL, objectItemList);
      item->setText(0, trUtf8("Compartment_1"));
      item = new ObjectBrowserItem(item_10, item, NULL, objectItemList);
      item->setText(0, trUtf8("Compartment_2"));
      item = new ObjectBrowserItem(item_10, item, NULL, objectItemList);
      item->setText(0, trUtf8("Compartment_3"));
      item_10->setText(0, trUtf8("Initial Volumn"));
      ObjectBrowserItem * item_11 = new ObjectBrowserItem(item_9, item_10, NULL, objectItemList);
      item = new ObjectBrowserItem(item_11, item_10, NULL, objectItemList);
      item->setText(0, trUtf8("Compartment_1"));
      item = new ObjectBrowserItem(item_11, item, NULL, objectItemList);
      item->setText(0, trUtf8("Compartment_2"));
      item = new ObjectBrowserItem(item_11, item, NULL, objectItemList);
      item->setText(0, trUtf8("Compartment_3"));
      item_11->setText(0, trUtf8("Transient Volumn"));
      ObjectBrowserItem * item_12 = new ObjectBrowserItem(item_9, item_11, NULL, objectItemList);
      item = new ObjectBrowserItem(item_12, item_11, NULL, objectItemList);
      item->setText(0, trUtf8("Compartment_1"));
      item = new ObjectBrowserItem(item_12, item, NULL, objectItemList);
      item->setText(0, trUtf8("Compartment_2"));
      item = new ObjectBrowserItem(item_12, item, NULL, objectItemList);
      item->setText(0, trUtf8("Compartment_3"));
      item_12->setText(0, trUtf8("Metabolites"));
      item_9->setText(0, trUtf8("Field"));
      item_4->setText(0, trUtf8("Compartments"));
      item = new ObjectBrowserItem(item_3, item_4, NULL, objectItemList);
      item->setText(0, trUtf8("Metabolites"));
      item = new ObjectBrowserItem(item_3, item, NULL, objectItemList);
      item->setText(0, trUtf8("Moieties"));
      item = new ObjectBrowserItem(item_3, item, NULL, objectItemList);
      item->setText(0, trUtf8("Reactions"));
      item_3->setText(0, trUtf8("Model"));
      ObjectBrowserItem * item_13 = new ObjectBrowserItem(item_2, item_3, NULL, objectItemList);
      item = new ObjectBrowserItem(item_13, item_3, NULL, objectItemList);
      item->setText(0, trUtf8("Steady State Task"));
      item = new ObjectBrowserItem(item_13, item, NULL, objectItemList);
      item->setText(0, trUtf8("Trajectory Task"));
      item = new ObjectBrowserItem(item_13, item, NULL, objectItemList);
      item->setText(0, trUtf8("Scan Task"));
      item_13->setText(0, trUtf8("Task"));
      ObjectBrowserItem * item_14 = new ObjectBrowserItem(item_2, item_13, NULL, objectItemList);
      item = new ObjectBrowserItem(item_14, 0, NULL, objectItemList);
      item->setText(0, trUtf8("Function 1"));
      item_14->setText(0, trUtf8("Functions"));
      item_2->setText(0, trUtf8("Copasi Root"));
  */

  ObjectBrowserItem * item_1 = new ObjectBrowserItem(ObjectListView, 0, NULL, objectItemList);
  ObjectBrowserItem * item_2 = new ObjectBrowserItem(item_1, 0, NULL, objectItemList);
  ObjectBrowserItem * item_3 = new ObjectBrowserItem(item_1, item_2, NULL, objectItemList);
  ObjectBrowserItem * item_4 = new ObjectBrowserItem(item_1, item_3, NULL, objectItemList);
  ObjectBrowserItem * item_5 = new ObjectBrowserItem(item_2, 0, NULL, objectItemList);
  ObjectBrowserItem * item_6 = new ObjectBrowserItem(item_2, item_5, NULL, objectItemList);
  item_1->setOpen(true);
  item_1->setText(0, trUtf8("Root"));
  item_2->setText(0, trUtf8("Model"));
  item_3->setText(0, trUtf8("Task"));
  item_4->setText(0, trUtf8("Function"));
  item_5->setText(0, trUtf8("Metabolites"));
  item_6->setText(0, trUtf8("Reaction"));

  updateUI();
}

void ObjectBrowser::updateUI()
{
  objectListItem* pCurrent = objectItemList->getRoot();
  setCheckMark(pCurrent->pItem);
  for (; pCurrent != NULL; pCurrent = pCurrent->pNext)
    setCheckMark(pCurrent->pItem);
}

void ObjectBrowser::setCheckMark(ObjectBrowserItem* pCurrent)
{
  switch (pCurrent->nUserChecked())
    {
    case NOCHECKED:
      pCurrent->setPixmap(0, *pObjectNone);
      break;
    case ALLCHECKED:
      pCurrent->setPixmap(0, *pObjectAll);
      break;
    case PARTCHECKED:
      pCurrent->setPixmap(0, *pObjectParts);
      break;
    }
}
