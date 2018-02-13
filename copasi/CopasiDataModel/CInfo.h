// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CInfo
#define COPASI_COPASIDATAMODEL_CINFO_H_

#include "copasi/core/CDataContainer.h"

class CDataModel;
template < class CType > class CDataObjectReference;
class CCopasiTimer;

class CInfo: public CDataContainer
{
private:
  // Operations
  CInfo();

  CInfo(const CInfo & src);

public:
  CInfo(const CDataModel * pParent);

  virtual ~CInfo();

  void update();

private:
  CDataObjectReference< std::string > * mpCopasiVersion;
  CDataObjectReference< std::string > * mpGivenName;
  CDataObjectReference< std::string > * mpFamilyName;
  CDataObjectReference< std::string > * mpOrganization;
  CDataObjectReference< std::string > * mpEmail;
  CDataObjectReference< std::string > * mpFileName;
  CCopasiTimer * mpCurrentTime;
};

#endif //COPASI_COPASIDATAMODEL_CINFO_H_
