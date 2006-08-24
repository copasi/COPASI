/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperimentObjectMap.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/24 14:16:37 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CExperimentObjectMap
#define COPASI_CExperimentObjectMap

#include "CExperiment.h"

#include "utilities/CCopasiParameterGroup.h"
#include "utilities/CVector.h"

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
         * Specific constructor used for reading copasi files
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
         * Assignement operator
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
         * Retreive the object CN of the object mapped to the column
         * @return std::string objctCN
         */
        std::string getObjectCN() const;

        /**
         * Set the weight for the column
         * @param const C_FLOAT64 & weight
         * @return bool success
         */
        bool setWeight(const C_FLOAT64 & weight);

        /**
         * Retreive the weight of the column
         * @return C_FLOAT64 weight
         */
        C_FLOAT64 getWeight() const;

      private:
        /**
         * Retreive the default weight of the column
         * @return C_FLOAT64 weight
         */
        C_FLOAT64 getDefaultWeight() const;

        // Attributes
      private:
        CExperiment::Type *mpRole;

        CCopasiObjectName *mpObjectCN;

        C_FLOAT64 *mpWeight;
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
     * @param const unsigned C_INT32 & numCols
     * @return bool success
     */
    bool setNumCols(const unsigned C_INT32 & numCols);

    /**
     * Retrieve the last non ignored column
     * @return unsigned C_INT32 lastNotIgnoredColumn
     */
    unsigned C_INT32 getLastNotIgnoredColumn() const;

    /**
     * Set the role of the indexed column
     * @param const unsigned C_INT32 & index
     * @param const CExperiment::Type & role
     * @return bool success
     */
    bool setRole(const unsigned C_INT32 & index,
                 const CExperiment::Type & role);

    /**
     * Retrieve the role of the indexed column
     * @param const unsigned C_INT32 & index
     * @return CExperiment::Type role
     */
    CExperiment::Type getRole(const unsigned C_INT32 & index) const;

    /**
     * Set the object CN of the object mapped to the indexed column
     * @param const unsigned C_INT32 & index
     * @param const std::string & objectCN
     * @return bool success
     */
    bool setObjectCN(const unsigned C_INT32 & index,
                     const std::string & objectCN);

    /**
     * Retreive the object CN of the object mapped to the indexed column
     * @param const unsigned C_INT32 & index
     * @return std::stringobjctCN
     */
    std::string getObjectCN(const unsigned C_INT32 & index) const;

    /**
     * Set the weight for the indexed column
     * @param const unsigned C_INT32 & index
     * @param const C_FLOAT64 & weight
     * @return bool success
     */
    bool setWeight(const unsigned C_INT32 & index,
                   const C_FLOAT64 & weight);

    /**
     * Retreive the weight of the indexed column
     * @param const unsigned C_INT32 & index
     * @return C_FLOAT64 weight
     */
    C_FLOAT64 getWeight(const unsigned C_INT32 & index) const;

    /**
     * Compile the map. This function must be called
     * before any operations can be performed.
     * @param const std::vector< CCopasiContainer * > listOfContainer
     * @return bool success
     */
    bool compile(const std::vector< CCopasiContainer * > listOfContainer =
                   CCopasiContainer::EmptyList);

    /**
     * Retrieve the vector of mapped objects
     * @return const CVector< CCopasiObject * > & mappedObjects
     */
    const CVector< CCopasiObject * > & getMappedObjects() const;

    /**
     * Retrieve the last mapped column number
     * @return const unsigned C_INT32 & lastColumn
     */
    const unsigned C_INT32 & getLastColumn() const;

  private:
    /**
     * A vector of pointer to the  objects corresponding
     * to the data column.
     */
    CVector<CCopasiObject *> mObjects;

    /**
     * The last mapped column
     */
    unsigned C_INT32 mLastColumn;
  };

#endif // COPASI_CExperimentObjectMap
