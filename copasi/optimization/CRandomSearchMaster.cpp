/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/CRandomSearchMaster.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:25:24 $
   End CVS Header */

/***************************************************************************
                    CRandomSearchMaster.cpp  -  Random Optimizer
                       -------------------
 
Programmer           : Rohan Luktuke
email                : rluktuke@vt.edu
 ***************************************************************************/

/***************************************************************************
 * This is the implementation of the Random Algorithm for Optimization.  The
 * class is inherited from the COptAlgorithm class
 ***************************************************************************/

#include "copasi.h"
#include "COptMethod.h"

CRandomSearchMaster::CRandomSearchMaster():
    COptMethod()
{}

CRandomSearchMaster::CRandomSearchMaster(const CRandomSearchMaster & src):
    COptMethod(src)
{}

/**
 * Destructor
 */
CRandomSearchMaster::~CRandomSearchMaster(){}

/**
 * Optimizer Function
 * Returns: nothing
 */
C_INT32 CRandomSearchMaster::optimise()
{return 0;}
