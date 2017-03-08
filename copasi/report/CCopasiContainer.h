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

/*!
    \file CCopasiContainer.h
    \brief Header file of class CCopasiContainer
 */

/**
 * Class CCopasiContainer
 *
 * This class is the is used to group CCopasiObjects logically. It inself is
 * an object. Contained objects are still globally accessible.
 *
 * Copyright Stefan Hoops 2002
 */

#ifndef COPASI_CCopasiContainer
#define COPASI_CCopasiContainer

#include <map>
#include <vector>

#include "copasi/report/CCopasiObject.h"

class CUnit;

class CCopasiContainer: public CCopasiObject
{
  //Attributes
public:
  class CObjectMap: private std::map< std::string, std::set< CCopasiObject * > >
  {
  public:
    class iterator
    {
    public:
      iterator();

      iterator(const CObjectMap & map,
               const bool & begin);

      iterator(const iterator & src);

      ~iterator();

      CCopasiObject * operator*() const;

      CCopasiObject * operator->() const;

      iterator & operator++();

      iterator operator++(int);

      bool operator != (const iterator & rhs) const;

    private:
      const std::map< std::string, std::set< CCopasiObject * > > * mpMap;
      bool mNameEnd;
      std::map< std::string, std::set< CCopasiObject * > >::iterator mName;
      bool mObjectEnd;
      std::set< CCopasiObject * >::iterator mObject;
    };

    class const_iterator
    {
    public:
      const_iterator();

      const_iterator(const CObjectMap & map,
                     const bool & begin);

      const_iterator(const const_iterator & src);

      ~const_iterator();

      CCopasiObject * operator*() const;

      CCopasiObject * operator->() const;

      const_iterator & operator++();

      const_iterator operator++(int);

      bool operator != (const const_iterator & rhs) const;

    private:
      const std::map< std::string, std::set< CCopasiObject * > > * mpMap;
      bool mNameEnd;
      std::map< std::string, std::set< CCopasiObject * > >::iterator mName;
      bool mObjectEnd;
      std::set< CCopasiObject * >::iterator mObject;
    };

  public:
    typedef std::map< std::string, std::set< CCopasiObject * > > data;
    typedef std::pair< std::set< CCopasiObject * >::const_iterator, std::set< CCopasiObject * >::const_iterator > range;

    CObjectMap();

    CObjectMap(const CObjectMap & src);

    ~CObjectMap();

    std::pair< std::set< CCopasiObject * >::iterator, bool > insert(CCopasiObject * pObject);
    bool erase(CCopasiObject * pObject);
    void clear();

    bool contains(CCopasiObject * pObject) const;
    void objectRenamed(CCopasiObject * pObject, const std::string & oldName);

    std::pair< std::set< CCopasiObject * >::const_iterator, std::set< CCopasiObject * >::const_iterator > equal_range(const std::string & name) const;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;
  };

  static const CObjectInterface::ContainerList EmptyList;

  typedef CObjectMap objectMap;

protected:
  objectMap mObjects;

private:
  // Operations
  CCopasiContainer();

protected:
  CCopasiContainer(const CCopasiContainer & src);

public:
  CCopasiContainer(const std::string & name,
                   const CCopasiContainer * pParent = NO_PARENT,
                   const std::string & type = "CN",
                   const unsigned C_INT32 & flag = CCopasiObject::Container);

  CCopasiContainer(const CCopasiContainer & src,
                   const CCopasiContainer * pParent);

  virtual ~CCopasiContainer();

  virtual const CObjectInterface * getObject(const CCopasiObjectName & cn) const;

  virtual const CCopasiObject * getValueObject() const;

  virtual const objectMap & getObjects() const;

  virtual bool add(CCopasiObject * pObject, const bool & adopt = true);

  virtual bool remove(CCopasiObject * pObject);

  void objectRenamed(CCopasiObject * pObject, const std::string & oldName);

  /**
   * Retrieve the units of the object.
   * @return std::string units
   */
  virtual const std::string getUnits() const;

  /**
   * Retrieve the units of the child object.
   * @return std::string units
   */
  virtual std::string getChildObjectUnits(const CCopasiObject * pObject) const;

  virtual size_t getIndex(const CCopasiObject * pObject) const;

  virtual CCopasiObject * insert(const CData & data);

  /**
   * Retrieve all descendant objects (optionally recursive)
   * @param std::set< const CCopasiObject * > & descendants
   * @param const bool & recursive (default: false)
   */
  void getDescendants(std::set< const CCopasiObject * > & descendants, const bool & recursive = false) const;

protected:
  void initObjects();

  template <class CType> CCopasiObject * addObjectReference(const std::string & name,
      CType & reference,
      const unsigned C_INT32 & flag = 0)
  {return createReference(name, this, reference, flag);}

  template <class CType> CCopasiObject * addVectorReference(const std::string & name,
      CType & reference,
      const unsigned C_INT32 & flag = 0)
  {return createVectorReference(name, this, reference, flag);}

  template <class CType> CCopasiObject * addMatrixReference(const std::string & name,
      CType & reference,
      const unsigned C_INT32 & flag = 0)
  {return createMatrixReference(name, this, reference, flag);}
};

#endif // COPASI_CCopasiContainer
