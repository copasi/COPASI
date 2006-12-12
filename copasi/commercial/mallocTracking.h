/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commercial/Attic/mallocTracking.h,v $
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
 **  mallocTracking.h
 **
 **   This file contains all the headers necessary to
 **   use mallocTracking.c
 **
 **  Version History:
 **   1.0   Release   June 11, 2001   ACG@kagi.com
 **     -- code yanked from ACGFramework.h
 **
 **  mallocTracking.h is  Copyright(c) 2002 Kagi
 **  All Rights Reserved.
 **
 **  Permission is granted to use this code module for development
 **  and deployment of a Kagi ACG free of charge as long as Kagi
 **  processes your payments for those application(s) .
 **  No warranty is made as to the suitability
 **  of mallocTracking.h to your application or even that mallocTracking.h is bug or
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

/*
 ** Memory Mgmt. Routines that use under-flow & over-flow detection
 */

#if (TRUE==1)
#define __NEED_BOOLEAN__ 0
#else
#define __NEED_BOOLEAN__ 1
#endif

#if (__NEED_BOOLEAN__ == 1)
/* if you use this and your system has not defined Boolean, then you need to set this up */
typedef int Boolean;
#define TRUE 1
#define FALSE 0
#endif

#define  kMaxMallocCallsStart  100  /* just a starting point, auto adjust if you need more */
#define  kAllocationMarker   'Y'
#define  kFreedMarker    'Z'
#define  kNumberOfTags    4

typedef void (*MALLOCTRACK_ERROR_FUNC)(char * stringToPrint);

void mallocTrack_Free(void *myPointer);
Boolean mallocTrack_MemoryCheck(void);
void mallocTrack_DebugBuffer(void *myPointer, int size);
void *mallocTrack_MallocAndTrack(int size);
Boolean mallocTrack_isMallocPointer(char *source);

/* error handling */
MALLOCTRACK_ERROR_FUNC mallocTrack_installErrorStingCallback(MALLOCTRACK_ERROR_FUNC newHandler);

/* init calls */
Boolean mallocTrack_initialize(void);
Boolean mallocTrack_reInitialize(void);
void mallocTrack_resume(void);
void mallocTrack_suspend(void);

#if (kREALMALLOCTRACK != 1)
/* in user .c files, replace malloc, free, realloc with these calls */

#define malloc(x) mallocTrack_MallocAndTrack(x)
#define free(x)  mallocTrack_Free(x)

#endif
