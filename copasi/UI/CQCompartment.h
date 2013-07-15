// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
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

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQCompartment.h"

#include <vector>

class CCompartment;

class CQCompartment : public CopasiWidget, public Ui::CQCompartment
{
  Q_OBJECT

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

  std::string mKeyOfCopy;

private slots:
  void slotBtnNew();
  void slotBtnCopy(){}; //dummy, to bypass warnings from TabWidget connections
  void slotBtnDelete();
  void slotTypeChanged(int type);
  void slotInitialTypeChanged(bool useInitialAssignment);
  void slotExpressionValid(bool valid);
  void slotInitialExpressionValid(bool valid);
  void slotMetaboliteTableCurrentChanged(int row, int col);
};

#endif // CQCOMPARTMENT_H
