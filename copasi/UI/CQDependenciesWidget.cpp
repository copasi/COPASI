// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include <QScrollArea>

#include "CQDependenciesWidget.h"
#include "ui_CQDependenciesWidget.h"

#include "copasi/CopasiModelTypes.h"

CQDependenciesWidget::CQDependenciesWidget(QWidget *parent, const char* name, Qt::WindowFlags f)
  : CopasiWidget(parent, name, f)
  , mVisibleModes(UNKNOWN)
{
  setupUi(this);

  mpCompartmentWidget->setDependencyType(COMPARTMENT);
  mpSpeciesWidget->setDependencyType(SPECIES);
  mpParameterWidget->setDependencyType(PARAMETERS);
  mpReactionWidget->setDependencyType(REACTION);
  mpEventWidget->setDependencyType(EVENT);

#ifndef DARWIN
//  setStyleSheet("background-color:transparent;");
#endif
}

CQDependenciesWidget::~CQDependenciesWidget()
{}

std::set< const CDataObject * > getDependentObjects(const CDataObject *pObject)
{
  std::set< const CDataObject * > result;

  if (pObject == NULL) return result;

  const CModelEntity * pEntity = dynamic_cast< const CModelEntity * >(pObject);

  if (pEntity != NULL)
    {
      pEntity->getDescendants(result, true);
    }
  else
    {
      const CReaction * pReaction = dynamic_cast< const CReaction * >(pObject);

      if (pReaction != NULL)
        {
          pReaction->getDescendants(result, true);
        }
      else
        {
          const CEvaluationTree * pFunction = dynamic_cast< const CEvaluationTree * >(pObject);

          if (pFunction != NULL)
            {
              pFunction->getDescendants(result, true);
            }
        }
    }

  return result;
}

void CQDependenciesWidget::loadFrom(const CDataObject * pObject)
{
  if (mpDataModel == NULL)
    initContext();

  std::set< const CDataObject * > deletedObjects = getDependentObjects(pObject);
  CModel* pModel = mpDataModel->getModel();

  // this method ought to be more performant
  CDataObject::DataObjectSet dependentReactions;
  CDataObject::DataObjectSet dependentMetabolites;
  CDataObject::DataObjectSet dependentCompartments;
  CDataObject::DataObjectSet dependentModelValues;
  CDataObject::DataObjectSet dependentEvents;
  CDataObject::DataObjectSet dependentEventAssignments;

  pModel->appendDirectDependents(*static_cast< const CDataContainer * >(pObject),
                                 dependentReactions,
                                 dependentMetabolites,
                                 dependentCompartments,
                                 dependentModelValues,
                                 dependentEvents,
                                 dependentEventAssignments);

  if (mVisibleModes & COMPARTMENT)
    mpCompartmentWidget->updateFromDependencies(deletedObjects, dependentCompartments, pModel);

  if (mVisibleModes & SPECIES)
    mpSpeciesWidget->updateFromDependencies(deletedObjects, dependentMetabolites, pModel);

  if (mVisibleModes & PARAMETERS)
    mpParameterWidget->updateFromDependencies(deletedObjects, dependentModelValues, pModel);

  if (mVisibleModes & REACTION)
    mpReactionWidget->updateFromDependencies(deletedObjects, dependentReactions, pModel);

  if (mVisibleModes & EVENT)
    {
      std::set< const CDataObject * >::iterator it = dependentEventAssignments.begin();
      std::set< const CDataObject * >::iterator end = dependentEventAssignments.end();

      for (; it != end; ++it)
        {
          const CDataObject * pObject = *it;
          dependentEvents.insert(pObject->getObjectParent()->getObjectParent());
        }

      mpEventWidget->updateFromDependencies(deletedObjects, dependentEvents, pModel);
    }
}

void
CQDependenciesWidget::setResizeTableToRows(bool resizeTable)
{
  mpCompartmentWidget->setResizeTableToRows(resizeTable);
  mpSpeciesWidget->setResizeTableToRows(resizeTable);
  mpParameterWidget->setResizeTableToRows(resizeTable);
  mpReactionWidget->setResizeTableToRows(resizeTable);
  mpEventWidget->setResizeTableToRows(resizeTable);
}

bool
CQDependenciesWidget::getResizeTableToRows() const
{
  return mpCompartmentWidget->getResizeTableToRows();
}

bool CQDependenciesWidget::haveDependencies() const
{
  return getNumDependencies() != 0;
}

int CQDependenciesWidget::getNumDependencies() const
{
  int count = 0;

  if ((mVisibleModes & COMPARTMENT) == COMPARTMENT)
    count += mpCompartmentWidget->getNumDependencies();

  if ((mVisibleModes & SPECIES) == SPECIES)
    count += mpSpeciesWidget->getNumDependencies();

  if ((mVisibleModes & PARAMETERS) == PARAMETERS)
    count += mpParameterWidget->getNumDependencies();

  if ((mVisibleModes & REACTION) == REACTION)
    count += mpReactionWidget->getNumDependencies();

  if ((mVisibleModes & EVENT) == EVENT)
    count += mpEventWidget->getNumDependencies();

  return count;
}

bool CQDependenciesWidget::enterProtected()
{
  loadFrom(mpObject);

  return CopasiWidget::enterProtected();
}

void
CQDependenciesWidget::setVisibleDependencies(int types)
{
  mVisibleModes = types;

  mpCompartmentWidget->setVisible(mVisibleModes & COMPARTMENT);
  mpSpeciesWidget->setVisible(mVisibleModes & SPECIES);
  mpParameterWidget->setVisible(mVisibleModes & PARAMETERS);
  mpReactionWidget->setVisible(mVisibleModes & REACTION);
  mpEventWidget->setVisible(mVisibleModes & EVENT);
}

int CQDependenciesWidget::getVisibleDependencies() const
{
  return mVisibleModes;
}

void CQDependenciesWidget::setLabelWidth(int width)
{
  if ((mVisibleModes & COMPARTMENT) == COMPARTMENT)
    mpCompartmentWidget->setLabelWidth(width);

  if ((mVisibleModes & SPECIES) == SPECIES)
    mpSpeciesWidget->setLabelWidth(width);

  if ((mVisibleModes & PARAMETERS) == PARAMETERS)
    mpParameterWidget->setLabelWidth(width);

  if ((mVisibleModes & REACTION) == REACTION)
    mpReactionWidget->setLabelWidth(width);

  if ((mVisibleModes & EVENT) == EVENT)
    mpEventWidget->setLabelWidth(width);
}

int CQDependenciesWidget::getLabelWidth() const
{
  if ((mVisibleModes & COMPARTMENT) == COMPARTMENT)
    return mpCompartmentWidget->getLabelWidth();

  if ((mVisibleModes & SPECIES) == SPECIES)
    return mpSpeciesWidget->getLabelWidth();

  if ((mVisibleModes & PARAMETERS) == PARAMETERS)
    return mpParameterWidget->getLabelWidth();

  if ((mVisibleModes & REACTION) == REACTION)
    return mpReactionWidget->getLabelWidth();

  if ((mVisibleModes & EVENT) == EVENT)
    return mpEventWidget->getLabelWidth();

  return -1;
}
