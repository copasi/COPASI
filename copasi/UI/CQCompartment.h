// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#ifdef COPASI_UNDO
class UndoCompartmentData;
#endif

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQCompartment.h"

#include <vector>

class CCompartment;

class CQCompartment : public CopasiWidget, public Ui::CQCompartment
{
  Q_OBJECT

#ifdef COPASI_UNDO
  friend class DeleteCompartmentCommand;
  friend class CreateNewCompartmentCommand;
//  friend class CompartmentTypeChangeCommand;
#endif

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

  void init();
  void load();
  void save();
  void destroy();
  void loadMetaboliteTable();

private slots:
  void slotBtnNew();
  void slotBtnCopy() {}; //dummy, to bypass warnings from TabWidget connections
  void slotBtnDelete();
  void slotTypeChanged(int type);
  void slotInitialTypeChanged(bool useInitialAssignment);
  void slotExpressionValid(bool valid);
  void slotInitialExpressionValid(bool valid);
  void slotMetaboliteTableCurrentChanged(int row, int col);

  //additional functions for UNDO framework
#ifdef COPASI_UNDO
  void deleteCompartment();
  void addCompartment(UndoCompartmentData *pSData);
  void createNewCompartment();
  void deleteCompartment(UndoCompartmentData *pSData);
  void CompartmentTypeChanged(int type);
#endif
};

#endif // CQCOMPARTMENT_H
