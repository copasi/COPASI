// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CConstants.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: aruff $
//   $Date: 2008/09/17 17:27:36 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CConstants
#define COPASI_CConstants

#include <string>
#include <map>
#include <vector>
#include "CMIRIAMResource.h"

class CRDFNode;

class CMIRIAMResources;

class CMIRIAMResourceObject
  {

  private:
    CMIRIAMResourceObject();

    void extractId(const std::string & URI);

  public:

    unsigned C_INT32 getResource(const std::string & URI);

    static const CMIRIAMResources & getResourceList();

    CMIRIAMResourceObject(CRDFNode * pNode);

    CMIRIAMResourceObject(const std::string & displayName, const std::string & id);

    CMIRIAMResourceObject(const CMIRIAMResourceObject & src);

    bool setId(const std::string & id);

    const std::string & getId() const;

    bool setURI(const std::string & URI);

    std::string getURI() const;

    bool setNode(CRDFNode * pNode);

    CRDFNode * getNode() const;

    bool setDisplayName(const std::string & displayName);

    std::string getDisplayName() const;

    bool isValid() const;

    bool isValid(const std::string & URI) const;

    static void setMIRIAMResources(const CMIRIAMResources * pResources);

    /**
     * Destructor
     */
    virtual ~CMIRIAMResourceObject();

  private:
    static const CMIRIAMResources * mpResources;

    unsigned C_INT32 mResource;
    std::string mId;
    CRDFNode * mpNode;
  };

#endif
