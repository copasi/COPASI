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
  //  refreshList = new objectList();
  loadData();
}

/*
 *  Destroys the object and frees any allocated resources
 */
ObjectBrowser::~ObjectBrowser()
{
  delete objectItemList;
  // delete refreshList;
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
  //  refreshList->insert(pCurrent);
  ObjectBrowserItem* pTmp = pCurrent;
  //  while (pTmp->parent() != NULL)
  //    {
  //      pTmp = pTmp->parent();
  //      refreshList->insert(pTmp);
  //}

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
  //  refreshList->insert(pCurrent);
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
  //  refreshList->insert(pCurrent);

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
  CCopasiContainer* root = &CRootContainer::ref();
  ObjectBrowserItem * itemRoot = new ObjectBrowserItem(ObjectListView, NULL, root, objectItemList);
  itemRoot->setObjectType(CONTAINERATTR);
  itemRoot->setText(0, root->getName().c_str());
  itemRoot->setOpen(true);
  loadChild(itemRoot, root, true);

  loadUI();
}

void ObjectBrowser::loadChild(ObjectBrowserItem* parent, CCopasiContainer* copaParent, bool nField)
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
      if (current->isContainer() && !current->isVector())
        {
          currentItem->setText(0, current->getObjectName().c_str());
          currentItem->setObjectType(CONTAINERATTR);
          currentItem->attachKey();
          loadChild(currentItem, (CCopasiContainer*) current, nField);
        }
      else
        {
          currentItem->setText(0, current->getObjectName().c_str());
          QString st1(current->getObjectName().c_str());
          if (current->isVector())
            {
              currentItem->setObjectType(CONTAINERATTR);
              currentItem->attachKey();
              ObjectBrowserItem* objectChild = currentItem;
              if (nField)
                {
                  objectChild = new ObjectBrowserItem(currentItem, NULL, NULL, objectItemList);
                  objectChild->setObjectType(OBJECTATTR);
                  objectChild->setText(0, "Object list");
                  nField = false;
                  loadChild(objectChild, (CCopasiContainer *) current, nField);

                  ObjectBrowserItem* fieldChild = new ObjectBrowserItem(currentItem, objectChild, NULL, objectItemList);
                  fieldChild->setObjectType(FIELDATTR);
                  fieldChild->setText(0, "Attribute list");
                  loadField(fieldChild, (CCopasiContainer*) current);

                  fieldChild->attachKey();
                  objectChild->attachKey();
                }
              else
                loadChild(objectChild, (CCopasiContainer *) current, nField);
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

void ObjectBrowser::loadField(ObjectBrowserItem* parent, CCopasiContainer * copaParent)
{
  // ObjectBrowserItem* parent=itemRoot;
  ObjectBrowserItem* lastField = NULL;
  CCopasiObject* currentField = NULL;
  ObjectBrowserItem* last = NULL;
  CCopasiObject* current = NULL;

  std::vector<CCopasiObject *> pObjectList = copaParent->getObjects();
  std::vector<CCopasiObject *>::iterator it = pObjectList.begin();
  std::vector<CCopasiObject *>::iterator end = pObjectList.end();
  std::vector<CCopasiObject *>::iterator pFirstObject = it;

  if (it == end)
    return;

  std::vector<CCopasiObject *> fieldList = ((CCopasiContainer*) * it)->getObjects();
  std::vector<CCopasiObject *>::iterator fieldIt = fieldList.begin();
  std::vector<CCopasiObject *>::iterator fieldEnd = fieldList.end();

  while (fieldIt < fieldEnd)
    {
      currentField = *fieldIt;
      ObjectBrowserItem* currentItemField = new ObjectBrowserItem(parent, lastField, NULL, objectItemList);
      currentItemField->setObjectType(FIELDATTR);
      currentItemField->setText(0, currentField->getObjectName().c_str());
      lastField = currentItemField;
      it = pFirstObject;
      while (it < end)
        {
          current = *it;
          CCopasiObject* pSubField = getFieldCopasiObject(current, currentField->getObjectName().c_str());

          ObjectBrowserItem* currentItem = new ObjectBrowserItem(currentItemField, last, pSubField, objectItemList);
          //          ObjectBrowserItem* currentItem = new ObjectBrowserItem(currentItemField, last, current, objectItemList);

          currentItem->setText(0, current->getObjectName().c_str());
          currentItem->setObjectType(FIELDATTR);
          last = currentItem;
          it++;
        }
      fieldIt++;
    }
}

void ObjectBrowser::updateUI()
{
  objectListItem* pCurrent = objectItemList->getRoot();
  setCheckMark(pCurrent->pItem);
  for (; pCurrent != NULL; pCurrent = pCurrent->pNext)
    setCheckMark(pCurrent->pItem);
  /*
    for (ObjectBrowserItem* pCurrent = refreshList->pop(); pCurrent != NULL; pCurrent = refreshList->pop())
      setCheckMark(pCurrent);
  */
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

void ObjectBrowser::loadUI()
{
  objectListItem* pCurrent = objectItemList->getRoot();
  setCheckMark(pCurrent->pItem);
  for (; pCurrent != NULL; pCurrent = pCurrent->pNext)
    setCheckMark(pCurrent->pItem);
}

CCopasiObject* ObjectBrowser::getFieldCopasiObject(CCopasiObject* pCurrent, const char* name)
{
  std::vector<CCopasiObject *> pObjectList = ((CCopasiContainer*)pCurrent)->getObjects();
  std::vector<CCopasiObject *>::iterator it = pObjectList.begin();
  std::vector<CCopasiObject *>::iterator end = pObjectList.end();

  while (it < end)
    {
      if (QString((*it)->getObjectName().c_str()) == name)
        return *it;
      it++;
    }
  return NULL;
}
