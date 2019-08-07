// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.


#include "copasi/copasi.h"

#include "copasi/math/CMathDerive.h"

#include "copasi/math/CMathContainer.h"
#include "copasi/math/CMathExpression.h"
#include "copasi/function/CDerive.h"



CMathDerive::CMathDerive(const CMathContainer* pContainer, size_t fun, size_t var):
  mpContainer(pContainer),
  mpRootNode(NULL)
{
  if (!pContainer)
    return;

  initOneVar(fun, var);
}



void CMathDerive::initOneVar(size_t fun, size_t var)
{
  size_t max = mpContainer->getValues().size();

  if (fun >= max)
    return;

  if (var >= max)
    return;


  CMathObject* pFMO = mpContainer->getMathObject(&mpContainer->getValues()[fun]);
  CMathObject* pVMO = mpContainer->getMathObject(&mpContainer->getValues()[var]);

  const CMathExpression* pMExp = pFMO->getExpressionPtr();

  //CEvaluationNode* tmp;

  //std::vector<const CEvaluationNode*> env;

  CDerive derive;
  derive.deriveBranch(pMExp->getRoot(), NULL);


}

const CEvaluationNode* CMathDerive::getRootNode()
{
  return mpRootNode;
}


#ifdef XXX

#include "copasi/function/CDerive.h"

CEvaluationNode* CModel::prepareElasticity(const CReaction * pReaction, const CModelEntity* pVar, bool simplify)
{
  //TODO check: pVar should be a pointer to a variable (ODE or REACTION), a local parameter, an initial value, or a fixed entity
  //it should not be an entity with an assignment.

  //here we select the actual derivation variable: concentration, or value, or volume, etc. TODO
  const CDataObject * pVarObj = pVar->CModelEntity::getValueObject();
  //const CDataObject * pVarObj = pVar->getValueObject();

  CEvaluationNode* tmp;
  CExpression * derivExp = new CExpression("derivative expression", this);

  //first handle mass action
  if (dynamic_cast<const CMassAction*>(pReaction->getFunction()))
    {
      //create the explicit kinetic law, so that we can calculate the derivative
      //we use the metabs in the object nodes. These are automatically converted to concentration references
      //during compile later
      CEvaluationNode* tmp_ma;

      //forward part
      std::vector<const CDataObject*> prod;
      size_t j;

      for (j = 0; j < pReaction->getMap().getObjects()[1].vector->size(); ++j)
        {
          prod.push_back((*(pReaction->getMap().getObjects()[1].vector))[j].value); //substrates
        }

      prod.push_back(pReaction->getMap().getObjects()[0].value); //k1

      if (prod.size() == 1)
        tmp_ma = new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + prod[0]->getCN() + ">");
      else
        {
          tmp_ma = CDerive::multiply(new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + prod[0]->getCN() + ">"),
                                     new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + prod[1]->getCN() + ">"), simplify);

          for (j = 2; j < prod.size(); ++j)
            tmp_ma = CDerive::multiply(tmp_ma,
                                       new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + prod[j]->getCN() + ">"), simplify);
        }

      //backwards part
      if (pReaction->isReversible())
        {
          CEvaluationNode * ttt = tmp_ma; //store the forward part
          CEvaluationNode * tt2; //for the backwards part
          prod.clear();

          for (j = 0; j < pReaction->getMap().getObjects()[3].vector->size(); ++j)
            {
              prod.push_back((*(pReaction->getMap().getObjects()[3].vector))[j].value); //products
            }

          prod.push_back(pReaction->getMap().getObjects()[2].value); //k2

          if (prod.size() == 1)
            tt2 = new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + prod[0]->getCN() + ">");
          else
            {
              tt2 = CDerive::multiply(new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + prod[0]->getCN() + ">"),
                                      new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + prod[1]->getCN() + ">"), simplify);

              for (j = 2; j < prod.size(); ++j)
                tt2 = CDerive::multiply(tt2,
                                        new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + prod[j]->getCN() + ">"), simplify);
            }

          tmp_ma = new CEvaluationNodeOperator(CEvaluationNode::SubType::MINUS, "-");
          tmp_ma->addChild(ttt);
          tmp_ma->addChild(tt2);
        }

      CExpression * tmpExp = new CExpression("Mass action expression", this);
      CDerive::compileTree(tmp_ma, tmpExp);

      tmpExp->setRoot(tmp_ma);
      tmpExp->compile(); //this converts references from model entities to value references

      std::vector<const CEvaluationNode*> env;
      tmp = CDerive::deriveBranch(tmp_ma, pVarObj, env, derivExp, simplify);

      CDerive::deleteBranch(tmp_ma);
    }
  else //not mass action
    {
      //create call environment for the kinetic function
      //do we have to call something on CReaction to make sure that the map is uptodate?
      std::vector<const CEvaluationNode*> env;
      size_t i, imax = pReaction->getMap().getObjects().size();
      env.resize(imax);

      for (i = 0; i < imax; ++i)
        {
          const CDataObject* tmpObj = pReaction->getMap().getObjects()[i].value;
          //if we have a metab, its always the concentration
          const CMetab* tmpMetab = dynamic_cast<const CMetab*>(tmpObj);

          if (tmpMetab)
            tmpObj = tmpMetab->getConcentrationReference();

          std::string tmpstr = tmpObj ? "<" + tmpObj->getCN() + ">" : "<>";
          CEvaluationNodeObject* tmpENO = new CEvaluationNodeObject(CEvaluationNode::SubType::CN, tmpstr);
          env[i] = tmpENO;
          tmpENO->compile(derivExp); //this uses derivExp as a dummy expression (so that the node has a context for the compile()
        }

      tmp = CDerive::deriveBranch(pReaction->getFunction()->getRoot(), pVarObj, env, derivExp, simplify);

      for (int l = (int)env.size() - 1; l >= 0; l--)
        {
          delete const_cast<CEvaluationNode*>(env[l]);
        }

      env.clear();
    }

  derivExp->setRoot(tmp);
  derivExp->compile();

  //tmp->printRecursively(std::cout);
  return tmp;
}

#endif
