// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQPlotEditWidget.h"

CQPlotEditWidget::CQPlotEditWidget(QWidget* parent /*= NULL*/ , Qt::WindowFlags fl /*= 0*/)
  : QWidget(parent, fl)
{
}

CQPlotEditWidget::~CQPlotEditWidget()
{
}

void CQPlotEditWidget::setModel(const CModel * model)
{
  mpModel = model;
}
