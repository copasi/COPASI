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
                           CType & reference):
        CCopasiObject(name, pParent, "Reference", 0),
        mReference(reference)
    {}

    CCopasiObjectReference(const CCopasiObjectReference< CType > & src):
        CCopasiObject(src),
        mReference(src.mReference)
    {}

    virtual ~CCopasiObjectReference() {}

    virtual void * getReference() {return &mReference;}
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
                           CType & reference):
        CCopasiObject(name, pParent, "Reference", 0),
        mReference(reference)
    {}

    CCopasiVectorReference(const CCopasiVectorReference< CType > & src):
        CCopasiObject(src),
        mReference(src.mReference)
    {}

    virtual ~CCopasiVectorReference() {}

    virtual CCopasiObject * getObject(const CCopasiObjectName & C_UNUSED(cn))
    {
      return new CCopasiObjectReference< typename CType::elementType >
      (mObjectName + cn,
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
                           CType & reference):
        CCopasiObject(name, pParent, "Reference", 0),
        mReference(reference)
    {}

    CCopasiMatrixReference(const CCopasiMatrixReference< CType > & src):
        CCopasiObject(src),
        mReference(src.mReference)
    {}

    virtual ~CCopasiMatrixReference() {}

    virtual CCopasiObject * getObject(const CCopasiObjectName & C_UNUSED(cn))
    {
      return new CCopasiObjectReference< typename CType::elementType >
      (mObjectName + cn,
       getObjectParent(),
       mReference(cn.getName(),
                  cn.getName(1)));
    }

    virtual void * getReference() {return &mReference;}
  };
#endif // COPASI_CCopasiObjectReference
