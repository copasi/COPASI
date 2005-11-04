/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperimentObjectMap.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/04 12:48:18 $
   End CVS Header */

#ifndef COPASI_CExperimentObjectMap
 #define COPASI_CExperimentObjectMap

#include "utilities/CCopasiParameterGroup.h"
 #include "utilities/CVector.h"

class CExperimentObjectMap: public CCopasiParameterGroup
  {
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

    /**
     * Add an object to the map.
     * @param const unsigned C_INT32 & index
     * @param const std::string & CN
     * @return bool success
     */
    bool addObjectCN(const unsigned C_INT32 & index,
                     const std::string & CN);

    /**
     * Remove an object from the map.
     * @param const unsigned C_INT32 & index
     * @return bool success
     */
    bool removeObjectCN(const unsigned C_INT32 & index);

    /**
     * Set the indexed object CN
     * @param const unsigned C_INT32 & index
     * @param const std::string & CN
     * @return bool success
     */
    bool setObjectCN(const unsigned C_INT32 & index,
                     const std::string & CN);

    /**
     * Retrieve the CN of the indexed object
     * @return const std::string & objectCN
     */
    std::string getObjectCN(const unsigned C_INT32 & index) const;

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
    // Attributes:
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
