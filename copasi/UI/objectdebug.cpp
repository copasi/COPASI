/****************************************************************************
 ** Form implementation generated from reading ui file 'objectdebug.ui'
 **
 ** Created: Tue Apr 1 19:46:58 2003
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
  ObjectDebugLayout = new QGridLayout(this, 1, 1, 11, 6, "ObjectDebugLayout");

  UpdateButton = new QPushButton(this, "UpdateButton");

  ObjectDebugLayout->addWidget(UpdateButton, 1, 1);

  ListOfObjects = new QListView(this, "ListOfObjects");
  ListOfObjects->addColumn(tr("Column 1"));

  ObjectDebugLayout->addMultiCellWidget(ListOfObjects, 0, 0, 0, 1);
  QSpacerItem* spacer = new QSpacerItem(121, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  ObjectDebugLayout->addItem(spacer, 1, 0);
  languageChange();
  resize(QSize(517, 486).expandedTo(minimumSizeHint()));

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
