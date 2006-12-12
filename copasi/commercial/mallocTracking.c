/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commercial/Attic/mallocTracking.c,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/12/12 21:22:08 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**** **  mallocTracking.c**  **   This file contains all the code necessary to **   track all uses of malloc and free to see if you have:**    1).  extra free calls**    2).  missing free calls**    3).  buffer over runs**    4).  buffer underruns******  Version History:**   1.0   Release   June 11, 2001   ACG@kagi.com**     -- code yanked from ACGFramework.c**  **  mallocTracking.c is  Copyright(c) 2002 Kagi**  All Rights Reserved.****  Permission is granted to use this code module for development **  and deployment of a Kagi ACG free of charge as long as Kagi **  processes your payments for those application(s) .  **  No warranty is made as to the suitability**  of mallocTracking.c to your application or even that mallocTracking.c is bug or **  error free.******  BECAUSE THE MODULE IS LICENSED FREE OF CHARGE, THERE IS NO **  WARRANTY FOR THE MODULE, TO THE EXTENT PERMITTED BY APPLICABLE LAW.**  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR**  OTHER PARTIES PROVIDE THE MODULE "AS IS" WITHOUT WARRANTY OF ANY**  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE**  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR**  PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE**  MODULE IS WITH YOU.  SHOULD THE MODULE PROVE DEFECTIVE, YOU ASSUME**  THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.****  If you make any corrections to the basic module or have suggestions**   please send them to ACG@kagi.com so others may benefit**  */#include <stdlib.h>#include <stdio.h>#include <ctype.h>#include <string.h>#define  kREALMALLOCTRACK 1  /* tells the header file not to replace malloc with mallocTrack routines */#include "mallocTracking.h"static void *mallocTrack_Malloc(size_t size);static void mallocTrack_trackMalloc(void *ptr);static void mallocTrack_atExitTime(void);static void mallocTrack_defaultErrorStringRoutine(char *stringToPrint);static void mallocTrack_reportErrorString(char *st
