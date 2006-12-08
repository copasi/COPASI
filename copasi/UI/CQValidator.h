/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQValidator.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/12/08 17:01:16 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CQValidator
#define COPASI_CQValidator

#include <qvalidator.h>
#include <qcolor.h>
#include <qlineedit.h>

#include "copasi.h"

template <typename Type> class CQValidator : public QValidator
  {
    // Operations
  public:
    CQValidator(Type * parent, const char * name = 0):
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

    virtual State validate(QString & input, int & /* pos */) const
      {
        if (input == mLastAccepted)
          mpLineEdit->setPaletteBackgroundColor(mSavedColor);
        else
          setColor(Acceptable);

        return Acceptable;
      }

    virtual State revalidate()
    {
      QString Input = mpLineEdit->text();
      int Pos = Input.length();

      return validate(Input, Pos);
    }

    virtual void saved() const
      {
        const_cast<CQValidator *>(this)->mLastAccepted = mpLineEdit->text();
        mpLineEdit->setPaletteBackgroundColor(mSavedColor);
      }

    virtual void force(const QString & input) const
      {
        const_cast<CQValidator *>(this)->mLastAccepted = input;
        setColor(Acceptable);
      }

  protected:
    State setColor(const State & state) const
      {
        if (state == Invalid)
          mpLineEdit->setPaletteBackgroundColor(mErrorColor);
        else
          mpLineEdit->setPaletteBackgroundColor(mAcceptableColor);

        return state;
      }

    //Attributes
    Type * mpLineEdit;

  private:
    QString mLastAccepted;

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

    void setRange(const C_INT32 & lowerBound, const C_INT32 & upperBound);

    //Attributes
  protected:
    QIntValidator * mpIntValidator;
  };

#endif // COPASI_CQValidator
