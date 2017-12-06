// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CModelVersion.h
 *
 *  Created on: Nov 14, 2017
 *      Author: shoops
 */

#ifndef COPASI_CModelVersion
#define COPASI_CModelVersion

#include "copasi/model/CAnnotation.h"
#include "copasi/versioning/CVCard.h"

class XMLOutputStream;
class XMLInputStream;
class CModelVersionHierarchy;

class CModelVersion : public CAnnotation , public CVCard
{
public:
  friend XMLOutputStream & operator << (XMLOutputStream & xml, const CModelVersion & version);
  friend class CModelVersionHierarchy;

  CModelVersion();

  CModelVersion(XMLInputStream & stream, const XMLToken & current);

  CModelVersion(const CModelVersion & src);

  CModelVersion(const std::string & Version,
                const std::string &  ParentName,
                const std::string &  AuthorGivenName,
                const std::string &  AuthorFamilyName,
                const std::string &  AuthorOrganization,
                const std::string &  AuthorEmail,
                const std::string &  Comments,
                const std::string &  Time);

  virtual ~CModelVersion();

  const std::string & getName() const;
  const std::string & getParentName() const;
  const std::string & getUTCTimeStamp() const;

private:
  std::string mName;
  std::string mParentName;
  std::string mUTCTimeStamp;
};

XMLOutputStream & operator << (XMLOutputStream & xml, const CModelVersion & version);
#endif // COPASI_CModelVersion
