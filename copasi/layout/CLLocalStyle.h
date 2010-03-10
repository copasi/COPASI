// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLLocalStyle.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/10 12:26:12 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLLocalStyle_H__
#define CLLocalStyle_H__

#include <copasi/layout/CLStyle.h>

#include <set>
#include <string>

#include <sbml/layout/render/LocalStyle.h>

class CLLocalStyle : public CLStyle
{
protected:
  std::set<std::string> mKeyList;

public:
  /**
   * Constructor.
   */
  CLLocalStyle(CCopasiContainer* pParent = NULL);

  /**
   * Copy Constructor.
   */
  CLLocalStyle(const CLLocalStyle& source, CCopasiContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLLocalStyle(const LocalStyle& source, CCopasiContainer* pParent = NULL);

  /**
   * Returns the number of keys in the key set.
   */
  unsigned int getNumKeys() const;

  /**
   * Returns the key list.
   */
  const std::set<std::string>& getKeyList() const;

  /**
   * Sets the key list.
   */
  void setKeyList(const std::set<std::string>& keyList);

  /**
   * Checks if a certain key is in the set or not.
   */
  bool isKeyInSet(const std::string& key) const;

  /**
   * Adds another key to the set.
   */
  void addKey(const std::string& key);

  /**
   * Checks whether a given key is in the role list.
   */
  bool isInKeyList(const std::string& key) const;

  /**
   * Removes an key from the set.
   */
  void removeKey(const std::string& key);

  /**
   * Converts this object to the corresponding SBML object.
   */
  LocalStyle* toSBML() const;
};

#endif /* CLLocalStyle_H__ */
