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
