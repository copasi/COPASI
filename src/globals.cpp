#include <string>

#include "copasi.h"

// version numbers
int GepasiVersion;
int GepasiVersionMajor;
int GepasiVersionMinor;
int GepasiVersionDevel;
string VersionString;
string ArchString;
string CompiledString;

// the full path to the user-defined kinetics database
string UDKinFileName;

// default values
double DefaultConc = 0.0;
double DefaultKinConst = 1.0;
double DefaultEndTime = 10.0;
int DefaultNewtonLimit = 50;
double DefaultSSRes = 1.0e-9;
double DefaultRelTol = 1.0e-6;
double DefaultAbsTol = 1.0e-12;
int DefaultAdamsMax = 12;
int DefaultBDFMax = 5;
char DefaultTUnit[16] = "s";
char DefaultCUnit[16] = "mM";
char DefaultVUnit[16] = "ml";
int DefaultPoints = 50;
int DefaultDyn = 1;
int DefaultSS = 1;
int DefaultRep = 0;
int DefaultTitles = 0;
int DefaultQuotes = 0;
int DefaultColWidth = 12;
int DefaultSeparator = (int) ' ';
int DefaultRepStruct = 0;
int DefaultRepMCA = 1;
int DefaultRepComments = 1;
int DefaultRepStab = 0;
int DefaultReder = 0;
double DefaultDerivFactor = 0.001;
int DefaultTimeZero = 1;

void InitGlobals( void )
{
#ifdef XXXX
 string Vers;
 int b, devtype;

 // get the version number from the string table
 Vers.LoadString( IDS_VERSION );
 sscanf( LPCTSTR( Vers ), "%d.%d", &GepasiVersionMajor, &b );
 GepasiVersion = GepasiVersionMajor*100000 + b;
 GepasiVersionMinor = b/1000;
 VersionString.Format( "ModEx version %d.%02d", GepasiVersionMajor, GepasiVersionMinor );
 GepasiVersionDevel = b%1000;
 if( GepasiVersionDevel != 0 )
 {
  devtype = GepasiVersionDevel/100;
  if( devtype == 1 )
   VersionString.Format( "ModEx version %d.%02d alpha %d ", GepasiVersionMajor, GepasiVersionMinor, GepasiVersionDevel%100 );
  if( devtype == 2 )
   VersionString.Format( "ModEx version %d.%02d beta %d ", GepasiVersionMajor, GepasiVersionMinor, GepasiVersionDevel%100 );
 }

 // set the compilation date string from macro
 CompiledString.Format("Compiled %s %s", __DATE__, __TIME__);

 // get the architecture from compiler macros
#ifdef _M_ALPHA
 ArchString = "Alpha executable";
#else
# ifdef _M_MRX000
 ArchString = "MIPS R4000 executable";
# else
#  ifdef _M_IX86
 ArchString = "Intel executable";
#  endif
# endif
#endif
 UDKinFileName.Empty();
#endif
}

int ReadDefaultReg( void )
{
#ifdef XXXX
 HKEY  hKey1;
 DWORD  dwType;
 DWORD  dwBytesRead;
 LONG   lRetCode;
 char buffer[512];

 // set the defaults to the hard-coded values first
 DefaultConc = 0.0;
 DefaultKinConst = 1.0;
 DefaultEndTime = 10;
 DefaultNewtonLimit = 50;
 DefaultSSRes = 1.0e-9;
 DefaultRelTol = 1.0e-6;
 DefaultAbsTol = 1.0e-12;
 DefaultAdamsMax = 12;
 DefaultBDFMax = 5;
 strcpy(DefaultTUnit,"s");
 strcpy(DefaultCUnit,"mM");
 strcpy(DefaultVUnit,"ml");
 DefaultEndTime = 10.0;
 DefaultPoints = 50;
 DefaultDyn = 1;
 DefaultSS = 1;
 DefaultRep = 0;
 DefaultTitles = 0;
 DefaultQuotes = 0;
 DefaultColWidth = 12;
 DefaultSeparator = (int) ' ';
 DefaultRepStruct = 0;
 DefaultRepStab = 0;
 DefaultRepMCA = 1;
 DefaultRepComments = 1;
 DefaultReder = 0;
 DefaultDerivFactor = 0.001;
 DefaultTimeZero = 1;

 // open the registry key in read mode
 lRetCode = RegOpenKeyEx( HKEY_CURRENT_USER,
                          "Software\\Enzyme Software\\Gepasi\\Default", 0, 
                           KEY_READ, &hKey1 );
 // if we failed return with error code
 if (lRetCode != ERROR_SUCCESS) goto ReturnEnd;
 // read the values
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Concentrations", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%lg", &DefaultConc );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Kinetic constants", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%lg", &DefaultKinConst );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "End time", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%lg", &DefaultEndTime );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Newton limit", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%d", &DefaultNewtonLimit );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Steady state resolution", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%lg", &DefaultSSRes );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Derivation Factor", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%lg", &DefaultDerivFactor );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Relative tolerance", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%lg", &DefaultRelTol );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Absolute tolerance", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%lg", &DefaultAbsTol );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Adams max order", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%d", &DefaultAdamsMax );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "BDF max order", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%d", &DefaultBDFMax );
 dwBytesRead = 15;
 lRetCode = RegQueryValueEx( hKey1, "Time unit", NULL , &dwType, (BYTE *) &DefaultTUnit, &dwBytesRead); 
 dwBytesRead = 15;
 lRetCode = RegQueryValueEx( hKey1, "Concentration unit", NULL , &dwType, (BYTE *) &DefaultCUnit, &dwBytesRead); 
 dwBytesRead = 15;
 lRetCode = RegQueryValueEx( hKey1, "Volume unit", NULL , &dwType, (BYTE *) &DefaultVUnit, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%lg", &DefaultEndTime );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Points", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%d", &DefaultPoints );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Dynamics", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%d", &DefaultDyn );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Steady state", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%d", &DefaultSS );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Report", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%d", &DefaultRep );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Titles", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%d", &DefaultTitles );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Quotes", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%d", &DefaultQuotes );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Column width", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%d", &DefaultColWidth );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Separator", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%d", &DefaultSeparator );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Report structural", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%d", &DefaultRepStruct );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Report stability", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%d", &DefaultRepStab );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "MCA", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%d", &DefaultRepMCA );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Report Comments", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%d", &DefaultRepComments );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Unscaled MCA", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS)
  sscanf( buffer, "%d", &DefaultReder );
 dwBytesRead = 511;
 lRetCode = RegQueryValueEx( hKey1, "Time Zero", NULL , &dwType, (BYTE *) &buffer, &dwBytesRead); 
 if (lRetCode == ERROR_SUCCESS) sscanf( buffer, "%d", &DefaultTimeZero );
ReturnEnd:
 // close the registry key
 RegCloseKey( hKey1 );
#endif
 return 0;
}



