// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef CSCANWIDGETSCAN_H
#define CSCANWIDGETSCAN_H

#include "copasi/UI/ui_CScanWidgetScan.h"
#include "copasi/UI/CScanItemData.h"

class CModel;
class CDataObject;

class CCopasiParameterGroup;

class CScanWidgetScan : public QWidget, public CScanItemData, public Ui::CScanWidgetScan
{
  Q_OBJECT

public:
  CScanWidgetScan(QWidget * parent = 0);

  CScanWidgetScan(const CScanWidgetScan & src, QWidget * parent = 0);

  virtual ~CScanWidgetScan();

  virtual void load(const CCopasiParameterGroup * pItem);

  virtual bool save(CCopasiParameterGroup * pItem) const;

  void initFromObject(const CDataObject *obj);

protected:
  // const CModel* mpModel;
  const CDataObject* mpObject;

protected slots:

  virtual void slotChooseObject();
  virtual void slotIntervalsChecked();
  virtual void slotValuesChecked();

private:
  void init();
};

#endif // CSCANWIDGETSCAN_H
