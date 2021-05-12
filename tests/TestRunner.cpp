// Copyright (C) 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// BEGIN: Copyright
// END: Copyright

// BEGIN: License
// Licensed under the Artistic License 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//   https://opensource.org/licenses/Artistic-2.0
// END: License

/**
 * Main Entry point for all tests (defines catch main, and only one
 * test file can do it). This file is there to include utility
 * functions used in all other test files.
 */

// now include catch
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <string.h>
#include <cstdlib>

#define COPASI_MAIN
#include <copasi/core/CRootContainer.h>

/**
 * Tries to find the test file in the srcdir environment variable.
 *
 * @param fileName the filename relative to this tests srcdir
 *        environment variable.
 *
 * If the filename cannot be found, the test from which this function
 * is called will fail.
 *
 * @return the full path to the test file
 */
std::string getTestFile(const std::string& fileName)
{
  std::stringstream str;
  char* srcDir = getenv("srcdir");

  if (srcDir != NULL) str << srcDir;
  else str << ".";

  str << "/" << fileName;
  std::string fullName = str.str();

  return fullName;
}

int main(int argc, char *argv[])
{
  CRootContainer::init(0, NULL);

  int result = Catch::Session().run(argc, argv);

  CRootContainer::destroy();

  return result;
}
