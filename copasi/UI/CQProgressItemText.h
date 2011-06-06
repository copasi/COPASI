// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQProgressItemText.h,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2011/06/06 16:14:06 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQPROGRESSITEMTEXT_H
#define CQPROGRESSITEMTEXT_H

#include <QVariant>
#include <QLabel>
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
