/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/ABiochem/r250.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:43 $
   End CVS Header */

/*** Function prototypes for R250 random number generator, by W. L. Maier  ***/
unsigned int r250(void);
unsigned int r250n(unsigned n);
double dr250(void);
void r250_init(int seed);
