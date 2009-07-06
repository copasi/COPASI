// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/04/11 15:21:36 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Sven Sahle and University of Heidelberg
// All rights reserved.

#ifndef EXPRESSION2PRESENTATIONMMLUNITS_H
#define EXPRESSION2PRESENTATIONMMLUNITS_H

#include "Expression2PresentationMML.h"

class CUnitInterfaceSBML;
class CUnitInformation;
class UnitDefinition;
class Unit;

class Expression2PresentationMMLUnits : public Expression2PresentationMML
{
public:
  Expression2PresentationMMLUnits(const ASTNode* rootnode);

  /**
   * sets the unit interface to the SBML model so that the units can be displayed.
   * this implicitly also handles setting the model
   */
  void setUnitInterface(CUnitInterfaceSBML * unitInterface, CUnitInterfaceSBML * unitInterface2);

  std::string getMathML(const CUnitInformation & ui) const;

protected:
//    virtual void writeMathMLFunction(std::ostream & out, const ASTNode* node, unsigned int l) const;
  virtual void writeMathMLName(std::ostream & out, const ASTNode* node, unsigned int l) const;
  virtual void writeMathMLNumber(std::ostream & out, const ASTNode* node, unsigned int l) const;

  /**
   * write the mathML for a box that is used to display an object identifier + its unit information
   * a and b are mathML strings
   */
  void writeMathMLBox(std::ostream & out, const std::string & a, const std::string & b,
                      const std::string & color, unsigned int l) const;

  void writeMathMLBox(std::ostream & out, const std::string & a, const std::string & b, const std::string & c,
                      const std::string & color, unsigned int l) const;

  std::string getMathML(const UnitDefinition & ud) const;
  std::string getMathML(const Unit * u, bool absExp) const;

  CUnitInterfaceSBML * mpUnitInterface;
  CUnitInterfaceSBML * mpUnitInterface2;
};

#endif // EXPRESSION2PRESENTATIONMMLUNITS_H
