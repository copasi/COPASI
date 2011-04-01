// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLImageTexturizer.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/04/01 15:06:41 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.


#include "copasi.h"

#include "CLImageTexturizer.h"

#include "utilities/CDirEntry.h"
#include "utilities/utility.h"

std::string CLImageTexturizer::to_absolute_path(const std::string& filename, const std::string& basedir)
{
  // first convert to UTF8 because CDirEntry expects UTF8
  std::string Path = filename;
  CDirEntry::makePathAbsolute(Path, basedir);

  return Path;
}
