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

#include "report/CCopasiObject.h"
#include "report/CCopasiObjectName.h"
#include "report/CCopasiContainer.h"
#include "utilities/CCopasiVector.h"

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
  if (pCurrent->isChecked(0) == ALLCHECKED)
    {
      if (pCurrent->isChecked(0))
        pCurrent->reverseChecked(0);
      setUncheck(pCurrent->child());
      return;
    }
  //else no check or partly checked
  if (!pCurrent->isChecked(0))
    pCurrent->reverseChecked(0);
  setCheck(pCurrent->child());
  return;
}

void ObjectBrowser::setUncheck(ObjectBrowserItem* pCurrent)
{
  if (pCurrent == NULL)
    return;
  if (pCurrent->isChecked(0))
    pCurrent->reverseChecked(0);
  if (pCurrent->child() != NULL)
    setUncheck(pCurrent->child());
  if (pCurrent->sibling() != NULL)
    setUncheck(pCurrent->sibling());
}

void ObjectBrowser::setCheck(ObjectBrowserItem* pCurrent)
{
  if (pCurrent == NULL)
    return;
  if (!pCurrent->isChecked(0))
    pCurrent->reverseChecked(0);
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
  CCopasiContainer* root = &CRootContainer::ref();
  ObjectBrowserItem * itemRoot = new ObjectBrowserItem(ObjectListView, 0, root, objectItemList);
  itemRoot->setText(0, root->getName().c_str());
  itemRoot->setOpen(true);
  loadChild(itemRoot, root);
  updateUI();
}

void ObjectBrowser::loadChild(ObjectBrowserItem* parent, CCopasiContainer* copaParent)
{
  // ObjectBrowserItem* parent=itemRoot;
  ObjectBrowserItem* last = NULL;
  CCopasiObject* current = NULL;

  objectList* childStack = new objectList();

  std::vector<CCopasiObject *> pObjectList = copaParent->getObjects();
  std::vector<CCopasiObject *>::iterator it = pObjectList.begin();
  std::vector<CCopasiObject *>::iterator end = pObjectList.end();

  while (it < end)
    {
      current = *it;
      ObjectBrowserItem* currentItem = new ObjectBrowserItem(parent, last, current, objectItemList);
      last = currentItem;
      QString st1(current->getObjectName().c_str());
      if (current->isContainer() && !current->isVector())
        {
          currentItem->setText(0, current->getObjectName().c_str());
          currentItem->setObjectType(CONTAINERATTR);
          currentItem->attachKey();
          loadChild(currentItem, (CCopasiContainer*) current);
        }
      else
        {
          currentItem->setText(0, current->getObjectName().c_str());
          if (current->isVector())
            {
              currentItem->setObjectType(CONTAINERATTR);
              currentItem->attachKey();

              ObjectBrowserItem* fieldChild = new ObjectBrowserItem(currentItem, NULL, NULL, objectItemList);
              fieldChild->attachKey();
              fieldChild->setObjectType(FIELDATTR);
              fieldChild->setText(0, "Attribute list");

              ObjectBrowserItem* objectChild = new ObjectBrowserItem(currentItem, fieldChild, NULL, objectItemList);
              objectChild->attachKey();
              objectChild->setObjectType(CONTAINERATTR);
              objectChild->setText(0, "Object list");

              loadChild(objectChild, (CCopasiContainer *) current);
            }
          else
            {
              currentItem->setObjectType(OBJECTATTR);
              childStack->insert(currentItem);
            }
        }
      it++;
    }

  ObjectBrowserItem* pCurrent;
  while (childStack->len() > 0)
    {
      pCurrent = childStack->pop();
      pCurrent->attachKey();
    }
}

/*
void ObjectBrowser::loadVectors(ObjectBrowserItem* parent, CCopasiContainer * copaParent)
{
  ObjectBrowserItem* last = NULL;
  CCopasiObject* current = NULL;
 
  objectList* vectorStack= new objectList();
  
  const std::vector<CCopasiObject *> * pObjectList = & copaParent->getObjects();
  std::vector<CCopasiObject *>::const_iterator it = pObjectList->begin();
  std::vector<CCopasiObject *>::const_iterator end = pObjectList->end();
 
  while (it < end)
    {
      current = *it;
      ObjectBrowserItem* currentItem = new ObjectBrowserItem(parent, last, current, objectItemList);
      last = currentItem;
   QString st1(current->getObjectName().c_str());
      if (current->isContainer() && !current->isVector())
        {
          currentItem->setText(0, current->getObjectName().c_str());
          currentItem->setObjectType(OBJECTATTR);
    currentItem->attachKey();
          loadChild(currentItem, (CCopasiContainer*)current);
        }
      else
        {
          currentItem->setText(0, current->getObjectName().c_str());
          currentItem->setObjectType(OBJECTATTR);
          if (current->isVector())
    {
   currentItem->attachKey();
            loadVectors(currentItem, (CCopasiContainer *) current);
    }
    else
    vectorStack->insert(currentItem);
          QString st1(current->getObjectName().c_str());
          bool test = current->isVector();
          test = current->isMatrix();
          test = current->isNameVector();
          test = current->isReference();
 
          //   loadChild(currentItem, current);
        }
      it++;
    }
 
    ObjectBrowserItem* pCurrent;
    while(vectorStack->len()>0)
 {
  pCurrent=vectorStack->pop();
  pCurrent->attachKey();
 }
}
 */

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
