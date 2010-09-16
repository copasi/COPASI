// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLGlobalStyle.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/09/16 18:28:05 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLGlobalStyle_H__
#define CLGlobalStyle_H__

#include "copasi/layout/CLStyle.h"

class CCopasiContainer;
class GlobalStyle;

class CLGlobalStyle : public CLStyle
{
public:
  /**
   * Ctor.
   */
  CLGlobalStyle(CCopasiContainer* pParent = NULL);

  /**
   * Copy Constructor.
   */
  CLGlobalStyle(const CLGlobalStyle& source, CCopasiContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLGlobalStyle(const GlobalStyle& source, CCopasiContainer* pParent = NULL);

  /**
   * Converts this object to the corresponding SBML object.
   */
  GlobalStyle* toSBML(unsigned int level, unsigned int version) const;
};

#endif /* CLGlobalStyle_H__ */
