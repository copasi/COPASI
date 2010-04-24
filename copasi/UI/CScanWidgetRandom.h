// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetRandom.h,v $
//   $Revision: 1.9.2.1 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2010/04/24 01:46:07 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CSCANWIDGETRANDOM_H
#define CSCANWIDGETRANDOM_H

#include "ui_CScanWidgetRandom.h"

#include "utilities/CCopasiParameterGroup.h"
#include "scan/CScanProblem.h"

class CScanWidgetRandom : public QWidget, public Ui::CScanWidgetRandom
{
  Q_OBJECT

public:
  CScanWidgetRandom(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
  ~CScanWidgetRandom();

  virtual bool initFromScanItem(CCopasiParameterGroup * pg, const CModel * model);
  virtual bool saveToScanItem(CScanProblem * pg) const;

  void initFromObject(const CCopasiObject *obj);

protected:
  const CModel* mpModel;
  const CCopasiObject* mpObject;

protected slots:
  virtual void languageChange();

  virtual void slotChooseObject();
  virtual void changeType();

private:
  void init();
};

#endif // CSCANWIDGETRANDOM_H
