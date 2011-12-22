// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetRandom.h,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/12/22 19:51:57 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
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
  const CCopasiObject* mpObject;

protected slots:

  virtual void slotChooseObject();
  virtual void changeType();

private:
  void init();
};

#endif // CSCANWIDGETRANDOM_H
