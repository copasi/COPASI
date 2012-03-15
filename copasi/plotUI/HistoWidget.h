// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/HistoWidget.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/03/15 17:04:48 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef HISTOWIDGET_H
#define HISTOWIDGET_H

#include "copasi/plotUI/ui_HistoWidget.h"

class CCopasiObject;
class CModel;
class CPlotItem;

class HistoWidget : public QWidget, public Ui::HistoWidget
{
  Q_OBJECT

public:
  HistoWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
  ~HistoWidget();

  virtual bool LoadFromCurveSpec(const CPlotItem * curve);
  virtual bool SaveToCurveSpec(CPlotItem * curve) const;
  virtual void setModel(const CModel * model);

protected:
  const CCopasiObject* mpObjectX;
  const CModel* mpModel;

protected slots:

  virtual void buttonPressedX();
};

#endif // HISTOWIDGET_H
