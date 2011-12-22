// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetScan.h,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/12/22 19:51:58 $
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

#include "copasi/UI/ui_CScanWidgetScan.h"
#include "copasi/UI/CScanItemData.h"

class CModel;
class CCopasiObject;

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

  void initFromObject(const CCopasiObject *obj);

protected:
  // const CModel* mpModel;
  const CCopasiObject* mpObject;

protected slots:

  virtual void slotChooseObject();

private:
  void init();
};

#endif // CSCANWIDGETSCAN_H
