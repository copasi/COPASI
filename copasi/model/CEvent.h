// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CEvent.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/06/09 07:17:49 $
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
#include <vector>

#include "utilities/CCopasiVector.h"
#include "function/CExpression.h"

class SBase;

/*!
    \brief The class for handling event task

 */

class CEvent : public CCopasiContainer
  {
    // Attributes
  private:

    /// The key of the event
    std::string mKey;

    /**
     * The id of the corresponding event in an SBML file.
     * This value is either set upon importing an SBML file,
     * or when the object is first exported to an SBML file.
     */
    std::string mSBMLId;

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
    ///  Destructor
    ~CEvent();

    /**
     *  Delete
     */
    void cleanup();

    /**
     *  Retrieve display name. Special treatment for reaction to
     *  provide a shorter display
     */
    virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;

    /**
     * Retreive the list of deleted numeric child objects;
     * @return std::set< const CCopasiObject * > deletedObjects
     */
    virtual std::set< const CCopasiObject * > getDeletedObjects() const;

    /**
     *  Retrieves the key of the event
     *  @return std::string key
     */
    virtual const std::string & getKey() const;

    /// Compile the event
    bool compile();

    /// Sets the SBMLId.
    void setSBMLId(const std::string& id);

    /**
     * Returns a reference to the SBML Id.
     */
    const std::string& getSBMLId() const;

    //    void setDelay(const C_FLOAT64 & d);
    //    const C_FLOAT64 & getDelay() const;

    /**
     * set the expression of trigger from a string. The return value indicates if
     * parsing the expression was succesful.
     * @param const st::string & expression
     * @return bool success
     */
    bool setExpressionTrigger(const std::string & expression);

    /**
     * retrieve the expression of trigger as a string.
     * @return std::string expression
     */
    std::string getExpressionTrigger() const;

    /**
     * retrieve the pointer to the expression.
     * @return CExpression *
     */
    //    const CExpression & getExpression() const;

    /**
     * set the expression of delay from a string. The return value indicates if
     * parsing the expression was succesful.
     * @param const st::string & expression
     * @return bool success
     */
    bool setExpressionDelay(const std::string & expression);

    /**
     * retrieve the expression of delay as a string.
     * @return std::string expression
     */
    std::string getExpressionDelay() const;

    /**************************************************************************************/

    /**
     * set the expression of event assignment from a string. The return value indicates if
     * parsing the expression was succesful.
     * @param const st::string & expression
     * @return bool success
     */
    bool setAssignmentExpression(const std::string & key, const std::string & expression);

    /**
     * retrieve the expression of event assignment as a string.
     * @return std::string expression
     */
    //    std::string getExpressionEA() const;

    /// retrieve the number of assignment the event has
    unsigned C_INT32 getNumAssignments() const;

    /*!
     * retrieve the key of the i-th assignment object
        * since the object is unique then it acts also as the key.
     */
    const std::string getAssignmentObjectKey(unsigned C_INT32 i) const;

    /* retrieve the position of object target in the current event object according to a given key.
     * It is usefull in case of deleting object targets several times without being saved inbetween.
     */
    unsigned C_INT32 getAssignmentIndex(const std::string & key);

    /// retrieve the expression with key target in string format
    std::string getAssignmentExpressionStr(const std::string & key);

    /// retrieve the expression of the i-th assignment in string format
    std::string getAssignmentExpressionStr(unsigned C_INT32 i) const;

    /// retrieve the expression of the i-th assignment
    const CExpression & getAssignmentExpression(unsigned C_INT32 i) const;

    /// retrieve the vector of assignment expression
    // const std::vector<std::pair<std::string, CExpression> > getAssignmentExpressionVector() const;
    std::vector<std::pair<std::string, CExpression> > getAssignmentExpressionVector();
    // std::vector<std::pair<std::string, CExpression> > * getAssignmentExpressionVector();

    /// set the vector of assignment expression
    void setAssignmentExpressionVector(std::vector<std::pair<std::string, CExpression> > &vector);

    /// set the vector of assignments
    void setAssignment(std::vector<std::pair<std::string, std::string> > &vector);

    /// show all assignments saved in the event object
    void showAssignments();

    // +++++

    /**
     * add an assignment to the event. The assignment is described by the key of a copasi
     * object and a mathematical expression, given as a string.
     */
    bool addAssignment(const std::string & key, const std::string & expression);
    //    bool addAssignment(const std::string & key);

    /**
     * update the i-th assignment of the event. The assignment is described by the key of a copasi
     * object and a mathematical expression, given as a string.
     */
    bool updateAssignment(unsigned C_INT32 i, const std::string & key, const std::string & expression);

    /**
     * delete the i-th assignment from the vector.
    */
    bool deleteAssignment(unsigned C_INT32 i);

    /**
     * delete all assignment
     */
    void clearAssignment();

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CEvent & d);

  protected:

    CCopasiObjectReference<C_FLOAT64> *mpTriggerValueReference;
    CCopasiObjectReference<C_FLOAT64> *mpDelayValueReference;
    CCopasiObjectReference<C_FLOAT64> *mpEAValueReference;
    CCopasiObjectReference<C_FLOAT64> *mpValueReference;

    /**
     * Expression to trigger the event
     */
    CExpression mTriggerExpression;

    /**
     * Expression to the event
     */
    CExpression *mpExpressionTrigger;

    /**
     * Expression to the event
     */
    CExpression *mpExpressionDelay;

    /**
     * Expression to the event assignment
     */
    CExpression *mpExpressionEA;

    /**
     * Delay before the action takes place.
     */
    C_FLOAT64 mDelay;

    /**
     *  List of assignment expressions that need to be applied after the event triggers.
     *  The std::string is the key of a copasi object, the expression is an assignment expression
     *  to this object.
     */
    std::vector < std::pair <std::string, CExpression> > mAssigns;

    /**
     *  List of assignment expressions that need to be applied after the event triggers.
     *  The std::string is the key of a copasi object, the expression is an assignment expression
     *  to this object.
     */
    std::vector < std::pair <std::string, CExpression> > mAssignsExpression;

    /**
     *  List of assignment names that need to be applied after the event triggers.
     *  The std::string is the key of a copasi object, the expression is an assignment name
     *  to this object.
     */
    std::vector < std::pair <std::string, std::string> > mAssignsName;

  public:

    /**
     *  List of pair of object key and its display name.
     */
    std::vector < std::pair <std::string, std::string> > mObjectKeyDisplayName;

  private:

    void initObjects();
  };

#endif // COPASI_CEvent
