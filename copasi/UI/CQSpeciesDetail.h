// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

class CMetab;
class CCompartment;
class CQScrolledDependenciesWidget;

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

  virtual void setFramework(int framework);

  void copy();

  CMetab* getCurrentMetab();

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();

  virtual bool event(QEvent * pEvent);

protected slots:

private:
  bool mChanged;
  CMetab * mpMetab;
  const CCompartment * mpCurrentCompartment;
  double mInitialNumber;
  double mInitialConcentration;
  CQScrolledDependenciesWidget * mpDependencies;

  void load();
  void save();
  void loadReactionTable();

private slots:
  void slotBtnNew();
  void slotBtnCopy();
  void slotBtnDelete();
  void slotCompartmentChanged(int compartment);
  void slotTypeChanged(const QString & type);
  void slotAddNoiseChanged(bool hasNoise);
  void slotInitialTypeChanged(bool useInitialExpression);
  void slotSwitchToReaction(int row, int column);
  void slotInitialValueLostFocus();

  //additional functions for UNDO framework
  void deleteSpecies();
  /**
   * creates a new species
   * @return boolean indicating whether a compartment was created
   */
  void createNewSpecies();
  void speciesTypeChanged(const QString & type);
};

#endif // CQSpeciesDetail_h
