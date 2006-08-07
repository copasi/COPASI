/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiContainer.h,v $
   $Revision: 1.28 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/07 19:27:10 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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

class CCopasiContainer: public CCopasiObject
  {
    //Attributes
  public:
    static CCopasiContainer * Root;

    static const std::vector< CCopasiContainer * > EmptyList;

    typedef std::multimap< const std::string, CCopasiObject * > objectMap;

  protected:
    objectMap mObjects;

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

    static void init();

    virtual const CCopasiObject * getObject(const CCopasiObjectName & cn) const;

    virtual const CCopasiObject * getValueObject() const;

    virtual const objectMap & getObjects() const;

    virtual bool add(CCopasiObject * pObject, const bool & adopt = true);

    virtual bool remove(CCopasiObject * pObject);

  protected:
    void initObjects();

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

#define RootContainer (*CCopasiContainer::Root)

#endif // COPASI_CCopasiConateiner
