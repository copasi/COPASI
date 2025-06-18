// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQCOMPARTMENT_H
#define CQCOMPARTMENT_H

#include <limits>

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQCompartment.h"

#include <vector>

class CCompartment;

class CQCompartment : public CopasiWidget, public Ui::CQCompartment
{
  Q_OBJECT

  friend class DeleteCompartmentCommand;
  friend class CreateNewCompartmentCommand;
  friend class CompartmentChangeCommand;

public:
  CQCompartment(QWidget* parent = 0, const char* name = 0);
  ~CQCompartment();

  void copy();

protected:
  bool enterProtected() override;
  bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CRegisteredCommonName & cn) override;
  bool leaveProtected() override;

protected slots:

private:
  CCompartment * mpCompartment;
  bool mChanged;
  bool mExpressionValid;
  bool mInitialExpressionValid;
  QString mValueUnits;
  QString mRateUnits;

  void init();
  void load();
  void save();
  void destroy();
  void loadMetaboliteTable();

private slots:
  void slotBtnNew();
  void slotBtnCopy(); //dummy, to bypass warnings from TabWidget connections
  void slotBtnDelete();
  void slotTypeChanged(const QString & type);
  void slotAddNoiseChanged(bool hasNoise);
  void slotInitialTypeChanged(bool useInitialAssignment);
  void slotMetaboliteTableCurrentChanged(int row, int col);
  void slotDimesionalityChanged(int);
};

#endif // CQCOMPARTMENT_H
