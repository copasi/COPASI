// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/*!
    \file CDataContainer.h
    \brief Header file of class CDataContainer
 */

/**
 * Class CDataContainer
 *
 * This class is the is used to group CDataObjects logically. It inself is
 * an object. Contained objects are still globally accessible.
 *
 * Copyright Stefan Hoops 2002
 */

#ifndef COPASI_CDataContainer
#define COPASI_CDataContainer

#include <map>
#include <vector>

#include "copasi/core/CDataObject.h"

template <class CType> class CDataObjectReference;
template <class CType> class CDataVectorReference;
template <class CType> class CDataMatrixReference;
class CUnit;

class CDataContainer: public CDataObject
{
  //Attributes
public:
  class CObjectMap: private std::map< std::string, std::set< CDataObject * > >
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

      CDataObject * operator*() const;

      CDataObject * operator->() const;

      iterator & operator++();

      iterator operator++(int);

      bool operator != (const iterator & rhs) const;

    private:
      const std::map< std::string, std::set< CDataObject * > > * mpMap;
      bool mNameEnd;
      std::map< std::string, std::set< CDataObject * > >::iterator mName;
      bool mObjectEnd;
      std::set< CDataObject * >::iterator mObject;
    };

    class const_iterator
    {
    public:
      const_iterator();

      const_iterator(const CObjectMap & map,
                     const bool & begin);

      const_iterator(const const_iterator & src);

      ~const_iterator();

      CDataObject * operator*() const;

      CDataObject * operator->() const;

      const_iterator & operator++();

      const_iterator operator++(int);

      bool operator != (const const_iterator & rhs) const;

    private:
      const std::map< std::string, std::set< CDataObject * > > * mpMap;
      bool mNameEnd;
      std::map< std::string, std::set< CDataObject * > >::iterator mName;
      bool mObjectEnd;
      std::set< CDataObject * >::iterator mObject;
    };

  public:
    typedef std::map< std::string, std::set< CDataObject * > > data;
    typedef std::pair< std::set< CDataObject * >::const_iterator, std::set< CDataObject * >::const_iterator > range;

    CObjectMap();

    CObjectMap(const CObjectMap & src);

    ~CObjectMap();

    std::pair< std::set< CDataObject * >::iterator, bool > insert(CDataObject * pObject);
    bool erase(CDataObject * pObject);
    void clear();

    bool contains(CDataObject * pObject) const;
    void objectRenamed(CDataObject * pObject, const std::string & oldName);

    std::pair< std::set< CDataObject * >::const_iterator, std::set< CDataObject * >::const_iterator > equal_range(const std::string & name) const;

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
  CDataContainer();

protected:
  CDataContainer(const CDataContainer & src);

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CDataContainer * pDataObject
   */
  static CDataContainer * fromData(const CData & data);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data);

  CDataContainer(const std::string & name,
                 const CDataContainer * pParent = NO_PARENT,
                 const std::string & type = "CN",
                 const CFlags< Flag > & flag = CFlags< Flag >::None);

  CDataContainer(const CDataContainer & src,
                 const CDataContainer * pParent);

  virtual ~CDataContainer();

  virtual const CObjectInterface * getObject(const CCommonName & cn) const;

  virtual const CDataObject * getValueObject() const;

  virtual const objectMap & getObjects() const;

  virtual bool add(CDataObject * pObject, const bool & adopt = true);

  /**
   * Removes the pointer to the object, from the vector
   * @param CDataObject * pObject
   * @return bool success
   */
  virtual bool remove(CDataObject * pObject);

  void objectRenamed(CDataObject * pObject, const std::string & oldName);

  /**
   * Retrieve the units of the object.
   * @return std::string units
   */
  virtual const std::string getUnits() const;

  /**
   * Retrieve the units of the child object.
   * @return std::string units
   */
  virtual std::string getChildObjectUnits(const CDataObject * pObject) const;

  virtual size_t getIndex(const CDataObject * pObject) const;

  virtual CDataObject * insert(const CData & data);

  /**
   * Retrieve all descendant objects (optionally recursive)
   * @param CDataObject::DataObjectSet & descendants
   * @param const bool & recursive (default: false)
   */
  void getDescendants(CDataObject::DataObjectSet & descendants, const bool & recursive = false) const;

protected:
  void initObjects();

  template <class CType> CDataObjectReference< CType > * addObjectReference(const std::string & name,
      CType & reference,
      const CFlags< Flag > & flag = CFlags< Flag >::None);

  template <class CType> CDataVectorReference< CType > * addVectorReference(const std::string & name,
      CType & reference,
      const CFlags< Flag > & flag = CFlags< Flag >::None);

  template <class CType> CDataMatrixReference< CType > * addMatrixReference(const std::string & name,
      CType & reference,
      const CFlags< Flag > & flag = CFlags< Flag >::None);
};

#include "copasi/core/CDataObjectReference.h"

template <class CType> CDataObjectReference< CType > * CDataContainer::addObjectReference(const std::string & name,
    CType & reference,
    const CFlags< Flag > & flag)
{
  return new CDataObjectReference< CType >(name, this, reference, flag);
}

template <class CType> CDataVectorReference< CType > * CDataContainer::addVectorReference(const std::string & name,
    CType & reference,
    const CFlags< Flag > & flag)
{
  return new CDataVectorReference< CType >(name, this, reference, flag);
}

template <class CType> CDataMatrixReference< CType > * CDataContainer::addMatrixReference(const std::string & name,
    CType & reference,
    const CFlags< Flag > & flag)
{
  return new CDataMatrixReference< CType >(name, this, reference, flag);
}

#endif // COPASI_CDataContainer
