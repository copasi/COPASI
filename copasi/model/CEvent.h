// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

/*!
 \file CEvent.h
 \brief Header file of class CEvent.
 */

#ifndef COPASI_CEvent
#define COPASI_CEvent

#include <string>
#include <set>

#include "copasi/model/CAnnotation.h"
#include "copasi/core/CDataVector.h"

class CExpression;
class CModel;
class CCallbackInterface;

class CEventAssignment : public CDataContainer
{
public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CEventAssignment * pDataObject
   */
  static CEventAssignment * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  /**
   * Create the undo data which represents the changes recording the
   * differences between the provided oldData and the current data.
   * @param CUndoData & undoData
   * @param const CUndoData::Type & type
   * @param const CData & oldData (default: empty data)
   * @param const CCore::Framework & framework (default: CCore::Framework::ParticleNumbers)
   * @return CUndoData undoData
   */
  virtual void createUndoData(CUndoData & undoData,
                              const CUndoData::Type & type,
                              const CData & oldData = CData(),
                              const CCore::Framework & framework = CCore::Framework::ParticleNumbers) const;

  /**
   * Default constructor
   * @param const std::string & targetCN (default: "")
   * @param "const CDataContainer * pParent (default: NULL)
   *
   *  Even though this constuctor usually expects the CN of a target, it will also work with a key
   */
  CEventAssignment(const std::string & targetCN = "",
                   const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param "const CEventAssignment &" src
   * @param "const CDataContainer * pParent (default: NULL)
   */
  CEventAssignment(const CEventAssignment & src,
                   const CDataContainer * pParent);

  /**
   * Destructor
   */
  ~CEventAssignment();

  /**
   * Comparison operator
   * @param const CEventAssignment & rhs
   * @return bool notEqual
   */
  bool operator != (const CEventAssignment & rhs) const;

  /**
   * Set the object parent
   * @param const CDataContainer * pParent
   * @return bool success
   */
  virtual bool setObjectParent(const CDataContainer * pParent);

  /**
   * Compile the event assignment.
   * @param CObjectInterface::ContainerList listOfContainer
   * @return CIssue issue
   */
  CIssue compile(CObjectInterface::ContainerList listOfContainer);

  /**
   * Retrieve the key
   * @return const std::string & key
   */
  const std::string & getKey() const;

  /**
   * Set the CN of the target
   * @param const std::string & targetCN
   * @return bool success;
   */
  bool setTargetCN(const std::string & targetCN);

  /**
   * Retrieve the target CN
   * @return const std::string & targetCN
   */
  const std::string & getTargetCN() const;

  /**
   * Retrieve the target CN for saving CopasiML
   * @return std::string targetCN
   */
  std::string getXmlTargetCN() const;

  /**
   * Retrieve a pointer to the target object.
   * @return const CDataObject * targetObject
   */
  const CDataObject * getTargetObject() const;

  /**
   * Set the expression from an infix string. The return value indicates if
   * parsing the expression was successful.
   * @param const std::string & expression
   * @return bool success
   */
  bool setExpression(const std::string & expression);

  /**
   * Set the expression from an expression pointer. CEventAssignment takes ownership.
   * @param CExpression* pExpression
   * @return bool success
   */
  bool setExpressionPtr(CExpression * pExpression);

  /**
   * Retrieve the expression as a string.
   * @return std::string expression
   */
  std::string getExpression() const;

  /**
   * Retrieve the pointer to the expression.
   * @return CExpression * pExpression
   */
  const CExpression * getExpressionPtr() const;

  /**
   * Retrieve the pointer to the expression.
   * @return CExpression * pExpression
   */
  CExpression * getExpressionPtr();

  // Attributes
private:
  /**
   * The key
   */
  std::string mKey;

  /**
   * The parent model
   */
  CModel * mpModel;

  /**
   * target object CN
   */
  CRegisteredCommonName mTargetCN;

  /**
   * The target object
   */
  const CDataObject * mpTarget;

  /**
   * The expression to calculate the new value
   */
  CExpression * mpExpression;
};

class CEvent : public CDataContainer, public CAnnotation
{
public:
  enum Type
  {
    Assignment,
    Discontinuity,
    Callback,
    Stop
  };

  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CEvent * pDataObject
   */
  static CEvent * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  /**
   * Create the undo data which represents the changes recording the
   * differences between the provided oldData and the current data.
   * @param CUndoData & undoData
   * @param const CUndoData::Type & type
   * @param const CData & oldData (default: empty data)
   * @param const CCore::Framework & framework (default: CCore::Framework::ParticleNumbers)
   * @return CUndoData undoData
   */
  virtual void createUndoData(CUndoData & undoData,
                              const CUndoData::Type & type,
                              const CData & oldData = CData(),
                              const CCore::Framework & framework = CCore::Framework::ParticleNumbers) const;

  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CDataContainer * pParent (default: NULL)
   */
  CEvent(const std::string & name = "NoName",
         const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param "const CEvent &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CEvent(const CEvent & src,
         const CDataContainer * pParent);

private:
  CEvent & operator= (const CEvent &);

public:
  /**
   * Destructor
   */
  ~CEvent();

  /**
   *  Delete
   */
  void cleanup();

  /**
   * Set the object parent
   * @param const CDataContainer * pParent
   * @return bool success
   */
  virtual bool setObjectParent(const CDataContainer * pParent);

  /**
   * Retrieve display name. Special treatment for reaction to
   * provide a shorter display
   */
  virtual std::string getObjectDisplayName() const;

  /**
   * Retrieves the key of the event
   * @return std::string key
   */
  virtual const std::string & getKey() const;

  /**
   * Appends pointers to assignments which are dependent on the candidates to the
   * list.
   * @param std::set< const CDataObject * > candidates
   * @param std::set< const CDataObject * > & dependents
   * @return bool objectsAppended
   */
  bool appendDependentAssignments(std::set< const CDataObject * > candidates,
                                  std::set< const CDataObject * > & dependents) const;

  /**
   * Return information where the element in the object set is being used.
   *
   * @param deletedObjects an object set that is used by the event
   * @return a string representing how the object is being used, this will be
   *   one of "Unused", "Trigger", "Priority", "Delay",
   *   "EventAssignment Expression" or "EventAssignment Target"
   */
  std::string getOriginFor(const DataObjectSet & deletedObjects) const;

  /**
   * Compile the event.
   * @param CObjectInterface::ContainerList listOfContainer
   * @return CIssue issue
   */
  CIssue compile(CObjectInterface::ContainerList listOfContainer);

  /**
   * Sets the SBMLId.
   * @param const std::string & id
   */
  void setSBMLId(const std::string & id) const;

  /**
   * Returns a reference to the SBML Id.
   */
  const std::string& getSBMLId() const;

  /**
   * Set whether the calculation or the assignment shall be delayed.
   * @param const bool & delayCalculation
   */
  void setDelayAssignment(const bool & delayCalculation);

  /**
   * Retrieve whether to delay the calculation of the assignment.
   * @return const bool & delayCalculation
   */
  const bool & getDelayAssignment() const;

  /**
   * Set whether the trigger may fire at the initial time.
   * @param const bool & fireAtInitialTime
   */
  void setFireAtInitialTime(const bool & fireAtInitialTime);

  /**
   * Retrieve whether the trigger may fire at the initial time.
   * @return const bool & fireAtInitialTime
   */
  const bool & getFireAtInitialTime() const;

  /**
   * Set whether the trigger must remain true between firing and executions.
   * @param const bool & persistentTrigger
   */
  void setPersistentTrigger(const bool & persistentTrigger);

  /**
   * Retrieve whether the trigger must remain true between firing and executions.
   * @return const bool & persistentTrigger
   */
  const bool & getPersistentTrigger() const;

  /**
   * Set the expression of trigger from a string. The return value indicates if
   * parsing the expression was successful.
   * @param const std::string & expression
   * @return bool success
   */
  bool setTriggerExpression(const std::string & expression);

  /**
   * Set the expression of trigger from an expression.
   * @param CExpression* pExpression
   * @return bool success
   */
  bool setTriggerExpressionPtr(CExpression * pExpression);

  /**
   * Retrieve the expression of trigger as a string.
   * @return std::string expression
   */
  std::string getTriggerExpression() const;

  /**
   * Retrieve the pointer to the expression of trigger.
   * @return CExpression* pExpression
   */
  const CExpression * getTriggerExpressionPtr() const;

  /**
   * Retrieve the pointer to the expression of trigger.
   * @return CExpression* pExpression
   */
  CExpression * getTriggerExpressionPtr();

  /**
   * Set the expression of delay from a string. The return value indicates if
   * parsing the expression was successful.
   * @param const std::string & expression
   * @return bool success
   */
  bool setDelayExpression(const std::string & expression);

  /**
   * Set the expression of delay from an expression.
   * @param CExpression* pExpression
   * @return bool success
   */
  bool setDelayExpressionPtr(CExpression* pExpression);

  /**
   * Retrieve the expression of the delay as a string.
   * @return std::string expression
   */
  std::string getDelayExpression() const;

  /**
   * Retrieve the pointer to the expression of the delay.
   * @return CExpression* pExpression
   */
  CExpression* getDelayExpressionPtr();

  /**
   * Retrieve the pointer to the expression of the delay.
   * @return CExpression* pExpression
   */
  const CExpression* getDelayExpressionPtr() const;

  /**
   * Set the expression of priority from a string. The return value indicates if
   * parsing the expression was successful.
   * @param const std::string & expression
   * @return bool success
   */
  bool setPriorityExpression(const std::string & expression);

  /**
   * Set the expression of priority from an expression.
   * @param CExpression* pExpression
   * @return bool success
   */
  bool setPriorityExpressionPtr(CExpression* pExpression);

  /**
   * Retrieve the expression of the priority as a string.
   * @return std::string expression
   */
  std::string getPriorityExpression() const;

  /**
   * Retrieve the pointer to the expression of the priority.
   * @return CExpression* pExpression
   */
  CExpression* getPriorityExpressionPtr();

  /**
   * Retrieve the pointer to the expression of the priority.
   * @return CExpression* pExpression
   */
  const CExpression* getPriorityExpressionPtr() const;

  /**
   * Retrieve the assignments
   * @return const CDataVectorN< CEventAssignment > & assignments
   */
  const CDataVectorN< CEventAssignment > & getAssignments() const;

  /**
   * Retrieve the assignments
   * @return CDataVectorN< CEventAssignment > & assignments
   */
  CDataVectorN< CEventAssignment > & getAssignments();

  /**
   * Delete assignment with the given key. Please note this is not the target key.
   * @param const std::string & key
   */
  void deleteAssignment(const std::string & key);

  /**
   * Retrieve the type of the event
   * @return const Type & type
   */
  const Type & getType() const;

  /**
   * Set the type of the event
   * @param const Type & type
   */
  void setType(const Type & type);

  /**
   * insert operator
   */
  friend std::ostream & operator<<(std::ostream &os, const CEvent & d);

  // Attributes
private:
  /**
   * The parent model
   */
  CModel * mpModel;

  /**
   * A vector assignments expressions which specify the changes made by the event.
   */
  CDataVectorN < CEventAssignment > mAssignments;

  /**
   * A Boolean flag indicating whether the calculation or the assignment should be delayed
   * in the case that a delay is present.
   */
  bool mDelayAssignment;

  /**
   * A Boolean flag indicating whether the trigger may fire at the initial time
   * if the trigger expression is true;
   */
  bool mFireAtInitialTime;

  /**
   * A Boolean flag indicating whether the trigger expression must remain true between
   * firing and executing the event.
   */
  bool mPersistentTrigger;

  /**
   * Pointer to the boolean Trigger Expression of the event
   */
  CExpression * mpTriggerExpression;

  /**
   * Pointer to the Delay Expression of the event
   */
  CExpression * mpDelayExpression;

  /**
   * Pointer to the Priority Expression of the event
   */
  CExpression * mpPriorityExpression;

  /**
   * A pointer to an optional callback function to be executed when the event is
   * triggered.
   */
  CCallbackInterface * mpCallback;

  /**
   * The type of the event
   */
  Type mType;

  /**
   * The id of the corresponding event in an SBML file.
   * This value is either set upon importing an SBML file,
   * or when the object is first exported to an SBML file.
   */
  mutable std::string mSBMLId;

private:

  void initObjects();
};

#endif // COPASI_CEvent
