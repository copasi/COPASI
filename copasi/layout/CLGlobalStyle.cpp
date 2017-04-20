// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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
CLGlobalStyle * CLGlobalStyle::fromData(const CData & data)
{
  return new CLGlobalStyle(NO_PARENT);
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
