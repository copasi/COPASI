/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperiment.h,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/02 18:02:52 $
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
      time
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
     * @param const std::string & name (default: Experiment)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CExperiment(const std::string & name = "Experiment",
                const CCopasiContainer * pParent = NULL);

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
     * Assignement operator
     * @param const CExperiment & rhs
     * @return CExperiment & lhs
     */
    CExperiment & operator = (const CExperiment & rhs);

    /**
     * This methods must be called to elevate subgroups to
     * derived objects. The default implementation does nothing.
     * @return bool success
     */
    virtual bool elevateChildren();

    C_FLOAT64 sumOfSquares(const unsigned C_INT32 & index);

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
     * Update the model with the independent data of the experiment
     * @param const unsigned C_INT32 & index
     * @return bool success
     */
    bool updateModelWithIndependentData(const unsigned C_INT32 & index);

    /**
     * set the experiment type
     * @param const CCopasiTask::Type & experimentType
     * @return bool success
     */
    bool setExperimentType(const CCopasiTask::Type & type);

    /**
     * Retrieve the experiment type
     * @return const CCopasiTask::Type & experimentType
     */
    const CCopasiTask::Type & getExperimentType() const;

    /**
     * Retrieve the time data of the experiment.
     * @return const CVector< C_FLOAT64 > & timeData
     */
    const CVector< C_FLOAT64 > & getTimeData() const;

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
     * @param const Type & type
     * @return bool success
     */
    bool addColumnType(const unsigned C_INT32 & index, const Type & type);

    /**
     * Retrieve the type fo the indexed column.
     * @param const unsigned C_INT32 & index,
     * @return bool success
     */
    bool removeColumnType(const unsigned C_INT32 & index);

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
     * Retrieve the first row
     * @return const unsigned C_INT32 & firstRow
     */
    const unsigned C_INT32 & getFirstRow() const;

    /**
     * Set the first row containing data
     * @param const unsigned C_INT32 & firstRow
     * @return bool success
     */
    bool setFirstRow(const unsigned C_INT32 & firstRow);

    /**
     * Retrieve the last row
     * @return const unsigned C_INT32 & lastRow
     */
    const unsigned C_INT32 & getLastRow() const;

    /**
     * Set the last row containing data
     * @param const unsigned C_INT32 & lastRow
     * @return bool success
     */
    bool setLastRow(const unsigned C_INT32 & lastRow);

    /**
     * Retrieve the header row
     * @return const unsigned C_INT32 & headerRow
     */
    const unsigned C_INT32 & getHeaderRow() const;

    /**
     * Set the header row containing data
     * @param const unsigned C_INT32 & headerRow
     * @return bool success
     */
    bool setHeaderRow(const unsigned C_INT32 & headerRow);

    /**
     * Retrieve the number of rows
     * @return const unsigned C_INT32 numRows
     */
    const unsigned C_INT32 getNumRows() const;

    /**
     * Retrieve the seperator
     * @return const std::string & separator
     */
    const std::string & getSeparator() const;

    /**
     * Set the seperator used when reading a stream
     * @param const std::string & separator
     * @return bool success
     */
    bool setSeparator(const std::string & seperator);

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

    /**
     * Comparison operator
     * @param const CExperiment & lhs
     * @param const CExperiment & rhs
     * @return bool equal
     */
    friend bool operator == (const CExperiment & lhs,
                             const CExperiment & rhs);

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
    unsigned C_INT32 * mpLastRow;

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
    unsigned C_INT32 *mpHeaderRow;

    /**
     * This is realized as a CCopasiParameter type UINT
     */
    unsigned C_INT32 * mpNumColumns;

    /**
     * This is realized as a CCopasiParameter type GROUP
     */
    CCopasiParameterGroup * mpColumnType;

    /**
     * The column names if available after reading a file
     */
    std::vector< std::string > mColumnName;

    /**
     * This is realized as a CCopasiParameter type GROUP
     */
    CExperimentObjectMap * mpObjectMap;

    /**
     * The vector of time points
     */
    CVector< C_FLOAT64 > mDataTime;

    /**
     * The relevant independent experimental data after reading a file
     */
    CMatrix< C_FLOAT64 > mDataIndependent;

    /**
     * The relevant dependent experimental data after reading a file
     */
    CMatrix< C_FLOAT64 > mDataDependent;

    CVector< C_FLOAT64 > mMeans;

    CVector< C_FLOAT64 > mWeight;

    CVector< C_FLOAT64 * > mDependentValues;

    CVector< UpdateMethod * > mIndependentUpdateMethods;
  };

#endif // COPASI_CExperiment
