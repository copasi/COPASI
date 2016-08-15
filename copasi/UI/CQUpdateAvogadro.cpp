// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQUpdateAvogadro.h"

#include <QtCore/QVariant>

/*
 *  Constructs a CQUpdateAvogadro as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
CQUpdateAvogadro::CQUpdateAvogadro(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
  : QDialog(parent, fl)
{
  setObjectName(QString::fromUtf8(name));
  setModal(modal);
  setupUi(this);

  mpBtnGrp->setId(mpPreserveConcentrations, 0);
  mpBtnGrp->setId(mpPreserveAmounts, 1);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQUpdateAvogadro::~CQUpdateAvogadro()
{
  // no need to delete child widgets, Qt does it all for us
}

int CQUpdateAvogadro::getSelection() const
{
  return mpBtnGrp->checkedId();
}

void CQUpdateAvogadro::setSelection(int selection)
{
  mpBtnGrp->button(selection)->setChecked(true);
}
