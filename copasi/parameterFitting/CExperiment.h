// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef COPASI_CExperiment
#define COPASI_CExperiment

#include <string>

#include "copasi/core/CDataVector.h"
#include "copasi/core/CMatrix.h"
#include "copasi/core/CVector.h"
#include "copasi/utilities/CCopasiParameterGroup.h"
#include "copasi/utilities/CCopasiTask.h"

class CExperimentObjectMap;
class CMathContainer;

class CFittingPoint: public CDataContainer
{
  // Operations
public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CFittingPoint * pDataObject
   */
  static CFittingPoint * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  CFittingPoint(const std::string & name = "unknown",
                const CDataContainer * pParent = NO_PARENT);

  CFittingPoint(const CFittingPoint & src,
                const CDataContainer * pParent);

  ~CFittingPoint();

  virtual std::string getObjectDisplayName() const;

  const std::string & getModelObjectCN() const;

  void setValues(const C_FLOAT64 & independent,
                 const C_FLOAT64 & measured,
                 const C_FLOAT64 & fitted,
                 const C_FLOAT64 & weightedError);

private:
  void initObjects();

  // Attributes
private:
  CRegisteredCommonName mModelObjectCN;
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
   * String literals for the GUI to display type names of columns known
   * to COPASI.
   */
  static const std::string TypeName[];

  /**
   * XML type names of tasks known to COPASI.
   */
  static const char* XMLType[];

  /**
   * Enumeration of methods to calculate the weight.
   */
  enum WeightMethod
  {
    MEAN = 0,
    MEAN_SQUARE,
    SD,
    VALUE_SCALING
  };

  /**
   * String literals for the GUI to display weight method known
   * to COPASI.
   */
  static const std::string WeightMethodName[];

  /**
   * XML type names of weight methods known to COPASI.
   */
  static const char* WeightMethodType[];

protected:
  CExperiment(const CExperiment & src);

public:
  /**
   * Default constructor
   * @param const CDataContainer * pParent
   * @param const std::string & name (default: Experiment)
   */
  CExperiment(const CDataContainer * pParent,
              const std::string & name = "Experiment");

  /**
   * Copy constructor
   * @param const CExperiment & src
   * @param const CDataContainer * pParent (default: src data model)
   */
  CExperiment(const CExperiment & src,
              const CDataContainer * pParent);

  /**
   * Specific constructor used for reading COPASI files
   * @param const CCopasiParameterGroup & group
   * @param const CDataContainer * pParent (default: group data model)
   */
  CExperiment(const CCopasiParameterGroup & group,
              const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CExperiment();

  /**
   * Assignment operator
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
   * @param const CMathContainer * pMathContainer
   * @return bool success
   */
  bool compile(const CMathContainer * pMathContainer);

  /**
   * Reads the experiment data form a the given stream
   * @param std::istream & in
   * @param size_t & currentLine
   * @return bool success
   */
  bool read(std::istream & in, size_t & currentLine);

  /**
   * Calculate/set the weights used in the sum of squares.
   * @return bool success
   */
  bool calculateWeights();

  /**
   * Retrieve the mapping of dependent data objects
   * to the index of the column, only counting columns with dependent data
   * @return const std::map< const CDataObject *, size_t > & dependentObjects
   */
  const std::map< const CObjectInterface *, size_t > & getDependentObjectsMap() const;

  /**
   * Calculate the sum of squares for the indexed row of the experiment.
   * If residuals is not NULL residuals will contain the differences
   * between the calculated and the experiment values.
   * @param const size_t & index
   * @param C_FLOAT64 *& residuals (may be NULL)
   * @return C_FLOAT64 sumOfSquares
   */
  C_FLOAT64 sumOfSquares(const size_t & index,
                         C_FLOAT64 *& residuals) const;

  /**
   * Calculate the sum of squares for the indexed row of the experiment.
   * On return dependentValues contains the calculated values. If
   * residuals is not NULL residuals will contain the differences
   * between the calculated and the experiment values.
   * @param const size_t & index
   * @param C_FLOAT64 *& dependentValues (must not be NULL)
   * @return C_FLOAT64 sumOfSquares
   */
  C_FLOAT64 sumOfSquaresStore(const size_t & index,
                              C_FLOAT64 *& dependentValues);

  /**
   * Initialize the storage of an extended time series for plotting.
   * This clears the storage, resizes it to the given size and sets the
   * iterator to the start of the storage.
   * The size given is the number of time points, not the number of data
   */
  void initExtendedTimeSeries(size_t s);

  /**
   * Add one dataset to the extended time series. The time and the simulated dependent
   * values are stored and the iterator is increased
   */
  void storeExtendedTimeSeriesData(C_FLOAT64 time);

  size_t extendedTimeSeriesSize() const;

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
   * @return size_t numColumns
   */
  size_t guessColumnNumber() const;

  /**
   * Retrieve the column names
   * @return const std::vector< std::string > & columnNames;
   */
  const std::vector< std::string > & getColumnNames() const;

  /**
   * Update the model with the independent data of the experiment
   * @param const size_t & index
   * @return bool success
   */
  bool updateModelWithIndependentData(const size_t & index);

  /**
   * set the experiment type
   * @param const CTaskEnum::Task & experimentType
   * @return bool success
   */
  bool setExperimentType(const CTaskEnum::Task & type);

  /**
   * Retrieve the experiment type
   * @return const CTaskEnum::Task & experimentType
   */
  const CTaskEnum::Task & getExperimentType() const;

  void setNormalizeWeightsPerExperiment(bool flag);
  bool getNormalizeWeightsPerExperiment() const;

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
   * Retrieve the file name in case it is a relative filename
   * an absolute path to the file will be created.
   *
   * @return const std::string & fileName
   */
  const std::string & getFileName() const;

  /**
   * @return returns the fileName only (no changing of paths
   * in case the file is a relative one)
   */
  const std::string & getFileNameOnly() const;

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
   * Retrieve the object map
   * @return CExperimentObjectMap & mpObjectMap
   */
  const CExperimentObjectMap & getObjectMap() const;

  /**
   * Retrieve the list of fitting points
   * @return const CDataVector< CFittingPoint > & fittingPoints
   */
  const CDataVector< CFittingPoint > & getFittingPoints() const;

  /**
   * This method needs to be called whenever the Object Map
   * is changed
   */
  void updateFittedPoints();

  /**
   * This method is used for output to fill the fitted points
   * with the values of the index data record. If index exceeds the
   * number of data records all values are set to NaN.
   */
  void updateFittedPointValues(const size_t & index);

  /**
   * Fill the fitted points with values from the extended time series
   */
  void updateFittedPointValuesFromExtendedTimeSeries(const size_t & index);

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
   * @return const size_t numDataRows
   */
  size_t getNumDataRows() const;

  /**
   * Retrieve the separator
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
   * Retrieve the method used for calculating the default weights.
   * @return const WeightMethod & weightMethod
   */
  const WeightMethod & getWeightMethod() const;

  /**
   * Set the weight calculation method and resets manual adjusted weights
   * @param const WeightMethod & weightMethod
   * @return bool success
   */
  bool setWeightMethod(const WeightMethod & weightMethod);

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
   * @param const CObjectInterface * pObject
   * @return C_FLOAT64 objectiveValue
   */
  C_FLOAT64 getObjectiveValue(const CObjectInterface * pObject) const;

  /**
   * Retrieve the default scaling factor for the object.
   * @param const CObjectInterface * pObject
   * @return C_FLOAT64 defaultScale
   */
  C_FLOAT64 getDefaultScale(const CObjectInterface * pObject) const;

  /**
   * Retrieve the scaling factor for the object.
   * @param const CObjectInterface * pObject
   * @return C_FLOAT64 scale or NULL if object can't be found
   */
  const C_FLOAT64* getScale(const CObjectInterface* pObject) const;

  /**
   * @return the scaling matrix
   */
  const CMatrix< C_FLOAT64 > & getScalingMatrix() const;

  /**
   * Retrieve the RMS for the object.
   * @param const CObjectInterface * pObject
   * @return C_FLOAT64 RMS
   */
  C_FLOAT64 getRMS(const CObjectInterface * pObject) const;

  /**
   * Retrieve the sum of errors (scaled residuals) for the object.
   * @param const CObjectInterface * pObject
   * @return C_FLOAT64 errorSum
   */
  C_FLOAT64 getErrorSum(const CObjectInterface * pObject) const;

  /**
   * Retrieve the error mean std. deviations for the object.
   * More specifically this is the sum of the squared deviations of the residuals
   * from the provided errorMean. The sum is over all data points for the object.
   * @param const CObjectInterface * pObject
   * @param C_FLOAT64 errorMean
   * @return C_FLOAT64 errorMeanSD
   */
  C_FLOAT64 getErrorMeanSD(const CObjectInterface * pObject,
                           const C_FLOAT64 & errorMean) const;

  /**
   * Retrieve the data point count for the object.
   * @param const CObjectInterface * pObject
   * @return size_t count
   */
  size_t getColumnValidValueCount(const CObjectInterface * pObject) const;

  /**
  * get number of independent data points for the whole experiment
  * only valid data points (that contain actual data) are counted.
  */
  size_t getValidValueCount() const;

  /**
  * get number of independent data points expected given the number of rows and columns
  *
  */
  size_t getTotalValueCount() const;

  /**
   * Retrieve the list of independent objects
   * @return const CObjectInterface::ObjectSet & independentObjects
   */
  const CObjectInterface::ObjectSet & getIndependentObjects() const;

  /**
   * Fix files written with Version 4.10.55, which wrote the square root of user defined weights for the
   * parameter fitting task
   */
  void fixBuild55();

private:
  /**
   * Allocates all group parameters and assures that they are
   * properly initialized.
   */
  void initializeParameter();

  /**
   * Initialize the scaling matrix
   */
  void initializeScalingMatrix();

private:
  // Attributes

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
  CTaskEnum::Task * mpTaskType;

  /**
   * Indicates whether the weights of this experiment should be normalized to 1
   */
  bool* mpNormalizeWeightsPerExperiment;

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

  /**
   * The individual scale for each residual
   */
  CMatrix< C_FLOAT64 > mScale;

  /**
   * Indicates whether we have missing data
   */
  bool mMissingData;

  CVector< C_FLOAT64 > mMeans;

  CVector< C_FLOAT64 > mColumnScale;

  CVector< C_FLOAT64 > mDefaultColumnScale;

  /**
   * Pointer to the actual independent values in the model
   * in the order in which they occur as colums in the file,
   * which is also the order in which the numbers are stored in the
   * various internal data structures
   */
  CVector< C_FLOAT64 * > mDependentValues;

  CVector< C_FLOAT64 * > mIndependentValues;

  CMathContainer * mpContainer;

  CCore::CUpdateSequence mIndependentUpdateSequence;
  CCore::CUpdateSequence mDependentUpdateSequence;

  CObjectInterface::ObjectSet mIndependentObjects;

  size_t mNumDataRows;

  /**
   * The relevant dependent experimental data after reading a file
   */
  C_FLOAT64 * mpDataDependentCalculated;

  C_FLOAT64 mMean;
  C_FLOAT64 mMeanSD;
  C_FLOAT64 mObjectiveValue;
  C_FLOAT64 mRMS;

  size_t mValidValueCount;

  CVector< C_FLOAT64 > mRowObjectiveValue;
  CVector< C_FLOAT64 > mRowRMS;

  CVector< C_FLOAT64 > mColumnObjectiveValue;
  CVector< C_FLOAT64 > mColumnRMS;
  CVector< size_t > mColumnValidValueCount;

  /**
   * A map of all dependent data objects to dependent data columns
   */
  std::map< const CObjectInterface *, size_t > mDependentObjectsMap;

  CDataVector< CFittingPoint > mFittingPoints;

  //storage for extended time series (for nicer plotting)
  CVector< C_FLOAT64 > mExtendedTimeSeries;

  //points to the next empty space in the time series storage
  C_FLOAT64 * mStorageIt;

  //number of data sets in the extended time series
  size_t mExtendedTimeSeriesSize;
};

#endif // COPASI_CExperiment
