// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <assert.h>

#include <sbml/packages/render/sbml/GlobalStyle.h>

#include "CLGlobalStyle.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"

// static
CLGlobalStyle * CLGlobalStyle::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CLGlobalStyle(NO_PARENT);
}

// virtual
CData CLGlobalStyle::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CLGlobalStyle::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

CLGlobalStyle::CLGlobalStyle(CDataContainer* pParent): CLStyle("GlobalStyle", pParent)
{
  this->mKey = CRootContainer::getKeyFactory()->add("GlobalStyle", this);
}

/**
 * Copy Constructor.
 */
CLGlobalStyle::CLGlobalStyle(const CLGlobalStyle& source, CDataContainer* pParent):
  CLStyle(source, pParent)
{
  this->mKey = CRootContainer::getKeyFactory()->add("GlobalStyle", this);
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLGlobalStyle::CLGlobalStyle(const GlobalStyle& source, CDataContainer* pParent):
  CLStyle(source, "GlobalStyle", pParent)
{
  this->mKey = CRootContainer::getKeyFactory()->add("GlobalStyle", this);
}

/**
 * Converts this object to the corresponding SBML object.
 */
GlobalStyle* CLGlobalStyle::toSBML(unsigned int level, unsigned int version) const
{
  GlobalStyle* pGS = new GlobalStyle(level, version);
  this->addSBMLAttributes(pGS);
  return pGS;
}
