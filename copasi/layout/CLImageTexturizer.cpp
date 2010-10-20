// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLImageTexturizer.cpp,v $
//   $Revision: 1.1.2.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/10/20 15:14:24 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.


#include "CLImageTexturizer.h"

#include <copasi/utilities/CDirEntry.h>
#include <copasi/utilities/utility.h>

std::string CLImageTexturizer::to_absolute_path(const std::string& filename, const std::string& basedir)
{
  // first convert to UTF8 because CDirEntry expects UTF8
  std::string Path = filename;
  CDirEntry::makePathAbsolute(Path, basedir);

  return Path;
}
