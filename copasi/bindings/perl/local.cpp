// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/perl/local.cpp,v $
//   $Revision: 1.2.2.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/07/28 08:44:50 $
// End CVS Header


// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifdef SWIGPERL
#undef NORMAL
#endif // SWIGPERL

#include "../common/local_common.cpp"
// since COPASI undefines TRUE from swig, we have to redefine it here
#define TRUE 1

#include "../common/downcast_common.cpp"
