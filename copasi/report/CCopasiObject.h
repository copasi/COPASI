/**
 * Class CCopasiObject
 *
 * This class is the base class for all global accessible objects in copasi.
 *
 * Copyright Stefan Hoops 2002
 */

#ifndef COPASI_CCopasiObject
#define COPASI_CCopasiObject

#include <string>
#include <typeinfo>
#include "copasi.h"

class CCopasiObjectName;
class CCopasiContainer;
template <class CType> class CCopasiObjectReference;
template <class CType> class CCopasiVectorReference;
template <class CType> class CCopasiMatrixReference;

/** @dia:pos 40.5964,2.55372 */
class CCopasiObject
  {
    typedef CCopasiObject referenceType;

    //Attributes
  protected:
    static const unsigned C_INT32 Container;

    static const unsigned C_INT32 Vector;

    static const unsigned C_INT32 Matrix;

    static const unsigned C_INT32 NameVector;

    static const unsigned C_INT32 Reference;

    static const unsigned C_INT32 ValueInt;

    static const unsigned C_INT32 ValueDbl;

    std::string mObjectName;

    std::string mObjectType;

    /** @dia:route 8,0; h,23.7081,53.1343,15.3196,2.55372,40.5964 */
    CCopasiContainer * mpObjectParent;

    unsigned C_INT32 mObjectFlag;

  private:
    static const C_FLOAT64 DummyValue;

    //Operations
  protected:
    CCopasiObject();

    CCopasiObject(const std::string & name,
                  const CCopasiContainer * pParent = NULL,
                  const std::string & type = "CN",
                  const unsigned C_INT32 & flag = 0);

  public:
    CCopasiObject(const CCopasiObject & src,
                  const CCopasiContainer * pParent = NULL);

    virtual ~CCopasiObject();

    virtual const std::string & getName() const;

    virtual const void * getObjectValueAddress() const;

    const std::string & getObjectName() const;

    const std::string & getObjectType() const;

    CCopasiContainer * getObjectParent() const;

    CCopasiContainer * getObjectAncestor(const std::string & type) const;

    virtual CCopasiObjectName getCN() const;

    virtual unsigned C_INT32 getIndex(const CCopasiObject * pObject) const;

    virtual unsigned C_INT32 getIndex(const std::string & name) const;

    virtual const CCopasiObject * getObject(const CCopasiObjectName & cn) const;

    template <class CType> CType * getReference(CType * reference)
    {return reference = (CType *) getReference();}

    bool isContainer() const;

    bool isVector() const;

    bool isMatrix() const;

    bool isNameVector() const;

    bool isReference() const;

    bool hasValueInt() const;
    bool hasValueDbl() const;

    virtual void * getReference();
  };

template <class CType> CCopasiObjectReference< CType > *
createReference(const std::string & name,
                const CCopasiContainer * pParent,
                CType & reference)
{return new CCopasiObjectReference< CType >(name, pParent, reference);}

template <class CType> CCopasiVectorReference< CType > *
createVectorReference(const std::string & name,
                      const CCopasiContainer * pParent,
                      CType & reference)
{return new CCopasiVectorReference< CType >(name, pParent, reference);}

template <class CType> CCopasiMatrixReference< CType > *
createMatrixReference(const std::string & name,
                      const CCopasiContainer * pParent,
                      CType & reference)
{return new CCopasiMatrixReference< CType >(name, pParent, reference);}

#endif // COPASI_CCopasiObject
