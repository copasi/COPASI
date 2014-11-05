//
//  CCopasiTaskStatus.h
//  COPASI
//
//  Created by Sven Sahle on 04.11.14.
//
//

#ifndef __COPASI__CCopasiTaskStatus__
#define __COPASI__CCopasiTaskStatus__

//#include <stdio.h>

//TODO if we don't mind the overhead this could be converted to a CCopasiObject

/**
 * This class contains status information of a CCopasiTask. 
 * It includes information whether the task is initialized, finished, etc.
 * and also the result status (success or error, also task specific information)
 */
class CCopasiTaskStatus
{
  CCopasiTaskStatus();

  /*virtual*/ void print(std::ostream * ostream) const;
  
  void setInitialized();


};

#endif /* defined(__COPASI__CCopasiTaskStatus__) */
