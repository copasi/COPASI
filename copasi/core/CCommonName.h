// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

class CData;

/** @dia:pos 21.4754,29.8662 */
class CCommonName: public std::string
{
  // Operations
public:
  /**
   * Default Constructor
   */
  CCommonName();

  /**
   * Copy Constructor
   * @param const CRegisteredCommonName & src
   */
  CCommonName(const CCommonName & src);

  /**
   * Destructor
   */
  ~CCommonName();

  /**
   * Constructor from base class
   * @param const std::string & name
   */
  CCommonName(const std::string & name);

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

  std::string::size_type findNext(const std::string & toFind,
                                  const std::string::size_type & pos = 0) const;

  std::string::size_type findPrevious(const std::string & toFind,
                                      const std::string::size_type & pos = std::string::npos) const;
};

#endif // COPASI_CCommonName
