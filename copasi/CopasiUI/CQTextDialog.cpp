/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQTextDialog.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/12 11:39:23 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQTextDialog.ui'
 **
 ** Created: Thu May 12 07:13:06 2005
 **      by: The User Interface Compiler ($Id: CQTextDialog.cpp,v 1.1 2005/05/12 11:39:23 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQTextDialog.h"

#include <qvariant.h>
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQTextDialog.ui.h"

/*
 *  Constructs a CQTextDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
CQTextDialog::CQTextDialog(QWidget* parent, const char* name, bool modal, WFlags fl)
    : QDialog(parent, name, modal, fl)
{
  if (!name)
    setName("CQTextDialog");
  setSizeGripEnabled(TRUE);
  CQTextDialogLayout = new QVBoxLayout(this, 11, 6, "CQTextDialogLayout");

  mpTextEdit = new QTextEdit(this, "mpTextEdit");
  CQTextDialogLayout->addWidget(mpTextEdit);

  mpBtnLayout = new QHBoxLayout(0, 0, 6, "mpBtnLayout");
  mpSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  mpBtnLayout->addItem(mpSpacer);

  mpBtnOK = new QPushButton(this, "mpBtnOK");
  mpBtnOK->setAutoDefault(TRUE);
  mpBtnOK->setDefault(TRUE);
  mpBtnLayout->addWidget(mpBtnOK);

  mpBtnCancel = new QPushButton(this, "mpBtnCancel");
  mpBtnCancel->setAutoDefault(TRUE);
  mpBtnLayout->addWidget(mpBtnCancel);
  CQTextDialogLayout->addLayout(mpBtnLayout);
  languageChange();
  resize(QSize(495, 178).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBtnOK, SIGNAL(clicked()), this, SLOT(accept()));
  connect(mpBtnCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQTextDialog::~CQTextDialog()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQTextDialog::languageChange()
{
  setCaption(tr("Text Dialog"));
  mpBtnOK->setText(tr("&OK"));
  mpBtnOK->setAccel(QKeySequence(QString::null));
  mpBtnCancel->setText(tr("&Cancel"));
  mpBtnCancel->setAccel(QKeySequence(QString::null));
}
