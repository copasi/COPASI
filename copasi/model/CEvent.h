// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CEvent.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/10/30 14:40:23 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CEvent & d);

  private:

    void initObjects();
  };

#endif // COPASI_CEvent
