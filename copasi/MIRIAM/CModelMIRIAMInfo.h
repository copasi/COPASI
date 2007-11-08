// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CModelMIRIAMInfo.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/11/08 22:26:35 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CModelMIRIAMInfo: Stores all MIRIAM info for a Model.
 *
 */

#ifndef COPASI_CMODELMIRIAMINFO
#define COPASI_CMODELMIRIAMINFO

#include "utilities/CCopasiVector.h"

#include "CAuthor.h"

class CModelMIRIAMInfo
  {
    // Attributes
  private:
    CCopasiVector <CAuthor> mAuthors;

    // Operations
  public:
    CModelMIRIAMInfo();
    ~CModelMIRIAMInfo();
    CCopasiVector <CAuthor> & getAuthors();
    CAuthor* createAuthor(const std::string name);
    bool removeAuthor(const std::string & key);
  };

#endif //COPASI_CMODELMIRIAMINFO
