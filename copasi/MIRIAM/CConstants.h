// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CConstants.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/03/10 15:49:56 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CConstants
#define COPASI_CConstants

#include <string>
#include <map>

class CConstants
  {
  public:
    CConstants::CConstants();
    static std::map<std::string, std::string> getReferencePredicates();
    static std::map<std::string, std::string> getPrefix2URI();
    static std::map<std::string, std::string> getRelationships();
    static std::map<std::string, std::string> getResources();
    static std::string getKey(const std::map<std::string, std::string>& map, const std::string& value);
  private:
    static std::map<std::string, std::string> referencePredicates;
    static std::map<std::string, std::string> prefix2URI;
    static std::map<std::string, std::string> relationships;
    static std::map<std::string, std::string> resources;
  };

#endif
