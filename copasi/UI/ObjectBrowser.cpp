/****************************************************************************
 ** Form implementation generated from reading ui file '.\ObjectBrowser.ui'
 **
 ** Created: Tue Apr 15 13:51:37 2003
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

  // signals and slots connections
  connect(nextButton, SIGNAL(clicked()), this, SLOT(nextClicked()));
  connect(backButton, SIGNAL(clicked()), this, SLOT(backClicked()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));

  // tab order
  setTabOrder(ObjectListView, backButton);
  setTabOrder(backButton, nextButton);
  setTabOrder(nextButton, cancelButton);
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
  destroy();
}

void ObjectBrowser::backClicked()
{
  qWarning("ObjectBrowser::backClicked(): Not implemented yet!");
}

void ObjectBrowser::nextClicked()
{
  qWarning("ObjectBrowser::nextClicked(): Not implemented yet!");
}
