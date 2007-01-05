/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commercial/Attic/BigInt.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/12/15 16:21:08 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
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
  *      VERSION HISTORY
  *      Alpha   3/1/2004
  *      1.0     Implementaion of the corrections sugested by Ty.
  *
  */
/**
 * BigInt provides an implementation of operations for BigInteger.The
 * operations provided are
 * power() , multiply() and add.
 */

#ifndef BigInt_H
#define BigInt_H

#ifdef  __cplusplus
extern "C"
  {
#endif

    /**
     * Returns the value of the first argument raised to the power of the second argument.
     * @param base : the number whose power is to be calculated
     * @param index: exponent to which the base is to be raised.
     */
    int * power(char *base, int index);
    /**
     * Returns the value of the first argument multiplied by the
     * multiplier
     * @param multiplicand : the number to be multiplied
     * @param size: the number of digit s n the multiplicand
     * @param multiplier: the number to multiply with.
     */
    int * multiply(int *multiplicand, int size, char *multiplier);

    /**
     * Converts a string to an integer array
     * @param number : string representation of the number
     * @returns the pointer to the resultant array.
     */
    int *toArray(char * number);

    /**
     * Adds to two numbers
     * @param number1 the number to which to add another number
     * @param number2 the number to be added.
     * @size1 the digits in number1
     * @size2 the digits in number2
     * @return the result of adding number1 and number2
     */
    int * add(int number1[], int size1, int number2 [], int size2);
    /** Prints the specified integer array to std out
     * @param number the number to be printed
     * @size the digits in number1
     */

    void print(int number[], int size);
    /**
      * Returns the size of  the number after addition
      */
    int getResultSize(void);

    /**
     * Returns the size of the number after multiplication.
     */
    int getResultLength(void);

#ifdef  __cplusplus
  }
#endif

#endif
