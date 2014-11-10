// Copyright (C) 2013 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQCompartmentCopyOptions.h"

#include <QtCore/QVariant>

/*
 *  Constructs a CQCompartmentCopyOptions as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
CQCompartmentCopyOptions::CQCompartmentCopyOptions(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
  : QDialog(parent, fl)
{
  setObjectName(QString::fromUtf8(name));
  setModal(modal);
  setupUi(this);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQCompartmentCopyOptions::~CQCompartmentCopyOptions()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQCompartmentCopyOptions::slotCompartment()
{
  done(COMP);
}

void CQCompartmentCopyOptions::slotAndSpecies()
{
  done(SPECIES);
}

void CQCompartmentCopyOptions::slotAndIntReactions()
{
  done(INTREAC);
}

void CQCompartmentCopyOptions::slotAndAllReactions()
{
  done(ALLREAC);
}
