// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQStartValueReset.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:39:42 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQStartValueReset.h"

#include <QtCore/QVariant>

/*
 *  Constructs a CQStartValueReset as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
CQStartValueReset::CQStartValueReset(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
  setObjectName(QString::fromUtf8(name));
  setModal(modal);
  setupUi(this);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQStartValueReset::~CQStartValueReset()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQStartValueReset::slotModel()
{
  done(MODEL);
}

void CQStartValueReset::slotRandom()
{
  done(RANDOM);
}

void CQStartValueReset::slotSolution()
{
  done(SOLUTION);
}
