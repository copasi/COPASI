// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFObject.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/21 16:15:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CRDFObject
#define COPASI_CRDFObject

#include <string>

class CRDFLiteral;

class CRDFObject
  {
    // Enumerations
  public:
    /**
     * The three different types possible for objects
     */
    enum eObjectType {RESOURCE = 0, BLANK_NODE, LITERAL};

    // Operations
  public:
    /**
     * Default Constructor
     */
    CRDFObject();

    /**
     * Copy Constructor
     * @param const CRDFObject & src
     */
    CRDFObject(const CRDFObject & src);

    /**
     * Destructor
     */
    virtual ~CRDFObject();

    /**
     * Set the type of the object
     * @param const eObjectType & type
     */
    void setType(const eObjectType & type);

    /**
     * Retrieve the type of the object
     * @return const eObjectType & type
     */
    const eObjectType & getType() const;

    /**
     * Set the resource of the object
     * @param const std::string & resource
     */
    void setResource(const std::string & resource);

    /**
     * Retrieve the resource of the object
     * @return const std::string & resource
     */
    const std::string & getResource() const;

    /**
     * Set the ID of the blank node of the object
     * @param const std::string & blankNodeId
     */
    void setBlankNodeId(const std::string & blankNodeId);

    /**
     * Retrieve the ID of the blank node of the object
     * @return const std::string & blankNodeId
     */
    const std::string & getBlankNodeID() const;

    /**
     * Set the literal of the object
     * @param const std::string & lexicalData
     */
    void setLiteral(const CRDFLiteral & literal);

    /**
     * Retrieve the literal of the object
     * @return const CRDFLiteral & literal
     */
    const CRDFLiteral & getLiteral() const;

    // Attributes
  private:
    /**
     * The type of the object
     */
    eObjectType mType;

    /**
     * The URI of the resource of type RESOURCE
     */
    std::string mResource;

    /**
     * The Id of the blank node for type BLANK_NODE
     */
    std::string mBlankNodeId;

    /**
     * The pointer to the literal for type LITERAL
     */
    mutable CRDFLiteral * mpLiteral;
  };

#endif // COPASI_CRDFObject
