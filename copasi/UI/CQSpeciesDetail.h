// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQSpeciesDetail_h
#define CQSpeciesDetail_h

#include <QtCore/QVariant>

#include "ui_CQSpeciesDetail.h"

class CMetab;
class CCompartment;

class CQSpeciesDetail : public CopasiWidget, public Ui::CQSpeciesDetail
{
  Q_OBJECT

public:
  CQSpeciesDetail(QWidget* parent = 0, const char* name = 0);
  virtual ~CQSpeciesDetail();

  virtual bool leave();
  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual void setFramework(int framework);

protected:
  virtual bool enterProtected();

protected slots:

private:
  bool mChanged;
  CMetab * mpMetab;
  const CCompartment * mpCurrentCompartment;
  std::vector< int > mItemToType;
  double mInitialNumber;
  double mInitialConcentration;
  bool mExpressionValid;
  bool mInitialExpressionValid;

  void load();
  void save();
  void loadReactionTable();

private slots:
  void slotBtnNew();
  void slotBtnCopy();
  void slotBtnDelete();
  void slotCompartmentChanged(int compartment);
  void slotTypeChanged(int type);
  void slotInitialTypeChanged(bool useInitialExpression);
  void slotNameLostFocus();
  void slotExpressionValid(bool valid);
  void slotInitialExpressionValid(bool valid);
  void slotSwitchToReaction(int row, int column);
  void slotInitialValueLostFocus();
};

#endif // CQSpeciesDetail_h
