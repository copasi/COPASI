// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFSubject.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/21 16:15:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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
     */
    void setResource(const std::string & resource);

    /**
     * Retrieve the resource of the subject
     * @return const std::string & resource
     */
    const std::string & getResource() const;

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
     * The Id of the blank node for type BLANK_NODE
     */
    std::string mBlankNodeId;
  };

#endif // COPASI_CRDFSubject
