// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CBiologicalDescription.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/03/10 15:49:56 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CBiologicalDescription
#define COPASI_CBiologicalDescription

#include <string>

#include "report/CCopasiContainer.h"

#include "CRDFObject.h"

class CBiologicalDescription : public CCopasiContainer
  {
    // Attributes
  private:

    std::string mKey;

    /** Object in RDF Graph corresponding to this object.*/
    CRDFObject* mpRDFObj;

    /** The XML parent tag under which this object comes under.*/
    std::string mParentTag;

    // Operations
  public:
    /**
     * Default constructor
     * @param const std::string & objectName
     * @param CRDFObject* pRDFObj
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CBiologicalDescription(const std::string & objectName, const CCopasiContainer * pParent = NULL,
                           CRDFObject* pRDFObj = NULL);

    /**
     * Copy constructor
     * @param "const CBiologicalDescription &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CBiologicalDescription(const CBiologicalDescription & src,
                           const CCopasiContainer * pParent = NULL);

    ~CBiologicalDescription();
    void initObjects();

    const std::string getRelationship() const;
    void setRelationship(const std::string r);

    const std::string getResource() const;

    const std::string getId() const;
    void setId(const std::string Id, const std::string resource);

    CRDFObject& getRDFObject();

    const std::string getParentTag() const;
    void setParentTag(const std::string pt);

    const std::string getObjectName() const;

    /**
        *  Returns a string with the name of this BiologicalDescription.
        *  @return std::string key
        */
    virtual const std::string & getKey() const;
  };

#endif //COPASI_CReference
