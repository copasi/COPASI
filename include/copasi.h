// copasi.h
// 
// This file contains compatability issues
// (C) Stefan Hoops 2001
//

#ifndef COPASI_copasi
#define COPASI_copasi

using namespace std ;

#ifdef WIN32 
#define COPASI__msbug (enum)
#else 
#define COPASI__msbug
#endif  // WIN32


#endif // COPASI_copasi
