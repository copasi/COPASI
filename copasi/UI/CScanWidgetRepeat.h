// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetRepeat.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/03/18 12:39:31 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CSCANWIDGETREPEAT_H
#define CSCANWIDGETREPEAT_H

#include "ui_CScanWidgetRepeat.h"

#include "utilities/CCopasiParameterGroup.h"
#include "scan/CScanProblem.h"

class CScanWidgetRepeat : public QWidget, public Ui::CScanWidgetRepeat
{
  Q_OBJECT

public:
  CScanWidgetRepeat(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
  ~CScanWidgetRepeat();

  virtual bool initFromScanItem(CCopasiParameterGroup * pg);
  virtual bool saveToScanItem(CScanProblem * pg) const;

protected slots:
  virtual void languageChange();

private:
  void init();
};

#endif // CSCANWIDGETREPEAT_H
