// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CReference.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/03/03 16:58:28 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/**
 *  CReferences: Stores publication details such as pubmed URL.
 *
 *
 */

#ifndef COPASI_CReference
#define COPASI_CReference

#include <string>

#include "report/CCopasiContainer.h"

#include "CRDFObject.h"

class CReference : public CCopasiContainer
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
    CReference(const std::string & objectName, const CCopasiContainer * pParent = NULL,
               CRDFObject* pRDFObj = NULL);

    /**
     * Copy constructor
     * @param "const CReference &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CReference(const CReference & src,
               const CCopasiContainer * pParent = NULL);

    ~CReference();
    void initObjects();

    /** Add the given name to Last name to get the full Name.
         *
         */

	const std::string getPubmedId() const;
	void setPubmedId(const std::string pubmedId);
	
	const std::string getDOI() const;
	void setDOI(const std::string DOI);

	const std::string getDescription() const;
	void setDescription(const std::string d);

    CRDFObject& getRDFObject();

	const std::string getParentTag() const;
    void setParentTag(const std::string pt);

    const std::string getObjectName() const;

    /**
        *  Returns a string with the name of this Reference.
        *  @return std::string key
        */
    virtual const std::string & getKey() const;
  };

#endif //COPASI_CReference
