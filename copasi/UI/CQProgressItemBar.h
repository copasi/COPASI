// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef CQPROGRESSITEMBAR_H
#define CQPROGRESSITEMBAR_H

#include <QtCore/QVariant>
#include <QLabel>

#include "CQProgressItem.h"
#include "ui_CQProgressItemBar.h"

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
  double mFactor;
  void * mpEnd;
  void * mpStart;
  void * mpValue;
  int mLastSet;
  int mCurrentValue;

  virtual void setValueFromDOUBLE();
  virtual void setValueFromINT();
  virtual void setValueFromUINT();
  void destroy();
  void init();
};

#endif // CQPROGRESSITEMBAR_H
