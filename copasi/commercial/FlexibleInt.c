/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commercial/Attic/FlexibleInt.c,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2007/01/03 14:16:49 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <malloc.h>
#include <memory.h>
#include <stdio.h>
#include <math.h>

#include "FlexibleInt.h"

#ifndef NULL
# define NULL 0x00
#endif

void FIprint(FlexibleInt * pX)
{
  int i = pX->len - 1;;

  for (; i >= 0; i--)
    printf("%d,", pX->pVal[i]);

  printf("\n");
}

void FIinit(FlexibleInt * pX, unsigned int len)
{
  pX->len = len;

  if (pX->len != 0)
    {
      pX->pVal = (int *) malloc(pX->len * sizeof(int));
      memset(pX->pVal, 0, pX->len * sizeof(int));
    }
  else
    pX->pVal = NULL;
}

void FIdestroy(FlexibleInt * pX)
{
  if (pX->pVal != NULL && pX->len != 0)
    {
      free(pX->pVal);
      pX->pVal = NULL;
      pX->len = 0;
    }
}

void FIcopy(FlexibleInt * pSrc, FlexibleInt * pCopy)
{
  if (pSrc->len != pCopy->len)
    {
      FIdestroy(pCopy);
      FIinit(pCopy, pSrc->len);
    }

  memcpy(pCopy->pVal, pSrc->pVal, pSrc->len * sizeof(int));
}

void FIcarryOver(FlexibleInt * pX, int base)
{
  int * pA = pX->pVal;
  int * pEndA = pA + pX->len;
  unsigned int lenA = 0;

  unsigned int count = 0;

  //  printf("FIcarryOver (in): ");
  //  FIprint(pX);

  // determine needed digits
  while (pA != pEndA)
    {
      count++;
      if (*pA++ != 0)
        lenA = count;
    }

  pA = pX->pVal;

  if (lenA > 0)
    pEndA = pA + lenA - 1;
  else
    pEndA = pA;

  for (; pA != pEndA; ++pA)
    {
      *(pA + 1) += *pA / base;
      *pA %= base;

      if (*pA > 0 && *pEndA < 0)
        {
          *(pA + 1) += 1;
          *pA -= base;
        }
      else if (*pA < 0 && *pEndA > 0)
        {
          *(pA + 1) -= 1;
          *pA += base;
        }
    }

  while (abs(*pEndA) >= base)
    {
      if (lenA == pX->len) // we need more digits
        {
          pX->len++;
          pA = pX->pVal;
          pX->pVal = (int *) malloc(pX->len * sizeof(int));
          memcpy(pX->pVal, pA, lenA * sizeof(int));
          // free(pA);
          pEndA = pX->pVal + lenA - 1;
        }

      *(pEndA + 1) = *pEndA / base;
      *pEndA %= base;

      lenA++;
      pEndA++;
    }

  //  printf("FIcarryOver (out): ");
  //  FIprint(pX);
}

void FIadd(FlexibleInt * pX, FlexibleInt * pY, FlexibleInt * pResult, int base)
{
  int * pA = pX->pVal;
  int * pEndA = pA + pX->len;
  unsigned int lenA = 0;

  int * pB = pY->pVal;
  int * pEndB = pB + pY->len;
  unsigned int lenB = 0;

  int * pSum;
  int * pEndSum;
  unsigned int count = 0;

  //  printf("FIadd (in): ");
  //  FIprint(pX);
  //  FIprint(pY);

  // determine needed digits
  while (pA != pEndA)
    {
      count++;
      if (*pA++ != 0)
        lenA = count;
    }

  pA = pX->pVal;
  pEndA = pA + lenA;

  count = 0;
  while (pB != pEndB)
    {
      count++;
      if (*pB++ != 0)
        lenB = count;
    }

  pB = pY->pVal;
  pEndB = pB + lenB;

  if (lenA > lenB)
    FIinit(pResult, lenA + 1);
  else
    FIinit(pResult, lenB + 1);

  pSum = pResult->pVal;
  pEndSum = pSum + pResult->len;

  for (; pA != pEndA && pB != pEndB; ++pA, ++pB, ++pSum)
    *pSum = *pA + *pB;

  for (; pA != pEndA; ++pA, ++pSum)
    *pSum = *pA;

  for (; pB != pEndB; ++pB, ++pSum)
    *pSum = *pB;

  FIcarryOver(pResult, base);

  //  printf("FIadd (out): ");
  //  FIprint(pResult);
}

void FIminus(FlexibleInt * pX, FlexibleInt * pY, FlexibleInt * pResult, int base)
{
  int * pA = pX->pVal;
  int * pEndA = pA + pX->len;
  unsigned int lenA = 0;

  int * pB = pY->pVal;
  int * pEndB = pB + pY->len;
  unsigned int lenB = 0;

  int * pDiff;
  int * pEndDiff;
  unsigned int count = 0;

  //  printf("FIminus (in): ");
  //  FIprint(pX);
  //  FIprint(pY);

  // determine needed digits
  while (pA != pEndA)
    {
      count++;
      if (*pA++ != 0)
        lenA = count;
    }

  pA = pX->pVal;
  pEndA = pA + lenA;

  count = 0;
  while (pB != pEndB)
    {
      count++;
      if (*pB++ != 0)
        lenB = count;
    }

  pB = pY->pVal;
  pEndB = pB + lenB;

  if (lenA > lenB)
    FIinit(pResult, lenA + 1);
  else
    FIinit(pResult, lenB + 1);

  pDiff = pResult->pVal;
  pEndDiff = pDiff + pResult->len;

  for (; pA != pEndA && pB != pEndB; ++pA, ++pB, ++pDiff)
    *pDiff = *pA - *pB;

  for (; pA != pEndA; ++pA, ++pDiff)
    *pDiff = *pA;

  for (; pB != pEndB; ++pB, ++pDiff)
    *pDiff = - *pB;

  FIcarryOver(pResult, base);

  //  printf("FIminus (out): ");
  //  FIprint(pResult);
}

void FImultiply(FlexibleInt * pX, FlexibleInt * pY, FlexibleInt * pResult, int base)
{
  int * pA = pX->pVal;
  int * pEndA = pA + pX->len;
  unsigned int lenA = 0;

  int * pB = pY->pVal;
  int * pEndB = pB + pY->len;
  unsigned int lenB = 0;

  FlexibleInt Product;

  FlexibleInt Tmp;
  int * pTmp;
  int * pEndTmp;

  unsigned int count = 0;

  //  printf("FImultiply (in): ");
  //  FIprint(pX);
  //  FIprint(pY);

  // determine needed digits
  while (pA != pEndA)
    {
      count++;
      if (*pA++ != 0)
        lenA = count;
    }
  pEndA = pX->pVal + lenA;

  count = 0;
  while (pB != pEndB)
    {
      count++;
      if (*pB++ != 0)
        lenB = count;
    }
  pEndB = pY->pVal + lenB;

  FIinit(&Product, lenA + lenB + 1);

  FIinit(&Tmp, Product.len);
  pEndTmp = Tmp.pVal + Tmp.len;

  for (count = 0, pA = pX->pVal; pA != pEndA; pA++, count++)
    {
      memset(Tmp.pVal, 0, Tmp.len * sizeof(int));
      pTmp = Tmp.pVal + count;

      if (count != 0)
        FIcopy(pResult, &Product);

      for (pB = pY->pVal; pB != pEndB; ++pB, ++pTmp)
        *pTmp = *pA * *pB; // This works as long as base < sqrt(LONG_MAX)

      FIcarryOver(&Tmp, base);

      FIadd(&Tmp, &Product, pResult, base);
    }

  //  printf("FImultiply (out): ");
  //  FIprint(pResult);
}

void FIpower(FlexibleInt *pX, unsigned int power, FlexibleInt *pResult, int base)
{
  FlexibleInt Power;
  FIinit(&Power, 0);

  FIdestroy(pResult);
  FIinit(pResult, 1);

  //  printf("FIpower (in): %d, ", power);
  //  FIprint(pX);

  // Handle case X == 0
  if (FIcompare(pX, &Power) == 0 && power != 0)
    return;

  *pResult->pVal = 1;
  while (power)
    {
      FIcopy(pResult, &Power);
      FImultiply(pX, &Power, pResult, base);
      power--;
    }

  //  printf("FIpower (out): ");
  //  FIprint(pResult);
}

// This operates correctly on positive and negative numbers;
int FIcompare(FlexibleInt * pX, FlexibleInt * pY)
{
  int * pA = pX->pVal;
  int * pEndA = pA + pX->len;
  int lenA = 0;

  int * pB = pY->pVal;
  int * pEndB = pB + pY->len;
  int lenB = 0;

  int count = 0;

  // determine needed digits
  while (pA != pEndA)
    {
      count++;
      if (*pA++ != 0)
        lenA = count;
    }

  count = 0;
  while (pB != pEndB)
    {
      count++;
      if (*pB++ != 0)
        lenB = count;
    }

  if (lenA < lenB)
    {
      // |Y| > |X|
      if (*pY->pVal < 0)
        return 1;  // Y < 0
      else
        return - 1; // Y > 0
    }

  if (lenA > lenB)
    {
      // |X| > |Y|
      if (*pX->pVal < 0)
        return - 1; // X < 0
      else
        return 1;  // X > 0
    }

  if (lenA == 0)
    return 0;

  pA = pX->pVal;
  pEndA = pA + lenA - 1;

  pB = pY->pVal;
  pEndB = pB + lenB - 1;

  while (pA <= pEndA)
    {
      if (*pEndA < *pEndB)
        return - 1;
      if (*pEndA > *pEndB)
        return 1;

      pEndA--;
      pEndB--;
    }

  return 0;
}
