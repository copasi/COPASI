/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQProgressItemBar.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/25 18:30:38 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQProgressItemBar.ui'
 **
 ** Created: Mon Apr 25 14:29:35 2005
 **      by: The User Interface Compiler ($Id: CQProgressItemBar.cpp,v 1.2 2005/04/25 18:30:38 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQProgressItemBar.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qprogressbar.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQProgressItem.h"
#include "CQProgressItemBar.ui.h"

/*
 *  Constructs a CQProgressItemBar which is a child of 'parent', with the
 *  name 'name'.' 
 */
CQProgressItemBar::CQProgressItemBar(QWidget* parent, const char* name)
    : CQProgressItem(parent, name)
{
  if (!name)
    setName("CQProgressItemBar");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, sizePolicy().hasHeightForWidth()));
  setMinimumSize(QSize(200, 33));

  QWidget* privateLayoutWidget = new QWidget(this, "mpLayout");
  privateLayoutWidget->setGeometry(QRect(11, 11, 335, 23));
  mpLayout = new QHBoxLayout(privateLayoutWidget, 1, 6, "mpLayout");

  mItemName = new QLabel(privateLayoutWidget, "mItemName");
  mItemName->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mItemName->sizePolicy().hasHeightForWidth()));
  mItemName->setMinimumSize(QSize(120, 20));
  mpLayout->addWidget(mItemName);
  mSpacer = new QSpacerItem(16, 16, QSizePolicy::Maximum, QSizePolicy::Minimum);
  mpLayout->addItem(mSpacer);

  mProgressBar = new QProgressBar(privateLayoutWidget, "mProgressBar");
  mProgressBar->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mProgressBar->sizePolicy().hasHeightForWidth()));
  mProgressBar->setMinimumSize(QSize(200, 14));
  mpLayout->addWidget(mProgressBar);
  languageChange();
  resize(QSize(200, 33).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQProgressItemBar::~CQProgressItemBar()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQProgressItemBar::languageChange()
{
  setCaption(tr("Progress Bar"));
  mItemName->setText(tr("Item Name"));
}
