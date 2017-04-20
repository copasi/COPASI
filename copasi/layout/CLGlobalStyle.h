// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLGlobalStyle_H__
#define CLGlobalStyle_H__

#include "copasi/layout/CLStyle.h"

class CDataContainer;

LIBSBML_CPP_NAMESPACE_BEGIN
class GlobalStyle;
LIBSBML_CPP_NAMESPACE_END

class CLGlobalStyle : public CLStyle
{
public:
  static CLGlobalStyle * fromData(const CData & data);

  /**
   * Ctor.
   */
  CLGlobalStyle(CDataContainer* pParent = NULL);

  /**
   * Copy Constructor.
   */
  CLGlobalStyle(const CLGlobalStyle& source, CDataContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLGlobalStyle(const GlobalStyle& source, CDataContainer* pParent = NULL);

  /**
   * Converts this object to the corresponding SBML object.
   */
  GlobalStyle* toSBML(unsigned int level, unsigned int version) const;
};

#endif /* CLGlobalStyle_H__ */
