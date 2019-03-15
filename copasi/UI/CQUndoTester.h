// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQ_UNDO_TESTER_H
#define CQ_UNDO_TESTER_H

#include <QObject>

class ListViews;
class CQCopasiApplication;

class CQTabWidget;

class CQModelWidget;
class CQCompartment;
class CQSpeciesDetail;
class CQModelValue;
class CQEventWidget1;
class ReactionsWidget1;

class CQCompartmentsWidget;
class CQSpeciesWidget;
class CQGlobalQuantitiesWidget;
class CQEventsWidget;
class CQReactionsWidget;
class CQParameterOverviewWidget;

class CQCompartmentDM;
class CQSpecieDM;
class CQGlobalQuantityDM;
class CQEventDM;
class CQReactionDM;
class CQParameterOverviewDM;

class CCompartment;
class CMetab;
class CModelValue;
class CEvent;
class CEventAssignment;
class CReaction;
class CUndoStack;

class CQUndoTester : public QObject
{
  Q_OBJECT
public:
  CQUndoTester(CQCopasiApplication * app, ListViews* pListViews);

  virtual ~CQUndoTester();

  /** starts all specified tests in the given number of milliseconds
   * @param msecs number of milliseconds after which to launche the tests
   */
  void startTestIn(int msecs);

public slots:

  /** runs all tests */
  void test();

  /** runs the tests of the model detail dialog */
  void testModelDetail();

  /** runs the tests of the compartment detail dialog */
  void testCompartmentDetail();

  /** runs the tests of the species detail dialog */
  void testSpeciesDetail();

  /** runs the tests of the parameter detail dialog */
  void testModelValueDetail();

  /** runs the tests of the event detail dialog */
  void testEventDetail();

  /** runs the tests of the reaction detail dialog */
  void testReactionDetail();

  /** runs the tests of the compartment overview dialog with the given
   *  number of repetitions.
   * @param repetitions the number for repetitions for this test
   */
  void testCompartmentDM(int repetitions = 1);

  /** runs the tests of the species overview dialog with the given
   *  number of repetitions.
   * @param repetitions the number for repetitions for this test
   */
  void testSpeciesDM(int repetitions = 1);

  /** runs the tests of the parameter overview dialog with the given
   *  number of repetitions.
   * @param repetitions the number for repetitions for this test
   */
  void testModelValueDM(int repetitions = 1);

  /** runs the tests of the event overview dialog with the given
   *  number of repetitions.
   * @param repetitions the number for repetitions for this test
   */
  void testEventDM(int repetitions = 1);

  /** runs the tests of the reaction overview dialog with the given
   *  number of repetitions.
   * @param repetitions the number for repetitions for this test
   */
  void testReactionDM(int repetitions = 1);

  /**
   * create some reactions and then changes the model parameters
   */
  void testOverviewWidget();

  /** deletes the compartment stored in mpCompartment */
  void deleteCompartment();

  /** deletes the event stored in mpEvent */
  void deleteEvent();

  /** deletes the parameter stored in mpModelValue */
  void deleteModelValue();

  /** deletes the reaction stored in mpReaction */
  void deleteReaction();

  /** deletes the species stored in mpSpecies */
  void deleteSpecies();

  /** creates a new compartment and stores it in mpCompartment */
  void createCompartment();

  /** creates a new event and stores it in mpEvent */
  void createEvent();

  /** creates a new parameter and stores it in mpModelValue */
  void createModelValue();

  /** creates a new reaction and stores it in mpReaction */
  void createReaction();

  /** creates a new species and stores it in mpSpecies */
  void createSpecies();

  /** track focus changes */
  void focusChange(QWidget * old, QWidget * now);

private:
  CQCopasiApplication * mpApp;
  ListViews* mpListViews;
  CUndoStack * mpUndoStack;

  // tab widgets
  CQTabWidget* mpTabModel;
  CQTabWidget* mpTabSpecies;
  CQTabWidget* mpTabCompartments;
  CQTabWidget* mpTabModelValues;
  CQTabWidget* mpTabEvents;
  CQTabWidget* mpTabReactions;

  // detail widgets
  CQModelWidget*    mpDetailModel;
  CQCompartment*    mpDetailComp;
  CQSpeciesDetail*  mpDetailSpecies;
  CQModelValue*     mpDetailMV;
  CQEventWidget1*   mpDetailEvent;
  ReactionsWidget1* mpDetailReaction;

  // data model widgets
  CQCompartmentsWidget*      mpDmWidgetComp;
  CQSpeciesWidget*           mpDmWidgetSpecies;
  CQGlobalQuantitiesWidget*  mpDmWidgetModelValues;
  CQEventsWidget*            mpDmWidgetEvents;
  CQReactionsWidget*         mpDmWidgetReactions;
  CQParameterOverviewWidget* mpDmWidgetOverview;

  // actual data models
  CQCompartmentDM*       mpDmCompartments;
  CQSpecieDM*            mpDmSpecies;
  CQGlobalQuantityDM*    mpDmModelValues;
  CQEventDM*             mpDmEvents;
  CQReactionDM*          mpDmReactions;
  CQParameterOverviewDM* mpDmOverview;

  // elements
  CCompartment*     mpCompartment;
  CMetab*           mpSpecies;
  CModelValue*      mpModelValue;
  CEvent*           mpEvent;
  CEventAssignment* mpEventAssignment;
  CReaction*        mpReaction;
};

#endif // CQ_UNDO_TESTER_H
