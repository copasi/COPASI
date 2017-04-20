// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * Class CCopasiObjectName
 *
 * This class is the class for handling Copasi object names.
 *
 * Copyright Stefan Hoops 2002
 */

#ifndef COPASI_CCopasiObjectName
#define COPASI_CCopasiObjectName

#include <string>
#include <set>

/** @dia:pos 21.4754,29.8662 */
class CCopasiObjectName: public std::string
{
  // Operations
public:
  CCopasiObjectName();

  CCopasiObjectName(const std::string & name);

  CCopasiObjectName(const CCopasiObjectName & src);

  ~CCopasiObjectName();

  CCopasiObjectName getPrimary() const;

  CCopasiObjectName getRemainder() const;

  std::string getObjectType() const;

  std::string getObjectName() const;

  size_t getElementIndex(const size_t & pos = 0) const;

  std::string getElementName(const size_t & pos /*= 0*/,
                             const bool & unescape = true) const;

  static std::string escape(const std::string & name);

  static std::string unescape(const std::string & name);

  // private:
  std::string::size_type findEx(const std::string & toFind,
                                const std::string::size_type & pos = 0) const;
};

class CRegisteredObjectName: public CCopasiObjectName
{
public:
  CRegisteredObjectName();

  CRegisteredObjectName(const std::string & name);

  CRegisteredObjectName(const CRegisteredObjectName & src);

  ~CRegisteredObjectName();

  static const std::set<CRegisteredObjectName*> & getSet();

  /**
   * Enable and disable the rename handler
   * @param const bool & enabled
   */
  static void setEnabled(const bool & enabled);

  static bool isEnabled();

  static void handle(const std::string & oldCN,
                     const std::string & newCN);

private:
  static std::set<CRegisteredObjectName*> mSet;

  static bool mEnabled;
};

#endif // COPASI_CCopasiObjectName
