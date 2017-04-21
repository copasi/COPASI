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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CILDMMethod
#define COPASI_CILDMMethod

#include <sstream>

#include "copasi/core/CMatrix.h"
#include "copasi/core/CVector.h"
#include "CTSSAMethod.h"

//#include "odepack++/CLSODA.h"

//#include "utilities/CMatrix.h"
//#include "core/CDataArray.h"

class CModel;
class CState;

class CILDMMethod : public CTSSAMethod
{
  // Operations
private:
  /**
   * Default constructor.
   */
  CILDMMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: tssILDM)
   * @param const CTaskEnum::Task & taskType (default: tssAnalysis)
   */
  CILDMMethod(const CDataContainer * pParent,
              const CTaskEnum::Method & methodType = CTaskEnum::tssILDM,
              const CTaskEnum::Task & taskType = CTaskEnum::tssAnalysis);

  /**
   * Copy constructor.
   * @param "const CILDMMethod &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CILDMMethod(const CILDMMethod & src,
              const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CILDMMethod();

  /**
   *  Intialize the method parameter
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
  virtual void  step(const double & deltaT);

  /**
   *  This instructs the method to prepare for integration
   *  starting with the initialState given.
   */
  virtual void start();

  /**
   *
   **/
  void newton(C_FLOAT64 *ys, C_INT & slow, C_INT & info);

  /**
     *
     **/

  void transformation_norm(C_INT & slow, C_INT & info);

  void deuflhard(C_INT & slow, C_INT & info);

  /**
     *vectors contain whole data for all calculation steps
     **/

  CVector<C_FLOAT64> mReacSlowSpace; // NEW TAB

  /* temporary tabs */

  CMatrix<C_FLOAT64> mTMP1;
  CMatrix<C_FLOAT64> mTMP2;
  CMatrix<C_FLOAT64> mTMP3;

  std::vector< CMatrix<C_FLOAT64> > mVec_mVslow;
  std::vector< CMatrix<C_FLOAT64> > mVec_mVslowMetab;
  std::vector< CVector<C_FLOAT64> > mVec_mVslowSpace;
  std::vector< CVector<C_FLOAT64> > mVec_mVfastSpace;
  std::vector< CVector<C_FLOAT64> > mVec_mReacSlowSpace;

  /* temporary tabs */
  std::vector< CMatrix<C_FLOAT64> > mVec_mTMP1;
  std::vector< CMatrix<C_FLOAT64> > mVec_mTMP2;
  std::vector< CMatrix<C_FLOAT64> > mVec_mTMP3;

  /**
   *CArraAnnotations for every ILDM-tab in the CQTSSAResultSubWidget
   **/

  /*
    std::map< std::string, CArrayAnnotation* > mapTableToName;
    std::vector<std::string>  tableNames;
  */

  CDataArray* pVslowPrintAnn;
  CDataArray* pVslowMetabPrintAnn;
  CDataArray* pVslowSpacePrintAnn;
  CDataArray* pVfastSpacePrintAnn;
  CDataArray* pReacSlowSpacePrintAnn;

  /* temporary tabs */

  CDataArray* pTMP1PrintAnn;
  CDataArray* pTMP2PrintAnn;
  CDataArray* pTMP3PrintAnn;

  /**
  *required for creation of above listed CArrayAnnotation
  **/
  CDataArray* pTmp1;
  CDataArray* pTmp2;
  CDataArray* pTmp3;
  CDataArray* pTmp4;
  CDataArray* pTmp5;

  /* temporary tabs */

  CDataArray* pTMP1;
  CDataArray* pTMP2;
  CDataArray* pTMP3;

  /**
  *input for every CArraAnnotations
  *contain data for single stepcalculation
  **/
  CMatrix<C_FLOAT64> mVslowPrint;
  CMatrix<C_FLOAT64> mVslowSpacePrint;
  CMatrix<C_FLOAT64> mVfastSpacePrint;
  CMatrix<C_FLOAT64> mVslowMetabPrint;
  CMatrix<C_FLOAT64> mReacSlowSpacePrint;

  /* temporary tabs */

  CMatrix<C_FLOAT64> mTMP1Print;
  CMatrix<C_FLOAT64> mTMP2Print;
  CMatrix<C_FLOAT64> mTMP3Print;

  /**
  * return CArrayAnnotation for visualization in ILDM-tab
  * in the CQTSSAResultSubWidget
  **/

  /*
    const std::vector<std::string> getTableName() const
    {return tableNames;}

    const CArrayAnnotation* getTable(std::string name)
    {return mapTableToName[name];}
  */

  const CDataArray* getVslowPrintAnn() const
  {return pVslowPrintAnn;}
  const CDataArray* getVslowSpacePrintAnn() const
  {return pVslowSpacePrintAnn;}
  const CDataArray* getVfastSpacePrintAnn() const
  {return pVfastSpacePrintAnn;}
  const CDataArray* getVslowMetabPrintAnn() const
  {return pVslowMetabPrintAnn;}
  const CDataArray* getReacSlowSpacePrintAnn() const
  {return pReacSlowSpacePrintAnn;}

  /* temporary tabs */
  const CDataArray* getTMP1PrintAnn() const
  {return pTMP1PrintAnn;}
  const CDataArray* getTMP2PrintAnn() const
  {return pTMP2PrintAnn;}
  const CDataArray* getTMP3PrintAnn() const
  {return pTMP3PrintAnn;}

  /* temporary tabs */

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
  void createAnnotationsM();

  /**
  * set the every CArrayAnnotation for the requested step
  * set the desription of CArayAnnotation for both dimensions
  **/
  //void setAnnotationM(int step);
  virtual bool setAnnotationM(size_t step);

  /**
   *  print of the standart report sequence for ILDM Method
   *  @param std::ostream * ostream
   **/
  void printResult(std::ostream * ostream) const;
};
#endif // COPASI_CILDMMethod
