// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CEvent.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/03/20 12:45:57 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// Copyright � 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CEvent class.
 */

#ifndef COPASI_CEvent
#define COPASI_CEvent

#include <string>
#include <vector>

#include "utilities/CCopasiVector.h"
#include "function/CExpression.h"

class SBase;

class CEvent : public CCopasiContainer
  {
    // Attributes
  private:

    /**
     *  The key of the event
     */
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
    /**
     *  Destructor
     */
    ~CEvent();

    /**
     *  Delete
     */
    void cleanup();

    /**
     *  Overload display name. Special treatment for reaction to
     *  provide a shorter display
     */
    virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;

    /**
     * Retreive the list of deleted numeric child objects;
     * @return std::set< const CCopasiObject * > deletedObjects
     */
    virtual std::set< const CCopasiObject * > getDeletedObjects() const;

    /**
     *  Retrieves the key of the reaction
     *  @return std::string key
     */
    virtual const std::string & getKey() const;

    /**
     *  Compile the event
     */
    void compile();

    /**
     * Sets the SBMLId.
     */
    void setSBMLId(const std::string& id);

    /**
     * Returns a reference to the SBML Id.
     */
    const std::string& getSBMLId() const;

    void setDelay(const C_FLOAT64 & d);
    const C_FLOAT64 & getDelay() const;

    /**
     * set the trigger expression from a string. The return value indicates if
     * parsing the expression was succesful.
     */
    bool setTriggerExpression(const std::string & s);

    std::string getTriggerExpressionString() const;
    const CExpression & getTriggerExpression() const;

    unsigned C_INT32 getNumActions() const;
    const std::string & getActionObjectKey(unsigned C_INT32 i) const;
    std::string getActionAssignmentString(unsigned C_INT32 i) const;
    const CExpression & getActionAssignment(unsigned C_INT32 i) const;

    /**
     * add an action to the event. The actions is described by the key of a copasi
     * object and a mathematical expression, given as a string.
     */
    bool addAction(const std::string & key, const std::string & expression);

    /**
     * delete all actions
     */
    void clearActions();

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CEvent & d);

  protected:

    /**
     * Expression to trigger the event
     */
    CExpression mTriggerExpression;

    /**
     * Delay before the action takes place.
     */
    C_FLOAT64 mDelay;

    /**
     *  List of actions that need to be applied after the event triggers.
     *  The std::string is the key of a copasi object, the expression is an assignment
     *  to this object.
     */
    std::vector < std::pair <std::string, CExpression> > mActions;

  private:

    void initObjects();
  };

#endif // COPASI_CEvent
