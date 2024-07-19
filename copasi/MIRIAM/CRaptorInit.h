// Copyright (C) 2019 - 2024 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

#ifndef COPASI_CRaptorInit
#define COPASI_CRaptorInit

#include <copasi/copasi.h>

#ifdef COPASI_USE_RAPTOR

class CRaptorInit
  {
    // Operations
  public:
    /**
     * Constructor
     */
    CRaptorInit();

    /**
     * Constructor
     */
    ~CRaptorInit();

    /**
     * Checks whether the given URI is resolved locally;
     * @param raptor_uri * pURI
     * @return bool isLocalURI
     */
    static bool isLocalURI(raptor_uri * pURI);

    // Attributes
  private:

    /**
     * This attribute indicates whether the raptor library is initialized
     */
    static bool Initialized;
  };

#define pRaptorFreeUri(p) {if (p) {raptor_free_uri(p); p = NULL;}}

#endif // COPASI_USE_RAPTOR

#endif // COPASI_CRaptorInit
