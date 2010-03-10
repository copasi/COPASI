// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLImageTexturizer.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/10 12:26:12 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLIMAGETEXTURIZER_H__
#define CLIMAGETEXTURIZER_H__

#include <string>

class CLTextureSpec;

class CLImageTexturizer
{
public:
  virtual CLTextureSpec* operator()(const std::string& filename, const std::string& basedir) = 0;

protected:
  /**
   * Takes a filename and tries to find out if it is a relative or an
   * absolute path.
   * If the file can not be found either way, an empty string is
   *returned.
   */
  static std::string to_absolute_path(const std::string& filename, const std::string& basedir);
};

#endif // CLIMAGETEXTURIZER_H__
