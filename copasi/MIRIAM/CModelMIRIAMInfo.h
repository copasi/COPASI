// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CModelMIRIAMInfo.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/10/27 01:45:50 $
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

#include <vector>

#include "CAuthor.h"

class CModelMIRIAMInfo
  {
    // Attributes
  private:
    std::vector <CAuthor> mAuthors;

    // Operations
  public:
    CModelMIRIAMInfo();
    std::vector <CAuthor> & getAuthors();
  };

#endif //COPASI_CMODELMIRIAMINFO
