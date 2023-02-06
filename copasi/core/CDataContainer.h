// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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
#include "copasi/core/CDataObjectMap.h"

template <class CType> class CDataObjectReference;
template <class CType> class CDataVectorReference;
template <class CType> class CDataMatrixReference;
class CUnit;

class CDataContainer: public CDataObject
{
  //Attributes
public:
  static const CObjectInterface::ContainerList EmptyList;

  typedef CDataObjectMap objectMap;

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
  static CDataContainer * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const override;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes) override;

  /**
   * Create the undo data which represents the changes recording the
   * differences between the provided oldData and the current data.
   * @param CUndoData & undoData
   * @param const CUndoData::Type & type
   * @param const CData & oldData (default: empty data)
   * @param const CCore::Framework & framework (default: CCore::Framework::ParticleNumbers)
   * @return CUndoData undoData
   */
  virtual void createUndoData(CUndoData & undoData,
                              const CUndoData::Type & type,
                              const CData & oldData = CData(),
                              const CCore::Framework & framework = CCore::Framework::ParticleNumbers) const override;

  /**
   * Append all required dependent undo data
   * @param CUndoData & undoData
   * @return bool dataAppended
   */
  virtual bool appendDeletedDependentData(CUndoData & undoData) const;

  CDataContainer(const std::string & name,
                 const CDataContainer * pParent = NO_PARENT,
                 const std::string & type = "CN",
                 const CFlags< Flag > & flag = CFlags< Flag >::None);

  CDataContainer(const CDataContainer & src,
                 const CDataContainer * pParent);

  virtual ~CDataContainer();

  virtual const CObjectInterface * getObject(const CCommonName & cn) const override;

  virtual const CDataObject * getValueObject() const override;

  virtual const objectMap & getObjects() const;
  virtual objectMap & getObjects();

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
  virtual const std::string getUnits() const override;

  /**
   * Retrieve the units of the child object.
   * @return std::string units
   */
  virtual std::string getChildObjectUnits(const CDataObject * pObject) const;

  virtual size_t getIndex(const CDataObject * pObject) const;

  /**
   * Create and insert an undo object based on the given data.
   * This method needs to be re-implemented in container which support INSERT and REMOVE
   * @param const CData & data
   * @return CUndoObjectInterface * pUndoObject
   */
  virtual CUndoObjectInterface * insert(const CData & data) override;

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
