// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetScan.h,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/17 13:10:24 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CSCANWIDGETSCAN_H
#define CSCANWIDGETSCAN_H

#include "ui_CScanWidgetScan.h"

#include "utilities/CCopasiParameterGroup.h"
#include "scan/CScanProblem.h"

class CScanWidgetScan : public QWidget, public Ui::CScanWidgetScan
{
  Q_OBJECT

public:
  CScanWidgetScan(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
  ~CScanWidgetScan();

  virtual bool initFromScanItem(CCopasiParameterGroup * pg, const CModel * model);
  virtual bool saveToScanItem(CScanProblem * pg) const;

  void initFromObject(const CCopasiObject *obj);

protected:
  const CModel* mpModel;
  const CCopasiObject* mpObject;

protected slots:

  virtual void slotChooseObject();

private:
  void init();
};

#endif // CSCANWIDGETSCAN_H
