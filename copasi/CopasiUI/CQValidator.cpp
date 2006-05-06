/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQValidator.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/05/06 03:07:17 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlineedit.h>

#include <float.h>

#include "CQValidator.h"

CQValidator::CQValidator(QLineEdit * parent, const char * name):
    QValidator(parent, name),
    mpLineEdit(parent),
    mLastAccepted("")
{
  int h, s, v;

  mSavedColor = mpLineEdit->paletteBackgroundColor();
  mSavedColor.getHsv(&h, &s, &v);

  if (s < 20) s = 20;

  mAcceptableColor.setHsv(240, s, v);
  mErrorColor.setHsv(0, s, v);
}

QValidator::State CQValidator::validate(QString & input, int & /* pos */) const
  {
    if (input == mLastAccepted)
      mpLineEdit->setPaletteBackgroundColor(mSavedColor);
    else
      setColor(Acceptable);

    return Acceptable;
  }

QValidator::State CQValidator::revalidate()
{
  QString Input = mpLineEdit->text();
  int Pos = Input.length();

  return validate(Input, Pos);
}

void CQValidator::saved() const
  {
    const_cast<CQValidator *>(this)->mLastAccepted = mpLineEdit->text();
    mpLineEdit->setPaletteBackgroundColor(mSavedColor);
  }

void CQValidator::force(const QString & input) const
  {
    const_cast<CQValidator *>(this)->mLastAccepted = input;
    setColor(Acceptable);
  }

QValidator::State CQValidator::setColor(const QValidator::State & state) const
  {
    if (state == Invalid)
      mpLineEdit->setPaletteBackgroundColor(mErrorColor);
    else
      mpLineEdit->setPaletteBackgroundColor(mAcceptableColor);

    return state;
  }

CQValidatorNotEmpty::CQValidatorNotEmpty(QLineEdit * parent, const char * name):
    CQValidator(parent, name)
{}

QValidator::State CQValidatorNotEmpty::validate(QString & input, int & pos) const
  {
    if (input != "")
      return CQValidator::validate(input, pos);

    setColor(Invalid);
    return Intermediate;
  }

CQValidatorBound::CQValidatorBound(QLineEdit * parent, const char * name):
    CQValidator(parent, name),
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

    CQValidator::force(input);
  }

CQValidatorDouble::CQValidatorDouble(QLineEdit * parent, const char * name):
    CQValidator(parent, name),
    mpDoubleValidator(new QDoubleValidator(-DBL_MAX, DBL_MAX, DBL_DIG, this))
{}

QValidator::State CQValidatorDouble::validate(QString & input, int & pos) const
  {
    if (mpDoubleValidator->validate(input, pos) == Acceptable)
      return CQValidator::validate(input, pos);

    setColor(Invalid);
    return Intermediate;
  }

void CQValidatorDouble::setRange(const C_FLOAT64 & lowerBound, const C_FLOAT64 & upperBound)
{mpDoubleValidator->setRange(lowerBound, upperBound, DBL_DIG);}

CQValidatorInt::CQValidatorInt(QLineEdit * parent, const char * name):
    CQValidator(parent, name),
    mpIntValidator(new QIntValidator(-LONG_MAX, LONG_MAX, this))
{}

QValidator::State CQValidatorInt::validate(QString & input, int & pos) const
  {
    if (mpIntValidator->validate(input, pos) == Acceptable)
      return CQValidator::validate(input, pos);

    setColor(Invalid);
    return Intermediate;
  }

void CQValidatorInt::setRange(const C_INT32 & lowerBound, const C_INT32 & upperBound)
{mpIntValidator->setRange(lowerBound, upperBound);}
