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

class UndoCompartmentData;
#include <copasi/undoFramework/CCopasiUndoCommand.h>
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

  virtual bool leave();
  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  void copy();

protected:
  virtual bool enterProtected();

protected slots:

private:
  std::vector< int > mItemToType;
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
  void slotTypeChanged(int type);
  void slotAddNoiseChanged(bool addNoise);
  void slotInitialTypeChanged(bool useInitialAssignment);
  void slotMetaboliteTableCurrentChanged(int row, int col);
  void slotDimesionalityChanged(int);

  //additional functions for UNDO framework
  void deleteCompartment();
  void addCompartment(UndoCompartmentData *pSData);
  void createNewCompartment();
  void deleteCompartment(UndoCompartmentData *pSData);
  bool changeValue(const std::string& key,
                   CCopasiUndoCommand::Type type,
                   const QVariant& newValue,
                   double iValue = std::numeric_limits<double>::quiet_NaN(),
                   UndoCompartmentData *pUndoData = NULL);
};

#endif // CQCOMPARTMENT_H
