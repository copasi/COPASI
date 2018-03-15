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

#ifdef COPASI_UNDO
class UndoGlobalQuantityData;
#endif

#include "copasi/utilities/CUnitDefinition.h"
#include "UI/CQValidatorUnit.h"

#include "ui_CQUnitDetail.h"

#include <string>

#include "copasiWidget.h"

class CQUnitDetail : public CopasiWidget, public Ui::CQUnitDetail
{
  Q_OBJECT

#ifdef COPASI_UNDO
//  friend class DeleteGlobalQuantityCommand;
//  friend class CreateNewGlobalQuantityCommand;
//  friend class GlobalQuantityTypeChangeCommand;
#endif

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
//#ifdef COPASI_UNDO
//  void deleteGlobalQuantity();
//  void addGlobalQuantity(UndoGlobalQuantityData *pSData);
//  void createNewGlobalQuantity();
//  void deleteGlobalQuantity(UndoGlobalQuantityData *pSData);
//  void globalQuantityTypeChanged(int type);
//#endif
};

#endif // CQUNITDETAIL_H
