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

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Sven Sahle and University of Heidelberg
// All rights reserved.

#ifndef EXPRESSION2PRESENTATIONMMLUNITS_H
#define EXPRESSION2PRESENTATIONMMLUNITS_H

#include "copasi/copasi.h"
#include "Expression2PresentationMML.h"

class CSBMLunitInterface;
class CSBMLunitInformation;

LIBSBML_CPP_NAMESPACE_BEGIN
class UnitDefinition;
class Unit;
LIBSBML_CPP_NAMESPACE_END

class Expression2PresentationMMLUnits : public Expression2PresentationMML
{
public:
  Expression2PresentationMMLUnits(const ASTNode* rootnode);

  /**
   * sets the unit interface to the SBML model so that the units can be displayed.
   * this implicitly also handles setting the model
   */
  void setUnitInterface(CSBMLunitInterface * unitInterface, CSBMLunitInterface * unitInterface2);

  std::string getMathML(const CSBMLunitInformation & ui) const;

protected:
//    virtual void writeMathMLFunction(std::ostream & out, const ASTNode* node, size_t l) const;
  virtual void writeMathMLName(std::ostream & out, const ASTNode* node, size_t l) const;
  virtual void writeMathMLNumber(std::ostream & out, const ASTNode* node, size_t l) const;

  /**
   * write the mathML for a box that is used to display an object identifier + its unit information
   * a and b are mathML strings
   */
  void writeMathMLBox(std::ostream & out, const std::string & a, const std::string & b,
                      const std::string & color, size_t l) const;

  void writeMathMLBox(std::ostream & out, const std::string & a, const std::string & b, const std::string & c,
                      const std::string & color, size_t l) const;

  std::string getMathML(const UnitDefinition & ud) const;
  std::string getMathML(const Unit * u, bool absExp) const;

  CSBMLunitInterface * mpUnitInterface;
  CSBMLunitInterface * mpUnitInterface2;
};

#endif // EXPRESSION2PRESENTATIONMMLUNITS_H
