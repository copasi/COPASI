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
#include "CCopasiObject.h"

/** @dia:pos 23.7081,50.8343 */
/** @dia:route CCopasiObject; v,60.054,22.7537,47.9048,40.5521,50.8343 */
class CCopasiContainer: public CCopasiObject
  {
    friend CCopasiObject::CCopasiObject(const std::string & name,
                                        const CCopasiContainer * pParent,
                                        const std::string & type,
                                        const unsigned C_INT32 & flag);

    friend CCopasiObject::CCopasiObject(const CCopasiObject & src,
                                        const CCopasiContainer * pParent);

    friend CCopasiObject::~CCopasiObject();

    //Attributes
  public:
    static CCopasiContainer * Root;

    typedef std::multimap< const std::string, CCopasiObject * > objectMap;
  protected:
    /** @dia:route 0,8; h,23.7081,50.8343,19.6311,4.45372,40.5964 */
    objectMap mObjects;

    // Operations
  private:
    CCopasiContainer();

  public:
    CCopasiContainer(const std::string & name,
                     const CCopasiContainer * pParent = NULL,
                     const std::string & type = "CN",
                     const unsigned C_INT32 & flag = CCopasiObject::Container);

    CCopasiContainer(const CCopasiContainer & src,
                     const CCopasiContainer * pParent = NULL);

    virtual ~CCopasiContainer();

    virtual const std::string getObjectUniqueName() const;

    static void init();

    virtual const CCopasiObject * getObject(const CCopasiObjectName & cn) const;

    virtual const objectMap & getObjects() const;

    virtual bool add(CCopasiObject * pObject, const bool & adopt = true);

    bool remove(CCopasiObject * pObject);

  protected:
    virtual void initObjects();

    template <class CType> void addObjectReference(const std::string & name,
        CType & reference)
    {createReference(name, this, reference);}

    template <class CType> void addVectorReference(const std::string & name,
        CType & reference)
    {createVectorReference(name, this, reference);}

    template <class CType> void addMatrixReference(const std::string & name,
        CType & reference)
    {createMatrixReference(name, this, reference);}
  };

#ifdef XXXX 
/** @dia:pos 33.0468,37.5833 */
class CRootContainer
      /** @dia:pos 23.7081,60.7007 */
  {
    // Attributes
  private:
    /** @dia:route 14,0; h,23.7081,55.5343,20.3803,60.7007,23.7081 */
    static CCopasiContainer mRoot;

    // Operations
  private:
    CRootContainer();

  public:
    ~CRootContainer();

    static CCopasiContainer & ref();
  };
#endif // XXXX

#define RootContainer *CCopasiContainer::Root

#endif // COPASI_CCopasiConateiner
