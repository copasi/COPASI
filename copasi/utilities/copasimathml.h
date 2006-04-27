/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/copasimathml.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:32:44 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_MATHML
#define COPASI_MATHML

#define SPC(level) std::string(level, ' ')

class CMathMl
  {
  public:

    static std::string fixName(const std::string & name)
    {
      if (name.find_first_of(" ()*+-") == std::string::npos)
        return name;
      else
        return "\"" + name + "\"";
    }
  };

#endif
