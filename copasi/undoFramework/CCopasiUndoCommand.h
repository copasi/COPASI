// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CCopasiUndoCommand.h
 *
 *  Created on: 3 Jul 2014
 *      Author: dada
 */
#ifndef CCOPASIUNDOCOMMAND_H_
#define CCOPASIUNDOCOMMAND_H_

#include <QUndoCommand>
#include <QModelIndex>

#include <set>

#include <copasi/UI/qtUtilities.h>

typedef QPair<int, int> PathItem;
typedef QList<PathItem> Path;

class CCopasiObject;
class UndoData;
class UndoSpeciesData;
class UndoReactionData;
class UndoGlobalQuantityData;
class UndoEventData;

class CCopasiUndoCommand : public QUndoCommand
{
public:

  /**
   * rather than using integers to refer to widgets,
   * let us use an enumeration, this will sort issues
   * caused by misunderstandings.
   */
  enum TopLevelWidgets
  {
    DFAULT = 0, // default widget
    MODEL = 1, // model widget
    COMPARTMENTS = 111, // compartment overview
    SPECIES = 112, // species overview
    REACTIONS = 114, // reactions overview
    GLOBALQUANTITYIES = 115, // global quantity dn
    EVENTS = 116, // events overview
    PARAMETER_OVERVIEW = 118, // parameter oveview widget
    PARAMETER_SETS = 119, // parameter set overview
    DIFFERENTIAL_EQNS = 126, // differential equations
    MATRICES = 127, // math matrices
    DEBUG = 128, // debug widget
    LAYOUTS = 13, // layout overview
    TASK_STEADY_STATE = 21, // steady state widget
    RESULT_STEADY_STATE = 211, // steady state result
    TASK_FLUX_MODES = 221, // elementary flux mode
    RESULT_FLUX_MODES = 2211, // efm result widget
    TASK_MOIETIES = 222, // moieties task
    RESULT_MOIETIES = 2221, // moieties task result
    TASK_TRAJECTORIES = 23, // trajectories task
    RESULT_TRAJECTORIES = 231, // trajectory task result
    TASK_MCA = 24, // mca task
    RESULT_MCA = 241, // mca task result
    TASK_LYAP = 26, // lyap task
    RESULT_LYAP = 261, // lyap task result
    TASK_TSSA = 27, // tssa task
    RESULT_TSSA = 271, // tssa task result
    TASK_CROSS_SECTION = 28, // crosssection task
    RESULT_CROSS_SECTION = 281, // crosssection task result
    TASK_OSCILLATION = 29, // oscillation task
    TASK_SCAN = 31, // scan task
    TASK_OPTIMIZATION = 32, // optimization task
    RESULT_OPTIMIZATION = 321, // optimization task result
    TASK_FITTING = 33, // fitting task
    RESULT_FITTING = 331, // fitting task result
    TASK_SENSITIVITIES = 34, // sensitivities task
    RESULT_SENSITIVITIES = 341, // sensitivities task result
    TASK_LNA = 35, // lna task
    RESULT_LNA = 351, // lna task results
    REPORTS = 43, // reports overview
    PLOTS = 42, // plots overview
    FUNCTIONS = 5, // functions overview
    INVALID = -1 // invalid widget
  };

  /**
   *  The valid command types for the undo history
   */
  enum Type
  {
    COMPARTMENT_CREATE = 0 , //creation of single compartment
    EVENT_CREATE, //creation of single event
    GLOBALQUANTITY_CREATE, //creation of single global quantity
    REACTION_CREATE, //creation of single reaction
    SPECIES_CREATE, //creation of single species
    COMPARTMENT_DELETE, //deletion of single compartment
    EVENT_DELETE, //deletion of single event
    GLOBALQUANTITY_DELETE, //deletion of single global quantity
    REACTION_DELETE, //deletion of single reaction
    SPECIES_DELETE, //deletion of single species
    COMPARTMENT_INSERT, //insert compartment
    EVENT_INSERT, //insert event
    GLOBALQUANTITY_INSERT, //insert global quantity
    REACTION_INSERT, //insert reaction
    SPECIES_INSERT, //insert species
    COMPARTMENT_REMOVE, //remove compartment
    EVENT_REMOVE, //remove event
    GLOBALQUANTITY_REMOVE, //remove global quantity
    REACTION_REMOVE, //remove reaction
    SPECIES_REMOVE, //remove species
    COMPARTMENT_REMOVE_ALL, //remove all compartment
    EVENT_REMOVE_ALL, //remove all event
    GLOBALQUANTITY_REMOVE_ALL, //remove all global quantity
    REACTION_REMOVE_ALL, //remove all reaction
    SPECIES_REMOVE_ALL, //remove all species
    COMPARTMENT_DATA_CHANGE, //change compartment data
    EVENT_DATA_CHANGE, //change event data
    GLOBALQUANTITY_DATA_CHANGE, //change global quantity data
    REACTION_DATA_CHANGE, //change reaction data
    SPECIES_DATA_CHANGE, //change species data
    SPECIES_TYPE_CHANGE, //change of species type
    MODEL_INITIAL_TIME_CHANGE, // change of model initial time
    MODEL_TIME_UNIT_CHANGE, // change of model time unit
    MODEL_QUANTITY_UNIT_CHANGE, // change of model quantity unit
    MODEL_VOLUME_UNIT_CHANGE, // change of model volume unit
    MODEL_AREA_UNIT_CHANGE, // change of model area unit
    MODEL_LENGTH_UNIT_CHANGE, // change of model length unit
    MODEL_STOCHASTIC_CORRECTION_CHANGE, // change of the stochastic correct on model
    COMPARTMENT_SIMULATION_TYPE_CHANGE, //change of compartment simulation type
    COMPARTMENT_INITIAL_VOLUME_CHANGE, // change of compartment initial volume
    COMPARTMENT_INITIAL_EXPRESSION_CHANGE, // change of compartment initial expression
    COMPARTMENT_EXPRESSION_CHANGE, // change of assignment / ode expression
    COMPARTMENT_SPATIAL_DIMENSION_CHANGE, // change of compartment spatial dimensions
    COMPARTMENT_ADD_NOISE_CHANGE, // change the compartment add noise setting
    COMPARTMENT_NOISE_EXPRESSION_CHANGE, // change the compartment noise expression
    GLOBALQUANTITY_INITAL_VALUE_CHANGE, // change of parameter initial value
    GLOBALQUANTITY_INITIAL_EXPRESSION_CHANGE, // change of parameter initial expression
    GLOBALQUANTITY_SIMULATION_TYPE_CHANGE, // change of parameter simulation type
    GLOBALQUANTITY_EXPRESSION_CHANGE, // change of parameter assignment / ode expression
    GLOBALQUANTITY_ADD_NOISE_CHANGE, // change the parameter add noise setting
    GLOBALQUANTITY_NOISE_EXPRESSION_CHANGE, // change the parameter noise expression
    GLOBALQUANTITY_UNIT_CHANGE, // change the unit
    EVENT_TRIGGER_EXPRESSION_CHANGE, // change of event trigger expression
    EVENT_TRIGGER_INITIALTIME_CHANGE, // change whether event can trigger at initial time
    EVENT_TRIGGER_PERSISTENT_CHANGE, // change whether event is persistent or not
    EVENT_DELAY_TYPE_CHANGE, //change of event delay type
    EVENT_DELAY_EXPRESSION_CHANGE, //change of event delay expression
    EVENT_PRIORITY_EXPRESSION_CHANGE, //change of event priority expression
    EVENT_ASSIGNMENT_TARGET_CHANGE, //change of event assignment target
    EVENT_ASSIGNMENT_EXPRESSION_CHANGE, //change of event assignment value
    EVENT_ASSIGNMENT_ADDED, // add event assignment to event
    EVENT_ASSIGNMENT_REMOVED, // remove event assignment from event
    REACTION_SCHEME_CHANGE, //change reaction scheme
    REACTION_REVERSIBLE_CHANGE, // change of reaction reversible flag
    REACTION_FAST_CHANGE, // change of reaction fast flag
    REACTION_FUNCTION_CHANGE, // change of reaction kinetics
    REACTION_LOCAL_PARAMETER_VALUE_CHANGE, // change of a local parameter value
    REACTION_MAPPING_VOLUME_CHANGE, // mapping of volume in kinetic law changed
    REACTION_MAPPING_SPECIES_CHANGE, // mapping of metabolite changed
    REACTION_MAPPING_PARAMETER_CHANGE, // mapping of local / global parameter changed
    REACTION_ADD_NOISE_CHANGE, // change the reactions add noise setting
    REACTION_NOISE_EXPRESSION_CHANGE, // change the reactions noise expression
    INVALID_TYPE
  };

  /**
   * Retrieve the type of the command.
   * @return const CCopasiUndoCommand::Type & type
   */
  const CCopasiUndoCommand::Type & getType() const;

  /**
   * Set the type
   * @param const CCopasiUndoCommand::Type & type
   */
  virtual void setType(const CCopasiUndoCommand::Type & type);

  /**
   * constructor initializing entity type and type
   * @param entityType the entity type (or empty if not given)
   * @param type the type (or INVALID_TYPE if not given)
   */
  CCopasiUndoCommand(const std::string& entityType = "",
                     CCopasiUndoCommand::Type type = INVALID_TYPE,
                     const std::string& action = "",
                     const std::string& property = "",
                     const std::string& newValue = "",
                     const std::string& oldValue = "",
                     const std::string& name = ""
                    );

  virtual ~CCopasiUndoCommand();

  virtual void undo() = 0;
  virtual void redo() = 0;

  static Path pathFromIndex(const QModelIndex & index);

  static QModelIndex pathToIndex(const Path& path, const QAbstractItemModel *model);

  bool isUndoState() const;

  void setUndoState(bool undoState);

  const std::string& getEntityType() const;

  const std::string& getNewValue() const;

  const std::string& getOldValue() const;

  const std::string& getProperty() const;

  void setEntityType(const std::string& entityType);

  void setNewValue(const std::string& newValue);

  void setOldValue(const std::string& oldValue);

  void setProperty(const std::string& property);

  const std::string& getAction() const;

  void setAction(const std::string& action);

  const std::string& getName() const;

  void setName(const std::string& name);

  const std::string& getKey() const;
  void setKey(const std::string &key);

  const std::string& getTime() const;

protected:

  /**
   *  Type of the undo command.
   */
  CCopasiUndoCommand::Type mType;

  bool undoState;
  std::string mNewValue;
  std::string mOldValue;
  std::string mProperty;
  std::string mEntityType;
  std::string mAction;
  std::string mName;
  std::string mTime;
  /**
   * Lookup of elements should always happen by key,
   * pointers are not reliable, names are not unique, thus
   * keys are most efficient.
   */
  std::string mKey;
};

#endif /* CCOPASIUNDOCOMMAND_H_ */
