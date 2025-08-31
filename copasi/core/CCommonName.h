// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * Class CCommonName
 *
 * This class is the class for handling COPASI object names.
 *
 * Copyright Stefan Hoops 2002
 */

#ifndef COPASI_CCommonName
#define COPASI_CCommonName

#include <string>
#include <set>

#include "copasi/core/CCommonNameComponent.h"
#include "copasi/core/CObjectInterface.h"

class CData;

/** @dia:pos 21.4754,29.8662 */
class CCommonName: public std::string
{
  // Operations
public:
  static std::string nameFromCN(const CCommonName & cn);
  static std::string compartmentNameFromCN(const CCommonName & cn);

  static CObjectInterface * GetObjectFromCN(const CObjectInterface::ContainerList & listOfContainer,
    CCommonName & objName);

  static void ResolveAll(const CDataContainer * pContainer);

  /**
   * Default Constructor
   */
  CCommonName();

  /**
   * Default Constructor
   */
  CCommonName(const CCommonNameComponent::shared_ptr & component);

  /**
   * Copy Constructor
   * @param const CCommonName & src
   */
  CCommonName(const CCommonName & src);

  /**
   * Destructor
   */
  ~CCommonName();

  /**
   * Constructor from base class
   * @param const char * name
   */
  CCommonName(const char * name);

  /**
   * Constructor from base class
   * @param const std::string & name
   */
  CCommonName(const std::string & name);

  CCommonName & operator=(const CCommonName & rhs);
  CCommonName & operator=(const std::string & rhs);
  CCommonName & operator=(const CCommonNameComponent::shared_ptr & rhs);

  bool isResolved() const;

  const CObjectInterface * resolve(const CDataContainer * pContainer);
  const CObjectInterface * getObject() const;
  void refresh();

  CCommonName getPrimary() const;

  CCommonName getRemainder() const;

  std::string getObjectType() const;

  std::string getObjectName() const;

  size_t getElementIndex(const size_t & pos = 0) const;

  std::string getElementName(const size_t & pos /*= 0*/,
                             const bool & unescape = true) const;

  void split(CCommonName & parentCN, std::string & objectType, std::string & objectName) const;

  static std::string escape(const std::string & name);

  static std::string unescape(const std::string & name);

  static std::string fromData(const CData & data);

  static std::string construct(const CCommonName & parent, const std::string & objectType, const std::string & objectName);

  std::string::size_type findNext(const std::string & toFind,
                                  const std::string::size_type & pos = 0) const;

  std::string::size_type findPrevious(const std::string & toFind,
                                      const std::string::size_type & pos = std::string::npos) const;

private:
  void createComponent();
  void fixSpelling();

  static std::set< CCommonName * > UnresolvedCNs;

  CCommonNameComponent::shared_ptr mpComponent;
};

#endif // COPASI_CCommonName
