// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/CopasiModelTypes.h"
#include "CQScrolledDependenciesWidget.h"

CQScrolledDependenciesWidget::CQScrolledDependenciesWidget(QWidget *parent, const char* name, Qt::WindowFlags f)
  : CopasiWidget(parent, name, f)
{
  setupUi(this);
  mpScrollArea->hide();
}

CQScrolledDependenciesWidget::~CQScrolledDependenciesWidget()
{}

// virtual
QSize CQScrolledDependenciesWidget::minimumSizeHint() const
{
  return mpLabel->minimumSizeHint();
}

void CQScrolledDependenciesWidget::loadFrom(const CDataObject * pObject)
{
  mpDependencies->loadFrom(pObject);

  mpLabel->setVisible(!haveDependencies());
  mpScrollArea->setVisible(haveDependencies());
}

void
CQScrolledDependenciesWidget::setResizeTableToRows(bool resizeTable)
{
  mpDependencies->setResizeTableToRows(resizeTable);
}

bool
CQScrolledDependenciesWidget::getResizeTableToRows() const
{
  return mpDependencies->getResizeTableToRows();
}

bool CQScrolledDependenciesWidget::haveDependencies() const
{
  return getNumDependencies() != 0;
}

int CQScrolledDependenciesWidget::getNumDependencies() const
{
  return mpDependencies->getNumDependencies();
}

bool
CQScrolledDependenciesWidget::enterProtected()
{
  return mpDependencies->enterProtected();
}

void
CQScrolledDependenciesWidget::setVisibleDependencies(int types)
{
  mpDependencies->setVisibleDependencies(types);
}

int CQScrolledDependenciesWidget::getVisibleDependencies() const
{
  return mpDependencies->getVisibleDependencies();
}

void CQScrolledDependenciesWidget::setLabelWidth(int width)
{
  mpDependencies->setLabelWidth(width);
}

int CQScrolledDependenciesWidget::getLabelWidth() const
{
  return mpDependencies->getLabelWidth();
}
