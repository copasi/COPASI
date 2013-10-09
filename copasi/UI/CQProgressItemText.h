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

#ifndef CQPROGRESSITEMTEXT_H
#define CQPROGRESSITEMTEXT_H

#include <QtCore/QVariant>
#include <QtGui/QLabel>
#include "CQProgressItem.h"

#include "ui_CQProgressItemText.h"

class CQProgressItemText : public CQProgressItem, public Ui::CQProgressItemText
{
  Q_OBJECT

public:
  CQProgressItemText(QWidget* parent = 0, const char* name = 0);
  ~CQProgressItemText();

  virtual bool initFromProcessReportItem(CProcessReportItem * pItem);
  virtual bool process();
  virtual bool reset();

private:
  void (CQProgressItemText::*mpSetValue)();
  CCopasiParameter::Value mParameterValue;

  virtual void setValueFromDOUBLE();
  virtual void setValueFromINT();
  virtual void setValueFromUINT();
  virtual void setValueFromSTRING();
};

#endif // CQPROGRESSITEMTEXT_H
