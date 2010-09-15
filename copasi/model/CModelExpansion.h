// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelExpansion.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/09/15 16:38:59 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CMODELEXPANSION_H
#define CMODELEXPANSION_H

#include <string>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <copasi.h>
#include <vector>

class CModel;
class CMetab;
class CCompartment;
class CReaction;
class CModelEntity;
class CExpression;

class CModelExpansion
{
public:
  CModelExpansion(CModel* pModel);

  void setModel(CModel* pModel);

  //just a simple method to call during development
  void simpleCall(const CCompartment* source, std::vector< std::string  > listOfMetabolites, int mult, bool diff);


  class CompartmentInfo
  {
  public:
    CompartmentInfo() {};

    std::map<std::string, std::string> keyMap;
    std::string key;
  };

  CompartmentInfo copyCompartment(const CCompartment* source);
protected:


  CompartmentInfo ci;

  /**
   * determine whether the one of the substrate, products, or modifiers of the reaction
   * is located in the given compartmen
   */
  static bool reactionInvolvesCompartment(const CReaction * reac, const CCompartment* comp);

  /**
   *   handle non constant model entities
   **/

  bool  copyCompartmentsExpressions(const CCompartment *source);
  bool  copyMetabolitesExpressions(const CCompartment *source);

  bool  copyModelValuesExpressions(std::string copyname);
  bool  copyEvents(std::string copyname);

  std::string copyExpression(const CExpression *pExpression);
  std::string testName(const std::string & mname);
  void  nameInSet(const std::string & mname);

  CModel * mpModel;

  std::set<std::string> NameSet;

  std::string name;
};

#endif // CMODELEXPANSION_H
