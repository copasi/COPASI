// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/plotUI/BandedGraphWidget.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: tjohann $
//   $Date: 2011/09/05 11:53:01 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef BANDEDGRAPHWIDGET_H
#define BANDEDGRAPHWIDGET_H

#include <QVariant>

#include "copasi/plotUI/ui_BandedGraphWidget.h"

class CCopasiObject;
class CModel;
class CPlotItem;

class BandedGraphWidget : public QWidget, public Ui::BandedGraphWidget
{
  Q_OBJECT

public:
  BandedGraphWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
  ~BandedGraphWidget();

  virtual bool LoadFromCurveSpec(const CPlotItem * curve);
  virtual bool SaveToCurveSpec(CPlotItem * curve) const;
  virtual void setModel(const CModel * model);

protected:
  const CCopasiObject* mpObjectYone;
  const CCopasiObject* mpObjectYtwo;
  const CCopasiObject* mpObjectX;
  const CModel* mpModel;

protected slots:

  virtual void buttonPressedX();
  virtual void buttonPressedY() {buttonPressedYone();};
  void buttonPressedYone();
  void buttonPressedYtwo();
};

#endif // BANDEDGRAPHWIDGET_H
