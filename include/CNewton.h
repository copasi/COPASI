/**
  CNewton.h

 */

#ifndef CNewton_H
#define CNewton_H

#include "CModel.h"
#include "utilities.h"

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

    /**
     * The number counter of FVal() function
     */
     //  C_INT32 mFunctionCounter;

    /**
     *  private function, evaluate the balance equations
     */
     void FEval(int num, double time, double *y, double *ydot );

    /**
     *  private function, evaluate the Jacobian matrix
     */
     void JEval( double *y, double **ydot );


   /*
      // variables for steady-state solution
// double			*ss_x;
 double			*ss_dxdt;
 //double			*ss_xnew;
 double			*ss_h;
 int			*ss_ipvt;
 int			ss_solution;
 int			ss_unstable;

     // copy from GepasiDoc.cpp void CGepasiDoc::InitialiseEngine( void ).
     //
     // Newton variables
 mSs_x = new double[Model.TotMetab+1];
 mSs_xnew = new double[Model.TotMetab+1];
 ss_dxdt = new double[Model.TotMetab+1];
 ss_h = new double[Model.TotMetab+1];
 ss_ipvt = new int[Model.IndMetab+1];
 ss_jacob = new double *[Model.TotMetab+1];
 for( i=0; i<Model.TotMetab+1; i++ )
  ss_jacob[i] = new double[Model.TotMetab+1];

  //copy from void CGepasiDoc::CleanupEngine( void )
  // Newton variables
// delete [] mSs_x;
// delete [] mSs_xnew;
 delete [] ss_dxdt;
 delete [] ss_h;
 delete [] ss_ipvt;
 for( i=0; i<Model.TotMetab+1; i++ ) delete [] ss_jacob[i];
 delete [] ss_jacob;

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
     * a counter for Fval() function
     */
     static int ss_nfunction;

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
     *  set CModel
     *  @param aModel is the CModel set as mModel
     */
     void SetModel(CModel * aModel);

    /**
     *  get CModel
     *  @return mModel, the private CModel pointer
     */
     CModel * GetModel() const;

    /**
     *  set mSSRes
     *  @param aDouble is a double set as mSSRes
     */
     void SetSSRes(C_FLOAT64 aDouble);

    /**
     *  get mSSRes
     *  @return mSSRes, the private mSSRes double
     */
     C_FLOAT64 GetSSRes() const;

    /**
     *  set mDerivFactor
     *  @param aDouble is a double set as mDerivFactor
     */
     void SetDerivFactor(C_FLOAT64 aDouble);

    /**
     *  get mDerivFactor
     *  @return mDerivFactor, the private mDerivFactor double
     */
     C_FLOAT64 GetDerivFactor() const;


    /**
     *  to process the primary function of this class
     */
     void ProcessNewton(void);

    /**
     * Clean up internal pointer variables
     */
     void Cleanup(double * ss_dxdt, 
                       double * ss_h, C_INT32 * ss_ipvt, double ** ss_jacob);

     /**
      * returns the largest value in a vector
      * @param mtm is a pointer to ??????
      */

     //C_FLOAT64 SS_XNorn( C_FLOAT64 * mtx );


};



#endif  //CNewton_H










