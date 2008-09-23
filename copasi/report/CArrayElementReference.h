// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CArrayElementReference.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/09/23 06:22:25 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CArrayElementReference
#define COPASI_CArrayElementReference

#include "CCopasiArray.h"
#include "CCopasiObject.h"

#include "CCopasiObjectName.h"

/**
 * Class CArrayElementReference
 *
 * This class is the is used to make an existing object gobally accesible.
 *
 */
class CArrayElementReference: public CCopasiObject
  {

    //Attributes
  private:
    CCopasiAbstractArray::data_type * mpReference;

    //Operations
  private:
    CArrayElementReference() {};

    void updateMethod(const CCopasiAbstractArray::data_type & value)
    {*mpReference = value;}

  public:
    CArrayElementReference(const std::string & name,
                           const CCopasiContainer * pParent,
                           CCopasiAbstractArray::data_type & reference,
                           const unsigned C_INT32 & flag = CCopasiObject::ValueDbl);

  private:
    CArrayElementReference(const CArrayElementReference & src);
    //: CCopasiObject(src),
    //    mpReference(src.mpReference)
    //{}

  public:
    virtual ~CArrayElementReference() {}

    virtual void * getValuePointer() const {return mpReference;}

    virtual const CCopasiObject * getValueObject() const {return this;}

    //virtual void setReference(CCopasiAbstractArray::data_type & reference)
    // {mpReference = &reference;}

    virtual void print(std::ostream * ostream) const
      {(*ostream) << *mpReference;};

    virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;
  };

#ifdef xxxx
template<> inline
CCopasiObjectReference<C_FLOAT64>::CCopasiObjectReference(const std::string & name,
    const CCopasiContainer * pParent,
    referenceType & reference,
    const unsigned C_INT32 & flag):
    CCopasiObject(name, pParent, "Reference",
                  CCopasiObject::Reference |
                  CCopasiObject::NonUniqueName |
                  flag),
    mpReference(&reference)
{
  assert(pParent != NULL);
  setUpdateMethod(this, &CCopasiObjectReference<C_FLOAT64>::updateMethod);
}

template<> inline
CCopasiObjectReference<C_INT32>::CCopasiObjectReference(const std::string & name,
    const CCopasiContainer * pParent,
    referenceType & reference,
    const unsigned C_INT32 & flag):
    CCopasiObject(name, pParent, "Reference",
                  CCopasiObject::Reference |
                  CCopasiObject::NonUniqueName |
                  flag),
    mpReference(&reference)
{
  assert(pParent != NULL);
  setUpdateMethod(this, &CCopasiObjectReference<C_INT32>::updateMethod);
}

template<> inline
CCopasiObjectReference<bool>::CCopasiObjectReference(const std::string & name,
    const CCopasiContainer * pParent,
    referenceType & reference,
    const unsigned C_INT32 & flag):
    CCopasiObject(name, pParent, "Reference",
                  CCopasiObject::Reference |
                  CCopasiObject::NonUniqueName |
                  flag),
    mpReference(&reference)
{
  assert(pParent != NULL);
  setUpdateMethod(this, &CCopasiObjectReference<bool>::updateMethod);
}
#endif

#endif
