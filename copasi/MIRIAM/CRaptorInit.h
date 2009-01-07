// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRaptorInit.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/01/07 18:58:54 $
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

#endif // COPASI_CRaptorInit
