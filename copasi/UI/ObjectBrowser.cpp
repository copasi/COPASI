/****************************************************************************
 ** Form implementation generated from reading ui file '.\ObjectBrowser.ui'
 **
 ** Created: Tue Apr 22 13:27:37 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#include "ObjectBrowser.h"

#include <qvariant.h>
#include <qheader.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
#include "ObjectBrowserItem.h"

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
  connect(ObjectListView, SIGNAL(pressed(QListViewItem*)), this, SLOT(listviewChecked(QListViewItem*)));
  connect(ObjectListView, SIGNAL(doubleClicked(QListViewItem*)), this, SLOT(listviewChecked(QListViewItem*)));

  // tab order
  setTabOrder(ObjectListView, backButton);
  setTabOrder(backButton, nextButton);
  setTabOrder(nextButton, cancelButton);

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

void ObjectBrowser::listviewChecked(ObjectBrowserItem* pCurrent)
{
  //   if (pCurrent->UserChecked()==NOCHECKED)
  // if (pCurrent->UserChecked()==
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
  ObjectBrowserItem * item_2 = new ObjectBrowserItem(ObjectListView, 0, NULL);
  item_2->setOpen(TRUE);
  item_2->setPixmap(0, *pObjectAll);
  ObjectBrowserItem * item_3 = new ObjectBrowserItem(item_2, 0, NULL);
  item_3->setOpen(TRUE);
  item_3->setPixmap(0, *pObjectAll);
  ObjectBrowserItem * item_4 = new ObjectBrowserItem(item_3, 0, NULL);
  item_4->setOpen(TRUE);
  item_4->setPixmap(0, *pObjectAll);
  ObjectBrowserItem * item_5 = new ObjectBrowserItem(item_4, 0, NULL);
  item_5->setOpen(TRUE);
  item_5->setPixmap(0, *pObjectAll);
  ObjectBrowserItem * item_6 = new ObjectBrowserItem(item_5, 0, NULL);
  item_6->setOpen(TRUE);
  item_6->setPixmap(0, *pObjectAll);
  ObjectBrowserItem * item = new ObjectBrowserItem(item_6, 0, NULL);
  item->setPixmap(0, *pObjectAll);
  item->setText(0, trUtf8("Subitem"));

  item_6->setText(0, trUtf8("Subitem"));
  item_5->setText(0, trUtf8("Subitem"));
  item_4->setText(0, trUtf8("Subitem"));
  item_3->setText(0, trUtf8("Subitem"));
  item_2->setText(0, trUtf8("Item"));
  item = new ObjectBrowserItem(ObjectListView, item_2, NULL);
  item->setPixmap(0, *pObjectAll);
  item->setText(0, trUtf8("Item"));
  item = new ObjectBrowserItem(ObjectListView, item, NULL);
  item->setPixmap(0, *pObjectAll);
  item->setText(0, trUtf8("Item"));
}
