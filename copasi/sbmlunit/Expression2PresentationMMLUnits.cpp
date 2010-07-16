// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/04/11 15:21:36 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Sven Sahle and University of Heidelberg
// All rights reserved.

#include "Expression2PresentationMMLUnits.h"
#include <sbml/Model.h>
#include "CUnitInterfaceSBML.h"

Expression2PresentationMMLUnits::Expression2PresentationMMLUnits(const ASTNode* rootnode)
    : Expression2PresentationMML(rootnode),
    mpUnitInterface(NULL)
{
}

void Expression2PresentationMMLUnits::setUnitInterface(CUnitInterfaceSBML * unitInterface, CUnitInterfaceSBML * unitInterface2)
{
  mpUnitInterface = unitInterface;
  mpUnitInterface2 = unitInterface2;
  mpModel = mpUnitInterface->getModel();
}

#define SPC(level) std::string(level, ' ')

void Expression2PresentationMMLUnits::writeMathMLName(std::ostream & out, const ASTNode* node, unsigned int l) const
{
  std::string reactionID = mpReaction ? mpReaction->getId() : "";
  CUnitInformation* unitInformation = mpUnitInterface->getMappedUnitFromIdentifier(node->getName(),
                                      CUnitInterfaceSBML::CEnvironmentInformation(reactionID));

  if (!unitInformation)
    {
      //use the base class implementation
      Expression2PresentationMML::writeMathMLName(out, node, l + 1);
      return;
    }

  std::string color;

  if (mpUnitInterface->getListOfConflictingNodes().count(node)
      || mpUnitInterface2->getListOfConflictingNodes().count(node))
    color = "#f0b0b0";
  else
    color = "#d0d0e0";

  CUnitInformation * unitInformation2 = NULL;

  if (mpUnitInterface2)
    unitInformation2 = mpUnitInterface2->getMappedUnitFromIdentifier(node->getName(),
                       CUnitInterfaceSBML::CEnvironmentInformation(reactionID));

  std::ostringstream oss;
  Expression2PresentationMML::writeMathMLName(oss, node, l + 2);

  if (unitInformation2 != NULL)
    {
      if (CUnitInformation::isEqual(*unitInformation, *unitInformation2))
        writeMathMLBox(out, oss.str(), getMathML(*unitInformation), "", color, l);
      else
        writeMathMLBox(out, oss.str(), getMathML(*unitInformation), getMathML(*unitInformation2), color, l);
    }
  else
    writeMathMLBox(out, oss.str(), getMathML(*unitInformation), color, l);
}

void Expression2PresentationMMLUnits::writeMathMLNumber(std::ostream & out, const ASTNode* node, unsigned int l) const
{
  CUnitInformation* unitInformation = mpUnitInterface->getMappedUnitFromNumberNode(node);
  CUnitInformation* unitInformation2 = NULL;

  if (mpUnitInterface2)
    unitInformation2 = mpUnitInterface2->getMappedUnitFromNumberNode(node);

  if (!unitInformation && !unitInformation2)
    {
      Expression2PresentationMML::writeMathMLNumber(out, node, l + 1);
      return;
    }

  std::string color;

  if (mpUnitInterface->getListOfConflictingNodes().count(node)
      || mpUnitInterface2->getListOfConflictingNodes().count(node))
    color = "#f0b0b0";
  else
    color = "#d0e0d0";

  std::ostringstream oss;
  Expression2PresentationMML::writeMathMLNumber(oss, node, l + 2);

  if (!unitInformation && unitInformation2)
    {
      writeMathMLBox(out, oss.str(), "<mi>unknown</mi>", getMathML(*unitInformation2), color, l);
    }

  if (unitInformation && !unitInformation2)
    {
      writeMathMLBox(out, oss.str(),  getMathML(*unitInformation), color, l);
    }

  if (unitInformation && unitInformation2)
    {
      writeMathMLBox(out, oss.str(),  getMathML(*unitInformation), getMathML(*unitInformation2), color, l);
    }
}

std::string Expression2PresentationMMLUnits::getMathML(const CUnitInformation & ui) const
{
  std::string tmp;
  tmp += "<mrow>";

  if (ui.isConflict())
    tmp += "<mi mathcolor = \"red\">conflict!</mi>";

  if (ui.getSymbolicExpExp() > 0)
    tmp += "<mfenced>";

  switch (ui.getInfo())
    {
      case CUnitInformation::UNKNOWN:
        tmp += "<mi mathcolor = \"orange\">unknown</mi>";
        break;

      case CUnitInformation::DEFAULT:
        tmp += "<mstyle mathcolor=\"#000060\">" + getMathML(ui.getSBMLUnitDefinition()) + "</mstyle>";
        break;

      case CUnitInformation::GLOBAL:
        tmp += "<mstyle mathcolor=\"#0000a0\">" + getMathML(ui.getSBMLUnitDefinition()) + "</mstyle>";
        break;

      case CUnitInformation::PROVIDED:
        tmp += "<mstyle mathcolor=\"#2020ff\">" + getMathML(ui.getSBMLUnitDefinition()) + "</mstyle>";
        break;

      case CUnitInformation::DERIVED:
        tmp += "<mstyle mathcolor=\"green\">" + getMathML(ui.getSBMLUnitDefinition()) + "</mstyle>";
        break;
    }

  if (ui.getSymbolicExpExp() > 0)
    {
      std::ostringstream ttt; ttt << ui.getSymbolicExpExp();
      tmp += "</mfenced><mo>^</mo><mi mathcolor = \"#c06000\">" + ui.getSymbolicExponent() + "</mi><mo>^</mo><mn>" + ttt.str() + "</mn>";
    }

  tmp += "</mrow>";
  return tmp;
}

void Expression2PresentationMMLUnits::writeMathMLBox(std::ostream & out, const std::string & a, const std::string & b,
    const std::string & color, unsigned int l) const
{
  out << SPC(l) << "<mstyle background=\"" << color << "\"><mfrac linethickness=\"0\">" << std::endl;
  out << a;
  out << SPC(l + 1) << "<mstyle scriptlevel=\"+1\">" << std::endl;
  out << SPC(l + 2) << b << std::endl;
  out << SPC(l + 1) << "</mstyle>" << std::endl;
  out << SPC(l) << "</mfrac></mstyle>" << std::endl;

  //formating is done so that it looks best when a is already indented nicely while b
  //is just a one line string
}

void Expression2PresentationMMLUnits::writeMathMLBox(std::ostream & out, const std::string & a, const std::string & b, const std::string & c,
    const std::string & color, unsigned int l) const
{
  out << SPC(l) << "<mstyle background=\"" << color << "\"><mtable rowspacing=\"0.1 ex\">" << std::endl;
  out << SPC(l + 1) << "<mtr><mtd>" << std::endl;
  out << a;
  out << SPC(l + 1) << "</mtd></mtr>" << std::endl;
  out << SPC(l + 1) << "<mtr><mtd><mstyle scriptlevel=\"+1\">" << std::endl;
  out << SPC(l + 2) << b << std::endl;
  out << SPC(l + 1) << "</mstyle></mtd></mtr>" << std::endl;
  out << SPC(l + 1) << "<mtr><mtd><mstyle scriptlevel=\"+1\">" << std::endl;
  out << SPC(l + 2) << c << std::endl;
  out << SPC(l + 1) << "</mstyle></mtd></mtr>" << std::endl;
  out << SPC(l) << "</mtable></mstyle>" << std::endl;

  //formating is done so that it looks best when a is already indented nicely while b
  //is just a one line string
}

std::string Expression2PresentationMMLUnits::getMathML(const UnitDefinition & ud) const
{
  std::string tmp;

  /*tmp += "<mrow>";
  unsigned int i, imax = ud.getNumUnits();
  for (i=0; i<imax; ++i)
  {
    if (i) tmp += "<mo>&CenterDot;</mo>";
    tmp += getMathML(ud.getUnit(i), false);
  }
  tmp += "</mrow>";*/

  tmp += "<mrow>";
  bool isFirst = true;
  unsigned int i, imax = ud.getNumUnits();

  for (i = 0; i < imax; ++i)
    {
      if (ud.getUnit(i)->getExponent() >= 0)
        {
          if (!isFirst) tmp += "<mo>&CenterDot;</mo>";

          tmp += getMathML(ud.getUnit(i), true);
          isFirst = false;
        }
    }

  if (isFirst) tmp += "<mn>1</mn>"; //there are no units with pos. exponent

  std::string tmp2;
  isFirst = true;

  for (i = 0; i < imax; ++i)
    {
      if (ud.getUnit(i)->getExponent() < 0)
        {
          if (!isFirst) tmp2 += "<mo>&CenterDot;</mo>";

          tmp2 += getMathML(ud.getUnit(i), true);
          isFirst = false;
        }
    }

  if (!isFirst) tmp += "<mo>/</mo>" + tmp2; //only create fraction when there is a denominator

  tmp += "</mrow>";

  return tmp;
}

std::string Expression2PresentationMMLUnits::getMathML(const Unit * u, bool absExp) const
{
  if (!u)
    return "<mi>EEE</mi>";

  int exponent = absExp ? abs(u->getExponent()) : u->getExponent();
  bool flagExp = (exponent != 1);
  bool flag = (u->getMultiplier() != 1.0) || (u->getScale() != 0); //are brackets needed?

  std::ostringstream tmp;

  if (flagExp) tmp << "<msup>";

  //if (flag) tmp << "<mfenced>";
  tmp << "<mrow>";

  if (flag) tmp << "<mo>(</mo>";

  if (u->getMultiplier() != 1.0)
    tmp << "<mn>" <<  u->getMultiplier() << "</mn><mo>&CenterDot;</mo>";

  if (u->getScale() != 0)
    tmp << "<msup><mn>10</mn><mn>" << u->getScale() << "</mn></msup><mo>&CenterDot;</mo>";

  tmp << "<mi>";
  tmp << UnitKind_toString(u->getKind());
  tmp << "</mi>";

  if (flag) tmp << "<mo>)</mo>";

  tmp << "</mrow>";
  //if (flag) tmp << "</mfenced>";

  if (flagExp) tmp << "<mn>" << exponent << "</mn>";

  if (flagExp) tmp << "</msup>";

  //tmp << "</mrow>";

  return tmp.str();
}
