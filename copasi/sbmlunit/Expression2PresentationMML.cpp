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

#include "Expression2PresentationMML.h"
#include <sbml/Model.h>

Expression2PresentationMML::Expression2PresentationMML(const ASTNode* rootnode)
    : mRootNode(rootnode), mpModel(NULL), mpReaction(NULL),
    mUseReactionNameInLocalParameters(true)
{
}

void Expression2PresentationMML::writeMathML(std::ostream & out) const
{
  writeMathML(out, mRootNode, 0);
}

#define SPC(level) std::string(level, ' ')

void Expression2PresentationMML::writeMathML(std::ostream & out, const ASTNode* node, unsigned int l) const
{
  ASTNodeType_t type = node->getType();

  //piecewise
  if (type == AST_FUNCTION_PIECEWISE)
    {
      unsigned int i;
      out << SPC(l) << "<mrow>" << std::endl;
      out << SPC(l + 1) << "<mo> {</mo>" << std::endl;
      out << SPC(l + 1) << "<mtable>" << std::endl;

      for (i = 0; i < node->getNumChildren() / 2 + 1; ++i)
        {
          out << SPC(l + 2) << "<mtr>" << std::endl;
          out << SPC(l + 3) << "<mtd>" << std::endl;
          writeMathML(out, node->getChild(0 + i*2), l + 3);
          out << SPC(l + 3) << "<mo> , </mo>" << std::endl;
          out << SPC(l + 3) << "</mtd>" << std::endl;

          out << SPC(l + 3) << "<mtd>" << std::endl;

          if (1 + i*2 >= node->getNumChildren())
            out << SPC(l + 3) << "<mo> else </mo>" << std::endl;
          else
            writeMathML(out, node->getChild(1 + i*2), l + 3);

          out << SPC(l + 3) << "</mtd>" << std::endl;
          out << SPC(l + 2) << "</mtr>" << std::endl;
        }

      out << SPC(l + 1) << "</mtable>" << std::endl;
      out << SPC(l) << "</mrow>" << std::endl;
      return;
    }

  //other functions like power, root
  if (type == AST_FUNCTION_POWER)
    type = AST_POWER;

  //generic functions, including call nodes. Call nodes may be handles separately later.
  if (type >= AST_FUNCTION/*_ABS*/ && type <= AST_FUNCTION_TANH)
    {
      writeMathMLFunction(out, node, l);
      return;
    }

  if (node->isNumber())
    {
      writeMathMLNumber(out, node, l);
      return;
    }

  unsigned int i;
  unsigned int tmp;
  bool flag;

  switch (type)
    {
      case AST_NAME:
        writeMathMLName(out, node, l);
        break;

      case AST_PLUS:
        out << SPC(l) << "<mrow>" << std::endl;

        for (i = 0; i < node->getNumChildren(); ++i)
          {
            if (i)
              out << SPC(l + 1) << "<mo>" << "+" << "</mo>" << std::endl;

            writeMathML(out, node->getChild(i), l + 1);
          }

        out << SPC(l) << "</mrow>" << std::endl;
        break;

      case AST_MINUS:

        if (node->getNumChildren() <= 0 || node->getNumChildren() > 2)
          break;

        out << SPC(l) << "<mrow>" << std::endl;

        if (node->getNumChildren() == 2)
          writeMathML(out, node->getChild(0), l + 1);

        out << SPC(l + 1) << "<mo>" << "-" << "</mo>" << std::endl;

        tmp = node->getNumChildren() - 1; //the last child
        flag = (node->getChild(tmp)->getType() == AST_PLUS)
               || (node->getChild(tmp)->getType() == AST_MINUS);

        //      || ((node->getChild(tmp)->getType() == AST_FUNCTION) && expand)); // a function call
        if (flag) out << SPC(l + 1) << "<mfenced>" << std::endl;

        writeMathML(out, node->getChild(tmp), l + 2);

        if (flag) out << SPC(l + 1) << "</mfenced>" << std::endl;

        out << SPC(l) << "</mrow>" << std::endl;
        break;

      case AST_TIMES:
        out << SPC(l) << "<mrow>" << std::endl;

        for (i = 0; i < node->getNumChildren(); ++i)
          {
            if (i)
              out << SPC(l + 1) << "<mo>" << "&CenterDot;" << "</mo>" << std::endl;

            //do we need "()" ?
            flag = (node->getChild(i)->getType() == AST_PLUS)
                   || (node->getChild(i)->getType() == AST_MINUS);

            //      || ((node->getChild(i)->getType() == AST_FUNCTION) && expand)); // a function call
            if (flag) out << SPC(l + 1) << "<mfenced>" << std::endl;

            writeMathML(out, node->getChild(i), l + 1);

            if (flag) out << SPC(l + 1) << "</mfenced>" << std::endl;
          }

        out << SPC(l) << "</mrow>" << std::endl;
        break;

      case AST_DIVIDE:
        out << SPC(l) << "<mfrac>" << std::endl;

        //out << SPC(l + 1) << "<mrow>" << std::endl;
        writeMathML(out, node->getChild(0), l + 1);
        //out << SPC(level + 1) << "</mrow>" << std::endl;

        //out << SPC(l + 1) << "<mrow>" << std::endl;
        writeMathML(out, node->getChild(1), l + 1);
        //out << SPC(l + 1) << "</mrow>" << std::endl;

        out << SPC(l) << "</mfrac>" << std::endl;
        break;

      case AST_POWER:
        out << SPC(l) << "<msup>" << std::endl;

        //do we need "()" ?
        flag = ((node->getChild(0)->getType() == AST_PLUS)
                || (node->getChild(0)->getType() == AST_MINUS)
                || (node->getChild(0)->getType() == AST_TIMES)
                || (node->getChild(0)->getType() == AST_DIVIDE)
                || (node->getChild(0)->getType() == AST_POWER));
        //  || (((node->getChild(0)->getType() == AST_FUNCTION) && expand)

        if (flag) out << SPC(l + 1) << "<mfenced>" << std::endl;

        writeMathML(out, node->getChild(0), l + 2);

        if (flag) out << SPC(l + 1) << "</mfenced>" << std::endl;

        out << SPC(l + 1) << "<mrow>" << std::endl;
        writeMathML(out, node->getChild(1), l + 2);
        out << SPC(l + 1) << "</mrow>" << std::endl;

        out << SPC(l) << "</msup>" << std::endl;
        break;

      case AST_CONSTANT_E:
        out << "<mi>&ExponentialE;</mi>" << std::endl;
        break;

      case AST_CONSTANT_PI:
        out << SPC(l)  << "<mi>&pi;</mi>" << std::endl;
        break;

      case AST_CONSTANT_FALSE:
        out << SPC(l)  << "<mi>false</mi>" << std::endl;
        break;

      case AST_CONSTANT_TRUE:
        out << SPC(l)  << "<mi>true</mi>" << std::endl;
        break;

      case AST_NAME_TIME:
        out << SPC(l)  << "<mi>t</mi>" << std::endl;
        break;

      case AST_LOGICAL_AND:
      case AST_LOGICAL_OR:
      case AST_LOGICAL_XOR:
      case AST_RELATIONAL_EQ:
      case AST_RELATIONAL_GEQ:
      case AST_RELATIONAL_GT:
      case AST_RELATIONAL_LEQ:
      case AST_RELATIONAL_LT:
      case AST_RELATIONAL_NEQ:
      {
        std::string op;

        switch (type)
          {
            case AST_LOGICAL_AND: op="&And;"; flag=true; break;
            case AST_LOGICAL_OR: op="&Or;"; flag=true; break;
            case AST_LOGICAL_XOR: op="xor"; flag=true; break;
            case AST_RELATIONAL_EQ: op="="; flag=false; break;
            case AST_RELATIONAL_GEQ: op="&geq;"; flag=false; break;
            case AST_RELATIONAL_GT: op="&gt;"; flag=false; break;
            case AST_RELATIONAL_LEQ: op="&leq;"; flag=false; break;
            case AST_RELATIONAL_LT: op="&lt;"; flag=false; break;
            case AST_RELATIONAL_NEQ: op="&NotEqual;"; flag=false; break;
            default: op="???"; flag=true; break;
          }

        out << SPC(l) << "<mrow>" << std::endl;

        for (i = 0; i < node->getNumChildren(); ++i)
          {
            if (i)
              out << SPC(l + 1) << "<mo>" << op << "</mo>" << std::endl;

            //do we need "()" ?

            if (flag) out << SPC(l + 1) << "<mfenced>" << std::endl;

            writeMathML(out, node->getChild(i), l + 1);

            if (flag) out << SPC(l + 1) << "</mfenced>" << std::endl;
          }

        out << SPC(l) << "</mrow>" << std::endl;
      }
      break;

      case AST_LOGICAL_NOT:
        out << SPC(l) << "<mover>" << std::endl;
        writeMathML(out, node->getChild(0), l + 1);
        out << SPC(l) << "<mo>&OverBar;</mo></mover>" << std::endl;
        break;

      default:
        out << SPC(l) << "<mi>" << "xxx" << "</mi>" << std::endl;
        break;
    }
}

void Expression2PresentationMML::writeMathMLFunction(std::ostream & out, const ASTNode* node, unsigned int l) const
{
  out << SPC(l) << "<mrow>" << std::endl;

  out << SPC(l + 1) << "<mi>" << node->getName() << "</mi>" << std::endl;
  out << SPC(l + 1) << "<mo> &ApplyFunction; </mo>" << std::endl;
  out << SPC(l + 1) << "<mrow>" << std::endl;
  out << SPC(l + 2) << "<mo> (</mo>" << std::endl;
  out << SPC(l + 2) << "<mrow>" << std::endl;

  unsigned int i;

  for (i = 0; i < node->getNumChildren(); ++i)
    {
      if (i)
        out << SPC(l + 3) << "<mo> , </mo>" << std::endl;

      writeMathML(out, node->getChild(i), l + 3);
    }

  out << SPC(l + 2) << "</mrow>" << std::endl;
  out << SPC(l + 2) << "<mo>) </mo>" << std::endl;

  out << SPC(l + 1) << "</mrow>" << std::endl;
  out << SPC(l) << "</mrow>" << std::endl;
}

void Expression2PresentationMML::writeMathMLName(std::ostream & out, const ASTNode* node, unsigned int l) const
{

  if (!mpModel)
    {
      out << SPC(l) << "<mi>" << node->getName() << "</mi>" << std::endl;
      return;
    }

  if (mpReaction)
    {
      const Parameter* p = mpReaction->getKineticLaw()->getParameter(node->getName());

      if (p)
        {
          std::string ident = p->getName() == "" ? p->getId() : p->getName();
          std::string r_ident = mpReaction->getName() == "" ? mpReaction->getId() : mpReaction->getName();

          if (!mUseReactionNameInLocalParameters) r_ident = "local";

          out << SPC(l) << "<msub><mi>" << ident << "</mi><mi>" << r_ident << "</mi></msub>" << std::endl;
          return;
        }
    }

  const Compartment* c = mpModel->getCompartment(node->getName());

  if (c)
    {
      std::string ident = c->getName() == "" ? c->getId() : c->getName();
      std::string ccc;

      switch (c->getSpatialDimensions())
        {
          case 1: ccc="l"; break;
          case 2: ccc="A"; break;
          case 3: ccc="V"; break;
          default: ccc="ERROR";
        }

      out << SPC(l) << "<msub><mi>" << ccc << "</mi><mi>" << ident << "</mi></msub>" << std::endl;
      return;
    }

  const Species* s = mpModel->getSpecies(node->getName());

  if (s)
    {
      std::string ident = s->getName() == "" ? s->getId() : s->getName();

      if (!s->getHasOnlySubstanceUnits())
        out << SPC(l) << "<mi>[" << ident << "]</mi>" << std::endl;
      else
        {
          out << SPC(l) << "<mrow><msup><mphantom><mi>.</mi></mphantom><mi mathcolor=\"gray\">S</mi></msup><mi>" << ident << "</mi></mrow>" << std::endl;
        }

      return;
    }

  const Parameter* p = mpModel->getParameter(node->getName());

  if (p)
    {
      std::string ident = p->getName() == "" ? p->getId() : p->getName();
      //out << SPC(l) << "<mi>" << ident << "</mi>" << std::endl;
      out << SPC(l) << "<mrow><msup><mphantom><mi>.</mi></mphantom><mi mathcolor=\"gray\">P</mi></msup><mi>" << ident << "</mi></mrow>" << std::endl;
      return;
    }

  //TODO area, length, reaction rates
  out << SPC(l) << "<mi>" << node->getName() << "</mi>" << std::endl;
}

void Expression2PresentationMML::writeMathMLNumber(std::ostream & out, const ASTNode* node, unsigned int l) const
{
  if (node->isInteger())
    out << SPC(l) << "<mn>" << node->getInteger() << "</mn>" << std::endl;
  else if (node->isReal())
    out << SPC(l) << "<mn>" << node->getReal() << "</mn>" << std::endl;

  //TODO rational
}
