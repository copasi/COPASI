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
                           referenceType & reference):
        CCopasiObject(name, pParent, "Reference", CCopasiObject::Reference),
        mReference(reference)
    {}

    CCopasiObjectReference(const CCopasiObjectReference< referenceType > & src):
        CCopasiObject(src),
        mReference(src.mReference)
    {}

    virtual ~CCopasiObjectReference() {}

    virtual void * getReference() {return &mReference;}

    // inherited from CCopasiObject. TODO: The hasValue flag needs to be set in the contructors.
    virtual const void * getObjectValueAddress() const {return &mReference;}
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
                           referenceType & reference):
        CCopasiObject(name, pParent, "Reference", CCopasiObject::Reference),
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
       mReference[cn.getIndex()]);
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
                           referenceType & reference):
        CCopasiObject(name, pParent, "Reference", CCopasiObject::Reference),
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
       mReference(cn.getIndex(),
                  cn.getIndex(1)));
    }

    virtual void * getReference() {return &mReference;}
  };
#endif // COPASI_CCopasiObjectReference
