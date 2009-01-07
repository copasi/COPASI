// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/SBMLIncompatibility.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/01/07 19:04:51 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "SBMLIncompatibility.h"
#include "incompatibilities.h"

#include <stdarg.h>
#include <stdio.h>

#include "incompatibilities.h"

#define INITIALTEXTSIZE 1024

SBMLIncompatibility::SBMLIncompatibility(unsigned C_INT32 n, ...): mNumber(0), mMinSBMLLevel(0),
    mMinSBMLVersion(0), mSeverity(SBMLIncompatibility::UNDEFINED), mMessage(""), mDetails("")

{
  const INCOMPATIBILITY* pTmp = &(Incompatibilities[0]);
  while (pTmp->mNo != 9999)
    {
      if (pTmp->mNo == n)
        {
          break;
        }
      pTmp++;
    }
  mNumber = pTmp->mNo;
  mMinSBMLLevel = pTmp->mSBMLLevel;
  mMinSBMLVersion = pTmp->mSBMLVersion;
  mSeverity = pTmp->mSeverity;
  mDetails = pTmp->mDetails;
  // now we have to create the message from the variable parameters
  if (mNumber != 9999)
    {
      const char* fmt = pTmp->mMessage;

      C_INT32 TextSize = INITIALTEXTSIZE;
      char *Text = new char[TextSize + 1];

      va_list args;
      va_start(args, n);
      C_INT32 Printed = vsnprintf(Text, TextSize, fmt, args);
      va_end(args);

      while (Printed < 0 || TextSize < Printed)
        {
          delete [] Text;

          (Printed < 0) ? TextSize *= 2 : TextSize = Printed;
          Text = new char[TextSize + 1];

          va_list args;
          va_start(args, n);
          Printed = vsnprintf(Text, TextSize, fmt, args);
          va_end(args);
        }

      mMessage = Text;
      delete[] Text;
    }
}

std::string SBMLIncompatibility::getMessage() const
  {
    return mMessage;
  }

std::string SBMLIncompatibility::getDetails() const
  {
    return mDetails;
  }

SBMLIncompatibility::SEVERITY SBMLIncompatibility::getSeverity() const
  {
    return mSeverity;
  }

unsigned C_INT32 SBMLIncompatibility::minSBMLVersion() const
  {
    return mMinSBMLVersion;
  }

unsigned C_INT32 SBMLIncompatibility::minSBMLLevel() const
  {
    return mMinSBMLLevel;
  }
