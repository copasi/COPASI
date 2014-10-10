// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CExperimentObjectMap
#define COPASI_CExperimentObjectMap

#include "parameterFitting/CExperiment.h"

#include "utilities/CCopasiParameterGroup.h"
#include "utilities/CVector.h"

class CMathContainer;

class CExperimentObjectMap: public CCopasiParameterGroup
{
public:

  class CDataColumn: public CCopasiParameterGroup
  {
  public:
    /**
     * Default constructor
     * @param const std::string & name (default: Object Map)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CDataColumn(const std::string & name = "Object Map",
                const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CDataColumn & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CDataColumn(const CDataColumn & src,
                const CCopasiContainer * pParent = NULL);

    /**
     * Specific constructor used for reading COPASI files
     * @param const CCopasiParameterGroup & group
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CDataColumn(const CCopasiParameterGroup & group,
                const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CDataColumn();

  private:
    /**
     * Allocates all group parameters and assures that they are
     * properly initialized.
     */
    void initializeParameter();

  public:
    /**
     * Assignment operator
     * @param const CDataColumn & rhs
     * @return CDataColumn & lhs
     */
    CDataColumn & operator = (const CDataColumn & rhs);

    /**
     * This methods must be called to elevate subgroups to
     * derived objects. The default implementation does nothing.
     * @return bool success
     */
    virtual bool elevateChildren();

    /**
     * Set the role of the column
     * @param const CExperiment::Type & role
     * @return bool success
     */
    bool setRole(const CExperiment::Type & role);

    /**
     * Retrieve the role of the column
     * @return const CExperiment::Type & role
     */
    const CExperiment::Type & getRole() const;

    /**
     * Set the object CN of the object mapped to the column
     * @param const std::string & objectCN
     * @return bool success
     */
    bool setObjectCN(const std::string & objectCN);

    /**
     * Retrieve the object CN of the object mapped to the column
     * @return std::string objctCN
     */
    std::string getObjectCN() const;

    /**
     * Set the scaling factor for the column
     * @param const C_FLOAT64 & scale
     * @return bool success
     */
    bool setScale(const C_FLOAT64 & scale);

    /**
     * Retrieve the scaling factor of the column
     * @return C_FLOAT64 scale
     */
    C_FLOAT64 getScale() const;

    /**
     * Retrieve the default weight of the column
     * @return C_FLOAT64 defaultScale
     */
    C_FLOAT64 getDefaultScale() const;

    /**
     * Fix files written with Version 4.10.55, which wrote the square root of user defined weights for the
     * parameter fitting task
     */
    void fixBuild55();

    // Attributes
  private:
    CExperiment::Type *mpRole;

    CCopasiObjectName *mpObjectCN;

    C_FLOAT64 *mpScale;
  };

public:
  /**
   * Default constructor
   * @param const std::string & name (default: Object Map)
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CExperimentObjectMap(const std::string & name = "Object Map",
                       const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor
   * @param const CExperimentObjectMap & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CExperimentObjectMap(const CExperimentObjectMap & src,
                       const CCopasiContainer * pParent = NULL);

  /**
   * Specific constructor used for reading copasi files
   * @param const CCopasiParameterGroup & group
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CExperimentObjectMap(const CCopasiParameterGroup & group,
                       const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  virtual ~CExperimentObjectMap();

private:
  /**
   * Allocates all group parameters and assures that they are
   * properly initialized.
   */
  void initializeParameter();

public:
  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

  /**
   * Set the number of data columns
   * @param const size_t & numCols
   * @return bool success
   */
  bool setNumCols(const size_t & numCols);

  /**
   * Retrieve the last non ignored column
   * @return size_t lastNotIgnoredColumn
   */
  size_t getLastNotIgnoredColumn() const;

  /**
   * Retrieve the name of a parameter or subgroup
   * @param const size_t & index
   * @return std::string name
   */
  virtual const std::string & getName(const size_t & index) const;

  /**
   * Set the role of the indexed column
   * @param const size_t & index
   * @param const CExperiment::Type & role
   * @return bool success
   */
  bool setRole(const size_t & index,
               const CExperiment::Type & role);

  /**
   * Retrieve the role of the indexed column
   * @param const size_t & index
   * @return CExperiment::Type role
   */
  CExperiment::Type getRole(const size_t & index) const;

  /**
   * Set the object CN of the object mapped to the indexed column
   * @param const size_t & index
   * @param const std::string & objectCN
   * @return bool success
   */
  bool setObjectCN(const size_t & index,
                   const std::string & objectCN);

  /**
   * Retrieve the object CN of the object mapped to the indexed column
   * @param const size_t & index
   * @return std::stringobjctCN
   */
  std::string getObjectCN(const size_t & index) const;

  /**
   * Set the scaling factor for the indexed column
   * @param const size_t & index
   * @param const C_FLOAT64 & scale
   * @return bool success
   */
  bool setScale(const size_t & index,
                const C_FLOAT64 & scale);

  /**
   * Retrieve the scaling factor of the indexed column
   * @param const size_t & index
   * @return C_FLOAT64 scale
   */
  C_FLOAT64 getScale(const size_t & index) const;

  /**
   * Retrieve the default scaling factor according to the selected weight method
   * of the indexed column
   * @param const size_t & index
   * @return C_FLOAT64 defaultScale
   */
  C_FLOAT64 getDefaultScale(const size_t & index) const;

  /**
   * Compile the map. This function must be called
   * before any operations can be performed.
   * @param const CMathContainer * pMathContainer
   * @return bool success
   */
  bool compile(const CMathContainer * pMathContainer);

  /**
   * Retrieve the vector of mapped objects
   * @return const CVector< const CCopasiObject * > & mappedObjects
   */
  const CVector< const CCopasiObject * > & getDataObjects() const;

  /**
   * Retrieve the last mapped column number
   * @return const size_t & lastColumn
   */
  const size_t & getLastColumn() const;

  /**
   * Fix files written with Version 4.10.55, which wrote the square root of user defined weights for the
   * parameter fitting task
   */
  void fixBuild55();

private:
  /**
   * A vector of pointer to the  objects corresponding
   * to the data column.
   */
  CVector< const CCopasiObject * > mObjects;

  /**
   * The last mapped column
   */
  size_t mLastColumn;
};

#endif // COPASI_CExperimentObjectMap
