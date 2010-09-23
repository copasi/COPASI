// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLImageTexturizer.cpp,v $
//   $Revision: 1.1.2.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/09/23 13:57:08 $
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
  std::string utf8 = localeToUtf8(filename);
  std::string dir = CDirEntry::dirName(filename);

  if (CDirEntry::isRelativePath(dir))
    {
      dir = basedir + "/" + filename;
    }
  else
    {
      dir = filename;
    }

  // convert back to locale
  return utf8ToLocale(dir);
}
