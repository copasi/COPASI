/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQValidator.h,v $
   $Revision: 1.12.2.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2011/03/08 15:15:53 $
   End CVS Header */

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CQValidator
#define COPASI_CQValidator

#include <qvalidator.h>
#include <qcolor.h>
#include <qlineedit.h>

#include <QtDebug>

#include "copasi.h"

template <typename Type> class CQValidator : public QValidator
{
  // Operations
public:
  CQValidator(Type * parent, QString(Type::*retrieve)(void) const, const char * name = 0):
      QValidator(parent, name),
      mpContainer(parent),
      mRetrieve(retrieve),
      mLastAccepted("")
  {
    int h, s, v;

    QPalette palette = mpContainer->palette();
    QBrush brush = palette.brush(QPalette::Active, QPalette::Base);
    mSavedColor = brush.color();
//    mSavedColor = mpLineEdit->paletteBackgroundColor();
    mSavedColor.getHsv(&h, &s, &v);

    if (s < 20) s = 20;

    mAcceptableColor.setHsv(240, s, v);
    mErrorColor.setHsv(0, s, v);
  }

  virtual State validate(QString & input, int & /* pos */) const
  {
    if (input == mLastAccepted)
      {
        QPalette palette;
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(mSavedColor);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        mpContainer->setPalette(palette);
      }
    else
      setColor(Acceptable);

    /*
        if (input == mLastAccepted)
          mpLineEdit->setPaletteBackgroundColor(mSavedColor);
        else
          setColor(Acceptable);
    */
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
#ifdef DEBUG_UI
    int h, s, v;
#endif

    QPalette palette;
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

#ifdef DEBUG_UI
    qDebug() << "---------------------";
    qDebug() << "-- on CQValidator --";
#endif

    if (state == Invalid)
      {
//      mpLineEdit->setPaletteBackgroundColor(mErrorColor);
        brush.setColor(mErrorColor);

#ifdef DEBUG_UI
        mErrorColor.getHsv(&h, &s, &v);
        qDebug() << "mErrorColor : h = " << h << " - s = " << s << " - v = " << v;
        qDebug() << "---------------------";
#endif
      }
    else
      {
//      mpLineEdit->setPaletteBackgroundColor(mAcceptableColor);
        brush.setColor(mAcceptableColor);

#ifdef DEBUG_UI
        mAcceptableColor.getHsv(&h, &s, &v);
        qDebug() << "mAcceptableColor : h = " << h << " - s = " << s << " - v = " << v;
        qDebug() << "---------------------";
#endif
      }

    palette.setBrush(QPalette::Active, QPalette::Base, brush);
    mpContainer->setPalette(palette);

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
