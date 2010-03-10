// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLDefaultStyles.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/10 12:26:12 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLDEFAULT_STYLES_H__
#define CLDEFAULT_STYLES_H__

#include <copasi/copasi.h>

#include <copasi/utilities/CCopasiVector.h>
#include <copasi/layout/CLGlobalRenderInformation.h>

extern CCopasiVector<CLGlobalRenderInformation>* DEFAULT_STYLES;

/**
 * This method returns a global render information list that contains the default styles
 * which are built into the renderer.
 */
CCopasiVector<CLGlobalRenderInformation>* getDefaultStyles();

/**
 * This method returns the number of global styles.
 */
unsigned int getNumDefaultStyles();

/**
 * This method returns the default render information object with
 * the requested index. If the index isinvalid, NULL is returned.
 */
CLGlobalRenderInformation* getDefaultStyle(unsigned int index);

/**
 * This method is used to initialize the default styles.
 * Normally this does not need to be called since it is called automatically.
 * The method returns a point to a ListOfGlobalRenderInformation object.
 * The caller is responsible for freeing the memory associated with the list.
 */
CCopasiVector<CLGlobalRenderInformation>* loadDefaultStyles();

#endif // CLDEFAULT_STYLES_H__
