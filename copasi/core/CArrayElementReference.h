// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CArrayElementReference
#define COPASI_CArrayElementReference

#include "copasi/core/CDataObject.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "CArray.h"

/**
 * Class CArrayElementReference
 *
 * This class is used to make an element of an array accessible as
 * a CDataObject. Usually an object from this class will be a child
 * of a CArrayAnnotation and will reference a single element of the
 * array that the CArrayAnnotation points to.
 */
class CArrayElementReference: public CDataObject
{

private:
  //CCopasiAbstractArray::data_type * mpReference;

  /**
   * this contains the index in string format, e.g. "[2][7]"
   */
  std::vector< CRegisteredCommonName > mIndex;
  bool mIgnoreUpdateObjectName;

private:
  /**
   * make the default constructor unaccessible
   */
  CArrayElementReference();

  /**
   * make the copy constructor unaccessible
   */
  CArrayElementReference(const CArrayElementReference & src);

  void updateObjectName();

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CArrayElementReference * pDataObject
   */
  static CArrayElementReference * fromData(const CData & data, CUndoObjectInterface * pParent);

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
  virtual bool applyData(const CData & data, CUndoData::ChangeSet & changes);

  /**
   * create an element reference with a given index. The index
   * is passed as a string, e.g. "[3][2]"
   * The object name will be the index string, the type is "ElementReference"
   * pParent may not be NULL.
   */
  CArrayElementReference(const std::vector< std::string > & index,
                         const CDataContainer * pParent,
                         const CFlags< Flag > & flag = CFlags< Flag >::None);

  virtual ~CArrayElementReference() {}

  /**
   * returns a pointer to the numerical values of the array element
   * this will be a *C_FLOAT64 for this class.
   */
  virtual void * getValuePointer() const;

  virtual const CDataObject * getValueObject() const {return this;}

  /**
   *
   */
  virtual void print(std::ostream * ostream) const;

  /**
   * generate a display name.
   */
  virtual std::string getObjectDisplayName() const;

  /**
   *
   */
  virtual CCommonName getCN() const;
};

#endif
