/**
 * @cond doxygen-libsbml-internal
 *
 * @file    IdList.h
 * @brief   Maintains a list of SIds.  Useful for finding cycles.
 * @author  Ben Bornstein
 * 
 * <!--------------------------------------------------------------------------
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright (C) 2009-2013 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. EMBL European Bioinformatics Institute (EBML-EBI), Hinxton, UK
 *  
 * Copyright (C) 2006-2008 by the California Institute of Technology,
 *     Pasadena, CA, USA 
 *  
 * Copyright (C) 2002-2005 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. Japan Science and Technology Agency, Japan
 * 
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.  A copy of the license agreement is provided
 * in the file named "LICENSE.txt" included with this software distribution
 * and also available online as http://sbml.org/software/libsbml/license.html
 * ---------------------------------------------------------------------- -->*/

#ifndef IdList_h
#define IdList_h


#ifdef __cplusplus


#include <string>
#include <vector>
#include <sbml/common/libsbml-namespace.h>

LIBSBML_CPP_NAMESPACE_BEGIN

class IdList
{
public:

  typedef std::vector<std::string>::iterator       iterator;
  typedef std::vector<std::string>::const_iterator const_iterator;

  /**
   * Appends id to the list of ids.
   */
  void append (const std::string id) { mIds.push_back(id); }

  /**
   * @return true if id is already in this IdList, false otherwise.
   */
  bool contains (const std::string id) const;

  /**
   * Removes all ids in this IdList before the given @p id.
   */
  void removeIdsBefore (const std::string id);

  /**
   * @return the number of ids in this IdList.
   */
  unsigned int size () const { return (unsigned int)mIds.size(); }

  /**
   * @return an iterator to the beginning of this IdList.
   */
  std::vector<std::string>::const_iterator begin () const
  {
    return mIds.begin();
  }

  /**
   * @return an iterator to the end of this IdList.
   */
  std::vector<std::string>::const_iterator end () const
  {
    return mIds.end();
  }


  void clear() { mIds.clear(); }

  std::string at(int n) { return mIds.at(n); }

private:

  std::vector<std::string> mIds;
};

LIBSBML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* IdList_h */

/** @endcond */
