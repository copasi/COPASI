/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/ABiochem/erdos.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:19:28 $
   End CVS Header */

/**
 *  Erdos
 *
 *  Program to generate random gene networks following an 
 *  Erdos Renyi topology
 *  
 */

#include "copasi.h"
#include <stdio.h>
#include "model/model.h"
#include "ABiochem/CGene.h"

void Erdos(C_INT32 n, C_INT32 k, C_FLOAT64 p, CCopasiVector < CGene > &gene, char *comments);
