// GepasiDoc.h : interface of the CGepasiDoc class

// an array of Optimisation parameters
typedef CTypedPtrArray<CObArray,COptParam*> COptParamArray;

 //optimisation variables
 BOOL			OptEnabled;			// set to TRUE if optimisation is enabled
 double			OptSign;			// 1 for minimisation -1 for maximisation
 BOOL			OptDyn;				// TRUE if optimisation is on time course FALSE for SS
 CDatum			OptObjF;			// the objective function
 COptParamArray	OptParam;			// array of optimisation parameters w/ constraints
 int			OptParamSize;		// size of the array f/ opt. parameters
 CString		OptMethod;			// name of the optimisation method to use
 BOOL			OptConstrained;		// TRUE if optimisation has constraints
 double			OptPV[5];			// 5 parameter values for the method
 int			OptModNum;			// ordinal number of optimisation module being used
 UINT			OptIteration;		// number of current iterations of the optimisation
 BOOL			OptSetModel;		// TRUE if model should be set to the optimum found

 double			TempOF;				// holds the value of the objective function temporarily

 //fitting variables
 BOOL			FitEnabled;			// set to TRUE if optimisation is enabled
 BOOL			FitDyn;				// TRUE if optimisation is on time course FALSE for SS
 COptParamArray	FitParam;			// array of optimisation parameters w/ constraints
 int			FitParamSize;		// size of the array f/ opt. parameters
 COptParamArray	FitIConc;			// array of initial concentrations subject to error
 int			FitIConcSize;		// size of the array f/ initial conc. subject to error
 COptParam		*FitICP;				// temporary array to hold all initial conc. COptParam
 
 int			RunSleep;			// amount to Sleep between LSODA calls
 int			RealTimeSimul;		// if 1 attempt will be made to be real time
 int			RunPoints;			// points for the interactive run time
 int			PRP;				// ratio of simul points per run-time point

 CString		ErrorReport;		// keeps list of errors in simulation
 CString		TmpStr;				// temporary string to be used in dynamic and other
                                    // functions that cannot call destructors (use SEH)

 CWinThread		*pThread;			// points to the Simulation Engine's thread
 HANDLE			Resume;				// Event signaled when SE can continue
 HANDLE			Stop;				// Event signaled when SE must stop
 HANDLE			Pause;				// Event signaled when SE must pause
 HANDLE			Continue;			// Event signaled when SE is to continue


// Implementation
public:
	virtual ~CGepasiDoc();

	double OptEvaluate( void );
	void OptSignalIter( double ofv );

private:

	void DeleteOptParameter( int idx );
	
	void UpdateOptParams( BOOL pointer );
	
	void Optimise( void );
	

/////////////////////////////////////////////////////////////////////////////
// FUNCTIONS THAT DON'T BELONG TO CGepasiDoc BUT WORK CLOSELY WITH IT

void OptimisationCallback( double ofv );



