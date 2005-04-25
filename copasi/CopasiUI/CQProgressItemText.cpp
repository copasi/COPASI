/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQProgressItemText.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/25 18:13:22 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQProgressItemText.ui'
 **
 ** Created: Thu Apr 21 13:02:57 2005
 **      by: The User Interface Compiler ($Id: CQProgressItemText.cpp,v 1.1 2005/04/25 18:13:22 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQProgressItemText.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQProgressItemText.ui.h"

/*
 *  Constructs a CQProgressItemText which is a child of 'parent', with the
 *  name 'name'.' 
 */
CQProgressItemText::CQProgressItemText(QWidget* parent, const char* name)
    : CQProgressItem(parent, name)
{
  if (!name)
    setName("CQProgressItemText");

  QWidget* privateLayoutWidget = new QWidget(this, "mLabel");
  privateLayoutWidget->setGeometry(QRect(10, 10, 330, 22));
  mLabel = new QHBoxLayout(privateLayoutWidget, 11, 6, "mLabel");

  mItemName = new QLabel(privateLayoutWidget, "mItemName");
  mItemName->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)3, 0, 0, mItemName->sizePolicy().hasHeightForWidth()));
  mItemName->setMinimumSize(QSize(100, 0));
  mLabel->addWidget(mItemName);
  mSpacer = new QSpacerItem(16, 16, QSizePolicy::Maximum, QSizePolicy::Minimum);
  mLabel->addItem(mSpacer);

  mValue = new QLineEdit(privateLayoutWidget, "mValue");
  mValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)3, 0, 0, mValue->sizePolicy().hasHeightForWidth()));
  mValue->setMinimumSize(QSize(200, 0));
  mValue->setFrameShape(QLineEdit::LineEditPanel);
  mValue->setFrameShadow(QLineEdit::Sunken);
  mLabel->addWidget(mValue);
  languageChange();
  resize(QSize(404, 44).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQProgressItemText::~CQProgressItemText()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQProgressItemText::languageChange()
{
  setCaption(tr("Form1"));
  mItemName->setText(tr("Item Name"));
}
