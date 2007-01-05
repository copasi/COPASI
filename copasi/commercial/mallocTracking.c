/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commercial/Attic/mallocTracking.c,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/12/12 21:41:32 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 **
 **  mallocTracking.c
 **
 **   This file contains all the code necessary to
 **   track all uses of malloc and free to see if you have:
 **    1).  extra free calls
 **    2).  missing free calls
 **    3).  buffer over runs
 **    4).  buffer underruns
 **
 **
 **  Version History:
 **   1.0   Release   June 11, 2001   ACG@kagi.com
 **     -- code yanked from ACGFramework.c
 **
 **  mallocTracking.c is  Copyright(c) 2002 Kagi
 **  All Rights Reserved.
 **
 **  Permission is granted to use this code module for development
 **  and deployment of a Kagi ACG free of charge as long as Kagi
 **  processes your payments for those application(s) .
 **  No warranty is made as to the suitability
 **  of mallocTracking.c to your application or even that mallocTracking.c is bug or
 **  error free.
 **
 **
 **  BECAUSE THE MODULE IS LICENSED FREE OF CHARGE, THERE IS NO
 **  WARRANTY FOR THE MODULE, TO THE EXTENT PERMITTED BY APPLICABLE LAW.
 **  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR
 **  OTHER PARTIES PROVIDE THE MODULE "AS IS" WITHOUT WARRANTY OF ANY
 **  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
 **  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 **  PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE
 **  MODULE IS WITH YOU.  SHOULD THE MODULE PROVE DEFECTIVE, YOU ASSUME
 **  THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
 **
 **  If you make any corrections to the basic module or have suggestions
 **   please send them to ACG@kagi.com so others may benefit
 **
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define  kREALMALLOCTRACK 1  /* tells the header file not to replace malloc with mallocTrack routines */
#include "mallocTracking.h"

static void *mallocTrack_Malloc(size_t size);
static void mallocTrack_trackMalloc(void *ptr);
static void mallocTrack_atExitTime(void);
static void mallocTrack_defaultErrorStringRoutine(char *stringToPrint);
static void mallocTrack_reportErrorString(char *string);
static size_t mallocTrack_ValidateAllocationLength(void *myPointer, Boolean *hasOverflow,
    Boolean *hasUnderflow, Boolean *hasBeenFreed);
static size_t mallocTrack_ValidateAllocation(void *myPointer);
static void mallocTrack_DoFree(void *myPointer, int indexIntoMallocArray);

/*

sample useage

just put:

#include "mallocTracking.h"

Into any file you want to trace and run the program normally.
If you have errors they will printed to stderr

 */

/*
 ** GLOBALS
 */
MALLOCTRACK_ERROR_FUNC __errorStringFunc = mallocTrack_defaultErrorStringRoutine;
void **__mallocArray = NULL;
int __maxNumOfMallocCalls = kMaxMallocCallsStart;  /* don't reset if persistant */
Boolean __isInTrackingMode = FALSE;

/* error handling */

/*
 ** mallocTrack_defaultErrorStringRoutine
 **
 ** default so code does not break on basic run
 */
static void mallocTrack_defaultErrorStringRoutine(char *string)
{

  fprintf(stderr, "STDERR:  %s", string);
  return;
}

/*
 ** mallocTrack_installErrorStingCallback
 **
 ** In CGI, DLL you want some other handler so use this to install it
 */
MALLOCTRACK_ERROR_FUNC mallocTrack_installErrorStingCallback(MALLOCTRACK_ERROR_FUNC newHandler)
{

  MALLOCTRACK_ERROR_FUNC oldHandler = __errorStringFunc;

  __errorStringFunc = newHandler;

  return(oldHandler);
}

/*
 ** mallocTrack_reportErrorString
 **
 **  report the string via the installed handler
 */
static void mallocTrack_reportErrorString(char *string)
{

  if (__errorStringFunc != NULL)
    {
      (*__errorStringFunc)(string);
    }
  return;
}

/* init, reinit, stop, start and exit stuff */

/*
 ** mallocTrack_initialize
 **
 **  set-up chains
 **
 */
Boolean mallocTrack_initialize(void)
{

  if (__mallocArray == NULL)
    {
      /* allocate auto grow tracking system */
      if ((__mallocArray = (void**)malloc(__maxNumOfMallocCalls * sizeof(void*))) == NULL)
        {
          mallocTrack_reportErrorString("\nFailed to allocate malloc buffer, big error, returning.");
          return(FALSE);
        }
      /* start to track stuff */
      mallocTrack_resume();

      /* at exit cause system cleanup */
      atexit(mallocTrack_atExitTime);
    }

  return(mallocTrack_reInitialize());
}

/*
 ** mallocTrack_reInitialize
 **
 **  clear chains
 **
 */
Boolean mallocTrack_reInitialize(void)
{

  int iterator;

  if (__mallocArray == NULL)
    {
      mallocTrack_reportErrorString("\nTracking array not allocated, big error, returning.");
      return(FALSE);
    }

  /* pre clear the global */
  for (iterator = 0;((__mallocArray != NULL) && (iterator < __maxNumOfMallocCalls));iterator++)
    __mallocArray[iterator] = NULL;

  return(TRUE);
}

/*
 ** mallocTrack_atExitTime
 **
 **  clear chains
 **
 */
static void mallocTrack_atExitTime(void)
{

  int iterator;

  if (__mallocArray == NULL)
    {
      mallocTrack_reportErrorString("\nTracking array not allocated, big error, returning.");
      return;
    }

  for (iterator = 0;iterator < __maxNumOfMallocCalls;iterator++)
    {
      /* safety clean the buffers */
      if (__mallocArray[iterator] != NULL)
        {
          /* ty free(__mallocArray[iterator]); */
          mallocTrack_DoFree(__mallocArray[iterator], iterator);
        }
      __mallocArray[iterator] = NULL;
    }

  /*
  ** can not have this here because it causes output that is not in XML and screws up parser
  **
  ** mallocTrack_reportErrorString("\nINFORMATIONAL ONLY -- default mallocTrack does not check for deallocation error at exit time, you must do this your self.");
  */

  free(__mallocArray);

  return;
}

/*
 ** mallocTrack_resume
 **
 **  start to track malloc/realloc/free again
 **
 */
void mallocTrack_resume(void)
{

  __isInTrackingMode = TRUE;

  return;
}

/*
 ** mallocTrack_suspend
 **
 **  stop tracking malloc/realloc/free again
 **
 */
void mallocTrack_suspend(void)
{

  __isInTrackingMode = FALSE;

  return;
}

/*********************************************************************************************
 **  mallocTrack_Malloc
 **
 **   Centeralize the memory allocation for Framework
 **   In this Framework we store the size in the front for debugging reasons only
 **   In the back and front we put in 'AAAA' pattern for debugging reasons only
 **
 **  internal structure looks like this myPointer = (length)AAAA(your buffer)AAAA
 *********************************************************************************************/
static void *mallocTrack_Malloc(size_t size)
{
  void *myPointer;
  size_t *p;

  if ((myPointer = (void*)malloc(size + sizeof(size_t) + 2 * (kNumberOfTags * sizeof(char)))) != NULL)
    {
      /* prefix it with the length */
      p = (size_t*)myPointer;
      *p = size;

      /* put in underwrite catch */
      memset(((char*)myPointer + sizeof(size_t)), kAllocationMarker, kNumberOfTags*sizeof(char));  /* Rob Muller bug 6.23.01 */

      /* the pointer we hand back is clear */
      memset((void*)((char*)myPointer + sizeof(size_t) + (kNumberOfTags*sizeof(char))) , 0, size*sizeof(char));

      /* put in overwrite catch */
      memset((void*)((char*)myPointer + sizeof(size_t) + (kNumberOfTags*sizeof(char)) + size), kAllocationMarker, kNumberOfTags);

      /*
      **
      ** don't track here, use different routine to do that (mallocTrack_MallocAndTrack)
      **
      */

      myPointer = (void *)((char*)myPointer + sizeof(size_t) + (kNumberOfTags * sizeof(char)));
    }
  else
    {
      myPointer = NULL;
    }

  /* pass back a useful pointer */
  return(myPointer);
}

/*********************************************************************************************
 **  mallocTrack_Free
 **
 **   Centeralize the memory deallocation for Framework
 **
 *********************************************************************************************/
void mallocTrack_Free(void *myPointer)
{
  int iterator = 0;
  int index = -1;

  for (iterator = 0;((iterator < __maxNumOfMallocCalls) && (__mallocArray != NULL));iterator++)
    {
      if (__mallocArray[iterator] == myPointer)
        {
          index = iterator;
          break;
        }
    }

  mallocTrack_DoFree(myPointer, index);

  return;
}

/*********************************************************************************************
 **  mallocTrack_DoFree
 **
 **   Do all the work for the free call
 **   Mostly a way to cut down on unnecessary scanning of __mallocArray
 **
 **   In this Framework we store the size in the front for debugging reasons only
 **   In the back we put in 'AAAA' pattern for debugging reasons only
 **
 **   internal structure looks like this truePointer = (length)AAAA(myPointer)AAAA
 **
 *********************************************************************************************/
static void mallocTrack_DoFree(void *myPointer, int indexIntoMallocArray)
{
  size_t length = 0;
  char *pA = NULL;
  Boolean hasOverflow = FALSE;  /* overrun or underrun */
  Boolean hasUnderflow = FALSE;  /* overrun or underrun */
  Boolean hasBeenFreed = FALSE;    /* was freed before */

  if (indexIntoMallocArray != -1)
    {
      if (__mallocArray[indexIntoMallocArray] == myPointer)
        {
          /*
          ** we found we are tracking this pointer
          ** do what is necessary to free it and mark it so
          */
          if ((length = mallocTrack_ValidateAllocation(myPointer)) != 0)
            {
              pA = (char*)myPointer - (sizeof(size_t) + (kNumberOfTags * sizeof(char)));
              __mallocArray[indexIntoMallocArray] = NULL;
              /* put in FREEd catch */
              memset(((char*)pA + sizeof(size_t)), kFreedMarker, kNumberOfTags*sizeof(char));

              /* put in FREEd catch */
              length = *((size_t*)pA);
              memset((void*)((char*)pA
                              + sizeof(size_t)
                              + (kNumberOfTags*sizeof(char))
                              + length),
                     kFreedMarker,
                     kNumberOfTags);
              free((void*)pA);
              myPointer = NULL; /* fix up so we don't free it later */
            }
          else
            {
              /*
              ** in list, but problem in when validation
              */
              if (__isInTrackingMode == TRUE)
                {
                  printf("\nPointer (%#lX)is currupt, be safe, don't call free\n", (long)myPointer);
                  printf("\nDon't remove from __mallocArray");
                  printf("\nProblem pointer was at index %d in __mallocArray", indexIntoMallocArray);
                  pA = (char*)1; /* just to give it a value */
                  __mallocArray[indexIntoMallocArray] = NULL;
                }
              else
                {
                  /*
                  ** in list, but we are not tracking for some reason now
                  ** just free the thing
                  */
                  free(myPointer);
                  myPointer = NULL; /* fix up so we don't free it later */
                }
            }
        }
    }

  if ((pA == NULL) && (__isInTrackingMode == TRUE))
    {
      /*
      ** we did not find the pointer in the list, but tracking system was on, so it should have been
      ** is there something we can find out -- overflow, underflow, previous free and alert programmer now
      */
      length = mallocTrack_ValidateAllocationLength(myPointer, &hasOverflow, &hasUnderflow, &hasBeenFreed);

      if (hasBeenFreed == TRUE)
        {
          printf("\nPointer (%#lX)is not listed in __mallocArray, but it was previously and it was freed.\n", (long)myPointer);
          printf("\nSetting length to 50 do debugging dump.");
          length = 50;
        }
      else
        {
          printf("\nPointer (%#lX)is not listed in __mallocArray, but attempt to free it using memory utils in mallocTrack_.\n", (long)myPointer);
          printf("\nSetting length to 50 do debugging dump.");
          length = 50;
        }

      mallocTrack_DebugBuffer(myPointer, length);
    }
  else
    {
      /*
      ** not in list
      ** tracking system not on
      ** just free it
      */
      if (myPointer != NULL)
        {
          free(myPointer);
        }
    }

  return;
}

/*********************************************************************************************
 **  mallocTrack_trackMalloc
 **
 **
 **  track the buffers.
 **
 **   For faster clean up we just load array with malloc results
 *********************************************************************************************/
static void mallocTrack_trackMalloc(void *ptr)
{
  int iterator, iterator2;
  void **myArray;
  int newMaxCalls;

  /* force allocation */
  if (__mallocArray == NULL)
    {
      mallocTrack_initialize();
    }

  for (iterator = 0;iterator < __maxNumOfMallocCalls;iterator++)
    if (__mallocArray[iterator] == NULL)
      break;
  if (iterator < __maxNumOfMallocCalls)
    {
      __mallocArray[iterator] = ptr;
    }
  else
    {
      /* reallocate auto grow tracking system */
      newMaxCalls = 2 * __maxNumOfMallocCalls;
      myArray = (void**)malloc(newMaxCalls * sizeof(void*));
      if (myArray != NULL)
        {
          /* pre clear the new global */
          for (iterator2 = 0;iterator2 < newMaxCalls;iterator2++)
            myArray[iterator2] = NULL;

          memcpy(myArray, __mallocArray, __maxNumOfMallocCalls * sizeof(void*));
          free(__mallocArray);
          __mallocArray = myArray;
          __mallocArray[iterator] = ptr;
          __maxNumOfMallocCalls = newMaxCalls;
        }
      else
        {
          mallocTrack_reportErrorString("\nPROBLEM: Ran out of space in __mallocArray, failed to realloc.");
        }
    }
  return;
}

/*********************************************************************************************
 **  mallocTrack_MallocAndTrack
 **
 **   Allocate and track memory
 *********************************************************************************************/
void *mallocTrack_MallocAndTrack(int size)
{
  void *myPointer;

  /* force allocation */
  if (__mallocArray == NULL)
    {
      mallocTrack_initialize();
    }

  if (__isInTrackingMode == TRUE)
    {
      if ((myPointer = mallocTrack_Malloc(size)) != NULL)
        {
          mallocTrack_trackMalloc(myPointer);
        }
    }
  else
    {
      myPointer = malloc(size);
    }

  return(myPointer);
}

/*********************************************************************************************
 **  mallocTrack_MemoryCheck
 **
 **  Run through all the allocations and check the prefix and suffix
 **  If error print something and return FALSE
 **
 *********************************************************************************************/
Boolean mallocTrack_MemoryCheck(void)
{

  int iterator = 0;
  Boolean isOK = TRUE;

  for (iterator = 0;((__mallocArray != NULL) && (__mallocArray[iterator] != NULL));iterator++)
    {
      if (mallocTrack_ValidateAllocation(__mallocArray[iterator]) == (size_t)0)
        {
          printf("\nOverrun occured in __mallocArray at index %d\n", iterator);
          isOK = FALSE;
        }
    }

  return(isOK);
}

/*********************************************************************************************
 **  isMallocTrack_MallocPointer
 **
 **  Run through all the allocations and check to see if source exists
 **  If error print something and return FALSE
 **
 **
 *********************************************************************************************/
Boolean mallocTrack_isMallocPointer(char *source)
{

  int iterator = 0;
  Boolean isAllocated = FALSE;

  for (iterator = 0;((__mallocArray != NULL) && (__mallocArray[iterator] != NULL));iterator++)
    {
      if (__mallocArray[iterator] == source)
        {
          isAllocated = TRUE;
        }
    }

  return(isAllocated);
}

/*********************************************************************************************
 **  mallocTrack_ValidateAllocationLength
 **
 **  Given a pointer, check it for consistance and return the lenght if OK, 0 otherwise
 **
 **   internal structure looks like this truePointer = (length)AAAA(myPointer)AAAA
 **
 *********************************************************************************************/
static size_t mallocTrack_ValidateAllocationLength(void *myPointer, Boolean *hasOverflow, Boolean *hasUnderflow, Boolean *hasBeenFreed)
{

  int i;
  size_t length = 0;
  size_t *p;
  char *pA;

  *hasOverflow = FALSE;  /* overrun or underrun */
  *hasUnderflow = FALSE;  /* overrun or underrun */
  *hasBeenFreed = FALSE;    /* was freed before */

  /* get the size of the buffer */
  p = (size_t*)((char*)myPointer - (sizeof(size_t) + (kNumberOfTags * sizeof(char))));
  length = *p;

  /* check for underflow */
  pA = (char*)myPointer - (kNumberOfTags * sizeof(char));
  for (i = 0;i < kNumberOfTags;i++)
    {
      if (pA[i] != kAllocationMarker)
        {
          if (pA[i] == kFreedMarker)
            {
              *hasBeenFreed = TRUE;
            }
          else
            {
              *hasUnderflow = TRUE;
            }
        }
    }

  if ((*hasUnderflow == FALSE) && (*hasBeenFreed == FALSE))
    {
      /* check for overflow, but we need good length to do this */
      pA = (char*)myPointer + (length);
      for (i = 0;i < kNumberOfTags;i++)
        {
          if (pA[i] != kAllocationMarker)
            {
              if (pA[i] == kFreedMarker)
                {
                  *hasBeenFreed = TRUE;
                }
              else
                {
                  *hasOverflow = TRUE;
                }
            }
        }
    }
  else
    {
      /*
      ** can not trust the length we are getting, if freed in mid stream,
      ** it is not 100% we will overwrite the markers, but overwrite the length
      */
      length = 0;
    }

  return(length);
}

/*********************************************************************************************
 **  mallocTrack_ValidateAllocation
 **
 **  Given a pointer, check it for consistance and return the lenght if OK, 0 otherwise
 **
 **   internal structure looks like this truePointer = (length)AAAA(myPointer)AAAA
 **
 *********************************************************************************************/
static size_t mallocTrack_ValidateAllocation(void *myPointer)
{
  Boolean hasOverflow;  /* overrun or underrun */
  Boolean hasUnderflow;  /* overrun or underrun */
  Boolean hasBeenFreed;    /* was freed before */
  size_t length = 0;
  char *pA;

  length = mallocTrack_ValidateAllocationLength(myPointer, &hasOverflow, &hasUnderflow, &hasBeenFreed);

  if (hasUnderflow == TRUE)
    {
      printf("\n\nBUFFER AT %#lX HAS UNDERFLOW PROBLEM.\n", (long)myPointer);
      if (length < 1)
        {
          printf("\nLength data may be bad, setting to 50 bytes for dump");
          printf("\nMoving back pointer to get underflow by 8");
          length = 50;
        }
      pA = (char *)myPointer;
      mallocTrack_DebugBuffer(pA - 8, length);
      length = 0;
    }

  if (hasOverflow == TRUE)
    {
      printf("\n\nBUFFER AT %#lX HAS OVERFLOW PROBLEM.\n", (long)myPointer);
      mallocTrack_DebugBuffer(myPointer, length);
      length = 0;
    }

  if (hasBeenFreed == TRUE)
    {
      printf("\n\nBUFFER AT %#lX HAS BEEN FREED.\n", (long)myPointer);
      mallocTrack_DebugBuffer(myPointer, length);
      length = 0;
    }

  return(length);
}

/*********************************************************************************************
 **  mallocTrack_DebugBuffer
 **
 **  Given a pointer and length, dump the buffer in hex and ascii to stdout
 **
 *********************************************************************************************/
void mallocTrack_DebugBuffer(void *myPointer, int size)
{

#define kDumpSize 16
#define kChunkSize 4

#define kHexSize (2*kDumpSize)+((2*kDumpSize)/kChunkSize)+100
#define kAsciiSize kDumpSize+(kDumpSize/kChunkSize)+100

  char hexDump[kHexSize],
  asciiDump[kAsciiSize],
  asciiChar[8],
  hexChar[8],
  bufferAddress[16];
  char *buffer = (char*)myPointer;
  size_t index = 0;
  int count = 0;

  printf("\nPointer being dumped is located at: %#lX", (long)myPointer);
  printf("\nLength of allocation was: %ld", (long)size);
  printf("\n\n%-10s\t%-36s\t%-19s", "Pointer", "Hex values", "ASCII values");
  printf("\n\n%-10.10s\t%-36.36s\t%-19.19s", "------------------", "-----------------------------------------", "----------------------------");

  for (index = 0;index < size;index++)
    {

      if (count == 0)
        {
          memset(hexDump, '\000', kHexSize);
          memset(asciiDump, '\000', kAsciiSize);
          sprintf(bufferAddress, "%#4lX", (long unsigned)(buffer + index));
        }

      /* make printable */
      sprintf(hexChar, "%1X", (buffer[index] & 0xFF));
      if (buffer[index] < 32 || buffer[index] > 126)
        {
          sprintf(asciiChar, "%c", '.');
        }
      else
        {
          sprintf(asciiChar, "%c", (int)buffer[index]);
        }

      /* add to dump values */
      if (strlen(hexChar) < 2)
        {
          /* no preceding 0 on 0-9 values */
          strcat(hexDump, "0");
        }
      strcat(hexDump, hexChar);
      strcat(asciiDump, asciiChar);

      if (((count + 1) > 3) && ((count + 1) % kChunkSize == 0) && ((count + 1) != kDumpSize))
        {
          /* add some spaces for readability */
          strcat(hexDump, " ");
          strcat(asciiDump, " ");
        }

      if (count == (kDumpSize - 1))
        {
          /* dump out the buffer and then reset */
          printf("\n%s\t%-36s\t%s", bufferAddress, hexDump, asciiDump);
          count = 0;
        }
      else
        {
          count++;
        }
    }

  if (count > 0)
    {
      /* dump out the last buffer and then reset */
      printf("\n%s\t%-36s\t%s", bufferAddress, hexDump, asciiDump);
    }

  return;
}
