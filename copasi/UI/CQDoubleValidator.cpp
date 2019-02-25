// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQDoubleValidator.h"

CQDoubleValidator::CQDoubleValidator(QObject * parent)
  : QDoubleValidator(parent)
{
}

CQDoubleValidator::CQDoubleValidator(double bottom, double top, int decimals, QObject * parent)
  : QDoubleValidator(bottom, top, decimals, parent)
{
}

QValidator::State CQDoubleValidator::validate(QString & input, int &) const
{
  const double b = bottom();
  const double t = top();
  const int d = decimals();

  // reject input if it contains a comma
  if (input.contains(","))
    return Invalid;


  // check whether input is a valid double
  bool ok;
  double entered = input.toDouble(&ok);

  if (!ok && !input.size())
    {
      // allow trailing .
      ok = true;
    }
  else if (!ok && (input == "."))
    {
      // allow leading .
      ok = true;
    }

  if (!ok || entered > t || entered < b)
    {
      // reject if out of range
      return Invalid;
    }
  else if (input.contains("."))
    {
      QStringList dec = input.split(".");

      if (dec[1].size() > d)
        {
          // reject multiple dots
          return Invalid;
        }
    }

  // all good
  return Acceptable;
}
