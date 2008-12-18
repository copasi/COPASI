// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRaptorInit.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 18:52:23 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <raptor.h>
#include <string.h>

#include "copasi.h"

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

// static
bool CRaptorInit::isLocalURI(raptor_uri * pURI)
{
  raptor_uri * pTmp =
    raptor_new_uri_for_retrieval(pURI);

  bool isLocal =
    (strcmp("/", (char *) raptor_uri_as_string(pTmp)) == 0);

  pRaptorFreeUri(pTmp);

  return isLocal;
}
