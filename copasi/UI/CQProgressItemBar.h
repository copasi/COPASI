// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef CQPROGRESSITEMBAR_H
#define CQPROGRESSITEMBAR_H

#include <QtCore/QVariant>
#include <QtGui/QLabel>
#include "CQProgressItem.h"
#include "ui_CQProgressItemBar.h"

#include "utilities/CProcessReport.h"
#include "utilities/CVector.h"

class CQProgressItemBar : public CQProgressItem, public Ui::CQProgressItemBar
{
  Q_OBJECT

public:
  CQProgressItemBar(QWidget* parent = 0, const char* name = 0);
  ~CQProgressItemBar();

  virtual bool initFromProcessReportItem(CProcessReportItem * pItem);
  virtual bool process();
  virtual bool reset();

private:
  void (CQProgressItemBar::*mpSetValue)();
  C_FLOAT64 mFactor;
  CCopasiParameter::Value mEnd;
  CCopasiParameter::Value mStart;
  CCopasiParameter::Value mValue;
  C_INT32 mLastSet;
  C_INT32 mCurrentValue;

  virtual void setValueFromDOUBLE();
  virtual void setValueFromINT();
  virtual void setValueFromUINT();
  void destroy();
  void init();
};

#endif // CQPROGRESSITEMBAR_H
