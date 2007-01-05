/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commercial/Attic/TestDriver.c,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/12/12 21:22:08 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*
 *  Copyright(c) 2004  Kagi.  All Rights Reserved.
 * Permission is granted to use this code module for development of decoding algorithm
 * for the generic acg.No warranty is made as to the suitability to your application
 *
 *     BECAUSE THE REFERENCE IS LICENSED FREE OF CHARGE, THERE IS NO
 *     WARRANTY FOR THE REFERENCE, TO THE EXTENT PERMITTED BY APPLICABLE LAW.
 *     EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR
 *     OTHER PARTIES PROVIDE THE REFERENCE "AS IS" WITHOUT WARRANTY OF ANY
 *     KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
 *     IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *     PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE
 *     REFERENCE IS WITH YOU.  SHOULD THE REFERENCE PROVE DEFECTIVE, YOU ASSUME
 *     THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
 *     If you make any corrections to the basic reference or have suggestions
 *     please send them to acg@kagi.com so other may benefit.
 *
 *  If you make any corrections to the basic module or have suggestions
 *   please send them to acg@kagi.com so others may benefit
 *  VERSION HISTORY
 *      Alpha   3/1/2004
 *      1.0     Implementaion of the corrections suggested by Ty.
 *       1.0.1     Fixed the bugs and suggestion received from suppliers
 *    1.0.2     8/25/2004 Changed stncmp to stcmp and added extern declarations. Suggestions by
 *     Yotam Rosenthal
 *
 **/

/**
 * This is a test driver to demonstrate how to use decode algorithm
 * implementation.
 * 1. First decode the registration code, to get the user seed on which it was * *    based
 * 2. Second use the 'user name/ email/hotsyncid' provided for the application
 *    to create the user seed.
 * Compare the user seed in step 1 and 2 this should match.
 *
 * To run in debug mode uncomment #define DEBUG in 'GenericDecode.h'
 *
 * With Borland compiler on windows use
 * c:\WORK_DIR>  bcc32 GenericDecode.c BigInt.c  TestDriver.c --------> Borland
 * With gcc on linux use
 *  $ gcc GenericDecode.c BigInt.c  TestDriver.c -o GenericDecode
 * To execute the program
 * EXECUTE
 * C:\WORK_DIR> GenericDecode
 * $ ./GenericDecode
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/** Staring point of the program */
int main()
{
  extern decodeGenericRegCode(char* , char*);
  extern void freememory(void);
  extern char* getUserSeed(void);
  extern char* getConstant(void);
  extern char* getSequenceNumber(void);
  extern char* getDate(void);
  extern char* getDebugMessage(void);
  extern void setUserName(char*);
  extern void setUserEmail(char*);
  extern void createUserSeed(void);
  extern char *getCreatedUserSeed(void);
  int value, result;

  char* config = "SUPPLIERID:rupali_test%E:1%N:5%H:1%COMBO:nn%SDLGTH:15%CONSTLGTH:2%CONSTVAL:Q2%SEQL:2%ALTTEXT:Contact abc@supplier.com to obtain your registration code%SCRMBL:U2,,U3,,U5,,U7,,U10,,U9,,U11,,U12,,U4,,C0,,U6,,U13,,U14,,D1,,U1,,S1,,D3,,D2,,C1,,U8,,U0,,D0,,S0,,%ASCDIG:3%MATH:48S,,48S,,48S,,48S,,48S,,909A,,909A,,909A,,909A,,909A,,10M,,10M,,10M,,48S,,48S,,48S,,48S,,48S,,R,,R,,R,,48S,,48S,,%BASE:42%BASEMAP:TmeMPGCrwxyaUXidbFngQYkHzKutDcWLRApjJNfqEh%REGFRMT:PROD-^#####-#####-#####-#####-#####-#####-#####-#####-##";
  char* regCode = "PROD-LwbAmM-HuDDR-urLiH-nuzYf-NxPHj-zkptA-GDuNF-DeTUH-Gn";

#ifdef DEBUG
  printf("Decoding the registration code %s \n", regCode);
  printf("for the configuration %s\n", confi);
#endif
  // first decode the registration, to get the user seed from which it was
  // created
  value = decodeGenericRegCode(config , regCode);
  if (value == 0)
    {
      printf("\nThe seed is %s\n", getUserSeed());
      printf("The sequence is %s\n", getSequenceNumber());
      printf("The date is %s\n", getDate());
      printf("The constant is %s\n", getConstant());
      printf("The debug messages are %s\n" , getDebugMessage());
    }

  //now use the name /email/hotsync id that is provided to the
  //application to create the user seed. This should match
  //the one obtained by decoding the registration code.
  //USE the setUserName() for the hotsyncId

  setUserName("tanishka");
  createUserSeed();
  printf("User Seed : %s \n", getCreatedUserSeed());
  result = strcmp(getUserSeed() , getCreatedUserSeed());
  if (result == 0)
    {
      printf("The registration code is verified.");
    }
  atexit(freememory);
  return value;
}
