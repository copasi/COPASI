/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiObject.h,v $
   $Revision: 1.48 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/04/12 15:06:33 $
   End CVS Header */

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
#include <iostream>
#include "copasi.h"

class CCopasiObjectName;
class CCopasiContainer;
template <class CType> class CCopasiObjectReference;
template <class CType> class CCopasiVectorReference;
template <class CType> class CCopasiMatrixReference;

#ifdef WIN32
template <class CType> class CCopasiVector;
#endif // WIN32

class UpdateMethod
  {
  public:

    virtual bool operator()(const C_FLOAT64 & C_UNUSED(value))
    {return false;}

    virtual bool operator()(const C_INT32 & C_UNUSED(value))
    {return false;}

    virtual bool operator()(const bool & C_UNUSED(value))
    {return false;}
  };

template <class CType, class VType> class SpecificUpdateMethod : public UpdateMethod
    {
    private:
      bool (CType::*mMethod)(const VType &);   // pointer to member function
      CType * mpType;                                    // pointer to object

    public:

      // constructor - takes pointer to an object and pointer to a member and stores
      // them in two private variables
      SpecificUpdateMethod(CType * pType,
                           bool(CType::*method)(const VType &))
      {
        mpType = pType;
        mMethod = method;
      };

      // override operator "()"
      virtual bool operator()(const VType & value)
      {return (*mpType.*mMethod)(value);};              // execute member function
    };

class CRenameHandler;

/** @dia:pos 40.5964,2.55372 */
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
      ValueString = 0x400
    };

  private:
    std::string mObjectName;

    std::string mObjectType;

    // std::string mUniqueName;

    /** @dia:route 8,0; h,23.7081,53.1343,15.3196,2.55372,40.5964 */
    CCopasiContainer * mpObjectParent;

    unsigned C_INT32 mObjectFlag;

    UpdateMethod * mpUpdateMethod;

  private:
    static const C_FLOAT64 DummyValue;

    static UpdateMethod mDefaultUpdateMethod;

    static const CRenameHandler * smpRenameHandler;

    //Operations
  protected:
    CCopasiObject();

    CCopasiObject(const std::string & name,
                  const CCopasiContainer * pParent = NULL,
                  const std::string & type = "CN",
                  const unsigned C_INT32 & flag = 0);

    virtual const std::string getObjectUniqueNameEx(const bool & isParent = true) const;

  public:
    CCopasiObject(const CCopasiObject & src,
                  const CCopasiContainer * pParent = NULL);

    virtual ~CCopasiObject();

    //  pure virtual function,
    /**
     * This is the output method for any object. The default implementation
     * provided with CCopasiObject uses the ostream operator<< of the object
     * to print the object.
     * There exist two ways to modify the print behaviour of an object
     * 1) implement an ostream operator for the object
     * 2) reimplement the virtual print function.
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

    virtual const std::string getObjectUniqueName() const;

    virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;

    const std::string & getObjectType() const;

    virtual bool setObjectParent(const CCopasiContainer * pParent);

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

    bool isValueBool() const;
    bool isValueInt() const;
    bool isValueDbl() const;
    bool isNonUniqueName() const;
    bool isStaticString() const;
    bool isValueString() const;

    virtual void * getReference() const;

    friend std::ostream &operator<<(std::ostream &os, const CCopasiObject & o);

    virtual const std::string & getKey() const;

    bool setObjectValue(const C_FLOAT64 & value);
    bool setObjectValue(const C_INT32 & value);
    bool setObjectValue(const bool & value);

    template <class CType>
    bool setUpdateMethod(CType * pType,
                         bool (CType::*method)(const C_FLOAT64 &))
    {
      if (mpUpdateMethod != &mDefaultUpdateMethod)
        pdelete(mpUpdateMethod);

      mpUpdateMethod =
        new SpecificUpdateMethod< CType, C_FLOAT64 >(pType, method);

      return true;
    }

    template <class CType>
    bool setUpdateMethod(CType * pType,
                         bool (CType::*method)(const C_INT32 &))
    {
      if (mpUpdateMethod != &mDefaultUpdateMethod)
        pdelete(mpUpdateMethod);

      mpUpdateMethod =
        new SpecificUpdateMethod< CType, C_INT32 >(pType, method);

      return true;
    }

    template <class CType>
    bool setUpdateMethod(CType * pType,
                         bool (CType::*method)(const bool &))
    {
      if (mpUpdateMethod != &mDefaultUpdateMethod)
        pdelete(mpUpdateMethod);

      mpUpdateMethod =
        new SpecificUpdateMethod< CType, bool >(pType, method);

      return true;
    }

    UpdateMethod * getUpdateMethod() const;

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

#endif // COPASI_CCopasiObject
