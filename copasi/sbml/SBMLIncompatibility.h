// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/SBMLIncompatibility.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/11/15 10:38:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SBMLINCOMPATIBILITY_H__
#define SBMLINCOMPATIBILITY_H__

#include <string>
#include "copasi.h"

class SBMLIncompatibility
  {
  public:
    enum SEVERITY
    {
      UNDEFINED,
      WARNING,
      ERROR
    };

  protected:
    // number of the incompatibility
    unsigned C_INT32 mNumber;
    // minimal version and level of SBML required to export the feature
    // if the feature is not supported by any SBML Version, the values are
    // set to 0
    unsigned C_INT32 mMinSBMLLevel;
    unsigned C_INT32 mMinSBMLVersion;
    SEVERITY mSeverity;
    std::string mMessage;
    std::string mDetails;

  public:
    SBMLIncompatibility(unsigned C_INT32, ...);

    std::string getMessage() const;
    std::string getDetails() const;
    SEVERITY getSeverity() const;
    unsigned C_INT32 minSBMLVersion() const;
    unsigned C_INT32 minSBMLLevel() const;
  };

typedef struct INCOMPATIBILITY
  {
    unsigned C_INT32 mNo;
    unsigned C_INT32 mSBMLLevel;
    unsigned C_INT32 mSBMLVersion;
    SBMLIncompatibility::SEVERITY mSeverity;
    const char * mMessage;
    const char* mDetails;
  };

#endif // SBMLINCOMPATIBILITY_H__
