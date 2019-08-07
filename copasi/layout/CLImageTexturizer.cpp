// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.


#include "copasi/copasi.h"

#include "CLImageTexturizer.h"

#include "copasi/utilities/CDirEntry.h"
#include "copasi/utilities/utility.h"

std::string CLImageTexturizer::to_absolute_path(const std::string& filename, const std::string& basedir)
{
  // first convert to UTF8 because CDirEntry expects UTF8
  std::string Path = filename;
  CDirEntry::makePathAbsolute(Path, basedir);

  return Path;
}
