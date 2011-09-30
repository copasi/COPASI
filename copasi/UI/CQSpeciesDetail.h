// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSpeciesDetail.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:39:39 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
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
  bool mInitialNumberLastChanged;
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
  void slotBtnCommit();
  void slotBtnRevert();
  void slotBtnNew();
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
