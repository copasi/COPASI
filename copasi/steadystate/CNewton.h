/**
 *  File name: CNewton.h
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the .h file for the class CNewton. 
 *           It is an important approach to solve the steady state solution problem
 *
 */


#ifndef CNewton_H
#define CNewton_H

#include "model/CModel.h"
#include "utilities/utilities.h"

/**
 * These may be better to appear somewhere else
 */
#define DefaultNewtonLimit 1
#define SS_NOT_FOUND 1
#define SS_FOUND 0
#define SS_SINGULAR_JACOBIAN 2
#define SS_DAMPING_LIMIT 3
#define SS_ITERATION_LIMIT 4

//Note: they may not be 1.0, check where it comes from orignially (Y.H.)
#define DefaultSSRes 1.0 
#define DefaultDerivFactor 1.0


class CNewton
{
  //Attibutes
 private:

  /**
   *  The CModel to work with
   */
  CModel * mModel;

  /**
   * The limit of iterations on Newton's method
   */
  C_INT32 mNewtonLimit;

  /**
   * The steady state resolution
   */
  C_FLOAT64 mSSRes;

  /**
   * The modulation factor for finite differences derivation
   */
  C_FLOAT64 mDerivFactor;

  /**
   *  variable for steady-state solution
   */
  C_FLOAT64 * mSs_x;

  /**
   *  variable for steady-state solution
   */
  C_FLOAT64 * mSs_xnew;


  // variables for steady-state solution
  //add more variables here

  C_FLOAT64 * mSs_dxdt;

  C_FLOAT64 * mSs_h;

  C_FLOAT64 ** mSs_jacob;

  C_INT32 * mSs_ipvt;

  int mSs_solution;

  //  int mSs_unstable;

  /**
   * The number counter of FVal() function
   */
  C_INT32 mSs_nfunction;

  /**
   *  private function, evaluate the balance equations
   */
  //void FEval(int num, double time, double *y, double *ydot );

  /**
   *  private function, evaluate the Jacobian matrix
   */
  void JEval( double *y, double **ydot );


  /*
  // the following functions are from gepasi and have not been used:

  //copy from  void CGepasiDoc::ResetVariables( void )
  NewtonLimit = DefaultNewtonLimit;

  //copy from BOOL CGepasiDoc::OnSaveDocument(LPCTSTR lpszPathName)
  f1.WriteString(LPCTSTR(OutStr));
  OutStr.Format("NewtonLimit=%d\n",NewtonLimit);

  //copy from int CGepasiDoc::BufferToVars(char *buffer)
  if( (buffpt = PointPastNewLine( buffpt, line )) == NULL ) goto ErrorExit;
  fields = sscanf( buffpt, "NewtonLimit=%d\n", &NewtonLimit);
  if( ScanfFailed( fields, 1, line ) ) goto ErrorExit;
  // sanity check
  if( NewtonLimit < 2 )
  {
  PMMessageBox( IDS_WARN_NEWTON, MB_ICONINFORMATION | MB_OK );
  NewtonLimit = DefaultNewtonLimit;
  }

  */

  //Operations
 public:

  /**
   * default constructor
   */
  CNewton();

  /**
   * constructor
   * @param anInt is an int set as mNewtonLimit
   */
  CNewton(C_INT32 anInt);

  /**
   * copy constructor
   * @param source a CNewton object for copy
   */
  CNewton(const CNewton& source);

  /**
   * Object assignment overloading
   * @param source a CNewton object for copy
   * @return an assigned CNewton object
   */
  CNewton& operator=(const CNewton& source);

  /**
   *  destructor
   */
  ~CNewton();


  /**
   *  initialize()
   */
  void initialize();

  /**
   * initialize mSs_x and mSs_xnew
   * it may be changed later and got directly from steady state class
   */
  void init_Ss_x_new(void);


  /**
   *  set CModel
   *  @param aModel is the CModel set as mModel
   */
  void setModel(CModel * aModel);

  /**
   *  get CModel
   *  @return mModel, the private CModel pointer
   */
  CModel * getModel() const;

  /**
   *  set mSSRes
   *  @param aDouble is a double set as mSSRes
   */
  void setSSRes(C_FLOAT64 aDouble);

  /**
   *  get mSSRes
   *  @return mSSRes, the private mSSRes double
   */
  C_FLOAT64 getSSRes() const;

  /**
   *  get mSs_nfunction
   *  @param aInt an int set as the private mSs_nfunction
   */
  void setSs_nfunction(C_INT32 aInt);
 
  /**
   *  get mSs_nfunction
   *  @return mSs_nfunction, the private mSs_nfunction int
   */
  C_INT32 getSs_nfunction() const;
    

  /**
   *  get mSs_xnew
   *  @return mSs_xnew, the private mSs_xnew double pointer
   */
  C_FLOAT64 * getSs_xnew() const;

  /**
   *  get mSs_dxdt
   *  @return mSs_dxdt, the private mSs_dxdt double pointer
   */
  C_FLOAT64 * getSs_dxdt() const;

  /**
   *  set mDerivFactor
   *  @param aDouble is a double set as mDerivFactor
   */
  void setDerivFactor(C_FLOAT64 aDouble);

  /**
   *  get mDerivFactor
   *  @return mDerivFactor, the private mDerivFactor double
   */
  C_FLOAT64 getDerivFactor() const;


  /**
   *  to process the primary function of this class
   */
  void process(void);

  /**
   * Clean up internal pointer variables
   */
  void cleanup(void);


  /**
   * finds out if current state is a valid steady state
   *  destroys the contents of matrix ss_dxdt
   */
  C_INT32 isSteadyState( void );


};
#endif  //CNewton_H
