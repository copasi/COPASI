// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

#include <memory>
#include <string>
#include <vector>
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

  CCommonNameComponent(const std::string & type,
                       const std::string & name,
                       const std::shared_ptr< CCommonNameComponent > & parent);

  // Disable copy constructor and assignment operator
  CCommonNameComponent() = delete;
  CCommonNameComponent(const CCommonNameComponent & src) = delete;
  CCommonNameComponent & operator = (const CCommonNameComponent & src) = delete;

public:
  typedef std::shared_ptr< CCommonNameComponent > shared_ptr;

  static shared_ptr create(const CDataObject * pObject);

  static shared_ptr create(const std::string & type,
                           const std::string & name,
                           const std::shared_ptr< CCommonNameComponent > & parent = nullptr);

  std::string operator()() const;
  std::vector< shared_ptr > getComponentList() const;

  ~CCommonNameComponent();
  void signalObjectDeleted();
  void signalObjectNameChanged();
  void signalObjectParentChanged();
  std::string getCN() const;
  const std::string & getPartialCN() const;
  const CDataObject * getObject();
  bool isResolved() const;
  bool hasAncestor(const CDataContainer * pObject) const;
  bool mayHaveAncestor(const CDataContainer * pObject) const;

protected:
  void updatePartialCN();
  std::string getObjectTypeFromParent() const;

  std::string mPartialCN;
  const std::string mType;
  std::string mName;
  shared_ptr mpParent;
  const CDataObject * mpObject;
};
