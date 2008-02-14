// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/utilities.hpp,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/02/14 10:52:44 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <istream>

class CCopasiDataModel;

bool load_cps_model_from_stream(std::istream& is, CCopasiDataModel& dataModel);

bool import_sbml_model_from_stream(const std::istream& is, CCopasiDataModel& dataModel);
