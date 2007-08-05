// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMMLOutput.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/05 21:28:02 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CMML_H
#define CMML_H

#include <sstream>
#include <set>
#include <vector>
#include "copasi.h"

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
                         const std::string & compName, unsigned C_INT32 l);

    static void writeRHS(std::ostream & out, const CMetab* pMetab, const CReaction* pReac,
                         bool numbers, bool expand, bool expandFull,
                         unsigned C_INT32 l);

    //list keys of all reactions that have the metab in their balances
    static std::set<std::string> listReactionsForMetab(const CModel* model,
        const std::string & key);

    static void createParameterMapping(const CReaction* pReac,
                                       std::vector<std::vector<std::string> > & params,
                                       bool numbers);

    static void writeLHS_ModelValue(std::ostream & out,
                                    const std::string & valueName, unsigned C_INT32 l);

    static void writeRHS_ModelEntity(std::ostream & out,
                                     const CModelEntity* pEntity,
                                     bool expandFull, unsigned C_INT32 l);

    //std::ostringstream mml;
  };

#endif
