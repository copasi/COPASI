/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiObjectReference.h,v $
   $Revision: 1.33 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2006/04/11 22:06:54 $
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
#include "CCopasiObjectName.h"

template <class CType> class CCopasiObjectReference: public CCopasiObject
  {
    typedef CType referenceType;

    //Attributes
  private:
    CType * mpReference;

    //Operations
  private:
    CCopasiObjectReference() {};

    void updateMethod(const CType & value)
    {*mpReference = value;}

  public:
    CCopasiObjectReference(const std::string & name,
                           const CCopasiContainer * pParent,
                           referenceType & reference,
                           const unsigned C_INT32 & flag = 0):
        CCopasiObject(name, pParent, "Reference",
                      CCopasiObject::Reference |
                      CCopasiObject::NonUniqueName |
                      flag),
        mpReference(&reference)
    {assert(pParent != NULL);}

    CCopasiObjectReference(const CCopasiObjectReference< referenceType > & src):
        CCopasiObject(src),
        mpReference(src.mpReference)
    {}

    virtual ~CCopasiObjectReference() {}

    virtual void * getValuePointer() const {return mpReference;}

    virtual void setReference(referenceType & reference)
    {mpReference = &reference;}

    virtual void print(std::ostream * ostream) const
      {(*ostream) << *mpReference;};

    virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const
      {
        //supress "Value"
        if (getObjectParent() && getObjectName() == "Value")
          return getObjectParent()->getObjectDisplayName(regular, richtext);

        //special treatment of metab children
        if (getObjectParent()->getObjectType() == "Metabolite")
          {
            if (getObjectName() == "Concentration")
              {
                if (richtext)
                  {
                    return "<font color=\"#2222cc\">[</font>"
                    + getObjectParent()->getObjectDisplayName(regular, richtext)
                    + "<font color=\"#2222cc\">]</font>";
                  }
                else
                {return "[" + getObjectParent()->getObjectDisplayName(regular, richtext) + "]";}
              }

            if (getObjectName() == "InitialConcentration")
              {
                if (richtext)
                  {
                    return "<font color=\"#2222cc\">[</font>"
                    + getObjectParent()->getObjectDisplayName(regular, richtext)
                    + "<font color=\"#2222cc\">]<sub>0</sub></font>";
                  }
                else
                {return "[" + getObjectParent()->getObjectDisplayName(regular, richtext) + "]_0";}
              }
          }

        return CCopasiObject::getObjectDisplayName(regular, richtext);
      }
  };

template<> inline
CCopasiObjectReference<C_FLOAT64>::CCopasiObjectReference(const std::string & name,
    const CCopasiContainer * pParent,
    referenceType & reference,
    const unsigned C_INT32 & flag):
    CCopasiObject(name, pParent, "Reference",
                  CCopasiObject::Reference |
                  CCopasiObject::NonUniqueName |
                  flag),
    mpReference(&reference)
{
  assert(pParent != NULL);
  setUpdateMethod(this, &CCopasiObjectReference<C_FLOAT64>::updateMethod);
}

template<> inline
CCopasiObjectReference<C_INT32>::CCopasiObjectReference(const std::string & name,
    const CCopasiContainer * pParent,
    referenceType & reference,
    const unsigned C_INT32 & flag):
    CCopasiObject(name, pParent, "Reference",
                  CCopasiObject::Reference |
                  CCopasiObject::NonUniqueName |
                  flag),
    mpReference(&reference)
{
  assert(pParent != NULL);
  setUpdateMethod(this, &CCopasiObjectReference<C_INT32>::updateMethod);
}

template<> inline
CCopasiObjectReference<bool>::CCopasiObjectReference(const std::string & name,
    const CCopasiContainer * pParent,
    referenceType & reference,
    const unsigned C_INT32 & flag):
    CCopasiObject(name, pParent, "Reference",
                  CCopasiObject::Reference |
                  CCopasiObject::NonUniqueName |
                  flag),
    mpReference(&reference)
{
  assert(pParent != NULL);
  setUpdateMethod(this, &CCopasiObjectReference<bool>::updateMethod);
}

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
                      CCopasiObject::Reference |
                      CCopasiObject::NonUniqueName |
                      flag),
        mReference(reference)
    {assert(pParent != NULL);}

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

    virtual void * getValuePointer() const {return &mReference;}

    /**
     * This is the output method for any object. The default implementation
     * provided with CCopasiObject uses the ostream operator<< of the object
     * to print the object.To overide this default behaviour one needs to
     * reimplement the virtual print function.
     * @param std::ostream * ostream
     */
    virtual void print(std::ostream * ostream) const
      {*ostream << mReference;}
  };

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
                      CCopasiObject::Reference |
                      CCopasiObject::NonUniqueName |
                      flag),
        mReference(reference)
    {assert(pParent != NULL);}

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

    virtual void * getValuePointer() const {return &mReference;}
  };
#endif // COPASI_CCopasiObjectReference
