/****************************************************************************
 ** Form implementation generated from reading ui file '.\ObjectBrowser.ui'
 **
 ** Created: Mon Apr 21 14:10:31 2003
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

  backButton = new QPushButton(this, "backButton");
  backButton->setText(trUtf8("Previous"));

  ObjectBrowserLayout->addWidget(backButton, 1, 0);

  nextButton = new QPushButton(this, "nextButton");
  nextButton->setText(trUtf8("Next"));

  ObjectBrowserLayout->addWidget(nextButton, 1, 1);

  cancelButton = new QPushButton(this, "cancelButton");
  cancelButton->setText(trUtf8("Cancel"));

  ObjectBrowserLayout->addWidget(cancelButton, 1, 2);

  ObjectList = new QListView(this, "ObjectList");
  ObjectList->addColumn(trUtf8("Object Browser"));
  ObjectList->header()->setClickEnabled(FALSE, ObjectList->header()->count() - 1);
  ObjectList->setAcceptDrops(FALSE);
  ObjectList->setResizeMode(QListView::LastColumn);
  ObjectList->setTreeStepSize(19);

  ObjectBrowserLayout->addMultiCellWidget(ObjectList, 0, 0, 0, 2);
}

/*
 *  Destroys the object and frees any allocated resources
 */
ObjectBrowser::~ObjectBrowser()
{
  // no need to delete child widgets, Qt does it all for us
}
