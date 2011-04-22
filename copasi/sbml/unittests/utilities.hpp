// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/utilities.hpp,v $
//   $Revision: 1.2.16.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/04/22 15:29:12 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <istream>
#include <ostream>

class CCopasiDataModel;

bool load_cps_model_from_stream(std::istream& is, CCopasiDataModel& dataModel);
bool save_cps_model_to_stream(std::ostream& os, CCopasiDataModel* pDataModel);

