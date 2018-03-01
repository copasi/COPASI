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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQMODELVALUE_H
#define CQMODELVALUE_H

#include <limits>

class CQExpressionWidget;
class CQScrolledDependenciesWidget;
class CModelValue;
class CExpression;

#include "ui_CQModelValue.h"

#include <string>

#include "copasiWidget.h"

class CQModelValue : public CopasiWidget, public Ui::CQModelValue
{
  Q_OBJECT

  friend class DeleteGlobalQuantityCommand;
  friend class CreateNewGlobalQuantityCommand;

public:
  CQModelValue(QWidget* parent = 0, const char* name = 0);
  ~CQModelValue();

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();

  virtual bool event(QEvent * pEvent);

protected slots:

private:
  CModelValue * mpModelValue;
  CQScrolledDependenciesWidget * mpDependencies;
  bool mChanged;

  void init();
  void destroy();
  void load();
  void save();
  CCommonName mObjectCNToCopy;

private slots:
  void slotBtnNew();
  void slotBtnCopy();
  void slotBtnDelete();
  void slotTypeChanged(const QString & type);
  void slotAddNoiseChanged(bool hasNoise);
  void slotInitialTypeChanged(bool useInitialAssignment);
  void slotUnitChanged();

public:
};

#endif // CQMODELVALUE_H
