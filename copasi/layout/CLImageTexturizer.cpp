// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLImageTexturizer.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/10 12:26:12 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <fstream>

#include "CLImageTexturizer.h"

std::string CLImageTexturizer::to_absolute_path(const std::string& filename, const std::string& basedir)
{
  // check if the filename is a relative filename
  // if yes, we extend it with mBaseDir
  // otherwise we just return the original string
  // we make this simple
  std::ifstream file((basedir + "/" + filename).c_str());

  if (!file)
    {
      // this is not totally correct since, but rather simple
      // TODO come up with a better way to determine f a filename is relative
      // TODO or absolute
      file.open(filename.c_str());

      if (!file)
        {
          return "";
        }
      else
        {
          return filename;
        }
    }
  else
    {
      return basedir + "/" + filename;
    }
}
