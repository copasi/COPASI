/*****************************************************************************
* PROGRAM NAME: CJacob.h
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: Declare the CJacob Class, its value is updated in steadyState()
*	       and output in Rep_Stability()			
*****************************************************************************/

#ifndef COPASI_CJacob
#define COPASI_CJacob

#include "model/CModel.h"
#include "tnt/tnt.h"
#include "tnt/cmat.h"

class CJacob {

 private:
  /**
   * Jacob Matrix
   */

  TNT::Matrix <C_FLOAT64> mJacob;

  /**
   *	auxiliary counter for func. evals
   */
  C_INT32	mNfunction;	

  /**
   *  auxiliary counter for jacob. evals
   */
  C_INT32	mNjacob; 

  /**
   * 
   */
  CModel mModel;

 public:
  /**
   * Defaulut constructor
   */
  CJacob();

  /**
   * User defined constructor
   * @param rows is the max row number of Jacob Matrix
   * @param cols is the max column number of Jacob Matrix
   */
  CJacob(int rows, int cols);

  /**
   * Deconstructor
   */

  ~CJacob();

  /**
   * evaluates the Jacobian matrix
   * @param src is the pointer of an array used for evaluating 
   * the Jacob Matrix
   * @param factor is modulation factor for finite differences derivation
   * @param res is the resolution of steady state
   */
  void jacobEval(C_FLOAT64 *src, C_FLOAT64 factor, C_FLOAT64 res);

  /**
   * return the Jacobian matrix
   */
  TNT::Matrix < C_FLOAT64 > getJacob();

  /**
   * Set the Jacobian Matrix
   */
  void setJacob(int rows, int cols);

  /**
   * return the counter of func. evals
   */
  C_INT32 getNfunction();

  /**
   * return counter of jacob. evals
   */
  C_INT32 getNjacob();

  /**
   * Set the counter of func. evals
   */
  void setNfunction(C_INT32 func);

  /**
   * Set the counter of func. evals
   */
  void setNjacob(C_INT32 jacob);

  /**
   * Set the Model
   */
  void setModel(CModel model);
};

#endif
