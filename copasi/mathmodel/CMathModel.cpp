/**
 *  CMathModel class.
 *  The class CMathModel is a mathematical representation of a chemical
 *  model (class CModel
 *
 *  Created for Copasi by Stefan Hoops 2003
 */

#include "copasi.h"
#include "CMathModel.h"
#include "CMathConstant.h"
#include "CMathVariable.h"
#include "CMathNode.h"
#include "CMathEq.h"

#include "model/CModel.h"
#include "utilities/CMethodParameter.h"

CMathModel::CMathModel():
    mpModel(NULL),
    mCompartmentList(),
    mMetabList(),
    mFixedMetabList(),
    mVolumeList(),
    mpTime(NULL),
    mFunctionList(),
    mConstantsList(),
    mEqList(),
    mpConversionFactor(NULL)
{}

CMathModel::CMathModel(const CMathModel & src):
    mpModel(src.mpModel),
    mCompartmentList(),
    mMetabList(),
    mFixedMetabList(),
    mVolumeList(),
    mpTime(NULL),
    mFunctionList(),
    mConstantsList(),
    mEqList(),
    mpConversionFactor(NULL)
{compile();}

CMathModel::~CMathModel()
{
  clearList(mCompartmentList);
  clearList(mMetabList);
  clearList(mFixedMetabList);
  clearList(mVolumeList);
  pdelete(mpTime);
  clearList(mFunctionList);
  clearList(mConstantsList);
  clearEqList();
  pdelete(mpConversionFactor)
}

bool CMathModel::setModel(const CModel * pModel)
{
  mpModel = pModel;
  return compile();
}

const CModel * CMathModel::getModel() const {return mpModel;}

bool CMathModel::compile()
{
  if (!mpModel) return false;

  bool Success = true;

  if (!buildCompartmentList()) Success = false;
  if (!buildMetabList()) Success = false;
  if (!buildFixedMetabList()) Success = false;
  if (!buildVolumeList()) Success = false;
  if (!buildTime()) Success = false;
  if (!buildFunctionList()) Success = false;
  if (!buildConstantsList()) Success = false;

  /* We create a symbol for the conversion factor */
  CCopasiObjectReference< C_FLOAT64 > & Reference =
    * (CCopasiObjectReference< C_FLOAT64 > *) const_cast<CModel *>(mpModel)->
    getObject(CCopasiObjectName("Reference=Quantity Conversion Factor"));

  mpConversionFactor = new CMathConstantReference(Reference);
  std::string Name("QCF");
  mpConversionFactor->setName(Name);

  if (!compileCompartmentList()) Success = false;
  if (!compileMetabList()) Success = false;
  if (!compileFixedMetabList()) Success = false;

  if (!buildEqList()) Success = false;

  return Success;
}

std::map< std::string, CMathConstantCompartment * > & CMathModel::getCompartmentList()
{return mCompartmentList;}

std::map< std::string, CMathVariableMetab * > & CMathModel::getMetabList()
{return mMetabList;}

std::map< std::string, CMathConstantMetab * > & CMathModel::getFixedMetabList()
{return mFixedMetabList;}

std::map< std::string, CMathVariableVolume * > & CMathModel::getVolumeList()
{return mVolumeList;}

CMathVariableTime * CMathModel::getTime() {return mpTime;}

std::map< std::string, CMathSymbol * > & CMathModel::getFunctionList()
{return mFunctionList;}

std::map< std::string, CMathConstantParameter * > & CMathModel::getConstantsList()
{return mConstantsList;}

bool CMathModel::buildCompartmentList()
{
  bool Success = true;

  clearList(mCompartmentList);

  const CCopasiVector< CCompartment > & List = mpModel->getCompartments();
  unsigned C_INT32 i, imax = List.size();

  CMathConstantCompartment * p;

  for (i = 0; i < imax; i++)
    {
      p = new CMathConstantCompartment(*List[i]);
      mCompartmentList[p->getName()] = p;
    }

  return Success;
}

bool CMathModel::buildMetabList()
{
  bool Success = true;

  clearList(mMetabList);

  const CCopasiVector< CMetab > & List = mpModel->getMetabolitesX();
  unsigned C_INT32 i, imax = mpModel->getIntMetab();

  CMathVariableMetab * p;

  for (i = 0; i < imax; i++)
    {
      p = new CMathVariableMetab(*List[i]);
      mMetabList[p->getName()] = p;
    }

  return Success;
}

bool CMathModel::buildFixedMetabList()
{
  bool Success = true;

  clearList(mFixedMetabList);

  const CCopasiVector< CMetab > & List = mpModel->getMetabolitesX();
  unsigned C_INT32 i, imax = List.size();

  CMathConstantMetab * p;

  for (i = mpModel->getIntMetab(); i < imax; i++)
    {
      p = new CMathConstantMetab(*List[i]);
      mFixedMetabList[p->getName()] = p;
    }

  return Success;
}

bool CMathModel::buildVolumeList()
{
  bool Success = true;

#ifdef  XXXX
  /* :TODO: This needs to be activated/modified when we implement variable
     volumes. */
  clearList((std::map< std::string, CMathSymbol * > *) & mCompartmentList);

  const CCopasiVector< CCompartment > & List = mpModel->getCompartments();
  unsigned C_INT32 i, imax = List.size();

  CMathVariableVolume * p;

  for (i = 0; i < imax; i++)
    {
      p = new CMathVariableVolume(*List[i]);
      mVolumeList[p->getName()] = p;
    }
#endif // XXXX
  return Success;
}

bool CMathModel::buildTime()
{
  bool Success = true;

  pdelete(mpTime);

  mpTime = new CMathVariableTime(*mpModel);

  return Success;
}

bool CMathModel::buildFunctionList()
{
  bool Success = true;

  clearList(mFunctionList);

  const CCopasiVector< CReaction > & List = mpModel->getReactions();
  unsigned C_INT32 i, imax = List.size();

  CMathSymbol * p;
  const CFunction * pFunction;

  for (i = 0; i < imax; i++)
    {
      pFunction = &List[i]->getFunction();
      if (pFunction && !CMathSymbol::find(pFunction))
        {
          p = new CMathSymbol(pFunction);
          mFunctionList[p->getName()] = p;
        }
    }

  return Success;
}

bool CMathModel::buildConstantsList()
{
  bool Success = true;

  clearList(mConstantsList);

  const CCopasiVector< CReaction > & List = mpModel->getReactions();
  unsigned C_INT32 i, imax = List.size();
  unsigned C_INT32 j, jmax;

  CMathConstantParameter * p;
  CCopasiVector< CReaction::CId2Param > * ParamList;
  for (i = 0; i < imax; i++)
    {
      ParamList = &List[i]->getId2Parameters();
      jmax = ParamList->size();

      for (j = 0; j < jmax; j++)
        {
          p = new CMathConstantParameter(*(*ParamList)[j], List[i]->getName());
          mConstantsList[p->getName()] = p;
        }
    }

  Success = CMathConstantParameter::buildSelection(mpModel);

  return Success;
}

bool CMathModel::compileCompartmentList()
{
  bool Success = true;

  std::map< std::string, CMathConstantCompartment * >::iterator it =
    mCompartmentList.begin();
  std::map< std::string, CMathConstantCompartment * >::iterator end =
    mCompartmentList.end();

  for (; it != end; it++)
    if (!it->second->compile()) Success = false;

  return Success;
}

bool CMathModel::compileMetabList()
{
  bool Success = true;

  std::map< std::string, CMathVariableMetab * >::iterator it =
    mMetabList.begin();
  std::map< std::string, CMathVariableMetab * >::iterator end =
    mMetabList.end();

  for (; it != end; it++)
    if (!it->second->compile()) Success = false;

  return Success;
}

bool CMathModel::compileFixedMetabList()
{
  bool Success = true;

  std::map< std::string, CMathConstantMetab * >::iterator it =
    mFixedMetabList.begin();
  std::map< std::string, CMathConstantMetab * >::iterator end =
    mFixedMetabList.end();

  for (; it != end; it++)
    if (!it->second->compile()) Success = false;

  return Success;
}

bool CMathModel::clearEqList()
{
  bool Success = true;

  std::vector< CMathEq * >::iterator it = mEqList.begin();
  std::vector< CMathEq * >::iterator end = mEqList.begin();

  for (; it != end; it++)
    pdelete(*it);

  std::map< std::string, CMathVariableMetab * >::iterator itM =
    mMetabList.begin();
  std::map< std::string, CMathVariableMetab * >::iterator endM =
    mMetabList.end();

  for (; itM != endM; itM++)
    itM->second->setEq(NULL);

  return Success;
}

bool CMathModel::buildEqList()
{
  bool Success = true;

  clearEqList();

  unsigned C_INT32 i, imax = mMetabList.size();
  mEqList.resize(imax);

  CMathEq * pEq;

  std::map< std::string, CMathVariableMetab *>::iterator it =
    mMetabList.begin();

  /* Create equation and crossreferences with metabolites */
  for (i = 0; i < imax; i++, it++)
    {
      pEq = new CMathEq;
      pEq->setVariable(it->second);
      it->second->setEq(pEq);
      mEqList[i] = pEq;

      CMathNodeDerivative * pD = new CMathNodeDerivative;
      pD->addChild(new CMathNodeSymbol(CMathSymbol::find(mpModel)));
      pD->addChild(new CMathNodeSymbol(it->second));

      pEq->getLeft().attachNode(pD);
    }

  /* Now loop through all reactions */
  const CCopasiVector< CReaction > & ReactionList = mpModel->getReactions();

  for (i = 0, imax = ReactionList.size(); i < imax; i++)
    {
      const CReaction * pReaction = ReactionList[i];

      /* loop through all participating metabolites */
      const CCopasiVector < CChemEqElement > * ChemEq =
        & pReaction->getChemEq().getBalances();

      unsigned C_INT32 j, jmax;
      for (j = 0, jmax = ChemEq->size(); j < jmax; j++)
        {
          const CMetab * pMetab = &(*ChemEq)[j]->getMetabolite();

          /* skip fixed metabolites */
          if (pMetab->getStatus() == CMetab::METAB_FIXED) continue;

          CMathNodeFunction * pFunction = createFunction(pReaction);
          CMathNode * pScalingFactor = createScalingFactor(pReaction);
          CMathNodeOperation * pComponent =
            createComponent((*ChemEq)[j],
                            pScalingFactor,
                            pFunction);

          CCopasiTree< CMathNode > & Tree =
            ((CMathVariable *) CMathSymbol::find(pMetab))->getEq()->getRight();

          CMathNode * pChild = (CMathNode *) Tree.getRoot()->getChild();
          if (pChild)
            {
              CMathNodeOperation * pNew = new CMathNodeOperation("+");
              pNew->addChild(pComponent);
              Tree.attachNode(pNew);
              Tree.moveNode(pChild, pNew, pNew);
            }
          else
            Tree.attachNode(pComponent);
        }
    }

  return Success;
}

CMathNodeFunction * CMathModel::createFunction(const CReaction * pReaction)
{
  CMathNodeFunction * pF =
    new CMathNodeFunction(CMathSymbol::find(&pReaction->getFunction()));

  CMathNodeList * pL = new CMathNodeList();
  CMathNodeList * pV;

  pF->addChild(pL);

  const CFunctionParameters & Description =
    pReaction->getFunction().getParameters();
  const CCallParameterPointers & Objects = pReaction->getCallParameterObjects();

  unsigned C_INT32 i, imax = Description.size();
  unsigned C_INT32 j, jmax;

  for (i = 0; i < imax; i++)
    {
      if (Description[i]->getType() < CFunctionParameter::VINT32)
        pL->addChild(new CMathNodeSymbol(CMathSymbol::find((CCopasiObject *)Objects[i])));
      else
        {
          pV = new CMathNodeList();
          pL->addChild(pV);

          std::vector< CCopasiObject * > * V =
            (std::vector< CCopasiObject * > *) Objects[i];

          jmax = V->size();

          for (j = 0; j < jmax; j++)
            pV->addChild(new CMathNodeSymbol(CMathSymbol::find((*V)[j])));
        }
    }

  return pF;
}

CMathNodeOperation *
CMathModel::createComponent(const CChemEqElement * pElement,
                            CMathNode * pScalingFactor,
                            CMathNodeFunction * pFunction)
{
  CMathNodeOperation * pC = new CMathNodeOperation("*");

  pC->addChild(new CMathNodeNumber(pElement->getMultiplicity()));
  pC->addChild(pScalingFactor);

  CMathNodeOperation * pNew = new CMathNodeOperation("*");
  pNew->addChild(pC);
  pC = pNew;

  pC->addChild(pFunction);

  return pC;
}

CMathNode * CMathModel::createScalingFactor(const CReaction * pReaction)
{
  CMathNode * pS;
  if (pReaction->getCompartmentNumber() == 1)
    {
      pS = new CMathNodeOperation("*");
      pS->addChild(new CMathNodeSymbol(mpConversionFactor));

      const CCopasiObject * pObject =
        pReaction->getChemEq().getBalances()[0]->getMetabolite().getCompartment();

      pS->addChild(new CMathNodeSymbol(CMathSymbol::find(pObject)));
    }

  else
    pS = new CMathNodeNumber(mpConversionFactor->getValue());

  return pS;
}
