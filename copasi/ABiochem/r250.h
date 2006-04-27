/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/ABiochem/r250.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:33:58 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*** Function prototypes for R250 random number generator, by W. L. Maier  ***/
unsigned int r250(void);
unsigned int r250n(unsigned n);
double dr250(void);
void r250_init(int seed);
