#ifdef min
# undef min
#endif // min

#ifdef max
# undef max
#endif // max

extern "C"
  {
#ifdef USE_CLAPACK
# include "f2c.h"
#endif

#include "clapack.h"        //use CLAPACK
  }

#ifdef min
# undef min
#endif // min

#ifdef max
# undef max
#endif // max

#ifdef WIN32
#define min _cpp_min
#define max _cpp_max
#endif // WIN32
