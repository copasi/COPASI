// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQ_DOUBLE_VALIDATOR_H

#include <QValidator.h>
#include <QString>

class QObject;

/**
 * A double validator, that rejects the comma ',' when entered.
 */
class CQDoubleValidator : public QDoubleValidator
{

public:
  explicit CQDoubleValidator(QObject * parent = nullptr);
  CQDoubleValidator(double bottom, double top, int decimals, QObject *parent = nullptr);

  QValidator::State validate(QString& input, int&) const;
};

#endif // CQ_DOUBLE_VALIDATOR_H
