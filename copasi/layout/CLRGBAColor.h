// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLRGBAColor.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/10 12:26:12 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLRGBACOLOR_H__
#define CLRGBACOLOR_H__

// opengl includes
#ifdef WIN32
#include "windows.h"
#endif // WIN32

#ifdef __APPLE__
#include "OpenGL/gl.h"
#include "OpenGL/glu.h"
#else
#include "GL/gl.h"
#include "GL/glu.h"
#endif // __APPLE__

struct CLRGBAColor
{
  // red
  GLubyte mR;
  // green
  GLubyte mG;
  // blue
  GLubyte mB;
  // alpha
  GLubyte mA;
};

#endif /* CLRGBACOLOR_H__ */
