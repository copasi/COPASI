/* Begin CVS Header
   $Source: /home/cvs/copasi_dev/cvs_admin/c++style,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/05 18:38:04 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'objectdebug.ui'
 **
 ** Created: Do Dez 16 10:00:22 2004
 **      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "objectdebug.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qheader.h>
#include <qlistview.h>
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
  spacer5 = new QSpacerItem(121, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  ObjectDebugLayout->addItem(spacer5, 1, 0);
  languageChange();
  resize(QSize(517, 486).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(UpdateButton, SIGNAL(clicked()), this, SLOT(update()));
  connect(ListOfObjects, SIGNAL(rightButtonClicked(QListViewItem*, const QPoint&, int)), this, SLOT(action(QListViewItem*, const QPoint&, int)));
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
