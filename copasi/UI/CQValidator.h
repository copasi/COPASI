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

#ifndef COPASI_CQValidator
#define COPASI_CQValidator

#include <QValidator>
#include <QColor>
#include <QLineEdit>

#include <QtCore/QtDebug>

#include "copasi/copasi.h"
#include "qtUtilities.h"

template <typename Type> class CQValidator : public QValidator
{
  // Operations
public:
  CQValidator(Type * parent, QString(Type::*retrieve)(void) const, const char * name = 0):
    QValidator(parent),
    mpContainer(parent),
    mRetrieve(retrieve),
    mLastAccepted("")
  {
    setObjectName(QString::fromUtf8(name));
    int h, s, v;

    QPalette palette = mpContainer->palette();
    QBrush brush = palette.brush(QPalette::Active, QPalette::Base);
    mSavedColor = brush.color();
//    mSavedColor = mpLineEdit->paletteBackgroundColor();
    mSavedColor.getHsv(&h, &s, &v);

    if (s < 20) s = 20;
      
    if (isDarkMode())
    {
        s = 128;
        if (v < 128) v = 128;
    }

    mAcceptableColor.setHsv(240, s, v);
    mErrorColor.setHsv(0, s, v);
  }

  virtual State validate(QString & input, int & /* pos */) const
  {
    if (input == mLastAccepted)
      {
        mpContainer->setStyleSheet(QString(mpContainer->metaObject()->className()) + " {background-color:" + mSavedColor.name() + ";}");
      }
    else
      setColor(Acceptable);

    return Acceptable;
  }

  virtual State revalidate()
  {
    QString Input = (*mpContainer.*mRetrieve)();
    int Pos = Input.length();

    return validate(Input, Pos);
  }

  virtual void saved() const
  {
    const_cast<CQValidator *>(this)->mLastAccepted = (*mpContainer.*mRetrieve)();
    const_cast<CQValidator *>(this)->revalidate();
  }

  virtual void force(const QString & input) const
  {
    const_cast<CQValidator *>(this)->mLastAccepted = input;
    setColor(Acceptable);
  }

protected:
  State setColor(const State & state) const
  {
    QString Color;

    switch (state)
      {
        case Invalid:
          Color = mErrorColor.name();
          break;

        case Acceptable:
        case Intermediate:
          Color = mAcceptableColor.name();
          break;
      }

    mpContainer->setStyleSheet(QString(mpContainer->metaObject()->className()) + " {background-color:" + Color + ";}");

    return state;
  }

  //Attributes
  Type * mpContainer;

  /**
   * Method to retrieve the content of the container as a QString
   */
  QString(Type::*mRetrieve)(void) const;

  QString mLastAccepted;

private:
  QColor mSavedColor;

  QColor mAcceptableColor;

  QColor mErrorColor;
};

class CQValidatorNotEmpty : public CQValidator< QLineEdit >
{
  // Operations
public:
  CQValidatorNotEmpty(QLineEdit * parent, const char * name = 0);

  virtual State validate(QString & input, int & pos) const;
};

class CQValidatorBound : public CQValidator< QLineEdit >
{
  // Operations
public:
  CQValidatorBound(QLineEdit * parent, const QString & sign);

  virtual State validate(QString & input, int & pos) const;

  virtual void force(const QString & input) const;

  //Attributes
protected:
  QDoubleValidator * mpDoubleValidator;

  QString mSign;

  QString mValidBound;
};

class CQValidatorDouble : public CQValidator< QLineEdit >
{
  // Operations
public:
  CQValidatorDouble(QLineEdit * parent, const char * name = 0);

  virtual State validate(QString & input, int & pos) const;

  void setRange(const C_FLOAT64 & lowerBound, const C_FLOAT64 & upperBound);

  //Attributes
protected:
  QDoubleValidator * mpDoubleValidator;
};

class CQValidatorInt : public CQValidator< QLineEdit >
{
  // Operations
public:
  CQValidatorInt(QLineEdit * parent, const char * name = 0);

  virtual State validate(QString & input, int & pos) const;

  void setRange(const int & lowerBound, const int & upperBound);

  //Attributes
protected:
  QIntValidator * mpIntValidator;
};

#endif // COPASI_CQValidator
