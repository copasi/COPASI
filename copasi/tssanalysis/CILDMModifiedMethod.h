// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef COPASI_CILDModMethod
#define COPASI_CILDModMethod

#include <sstream>

#include "copasi/core/CMatrix.h"
#include "copasi/core/CVector.h"
#include "CTSSAMethod.h"

class CModel;
class CState;

/**
 * @brief The CILDMModifiedMethod class implementes the modified ILDM method
 *
 * Full details described in: http://copasi.org/Support/User_Manual/Methods/Time_Scale_Separation_Methods/Modified_ILDM/
 */
class CILDMModifiedMethod : public CTSSAMethod
{
private:
  /**
   * Default constructor.
   */
  CILDMModifiedMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: tssILDMModified)
   * @param const CTaskEnum::Task & taskType (default: tssAnalysis)
   */
  CILDMModifiedMethod(const CDataContainer * pParent,
                      const CTaskEnum::Method & methodType = CTaskEnum::Method::tssILDMModified,
                      const CTaskEnum::Task & taskType = CTaskEnum::Task::tssAnalysis);

  /**
   * Copy constructor.
   * @param "const CILDMMethod &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CILDMModifiedMethod(const CILDMModifiedMethod & src,
                      const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  virtual ~CILDMModifiedMethod();

  /**
   * Initialize the method parameter
   */
  virtual void initializeParameter();

  /**
   *  This instructs the method to calculate a time step of deltaT
   *  starting with the current state, i.e., the result of the previous
   *  step.
   *  The new state (after deltaT) is expected in the current state.
   *  The return value is the actual timestep taken.
   *  @param "const double &" deltaT
   */
  virtual void step(const double & deltaT);

  /**
   *  This instructs the method to prepare for integration
   *  starting with the initialState given.
   */
  virtual void start();

  /**
  * return CArrayAnnotation for visualization in ILDM-tab
  * in the CQTSSAResultSubWidget
  **/
  const CDataArray* getVslowPrintAnn() const;
  const CDataArray* getVslowSpacePrintAnn() const;
  const CDataArray* getVfastSpacePrintAnn() const;
  const CDataArray* getVslowMetabPrintAnn() const;

  /**
   * upgrade all vectors with values from actually calculalion for current step
   **/
  void setVectors(int slowMode);

  /**
   * empty every vector to be able to fill them with new values for a
   * new calculation also nullify the step counter
   **/
  void emptyVectors();

  /**
   * create the CArraAnnotations for every ILDM-tab in the CQTSSAResultSubWidget
   * input for each CArraAnnotations is a seperate CMatrix
   **/
  virtual void createAnnotationsM();

  /**
   * initialize output for the result elements, this method
   * initializes the output elements so that an output handler
   * can be used afterwards
   **/
  virtual void initializeOutput();

  /**
   * set the every CArrayAnnotation for the requested step
   * set the desription of CArayAnnotation for both dimensions
   **/
  virtual bool setAnnotationM(size_t step);

  /**
   *  print of the standart report sequence for ILDM Method
   *  @param std::ostream * ostream
   **/
  virtual void printResult(std::ostream * ostream) const;

protected:

  void deuflhard_metab(C_INT & slow, C_INT & info);

  void newton_new(C_INT *index_metab, C_INT & slow, C_INT & info);

  void newton_for_timestep(C_INT metabolite_number, C_FLOAT64 &y_consistent, C_INT & info);

  void evalsort(C_FLOAT64 * reval, C_INT * index, const C_INT & dim_x);

protected:
  /**
   * vectors contain whole data for all calculationsteps
   **/
  std::vector< CMatrix<C_FLOAT64> > mVec_mVslow;
  std::vector< CMatrix<C_FLOAT64> > mVec_mVslowMetab;
  std::vector< CVector<C_FLOAT64> > mVec_mVslowSpace;
  std::vector< CVector<C_FLOAT64> > mVec_mVfastSpace;

  /**
   * CArraAnnotations for every ILDM-tab in the CQTSSAResultSubWidget
   **/

  CDataArray* pVslowPrintAnn;
  CDataArray* pVslowMetabPrintAnn;
  CDataArray* pVslowSpacePrintAnn;
  CDataArray* pVfastSpacePrintAnn;

  /**
   *required for creation of above listed CArrayAnnotation
   **/
  CDataArray* pTmp1;
  CDataArray* pTmp2;
  CDataArray* pTmp3;
  CDataArray* pTmp4;

  /**
   * input for every CArraAnnotations
   * contain data for single stepcalculation
   **/
  CMatrix<C_FLOAT64> mVslowPrint;
  CMatrix<C_FLOAT64> mVslowSpacePrint;
  CMatrix<C_FLOAT64> mVfastSpacePrint;
  CMatrix<C_FLOAT64> mVslowMetabPrint;


};
#endif // COPASI_CILDMMethod
