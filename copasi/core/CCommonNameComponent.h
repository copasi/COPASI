// Copyright (C) 2025 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <set>
#include <map>

class CDataObject;
class CDataContainer;

class CCommonNameComponent : public std::enable_shared_from_this< CCommonNameComponent >
{
private:
  static const std::map< std::string, std::string > VectorName2ObjectType;

  /**
   * @brief Construct a new CCommonNameComponent object
   *
   * @param pObject
   */
  CCommonNameComponent(const CDataObject * pObject);

  CCommonNameComponent(const std::string & partialCN,
                       const std::string & type,
                       const std::string & name,
                       const std::shared_ptr< CCommonNameComponent > & parent);

  // Disable copy constructor and assignment operator
  CCommonNameComponent() = delete;
  CCommonNameComponent(const CCommonNameComponent & src) = delete;
  CCommonNameComponent & operator = (const CCommonNameComponent & src) = delete;

public:
  static std::string ObjectTypeFromVectorName(const std::string & name);

  typedef std::shared_ptr< CCommonNameComponent > shared_ptr;
  typedef std::weak_ptr< CCommonNameComponent > weak_ptr;
  typedef std::shared_ptr< std::string > cn_ptr;

  static shared_ptr create(const CDataObject * pObject);

  static shared_ptr create(const std::string & partialCN,
                           const std::string & type,
                           const std::string & name,
                           const std::shared_ptr< CCommonNameComponent > & parent = nullptr);

  static std::string::size_type findNext(const std::string & cn,
                                         const std::string & toFind,
                                         const std::string::size_type & pos = 0);

  static std::string::size_type findPrevious(const std::string & cn,
                                             const std::string & toFind,
                                             const std::string::size_type & pos = std::string::npos);

  static size_t getElementIndex(const std::string & cn,
                                const size_t & pos);

  static std::string getElementName(const std::string & cn,
                                    const size_t & pos,
                                    const bool & unescape = true);

  static std::string escape(const std::string & name);

  static std::string unescape(const std::string & name);

  ~CCommonNameComponent();
  void signalObjectDeleted();
  void signalObjectNameChanged();
  void signalObjectParentChanged();
  cn_ptr getCN() const;
  std::vector< shared_ptr > getComponentList() const;
  const std::string & getPartialCN() const;
  const std::string & getObjectType() const;
  const std::string & getObjectName() const;

  const CDataObject * getObject();
  bool isResolved() const;
  bool hasAncestor(const CDataContainer * pObject) const;
  bool mayHaveAncestor(const CDataContainer * pObject) const;
  bool isValid() const;
  void addPrerequisite(shared_ptr prerequisite);
  void clearPrerequisites();

protected:
  void addChild(const CCommonNameComponent * pChild);
  void removeChild(const CCommonNameComponent * pChild);
  bool updatePartialCN();
  std::string getObjectTypeFromParent() const;
  void signalChanged();
  void signalParentCNChanged(const std::string & parentCN) const;
  std::string getParentCN() const;
  void appendPartialCN(std::string & parentCN) const;
  void addDependent(const CCommonNameComponent * pDependent);
  void removeDependent(const CCommonNameComponent * pDependent);
  void signalPrerequisiteChanged(shared_ptr prerequisite) const;
  std::string getCNasString() const;

  std::string mPartialCN;
  const std::string mType;
  std::string mName;
  shared_ptr mpParent;
  const CDataObject * mpObject;
  mutable std::weak_ptr< std::string > mpCN;
  std::set< const CCommonNameComponent * > mChildren;
  std::set< const CCommonNameComponent * > mDependents;
  std::vector< shared_ptr > mPrerequisites;
};
