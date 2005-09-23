/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperiment.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/09/23 19:17:28 $
   End CVS Header */

#ifndef COPASI_CExperiment
#define COPASI_CExperiment

#include <string>

#include "utilities/CCopasiParameterGroup.h"
#include "utilities/CCopasiTask.h"
#include "utilities/CMatrix.h"
#include "utilities/CVector.h"

class CExperimentObjectMap;

class CExperiment: public CCopasiParameterGroup
  {
  public:
    /**
     * Enumeration of the types of columns known to COPASI.
     */
    enum Type
    {
      ignore = 0,
      independent,
      dependent,
    };

    /**
     * String literals for the GUI to display type names of columns known
     * to COPASI.
     */
    static const std::string TypeName[];

    /**
     * XML type names of tasks known to COPASI.
     */
    static const char* XMLType[];

    /**
     * Default constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CExperiment(const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CExperiment & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CExperiment(const CExperiment & src,
                const CCopasiContainer * pParent = NULL);

    /**
     * Specific constructor used for reading copasi files
     * @param const CCopasiParameterGroup & group
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CExperiment(const CCopasiParameterGroup & group,
                const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CExperiment();

    /**
     * Compile the experiment. This function must be called 
     * before any evaluations can be performed.
     * @param const std::vector< CCopasiContainer * > listOfContainer
     * @return bool success
     */
    bool compile(const std::vector< CCopasiContainer * > listOfContainer =
                   CCopasiContainer::EmptyList);

    /**
     * Reads the experiment data form a the given stream
     * @param std::istream & in
     * @param unsigned C_INT32 & currentLine
     * @return bool success
     */
    bool read(std::istream & in, unsigned C_INT32 & currentLine);

    /**
     * Retrieve the experiment type
     * @return const CCopasiTask::Type & experimentType
     */
    const CCopasiTask::Type & getExperimentType() const;

    /**
     * Retrieve the independent data of the experiment.
     * @return const CMatrix< C_FLOAT64 > & independentData
     */
    const CMatrix< C_FLOAT64 > & getIndependentData() const;

    /**
     * Retrieve the dependent data of the experiment.
     * @return const CMatrix< C_FLOAT64 > & dependentData
     */
    const CMatrix< C_FLOAT64 > & getDependentData() const;

    /**
     * Retrieve the file name
     * @return const std::string & fileName
     */
    const std::string & getFileName() const;

    /**
     * Set the file name
     * @param const std::string & fileName
     * @return bool success
     */
    bool setFileName(const std::string & fileName);

    /**
     * Retrieve the type fo the indexed column.
     * @param const unsigned C_INT32 & index,
     * @return const Type & columnType
     */
    const Type & getColumnType(const unsigned C_INT32 & index) const;

    /**
     * Set the type of the indexed column.
     * @param const unsigned C_INT32 & index,
     * @param const Type & type
     * @return bool success
     */
    bool setColumnType(const unsigned C_INT32 & index, const Type & type);

    /**
     * Retrieve the number of columns
     * @return const unsigned C_INT32 & numColumns
     */
    const unsigned C_INT32 & getNumColumns() const;

    /**
     * Set the number of columns in a stream
     * @param const unsigned C_INT32 & cols
     * @return bool success
     */
    bool setNumColumns(const unsigned C_INT32 & cols);

    /**
     * Retrieve the number of rows
     * @return const unsigned C_INT32 & numRows
     */
    const unsigned C_INT32 & getNumRows() const;

    /**
     * Set the number of data rows in a stream
     * @param const unsigned C_INT32 & rows
     * @return bool success
     */
    bool setNumRows(const unsigned C_INT32 & rows);

    /**
     * Retrieve the seperator
     * @return const std::string & seperator
     */
    const std::string & getSeperator() const;

    /**
     * Set the seperator used when reading a stream
     * @param const std::string & seperator
     * @return bool success
     */
    bool setSeperator(const std::string & seperator);

    /**
     * Check whter the data is row oriented.
     * @return const bool & isRowOriented
     */
    const bool & isRowOriented() const;

    /**
     * Set whether the data is row oriented. This only
     * impacts reading the data from a stream
     * @param const bool & isRowOriented
     * @return bool success
     */
    bool setIsRowOriented(const bool & isRowOriented);

    /**
     * Comparison used to evaluate the order of the experiment
     * based on the filename and starting line number.
     * @param const CExperiment * lhs;
     * @param const CExperiment * rhs;
     * @return bool isLess
     */
    static bool compare(const CExperiment * lhs,
                        const CExperiment * rhs);

  private:
    /**
     * Allocates all group parameters and assures that they are 
     * properly initialized.
     */
    void initializeParameter();

  private:
    // Attributes

    /**
     * The key of the experiment
     */ 
    //    const std::string mKey;

    /**
     * This is realized as a CCopasiParameter type STRING
     */
    std::string * mpFileName;

    /**
     * This is realized as a CCopasiParameter type UINT
     */
    unsigned C_INT32 * mpFirstRow;

    /**
     * This is realized as a CCopasiParameter type UINT
     */
    CCopasiTask::Type * mpTaskType;

    /**
     * This is realized as a CCopasiParameter type STRING
     */
    std::string * mpSeparator;

    /**
     * This is realized as a CCopasiParameter type BOOL
     */
    bool * mpRowOriented;

    /**
     * This is realized as a CCopasiParameter type UINT
     */
    unsigned C_INT32 *mpNameRow;

    /**
     * This is realized as a CCopasiParameter type UINT
     */
    unsigned C_INT32 * mpNumRows;

    /**
     * This is realized as a CCopasiParameter type UINT
     */
    unsigned C_INT32 * mpNumColumns;

    /**
     * This is realized as a CCopasiParameter type GROUP
     */
    std::vector< CCopasiParameter * > * mpColumnType;

    /**
     * The column names if available after reading a file
     */
    std::vector< std::string > mRowName;

    /**
     * This is realized as a CCopasiParameter type GROUP
     */
    CExperimentObjectMap * mpObjectMap;

    /**
     * The relevant independent experimental data after reading a file
     */
    CMatrix< C_FLOAT64 > mDataIndependent;

    /**
     * The relevant dependent experimental data after reading a file
     */
    CMatrix< C_FLOAT64 > mDataDependent;

    CVector< C_FLOAT64 > mMeans;

    CVector< C_FLOAT64 > mVariances;

    CVector< C_FLOAT64 * > mDependentValues;

    CVector< UpdateMethod * > mIndependentUpdateMethods;
  };

#endif // COPASI_CExperiment
