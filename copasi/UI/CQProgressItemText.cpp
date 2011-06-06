// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQProgressItemText.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2011/06/06 16:14:06 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQProgressItemText.h"
#include "UI/qtUtilities.h"

/*
 *  Constructs a CQProgressItemText which is a child of 'parent', with the
 *  name 'name'.'
 */
CQProgressItemText::CQProgressItemText(QWidget* parent, const char* name)
    : CQProgressItem(parent, name)
{
  Ui::CQProgressItemText::setupUi(this);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQProgressItemText::~CQProgressItemText()
{
  // no need to delete child widgets, Qt does it all for us
}

bool CQProgressItemText::initFromProcessReportItem(CProcessReportItem * pItem)
{
  mpItem = pItem;
  mParameterValue = mpItem->getValue();

  mItemName->setText(FROM_UTF8(mpItem->getObjectName()));

  this->show();

  return reset();
}

bool CQProgressItemText::process()
{
  (this->*mpSetValue)();
  return true;
}

bool CQProgressItemText::reset()
{
  switch (mpItem->getType())
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        mpSetValue = & CQProgressItemText::setValueFromDOUBLE;
        break;

      case CCopasiParameter::INT:
        mpSetValue = & CQProgressItemText::setValueFromINT;
        break;

      case CCopasiParameter::UINT:
        mpSetValue = & CQProgressItemText::setValueFromUINT;
        break;

      case CCopasiParameter::STRING:
        mpSetValue = & CQProgressItemText::setValueFromSTRING;
        break;

      default:
        return false;
        break;
    }

  return process();
}

void CQProgressItemText::setValueFromDOUBLE()
{
  mValue->setText(QString::number(* mParameterValue.pDOUBLE));
}

void CQProgressItemText::setValueFromINT()
{
  mValue->setText(QString::number(* mParameterValue.pINT));
}

void CQProgressItemText::setValueFromUINT()
{
  mValue->setText(QString::number(* mParameterValue.pUINT));
}

void CQProgressItemText::setValueFromSTRING()
{
  mValue->setText(FROM_UTF8(* mParameterValue.pSTRING));
}

