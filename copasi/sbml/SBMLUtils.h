// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/SBMLUtils.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/03/16 18:57:03 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SBMLUTILS_H__
#define SBMLUTILS_H__

#include <string>
#include "copasi/copasi.h"

LIBSBML_CPP_NAMESPACE_BEGIN
class SBase;
LIBSBML_CPP_NAMESPACE_END

class SBMLUtils
{
public:

  /**
   * Return the sbml ID if the sbml object actually has one.
   * If not, it returns "".
   * It only handles core sbml objects. No layout objects yet.
   */
  static std::string getIdFromSBase(const SBase* s);

  /**
   * This method goes through the given SBML model and collects all ids and
   * meta ids used in the model.
   */
  static void collectIds(Model* pModel, std::map<std::string, const SBase*>& ids, std::map<std::string, const SBase*>& metaIds);

protected:

  template<class CType>
  static std::string getId(const CType * pA, C_INT32 level = 2);
};

#endif
