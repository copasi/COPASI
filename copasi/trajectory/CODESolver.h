/**
 * CODESolver
 *
 * (C) Pedro Mendes 2001, based on code in Gepasi (C) Pedro Mendes 1990-2000
 */
#ifndef COPASI_CODESolver
#define COPASI_CODESolver

#include "utilities/CReadConfig.h"
#include "utilities/CWriteConfig.h"
#include "utilities/CVersion.h"
#include "Clsoda.h"

class CODESolver
{
  // Attributes
 private:
  /**
   * Version number of this class
   */
  CVersion mVersion;

  /**
   *  Name of the selected ODE solver.
   */
  string mName;

  /**
   *  Index of selected ODE solver.
   */
  C_INT32 mMethod;

  /**
   *  Current time.
   */
  C_FLOAT64 mTime;

  /**
   *  Requested end time.
   */
  C_FLOAT64 mEndt;

  /**
   *  Old time ?????????.
   */
  C_FLOAT64 mOldt;

  /**
   *  Relative tolerance.
   */
  C_FLOAT64 mRtol;

  /**
   *  Default relative tolerance.
   */
  static C_FLOAT64 mRtolDefault;

  /**
   *  Absolute tolerance.
   */
  C_FLOAT64 mAtol;

  /**
   *  Default absolute tolerance.
   */
  static C_FLOAT64 mAtolDefault;

  /**
   *  Maximum order for BDF method.
   */
  C_INT32 mBDF;

  /**
   *  Default maximum order for BDF method.
   */
  static C_INT32 mBDFDefault;

  /**
   *  Maximum order for Adams method.
   */
  C_INT32 mAdams;

  /**
   *  Default maximum order for Adams method.
   */
  static C_INT32 mAdamsDefault;

  /**
   *  LSODA state.
   */
  C_INT32 mState;

  /**
   *  Time increment.
   */
  C_FLOAT64 mIncr;

  /**
   *  Dimension of the ODE system.
   */
  C_INT32 mDim;

  /**
   *  Pointer to the array with left hand side values.
   */
  C_FLOAT64 * mY;

  /**
   *  Pointer to lsoda integrator
   */
  Clsoda * mLsoda;

  /**
   *  Pointer to model
   */
  CModel * mModel;

  // copies of lsoda internals
  C_FLOAT64 intst;  // nst
  C_FLOAT64 nfeval; // nfe
  C_FLOAT64 njeval; // nje
  C_FLOAT64 stsize; // h


  // Operations
 public:
  /**
   *  Default constructor.
   */
  CODESolver();

  /**
   *  Destructor.
   *  The destructor does nothing.
   */
  ~CODESolver();

  /**
   *  Loads parameters for this solver with data coming from a
   *  CReadConfig object. (CReadConfig object reads an input stream)
   *  @param configbuffer reference to a CReadConfig object.
   *  @return mFail
   *  @see mFail
   */
  C_INT32 load(CReadConfig & configbuffer);

  /**
   *  Saves the parameters of the solver to a CWriteConfig object.
   *  (Which usually has a file attached but may also have socket)
   *  @param configbuffer reference to a CWriteConfig object.
   *  @return mFail
   *  @see mFail
   */
  C_INT32 save(CWriteConfig & configbuffer);

  /**
   *  Returns a string with the name of this solver.
   *  @return mName
   *  @see mName
   */
  string getName();

  /**
   *  Initializes the solver routine.
   *  @param mF pointer to function that evaluates RHS
   *  @param y pointer to vector containing LHS values
   *  @param n dimension of the problem
   *  @param method solver to be used
   */
  void initialize(CModel & model,
                  C_FLOAT64* y,
                  C_INT32 n,
                  C_INT32 method = 1);

  /**
   *  Cleans up memory, etc, such that solver is ready to be
   *  initialized for next time.
   *
   */
  void cleanup();

  /**
   *  Integrate the system from t to et using the selected solver
   *  @param t current time.
   *  @param et end time (for requested solution)
   *  @return 0 if successful or an error code otherwise
   */
  C_INT32 step(C_FLOAT64 t, C_FLOAT64 et);

  /**
   *  Loads parameters specific for the LSODA solver, from a
   *  CReadConfig object. (CReadConfig object reads an input stream)
   *  @param configbuffer reference to a CReadConfig object.
   *  @return mFail
   *  @see mFail
   */
  static C_INT32 loadLSODAParameters(CReadConfig & configbuffer);

  /**
   *  Saves the parameters specific for the LSODA solver to a
   *  CWriteConfig object. (Which usually has a file attached but
   *  may also have socket)
   *  @param configbuffer reference to a CWriteConfig object.
   *  @return mFail
   *  @see mFail
   */
  static C_INT32 saveLSODAParameters(CWriteConfig & configbuffer);

 private:
  /**
   *  Uses LSODA to integrate the system from t to et
   *  @param t current time.
   *  @param et end time (for requested solution)
   *  @return 0 if successful or an error code otherwise
   */
  C_INT32 lSODAStep(C_FLOAT64 t, C_FLOAT64 et);
};

#endif // CODESolver
