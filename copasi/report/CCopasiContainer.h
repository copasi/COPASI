/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiContainer.h,v $
   $Revision: 1.23 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/03/17 19:56:00 $
   End CVS Header */

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
#include <vector>

#include "CCopasiObject.h"

/** @dia:pos 23.7081,50.8343 */
/** @dia:route CCopasiObject; v,60.054,22.7537,47.9048,40.5521,50.8343 */
class CCopasiContainer: public CCopasiObject
  {
    //Attributes
  public:
    static CCopasiContainer * Root;

    static const std::vector< CCopasiContainer * > EmptyList;

    typedef std::multimap< const std::string, CCopasiObject * > objectMap;

    typedef std::map < const CCopasiObject *,
    bool (CCopasiContainer::*)(const C_FLOAT64 & value) > updateMap;

  protected:
    /** @dia:route 0,8; h,23.7081,50.8343,19.6311,4.45372,40.5964 */
    objectMap mObjects;

    updateMap mUpdates;

    // Operations
  private:
    CCopasiContainer();

  public:
    /**
     * @param const std::vector< CCopasiContainer * > &listOfContainer
     * @param const CCopasiObjectName& objName
     * @return CCopasiObject * pObject
     */
    static
    CCopasiObject * ObjectFromName(const std::vector< CCopasiContainer * > & listOfContainer,
                                   const CCopasiObjectName & objName);

    static
    CCopasiObject * ObjectFromName(const CCopasiObjectName & objName);

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

    virtual bool addUpdateMethod(const CCopasiObject * pObject,
                                 bool (CCopasiContainer::*updateMethod)(const C_FLOAT64 & value));

    virtual bool remove(CCopasiObject * pObject);

    virtual bool setChildValue(const CCopasiObject * pChild,
                               const C_FLOAT64 & value);

  protected:
    virtual void initObjects();

    template <class CType> CCopasiObject * addObjectReference(const std::string & name,
        CType & reference,
        const unsigned C_INT32 & flag = 0)
    {return createReference(name, this, reference, flag);}

    template <class CType> CCopasiObject * addVectorReference(const std::string & name,
        CType & reference,
        const unsigned C_INT32 & flag = 0)
    {return createVectorReference(name, this, reference, flag);}

    template <class CType> CCopasiObject * addMatrixReference(const std::string & name,
        CType & reference,
        const unsigned C_INT32 & flag = 0)
    {return createMatrixReference(name, this, reference, flag);}
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

#define RootContainer (*CCopasiContainer::Root)

#endif // COPASI_CCopasiConateiner
