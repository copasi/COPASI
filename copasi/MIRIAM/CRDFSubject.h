// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFSubject.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/10 20:31:11 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CRDFSubject
#define COPASI_CRDFSubject

#include <string>

class CRDFSubject
  {
    // Enumerations
  public:
    /**
     * The two different types possible for subjects
     */
    enum eSubjectType {RESOURCE = 0, BLANK_NODE};

    // Operations
  public:
    /**
     * Default Constructor
     */
    CRDFSubject();

    /**
     * Copy Constructor
     * @param const CRDFSubject & src
     */
    CRDFSubject(const CRDFSubject & src);

    /**
     * Destructor
     */
    ~CRDFSubject();

    CRDFSubject& operator =(const CRDFSubject& rhs);

  private:
    bool operator ==(const CRDFSubject& rhs) const;

  public:
    /**
     * Set the type of the subject
     * @param const eSubjectType & type
     */
    void setType(const eSubjectType & type);

    /**
     * Retrieve the type of the subject
     * @return const eSubjectType & type
     */
    const eSubjectType & getType() const;

    /**
     * Set the resource of the subject
     * @param const std::string & resource
     * @param const bool & isLocal
     */
    void setResource(const std::string & resource, const bool & isLocal);

    /**
     * Retrieve the resource of the subject
     * @return const std::string & resource
     */
    const std::string & getResource() const;

    /**
     * Check whehter the resource is local
     * @return const bool & isLocal
     */
    const bool & isLocal() const;

    /**
     * Set the ID of the blank node of the subject
     * @param const std::string & blankNodeId
     */
    void setBlankNodeId(const std::string & blankNodeId);

    /**
     * Retrieve the ID of the blank node of the subject
     * @return const std::string & blankNodeId
     */
    const std::string & getBlankNodeID() const;

    /**
     * Reset all Data
     */
    void clearData();

    // Attributes
  private:
    /**
     * The type of the subject
     */
    eSubjectType mType;

    /**
     * The URI of the resource of type RESOURCE
     */
    std::string mResource;

    /**
     * Stores whether the reources is resolve locally or remotely.
     */
    bool mIsLocalResource;

    /**
     * The Id of the blank node for type BLANK_NODE
     */
    std::string mBlankNodeId;
  };

std::ostream & operator << (std::ostream & os, const CRDFSubject & subject);

#endif // COPASI_CRDFSubject
