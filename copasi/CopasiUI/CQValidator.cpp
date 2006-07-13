/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQValidator.cpp,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/07/13 18:02:22 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlineedit.h>

#include <float.h>

#include "CQValidator.h"

CQValidatorNotEmpty::CQValidatorNotEmpty(QLineEdit * parent, const char * name):
    CQValidator< QLineEdit >(parent, name)
{}

QValidator::State CQValidatorNotEmpty::validate(QString & input, int & pos) const
  {
    if (input != "")
      return CQValidator< QLineEdit >::validate(input, pos);

    setColor(Invalid);
    return Intermediate;
  }

CQValidatorBound::CQValidatorBound(QLineEdit * parent, const char * name):
    CQValidator< QLineEdit >(parent, name),
    mpDoubleValidator(new QDoubleValidator(-DBL_MAX, DBL_MAX, DBL_DIG, this)),
    mValidBound("\t") // It is not possible to insert a tab.
{}

QValidator::State CQValidatorBound::validate (QString & input, int & pos) const
  {
    if (input == mValidBound ||
        mpDoubleValidator->validate(input, pos) == Acceptable)
      {
        force(input);
        return Acceptable;
      }

    setColor(Invalid);
    return Intermediate;
  }

void CQValidatorBound::force(const QString & input) const
  {
    const_cast<CQValidatorBound *>(this)->mValidBound = input;

    CQValidator< QLineEdit >::force(input);
  }

CQValidatorDouble::CQValidatorDouble(QLineEdit * parent, const char * name):
    CQValidator< QLineEdit >(parent, name),
    mpDoubleValidator(new QDoubleValidator(-DBL_MAX, DBL_MAX, DBL_DIG, this))
{}

QValidator::State CQValidatorDouble::validate(QString & input, int & pos) const
  {
    if (mpDoubleValidator->validate(input, pos) == Acceptable)
      return CQValidator< QLineEdit >::validate(input, pos);

    setColor(Invalid);
    return Intermediate;
  }

void CQValidatorDouble::setRange(const C_FLOAT64 & lowerBound, const C_FLOAT64 & upperBound)
{mpDoubleValidator->setRange(lowerBound, upperBound, DBL_DIG);}

CQValidatorInt::CQValidatorInt(QLineEdit * parent, const char * name):
    CQValidator< QLineEdit >(parent, name),
    mpIntValidator(new QIntValidator(-LONG_MAX, LONG_MAX, this))
{}

QValidator::State CQValidatorInt::validate(QString & input, int & pos) const
  {
    if (mpIntValidator->validate(input, pos) == Acceptable)
      return CQValidator< QLineEdit >::validate(input, pos);

    setColor(Invalid);
    return Intermediate;
  }

void CQValidatorInt::setRange(const C_INT32 & lowerBound, const C_INT32 & upperBound)
{mpIntValidator->setRange(lowerBound, upperBound);}
