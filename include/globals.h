// version number related variables
extern long GepasiVersion;
extern long GepasiVersionMajor;
extern long GepasiVersionMinor;
extern long GepasiVersionDevel;
extern string VersionString;
extern string ArchString;
extern string CompiledString;

// the full path to the user-defined kinetics database
extern string UDKinFileName;

// default values
extern double DefaultConc;
extern double DefaultKinConst;
extern double DefaultEndTime;
extern long DefaultNewtonLimit;
extern double DefaultSSRes;
extern double DefaultRelTol;
extern double DefaultAbsTol;
extern long DefaultAdamsMax;
extern long DefaultBDFMax;
extern char DefaultTUnit[];
extern char DefaultCUnit[];
extern char DefaultVUnit[];
extern double DefaultEndTime;
extern long DefaultPoints;
extern long DefaultDyn;
extern long DefaultSS;
extern long DefaultRep;
extern long DefaultTitles;
extern long DefaultQuotes;
extern long DefaultColWidth;
extern long DefaultSeparator;
extern long DefaultRepStruct;
extern long DefaultRepStab;
extern long DefaultRepMCA;
extern long DefaultRepComments;
extern long DefaultReder;
extern double DefaultDerivFactor;
extern long DefaultTimeZero;

// functions
void InitGlobals( void );
long ReadDefaultReg( void );

