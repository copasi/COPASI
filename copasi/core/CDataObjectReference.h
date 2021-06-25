// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * Class CDataObjectReference
 *
 * This class is the is used to make an existing object globally accessible.
 *
 * Copyright Stefan Hoops 2002
 */

#ifndef COPASI_CDataContainer
# include "copasi/core/CDataContainer.h"
#endif

#ifndef COPASI_CDataObjectReference
#define COPASI_CDataObjectReference

#include <assert.h>

#include "copasi/core/CRegisteredCommonName.h"

template <class CType> class CDataObjectReference: public CDataObject
{
public:
  typedef CType referenceType;

  //Attributes
private:
  CType * mpReference;

  //Operations
private:
  CDataObjectReference():
    mpReference(NULL)
  {};

public:
  // Data methods do not apply as these references point to memory locations during runtime.
  CDataObjectReference(const std::string & name,
                       const CDataContainer * pParent,
                       referenceType & reference,
                       const CFlags< Flag > & flag = CFlags< Flag >::None):
    CDataObject(name, pParent, "Reference", flag | CDataObject::Reference | CDataObject::NonUniqueName),
    mpReference(&reference)
  {}

  CDataObjectReference(const CDataObjectReference< referenceType > & src,
                       const CDataContainer * pParent):
    CDataObject(src, pParent),
    mpReference(src.mpReference)
  {}

  virtual ~CDataObjectReference() {}

  virtual void * getValuePointer() const {return mpReference;}

  virtual const CDataObject * getValueObject() const {return this;}

  virtual void print(std::ostream * ostream) const
  {(*ostream) << *mpReference;};

  virtual std::string getObjectDisplayName() const
  {
    // Suppress "Value"
    if (getObjectParent() && getObjectName() == "Value")
      return getObjectParent()->getObjectDisplayName();

    // Suppress "DisplayName"
    if (getObjectName() == "DisplayName" && mpReference)
      {
        std::stringstream str;
        str << "'" << *mpReference << "'";
        return str.str();
      }

    // Special treatment for Avogadro Constant
    if (getObjectName() == "Avogadro Constant"
        && getObjectParent()
        && (getObjectParent()->getObjectType() == "Model"
            || getObjectParent()->getObjectType() == "FunctionDB"))
      return getObjectName();

    // Special treatment of species children
    if (getObjectParent() && getObjectParent()->getObjectType() == "Metabolite")
      {
        if (getObjectName() == "Concentration")
          {
            return "[" + getObjectParent()->getObjectDisplayName() + "]";
          }

        if (getObjectName() == "InitialConcentration")
          {
            return "[" + getObjectParent()->getObjectDisplayName() + "]_0";
          }
      }

    return CDataObject::getObjectDisplayName();
  }

  void setReference(referenceType & reference)
  {
    mpReference = &reference;
  }
};

template<> inline CDataObjectReference< double >::CDataObjectReference(const std::string & name,
    const CDataContainer * pParent,
    double & reference,
    const CFlags< Flag > & flag) :
  CDataObject(name, pParent, "Reference",
              flag | CDataObject::Reference | CDataObject::NonUniqueName | CDataObject::ValueDbl),
  mpReference(&reference)
{
  assert(pParent != NULL);
}

template<> inline CDataObjectReference< int >::CDataObjectReference(const std::string & name,
    const CDataContainer * pParent,
    int & reference,
    const CFlags< Flag > & flag) :
  CDataObject(name, pParent, "Reference",
              flag | CDataObject::Reference | CDataObject::NonUniqueName | CDataObject::ValueInt),
  mpReference(&reference)
{
  assert(pParent != NULL);
}

template<> inline CDataObjectReference< bool >::CDataObjectReference(const std::string & name,
    const CDataContainer * pParent,
    bool & reference,
    const CFlags< Flag > & flag) :
  CDataObject(name, pParent, "Reference",
              flag | CDataObject::Reference | CDataObject::NonUniqueName | CDataObject::ValueBool),
  mpReference(&reference)
{
  assert(pParent != NULL);
}

template <class CType> class CDataVectorReference: public CDataObject
{
public:
  typedef CType referenceType;

  //Attributes
private:
  CType & mReference;

  //Operations
private:
  CDataVectorReference():
    mReference(CType())
  {};

public:
  // Data methods do not apply as these references point to memory locations during runtime.
  CDataVectorReference(const std::string & name,
                       const CDataContainer * pParent,
                       referenceType & reference,
                       const CFlags< Flag > & flag = CFlags< Flag >::None):
    CDataObject(name, pParent, "Reference",
                flag | CDataObject::Reference | CDataObject::NonUniqueName),
    mReference(reference)
  {
    assert(pParent != NULL);
  }

  CDataVectorReference(const CDataVectorReference< referenceType > & src,
                       const CDataContainer * pParent):
    CDataObject(src, pParent),
    mReference(src.mReference)
  {
    assert(pParent != NULL);
  }

  virtual ~CDataVectorReference() {}

  virtual CDataObject * getObject(const CCommonName & cn)
  {
    size_t Index = cn.getElementIndex();

    if (Index < mReference.size())
      return new CDataObjectReference< typename referenceType::elementType >(getObjectName() + cn,
             getObjectParent(),
             mReference[Index]);

    return NULL;
  }

  virtual void * getValuePointer() const {return &mReference;}

  virtual const CDataObject * getValueObject() const {return this;}

  /**
   * This is the output method for any object. The default implementation
   * provided with CDataObject uses the ostream operator<< of the object
   * to print the object.To override this default behavior one needs to
   * reimplement the virtual print function.
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const
  {*ostream << mReference;}
};

template <class CType> class CDataMatrixReference: public CDataObject
{
public:
  typedef CType referenceType;

  //Attributes
private:
  CType & mReference;

  //Operations
private:
  CDataMatrixReference():
    mReference(CType())
  {};

public:
  // Data methods do not apply as these references point to memory locations during runtime.
  CDataMatrixReference(const std::string & name,
                       const CDataContainer * pParent,
                       referenceType & reference,
                       const CFlags< Flag > & flag = CFlags< Flag >::None):
    CDataObject(name, pParent, "Reference",
                flag | CDataObject::Reference | CDataObject::NonUniqueName),
    mReference(reference)
  {
    assert(pParent != NULL);
  }

  CDataMatrixReference(const CDataMatrixReference< referenceType > & src,
                       const CDataContainer * pParent):
    CDataObject(src, pParent),
    mReference(src.mReference)
  {
    assert(pParent != NULL);
  }

  virtual ~CDataMatrixReference() {}

  virtual CDataObject * getObject(const CCommonName & cn)
  {
    size_t Index_0 = cn.getElementIndex(0);
    size_t Index_1 = cn.getElementIndex(1);

    if (Index_0 < mReference.numRows() &&
        Index_1 < mReference.numCols())
      return new CDataObjectReference< typename referenceType::elementType >(getObjectName() + cn,
             getObjectParent(),
             mReference(cn.getElementIndex(), cn.getElementIndex(1)));

    return NULL;
  }

  virtual void * getValuePointer() const {return &mReference;}
  virtual const CDataObject * getValueObject() const {return this;}
};
#endif // COPASI_CDataObjectReference
