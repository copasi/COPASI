// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLGlobalStyle.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/09/16 18:28:05 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <assert.h>

#include <sbml/layout/render/GlobalStyle.h>

#include "CLGlobalStyle.h"

#include "copasi/report/CCopasiRootContainer.h"
#include "copasi/report/CKeyFactory.h"

CLGlobalStyle::CLGlobalStyle(CCopasiContainer* pParent): CLStyle("GlobalStyle", pParent)
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("GlobalStyle", this);
}

/**
 * Copy Constructor.
 */
CLGlobalStyle::CLGlobalStyle(const CLGlobalStyle& source, CCopasiContainer* pParent):
    CLStyle(source, pParent)
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("GlobalStyle", this);
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLGlobalStyle::CLGlobalStyle(const GlobalStyle& source, CCopasiContainer* pParent):
    CLStyle(source, "GlobalStyle", pParent)
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("GlobalStyle", this);
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
