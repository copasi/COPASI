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

#include "CUnitInterfaceSBML.h"
#include <sbml/Model.h>

CUnitInterfaceSBML::CUnitInterfaceSBML(Model * model, bool unitsFromModel)
    : mAssumeDimensionlessOne(false)
{
  initializeDefaultUnits();
  initializeFromSBMLModel(model, unitsFromModel);
}

void CUnitInterfaceSBML::initializeDefaultUnits()
{
  UnitDefinition tmpTime;
  Unit tmpUnitTime(UNIT_KIND_SECOND);
  tmpTime.addUnit(&tmpUnitTime);
  mSBMLTimeUnit = CUnitInformation(&tmpTime, CUnitInformation::DEFAULT);

  UnitDefinition tmpAmount;
  Unit tmpUnitAmount(UNIT_KIND_MOLE);
  tmpAmount.addUnit(&tmpUnitAmount);
  mSBMLAmountUnit = CUnitInformation(&tmpAmount, CUnitInformation::DEFAULT);

  UnitDefinition tmpVol;
  Unit tmpUnitVol(UNIT_KIND_LITRE);
  tmpVol.addUnit(&tmpUnitVol);
  mSBMLVolumeUnit = CUnitInformation(&tmpVol, CUnitInformation::DEFAULT);

  UnitDefinition tmpAr;
  Unit tmpUnitAr(UNIT_KIND_METRE, 2);
  tmpAr.addUnit(&tmpUnitAr);
  mSBMLAreaUnit = CUnitInformation(&tmpAr, CUnitInformation::DEFAULT);

  UnitDefinition tmpL;
  Unit tmpUnitL(UNIT_KIND_METRE);
  tmpL.addUnit(&tmpUnitL);
  mSBMLLengthUnit = CUnitInformation(&tmpL, CUnitInformation::DEFAULT);

  mSBMLConflictUnit = CUnitInformation(CUnitInformation::UNKNOWN, true);
}

void CUnitInterfaceSBML::initializeFromSBMLModel(Model* model, bool unitsFromModel)
{
  if (!model) return;

  mpModel = model;

  //initialize global units
  if (unitsFromModel)
    {
      if (model->getUnitDefinition("time"))
        mSBMLTimeUnit = CUnitInformation(model->getUnitDefinition("time"), CUnitInformation::GLOBAL);

      if (model->getUnitDefinition("substance"))
        mSBMLAmountUnit = CUnitInformation(model->getUnitDefinition("substance"), CUnitInformation::GLOBAL);

      if (model->getUnitDefinition("volume"))
        mSBMLVolumeUnit = CUnitInformation(model->getUnitDefinition("volume"), CUnitInformation::GLOBAL);

      if (model->getUnitDefinition("area"))
        mSBMLAreaUnit = CUnitInformation(model->getUnitDefinition("area"), CUnitInformation::GLOBAL);

      if (model->getUnitDefinition("length"))
        mSBMLLengthUnit = CUnitInformation(model->getUnitDefinition("length"), CUnitInformation::GLOBAL);
    }

  mSBMLObjectsMap.clear();

  //initialize list of species
  unsigned int i;

  for (i = 0; i < model->getNumSpecies(); i++)
    {
      Species * s = model->getSpecies(i);

      if (unitsFromModel && s->isSetUnits())
        mSBMLObjectsMap[s->getId()] = CUnitInformation(s->getDerivedUnitDefinition(), CUnitInformation::PROVIDED);
      else //take info from global units
        {
          if (s->getHasOnlySubstanceUnits())
            mSBMLObjectsMap[s->getId()] = mSBMLAmountUnit;
          else //concentration
            {
              CUnit tmp;
              Compartment* comp = model->getCompartment(s->getCompartment());

              if (!comp)
                {
                  mSBMLObjectsMap[s->getId()] = mSBMLConflictUnit;
                  continue;
                }

              switch (comp->getSpatialDimensions())
                {
                  case 0:
                    break;
                  case 1:
                    tmp = mSBMLLengthUnit;
                    break;
                  case 2:
                    tmp = mSBMLAreaUnit;
                    break;
                  case 3:
                    tmp = mSBMLVolumeUnit;
                    break;
                  default:
                    break;
                };

              tmp.invert();

              tmp.multiply(mSBMLAmountUnit);

              mSBMLObjectsMap[s->getId()] = CUnitInformation(tmp, CUnitInformation::GLOBAL);

              //TODO: it should be DEFAULT rather than GLOBAL if both amount unit and size unit are DEFAULT.
            }
        }
    }

  //initialize list of compartments
  for (i = 0; i < model->getNumCompartments(); i++)
    {
      Compartment *c = model->getCompartment(i);

      if (unitsFromModel && c->isSetUnits())
        mSBMLObjectsMap[c->getId()] = CUnitInformation(c->getDerivedUnitDefinition(), CUnitInformation::PROVIDED);
      else //take info from global units
        {
          CUnitInformation tmp;

          switch (c->getSpatialDimensions())
            {
              case 0:
                break;
              case 1:
                tmp = mSBMLLengthUnit;
                break;
              case 2:
                tmp = mSBMLAreaUnit;
                break;
              case 3:
                tmp = mSBMLVolumeUnit;
                break;
              default:
                break;
            };

          mSBMLObjectsMap[c->getId()] = tmp;
        }
    }

  //initialize list of global parameters
  for (i = 0; i < model->getNumParameters(); i++)
    {
      Parameter *p = model->getParameter(i);

      if (unitsFromModel && p->isSetUnits())
        mSBMLObjectsMap[p->getId()] = CUnitInformation(p->getDerivedUnitDefinition(),
                                      CUnitInformation::PROVIDED);
      else
        mSBMLObjectsMap[p->getId()] = CUnitInformation(CUnitInformation::UNKNOWN);
    }

  //initialize list of local parameters
  mSBMLLocalParametersMap.clear();
  unsigned int j;

  for (j = 0; j < model->getNumReactions(); j++)
    {
      Reaction * reaction = model->getReaction(j);
      std::map<std::string, CUnitInformation> tmpMap;

      for (i = 0; i < reaction->getKineticLaw()->getNumParameters(); i++)
        {
          Parameter *p = reaction->getKineticLaw()->getParameter(i);

          if (unitsFromModel && p->isSetUnits())
            {
              //tmpMap[p->getId()]=CUnitInformation(p->getDerivedUnitDefinition(), CUnitInformation::PROVIDED);
              UnitDefinition* tmpUD = model->getUnitDefinition(p->getUnits());

              if (tmpUD)
                tmpMap[p->getId()] = CUnitInformation(tmpUD, CUnitInformation::PROVIDED);
              else
                {
                  //this is just a workaround
                  if (p->getUnits() == "dimensionless")
                    {
                      tmpMap[p->getId()] = CUnitInformation(CUnitInformation::PROVIDED);
                    }
                  else
                    {
                      tmpMap[p->getId()] = CUnitInformation(CUnitInformation::UNKNOWN);
                      std::cout << "Could not resolve unit ID " << p->getUnits()  << " for " <<  p->getId() << std::endl;
                      //TODO
                    }
                }
            }
          else //take info from global units
            tmpMap[p->getId()] = CUnitInformation(CUnitInformation::UNKNOWN);
        }

      mSBMLLocalParametersMap[reaction->getId()] = tmpMap;
    }

  //determine units of stoichiometries

  //**** generate list of all mathematical expressions that need to be considered

  mSBMLExpressions.resize(0);

  //stoichiometry math TODO

  //kinetic laws
  //construct the units for amount/time (for kinetic laws)
  CUnitInformation amountPerTimeUnit = mSBMLTimeUnit;
  amountPerTimeUnit.invert();
  amountPerTimeUnit.multiply(mSBMLAmountUnit);

  if (mSBMLAmountUnit.getInfo() != CUnitInformation::DEFAULT)
    amountPerTimeUnit.setInfo(CUnitInformation::GLOBAL);

  for (i = 0; i < model->getNumReactions(); i++)
    {
      Reaction * reaction = model->getReaction(i);

      if (!reaction->getKineticLaw()) continue;

      if (!reaction->getKineticLaw()->isSetMath()) continue;

      CExpressionInformation tmp;
      tmp.mTypeDescription = "Kinetic Law";
      tmp.mObjectDisplayString = reaction->isSetName() ? reaction->getName() : reaction->getId();
      tmp.mpExpression = reaction->getKineticLaw()->getMath();
      tmp.mRootUnit = amountPerTimeUnit;
      tmp.mReactionId = reaction->getId();
      mSBMLExpressions.push_back(tmp);
    }

  //rate rules
  //assignment rules
  //algebraic rules
  for (i = 0; i < model->getNumRules(); i++)
    {
      Rule* rule = model->getRule(i);

      if (!rule->isSetMath()) continue;

      CExpressionInformation tmp;
      tmp.mpExpression = rule->getMath();

      if (rule->isRate())
        {
          tmp.mTypeDescription = "Rate rule";
          tmp.mObjectDisplayString = rule->getVariable(); //TODO
          tmp.mRootObject = rule->getVariable();
          tmp.mPerTime = true;
        }
      else if (rule->isAssignment())
        {
          tmp.mTypeDescription = "Assignment rule";
          tmp.mObjectDisplayString = rule->getVariable(); //TODO
          tmp.mRootObject = rule->getVariable();
          tmp.mPerTime = false;
        }
      else if (rule->isAlgebraic())
        {
          tmp.mTypeDescription = "Algebraic rule";
          //nothing to be done. UNKNOWN is the default for a CUnitInformation
          //tmp.mRootUnit=UNKNOWN;
        }

      mSBMLExpressions.push_back(tmp);
    }

  //Events
  for (i = 0; i < model->getNumEvents(); i++)
    {
      //std::cout << "Event" << std::endl;
      Event* event = model->getEvent(i);

      //trigger
      if (event->isSetTrigger() && event->getTrigger()->isSetMath())
        {
          //std::cout << "  event trigger" << std::endl;
          CExpressionInformation tmp;
          tmp.mTypeDescription = "Event trigger";
          tmp.mObjectDisplayString = event->isSetName() ? event->getName() : event->getId();
          tmp.mpExpression = event->getTrigger()->getMath();
          mSBMLExpressions.push_back(tmp);
        }

      //delay
      if (event->isSetDelay() && event->getDelay()->isSetMath())
        {
          //std::cout << "  event delay" << std::endl;
          CExpressionInformation tmp;
          tmp.mTypeDescription = "Event delay";
          tmp.mObjectDisplayString = event->isSetName() ? event->getName() : event->getId();
          tmp.mpExpression = event->getDelay()->getMath();
          tmp.mRootUnit = mSBMLTimeUnit;
          mSBMLExpressions.push_back(tmp);
        }

      //event assignments
      for (j = 0; j < event->getNumEventAssignments(); ++j)
        {
          EventAssignment* ea = event->getEventAssignment(j);

          if (ea->isSetMath())
            {
              //std::cout << "  event assignment" << std::endl;
              CExpressionInformation tmp;
              tmp.mTypeDescription = "Event assignment";
              tmp.mObjectDisplayString = ea->getVariable(); //TODO
              tmp.mpExpression = ea->getMath();
              tmp.mRootObject = ea->getVariable();
              tmp.mPerTime = false;
              mSBMLExpressions.push_back(tmp);
            }
        }
    }

  //initial assignments

  //constraints?

  mSBMLNumbersMap.clear();
  calculateStatistics();
}

void CUnitInterfaceSBML::writeBackToModel()
{
  //**** global objects *****

  //species
  unsigned int i;

  //do nothing for level 2 since the species units are never unknown
  // for (i = 0; i < mpModel->getNumSpecies(); i++)
  //   {
  //     Species * s = mpModel->getSpecies(i);
  //}

  //compartments
  //do nothing for level 2 since the compartment units are never unknown

  //global parameters
  for (i = 0; i < mpModel->getNumParameters(); i++)
    {
      Parameter *p = mpModel->getParameter(i);
      CUnitInformation * tmp = getMappedUnitFromIdentifier(p->getId(), CEnvironmentInformation());

      //if the unit could be derived and it does not contain a symbolic exponent
      if (tmp && tmp->getInfo() == CUnitInformation::DERIVED && tmp->getSymbolicExpExp() == 0)
        {
          //first try to find an equivalent unit in the model
          unsigned int j;

          for (j = 0; j < mpModel->getNumUnitDefinitions(); ++j)
            if (UnitDefinition::areEquivalent(&tmp->getSBMLUnitDefinition(), mpModel->getUnitDefinition(j)))
              break;

          if (j < mpModel->getNumUnitDefinitions())
            p->setUnits(mpModel->getUnitDefinition(j)->getId());
          else
            {
              //we have to create a new unit definition in the model
              std::string tmpstring;
              unsigned int id = 0;

              do
                {
                  std::ostringstream tmpid; tmpid << "unit_" << id;
                  tmpstring = tmpid.str();
                  ++id;
                }
              while (mpModel->getUnitDefinition(tmpstring));

              tmp->getSBMLUnitDefinition().setId(tmpstring);
              tmp->getSBMLUnitDefinition().unsetName();
              tmp->getSBMLUnitDefinition().unsetMetaId();
              tmp->getSBMLUnitDefinition().unsetNotes();
              tmp->getSBMLUnitDefinition().unsetAnnotation();
              tmp->getSBMLUnitDefinition().unsetSBOTerm();
              mpModel->addUnitDefinition(&tmp->getSBMLUnitDefinition());
              p->setUnits(tmpstring);
            }
        }
    }

  //local parameters
  unsigned int j;

  for (j = 0; j < mpModel->getNumReactions(); j++)
    {
      Reaction * reaction = mpModel->getReaction(j);

      for (i = 0; i < reaction->getKineticLaw()->getNumParameters(); i++)
        {
          Parameter *p = reaction->getKineticLaw()->getParameter(i);

          CUnitInformation * tmp = getMappedUnitFromIdentifier(p->getId(), CEnvironmentInformation(reaction->getId()));
          //TODO this could be easier directly from the map instead of using getMappedUnitFromIdentifier()

          //if the unit could be derived and it does not contain a symbolic exponent
          if (tmp && tmp->getInfo() == CUnitInformation::DERIVED && tmp->getSymbolicExpExp() == 0)
            {
              //first try to find an equivalent unit in the model
              unsigned int j;

              for (j = 0; j < mpModel->getNumUnitDefinitions(); ++j)
                if (UnitDefinition::areEquivalent(&tmp->getSBMLUnitDefinition(), mpModel->getUnitDefinition(j)))
                  break;

              if (j < mpModel->getNumUnitDefinitions())
                p->setUnits(mpModel->getUnitDefinition(j)->getId());
              else
                {
                  //we have to create a new unit definition in the model
                  std::string tmpstring;
                  unsigned int id = 0;

                  do
                    {
                      std::ostringstream tmpid; tmpid << "unit_" << id;
                      tmpstring = tmpid.str();
                      ++id;
                    }
                  while (mpModel->getUnitDefinition(tmpstring));

                  tmp->getSBMLUnitDefinition().setId(tmpstring);
                  tmp->getSBMLUnitDefinition().unsetName();
                  tmp->getSBMLUnitDefinition().unsetMetaId();
                  tmp->getSBMLUnitDefinition().unsetNotes();
                  tmp->getSBMLUnitDefinition().unsetAnnotation();
                  tmp->getSBMLUnitDefinition().unsetSBOTerm();
                  mpModel->addUnitDefinition(&tmp->getSBMLUnitDefinition());
                  p->setUnits(tmpstring);
                }
            }
        }
    }

  //numbers TODO (not possible at the moment)
}

void CUnitInterfaceSBML::calculateStatistics()
{
  //std::vector<unsigned int> frequency_global, frequency_local, frequency_numbers, frequency;
  mStatistics = Statistics();

  //CONFLICT is used as index for a unit conflict.
  const unsigned int CONFLICT = 5;
  mStatistics.global.resize(CONFLICT + 1);
  mStatistics.local.resize(CONFLICT + 1);
  mStatistics.numbers.resize(CONFLICT + 1);
  mStatistics.all.resize(CONFLICT + 1);

  //collect statistics from global objects with units
  std::map<std::string, CUnitInformation>::const_iterator it, itEnd = mSBMLObjectsMap.end();

  for (it = mSBMLObjectsMap.begin(); it != itEnd; ++it)
    {
      if (it->second.isConflict())
        ++mStatistics.global[CONFLICT];
      else
        ++mStatistics.global[it->second.getInfo()];
    }

  //collect statistics from localparameter
  std::map<std::string, std::map<std::string, CUnitInformation> >::const_iterator rit;

  for (rit = mSBMLLocalParametersMap.begin(); rit != mSBMLLocalParametersMap.end(); ++rit)
    {
      for (it = rit->second.begin(); it != rit->second.end(); ++it)
        {
          if (it->second.isConflict())
            ++mStatistics.local[CONFLICT];
          else
            ++mStatistics.local[it->second.getInfo()];
        }
    }

  //collect statistics from numbers
  std::map<const ASTNode*, CUnitInformation>::const_iterator nit, nitEnd = mSBMLNumbersMap.end();

  for (nit = mSBMLNumbersMap.begin(); nit != nitEnd; ++nit)
    {
      if (nit->second.isConflict())
        ++mStatistics.numbers[CONFLICT];
      else
        ++mStatistics.numbers[nit->second.getInfo()];
    }

  unsigned int i;

  for (i = 0; i < mStatistics.all.size(); ++i)
    mStatistics.all[i] = mStatistics.global[i] + mStatistics.local[i] + mStatistics.numbers[i];
}

void CUnitInterfaceSBML::outputStatistics(const Statistics & stat, bool flag)
{
  if (stat.all.size() != 6) return;

  std::cout << "Global: " << "  ? " <<  stat.global[0]
            << "  default " <<  stat.global[1]
            << "  glob " <<  stat.global[2]
            << "  pro " <<  stat.global[3]
            << "  deriv " <<  stat.global[4]
            << (stat.global[5] > 0 ? "  conflict " : " ")  <<  stat.global[5] << std::endl;
  std::cout << "Local:  " << "  ? " <<  stat.local[0]
            << "  default " <<  stat.local[1]
            << "  glob " <<  stat.local[2]
            << "  pro " <<  stat.local[3]
            << "  deriv " <<  stat.local[4]
            << (stat.local[5] > 0 ? "  conflict " : " ")  <<  stat.local[5] << std::endl;
  std::cout << "Numbers:" << "  ? " <<  stat.numbers[0]
            << "  default " <<  stat.numbers[1]
            << "  glob " <<  stat.numbers[2]
            << "  pro " <<  stat.numbers[3]
            << "  deriv " <<  stat.numbers[4]
            << (stat.numbers[5] > 0 ? "  conflict " : " ")  <<  stat.numbers[5] << std::endl;

  if (flag) std::cout << "_";

  std::cout << "Sum    :" << "  ? " <<  stat.all[0]
            << "  default " <<  stat.all[1]
            << "  glob " <<  stat.all[2]
            << "  pro " <<  stat.all[3]
            << "  deriv " <<  stat.all[4]
            << (stat.all[5] > 0 ? "  CONFLICT_SUM " : " ")  <<  stat.all[5] << std::endl;

  if (stat.all[0] == 0)
    std::cout << "***SUCCESS***" << std::endl;
  else
    std::cout << "some unknown units left..." << std::endl;

  //if (stat.all[5]>0)
  //  debugOutput();
}

void CUnitInterfaceSBML::debugOutput() const
{
  std::cout << "global units:" << std::endl;
  std::cout << "Time:        " << mSBMLTimeUnit.getDisplayString() << std::endl;
  std::cout << "Amount:   " << mSBMLAmountUnit.getDisplayString() << std::endl;
  std::cout << "Volume:   " << mSBMLVolumeUnit.getDisplayString() << std::endl;
  std::cout << "Area:        " << mSBMLAreaUnit.getDisplayString() << std::endl;
  std::cout << "Length:    " << mSBMLLengthUnit.getDisplayString() << std::endl;

  std::cout << std::endl;

  std::map<std::string, CUnitInformation>::const_iterator it, itEnd = mSBMLObjectsMap.end();

  for (it = mSBMLObjectsMap.begin(); it != itEnd; ++it)
    {
      std::cout << it->first << "  " <<  it->second.getDisplayString() <<  std::endl;
    }

  std::cout << std::endl;

  std::map<std::string, std::map<std::string, CUnitInformation> >::const_iterator rit;

  for (rit = mSBMLLocalParametersMap.begin(); rit != mSBMLLocalParametersMap.end(); ++rit)
    {
      for (it = rit->second.begin(); it != rit->second.end(); ++it)
        {
          std::cout << rit-> first << "  "
                    << it->first << "  " <<  it->second.getDisplayString() <<  std::endl;
        }
    }

  std::cout << std::endl;
  std::cout << "Expressions: \n\n";
  unsigned int i;

  for (i = 0; i <  mSBMLExpressions.size(); ++i)
    {
      const CExpressionInformation& tmp = mSBMLExpressions[i];
      std::cout << std::string(SBML_formulaToString(tmp.mpExpression)) << "  ::  "
                << (tmp.mPerTime ? "per time" : "") << " "
                << tmp.mRootObject << " ";

      if (tmp.mReactionId != "")
        std::cout << "env:" << tmp.mReactionId << " ";

      if (tmp.mRootObject == "")
        std::cout << tmp.mRootUnit.getDisplayString();

      if (tmp.mErrorCode) std::cout << "Conflict: " << tmp.mErrorCode;

      std::cout << std::endl;
    }
}

void CUnitInterfaceSBML::determineUnits()
{
  if (!mpModel) return;

  //first a very crude implementation... TODO
  std::vector<CExpressionInformation>::iterator it, itEnd = mSBMLExpressions.end();
  unsigned int count;

  for (count = 0; count < 3; ++count)
    {
      for (it = mSBMLExpressions.begin(); it != itEnd; ++it)
        {
          //debug
          if (false)
            {
              const CExpressionInformation& tmp = *it;
              std::cout << std::string(SBML_formulaToString(tmp.mpExpression)) << "  ::  "
                        << (tmp.mPerTime ? "per time" : "") << " "
                        << tmp.mRootObject << " ";

              if (tmp.mReactionId != "")
                std::cout << "env:" << tmp.mReactionId << " ";

              if (tmp.mRootObject == "")
                std::cout << tmp.mRootUnit.getDisplayString();

              std::cout << std::endl;
            }

          //if (it->mObjectDisplayString=="Glucose-1-phosphate adenyltransferase")
          //  std::cout << "hit!" << std::endl;

          handleOneExpression(*it);
        }
    }

  calculateStatistics();
}

void CUnitInterfaceSBML::handleOneExpression(CExpressionInformation & ei)
{
  mError = 0;
  CEnvironmentInformation environment;

  if (ei.mRootObject == "")
    {
      //set the environment (for local parameters)
      environment.mReactionID = ei.mReactionId;

      //call recursive evaluation
      recursion(ei.mpExpression, ei.mRootUnit, environment);
    }
  else
    {
      /*      if (ei.mPerTime)
              {
                std::cout << "rate rules" << std::endl;
              }*/
      CUnitInformation * pNodeUnit = getMappedUnitFromIdentifier(ei.mRootObject, environment);

      if (!pNodeUnit) return;

      CUnitInformation sourceUnit = *pNodeUnit;

      if (ei.mPerTime && sourceUnit.getInfo() > CUnitInformation::UNKNOWN)
        {//devide unit of rule target by time
          //std::cout << "rate rule enter" << std::endl;
          CUnitInformation invTime = mSBMLTimeUnit;
          invTime.invert();
          sourceUnit.multiply(invTime);
        }

      CUnitInformation tmp = recursion(ei.mpExpression, sourceUnit, environment);
      //tmp.setStatus()

      if (ei.mPerTime && tmp.getInfo() > CUnitInformation::UNKNOWN)
        {//multiply unit of the rate rule expression by time
          tmp.multiply(mSBMLTimeUnit);
          //std::cout << "rate rule return" << std::endl;
        }

      handleTerminalNode(tmp, pNodeUnit);
    }

  //TODO handle mpRootObject case

  if (mError > ei.mErrorCode) ei.mErrorCode = mError;
}

//*********************************************************************************

//#define UNIT_DEBUG

CUnitInformation CUnitInterfaceSBML::recursion(const ASTNode* node,
    const CUnitInformation & ui,
    const CEnvironmentInformation & ei)
{
#ifdef UNIT_DEBUG
  std::cout << "recursion: " << ui.getDisplayString() << std::endl;
#endif

  CUnitInformation ret;

  if (!node) return ret;

  //handle delay first since it is unclear from the documentation in which class of nodes it is included
  if (node->getType() == AST_FUNCTION_DELAY)
    {
      if (node->getNumChildren() != 2)
        return ret;

      CUnitInformation tmpTimeUnit = mSBMLTimeUnit;
      recursion(node->getChild(1), tmpTimeUnit, ei); //second child should have time units
      return recursion(node->getChild(0), ui, ei); //first child has the same units as the parent
    }

  //object node
  if (isObject(node))
    {
      //time nodes
      if (node->getType() == AST_NAME_TIME)
        {
          //TODO: does not work???
          //std::cout << "time" << std::endl;
          CUnitInformation tmpTimeUnit = mSBMLTimeUnit;
          return handleTerminalNode(ui, &tmpTimeUnit);
        }

      //check if the object is a function variable
      ASTNode* variable = resolveVariableName(getIdentifier(node), ei);

      if (variable)
        {
          //drop one level from the environment stack
          CEnvironmentInformation tmpIE = ei;
          tmpIE.drop();
          return recursion(variable, ui, tmpIE);
        }

      //now it should be certain that the object is a reference to an sbml object with a mapped unit.
      CUnitInformation * pNodeUnit = getMappedUnitFromIdentifier(getIdentifier(node), ei);

      if (!pNodeUnit) return mSBMLConflictUnit;

      //if (getIdentifier(node)=="PIP2_PM") for debugging...
      //  std::cout << getIdentifier(node)<< std::endl;

      return handleTerminalNode(ui, pNodeUnit);
    }//is object node

  //number node
  else if (isNumber(node))
    {
      CUnitInformation* pNodeUnit;
      pNodeUnit = &mSBMLNumbersMap[node];

//       //check if the node is already in the map
//       std::map<const ASTNode*, CUnitInformation>::iterator it = mSBMLNumbersMap.find(node);
//       if (it != mSBMLNumbersMap.end())
//         pNodeUnit=&it->second;
//       else //create new entry in the map
//         {
//           pNodeUnit=&mSBMLNumbersMap[node];
//}

      if (mAssumeDimensionlessOne)
        {
          if (getValueFromNumberNode(node) == 1.0 || getValueFromNumberNode(node) == -1.0)
            pNodeUnit->setInfo(CUnitInformation::DERIVED);
        }

      return handleTerminalNode(ui, pNodeUnit);
    }

  //operator node
  else if (isOperator(node))
    {
      switch (node->getType())
        {
          case AST_PLUS:
          case AST_MINUS:
          case AST_RELATIONAL_EQ:
          case AST_RELATIONAL_GEQ:
          case AST_RELATIONAL_GT:
          case AST_RELATIONAL_LEQ:
          case AST_RELATIONAL_LT:
          case AST_RELATIONAL_NEQ:
            return recursionEqual(node, ui, ei);
            break;

          case AST_TIMES:
            return recursionTimes(node, ui, ei);
            break;

          case AST_DIVIDE:
            return recursionDivide(node, ui, ei);
            break;

          case AST_POWER:
          case AST_FUNCTION_POWER:
            return recursionPower(node, ui, ei);
            break;

          default:
            break;
        }
    }

  else if (isFunctionCall(node))
    {
      //std::cout << "function call" << std::endl;
      //check if the object is a function call
      FunctionDefinition *fd = resolveFunctionName(getIdentifier(node));

      if (fd)
        {
          //std::cout << "could resolve function call" << std::endl;
          unsigned int i, numArgs = fd->getNumArguments();
          assert(numArgs == node->getNumChildren());

          //create mapping from variable ID to the node that should be substituted
          std::map<std::string, ASTNode*> tmpMap;

          for (i = 0; i < numArgs; ++i)
            tmpMap[fd->getArgument(i)->getName()] = node->getChild(i);

          //std::cout << i  << fd->getArgument(i)->getName() << std::endl;
          CEnvironmentInformation tmpEI = ei;
          tmpEI.push(tmpMap);
          return recursion(fd->getBody(), ui, tmpEI);
        }
    }

  else if (isBuiltInFunctionCall(node))
    {
      //std::cout << "built in function" << std::endl;
      switch (node->getType())
        {
          case AST_FUNCTION_ARCCOS:
          case AST_FUNCTION_ARCCOSH:
          case AST_FUNCTION_ARCCOT:
          case AST_FUNCTION_ARCCOTH:
          case AST_FUNCTION_ARCCSC:
          case AST_FUNCTION_ARCCSCH:
          case AST_FUNCTION_ARCSEC:
          case AST_FUNCTION_ARCSECH:
          case AST_FUNCTION_ARCSIN:
          case AST_FUNCTION_ARCSINH:
          case AST_FUNCTION_ARCTAN:
          case AST_FUNCTION_ARCTANH:

          case AST_FUNCTION_COS:
          case AST_FUNCTION_COSH:
          case AST_FUNCTION_COT:
          case AST_FUNCTION_COTH:
          case AST_FUNCTION_CSC:
          case AST_FUNCTION_CSCH:
          case AST_FUNCTION_SEC:
          case AST_FUNCTION_SECH:
          case AST_FUNCTION_SIN:
          case AST_FUNCTION_SINH:
          case AST_FUNCTION_TAN:
          case AST_FUNCTION_TANH:

          case AST_FUNCTION_EXP:
          case AST_FUNCTION_FACTORIAL:
          case AST_FUNCTION_LN:
          case AST_FUNCTION_LOG:
            recursion(node->getChild(0), CUnitInformation(CUnitInformation::DEFAULT), ei);
            return CUnitInformation(CUnitInformation::DEFAULT);
            break;

          case AST_FUNCTION_CEILING:
          case AST_FUNCTION_FLOOR:
          case AST_FUNCTION_ABS:
            return recursion(node->getChild(0), ui, ei);
            break;

          default:
            break;
        }
    }

  switch (node->getType())
    {
      case AST_CONSTANT_E:
      case AST_CONSTANT_PI:
        return  CUnitInformation(CUnitInformation::DEFAULT);
        break;

      case AST_FUNCTION_PIECEWISE:
        return recursionPiecewise(node, ui, ei);

      default:
        break;
    }

  //TODO numbers, functions, calls, variables, choice, delay, time, ...
  //logicals (comparison operators), constants (pi, ...),  ...

  //std::cout << "not handled " << node->getType() << std::endl;

  //fallback: just to make sure the whole tree is covered
  unsigned int i, numChildren = node->getNumChildren();

  for (i = 0; i < numChildren; ++i)
    recursion(node->getChild(i), CUnitInformation(CUnitInformation::UNKNOWN), ei);

  return ret;
}

CUnitInformation CUnitInterfaceSBML::handleTerminalNode(const CUnitInformation & ui, CUnitInformation *pNodeUnit)
{
#ifdef UNIT_DEBUG
  std::cout << "terminal: assign " << ui.getDisplayString() << "  to " << pNodeUnit->getDisplayString() <<  std::endl;
#endif
  //TODO handle case where conflict flag is set bfore

  if (ui.getInfo() == CUnitInformation::UNKNOWN)
    {
      return *pNodeUnit;
    }
  else if (pNodeUnit->getInfo() == CUnitInformation::UNKNOWN)
    {
      *pNodeUnit = ui;
      pNodeUnit->setInfo(CUnitInformation::DERIVED);
      return *pNodeUnit;
    }
  else //both are known
    {
      //check for conflict
      if (CUnit::isEqual(ui, *pNodeUnit))
        return ui;
      else //there is a conflict
        {
          //std::cout << ui.getDisplayString() << "   " << pNodeUnit->getDisplayString() << std::endl;
          if (ui.getInfo() < pNodeUnit->getInfo())  //the new unit is more reliable
            {
              *pNodeUnit = ui;
              pNodeUnit->setInfo(CUnitInformation::DERIVED);
            }

          if (!pNodeUnit->isConflict())
            if (1 > mError) mError = 1; //only report the conflict for this expression if it was not known before

          pNodeUnit->setConflict(true);
          return *pNodeUnit;
        }
    }
}

CUnitInformation CUnitInterfaceSBML::recursionEqual(const ASTNode* node,
    const CUnitInformation & ui,
    const CEnvironmentInformation & ei)
{
  CUnitInformation ret;

  if (!node) return ret;

  ret = ui;

  //TODO deal with conflicts

  unsigned int i, numChildren = node->getNumChildren();
  std::vector<CUnitInformation> childUnits;
  childUnits.resize(numChildren);
  //std::cout << "+ " << numChildren << std::endl;

  //first deal with the unit that is passed from above
  if (ui.getInfo() > CUnitInformation::UNKNOWN)
    {
      //pass the unit to all child nodes
      for (i = 0; i < numChildren; ++i)
        childUnits[i] = recursion(node->getChild(i), ui, ei);
    }
  else
    {
      //the unit passed from above is unknown. Check if one of the children has a known unit
      for (i = 0; i < numChildren; ++i)
        {
          childUnits[i] = recursion(node->getChild(i), ui, ei);

          if (childUnits[i].getInfo() > CUnitInformation::UNKNOWN)
            break;
        }

      if (i >= numChildren)
        return ret; //do nothing if all units are unknown

      // i is now the index of the first child with known units
      // pass this unit information to the return value and all other children
      unsigned int tmp = i;
      ret = childUnits[tmp];

      for (i = 0; i < numChildren; ++i)
        {
          if (i == tmp) continue;

          childUnits[i] = recursion(node->getChild(i), ret, ei);
        }
    }

  //TODO deal with conflicts: if any conflict occured, pass conflict to all children and ret

  return ret;
}

CUnitInformation CUnitInterfaceSBML::recursionTimes(const ASTNode* node,
    const CUnitInformation & ui,
    const CEnvironmentInformation & ei)
{
  CUnitInformation ret;

  if (!node) return ret;

  ret = ui;

  //TODO deal with conflicts

  unsigned int i, numChildren = node->getNumChildren();
  std::vector<CUnitInformation> childUnits;
  childUnits.resize(numChildren);
  //std::cout << "* " << numChildren << std::endl;

  // ask all children for their unit
  std::vector<int> unknown;
  CUnitInformation uu; //unknown units

  for (i = 0; i < numChildren; ++i) //TODO should stop when we know enough
    {
      childUnits[i] = recursion(node->getChild(i), uu, ei);

      if (childUnits[i].getInfo() == CUnitInformation::UNKNOWN)
        unknown.push_back(i);
    }

  //first the case where the parent unit is unknown
  if (ui.getInfo() == CUnitInformation::UNKNOWN)
    {
      //if there are children with unknown units we can do nothing
      if (unknown.size() > 0)
        return ret;

      //determine the units for the parent
      ret = childUnits[0];
      bool success = true;

      for (i = 1; i < numChildren; ++i)
        success &= ret.multiply(childUnits[i]);

      if (success)
        ret.setInfo(CUnitInformation::DERIVED);
      else
        ret.setInfo(CUnitInformation::UNKNOWN);
    }
  else //parent units are known
    {
      //if there is more than one child with unknown units we can do nothing
      if (unknown.size() > 1)
        return ret;

      //if no child has unknown units assume the first (and check for conflicts later)
      unsigned int tmp = unknown.size() ? unknown[0] : 0;

      //determine units
      CUnitInformation tmpUnit;
      bool success = true;

      for (i = 0; i < numChildren; ++i)
        if (i != tmp)
          success &= tmpUnit.multiply(childUnits[i]);

      tmpUnit.invert();
      success &= tmpUnit.multiply(ui);

      if (success)
        tmpUnit.setInfo(CUnitInformation::DERIVED);
      else
        tmpUnit.setInfo(CUnitInformation::UNKNOWN);

      //tell child about derived unit
      childUnits[tmp] = recursion(node->getChild(tmp), tmpUnit, ei);
      //TODO check for conflicts
    }

  return ret;
}

CUnitInformation CUnitInterfaceSBML::recursionDivide(const ASTNode* node,
    const CUnitInformation & ui,
    const CEnvironmentInformation & ei)
{
  CUnitInformation ret;

  if (!node) return ret;

  ret = ui;

  //TODO deal with conflicts

  unsigned int i, numChildren = node->getNumChildren();
  assert(numChildren == 2);
  std::vector<CUnitInformation> childUnits;
  childUnits.resize(numChildren);
  //std::cout << "/ " << numChildren << std::endl;

  // ask all children for their unit
  std::vector<int> unknown;
  CUnitInformation uu; //unknown units

  for (i = 0; i < numChildren; ++i)
    {
      childUnits[i] = recursion(node->getChild(i), uu, ei);

      if (childUnits[i].getInfo() == CUnitInformation::UNKNOWN)
        unknown.push_back(i);
    }

  //first the case where the parent unit is unknown
  if (ui.getInfo() == CUnitInformation::UNKNOWN)
    {
      //if there are children with unknown units we can do nothing
      if (unknown.size() > 0)
        return ret;

      //determine the units for the parent
      ret = childUnits[1];
      bool success = true;
      ret.invert();
      success &= ret.multiply(childUnits[0]);

      if (success)
        ret.setInfo(CUnitInformation::DERIVED);
      else
        ret.setInfo(CUnitInformation::UNKNOWN);
    }
  else
    {
      //if there is more than one child with unknown units we can do nothing
      if (unknown.size() > 1)
        return ret;

      //case where nominator is unknown (or assumed unknown)
      if (unknown.size() == 0 || unknown[0] == 0)
        {
          //determine units
          CUnitInformation tmpUnit = childUnits[1];
          bool success = true;
          success &= tmpUnit.multiply(ui);

          if (success)
            tmpUnit.setInfo(CUnitInformation::DERIVED);
          else
            tmpUnit.setInfo(CUnitInformation::UNKNOWN);

          //tell child about derived unit
          childUnits[0] = recursion(node->getChild(0), tmpUnit, ei);
          //TODO check for conflicts
        }
      else //denominator is unknown
        {
          //determine units
          CUnitInformation tmpUnit = ui;
          bool success = true;
          tmpUnit.invert();
          success &= tmpUnit.multiply(childUnits[0]);

          //tmpUnit.multiply(ui);
          if (success)
            tmpUnit.setInfo(CUnitInformation::DERIVED);
          else
            tmpUnit.setInfo(CUnitInformation::UNKNOWN);

          //tell child about derived unit
          childUnits[1] = recursion(node->getChild(1), tmpUnit, ei);
        }
    }

  return ret;
}

CUnitInformation CUnitInterfaceSBML::recursionPower(const ASTNode* node,
    const CUnitInformation & ui,
    const CEnvironmentInformation & ei)
{
  CUnitInformation ret;

  if (!node) return ret;

  ret = ui;

#ifdef UNIT_DEBUG
  std::cout << "power: " << ui.getDisplayString() << std::endl;
#endif
  unsigned int numChildren = node->getNumChildren();
  assert(numChildren == 2);
  std::vector<CUnitInformation> childUnits;
  childUnits.resize(numChildren);

  //the exponent should always be dimensionless
  childUnits[1] = recursion(node->getChild(1), CUnitInformation(CUnitInformation::DEFAULT), ei);

  //try to evaluate the exponent
  EvaluationResult res = evaluate(node->getChild(1));

  if (res.known) //the base of the power could be evaluated
    {
      //check if the exponent is integer
      if (fabs(res.result - floor(res.result + 0.5)) < 1e-100)
        {
          //std::cout << "fixed exponent is integer" << std::endl;
          int intExp = (int) floor(res.result + 0.5);

          if (ui.getInfo() == CUnitInformation::UNKNOWN)
            {
              childUnits[0] = recursion(node->getChild(0), CUnitInformation(CUnitInformation::UNKNOWN), ei);
              ret = childUnits[0];

              if (ret.getInfo() > CUnitInformation::UNKNOWN)
                {//only if the base is known, we can make use of the exponent to calculate the return unit
                  ret.applyExponent(intExp);
                  ret.setInfo(CUnitInformation::DERIVED);
                }
            }
          else
            {
              CUnitInformation tmpUI = ui;
              tmpUI.applyExponent(1 / (double)intExp);
              tmpUI.setInfo(CUnitInformation::DERIVED);
              childUnits[0] = recursion(node->getChild(0), tmpUI, ei);
            }
        }
      else
        {
          //std::cout << "fixed exponent is non integer" << std::endl;
          //TODO perhaps rather conflict???
          childUnits[0] = recursion(node->getChild(0), CUnitInformation(CUnitInformation::UNKNOWN), ei);
        }

      //TODO extend to deal with non integer exponents properly. CUnit needs to support it first.
    }
  else
    {
      //std::cout << "exponent could not be evaluated" << std::endl;
      //the exponent could not be determined as a number

      //special case: exponent is an identifier
      if (node->getChild(1)->isName())
        {
          //std::cout << "exponent is identifier " << node->getChild(1)->getName() <<  std::endl;
          if (ui.getInfo() == CUnitInformation::UNKNOWN)
            {
              childUnits[0] = recursion(node->getChild(0), CUnitInformation(CUnitInformation::UNKNOWN), ei);
              ret = childUnits[0];

              if (ret.getInfo() > CUnitInformation::UNKNOWN)
                {//only if the base is known, we can make use of the exponent to calculate the return unit
                  ret.applyExponent(node->getChild(1)->getName(), ei.mFrameStack.size());
                  ret.setInfo(CUnitInformation::DERIVED);
                }
            }
          else
            {
              CUnitInformation tmpUI = ui;
              tmpUI.applyInverseExponent(node->getChild(1)->getName(), ei.mFrameStack.size());
              tmpUI.setInfo(CUnitInformation::DERIVED);
              childUnits[0] = recursion(node->getChild(0), tmpUI, ei);
            }
        }
      else //exponent is neither a number nor a simple identifier. Units of the base are unknown
        {
          //std::cout << "exponent is: " << std::string(SBML_formulaToString(node->getChild(1))) << std::endl;
          childUnits[0] = recursion(node->getChild(0), CUnitInformation(CUnitInformation::UNKNOWN), ei);
        }
    }

  //heuristics: if the exponent is variable, the base should be dimensionless
  //TODO

  //TODO deal with conflicts

#ifdef UNIT_DEBUG
  std::cout << "  power return   " << ret.getDisplayString() << std::endl;
#endif

  return ret;
}

CUnitInterfaceSBML::EvaluationResult CUnitInterfaceSBML::evaluate(const ASTNode* node)
{
  EvaluationResult ret;
  ret.result = 0;
  ret.known = false;

  //numbers
  if (isNumber(node))
    {
      ret.result = getValueFromNumberNode(node);
      ret.known = true;
    }

  //TODO at least plus, minus, uminus

  return ret;
}

CUnitInformation CUnitInterfaceSBML::recursionPiecewise(const ASTNode* node,
    const CUnitInformation & ui,
    const CEnvironmentInformation & ei)
{
  CUnitInformation ret;

  if (!node) return ret;

  ret = ui;

  //TODO deal with conflicts

  unsigned int i, numChildren = node->getNumChildren();
  std::vector<CUnitInformation> childUnits;
  childUnits.resize(numChildren);
  //std::cout << "+ " << numChildren << std::endl;

  //first do the recursion for the logical parts (the children with uneven index)
  for (i = 1; i < numChildren; i += 2)
    recursion(node->getChild(i), CUnitInformation(CUnitInformation::UNKNOWN), ei);

  //first deal with the unit that is passed from above
  if (ui.getInfo() > CUnitInformation::UNKNOWN)
    {
      //pass the unit to all child nodes
      for (i = 0; i < numChildren; i += 2)
        childUnits[i] = recursion(node->getChild(i), ui, ei);
    }
  else
    {
      //the unit passed from above is unknown. Check if one of the children has a known unit
      for (i = 0; i < numChildren; i += 2)
        {
          childUnits[i] = recursion(node->getChild(i), ui, ei);

          if (childUnits[i].getInfo() > CUnitInformation::UNKNOWN)
            break;
        }

      if (i >= numChildren)
        return ret; //do nothing if all units are unknown

      // i is now the index of the first child with known units
      // pass this unit information to the return value and all other children
      unsigned int tmp = i;
      ret = childUnits[tmp];

      for (i = 0; i < numChildren; i += 2)
        {
          if (i == tmp) continue;

          childUnits[i] = recursion(node->getChild(i), ret, ei);
        }
    }

  //TODO deal with conflicts: if any conflict occured, pass conflict to all children and ret

  return ret;
}

//**************************************************

CUnitInformation* CUnitInterfaceSBML::getMappedUnitFromIdentifier(const std::string & node,
    const CEnvironmentInformation & ei)
{
  //try local parameters
  if (ei.isReactionScope())
    {
      std::map<std::string, std::map<std::string, CUnitInformation> >::iterator rit;
      rit =  mSBMLLocalParametersMap.find(ei.mReactionID);

      if (rit != mSBMLLocalParametersMap.end())
        {
          std::map<std::string, CUnitInformation>::iterator it;
          it = rit->second.find(node);

          if (it != rit->second.end())
            return &it->second;
        }
      else
        {
          //error
        }
    }

  //now global objects
  std::map<std::string, CUnitInformation>::iterator it;
  it = mSBMLObjectsMap.find(node);

  if (it != mSBMLObjectsMap.end())
    return &it->second;

  return NULL;
}

ASTNode* CUnitInterfaceSBML::resolveVariableName(const std::string & node,
    const CEnvironmentInformation & ei)
{
  //TODO find ASTNode corresponding to the variable (from top level of frame stack in ei).
  if (!ei.mFrameStack.size()) return NULL;

  std::map<std::string, ASTNode*>::const_iterator it;
  it = ei.mFrameStack[ei.mFrameStack.size()-1].find(node);

  if (it == ei.mFrameStack[ei.mFrameStack.size()-1].end())
    return NULL;
  else
    return it->second;
}

FunctionDefinition* CUnitInterfaceSBML::resolveFunctionName(const std::string & node)
{
  if (!mpModel) return NULL;

  return mpModel->getFunctionDefinition(node);
}

CUnitInformation* CUnitInterfaceSBML::getMappedUnitFromNumberNode(const ASTNode* node)
{
  //check if the node is in the map
  std::map<const ASTNode*, CUnitInformation>::iterator it = mSBMLNumbersMap.find(node);

  if (it != mSBMLNumbersMap.end())
    return &it->second;
  else
    return NULL;
}

//*************************************************

bool CUnitInterfaceSBML::isObject(const ASTNode* node)
{
  return (node && node->isName());
}

bool CUnitInterfaceSBML::isOperator(const ASTNode* node)
{
  //is this a bug in libsbml that power is a function?
  return (node &&
          (node->isOperator() || node->isRelational() || node->getType() == AST_FUNCTION_POWER));
}

bool CUnitInterfaceSBML::isNumber(const ASTNode* node)
{
  return (node && (node->isNumber() || node->isRational()));
}

bool CUnitInterfaceSBML::isFunctionCall(const ASTNode* node)
{
  return (node && (node->getType() == AST_FUNCTION));
}

bool CUnitInterfaceSBML::isBuiltInFunctionCall(const ASTNode* node)
{
  return (node && (node->getType() > AST_FUNCTION) && (node->getType() <= AST_FUNCTION_TANH));
}

double CUnitInterfaceSBML::getValueFromNumberNode(const ASTNode* node)
{
  if (!node)
    return std::numeric_limits< double >::quiet_NaN();

  switch (node->getType())
    {
      case AST_INTEGER:
        return node->getInteger();
        break;

      case AST_REAL:
      case AST_REAL_E:
      case AST_RATIONAL:
        return node->getReal();
        break;

        //TODO rational number format
      default:
        std::cout << "unsupported number format" << std::endl;
        return std::numeric_limits< double >::quiet_NaN();
    }
}

std::string CUnitInterfaceSBML::getIdentifier(const ASTNode* node)
{
  if (node)
    return node->getName();
  else
    return "";
}
