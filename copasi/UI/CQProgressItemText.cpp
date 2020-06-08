// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQProgressItemText.h"

#include "copasi/copasi.h"
#include "qtUtilities.h"

#include "copasi/utilities/CProcessReport.h"

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
  mpParameterValue = mpItem->getValuePointer();

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
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
        mpSetValue = & CQProgressItemText::setValueFromDOUBLE;
        break;

      case CCopasiParameter::Type::INT:
        mpSetValue = & CQProgressItemText::setValueFromINT;
        break;

      case CCopasiParameter::Type::UINT:
        mpSetValue = & CQProgressItemText::setValueFromUINT;
        break;

      case CCopasiParameter::Type::STRING:
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
  mValue->setText(convertToQString(* static_cast< C_FLOAT64 * >(mpParameterValue)));
}

void CQProgressItemText::setValueFromINT()
{
  mValue->setText(QString::number(* static_cast< C_INT32 * >(mpParameterValue)));
}

void CQProgressItemText::setValueFromUINT()
{
  mValue->setText(QString::number(* static_cast< unsigned C_INT32 * >(mpParameterValue)));
}

void CQProgressItemText::setValueFromSTRING()
{
  mValue->setText(FROM_UTF8(* static_cast< std::string * >(mpParameterValue)));
}
