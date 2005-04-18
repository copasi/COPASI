/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/DefaultplotDialog.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/04/18 09:04:14 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'DefaultplotDialog.ui'
 **
 ** Created: Mo Apr 18 10:34:33 2005
 **      by: The User Interface Compiler ($Id: DefaultplotDialog.cpp,v 1.1 2005/04/18 09:04:14 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "DefaultplotDialog.h"

#include <qvariant.h>
#include <qlistbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "DefaultplotDialog.ui.h"

/*
 *  Constructs a DefaultPlotDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
DefaultPlotDialog::DefaultPlotDialog(QWidget* parent, const char* name, bool modal, WFlags fl)
    : QDialog(parent, name, modal, fl)
{
  if (!name)
    setName("DefaultPlotDialog");
  DefaultPlotDialogLayout = new QGridLayout(this, 1, 1, 11, 6, "DefaultPlotDialogLayout");

  listBox = new QListBox(this, "listBox");

  DefaultPlotDialogLayout->addMultiCellWidget(listBox, 0, 2, 0, 0);

  titleLabel = new QLabel(this, "titleLabel");

  DefaultPlotDialogLayout->addWidget(titleLabel, 0, 1);

  lineEditTitle = new QLineEdit(this, "lineEditTitle");

  DefaultPlotDialogLayout->addWidget(lineEditTitle, 1, 1);

  textEdit = new QTextEdit(this, "textEdit");

  DefaultPlotDialogLayout->addWidget(textEdit, 2, 1);

  layoutButtons = new QHBoxLayout(0, 0, 6, "layoutButtons");
  spacerButtons = new QSpacerItem(51, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layoutButtons->addItem(spacerButtons);

  createButton = new QPushButton(this, "createButton");
  layoutButtons->addWidget(createButton);

  cancelButton = new QPushButton(this, "cancelButton");
  layoutButtons->addWidget(cancelButton);

  DefaultPlotDialogLayout->addMultiCellLayout(layoutButtons, 3, 3, 0, 1);
  languageChange();
  resize(QSize(586, 383).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
  connect(createButton, SIGNAL(clicked()), this, SLOT(slotCreate()));
  connect(listBox, SIGNAL(selectionChanged()), this, SLOT(slotSelect()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
DefaultPlotDialog::~DefaultPlotDialog()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void DefaultPlotDialog::languageChange()
{
  setCaption(tr("Form1"));
  listBox->clear();
  listBox->insertItem(tr("New Item"));
  titleLabel->setText(tr("Title"));
  createButton->setText(tr("Create!"));
  cancelButton->setText(tr("Cancel"));
}
