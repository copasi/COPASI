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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CKeyFactory class.
 * This class is used to create a unique key whithin COPASI. It also allows
 * retreival of the CDataObject the key is assigned to.
 *
 * Created for Copasi by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */

#ifndef COPASI_CKeyFactory
#define COPASI_CKeyFactory

#include <string>
#include <map>
#include <stack>

#include "copasi/core/CVector.h"

class CDataObject;

class CKeyFactory
{
private:
  class HashTable
  {
  private:
    size_t mBeyond;
    size_t mSize;
    CVector< CDataObject * > mTable;
    std::stack< size_t > mFree;

  public:
    HashTable();
    HashTable(const HashTable & src);
    ~HashTable();
    size_t add(CDataObject * pObject);
    bool addFix(const size_t & index, CDataObject * pObject);
    CDataObject * get(const size_t & index);
    bool remove(const size_t & index);
  };

  class CDecisionVector : private CVector< bool >
  {
  private:
    CDecisionVector();

  public:
    CDecisionVector(const std::string & str);

    virtual ~CDecisionVector();

    const bool & operator()(const unsigned char & c) const;
  };

  // Attributes
protected:
  /**
   * A map of hash tables for the prefixes.
   */
  std::map< std::string, HashTable > mKeyTable;

  /**
   * Fast way to decide whether a character is a digit.
   */
  static CDecisionVector isDigit;

  /**
   * Fast way to decide whether a character is a valid part of the prefix.
   */
  static CDecisionVector isPrefix;

  // Operations
public:
  /**
   * check whether the key is valid
   * @param const std::string & key
   * @param const std::string & prefix (default: check for [_a-zA-Z]+_\d+)
   * @return bool isValid
   */
  static bool isValidKey(const std::string & key,
                         const std::string & prefix = "");

  /**
   * Default constructor
   */
  CKeyFactory();

  /**
   * Destructor
   */
  ~CKeyFactory();

  /**
   * Add an object with a key generated from the given prefix to the key map.
   * The return value is the actually generated key.
   * @param const std::string & prefix
   * @param CDataObject * pObject
   * @return std::string key
   */
  std::string add(const std::string & prefix, CDataObject * pObject);

  /**
   * Add an object with a fix given key.
   * The return value indicate whether the key was actually inserted.
   * @param const std::string & key
   * @param CDataObject * pObject
   * @return bool success
   */
  bool addFix(const std::string & key, CDataObject * pObject);

  /**
   * Remove the key and the related object from the key map.
   * @param const std::string & key
   * @return bool success
   */
  bool remove(const std::string & key);

  /**
   * Retrieve the object referred by key from the key map.
   * @param const std::string & key
   * @return CDataObject * pObject
   */
  CDataObject * get(const std::string & key);
};

#endif // COPASI_CKeyFactory
