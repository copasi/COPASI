/**
 *  File name: CTrajactory.h
 *
 *  Research Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the .h file for the class CTrajectory. 
 *           It is to solve the trajectory time course problem of copasi
 */

#ifndef CTRAJECTORY_H
#define CTRAJECTORY_H

#include "model/model.h"
#include "utilities/utilities.h"
#include "CODESolver.h"

// #include "COutputEvent.h"

class CTrajectory
{
 public:
    /**
     * The types of method used to calculate the trajectory. 
     * This may be done by a continuous method, a stochastic method, 
     * or a hybrid of the two. XXX The latter is still to be implemented.
     */
    enum MethodType {CONTINUOUS_ODE=1, STOCH_DIRECT, STOCH_NEXTREACTION, MIXED)
  //Attributes
 private:

  /**
   *  The pointer to the CModel with which we are working
   */
  CModel * mModel;

  /**
   *  The pointer to the CODESolver with which we are working
   */
  CODESolver * mODESolver;

  /**
   * The stochastic solver
   */
  CStochSolver *mStochSolver;
  /**
   *  The time points
   */
  C_INT32 mPoints;

  /**
   *  The size of the array mY
   */
  C_INT32 mN;

  /**
   * The maximum number of points allowed for stochastic simulations
   */
  C_INT32 mMaxPoints;
  /**
   *  The end time point
   */
  C_FLOAT64 mEndTime;

  /**
   *  The current time point
   */
  C_FLOAT64 mTime;

  /**
   *  Pointer to array of doubles "y", vector of mole numbers for each particle
   */
  C_FLOAT64 * mY;

  /**
   *  the method to use
   */
  C_INT32 mMethod;

  //Operations
 public:

  /**
   * default constructor
   */
  CTrajectory();
	
  /*
   * A CTrajectory constructor
   */	
  CTrajectory(CModel * aModel, C_INT32 aPoints,
	      C_FLOAT64 aEndTime, C_INT32 aMethod);

  /**
   * Copy constructor
   * @param source a CTrajectory object for copy
   */
  CTrajectory(const CTrajectory& source);

  /**
   * Object assignment overloading
   * @param source a CTrajectory object for copy
   * @return an assigned CTrajectory object
   */
  CTrajectory& operator=(const CTrajectory& source);


  /**
   * destructor
   */	
  ~CTrajectory();

  /**
   * initialize()
   * @param CModel * aModel
   */
  void initialize(CModel * aModel);
        
  /**
   * cleanup()
   */
  void cleanup();
        

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
   * Set the CModel member variable
   * @param aModel a CModel pointer to be set as mCModel
   */	
  void setModel(CModel * aModel);

  /**
   *  Get the CModel member variable
   *  @return mCModel
   */	
  CModel * getModel() const;

  /**
   * Set the CODESolver member variable
   * @param aSolver a CODESolver pointer to be set as mModel member
   */	
  void setODESolver(CODESolver * aSolver);

  /**
   *  Get the CODESolver member variable
   *  @return mODESolver
   */	
  CODESolver * getODESolver() const;

  /*
   * Set the time points
   * @param anInt an int passed to be set as mPoints
   */
  void setPoints(const C_INT32 anInt);

  /*
   * Get the time points
   * @return mPoints
   */
  C_INT32 getPoints() const;

  /*
   * Set the size of array mY, can be obtained from CModel (how??)
   * @param anInt an int passed to be set as mN
   */
  void setArrSize(const C_INT32 anInt);

  /*
   * Get the mY array size
   * @return mN
   */
  C_INT32 getArrSize() const;

  /*
   * calculate the time lenghth
   * @return mN
   */
  C_FLOAT64 calcTimeLength();


  /*
   * Set the end of time points
   * @param aDouble a double type to be set as mEndTime
   */	
  void setEndTime(const C_FLOAT64 aDouble);

  /*
   * Get the end of time points
   * @return "const C_FLOAT64 &" mEndTime
   */
  const C_FLOAT64 & getEndTime() const;

  /*
   * Get the end of time points
   * @return "const C_FLOAT64 &" mTime
   */
  const C_FLOAT64 & getTime() const;

  /*
   * Set the point to the array with the left hand side value
   * @param arrDouble an array of double that will be set as mY
   */	
  void setMY(const C_FLOAT64 * arrDouble);

  /*
   * Get the point to the array with the left hand side value
   * @return mY
   */
  C_FLOAT64 * getMY() const;

  /*
   * Set the method to use
   * @param anInt an int type that will set as mTypeOfSolver
   */
  void setMethod(const C_INT32 anInt);

  /*
   * Get the type of solver
   * @return mTypeOfSolver
   */
  C_INT32 getMethod() const;


  /*
   * Process the CTrajectory primary function
   */	
  void process();
	
};


#endif //CTRAJECOTRY_H
