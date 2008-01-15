// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRaptorInit.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/15 17:45:38 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <raptor.h>

#include "CRaptorInit.h"

// static
bool CRaptorInit::Initialized = false;

CRaptorInit::CRaptorInit()
{
  if (!Initialized)
    {
      raptor_init();
      Initialized = true;
    }
}

CRaptorInit::~CRaptorInit()
{}
