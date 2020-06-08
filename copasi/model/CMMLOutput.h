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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CMML_H
#define CMML_H

#include <sstream>
#include <set>
#include <vector>
#include "copasi/copasi.h"

class CModel;
class CMetab;
class CModelEntity;
class CReaction;

/**
 * This class handles the output of the differential equations as presentation MathML
 */
class CMMLOutput
{

public:
  CMMLOutput();

  static void writeDifferentialEquations(std::ostream & mml, CModel * model, bool localParameterNumbers, bool expand, bool expandFull);

private:
  static void writeLHS(std::ostream & out, const std::string & metabName,
                       const std::string & compName, size_t l);

  static void writeRHS(std::ostream & out, const CMetab* pMetab, const CReaction* pReac,
                       bool numbers, bool expand, bool expandFull,
                       size_t l);

  //list keys of all reactions that have the metab in their balances
  static std::set<std::string> listReactionsForMetab(const CModel* model,
      const std::string & key);

  static void createParameterMapping(const CReaction* pReac,
                                     std::vector<std::vector<std::string> > & params,
                                     bool numbers);

  static void writeLHS_ModelValue(std::ostream & out,
                                  const std::string & valueName, size_t l);

  static void writeRHS_ModelEntity(std::ostream & out,
                                   const CModelEntity* pEntity,
                                   bool expandFull, size_t l);

  //std::ostringstream mml;
};

#endif
