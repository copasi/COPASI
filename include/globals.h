// version number related variables
extern int GepasiVersion;
extern int GepasiVersionMajor;
extern int GepasiVersionMinor;
extern int GepasiVersionDevel;
extern string VersionString;
extern string ArchString;
extern string CompiledString;

// the full path to the user-defined kinetics database
extern string UDKinFileName;

// default values
extern double DefaultConc;
extern double DefaultKinConst;
extern double DefaultEndTime;
extern int DefaultNewtonLimit;
extern double DefaultSSRes;
extern double DefaultRelTol;
extern double DefaultAbsTol;
extern int DefaultAdamsMax;
extern int DefaultBDFMax;
extern char DefaultTUnit[];
extern char DefaultCUnit[];
extern char DefaultVUnit[];
extern double DefaultEndTime;
extern int DefaultPoints;
extern int DefaultDyn;
extern int DefaultSS;
extern int DefaultRep;
extern int DefaultTitles;
extern int DefaultQuotes;
extern int DefaultColWidth;
extern int DefaultSeparator;
extern int DefaultRepStruct;
extern int DefaultRepStab;
extern int DefaultRepMCA;
extern int DefaultRepComments;
extern int DefaultReder;
extern double DefaultDerivFactor;
extern int DefaultTimeZero;

// functions
void InitGlobals( void );
int ReadDefaultReg( void );

