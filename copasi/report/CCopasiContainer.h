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

#include <vector>

#include "CCopasiObject.h"

/** @dia:pos 23.7081,50.8343 */
/** @dia:route CCopasiObject; v,60.054,22.7537,47.9048,40.5521,50.8343 */
class CCopasiContainer: public CCopasiObject
  {
    //Attributes
  protected:
    /** @dia:route 0,8; h,23.7081,50.8343,19.6311,4.45372,40.5964 */
    std::vector< CCopasiObject * > mObjects;

    // Operations
  private:
    CCopasiContainer();

  public:
    CCopasiContainer(const std::string & name,
                     const CCopasiContainer * pParent = NULL,
                     const std::string & type = "CN",
                     const unsigned C_INT32 & flag = 1);

    CCopasiContainer(const CCopasiContainer & src,
                     const CCopasiContainer * pParent = NULL);

    virtual ~CCopasiContainer();

    virtual const CCopasiObject * getObject(const CCopasiObjectName & cn) const;

    const std::vector< CCopasiObject * > & getObjects() const
      {return mObjects;}

  protected:
    virtual void initObjects();

    void add(CCopasiObject * object);

    template <class CType> void addObjectReference(const std::string & name,
        CType & reference)
    {add(CCopasiObject::createReference(name, this, reference));}

    template <class CType> void addVectorReference(const std::string & name,
        CType & reference)
    {add(CCopasiObject::createVectorReference(name, this, reference));}

    template <class CType> void addMatrixReference(const std::string & name,
        CType & reference)
    {add(CCopasiObject::createMatrixReference(name, this, reference));}
  };

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

#define RootContainer CRootContainer::ref()

#endif // COPASI_CCopasiConateiner
