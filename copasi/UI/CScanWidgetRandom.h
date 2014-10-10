// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef CSCANWIDGETRANDOM_H
#define CSCANWIDGETRANDOM_H

#include "copasi/UI/ui_CScanWidgetRandom.h"
#include "copasi/UI/CScanItemData.h"

class CCopasiParameterGroup;

class CScanWidgetRandom : public QWidget, public CScanItemData, public Ui::CScanWidgetRandom
{
  Q_OBJECT

public:
  CScanWidgetRandom(QWidget * parent = 0);

  CScanWidgetRandom(const CScanWidgetRandom & src, QWidget * parent = 0);

  virtual ~CScanWidgetRandom();

  virtual void load(const CCopasiParameterGroup * pItem);

  virtual bool save(CCopasiParameterGroup * pItem) const;

  void initFromObject(const CCopasiObject *obj);

protected:
  const CCopasiObject * mpObject;

protected slots:

  virtual void slotChooseObject();
  virtual void changeType();

private:
  void init();
};

#endif // CSCANWIDGETRANDOM_H
