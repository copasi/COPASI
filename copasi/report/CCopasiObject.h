// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiObject.h,v $
//   $Revision: 1.73 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/09/22 22:15:11 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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
#include <iostream>
#include <vector>
#include <set>
#include <list>

#include "copasi.h"

class CCopasiObjectName;
class CCopasiContainer;
class CCopasiObject;
class CModel;

template <class CType> class CCopasiObjectReference;
template <class CType> class CCopasiVectorReference;
template <class CType> class CCopasiMatrixReference;

#ifdef WIN32
template <class CType> class CCopasiVector;
#endif // WIN32

class UpdateMethod
  {
  public:

    virtual ~UpdateMethod(){};

    virtual void operator()(const C_FLOAT64 & C_UNUSED(value))
    {return;}

    virtual void operator()(const C_INT32 & C_UNUSED(value))
    {return;}

    virtual void operator()(const bool & C_UNUSED(value))
    {return;}
  };

template <class CType, class VType> class SpecificUpdateMethod : public UpdateMethod
    {
    private:
      void (CType::*mMethod)(const VType &);   // pointer to member function
      CType * mpType;                                    // pointer to object

    public:

      // constructor - takes pointer to an object and pointer to a member and stores
      // them in two private variables
      SpecificUpdateMethod(CType * pType,
                           void(CType::*method)(const VType &))
      {
        mpType = pType;
        mMethod = method;
      };

      virtual ~SpecificUpdateMethod(){};

      // override operator "()"
      virtual void operator()(const VType & value)
      {(*mpType.*mMethod)(value);}      ;              // execute member function
    };

class Refresh
  {
  protected:
    Refresh()
    {}

  public:
    virtual ~Refresh(){}

    virtual void operator()(void)
    {return;}

    virtual bool isEqual(Refresh *const rhs) const
      {return (this == rhs);}

    virtual CCopasiObject * getObject() const
      {return NULL;}
  };

template <typename CClass> class RefreshTemplate : public Refresh
  {
  private:
    CClass * mpInstance;             // pointer to object
    void (CClass::*mMethod)(void);   // pointer to member function

  private:
    RefreshTemplate():
        Refresh(),
        mpInstance(NULL),
        mMethod(NULL)
    {}

  public:
    // constructor - takes pointer to an object and pointer to a member and stores
    // them in two private variables
    RefreshTemplate(CClass * pInstance, void (CClass::*method)(void)):
        Refresh(),
        mpInstance(pInstance),
        mMethod(method)
    {}

    virtual ~RefreshTemplate(){};

    // override operator "()"
    virtual void operator()(void)
    {(*mpInstance.*mMethod)();}  // execute member function

    virtual CCopasiObject * getObject() const
      {return mpInstance;}

    virtual bool isEqual(Refresh *const rhs) const
      {
        const RefreshTemplate< CClass > * pRhs =
          dynamic_cast< RefreshTemplate< CClass > * >(rhs);

        if (!pRhs) return false;

        return (mpInstance == pRhs->mpInstance && mMethod == pRhs->mMethod);
      }
  };

class CRenameHandler;

//********************************************************************************

class CCopasiObject
  {
#ifdef WIN32
    friend CCopasiVector< CCopasiObject >;
#endif // WIN32

    typedef CCopasiObject referenceType;

    //Attributes
  protected:
    enum Flag
    {
      Container = 0x1,
      Vector = 0x2,
      Matrix = 0x4,
      NameVector = 0x8,
      Reference = 0x10,
      ValueBool = 0x20,
      ValueInt = 0x40,
      ValueDbl = 0x80,
      NonUniqueName = 0x100,
      StaticString = 0x200,
      ValueString = 0x400,
      Separator = 0x800,
      ModelEntity = 0x1000,
      Array = 0x2000  //the object represents an n-dimensional array
    };

  private:
    std::string mObjectName;

    std::string mObjectType;

    CCopasiContainer * mpObjectParent;

    unsigned C_INT32 mObjectFlag;

  protected:
    /**
     * A list of all objects the object depends on directly, i.e, the
     * objects which are used to calculate the object.
     */
    std::set< const CCopasiObject * > mDependencies;

  private:

    UpdateMethod * mpUpdateMethod;

    Refresh * mpRefresh;

    static const C_FLOAT64 DummyValue;

    static UpdateMethod mDefaultUpdateMethod;

  protected:
    static const CRenameHandler * smpRenameHandler;

    //Operations
    CCopasiObject();

    CCopasiObject(const std::string & name,
                  const CCopasiContainer * pParent = NULL,
                  const std::string & type = "CN",
                  const unsigned C_INT32 & flag = 0);

  public:
    CCopasiObject(const CCopasiObject & src,
                  const CCopasiContainer * pParent = NULL);

    virtual ~CCopasiObject();

    /**
     * This is the output method for any object. The default implementation
     * provided with CCopasiObject uses the ostream operator<< of the object
     * to print the object.To overide this default behaviour one needs to
     * reimplement the virtual print function.
     * @param std::ostream * ostream
     */
    virtual void print(std::ostream * ostream) const;

    /**
     * Set the name of the object.
     * Note: An attempt set the name to "" results in the name
     *       being set to "No Name".
     * @param const std::string & name
     * @return success
     */
    bool setObjectName(const std::string & name);

    const std::string & getObjectName() const;

    virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;

    const std::string & getObjectType() const;

    virtual bool setObjectParent(const CCopasiContainer * pParent);

    CCopasiContainer * getObjectParent() const;

    CCopasiContainer * getObjectAncestor(const std::string & type) const;

    virtual CCopasiObjectName getCN() const;

    virtual const CCopasiObject * getObject(const CCopasiObjectName & cn) const;

    /**
     * Set the direct dependencies
     * @param const std::set< const CCopasiObject * > & directDependencies
     */
    void setDirectDependencies(const std::set< const CCopasiObject * > & directDependencies);

    /**
     * Retrieve the list of direct dependencies
     * @return const std::set< const CCopasiObject * > & directDependencies
     */
    const std::set< const CCopasiObject * > & getDirectDependencies() const;

    /**
     * Add a the object to the direct dependencies
     * @param const CCopasiObject * pObject
     */
    void addDirectDependency(const CCopasiObject * pObject);

    /**
     * If called with an empty set of dependencies it retrieves the complete list
     * of all dependencies (including all indirect) of the current object.
     * If called with a non empty set it will only add any dependency and all its
     * dependencies to the list if the dependency is not already among the dependencies
     * @param std::set< const CCopasiObject * > & dependencies
     */
    void getAllDependencies(std::set< const CCopasiObject * > & dependencies) const;

    /**
     * Check whether the current object depends on any objects in the candidates.
     * @param std::set< const CCopasiObject * > & candidates
     * @return bool dependsOn
     */
    bool dependsOn(std::set< const CCopasiObject * > & candidates) const;

    /**
     * If called with an empty set it will check whether the current object and all its
     * dependencies (including all indirect) form a circular dependency.
     * If called with a non empty set it check whether the candidates plus the current object
     * and all its dependencies form a circular dependency.
     * @param std::set< const CCopasiObject * > & dependencies
     * @param std::set< const CCopasiObject * > & verified
     * @return bool hasCircularDependencies
     */
    bool hasCircularDependencies(std::set< const CCopasiObject * > & candidates,
                                 std::set< const CCopasiObject * > & verified) const;

    /**
     * Build the update sequence for the given list of objects. The resulting sequence
     * takes the dependencies of the objects in consideration. If circular dependencies
     * are detected an exception is thrown
     * @param const std::set< const CCopasiObject * > & objects
     * @param CModel * pModel
     * @return std::vector< Refresh * > updateSequence
     */
    static std::vector< Refresh * > buildUpdateSequence(const std::set< const CCopasiObject * > & objects,
        const std::set< const CCopasiObject * > & uptoDateObjects);

    /**
     * Retrieve the units of the object.
     * @return std::string units
     */
    virtual std::string getUnits() const;

    /**
     * Comparison operator which can be used to sort objects based on their dependencies
     * If the object *lhs is a dependency of *rhs and must be evaluated first the operator
     * return true.
     * @param const CCopasiObject * lhs
     * @param const CCopasiObject * rhs
     * @return bool isLess
     */
    static
    bool compare(const CCopasiObject * lhs, const CCopasiObject * rhs);

    bool isContainer() const;

    bool isVector() const;

    bool isMatrix() const;

    bool isNameVector() const;

    bool isReference() const;

    bool isValueBool() const;
    bool isValueInt() const;
    bool isValueDbl() const;
    bool isNonUniqueName() const;
    bool isStaticString() const;
    bool isValueString() const;
    bool isSeparator() const;
    bool isArray() const;

    virtual void * getValuePointer() const;

    virtual const CCopasiObject * getValueObject() const;

    friend std::ostream &operator<<(std::ostream &os, const CCopasiObject & o);

    virtual const std::string & getKey() const;

    void setObjectValue(const C_FLOAT64 & value);
    void setObjectValue(const C_INT32 & value);
    void setObjectValue(const bool & value);

    template <class CType>
    void setUpdateMethod(CType * pType,
                         void (CType::*method)(const C_FLOAT64 &))
    {
      if (mpUpdateMethod != &mDefaultUpdateMethod)
        pdelete(mpUpdateMethod);

      mpUpdateMethod =
        new SpecificUpdateMethod< CType, C_FLOAT64 >(pType, method);

      return;
    }

    template <class CType>
    void setUpdateMethod(CType * pType,
                         void (CType::*method)(const C_INT32 &))
    {
      if (mpUpdateMethod != &mDefaultUpdateMethod)
        pdelete(mpUpdateMethod);

      mpUpdateMethod =
        new SpecificUpdateMethod< CType, C_INT32 >(pType, method);

      return;
    }

    template <class CType>
    void setUpdateMethod(CType * pType,
                         void (CType::*method)(const bool &))
    {
      if (mpUpdateMethod != &mDefaultUpdateMethod)
        pdelete(mpUpdateMethod);

      mpUpdateMethod =
        new SpecificUpdateMethod< CType, bool >(pType, method);

      return;
    }

    UpdateMethod * getUpdateMethod() const;

    bool hasUpdateMethod() const;

    template <class CType>
    void setRefresh(CType * pType,
                    void (CType::*method)(void))
    {
      pdelete(mpRefresh);

      mpRefresh =
        new RefreshTemplate< CType >(pType, method);

      return;
    }

    void clearRefresh();

    Refresh * getRefresh() const;

    static void setRenameHandler(CRenameHandler* rh)
    {smpRenameHandler = rh;}
  };

template <class CType> CCopasiObjectReference< CType > *
createReference(const std::string & name,
                const CCopasiContainer * pParent,
                CType & reference,
                const unsigned C_INT32 & flag = 0)
{return new CCopasiObjectReference< CType >(name, pParent, reference, flag);}

template <class CType> CCopasiVectorReference< CType > *
createVectorReference(const std::string & name,
                      const CCopasiContainer * pParent,
                      CType & reference,
                      const unsigned C_INT32 & flag = 0)
{return new CCopasiVectorReference< CType >(name, pParent, reference, flag);}

template <class CType> CCopasiMatrixReference< CType > *
createMatrixReference(const std::string & name,
                      const CCopasiContainer * pParent,
                      CType & reference,
                      const unsigned C_INT32 & flag = 0)
{return new CCopasiMatrixReference< CType >(name, pParent, reference, flag);}

/**
 * Sort the CCopasiObjects in the interval [begin, end) according to
 * their dependencies
 * @param ForwardAccessIterator begin
 * @param ForwardAccessIterator end
 * @return std::list< const CCopasiObject * >
 */
template <typename ForwardAccessIterator>
std::list< const CCopasiObject * > sortObjectsByDependency(ForwardAccessIterator begin,
    ForwardAccessIterator end)
{
  std::list< const CCopasiObject * > SortedList;
  std::list< const CCopasiObject * >::iterator itList;
  std::list< const CCopasiObject * >::iterator endList;

  std::set< const CCopasiObject * > AllDependencies;
  std::list< std::set< const CCopasiObject * > > DependencyList;
  std::list< std::set< const CCopasiObject * > >::iterator itDependencies;

  for (; begin != end; ++begin)
    {
      AllDependencies.clear();
      (*begin)->getAllDependencies(AllDependencies);

      itList = SortedList.begin();
      endList = SortedList.end();
      itDependencies = DependencyList.begin();

      for (; itList != endList; ++itList, ++itDependencies)
        if (itDependencies->count(*begin)) break;

      SortedList.insert(itList, *begin);
      DependencyList.insert(itDependencies, AllDependencies);
    }

  return SortedList;
}

#endif // COPASI_CCopasiObject
