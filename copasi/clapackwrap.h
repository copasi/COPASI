extern "C"
  {
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
#define max _cpp_min
#endif // WIN32
