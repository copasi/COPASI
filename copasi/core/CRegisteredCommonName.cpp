// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include <sstream>

#include "copasi/copasi.h"

#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/core/CDataObject.h"
#include "copasi/core/CDataContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"

using std::string;

// uncomment the following line to enable debug output for CN resolution
// #define DEBUG_CN 1

//********** CRegisteredCommonName ***************

// static
std::set< const CRegisteredCommonName * > CRegisteredCommonName::UnresolvedCNs;

// static
void CRegisteredCommonName::ResolveAll(const CDataObject *  pContainer)
{
  std::set< const CRegisteredCommonName * > UnresolvedCNsCopy;

#pragma omp critical(cregisteredcommonname_access)
  UnresolvedCNsCopy = UnresolvedCNs;

  for (const CRegisteredCommonName * pCN : UnresolvedCNsCopy)
    pCN->resolve(pContainer);

#ifdef DEBUG_CN
  for (auto it = UnresolvedCNs.begin(); it != UnresolvedCNs.end(); ++it)
    std::cout << *it << ": " << **it << std::endl;

  std::cout << UnresolvedCNs.size() << std::endl;
#endif // DEBUG_CN
}

CRegisteredCommonName::CRegisteredCommonName()
  : CCommonName()
{}

CRegisteredCommonName::CRegisteredCommonName(const CCommonName & name)
  : CCommonName(name)
{
  if (!empty())
#pragma omp critical (cregisteredcommonname_access)
    UnresolvedCNs.insert(this);
}

CRegisteredCommonName::CRegisteredCommonName(const std::string & name)
  : CCommonName(name)
{
  if (!empty())
#pragma omp critical(cregisteredcommonname_access)
    UnresolvedCNs.insert(this);
}

CRegisteredCommonName::CRegisteredCommonName(const CRegisteredCommonName & src)
  : CCommonName(src)
{
  if (!empty()
      && (mpComponent == nullptr
          || !mpComponent->isResolved()))
#pragma omp critical (cregisteredcommonname_access)
    UnresolvedCNs.insert(this);
}

CRegisteredCommonName::~CRegisteredCommonName()
{
#pragma omp critical (cregisteredcommonname_access)
  UnresolvedCNs.erase(this);
}

CRegisteredCommonName& CRegisteredCommonName::operator=(const std::string& rhs)
{
  return CRegisteredCommonName::operator=(CCommonName(rhs));
}

CRegisteredCommonName & CRegisteredCommonName::operator=(const CCommonName & rhs)
  {
    if (this != &rhs)
    {
      if (!empty()
          && (mpComponent == nullptr
              || !mpComponent->isResolved()))
#pragma omp critical (cregisteredcommonname_access)
        UnresolvedCNs.erase(this);

      CCommonName::operator=(rhs);

      if (!empty()
          && (mpComponent == nullptr
              || !mpComponent->isResolved()))
#pragma omp critical (cregisteredcommonname_access)
        UnresolvedCNs.insert(this);
    }

  return *this;
  }

CRegisteredCommonName & CRegisteredCommonName::operator=(const CRegisteredCommonName & rhs)
{
  if (this != &rhs)
    {
      if (!empty()
          && (mpComponent == nullptr
              || !mpComponent->isResolved()))
#pragma omp critical (cregisteredcommonname_access)
        UnresolvedCNs.erase(this);

      CCommonName::operator=(rhs);

      if (!empty()
          && (mpComponent == nullptr
              || !mpComponent->isResolved()))
#pragma omp critical (cregisteredcommonname_access)
        UnresolvedCNs.insert(this);
    }

  return *this;
}

const CObjectInterface * CRegisteredCommonName::resolve(const CDataObject *  pContainer) const
{
  const CObjectInterface * pObject = CCommonName::resolve(pContainer);

  if (pObject != nullptr
      || !isValid())
#pragma omp critical (cregisteredcommonname_access)
    UnresolvedCNs.erase(this);

  return pObject;
}
