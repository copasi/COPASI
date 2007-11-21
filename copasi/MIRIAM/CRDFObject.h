// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFObject.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/11/21 06:33:48 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CRDFObject: Virtual class for all RDF Objects.
 *
 */

#ifndef COPASI_CRDFOBJECT
#define COPASI_CRDFOBJECT

#include <string>
#include "utilities/CCopasiVector.h"

class CRDFObject
  {
    // Attributes
  protected:
    std::string mResource;

    // Operations
  public:
    CRDFObject(std::string resource);
    ~CRDFObject();
    virtual std::string getResource();
    virtual CCopasiVector <std::string> getProperties() = 0;
    virtual CCopasiVector <std::string> getPropertyValues() = 0;

    virtual void setResource(std::string resource);
  };

#endif //COPASI_CRDFOBJECT
