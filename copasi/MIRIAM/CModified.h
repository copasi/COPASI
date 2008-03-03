// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CModified.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/03/03 16:58:28 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/**
 *  CModified: Stores Modification dates.
 */

#ifndef COPASI_CMODIFIED
#define COPASI_CMODIFIED

#include <string>

#include "report/CCopasiContainer.h"

#include "CRDFObject.h"

class CModified : public CCopasiContainer
  {
    // Attributes
  private:

    std::string mKey;

    /** Object in RDF Graph corresponding to this object.*/
    CRDFObject* mpRDFObj;

    // Operations
  public:
    /**
     * Default constructor
     * @param const std::string & objectName
     * @param CRDFObject* pRDFObj
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CModified(const std::string & objectName, const CCopasiContainer * pParent = NULL,
              CRDFObject* pRDFObj = NULL);

    /**
     * Copy constructor
     * @param "const CModified &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CModified(const CModified & src,
              const CCopasiContainer * pParent = NULL);

    ~CModified();
    void initObjects();

    /** Add the given name to Last name to get the full Name.
         *
         */

    const std::string getDateModified() const;

    void setDateModified(const std::string dateModified);

    CRDFObject& getRDFObject();

    const std::string getObjectName() const;

    /**
        *  Returns a string with the name of this Modified.
        *  @return std::string key
        */
    virtual const std::string & getKey() const;
  };

#endif //COPASI_CMODIFIED
