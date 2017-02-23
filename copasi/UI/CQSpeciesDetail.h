// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

class UndoSpeciesData;

class CMetab;
class CCompartment;

class CQDependenciesWidget;

class CQSpeciesDetail : public CopasiWidget, public Ui::CQSpeciesDetail
{
  Q_OBJECT

  friend class DeleteSpeciesCommand;
  friend class CreateNewSpeciesCommand;
  friend class SpeciesTypeChangeCommand;
  friend class SpeciesInitialValueLostFocusCommand;

public:
  CQSpeciesDetail(QWidget* parent = 0, const char* name = 0);
  virtual ~CQSpeciesDetail();

  virtual bool leave();
  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual void setFramework(int framework);

  void copy();

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
  CQDependenciesWidget* mpDependencies;

  void load();
  void save();
  void loadReactionTable();

private slots:
  void slotBtnNew();
  void slotBtnCopy();
  void slotBtnDelete();
  void slotCompartmentChanged(int compartment);
  void slotTypeChanged(int type);
  void slotAddNoiseChanged(bool hasNoise);
  void slotInitialTypeChanged(bool useInitialExpression);
  void slotNameLostFocus();
  void slotSwitchToReaction(int row, int column);
  void slotInitialValueLostFocus();

  //additional functions for UNDO framework
  void deleteSpecies();
  void addSpecies(UndoSpeciesData *pSData);
  void createNewSpecies();
  void deleteSpecies(UndoSpeciesData *pSData);
  void speciesTypeChanged(int type);
  void speciesTypeChanged(UndoSpeciesData *pSData, int type);
  void speciesInitialValueLostFocus();
  void speciesInitialValueLostFocus(UndoSpeciesData *pSData);
};

#endif // CQSpeciesDetail_h
