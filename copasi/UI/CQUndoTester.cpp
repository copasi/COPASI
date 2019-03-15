// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include <copasi/UI/CQUndoTester.h>

#include <QTimer>

#include <copasi/CopasiTypes.h>
#include <copasi/commandline/COptions.h>
#include <copasi/UI/CopasiGuiTypes.h>
#include "copasi/UI/CQCopasiApplication.h"

CQUndoTester::CQUndoTester(CQCopasiApplication * app,
                           ListViews* pListViews)
  : QObject(app)
  , mpApp(app)
  , mpListViews(pListViews)
  , mpUndoStack(NULL)
  , mpTabModel(NULL)
  , mpTabSpecies(NULL)
  , mpTabCompartments(NULL)
  , mpTabModelValues(NULL)
  , mpTabEvents(NULL)
  , mpTabReactions(NULL)
  , mpDetailComp(NULL)
  , mpDetailSpecies(NULL)
  , mpDetailMV(NULL)
  , mpDetailEvent(NULL)
  , mpDetailReaction(NULL)
  , mpDmWidgetComp(NULL)
  , mpDmWidgetSpecies(NULL)
  , mpDmWidgetModelValues(NULL)
  , mpDmWidgetEvents(NULL)
  , mpDmWidgetReactions(NULL)
  , mpDmWidgetOverview(NULL)
  , mpDmCompartments(NULL)
  , mpDmSpecies(NULL)
  , mpDmModelValues(NULL)
  , mpDmEvents(NULL)
  , mpDmReactions(NULL)
  , mpDmOverview(NULL)
  , mpCompartment(NULL)
  , mpSpecies(NULL)
  , mpModelValue(NULL)
  , mpEvent(NULL)
  , mpEventAssignment(NULL)
  , mpReaction(NULL)
{
  if (mpListViews == NULL)
    mpListViews = mpApp->getMainWindow()->getMainWidget();

  if (mpListViews != NULL)
    mpUndoStack = mpListViews->getDataModel()->getUndoStack();

  assert(mpUndoStack != NULL);

  /*
  mpTabModel = qobject_cast<CQTabWidget*>(mpListViews->findWidgetFromId(CCopasiUndoCommand::MODEL));
  mpTabSpecies = qobject_cast<CQTabWidget*>(mpListViews->findTabWidgetFromId(CCopasiUndoCommand::SPECIES));
  mpTabCompartments = qobject_cast<CQTabWidget*>(mpListViews->findTabWidgetFromId(CCopasiUndoCommand::COMPARTMENTS));
  mpTabModelValues = qobject_cast<CQTabWidget*>(mpListViews->findTabWidgetFromId(CCopasiUndoCommand::GLOBALQUANTITIES));
  mpTabEvents = qobject_cast<CQTabWidget*>(mpListViews->findTabWidgetFromId(CCopasiUndoCommand::EVENTS));
  mpTabReactions = qobject_cast<CQTabWidget*>(mpListViews->findTabWidgetFromId(CCopasiUndoCommand::REACTIONS));

  mpDetailModel = qobject_cast<CQModelWidget*>(mpTabModel->getTab(0));
  mpDetailComp = qobject_cast<CQCompartment*>(mpTabCompartments->getTab(0));
  mpDetailSpecies = qobject_cast<CQSpeciesDetail*>(mpTabSpecies->getTab(0));
  mpDetailMV = qobject_cast<CQModelValue*>(mpTabModelValues->getTab(0));
  mpDetailEvent = qobject_cast<CQEventWidget1*>(mpTabEvents->getTab(0));
  mpDetailReaction = qobject_cast<ReactionsWidget1*>(mpTabReactions->getTab(0));

  mpDmWidgetComp = qobject_cast<CQCompartmentsWidget*>(mpListViews->findWidgetFromId(CCopasiUndoCommand::COMPARTMENTS));
  mpDmWidgetSpecies = qobject_cast<CQSpeciesWidget*>(mpListViews->findWidgetFromId(CCopasiUndoCommand::SPECIES));
  mpDmWidgetModelValues = qobject_cast<CQGlobalQuantitiesWidget*>(mpListViews->findWidgetFromId(CCopasiUndoCommand::GLOBALQUANTITIES));
  mpDmWidgetEvents = qobject_cast<CQEventsWidget*>(mpListViews->findWidgetFromId(CCopasiUndoCommand::EVENTS));
  mpDmWidgetReactions = qobject_cast<CQReactionsWidget*>(mpListViews->findWidgetFromId(CCopasiUndoCommand::REACTIONS));
  mpDmWidgetOverview = qobject_cast<CQParameterOverviewWidget*>(mpListViews->findWidgetFromId(CCopasiUndoCommand::PARAMETER_OVERVIEW));

  mpDmCompartments = dynamic_cast<CQCompartmentDM*>(mpDmWidgetComp->getCqDataModel());
  mpDmSpecies = dynamic_cast<CQSpecieDM*>(mpDmWidgetSpecies->getCqDataModel());
  mpDmModelValues = dynamic_cast<CQGlobalQuantityDM*>(mpDmWidgetModelValues->getCqDataModel());
  mpDmEvents = dynamic_cast<CQEventDM*>(mpDmWidgetEvents->getCqDataModel());
  mpDmReactions = dynamic_cast<CQReactionDM*>(mpDmWidgetReactions->getCqDataModel());
  mpDmOverview = dynamic_cast<CQParameterOverviewDM*>(mpDmWidgetOverview->getCqDataModel());
  */
}

CQUndoTester::~CQUndoTester()
{
}

void CQUndoTester::startTestIn(int msecs)
{
  QTimer::singleShot(msecs, this, SLOT(test()));
}

void CQUndoTester::test()
{

  QString options = FROM_UTF8(COptions::getEnvironmentVariable("COPASI_TEST_UNDO"));

  if (options.isEmpty()) options = "all";

  if (options.contains("focus"))
    {
      mpApp->connect(mpApp, SIGNAL(focusChanged(QWidget*, QWidget*)),
                     this, SLOT(focusChange(QWidget*, QWidget*)));
    }

  if (options.contains("all") || options.contains("model"))
    testModelDetail();

  if (options.contains("all") || options.contains("compartment"))
    testCompartmentDetail();

  if (options.contains("all") || options.contains("species"))
    testSpeciesDetail();

  if (options.contains("all") || options.contains("modelvalue"))
    testModelValueDetail();

  if (options.contains("all") || options.contains("event"))
    testEventDetail();

  if (options.contains("all") || options.contains("reaction"))
    testReactionDetail();

  if (options.contains("all") || options.contains("dm"))
    {
      testCompartmentDM();
      testSpeciesDM();
      testModelValueDM();
      testEventDM();
      testReactionDM();
    }

  if (options.contains("all") || options.contains("overview"))
    testOverviewWidget();

  if (options.contains("repeat"))
    {
      // undo / redo a couple of times
      for (int i = 0; i < 10; ++i)
        {
          while (mpUndoStack->canUndo())
            mpUndoStack->undo();

          while (mpUndoStack->canRedo())
            mpUndoStack->redo();
        }
    }
}

void CQUndoTester::testModelDetail()
{
  CModel* pModel = (*CRootContainer::getDatamodelList())[0].getModel();

#ifdef XXXX
  mpUndoStack->push(
    new EntityRenameCommand(
      pModel,
      pModel->getObjectName(),
      "model1",
      mpTabModel)
  );

  // change time units
  mpUndoStack->push(
    new ModelChangeCommand(CCopasiUndoCommand::MODEL_TIME_UNIT_CHANGE,
                           FROM_UTF8(pModel->getTimeUnitName()),
                           "h",
                           mpDetailModel)
  );

  // change length units
  mpUndoStack->push(
    new ModelChangeCommand(CCopasiUndoCommand::MODEL_LENGTH_UNIT_CHANGE,
                           FROM_UTF8(pModel->getLengthUnitName()),
                           "m",
                           mpDetailModel)
  );

  // change area units
  mpUndoStack->push(
    new ModelChangeCommand(CCopasiUndoCommand::MODEL_AREA_UNIT_CHANGE,
                           FROM_UTF8(pModel->getAreaUnitName()),
                           "m*m",
                           mpDetailModel)
  );

  // change volume units
  mpUndoStack->push(
    new ModelChangeCommand(CCopasiUndoCommand::MODEL_VOLUME_UNIT_CHANGE,
                           FROM_UTF8(pModel->getVolumeUnitName()),
                           "l",
                           mpDetailModel)
  );

  // change initial time
  mpUndoStack->push(
    new ModelChangeCommand(CCopasiUndoCommand::MODEL_INITIAL_TIME_CHANGE,
                           pModel->getInitialTime(),
                           10,
                           mpDetailModel)
  );

  // change stochastic interpretation
  mpUndoStack->push(
    new ModelChangeCommand(CCopasiUndoCommand::MODEL_STOCHASTIC_CORRECTION_CHANGE,
                           pModel->getModelType() == CModel::ModelType::deterministic,
                           pModel->getModelType() != CModel::ModelType::deterministic,
                           mpDetailModel)
  );
#endif // XXXX
}

void CQUndoTester::testCompartmentDetail()
{
#ifdef XXXX
  createCompartment();

  // rename
  mpUndoStack->push(
    new EntityRenameCommand(
      mpCompartment,
      mpCompartment->getObjectName(),
      "vol",
      mpTabCompartments)
  );

  // change initial value
  mpUndoStack->push(
    new CompartmentChangeCommand(CCopasiUndoCommand::COMPARTMENT_INITIAL_VOLUME_CHANGE,
                                 mpCompartment->getInitialValue(),
                                 10,
                                 mpCompartment,
                                 mpDetailComp
                                )
  );

  // change initial expression
  mpUndoStack->push(
    new CompartmentChangeCommand(CCopasiUndoCommand::COMPARTMENT_INITIAL_EXPRESSION_CHANGE,
                                 FROM_UTF8(mpCompartment->getInitialExpression()),
                                 "10 * 10",
                                 mpCompartment,
                                 mpDetailComp,
                                 mpCompartment->getInitialValue()
                                )
  );

  // change type
  mpUndoStack->push(
    new CompartmentChangeCommand(CCopasiUndoCommand::COMPARTMENT_SIMULATION_TYPE_CHANGE,
                                 static_cast<unsigned C_INT32>(mpCompartment->getStatus()),
                                 static_cast<unsigned C_INT32>(CModelEntity::Status::ASSIGNMENT),
                                 mpCompartment,
                                 mpDetailComp,
                                 static_cast<CModelEntity*>(mpCompartment)->getInitialValue()
                                )
  );

  // change expression
  mpUndoStack->push(
    new CompartmentChangeCommand(CCopasiUndoCommand::COMPARTMENT_EXPRESSION_CHANGE,
                                 FROM_UTF8(mpCompartment->getInitialExpression()),
                                 "0/0",
                                 mpCompartment,
                                 mpDetailComp,
                                 static_cast<CModelEntity*>(mpCompartment)->getInitialValue()
                                )
  );

  deleteCompartment();
#endif
}

void CQUndoTester::testSpeciesDetail()
{
#ifdef XXXX
  createSpecies();

  // rename species
  mpUndoStack->push(
    new EntityRenameCommand(
      mpSpecies,
      mpSpecies->getObjectName(),
      "A",
      mpTabSpecies)
  );

  // change initial value
  mpUndoStack->push(
    new SpeciesChangeCommand(CCopasiUndoCommand::SPECIES_INITAL_PARTICLENUMBER_CHANGE,
                             mpSpecies->getInitialValue(), 10, mpSpecies,
                             mpDetailSpecies)
  );

  // change initial concentration
  mpUndoStack->push(
    new SpeciesChangeCommand(CCopasiUndoCommand::SPECIES_INITAL_CONCENTRATION_CHANGE,
                             mpSpecies->getInitialConcentration(), 10, mpSpecies,
                             mpDetailSpecies)
  );

  // change initial assignment expression
  mpUndoStack->push(
    new SpeciesChangeCommand(CCopasiUndoCommand::SPECIES_INITIAL_EXPRESSION_CHANGE,
                             "",
                             QString("2 * <%1> + 10")
                             .arg(mpSpecies->getModel()->getValueReference()->getCN().c_str()),
                             mpSpecies,
                             mpDetailSpecies, mpSpecies->getInitialValue())
  );

  // change type this time by name
  mpUndoStack->push(
    new SpeciesChangeCommand(CCopasiUndoCommand::SPECIES_SIMULATION_TYPE_CHANGE,
                             FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::REACTIONS]),
                             FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::FIXED]),
                             mpSpecies,
                             mpDetailSpecies, mpSpecies->getInitialValue()
                            )
  );

  // change type by number
  mpUndoStack->push(
    new SpeciesChangeCommand(CCopasiUndoCommand::SPECIES_SIMULATION_TYPE_CHANGE,
                             static_cast<unsigned C_INT32>(CModelEntity::Status::FIXED),
                             static_cast<unsigned C_INT32>(CModelEntity::Status::ASSIGNMENT),
                             mpSpecies,
                             mpDetailSpecies, mpSpecies->getInitialValue()
                            )
  );

  // change assignment expression
  mpUndoStack->push(
    new SpeciesChangeCommand(CCopasiUndoCommand::SPECIES_EXPRESSION_CHANGE,
                             "",
                             QString("sin(<%1>)")
                             .arg(mpSpecies->getModel()->getValueReference()->getCN().c_str()),
                             mpSpecies,
                             mpDetailSpecies, mpSpecies->getInitialValue())
  );

  deleteSpecies();

#endif
}

void CQUndoTester::testModelValueDetail()
{
  createModelValue();

#ifdef XXXX
  // rename
  mpUndoStack->push(
    new EntityRenameCommand(
      mpModelValue,
      mpModelValue->getObjectName(),
      "param1",
      mpTabModelValues)
  );

  // change initial value
  mpUndoStack->push(
    new GlobalQuantityChangeCommand(CCopasiUndoCommand::GLOBALQUANTITY_INITIAL_VALUE_CHANGE,
                                    mpModelValue->getInitialValue(),
                                    10,
                                    mpModelValue,
                                    mpDetailMV
                                   )
  );

  // change initial expression
  mpUndoStack->push(
    new GlobalQuantityChangeCommand(CCopasiUndoCommand::GLOBALQUANTITY_INITIAL_EXPRESSION_CHANGE,
                                    FROM_UTF8(mpModelValue->getInitialExpression()),
                                    "10 * 10",
                                    mpModelValue,
                                    mpDetailMV,
                                    mpModelValue->getInitialValue()
                                   )
  );

  // change type
  mpUndoStack->push(
    new GlobalQuantityChangeCommand(CCopasiUndoCommand::GLOBALQUANTITY_SIMULATION_TYPE_CHANGE,
                                    static_cast<int>(mpModelValue->getStatus()),
                                    static_cast<int>(CModelEntity::Status::ASSIGNMENT),
                                    mpModelValue,
                                    mpDetailMV,
                                    static_cast<CModelEntity*>(mpModelValue)->getInitialValue()
                                   )
  );

  // change expression
  mpUndoStack->push(
    new GlobalQuantityChangeCommand(CCopasiUndoCommand::GLOBALQUANTITY_EXPRESSION_CHANGE,
                                    FROM_UTF8(mpModelValue->getInitialExpression()),
                                    "0/0",
                                    mpModelValue,
                                    mpDetailMV,
                                    static_cast<CModelEntity*>(mpModelValue)->getInitialValue()
                                   )
  );

  deleteModelValue();
#endif // XXXX
}

void CQUndoTester::testEventDetail()
{
  createEvent();

#ifdef XXXX
  // rename event
  mpUndoStack->push(
    new EntityRenameCommand(
      mpEvent,
      mpEvent->getObjectName(),
      "eventA",
      mpTabEvents)
  );

  // change trigger expression
  CModel * model = const_cast<CModel*>(mpEvent->getObjectDataModel()->getModel());

  mpUndoStack->push(
    new EventChangeCommand(CCopasiUndoCommand::EVENT_TRIGGER_EXPRESSION_CHANGE,
                           FROM_UTF8(mpEvent->getTriggerExpression()),
                           QString("<%1> > 10").arg(model->getValueReference()->getCN().c_str()),
                           mpEvent,
                           mpDetailEvent)
  );

  mpUndoStack->push(
    new EventChangeCommand(CCopasiUndoCommand::EVENT_TRIGGER_INITIALTIME_CHANGE,
                           mpEvent->getFireAtInitialTime(),
                           !mpEvent->getFireAtInitialTime(),
                           mpEvent,
                           mpDetailEvent)
  );

  mpUndoStack->push(
    new EventChangeCommand(CCopasiUndoCommand::EVENT_TRIGGER_PERSISTENT_CHANGE,
                           mpEvent->getPersistentTrigger(),
                           !mpEvent->getPersistentTrigger(),
                           mpEvent,
                           mpDetailEvent)
  );

  mpUndoStack->push(
    new EventChangeCommand(CCopasiUndoCommand::EVENT_DELAY_TYPE_CHANGE,
                           mpEvent->getDelayAssignment(),
                           !mpEvent->getDelayAssignment(),
                           mpEvent,
                           mpDetailEvent)
  );

  // change delay expression
  mpUndoStack->push(
    new EventChangeCommand(CCopasiUndoCommand::EVENT_DELAY_EXPRESSION_CHANGE,
                           FROM_UTF8(mpEvent->getDelayExpression()),
                           QString("10"),
                           mpEvent,
                           mpDetailEvent)
  );

  // change priority expression
  mpUndoStack->push(
    new EventChangeCommand(CCopasiUndoCommand::EVENT_PRIORITY_EXPRESSION_CHANGE,
                           FROM_UTF8(mpEvent->getPriorityExpression()),
                           QString("10"),
                           mpEvent,
                           mpDetailEvent)
  );

  createCompartment();
  // add assignment
  mpUndoStack->push(
    new EventChangeCommand(
      CCopasiUndoCommand::EVENT_ASSIGNMENT_ADDED,
      "",
      FROM_UTF8(mpCompartment->getKey()),
      mpEvent,
      mpDetailEvent,
      mpCompartment->getKey(),
      "2"
    )
  );

  //change expression
  mpUndoStack->push(
    new EventChangeCommand(
      CCopasiUndoCommand::EVENT_ASSIGNMENT_EXPRESSION_CHANGE,
      "2",
      "2*2",
      mpEvent,
      mpDetailEvent,
      mpEvent->getAssignments()[0].getObjectName(),
      mpEvent->getAssignments()[0].getObjectName()
    )
  );

  // remove assignment
  mpUndoStack->push(new EventChangeCommand(
                      CCopasiUndoCommand::EVENT_ASSIGNMENT_REMOVED,
                      FROM_UTF8(mpCompartment->getKey()), // target key
                      "",
                      mpEvent,
                      mpDetailEvent,
                      mpEvent->getAssignments()[0].getExpression(),  // expression
                      mpEvent->getAssignments()[0].getTargetCN()   // key
                    ));

#endif // XXXX
  deleteCompartment();

  deleteEvent();
}

void CQUndoTester::testReactionDetail()
{
#ifdef XXXX
  createReaction();

  // rename
  // rename species
  mpUndoStack->push(
    new EntityRenameCommand(
      mpReaction,
      mpReaction->getObjectName(),
      "R1",
      mpTabReactions)
  );

  // set reaction scheme
  mpUndoStack->push(new ReactionChangeCommand(
                      CCopasiUndoCommand::REACTION_SCHEME_CHANGE,
                      "",
                      "A -> B",
                      mpDetailReaction,
                      mpReaction,
                      FROM_UTF8(mpReaction->getFunction()->getObjectName()),
                      FROM_UTF8(mpReaction->getFunction()->getObjectName())
                    ));

  // change reversibility
  mpUndoStack->push(new ReactionChangeCommand(
                      CCopasiUndoCommand::REACTION_REVERSIBLE_CHANGE,
                      mpReaction->isReversible(),
                      !mpReaction->isReversible(),
                      mpDetailReaction,
                      mpReaction,
                      FROM_UTF8(mpReaction->getFunction()->getObjectName()),
                      FROM_UTF8(mpReaction->getFunction()->getObjectName())
                    ));

  mpUndoStack->push(new ReactionChangeCommand(
                      CCopasiUndoCommand::REACTION_FUNCTION_CHANGE,
                      FROM_UTF8(mpReaction->getFunction()->getObjectName()),
                      "Reversible Michaelis-Menten",
                      mpDetailReaction,
                      mpReaction
                    ));

  deleteReaction();

#endif // XXXX
}

void CQUndoTester::testCompartmentDM(int repetitions)
{
#ifdef XXXX
  // add by name
  int currentRow = mpDmCompartments->rowCount();
  mpUndoStack->push(new InsertCompartmentRowsCommand(
                      currentRow, 1, mpDmCompartments, mpDmCompartments->index(currentRow, COL_NAME_COMPARTMENTS), "compartment1")
                   );

  for (int i = 0; i < repetitions; ++i)
    {

      // add by volume
      //int currentRow = currentRow;
      mpUndoStack->push(new InsertCompartmentRowsCommand(
                          currentRow, 1, mpDmCompartments, mpDmCompartments->index(currentRow, COL_IVOLUME), 10)
                       );
      // change
      mpUndoStack->push(new CompartmentDataChangeCommand(
                          mpDmCompartments->index(currentRow, COL_IVOLUME), i + 1.12, mpDmCompartments)
                       );

      QModelIndexList lst;
      lst.append(mpDmCompartments->index(currentRow, COL_NAME_COMPARTMENTS));
      mpUndoStack->push(new RemoveCompartmentRowsCommand(lst, mpDmCompartments));
      //++currentRow;
    }

  // remove
  //QModelIndexList lst;
  //for (int i = 0; i < repetitions; ++i)
  //{
  //  lst.append(mpDmCompartments->index(i + 1, COL_NAME_COMPARTMENTS));
  //}
  //mpUndoStack->push(new RemoveCompartmentRowsCommand(lst, mpDmCompartments));
#endif
}

void CQUndoTester::testSpeciesDM(int repetitions)
{
#ifdef XXXX
  // add by name
  int currentRow = mpDmSpecies->rowCount();
  mpUndoStack->push(new InsertSpecieRowsCommand(
                      currentRow, 1, mpDmSpecies, mpDmSpecies->index(currentRow, COL_NAME_SPECIES), "s1")
                   );

  for (int i = 0; i < repetitions; ++i)
    {

      // add by volume
      mpUndoStack->push(new InsertSpecieRowsCommand(
                          currentRow, 1, mpDmSpecies, mpDmSpecies->index(currentRow, COL_ICONCENTRATION), 10)
                       );

      // change
      CMetab* pMetab = &mpDmWidgetSpecies->getDataModel()->getModel()->getMetabolites()[currentRow];
      mpUndoStack->push(new SpecieDataChangeCommand(pMetab, i + 2.23, 10, COL_ICONCENTRATION, mpDmSpecies)
                       );

      // delete
      QModelIndexList lst;
      lst.append(mpDmSpecies->index(currentRow, COL_NAME_SPECIES));
      mpUndoStack->push(new RemoveSpecieRowsCommand(lst, mpDmSpecies));
    }

#endif
}

void CQUndoTester::testModelValueDM(int repetitions)
{
#ifdef XXXX
  // add by name
  int currentRow = mpDmModelValues->rowCount();
  mpUndoStack->push(new InsertGlobalQuantityRowsCommand(
                      currentRow, 1, mpDmModelValues, mpDmModelValues->index(currentRow, COL_NAME_GQ), "p1")
                   );

  for (int i = 0; i < repetitions; ++i)
    {

      // add by volume
      mpUndoStack->push(new InsertGlobalQuantityRowsCommand(
                          currentRow, 1, mpDmModelValues, mpDmModelValues->index(currentRow, COL_INITIAL_GQ), 10)
                       );

      // change
      mpUndoStack->push(new GlobalQuantityDataChangeCommand(
                          mpDmModelValues->index(currentRow, COL_INITIAL_GQ), i + 3.34, mpDmModelValues)
                       );

      // delete
      QModelIndexList lst;
      lst.append(mpDmModelValues->index(currentRow, COL_NAME_GQ));
      mpUndoStack->push(new RemoveGlobalQuantityRowsCommand(lst, mpDmModelValues));
    }

#endif
}

void CQUndoTester::testEventDM(int repetitions)
{
#ifdef XXXX
  // add by name
  int currentRow = mpDmEvents->rowCount();
  mpUndoStack->push(new InsertEventRowsCommand(
                      currentRow, 1, mpDmEvents, mpDmEvents->index(currentRow, COL_NAME_EVENTS), "event1")
                   );

  for (int i = 0; i < repetitions; ++i)
    {

      // add by volume
      mpUndoStack->push(new InsertEventRowsCommand(
                          currentRow, 1, mpDmEvents, mpDmEvents->index(currentRow, COL_NAME_EVENTS),
                          QString("event_test_%1").arg(i))
                       );

      // change
      CEvent* pEvent = &mpDmWidgetEvents->getDataModel()->getModel()->getEvents()[currentRow];
      mpUndoStack->push(new EventDataChangeCommand(
                          mpDmEvents->index(currentRow, COL_NAME_EVENTS), QString("event_change_%1").arg(i), mpDmEvents)
                       );

      // delete
      QModelIndexList lst;
      lst.append(mpDmEvents->index(currentRow, COL_NAME_EVENTS));
      mpUndoStack->push(new RemoveEventRowsCommand(lst, mpDmEvents));
    }

#endif // XXXX
}

void CQUndoTester::testOverviewWidget()
{
#ifdef XXXX
  // create 8 reactions
  testReactionDM(7);

  CModel * pModel = mpDmWidgetOverview->getDataModel()->getModel();

  {
    // change species initial values
    CDataVector< CMetab >& metabs = pModel->getMetabolites();
    CDataVector< CMetab >::iterator it = metabs.begin();

    for (; it != metabs.end(); ++it)
      {
        mpUndoStack->push(
          new ParameterOverviewDataChangeCommand(
            it->getCN(),
            it->getObjectName(),
            "2", // new value
            "1", // old value
            mpDmOverview,
            "", // parameter set key
            COL_VALUE   // column
          )
        );
      }
  }

  {
    // change all reaction parameters
    CDataVectorNS < CReaction >& reactions = pModel->getReactions();
    CDataVectorNS < CReaction >::iterator it = reactions.begin();

    for (; it != reactions.end(); ++it)
      {
        mpUndoStack->push(
          new ParameterOverviewDataChangeCommand(
            it->getCN() +  std::string(",ParameterGroup=Parameters,Parameter=k1"),
            "k1",
            "2", // new value
            "0.1", // old value
            mpDmOverview,
            "", // parameter set key
            COL_VALUE   // column
          )
        );
      }
  }
#endif // XXXX
}

void CQUndoTester::testReactionDM(int repetitions)
{
#ifdef XXXX
  // add by name
  CModel * pModel = mpDmWidgetReactions->getDataModel()->getModel();
  int numReactions = pModel->getReactions().size();
  int currentRow = mpDmReactions->rowCount();
  bool isDefaultRow = numReactions == (mpDmReactions->rowCount() - 1);

  if (isDefaultRow)
    currentRow -= 1;

  // create new reaction
  mpUndoStack->push(new InsertReactionRowsCommand(
                      currentRow, 1, mpDmReactions, mpDmReactions->index(currentRow, COL_NAME_REACTIONS), "r1")
                   );

  // change reaction scheme
  mpUndoStack->push(new ReactionDataChangeCommand(
                      mpDmReactions->index(currentRow, COL_EQUATION), QString("S1 -> S2"), mpDmReactions)
                   );

  for (int i = 0; i < repetitions; ++i)
    {
      {
        // increment row
        ++currentRow;

        // add by name
        mpUndoStack->push(new InsertReactionRowsCommand(
                            currentRow, 1, mpDmReactions, mpDmReactions->index(currentRow, COL_NAME_REACTIONS),
                            QString("r_test_%1").arg(i))
                         );

        // change
        CReaction* pReact = &pModel->getReactions()[currentRow];
        mpUndoStack->push(new ReactionDataChangeCommand(
                            mpDmReactions->index(currentRow, COL_NAME_REACTIONS), QString("r_change_%1").arg(i), mpDmReactions)
                         );

        // delete
        QModelIndexList lst;
        lst.append(mpDmReactions->index(currentRow, COL_NAME_REACTIONS));
        mpUndoStack->push(new RemoveReactionRowsCommand(lst, mpDmReactions));
      }

      {
        // add by scheme
        mpUndoStack->push(new InsertReactionRowsCommand(
                            currentRow, 1, mpDmReactions, mpDmReactions->index(currentRow, COL_EQUATION),
                            QString("A%1 -> A%2").arg(i).arg(i + 1))
                         );

        // change
        CReaction* pReact = &pModel->getReactions()[currentRow];
        mpUndoStack->push(new ReactionDataChangeCommand(
                            mpDmReactions->index(currentRow, COL_EQUATION), QString("A%1 -> ").arg(i), mpDmReactions)
                         );

        // delete
        //QModelIndexList lst;
        //lst.append(mpDmReactions->index(currentRow, COL_NAME_REACTIONS));
        //mpUndoStack->push(new RemoveReactionRowsCommand(lst, mpDmReactions));
      }
    }

#endif // XXXX
}

void CQUndoTester::createCompartment()
{
#ifdef XXXX
  // add compartment
  mpUndoStack->push(new CreateNewCompartmentCommand(mpDetailComp));
  mpCompartment = dynamic_cast<CCompartment*>(const_cast<CDataObject*>(mpDetailComp->getObject()));
#endif
}

void CQUndoTester::createEvent()
{
#ifdef XXXX
  // add event
  mpUndoStack->push(
    new CreateNewEventCommand(mpDetailEvent)
  );
  mpEvent = dynamic_cast<CEvent*>(const_cast<CDataObject*>(mpDetailEvent->getObject()));
#endif
}

void CQUndoTester::createModelValue()
{
#ifdef XXXX
  // add model value
  mpUndoStack->push(new CreateNewGlobalQuantityCommand(mpDetailMV));
  mpModelValue = dynamic_cast<CModelValue*>(const_cast<CDataObject*>(mpDetailMV->getObject()));
#endif
}

void CQUndoTester::createReaction()
{
#ifdef XXXX
  // add reaction
  mpUndoStack->push(new CreateNewReactionCommand(mpDetailReaction));
  mpReaction = dynamic_cast<CReaction*>(const_cast<CDataObject*>(mpDetailReaction->getObject()));
#endif
}

void CQUndoTester::createSpecies()
{
#ifdef XXXX
  // add species
  mpUndoStack->push(
    new CreateNewSpeciesCommand(mpDetailSpecies)
  );
  mpSpecies = mpDetailSpecies->getCurrentMetab();
#endif
}

void CQUndoTester::deleteCompartment()
{
#ifdef XXXX

  if (mpCompartment == NULL) return;

  mpListViews->switchToOtherWidget(ListViews::WidgetType::CompartmentDetail, mpCompartment->getKey());
  // delete compartment
  mpUndoStack->push(
    new DeleteCompartmentCommand(mpDetailComp)
  );

  mpCompartment = NULL;
#endif
}

void CQUndoTester::deleteEvent()
{
#ifdef XXXX

  if (mpEvent == NULL)
    return;

  mpListViews->switchToOtherWidget(ListViews::WidgetType::EventDetail, mpEvent->getKey());
  // delete event
  mpUndoStack->push(
    new DeleteEventCommand(mpDetailEvent)
  );

  mpEvent = NULL;
#endif
}

void CQUndoTester::deleteModelValue()
{
#ifdef XXXX

  if (mpModelValue == NULL)
    return;

  mpListViews->switchToOtherWidget(ListViews::WidgetType::GlobalQuantityDetail, mpModelValue->getKey());
  // delete model value
  mpUndoStack->push(
    new DeleteGlobalQuantityCommand(mpDetailMV)
  );
  mpModelValue = NULL;
#endif
}

void CQUndoTester::deleteReaction()
{
#ifdef XXXX

  if (mpReaction == NULL)
    return;

  mpListViews->switchToOtherWidget(ListViews::WidgetType::ReactionDetail, mpReaction->getKey());
  // delete reaction
  mpUndoStack->push(
    new DeleteReactionCommand(mpDetailReaction)
  );

  mpReaction = NULL;
#endif
}

void CQUndoTester::deleteSpecies()
{
#ifdef XXXX

  if (mpSpecies == NULL)
    return;

  mpListViews->switchToOtherWidget(ListViews::WidgetType::SpeciesDetail, mpSpecies->getKey());
  // delete species
  mpUndoStack->push(
    new DeleteSpeciesCommand(mpDetailSpecies)
  );

  mpSpecies = NULL;
#endif
}

void CQUndoTester::focusChange(QWidget *old, QWidget *now)
{
  if (!old || !now)
    return;

  std::cerr << "Focus changed from " << old->objectName().toStdString()
            << " to " << now->objectName().toStdString() << std::endl;
}
