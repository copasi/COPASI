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

#include <iostream>
#include "model/model.h" 
// #include "output/output.h"
#include "utilities/utilities.h"
#include "CODESolver.h"
#include "CStochSolver.h"

// #include "COutputEvent.h"
class COutputEvent;

class CTrajectory
  {
  public:
    /**
     * The types of method used to calculate the trajectory.
     * This may be done by a continuous method, a stochastic method,
     * or a hybrid of the two. XXX The latter is still to be implemented.
     */
    enum MethodType {UNDEFINED = 0,
                     CONTINUOUS_ODE, STOCH_DIRECT, STOCH_NEXTREACTION, MIXED};

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
    CStochSolver * mStochSolver;
    /**
     *  The time points
     */
    C_INT32 mPoints;

    /**
     *  The size of the array mY
     */
    C_INT32 mN;

    /**
     * The maximum number of steps allowed for stochastic simulations
     */
    C_INT32 mMaxSteps;

    /**
     *  The start time point
     */
    C_FLOAT64 mStartTime;

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
    CTrajectory::MethodType mMethod;

    /**
     * Initial Output Event
     */
    COutputEvent *mOutInit;

    /**
     * Any Point Output Event from beginning to end
     */
    COutputEvent *mOutPoint;

    /**
     * End Phase Output Event
     */
    COutputEvent *mOutEnd;

    /**
     * if the report is to include output at time zero
     */
    C_INT16 mOutputTimeZero;

    //Operations
  public:

    /**
     * default constructor
     */
    CTrajectory();

    /**
     * destructor
     */
    ~CTrajectory();

    /**
     * initialize()
     * @param CModel * aModel
     */
    void initialize();

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

    /**
     *  Set the starting point of the trajectory
     *  @param "const C_FLOAT64 &" time (Default: 0)
     *  @param "const C_FLOAT64 *" particleNumbers (Default: Models Initial Val.)
     */
    void setStartingPoint(const C_FLOAT64 & time = 0,
                          const C_FLOAT64 * particleNumbers = NULL);

    /**
     * Set the maximum number of points for the stochastic simulation.
     * @param max_points The maximum number of points
     */
    void setMaxSteps(C_INT32 max_points);

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
     * Set the method to use
     * @param anInt an int type that will set as mTypeOfSolver
     */
    void setMethod(const CTrajectory::MethodType & anInt);

    /*
     * Get the type of solver
     * @return mTypeOfSolver
     */
    const CTrajectory::MethodType & getMethod() const;

    /*
     * Process the CTrajectory primary function
     * @param ofstream &fout
     */
    void process(std::ofstream &fout);
  };
#endif //CTRAJECOTRY_H
