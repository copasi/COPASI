/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiTask.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/30 17:59:21 $
   End CVS Header */

/**
 *  CCopasiTask class.
 *  This class is used to describe a task in COPASI. This class is 
 *  intended to be used as the parent class for all tasks whithin COPASI.
 *  
 *  Created for Copasi by Stefan Hoops 2003
 */

#include "copasi.h"

#include "CCopasiTask.h"

const std::string CCopasiTask::TypeName[] =
  {
    "Not set",
    "Stead-State",
    "Time-Course",
    "Scan",
    "Elementary Flux Modes",
    "Optimization",
    "Parameter Fitting",
    ""
  };

const char* CCopasiTask::XMLType[] =
  {
    "NotSet",
    "SteadyState",
    "TimeCourse",
    "Scan",
    "FluxMode",
    "Optimization",
    "ParameterFitting",
    NULL
  };
