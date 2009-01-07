/* Begin CVS Header
 $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/odepack++/Cxerrwd.h,v $
 $Revision: 1.5 $
 $Name:  $
 $Author: shoops $
 $Date: 2009/01/07 19:01:06 $
 End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.
//
// This C++ code is based on an f2c conversion of the Fortran
// library ODEPACK available at: http://www.netlib.org/odepack/

#ifndef ODEPACK_xerrwd
#define ODEPACK_xerrwd

#include <iostream>
#include <string>

class Cxerrwd
  {
  public:
    Cxerrwd(const bool & print);

    ~Cxerrwd();

    void operator() (const std::string & msg, const C_INT *nmes, const C_INT *nerr, const C_INT
                     *level, const C_INT *ni, const C_INT *i1, const C_INT *i2, const C_INT *nr,
                     const double *r1, const double *r2, C_INT msg_len);

    void setOstream(std::ostream & os);
    void enablePrint(const bool & print = true);

  private:
    bool mPrint;
    std::ostream * mpOstream;
  };

#endif // ODEPACK_xerrwd
