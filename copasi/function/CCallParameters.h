/**
 * CCallParameters
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_CCallParameters
#define COPASI_CCallParameters

#include <vector>
#include "CCallParameter.h"

class CCallParameters : public std::vector< const void * >
  {};

#endif // COPASI_CCallParameters
