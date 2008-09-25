// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CArrayElementReference.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/09/25 22:56:51 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CArrayElementReference
#define COPASI_CArrayElementReference

#include "CCopasiArray.h"
#include "CCopasiObject.h"

#include "CCopasiObjectName.h"

/**
 * Class CArrayElementReference
 *
 * This class is used to make an element of an array accessible as
 * a CCopasiObject. Usually an object from this class will be a child
 * of a CArrayAnnotation and will reference a single element of the
 * array that the CArrayAnnotation points to.
 */
class CArrayElementReference: public CCopasiObject
  {

  private:
    CCopasiAbstractArray::data_type * mpReference;

    /**
     * this contains the index in string format, e.g. "[2][7]"
     */
    std::string mIndex;

  private:
    /**
     * make the default constructor unaccessible
     */
    CArrayElementReference();

    /**
     * make the copy constructor unaccessible
     */
    CArrayElementReference(const CArrayElementReference & src);

    void updateMethod(const CCopasiAbstractArray::data_type & value);

  public:
    /**
     * create an element reference with a given index. The index
     * is passed as a string, e.g. "[3][2]"
     * The object name will be the index string, the type is "ElementReference"
     * pParent may not be NULL.
     */
    CArrayElementReference(const std::string & index,
                           const CCopasiContainer * pParent);

    virtual ~CArrayElementReference() {}

    /**
     * returns a pointer to the numerical values of the array element
     * this will be a *C_FLOAT64 for this class.
     */
    virtual void * getValuePointer() const;

    virtual const CCopasiObject * getValueObject() const {return this;}

    /**
     *
     */
    virtual void print(std::ostream * ostream) const;

    /**
     *
     */
    virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;

    /**
     *
     */
    virtual CCopasiObjectName getCN() const;
  };

#endif
