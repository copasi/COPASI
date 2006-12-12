/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commercial/Attic/BigInt.c,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/12/12 21:28:29 $
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
 *  If you make any corrections to the basic module or have suggestions
 *   please send them to acg@kagi.com so others may benefit
 *  VERSION HISTORY
 *      Alpha   3/1/2004
 *      1.0     Implementaion of the corrections sugested by Ty.
 *         1.0.1   Made memory leak fixes provided by Al Evans 2/14/2005
 *
 **/

//Implementaion of functions used for performing
//arithmetic operations on large integers.
#define DEBUG

#include "BigInt.h"

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int newlength = 0;
int resultLen = 1;
extern int CHAR_TYPE;
extern int INT_TYPE;
extern char debugBuffer[200];
extern int debugBufferCount;
extern void setDebugMessage(int size, char *);
extern void* allocateMemory(int size, int type);

/*Returns the value of the first argument raised to
the power of the second argument.
If the second argument is zero, then the result is 1.
If the second argument is 1, then the result is the same
as the first argument.
base - the base
index - exponent
 */
int * power(char* base, int index)
{
  int *result , *newResult ; // stores the result of base^index
  int x;
  result = (int *)allocateMemory(1 , INT_TYPE);
  *result = 1;
  //intialize variables
  newlength = 1;
  resultLen = 1;

#ifdef DEBUG
  debugBufferCount = sprintf (debugBuffer, "Computing power for %s^%d\n", base, index);
  setDebugMessage(debugBufferCount, debugBuffer);
#endif
  for (x = 0 ; x < index;++x)
    {
      newResult = multiply(result, resultLen, base);
      free(result);
      result = newResult;
      resultLen = newlength;
    }
  return result;
}

/* This functions returns a integer array whose value is
 multiplicand * baseNumb.
 multiplicand - the number that is multiplied by the multiplier
 baseNumb - the number by which a multiplicand is multiplied
 size - number of digits in the multiplicand
 */

int * multiply(int* multiplicand, int size, char* baseNumb)
{
  int x, i;
  int multiplier = atoi(baseNumb);
  int *result = (int *)allocateMemory(1 , INT_TYPE); //newlength
  int *mresult, *newResult;
  int *multiplicand2 = (int *)allocateMemory(size , INT_TYPE);

  int len = 1;
  *result = 0;
  //result of multiplying with 0 is 0
  if (multiplier == 0)
    {
      *result = 0;
      newlength = 1;
      // Free local variable --AE 02/05
      free(multiplicand2);
      return result;
    }
  //copy of the  multiplicand
  for (i = 0 ; i < size ; i++)
    {
      *(multiplicand2 + i) = *(multiplicand + i);
    }
#ifdef DEBUG
  debugBufferCount = sprintf (debugBuffer, "\tMultiplying  ");
  setDebugMessage(debugBufferCount, debugBuffer);
  for (i = 0 ; i < newlength ; i++)
    {
      debugBufferCount = sprintf (debugBuffer, "%d", *(multiplicand + i));
      setDebugMessage(debugBufferCount, debugBuffer);
    }
  debugBufferCount = sprintf (debugBuffer, " * %d: \t", multiplier);
  setDebugMessage(debugBufferCount, debugBuffer);
#endif
  //add the multiplicand multiplier times
  for (x = 0 ; x < multiplier ; ++x)
    {
#ifdef DEBUG
      debugBufferCount = sprintf (debugBuffer, "Adding ");
      setDebugMessage(debugBufferCount, debugBuffer);
      for (i = 0 ; i < len ; i++)
        {
          debugBufferCount = sprintf (debugBuffer, "%d", *(result + i));
          setDebugMessage(debugBufferCount, debugBuffer);
        }
      debugBufferCount = sprintf (debugBuffer, " + ", *(result + i));
      setDebugMessage(debugBufferCount, debugBuffer);
      for (i = 0 ; i < size ; i++)
        {
          debugBufferCount = sprintf (debugBuffer, "%d", *(multiplicand2 + i));
          setDebugMessage(debugBufferCount, debugBuffer);
        }
      debugBufferCount = sprintf (debugBuffer, "\n");
      setDebugMessage(debugBufferCount, debugBuffer);
#endif
      newResult = add(result, len, multiplicand2, size);
      free(result);
      result = newResult;
      //get the new length of the result
      len = newlength;
    }
#ifdef DEBUG
  debugBufferCount = sprintf (debugBuffer, "Result =");
  setDebugMessage(debugBufferCount, debugBuffer);
  for (i = 0 ; i < newlength ; i++)
    {
      debugBufferCount = sprintf (debugBuffer, "%d ", *(result + i));
      setDebugMessage(debugBufferCount, debugBuffer);
    }
  debugBufferCount = sprintf (debugBuffer, "\n");
  setDebugMessage(debugBufferCount, debugBuffer);
#endif
  //allocate memory and copy the result
  mresult = (int *)allocateMemory(newlength, INT_TYPE);
  for (i = 0; i < (newlength) ;i++)
    {
      *(mresult + i) = *(result + i);
    }
  free(result);
  free(multiplicand2);
  return mresult;
}

/**This function adds two numbers and returns the result as an
integer array. Add number stored in operand1 to number stored
in operand2 and resturn the result
 */
int * add(int operand1[] , int l1, int operand2[], int l2)
{

  int *op1;
  int *op2;
  int i, k, j, x;
  int *result;
  int carry = 0; //carry produced by adding two digits
  int sum ; //result of adding two digits

  //determine which number has more digits and accordingle designate
  //it as the the op1, the other number is op2
  // assign to k the last index of the larger of the
  // two operands.
  if (l1 >= l2)
    {
      k = l1 - 1;
      j = l2 - 1;
      op1 = (int *)allocateMemory(l1, INT_TYPE);
      op2 = (int *)allocateMemory(l2, INT_TYPE);
      for (i = 0 ; i < l1 ; i++)
        {
          *(op1 + i) = *(operand1 + i);
        }
      for (i = 0 ; i < l2 ; i++)
        {
          *(op2 + i) = *(operand2 + i);
        }
      newlength = l1;
    }
  else
    {
      k = l2 - 1;
      j = l1 - 1;
      op1 = (int *)allocateMemory(l2, INT_TYPE);
      op2 = (int *)allocateMemory(l1, INT_TYPE);
      for (i = 0 ; i < l2 ; i++)
        {
          *(op1 + i) = *(operand2 + i);
        }
      for (i = 0 ; i < l1 ; i++)
        {
          *(op2 + i) = *(operand1 + i);
        }
      newlength = l2;
      i = l1;
      l1 = l2;
      l2 = i;
    }
  // repeat the loop until k is >= "0".
  // The other operand is smaller.
  for (i = k ; i >= 0 ; --i)
    {
      //if the inner operand has digits
      //then use them to find the sum.
      if (j >= 0)
        {
          sum = *(op1 + i) + *(op2 + j) + carry;
        }
      else
        {
          // there are no digits in the smaller number
          // so the sum is obtained by adding the digit of the
          // larger number and the carry if it is greater than zero.
          if (carry > 0)
            {
              sum = *(op1 + i) + carry;
            }
          else
            sum = *(op1 + i);
        }
      //reset the carry.
      carry = 0;
      if (sum > 9)
        {
          // seperate the unit and tens digit.
          *(op1 + i) = sum % 10;
          carry = sum / 10;
        }
      else
        *(op1 + i) = sum;
      // printf("%d ",*(op1+i));
      --j;
    } //for
  //if we run out of digits and there is a carry,then
  // we have to increase the number of digits.
  if (carry != 0)
    {
      //l1 = l1+1;
      // Need one more digit --AE 02/05
      result = (int *)allocateMemory(l1 + 1, INT_TYPE);
      *(result) = carry;
      //now copy the remaining number into the new array
      for (x = 0; x < (l1) ;x++)
        *(result + x + 1) = *(op1 + x);

      l1 = l1 + 1;
      newlength = l1;
      free(op2);
      free(op1);
    }
  else
    {
      // Double assignment?? --AE 02/05
      //result = (int *)allocateMemory(l1, INT_TYPE);
      result = op1;
      free(op2);
    }
#ifdef DEBUG
  for (i = 0 ; i < newlength ; i++)
    {
      debugBufferCount = sprintf (debugBuffer, "%d", *(result + i));
      setDebugMessage(debugBufferCount, debugBuffer);
    }
  debugBufferCount = sprintf (debugBuffer, "\n\n");
  setDebugMessage(debugBufferCount, debugBuffer);
#endif
  return result;
}

/**
 This function returns the number of digits in the number
 obtained after calculating base ^ exponent
 */
int getResultSize()
{
  return resultLen;
}

/**
 This method returns the number of digits in the number
 obtained after adding two numbers or multiplying two numbers
 */
int getResultLength()
{
  return newlength;
}
