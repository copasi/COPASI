// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQDependenciesWidget.h"
#include "ui_CQDependenciesWidget.h"

#include "copasi/CopasiModelTypes.h"

CQDependenciesWidget::CQDependenciesWidget(QWidget *parent, const char* name, Qt::WindowFlags f)
  : CopasiWidget(parent, name, f)
  , ui(new Ui::CQDependenciesWidget)
  , mVisibleModes(UNKNOWN)
  , mpCompartmentWidget(NULL)
  , mpSpeciesWidget(NULL)
  , mpParameterWidget(NULL)
  , mpReactionWidget(NULL)
  , mpEventWidget(NULL)
  , mpLayout(NULL)
{
  ui->setupUi(this);
  //ui->scrollArea->setAutoFillBackground(true);
  //ui->scrollAreaWidgetContents->setAutoFillBackground(true);
  //setAutoFillBackground(true);
  // sort the background of the control
  setStyleSheet("background-color:transparent;");

#if QT_VERSION >= 0x050000
  ui->scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
#endif
}

CQDependenciesWidget::~CQDependenciesWidget()
{
  delete ui;
}

CQDependencyWidget*
CQDependenciesWidget::clearWidget(CQDependencyWidget* pWidget)
{
  if (pWidget == NULL) return NULL;

  if (mpLayout != NULL)
    mpLayout->removeWidget(pWidget);

  pWidget->setVisible(false);
  pWidget->deleteLater();
  pWidget = NULL;
  return NULL;
}

CQDependencyWidget *
CQDependenciesWidget::addWidget(CDependencyType type)
{
  if (mpLayout == NULL)
    {
      //mpLayout = new QGridLayout(ui->scrollAreaWidgetContents);
      mpLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
      mpLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    }

  CQDependencyWidget *pResult = new CQDependencyWidget(this);
  pResult->setDependencyType(type);
  pResult->setVisible(false);
  //mpLayout->addWidget(pResult);
#if QT_VERSION >= 0x050000
  mpLayout->addWidget(pResult);
#else
  mpLayout->addWidget(pResult, type == REACTION || type == EVENT ? 4 : 1);
#endif
  return pResult;
}

std::set< const CDataObject * > getDependentObjects(CDataObject *pObject)
{
  std::set< const CDataObject * > result;

  if (pObject == NULL) return result;

  CModelEntity* pEntity = dynamic_cast<CModelEntity*>(pObject);

  if (pEntity != NULL)
    {
      pEntity->getDescendants(result, true);
    }
  else
    {
      CReaction* pReaction = dynamic_cast<CReaction*>(pObject);

      if (pReaction != NULL)
        {
          pReaction->getDescendants(result, true);
        }
      else
        {
          CEvaluationTree* pFunction = dynamic_cast<CEvaluationTree*>(pObject);

          if (pFunction != NULL)
            {
              pFunction->getDescendants(result, true);
            }
        }
    }

  return result;
}

void CQDependenciesWidget::loadFrom(CDataObject * pObject)
{
  std::set< const CDataObject * > deletedObjects = getDependentObjects(pObject);
  CModel* pModel = mpDataModel->getModel();

  // this method ought to be more performant
  CDataObject::DataObjectSet dependentReactions;
  CDataObject::DataObjectSet dependentMetabolites;
  CDataObject::DataObjectSet dependentCompartments;
  CDataObject::DataObjectSet dependentModelValues;
  CDataObject::DataObjectSet dependentEvents;
  CDataObject::DataObjectSet dependentEventAssignments;

  pModel->appendDirectDependents(*static_cast< CDataContainer * >(pObject),
                                 dependentReactions,
                                 dependentMetabolites,
                                 dependentCompartments,
                                 dependentModelValues,
                                 dependentEvents,
                                 dependentEventAssignments);

  if (mpCompartmentWidget && (mVisibleModes & COMPARTMENT) == COMPARTMENT)
    mpCompartmentWidget->updateFromDependencies(deletedObjects, dependentCompartments, pModel);

  if (mpSpeciesWidget && (mVisibleModes & SPECIES) == SPECIES)
    mpSpeciesWidget->updateFromDependencies(deletedObjects, dependentMetabolites, pModel);

  if (mpParameterWidget && (mVisibleModes & PARAMETERS) == PARAMETERS)
    mpParameterWidget->updateFromDependencies(deletedObjects, dependentModelValues, pModel);

  if (mpReactionWidget && (mVisibleModes & REACTION) == REACTION)
    mpReactionWidget->updateFromDependencies(deletedObjects, dependentReactions, pModel);

  if (mpEventWidget && (mVisibleModes & EVENT) == EVENT)
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

  ui->mpLabel->setVisible(!haveDependencies());
}

void
CQDependenciesWidget::setResizeTableToRows(bool resizeTable)
{
  if ((mVisibleModes & COMPARTMENT) == COMPARTMENT)
    mpCompartmentWidget->setResizeTableToRows(resizeTable);

  if ((mVisibleModes & SPECIES) == SPECIES)
    mpSpeciesWidget->setResizeTableToRows(resizeTable);

  if ((mVisibleModes & PARAMETERS) == PARAMETERS)
    mpParameterWidget->setResizeTableToRows(resizeTable);

  if ((mVisibleModes & REACTION) == REACTION)
    mpReactionWidget->setResizeTableToRows(resizeTable);

  if ((mVisibleModes & EVENT) == EVENT)
    mpEventWidget->setResizeTableToRows(resizeTable);
}

bool
CQDependenciesWidget::getResizeTableToRows() const
{
  if ((mVisibleModes & COMPARTMENT) == COMPARTMENT)
    return mpCompartmentWidget->getResizeTableToRows();

  if ((mVisibleModes & SPECIES) == SPECIES)
    return mpSpeciesWidget->getResizeTableToRows();

  if ((mVisibleModes & PARAMETERS) == PARAMETERS)
    return mpParameterWidget->getResizeTableToRows();

  if ((mVisibleModes & REACTION) == REACTION)
    return mpReactionWidget->getResizeTableToRows();

  if ((mVisibleModes & EVENT) == EVENT)
    return mpEventWidget->getResizeTableToRows();

  return false;
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

bool
CQDependenciesWidget::enterProtected()
{
  loadFrom(mpObject);

  return CopasiWidget::enterProtected();
}

void
CQDependenciesWidget::setVisibleDependencies(int types)
{
  mVisibleModes = types;

  clearWidget(mpCompartmentWidget);
  clearWidget(mpSpeciesWidget);
  clearWidget(mpParameterWidget);
  clearWidget(mpReactionWidget);
  clearWidget(mpEventWidget);

  if ((mVisibleModes & REACTION) == REACTION)
    {
      mpReactionWidget = addWidget(REACTION);
      //mpLayout->setRowStretch(mpLayout->rowCount() - 1, 3);
    }

  if ((mVisibleModes & EVENT) == EVENT)
    {
      mpEventWidget = addWidget(EVENT);
      //mpLayout->setRowStretch(mpLayout->rowCount() - 1, 3);
    }

  if ((mVisibleModes & PARAMETERS) == PARAMETERS)
    {
      mpParameterWidget = addWidget(PARAMETERS);
      //mpLayout->setRowStretch(mpLayout->rowCount() - 1, 1);
    }

  if ((mVisibleModes & SPECIES) == SPECIES)
    {
      mpSpeciesWidget = addWidget(SPECIES);
      //mpLayout->setRowStretch(mpLayout->rowCount() - 1, 1);
    }

  if ((mVisibleModes & COMPARTMENT) == COMPARTMENT)
    {
      mpCompartmentWidget = addWidget(COMPARTMENT);
      //mpLayout->setRowStretch(mpLayout->rowCount() - 1, 1);
    }

  if (mpLayout != NULL)
    {
      mpLayout->addStretch(2);
      //mpLayout->addItem(
      //  new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding),
      //  mpLayout->rowCount(), 0);
      //mpLayout->setRowStretch(mpLayout->rowCount() - 1, 0);
    }
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
