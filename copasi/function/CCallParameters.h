// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CFunctionParameterMap
 *
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_CCallParameters
#define COPASI_CCallParameters

#include <vector>
#include "copasi/function/CFunctionParameter.h"
#include "copasi/function/CFunctionParameters.h"
#include "copasi/core/CDataObject.h"

/**
 * CCallParameterPointers
 *
 * This is what is actually passed to a function. Some of the void* can be
 * pointers to vector<const CDataObject*>
 */
template < typename Type >
class CCallParameters : private std::vector<void *>
{
public:
  union UType
  {
    const Type * value;
    CCallParameters< Type > * vector;
    //        std::vector< void * > * unTyped;
  };

  typedef typename std::vector< UType >::const_iterator const_iterator;

  // Operations
public:
  CCallParameters(const size_t & size = 0):
    std::vector<void *>(size)
  {}

  CCallParameters(const CCallParameters & src):
    std::vector<void *>(src)
  {}

  ~CCallParameters() {}

  void resize(const size_t & size)
  {
    ((std::vector<void *> *) this)->resize(size);

    std::vector<void *>::iterator it
      = ((std::vector<void *> *) this)->begin();
    typename std::vector<void *>::iterator end
      = ((std::vector<void *> *) this)->end();

    for (; it != end; ++it) *it = NULL;
  }

  inline void push_back(const Type * value)
  {((std::vector<const Type *> *) this)->push_back(value);}

  inline void push_back(CCallParameters< Type > * vector)
  {((std::vector<void *> *) this)->push_back(vector);}

  inline void clear()
  {((std::vector<void *> *) this)->clear();}

  inline size_t size() const
  {return ((std::vector<void *> *) this)->size();}

  inline UType & operator[](const size_t & index)
  {return (*(std::vector< UType > *)this)[index];}

  inline const UType & operator[](const size_t & index) const
  {return (*(const std::vector< UType > *)this)[index];}

  inline const_iterator begin() const
  {return ((std::vector<UType> *) this)->begin();}

  inline const_iterator end() const
  {return ((std::vector<UType> *) this)->end();}
};

/**
 * CFunctionParameterMap
 *
 * This class describes how a reaction fills the call parameters of a function.
 * It is generated from a CFunctionParameters object.
 * The reaction provides what exactly is to be passed as function parameters.
 */
class CFunctionParameterMap
{
public:
  static CDataObject * pUnmappedObject;

  CFunctionParameterMap();

  CFunctionParameterMap(const CFunctionParameterMap & src);

  /**
   * Destructor();
   */
  ~CFunctionParameterMap();

  /**
   * Sets a specific parameter. Works only if the parameter is no vector
   */
  CIssue setCallParameter(const std::string paramName, const CDataObject* obj);

  /**
   * Adds an object to a specific parameter vector. Works only if the parameter is a vector
   */
  CIssue addCallParameter(const std::string paramName, const CDataObject* obj);

  /**
   * Removes an object from a specific parameter vector. Works only if the parameter is a vector
   */
  void removeCallParameter(const std::string paramName, const CDataObject* obj);

  /**
   * Removes all objects from a specific parameter vector. Works only if the parameter is a vector.
   */
  void clearCallParameter(const std::string paramName);

  /**
   * Initializes a CallParameters object from a CFunctionParameters object.
   */
  void initializeFromFunctionParameters(const CFunctionParameters & src);

  size_t findParameterByName(const std::string & name,
                             const CFunctionParameter ** ppFunctionParameter = NULL) const;

private:

  /**
   * Clear the mPointers and mObjects vectors.
   */
  void clearCallParameters();

  /**
   * Create the mPointers and mObjects vectors with
   * type information from the CFunctionParameters object.
   */
  void initCallParameters();

  /**
   * Check if all pointers are !=NULL.
   */
  void checkCallParameters() const;

  /**
   * This is a vector of pointers to the data that is passed to a function
   */
  CCallParameters<C_FLOAT64> mPointers;

  /**
   * This is a vector of pointers to objects. Each objects needs to have a value
   * that can be passed to a function
   */
  CCallParameters<CDataObject> mObjects;

  /**
   * The CFunctionParameters object provides the data types of the call parameters
   */
  CFunctionParameters * mpFunctionParameters;

  // these are preliminary
public:
  const CFunctionParameters & getFunctionParameters() const;

  CCallParameters<C_FLOAT64> & getPointers();

  const CCallParameters<C_FLOAT64> & getPointers() const;

  CCallParameters<CDataObject> & getObjects();

  const CCallParameters<CDataObject> & getObjects() const;

  std::vector< const CDataObject * > getObjects(const size_t & index) const;
};

#endif // COPASI_CCallParameters
