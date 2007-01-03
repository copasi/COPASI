/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commercial/Attic/FlexibleInt.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2007/01/03 14:16:49 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef LICENSE_FlexibleInt
#define LICENSE_FlexibleInt

#ifdef  __cplusplus
extern "C"
  {
#endif

    struct FLEXIBLE_INTEGER
      {
        int * pVal;
        unsigned int len;
      };

    typedef struct FLEXIBLE_INTEGER FlexibleInt;

    void FIprint(FlexibleInt * pX);

    void FIinit(FlexibleInt * pX, unsigned int len);

    void FIdestroy(FlexibleInt * pX);

    void FIcopy(FlexibleInt * pSrc, FlexibleInt * pCopy);

    void FIcarryOver(FlexibleInt * pResult, int base);

    void FIadd(FlexibleInt * pX, FlexibleInt * pY, FlexibleInt * pResult, int base);

    void FIminus(FlexibleInt * pX, FlexibleInt * pY, FlexibleInt * pResult, int base);

    void mFIultiply(FlexibleInt * pX, FlexibleInt * pY, FlexibleInt * pResult, int base);

    void FIpower(FlexibleInt *pX, unsigned int power, FlexibleInt *pResult, int base);

    int FIcompare(FlexibleInt * pX, FlexibleInt * pY);

#ifdef  __cplusplus
  }
#endif

#endif // LICENSE_FlexibleInt
