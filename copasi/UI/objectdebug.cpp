/****************************************************************************
 ** Form implementation generated from reading ui file 'objectdebug.ui'
 **
 ** Created: Fri Mar 28 17:58:13 2003
 **      by: The User Interface Compiler ($Id: qt/main.cpp   3.1.1   edited Nov 21 17:40 $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "objectdebug.h"

#include <qvariant.h>
#include <qheader.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "objectdebug.ui.h"

/*
 *  Constructs a ObjectDebug as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
ObjectDebug::ObjectDebug(QWidget* parent, const char* name, bool modal, WFlags fl)
    : QDialog(parent, name, modal, fl)

{
  if (!name)
    setName("ObjectDebug");

  UpdateButton = new QPushButton(this, "UpdateButton");
  UpdateButton->setGeometry(QRect(410, 430, 141, 30));

  ListOfObjects = new QListView(this, "ListOfObjects");
  ListOfObjects->addColumn(tr("Column 1"));
  ListOfObjects->setGeometry(QRect(10, 10, 581, 410));
  languageChange();
  resize(QSize(600, 480).expandedTo(minimumSizeHint()));

  // signals and slots connections
  connect(UpdateButton, SIGNAL(clicked()), this, SLOT(update()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
ObjectDebug::~ObjectDebug()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ObjectDebug::languageChange()
{
  setCaption(tr("Copasi Object Tree"));
  UpdateButton->setText(tr("update"));
  ListOfObjects->header()->setLabel(0, tr("Column 1"));
  ListOfObjects->clear();
  QListViewItem * item = new QListViewItem(ListOfObjects, 0);
  item->setText(0, tr("New Item"));
}
