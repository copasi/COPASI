// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CAnnotatedMatrix.h,v $
//   $Revision: 1.22.2.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/10/15 20:12:47 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*!
    \file CAnnotatedMatrix.h
    \brief Header file of class CArrayAnnotation
 */

#ifndef CANNOTATEDMATRIX_H
#define CANNOTATEDMATRIX_H

#include "report/CCopasiContainer.h"
#include "report/CCopasiObjectName.h"

#include "report/CCopasiArray.h"
#include <string>

#include "copasi.h"

/**
 * This class contains the annotations to a n-dimensional array. Annotations can be provided
 * for the array as such, for each of the dimensions, and for each of the indices (rows,
 * columns, ...)
 */
class CArrayAnnotation: public CCopasiContainer
  {
  public:

    /**
     * The annotation to an array can work in different modes. The mode
     * for each dimension can be changed independently.
     *
     * OBJECTS: The CNs for the rows, cols, ... of the array are given explicitly
     *
     * VECTOR: A CCopasiVector is provided from which the CNs are generated at
     * the time the vector is set
     *
     * VECTOR_ON_THE_FLY: A CCopasiVector is provided, but the CNs are generated
     * every time the annotations are retrieved (so that they are alway up to date).
     *
     * STRINGS: The annotations for the rows, cols, ... are given explicitly
     * as strings.
     *
     * NUMBERS: The rows, cols, ... of the array are only annotation with
     * running numbers (starting with 0)-
     */
    enum Mode
    {
      OBJECTS,
      VECTOR,
      VECTOR_ON_THE_FLY,
      STRINGS,
      NUMBERS
    };

  private:
    CCopasiAbstractArray * mpArray;
    bool mDestructArray;

    mutable std::vector< std::vector<CRegisteredObjectName> > mAnnotationsCN;
    mutable std::vector< std::vector<std::string> > mAnnotationsString;

    std::vector< std::string > mDimensionDescriptions;
    std::vector< const CCopasiContainer * > mCopasiVectors;

    /**
     * This contains the mode for the different dimensions
     */
    std::vector<Mode> mModes;

    /**
     * This contains the default mode that is used if during a resize()
     * the dimensionality is increased.
     */
    Mode mDefaultMode;

    std::string mDescription;

  public:
    CArrayAnnotation(const std::string & name,
                     const CCopasiContainer * pParent,
                     CCopasiAbstractArray * array,
                     const bool & adopt);

    ~CArrayAnnotation();

  private:
    CArrayAnnotation();
    CArrayAnnotation(const CArrayAnnotation &);
    CArrayAnnotation & operator=(const CArrayAnnotation &);

  public:

    /**
     *  let the ArrayAnnotation point to a different array.
     *  If you use this method without updating the annotations afterwards
     *  it is your responsibility to make sure the new array fits the
     *  existing annotation (in dimensionality and, if not in VECTOR_ON_THE_FLY mode,
     *  in size).
     */
    void setArray(CCopasiAbstractArray * a);

    CCopasiAbstractArray * array()
    {return mpArray;}

    const CCopasiAbstractArray * array() const
      {return mpArray;}

    /**
     * set the mode for the dimension d
     */
    void setMode(unsigned int d, Mode m);

    /**
     * set the mode for all dimensions, this also sets the
     * default mode that is used when resizing the ArrayAnnotion
     * to a larger dimensionality
     */
    void setMode(Mode m);

    Mode getMode(unsigned int d) const
      {return mModes[d];};

    Mode getDefaultMode() const
      {return mDefaultMode;};

    unsigned int dimensionality() const;

    CCopasiAbstractArray::index_type size() const
      {return mpArray->size();}

    /**
     * Associates a dimension d of the array with a CCopasiVector of
     * CCopasiObjects. If the mode of the dimension d is VECTOR than
     * the CNs of the objects in the vector are generated and stored immediately.
     * If the mode is VECTOR_ON_THE_FLY the CNs are generated when getAnnotationsCN()
     * or getAnnotationsString() is called.
     */
    void setCopasiVector(unsigned int d, const CCopasiContainer* v);

    void setAnnotationCN(unsigned int d, unsigned int i, const std::string cn);
    void setAnnotationString(unsigned int d, unsigned int i, const std::string s);

    /**
     * returns the vector of CNs that correspond to the rows, columns, ... of the array.
     * This method must not be called if the mode for the dimension d is STRINGS or NUMBERS
     */
    const std::vector<CRegisteredObjectName> & getAnnotationsCN(unsigned int d) const;

    /**
     * This returns strings that annotate the rows, columns, ... of the array.
     * If the mode is OBJECTS, VECTOR, or VECTOR_ON_THE_FLY the display argument determines
     * if the object name or the object display name is used.
     * Note that this method returns a reference. The content that the reference points to
     * may be changes by later calls to the getAnnotationsCN() method with the same value for d.
     * Specifically if you use this method to obtain a reference to the list of display names
     * and then call the method again to get the plain object names, the first reference will
     * after that also point to the plain object names.
     */
    const std::vector<std::string> & getAnnotationsString(unsigned int d, bool display = true) const;

    const std::string & getDimensionDescription(unsigned int d) const;
    void setDimensionDescription(unsigned int d, const std::string & s);

    const std::string & getDescription() const;
    void setDescription(const std::string & s);

    /**
     * adjust the dimensionality and size to that of the array
     */
    void resize();

    /**
     * an object that will act as a reference to one element of an array
     * will be created and inserted as a child of the array annotation. Basically
     * most of the work will be done by getObject(). If the element already
     * exists, the existing element will be returned.
     */
    const CCopasiObject* addElementReference(CCopasiAbstractArray::index_type index) const;

    /**
     * a convenience function for 2-dimensional arrays.
     */
    const CCopasiObject* addElementReference(C_INT32 u, C_INT32 v) const;

    /**
     * Resolve a cn. Since this is an array, the CN can start with an index like "[2][3]".
     * Since this is also a container, this is not necessarily the case.
     */
    virtual const CCopasiObject * getObject(const CCopasiObjectName & cn) const;

    /**
     * Check whether the size of array is greater than 0 for each dimension.
     * Return true, if so. Otherwise, false.
     */
    bool isEmpty();

  private:
    /**
     *  resize the internal vectors according to the dimensionality of the array
     */
    void reDimensionalize(unsigned int d);

    void resizeOneDimension(unsigned int d);

    //void printDebugLoop(std::ostream & out, CCopasiAbstractArray::index_type & index, unsigned int level) const;

    /**
     *  generate the list of CNs from the copasi vector v.
     *  v needs to be a CCopasiVector (or derived from it)!
     */
    bool createAnnotationsCNFromCopasiVector(unsigned int d, const CCopasiContainer* v) const;

    void createNumbers(unsigned int d) const;

    //void printDebug(std::ostream & out) const;

    void printRecursively(std::ostream & ostream, C_INT32 level,
                          CCopasiAbstractArray::index_type & index,
                          const std::vector<std::vector<std::string> > & display) const;

  public:
    virtual void print(std::ostream * ostream) const;

    friend std::ostream &operator<<(std::ostream &os, const CArrayAnnotation & o);
  };

#endif
