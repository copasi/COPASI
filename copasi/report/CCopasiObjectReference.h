/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiObjectReference.h,v $
   $Revision: 1.19 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/07/06 17:41:30 $
   End CVS Header */

/**
 * Class CCopasiObjectReference
 *
 * This class is the is used to make an existing object gobally accesible.
 *
 * Copyright Stefan Hoops 2002
 */

#ifndef COPASI_CCopasiObjectReference
#define COPASI_CCopasiObjectReference

#include "CCopasiObject.h"

/** @dia:pos 64.092,27.0418 */
/** @dia:route CCopasiObject; v,60.054,22.7537,25.1206,81.8072,27.0418 */
template <class CType> class CCopasiObjectReference: public CCopasiObject
  {
    typedef CType referenceType;

    //Attributes
  private:
    CType & mReference;

    //Operations
  private:
    CCopasiObjectReference() {};

  public:
    CCopasiObjectReference(const std::string & name,
                           const CCopasiContainer * pParent,
                           referenceType & reference,
                           const unsigned C_INT32 & flag = 0):
        CCopasiObject(name, pParent, "Reference",
                      CCopasiObject::Reference |
                      CCopasiObject::NonUniqueName |
                      flag),
        mReference(reference)
    {}

    CCopasiObjectReference(const CCopasiObjectReference< referenceType > & src):
        CCopasiObject(src),
        mReference(src.mReference)
    {}

    virtual ~CCopasiObjectReference() {}

    virtual void * getReference() {return &mReference;}

    virtual void print(std::ostream * ostream) const
      {(*ostream) << mReference;};
  };

/** @dia:pos 64.092,38.1129 */
/** @dia:route CCopasiObject; v,60.054,22.7537,36.0826,82.52,38.1129 */
template <class CType> class CCopasiVectorReference: public CCopasiObject
  {
    typedef CType referenceType;

    //Attributes
  private:
    CType & mReference;

    //Operations
  private:
    CCopasiVectorReference() {};

  public:
    CCopasiVectorReference(const std::string & name,
                           const CCopasiContainer * pParent,
                           referenceType & reference,
                           const unsigned C_INT32 & flag = 0):
        CCopasiObject(name, pParent, "Reference",
                      CCopasiObject::Reference | CCopasiObject::NonUniqueName),
        mReference(reference)
    {}

    CCopasiVectorReference(const CCopasiVectorReference< referenceType > & src):
        CCopasiObject(src),
        mReference(src.mReference)
    {}

    virtual ~CCopasiVectorReference() {}

    virtual CCopasiObject * getObject(const CCopasiObjectName & cn)
    {
#ifdef WIN32
      return new CCopasiObjectReference< referenceType::elementType >
#else
      return new CCopasiObjectReference< typename referenceType::elementType >
#endif
      (getObjectName() + cn,
       getObjectParent(),
       mReference[cn.getElementIndex()],
       isValueBool() ? CCopasiObject::ValueBool :
       isValueInt() ? CCopasiObject::ValueInt :
       isValueDbl() ? CCopasiObject::ValueDbl : (CCopasiObject::Flag) 0
);
    }

    virtual void * getReference() {return &mReference;}
  };

/** @dia:pos 64.092,50.0714 */
/** @dia:route CCopasiObject; v,60.054,22.7537,47.8736,82.52,50.0714 */
template <class CType> class CCopasiMatrixReference: public CCopasiObject
  {
    typedef CType referenceType;

    //Attributes
  private:
    CType & mReference;

    //Operations
  private:
    CCopasiMatrixReference() {};

  public:
    CCopasiMatrixReference(const std::string & name,
                           const CCopasiContainer * pParent,
                           referenceType & reference,
                           const unsigned C_INT32 & flag = 0):
        CCopasiObject(name, pParent, "Reference",
                      CCopasiObject::Reference | CCopasiObject::NonUniqueName),
        mReference(reference)
    {}

    CCopasiMatrixReference(const CCopasiMatrixReference< referenceType > & src):
        CCopasiObject(src),
        mReference(src.mReference)
    {}

    virtual ~CCopasiMatrixReference() {}

    virtual CCopasiObject * getObject(const CCopasiObjectName & cn)
    {
#ifdef WIN32
      return new CCopasiObjectReference< referenceType::elementType >
#else
      return new CCopasiObjectReference< typename referenceType::elementType >
#endif
      (getObjectName() + cn,
       getObjectParent(),
       mReference(cn.getElementIndex(),
                  cn.getElementIndex(1)),
       isValueBool() ? CCopasiObject::ValueBool :
       isValueInt() ? CCopasiObject::ValueInt :
       isValueDbl() ? CCopasiObject::ValueDbl : (CCopasiObject::Flag) 0);
    }

    virtual void * getReference() {return &mReference;}
  };
#endif // COPASI_CCopasiObjectReference
