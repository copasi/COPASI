/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/ABiochem/r250.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:19:28 $
   End CVS Header */

/*** Function prototypes for R250 random number generator, by W. L. Maier  ***/
unsigned int r250(void);
unsigned int r250n(unsigned n);
double dr250(void);
void r250_init(int seed);
