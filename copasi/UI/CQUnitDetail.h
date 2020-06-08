// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQUNITDETAIL_H
#define CQUNITDETAIL_H

class UndoGlobalQuantityData;

#include "copasi/utilities/CUnitDefinition.h"
#include "copasi/UI/CQValidatorUnit.h"

#include "ui_CQUnitDetail.h"

#include <string>

#include "copasiWidget.h"

class CQUnitDetail : public CopasiWidget, public Ui::CQUnitDetail
{
  Q_OBJECT

//  friend class DeleteGlobalQuantityCommand;
//  friend class CreateNewGlobalQuantityCommand;
//  friend class GlobalQuantityTypeChangeCommand;

public:
  CQUnitDetail(QWidget* parent = 0, const char* name = 0);
  ~CQUnitDetail();

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();

protected slots:

private:
  std::vector< int > mItemToType;
  CUnitDefinition * mpUnitDefinition;
  CQValidatorUnit * mpExpressionValidator;
  bool mChanged;

  void init();
  void destroy();
  void load();
  void save();

private slots:
  void slotBtnNew();
  void slotBtnCopy();
  void slotBtnDelete();
//  void slotTypeChanged(int type);
//  void slotExpressionValid(bool valid);
//  void slotInitialExpressionValid(bool valid);
//  void slotInitialTypeChanged(bool useInitialAssignment);

//  //additional functions for UNDO framework
//  void deleteGlobalQuantity();
//  void addGlobalQuantity(UndoGlobalQuantityData *pSData);
//  void createNewGlobalQuantity();
//  void deleteGlobalQuantity(UndoGlobalQuantityData *pSData);
//  void globalQuantityTypeChanged(int type);
};

#endif // CQUNITDETAIL_H
