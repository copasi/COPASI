// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/*!
    \file CDataArray.h
    \brief Header file of class CArrayAnnotation
 */

#ifndef CANNOTATEDMATRIX_H
#define CANNOTATEDMATRIX_H

#include "copasi/core/CDataContainer.h"
#include "copasi/core/CRegisteredCommonName.h"

#include <string>

#include "copasi/copasi.h"

#include "copasi/core/CDataVector.h"
#include "CArray.h"

/**
 * This class contains the annotations to a n-dimensional array. Annotations can be provided
 * for the array as such, for each of the dimensions, and for each of the indices (rows,
 * columns, ...)
 */
class CDataArray: public CDataContainer
{
public:
  typedef C_FLOAT64 data_type;
  typedef CArray::index_type index_type;
  typedef std::vector< std::string > name_index_type;

  /**
   * The annotation to an array can work in different modes. The mode
   * for each dimension can be changed independently.
   *
   * OBJECTS: The CNs for the rows, cols, ... of the array are given explicitly
   *
   * VECTOR: A CDataVector is provided from which the CNs are generated at
   * the time the vector is set
   *
   * VectorOnTheFly: A CDataVector is provided, but the CNs are generated
   * every time the annotations are retrieved (so that they are always up to date).
   *
   * STRINGS: The annotations for the rows, cols, ... are given explicitly
   * as strings.
   *
   * NUMBERS: The rows, cols, ... of the array are only annotation with
   * running numbers (starting with 0)-
   */
  enum struct Mode
  {
    Objects,
    Vector,
    VectorOnTheFly,
    Strings,
    Numbers,
    __SIZE
  };

private:
  CDataArray();
  CDataArray(const CDataArray &);
  CDataArray & operator=(const CDataArray &);

public:
  CDataArray(const std::string & name,
             const CDataContainer * pParent,
             CArrayInterface * array,
             const bool & adopt);

  virtual ~CDataArray();

  /**
   *  let the ArrayAnnotation point to a different array.
   *  If you use this method without updating the annotations afterwards
   *  it is your responsibility to make sure the new array fits the
   *  existing annotation (in dimensionality and, if not in VectorOnTheFly mode,
   *  in size).
   */
  void setArray(CArrayInterface * a);

  CArrayInterface * array()
  {return mpArray;}

  const CArrayInterface * array() const
  {return mpArray;}

  /**
   * set the mode for the dimension d
   */
  void setMode(size_t d, Mode m);

  /**
   * set the mode for all dimensions, this also sets the
   * default mode that is used when resizing the ArrayAnnotion
   * to a larger dimensionality
   */
  void setMode(Mode m);

  Mode getMode(size_t d) const
  {return mModes[d];};

  Mode getDefaultMode() const
  {return mDefaultMode;};

  size_t dimensionality() const;

  CArrayInterface::index_type size() const
  {return mpArray->size();}

  /**
   * Associates a dimension d of the array with a CDataVector of
   * CDataObjects. If the mode of the dimension d is VECTOR than
   * the CNs of the objects in the vector are generated and stored immediately.
   * If the mode is VectorOnTheFly the CNs are generated when getAnnotationsCN()
   * or getAnnotationsString() is called.
   */
  template < class CType > void setCopasiVector(size_t d, const CDataVector< CType > & v)
  {
    assert(d < dimensionality());
    assert((mModes[d] == Mode::Vector) || (mModes[d] == Mode::VectorOnTheFly));

    size_t i;

    for (i = 0; i < mAnnotationsCN[d].size() && i < v.size(); ++i)
      {
        mAnnotationsCN[d][i] = v[i].getCN();

        // The annotation string is always updated when retrieved since objects may be renamed
        // Thus we do not update them here
      }

    return;
  }

  void setAnnotation(size_t d, size_t i, const CDataObject * pObject);
  void setAnnotationString(size_t d, size_t i, const std::string s);

  /**
   * returns the vector of CNs that correspond to the rows, columns, ... of the array.
   * This method must not be called if the mode for the dimension d is STRINGS or NUMBERS
   */
  const std::vector<CRegisteredCommonName> & getAnnotationsCN(size_t d) const;

  /**
   * This returns strings that annotate the rows, columns, ... of the array.
   * If the mode is OBJECTS, VECTOR, or VectorOnTheFly the display argument determines
   * if the object name or the object display name is used.
   * Note that this method returns a reference. The content that the reference points to
   * may be changes by later calls to the getAnnotationsCN() method with the same value for d.
   * Specifically if you use this method to obtain a reference to the list of display names
   * and then call the method again to get the plain object names, the first reference will
   * after that also point to the plain object names.
   */
  const std::vector<std::string> & getAnnotationsString(size_t d, bool display = true) const;

  const std::string & getDimensionDescription(size_t d) const;
  void setDimensionDescription(size_t d, const std::string & s);

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
  const CDataObject * addElementReference(const index_type & index) const;
  const CDataObject * addElementReference(const name_index_type & nameIndex) const;

  /**
   * a convenience function for 2-dimensional arrays.
   */
  const CDataObject * addElementReference(C_INT32 u, C_INT32 v) const;

  /**
   * a convenience function for 1-dimensional arrays.
   */
  const CDataObject * addElementReference(C_INT32 u) const;

  /**
   * Resolve a cn. Since this is an array, the CN can start with an index like "[2][3]".
   * Since this is also a container, this is not necessarily the case.
   */
  virtual const CObjectInterface * getObject(const CCommonName & cn) const;

  /**
   * Check whether the size of array is greater than 0 for each dimension.
   * Return true, if so. Otherwise, false.
   */
  bool isEmpty();

//private:
  /**
   *  resize the internal vectors according to the dimensionality of the array
   */
  void reDimensionalize(size_t d);

  void resizeOneDimension(size_t d);

  //void printDebugLoop(std::ostream & out, CCopasiAbstractArray::index_type & index, size_t level) const;

  //void printDebug(std::ostream & out) const;

  void printRecursively(std::ostream & ostream, size_t level,
                        CArrayInterface::index_type & index,
                        const std::vector<std::vector<std::string> > & display) const;

  /**
   * generate a display name for the array annotation.
   */
  virtual std::string getObjectDisplayName() const;

  virtual void print(std::ostream * ostream) const;

  friend std::ostream &operator<<(std::ostream &os, const CDataArray & o);

  data_type & operator[](const name_index_type & nameIndex);
  const data_type & operator[](const name_index_type & nameIndex) const;

  CArrayInterface * getArray() const;

  name_index_type displayNamesToCN(const std::vector< std::string > & DisplayNames) const;
  index_type cnToIndex(const name_index_type & cnIndex) const;
private:
  std::string createDisplayName(const std::string & cn) const;
  void updateDisplayNames() const;

  CArrayInterface * mpArray;
  bool mDestructArray;

  std::vector< std::vector< CRegisteredCommonName > > mAnnotationsCN;
  mutable std::vector< std::vector< std::string > > mAnnotationsString;

  std::vector< std::string > mDimensionDescriptions;

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
};

#endif
