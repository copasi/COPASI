// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#ifndef CLStyle_H__
#define CLStyle_H__

#include <set>
#include <string>

#include "copasi/layout/CLBase.h"
#include "copasi/layout/CLGroup.h"

#include "copasi/core/CDataContainer.h"

LIBSBML_CPP_NAMESPACE_BEGIN
class Style;
LIBSBML_CPP_NAMESPACE_END

class CLGraphicalObject;

class CLStyle : public CLBase, public CDataContainer
{
private:
  // prevent the compiler from generating the assignment operator
  CLStyle& operator=(const CLStyle& source);

protected:
  std::set<std::string> mRoleList;
  std::set<std::string> mTypeList;
  CLGroup* mpGroup;

  /**
   * key string for the style.
   */
  std::string mKey;

public:
  /**
   * Constructor.
   */
  CLStyle(const std::string& name, CDataContainer* pParent = NULL);

  /**
   * Copy Constructor.
   */
  CLStyle(const CLStyle& source, CDataContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLStyle(const Style& source, const std::string& name, CDataContainer* pParent = NULL);

  /**
   * Destructor
   */
  ~CLStyle();

  /**
   * Sets the group.
   */
  void setGroup(const CLGroup* pGroup);

  /**
   * Returns the group.
   */
  const CLGroup* getGroup() const;

  /**
   * Returns the group.
   */
  CLGroup* getGroup();

  /**
   * Returns the number of roles in the role list.
   */
  size_t getNumRoles() const;

  /**
   * Adds an role to the role list.
   */
  void addRole(const std::string& role);

  /**
   * Checks whether a given role is in the role list.
   */
  bool isInRoleList(const std::string& role) const;

  /**
   * Removes a role from the role list.
   */
  void removeRole(const std::string& role);

  /**
   * Sets the role list.
   */
  void setRoleList(const std::set<std::string>& roleList);

  /**
   * Returns the role list.
   */
  const std::set<std::string>& getRoleList() const;

  /**
   * @return the roles as string
   */
  std::string getRoleListString() const;

  /**
   * Returns the type list.
   */
  const std::set<std::string>& getTypeList() const;

  /**
   * @return the types in the type list as string
   */
  std::string getTypeListString() const;

  /**
   * Sets the type list.
   */
  void setTypeList(const std::set<std::string>& typeList);

  /**
   * Returns the number of types in the type list.
   */
  size_t getNumTypes() const;

  /**
   * Adds a type to the type list.
   */
  void addType(const std::string& type);

  /**
   * Checks whether a given type is in the type list.
   */
  bool isInTypeList(const std::string& type) const;

  /**
   * Removes an type from the type list.
   */
  void removeType(const std::string& type);

  static void readIntoSet(const std::string& s, std::set<std::string>& set);

  static std::string createStringFromSet(const std::set<std::string>& set);

  /**
   * Returns the key of the style
   */
  const std::string& getKey() const;

  /**
   * Adds the attributes for a style object to the passed in.
   * object.
   */
  void addSBMLAttributes(Style* pStyle) const;

  /**
   * Checks whether the style applies to the graphical object
   *
   * @param pObject the object to check
   * @return 0, if the style does not apply, 1 if it applies by type,
   *         2 if it applies by role
   */
  virtual int appliesTo(const CLGraphicalObject * pObject) const;
};

#endif /* CLStyle_H__ */
