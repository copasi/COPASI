/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperiment.h,v $
   $Revision: 1.22 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/22 18:26:59 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CExperiment
#define COPASI_CExperiment

#include <string>

#include "utilities/CCopasiVector.h"
#include "utilities/CCopasiParameterGroup.h"
#include "utilities/CCopasiTask.h"
#include "utilities/CMatrix.h"
#include "utilities/CVector.h"

class CExperimentObjectMap;

class CFittingPoint: public CCopasiContainer
  {
    // Operations
  public:
    CFittingPoint(const std::string & name = "unknown",
                  const CCopasiContainer * pParent = NULL);

    CFittingPoint(const CFittingPoint & src,
                  const CCopasiContainer * pParent = NULL);

    ~CFittingPoint();

    void setValues(const C_FLOAT64 & independent,
                   const C_FLOAT64 & measured,
                   const C_FLOAT64 & fitted,
                   const C_FLOAT64 & weightedError);

  private:
    void initObjects();

    // Attributes
  private:
    C_FLOAT64 mIndependentValue;
    C_FLOAT64 mMeasuredValue;
    C_FLOAT64 mFittedValue;
    C_FLOAT64 mWeightedError;
  };

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
     * Enumaration of methods to calculate the weight.
     */
    enum WeightMethod
    {
      SD = 0,
      MEAN
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
     * Retrieve the list of dependent data objects
     * @return const std::map< CCopasiObject *, unsigned C_INT32 > & dependentObjects
     */
    const std::map< CCopasiObject *, unsigned C_INT32 > & getDependentObjects() const;

    /**
     * Calculate the sum of squares for the indexed row of the experiment.
     * If residuals is not NULL residuals will contain the differences
     * between the calculated and the experiment values.
     * @param const unsigned C_INT32 & index
     * @param C_FLOAT64 *& residuals (may be NULL)
     * @return C_FLOAT64 sumOfSquares
     */
    C_FLOAT64 sumOfSquares(const unsigned C_INT32 & index,
                           C_FLOAT64 *& residuals) const;

    /**
     * Calculate the sum of squares for the indexed row of the experiment.
     * On return dependentValues contains the calculated values. If
     * residuals is not NULL residuals will contain the differences
     * between the calculated and the experiment values.
     * @param const unsigned C_INT32 & index
     * @param C_FLOAT64 *& dependentValues (must not be NULL)
     * @return C_FLOAT64 sumOfSquares
     */
    C_FLOAT64 sumOfSquaresStore(const unsigned C_INT32 & index,
                                C_FLOAT64 *& dependentValues);

    /**
     * Calculate statistics by comparing the stored calculated values
     * with the measurements.
     * @return bool success
     */
    bool calculateStatistics();

    /**
     * Reads the header row for the experiment data
     * @return bool success
     */
    bool readColumnNames();

    /**
     * Try to guess the number of columns
     * @return unsigned C_INT32 numColumns
     */
    unsigned C_INT32 guessColumnNumber() const;

    /**
     * Retrieve the column names
     * @return const std::vector< std::string > & columnNames;
     */
    const std::vector< std::string > & getColumnNames() const;

    /**
     * Update the model with the independent data of the experiment
     * @param const unsigned C_INT32 & index
     * @return bool success
     */
    bool updateModelWithIndependentData(const unsigned C_INT32 & index);

    /**
     * Restore the model with the independent data from before the experiment
     * @return bool success
     */
    bool restoreModelIndependentData();

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
     * Retrieve the object map
     * @return CExperimentObjectMap & mpObjectMap
     */
    CExperimentObjectMap & getObjectMap();

    /**
     * Retrieve the list of fitting points
     * @return const CCopasiVector< CFittingPoint > & fittingPoints
     */
    const CCopasiVector< CFittingPoint > & getFittingPoints() const;

    /**
     * This method needs to be called whenever the Object Map
     * is changed
     */
    void updateFittedPoints();

    /**
     * This method is used for output to fill the fitted points
     * with the values of the index data record. If index exceedds the
     * number of data records all values are set to NaN.
     */
    void updateFittedPointValues(const unsigned C_INT32 & index);

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
     * Retrieve the number of data rows
     * @return const unsigned C_INT32 numDataRows
     */
    const unsigned C_INT32 getNumDataRows() const;

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

    /**
     * This is the output method for the statistics for the experiment.
     * This method is called from CFitProblem::printResult.
     * @param std::ostream * ostream
     */
    virtual void printResult(std::ostream * ostream) const;

    /**
     * Retrieve the value of the objective function
     * @param const C_FLOAT64 & errorMean
     */
    const C_FLOAT64 & getObjectiveValue() const;

    /**
     * Retrieve the RMS
     * @param const C_FLOAT64 & RMS
     */
    const C_FLOAT64 & getRMS() const;

    /**
     * Retrieve the mean of the error
     * @param const C_FLOAT64 & errorMean
     */
    const C_FLOAT64 & getErrorMean() const;

    /**
     * Retrieve the std. deviation of the error
     * @param const C_FLOAT64 & errorMeanSD
     */
    const C_FLOAT64 & getErrorMeanSD() const;

    /**
     * Retrieve the objective value for the object.
     * @param CCopasiObject *const& pObject
     * @return C_FLOAT64 objectiveValue
     */
    C_FLOAT64 getObjectiveValue(CCopasiObject * const& pObject) const;

    /**
     * Retrieve the weight for the object.
     * @param CCopasiObject *const& pObject
     * @return C_FLOAT64 weight
     */
    C_FLOAT64 getWeight(CCopasiObject * const& pObject) const;

    /**
     * Retrieve the RMS for the object.
     * @param CCopasiObject *const& pObject
     * @return C_FLOAT64 RMS
     */
    C_FLOAT64 getRMS(CCopasiObject *const& pObject) const;

    /**
     * Retrieve the error mean for the object.
     * @param CCopasiObject *const& pObject
     * @return C_FLOAT64 errorMean
     */
    C_FLOAT64 getErrorMean(CCopasiObject *const& pObject) const;

    /**
     * Retrieve the error mean std. deviations for the object.
     * @param CCopasiObject *const& pObject
     * @param C_FLOAT64 errorMean
     * @return C_FLOAT64 errorMeanSD
     */
    C_FLOAT64 getErrorMeanSD(CCopasiObject *const& pObject,
                             const C_FLOAT64 & errorMean) const;

    /**
     * Retrieve the data point caount for the object.
     * @param CCopasiObject *const& pObject
     * @return unsigned C_INT32 count
     */
    unsigned C_INT32 getCount(CCopasiObject *const& pObject) const;

  private:
    /**
     * Allocates all group parameters and assures that they are
     * properly initialized.
     */
    void initializeParameter();

    /**
     * Calculate/set the weights used in the sum of squares.
     * @return bool success
     */
    bool calculateWeights();

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
     * This is realized as a CCopasiParameter type UINT
     */
    WeightMethod * mpWeightMethod;

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
    //    CCopasiParameterGroup * mpColumnType;

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

    CVector< C_FLOAT64 > mWeightSquare;

    CVector< C_FLOAT64 * > mDependentValues;

    CVector< UpdateMethod * > mIndependentUpdateMethods;

    std::vector< Refresh * > mRefreshMethods;

    CVector< C_FLOAT64 > mIndependentValues;

    unsigned C_INT32 mNumDataRows;

    /**
     * The relevant dependent experimental data after reading a file
     */
    C_FLOAT64 * mpDataDependentCalculated;

    C_FLOAT64 mMean;
    C_FLOAT64 mMeanSD;
    C_FLOAT64 mObjectiveValue;
    C_FLOAT64 mRMS;

    CVector< C_FLOAT64 > mRowObjectiveValue;
    CVector< C_FLOAT64 > mRowRMS;

    CVector< C_FLOAT64 > mColumnObjectiveValue;
    CVector< C_FLOAT64 > mColumnRMS;
    CVector< unsigned C_INT32 > mColumnCount;

    /**
     * A map of all dependent data objects to dependent data columns;
     */
    std::map< CCopasiObject *, unsigned C_INT32 > mDependentObjects;

    CCopasiVector< CFittingPoint > mFittingPoints;
  };

#endif // COPASI_CExperiment
