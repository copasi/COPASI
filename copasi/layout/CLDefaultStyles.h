// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLDEFAULT_STYLES_H__
#define CLDEFAULT_STYLES_H__

#include "copasi/copasi.h"

#include "copasi/core/CDataVector.h"
#include "copasi/layout/CLGlobalRenderInformation.h"

extern CDataVector<CLGlobalRenderInformation>* DEFAULT_STYLES;

/**
 * This method returns a global render information list that contains the default styles
 * which are built into the renderer.
 */
CDataVector<CLGlobalRenderInformation>* getDefaultStyles();

/**
 * This method returns the number of global styles.
 */
size_t getNumDefaultStyles();

/**
 * This method returns the default render information object with
 * the requested index. If the index isinvalid, NULL is returned.
 */
CLGlobalRenderInformation* getDefaultStyle(size_t index);

/**
 * This method is used to initialize the default styles.
 * Normally this does not need to be called since it is called automatically.
 * The method returns a point to a ListOfGlobalRenderInformation object.
 * The caller is responsible for freeing the memory associated with the list.
 */
CDataVector<CLGlobalRenderInformation>* loadDefaultStyles();

#endif // CLDEFAULT_STYLES_H__
