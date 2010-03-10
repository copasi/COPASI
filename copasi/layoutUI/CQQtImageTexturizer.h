// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQQtImageTexturizer.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/10 12:33:51 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQQTIMAGERASTERIZER_H__
#define CQQTIMAGERASTERIZER_H__

#include <string>

#include <copasi/layout/CLImageTexturizer.h>

class CLTextureSpec;

class CQQtImageTexturizer : public CLImageTexturizer
{
public:
  virtual CLTextureSpec* operator()(const std::string& filename, const std::string& basedir);

protected:
  CLTextureSpec* create_texture_for_image(const std::string& filename, const char* format = NULL);
};

#endif // CQQTIMAGERASTERIZER_H__
