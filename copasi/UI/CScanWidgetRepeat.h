// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetRepeat.h,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/12/22 19:51:58 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CSCANWIDGETREPEAT_H
#define CSCANWIDGETREPEAT_H

#include "copasi/UI/ui_CScanWidgetRepeat.h"
#include "copasi/UI/CScanItemData.h"

class CCopasiParameterGroup;

class CScanWidgetRepeat : public QWidget, public CScanItemData, public Ui::CScanWidgetRepeat
{
  Q_OBJECT

public:
  CScanWidgetRepeat(QWidget * parent = 0);

  CScanWidgetRepeat(const CScanWidgetRepeat & src, QWidget * parent = 0);

  virtual ~CScanWidgetRepeat();

  virtual void load(const CCopasiParameterGroup * pItem);

  virtual bool save(CCopasiParameterGroup * pItem) const;

protected slots:

private:
  void init();
};

#endif // CSCANWIDGETREPEAT_H
