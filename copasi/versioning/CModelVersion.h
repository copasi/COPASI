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

class CModelVersion : public CAnnotation
{
public:
  CModelVersion();
  virtual ~CModelVersion();

private:
  std::string Name;
  std::string ParentName;
  std::string AuthorGivenName;
  std::string AuthorFamilyName;
  std::string AuthorOrganization;
  std::string AuthorEmail;
  std::string Time;
};

#endif // COPASI_CModelVersion
