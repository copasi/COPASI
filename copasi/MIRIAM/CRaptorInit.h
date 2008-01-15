// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRaptorInit.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/15 17:45:38 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CRaptorInit
#define COPASI_CRaptorInit

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

    // Attributes
  private:

    /**
     * This attribute indicates whether the rapor library is initialized
     */
    static bool Initialized;
  };

#define pRaptorFreeUri(p) {if (p) {raptor_free_uri(p); p = NULL;}}

#endif // COPASI_CRaptorInit
