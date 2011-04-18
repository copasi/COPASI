// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLImageTexturizer.cpp,v $
//   $Revision: 1.1.2.4 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/04/18 20:28:30 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.


#include "CLImageTexturizer.h"

#include <copasi/utilities/CDirEntry.h>
#include <copasi/copasi.h>
#include <copasi/utilities/utility.h>

std::string CLImageTexturizer::to_absolute_path(const std::string& filename, const std::string& basedir)
{
  // first convert to UTF8 because CDirEntry expects UTF8
  std::string Path = filename;
  CDirEntry::makePathAbsolute(Path, basedir);

  return Path;
}
