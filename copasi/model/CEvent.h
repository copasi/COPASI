// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CEvent.h,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/10/07 22:04:57 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// Copyright (C) 2005 by Pedro Mendes, Virginia Tech Intellectual
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

class CExpression;
class CModel;

class CEventAssignment : public CCopasiContainer
{
  // Operations
public:
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
   */
  void setExpressionPtr(CExpression * pExpression);

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

class CEvent : public CCopasiContainer
{
public:
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
   * Compile the event.
   * @param std::vector< CCopasiContainer * > listOfContainer
   * @return bool success
   */
  bool compile(std::vector< CCopasiContainer * > listOfContainer);

  /**
   * Set the order in which the event is executed for simultaneous events.
   * @param const unsigned C_INT32 & order
   * const bool & correctOther = true
   */
  void setOrder(const unsigned C_INT32 & order, const bool & correctOther = true);

  /**
   * Retrieve the order in which the events is executed for simultaneous events
   */
  const unsigned C_INT32 & getOrder() const;

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
   * Set whether the calculation or the assignment shall be delayed
   * @param
   */
  void setDelayAssignment(const bool & delayCalculation);

  /**
   * Retrieve whether to delay the calculation of the assignment.
   * @return const bool & delayCalculation
   */
  const bool & getDelayAssignment() const;

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
   */
  void setTriggerExpressionPtr(CExpression * pExpression);

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
   */
  void setDelayExpressionPtr(CExpression* pExpression);

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
   * Set the RDF/XML representation of the MIRIAM annotation
   * @param const std::string & miriamAnnotation
   * @param const std::string & oldId
   */
  void setMiriamAnnotation(const std::string & miriamAnnotation,
                           const std::string & oldId);

  /**
   * Retrieve the RDF/XML representation of the MIRIAM annotation
   * @return const std::string & miriamAnnotation
   */
  const std::string & getMiriamAnnotation() const;

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
   * The order in which the event is executed for simultaneous events.
   */
  unsigned C_INT32 mOrder;

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
   * Pointer to the Trigger Expression of the event
   */
  CExpression * mpTriggerExpression;

  /**
   * Pointer to the Delay Expression of the event
   */
  CExpression * mpDelayExpression;

  /**
   * The id of the corresponding event in an SBML file.
   * This value is either set upon importing an SBML file,
   * or when the object is first exported to an SBML file.
   */
  std::string mSBMLId;

  /**
   * The RDF/XML representation of the MIRIAM annotation
   */
  std::string mMiriamAnnotation;

private:

  void initObjects();
};

#endif // COPASI_CEvent
