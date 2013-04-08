// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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
#include "copasi/utilities/CCopasiVector.h"

class CExpression;
class CModel;

class CEventAssignment : public CCopasiContainer
{
public:
  // Operations
  /**
   * Default constructor
   * @param const std::string & targetKey (default: "")
   * @param "const CCopasiContainer * pParent (default: NULL)
   */
  CEventAssignment(const std::string & targetKey = "",
                   const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor
   * @param "const CEventAssignment &" src
   * @param "const CCopasiContainer * pParent (default: NULL)
   */
  CEventAssignment(const CEventAssignment & src,
                   const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  ~CEventAssignment();

  /**
   * Set the object parent
   * @param const CCopasiContainer * pParent
   * @return bool success
   */
  virtual bool setObjectParent(const CCopasiContainer * pParent);

  /**
   * Compile the event assignment.
   * @param std::vector< CCopasiContainer * > listOfContainer
   * @return bool success
   */
  bool compile(std::vector< CCopasiContainer * > listOfContainer);

  /**
   * Retrieve the key
   * @return const std::string & key
   */
  const std::string & getKey() const;

  /**
   * Set the key of the target
   * @param const std::string & targetKey
   * @return bool success;
   */
  bool setTargetKey(const std::string & targetKey);

  /**
   * Retrieve the target key
   * @return const std::string & targetKey
   */
  const std::string & getTargetKey() const;

  /**
   * Retrieve a pointer to the target object.
   * @return const CCopasiObject * targetObject
   */
  const CCopasiObject * getTargetObject() const;

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
   * The target object
   */
  const CCopasiObject * mpTarget;

  /**
   * The expression to calculate the new value
   */
  CExpression * mpExpression;
};

class CEvent : public CCopasiContainer, public CAnnotation
{
public:
  enum Type
  {
    Assignment,
    Discontinuity,
    CutPlane
  };

  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CEvent(const std::string & name = "NoName",
         const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor
   * @param "const CEvent &" src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CEvent(const CEvent & src,
         const CCopasiContainer * pParent = NULL);

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
   * @param const CCopasiContainer * pParent
   * @return bool success
   */
  virtual bool setObjectParent(const CCopasiContainer * pParent);

  /**
   * Retrieve display name. Special treatment for reaction to
   * provide a shorter display
   */
  virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;

  /**
   * Retrieves the key of the event
   * @return std::string key
   */
  virtual const std::string & getKey() const;

  /**
   * Check whether an object must be deleted because its prerequisites can
   * no longer be fulfilled due to the given deleted objects
   * @param const DataObjectSet & deletedObjects
   * @return bool mustBeDeleted
   */
  virtual bool mustBeDeleted(const DataObjectSet & deletedObjects) const;

  /**
   * Compile the event.
   * @param std::vector< CCopasiContainer * > listOfContainer
   * @return bool success
   */
  bool compile(std::vector< CCopasiContainer * > listOfContainer);

  /**
   * Sets the SBMLId.
   * @param const std::string & id
   */
  void setSBMLId(const std::string & id);

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
   * @return const CCopasiVectorN< CEventAssignment > & assignments
   */
  const CCopasiVectorN< CEventAssignment > & getAssignments() const;

  /**
   * Retrieve the assignments
   * @return CCopasiVectorN< CEventAssignment > & assignments
   */
  CCopasiVectorN< CEventAssignment > & getAssignments();

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
   *  The key of the event
   */
  std::string mKey;

  /**
   * The parent model
   */
  CModel * mpModel;

  /**
   * A vector assignments expressions which specify the changes made by the event.
   */
  CCopasiVectorN < CEventAssignment > mAssignments;

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
   * The type of the event
   */
  Type mType;

  /**
   * The id of the corresponding event in an SBML file.
   * This value is either set upon importing an SBML file,
   * or when the object is first exported to an SBML file.
   */
  std::string mSBMLId;

private:

  void initObjects();
};

#endif // COPASI_CEvent
