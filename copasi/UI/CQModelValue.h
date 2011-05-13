// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQModelValue.h,v $
//   $Revision: 1.19.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/13 21:46:59 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQMODELVALUE_H
#define CQMODELVALUE_H

class CQExpressionWidget;
class CModelValue;
class CExpression;

#include "ui_CQModelValue.h"

#include <string>

#include "copasiWidget.h"

class CQModelValue : public CopasiWidget, public Ui::CQModelValue
{
  Q_OBJECT

public:
  CQModelValue(QWidget* parent = 0, const char* name = 0);
  ~CQModelValue();

  virtual bool leave();
  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

protected:
  virtual bool enterProtected();

protected slots:


private:
  std::vector< int > mItemToType;
  CModelValue * mpModelValue;
  bool mChanged;
  bool mExpressionValid;
  bool mInitialExpressionValid;

  void init();
  void destroy();
  void load();
  void save();

private slots:
  void slotBtnCommit();
  void slotBtnRevert();
  void slotBtnNew();
  void slotBtnDelete();
  void slotTypeChanged(int type);
  void slotExpressionValid(bool valid);
  void slotInitialExpressionValid(bool valid);
  void slotNameLostFocus();
  void slotInitialTypeChanged(bool useInitialAssignment);
};

#endif // CQMODELVALUE_H
