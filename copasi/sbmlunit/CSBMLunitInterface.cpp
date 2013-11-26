// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Sven Sahle and University of Heidelberg
// All rights reserved.

#include "CSBMLunitInterface.h"
#include <sbml/Model.h>

#include "copasi/copasi.h"

CSBMLunitInterface::CSBMLunitInterface(Model * model, bool unitsFromModel) :
    mpModel(model),
    mSBMLLevel(2),
    mSBMLVersion(4),
    mAssumeDimensionlessOne(false),
    mpSBMLTimeUnit(NULL),
    mpSBMLAmountUnit(NULL),
    mpSBMLVolumeUnit(NULL),
    mpSBMLAreaUnit(NULL),
    mpSBMLLengthUnit(NULL),
    mpSBMLConflictUnit(NULL)
{
  if (this->mpModel != NULL)
    {
      this->mSBMLLevel = this->mpModel->getLevel();
      this->mSBMLVersion = this->mpModel->getVersion();
    }

  initializeDefaultUnits();
  initializeFromSBMLModel(unitsFromModel);
}

/**
 * Destructor.
 */
CSBMLunitInterface::~CSBMLunitInterface()
{
  pdelete(this->mpSBMLTimeUnit);
  pdelete(this->mpSBMLAmountUnit);
  pdelete(this->mpSBMLVolumeUnit);
  pdelete(this->mpSBMLAreaUnit);
  pdelete(this->mpSBMLLengthUnit);
  pdelete(this->mpSBMLConflictUnit);
}

void CSBMLunitInterface::initializeDefaultUnits()
{
  UnitDefinition tmpTime(this->mSBMLLevel, this->mSBMLVersion);
  Unit tmpUnitTime(this->mSBMLLevel, this->mSBMLVersion);
  tmpUnitTime.setKind(UNIT_KIND_SECOND);
  tmpTime.addUnit(&tmpUnitTime);
  mpSBMLTimeUnit = new CSBMLunitInformation(&tmpTime, CSBMLunitInformation::DEFAULT);

  UnitDefinition tmpAmount(this->mSBMLLevel, this->mSBMLVersion);
  Unit tmpUnitAmount(this->mSBMLLevel, this->mSBMLVersion);
  tmpUnitAmount.setKind(UNIT_KIND_MOLE);
  tmpAmount.addUnit(&tmpUnitAmount);
  mpSBMLAmountUnit = new CSBMLunitInformation(&tmpAmount, CSBMLunitInformation::DEFAULT);

  UnitDefinition tmpVol(this->mSBMLLevel, this->mSBMLVersion);
  Unit tmpUnitVol(this->mSBMLLevel, this->mSBMLVersion);
  tmpUnitVol.setKind(UNIT_KIND_LITRE);
  tmpVol.addUnit(&tmpUnitVol);
  mpSBMLVolumeUnit = new CSBMLunitInformation(&tmpVol, CSBMLunitInformation::DEFAULT);

  UnitDefinition tmpAr(this->mSBMLLevel, this->mSBMLVersion);
  Unit tmpUnitAr(this->mSBMLLevel, this->mSBMLVersion);
  tmpUnitAr.setKind(UNIT_KIND_METRE);
  tmpUnitAr.setExponent(2);
  tmpAr.addUnit(&tmpUnitAr);
  mpSBMLAreaUnit = new CSBMLunitInformation(&tmpAr, CSBMLunitInformation::DEFAULT);

  UnitDefinition tmpL(this->mSBMLLevel, this->mSBMLVersion);
  Unit tmpUnitL(this->mSBMLLevel, this->mSBMLVersion);
  tmpUnitL.setKind(UNIT_KIND_METRE);
  tmpL.addUnit(&tmpUnitL);
  mpSBMLLengthUnit = new CSBMLunitInformation(&tmpL, CSBMLunitInformation::DEFAULT);

  mpSBMLConflictUnit = new CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion, CSBMLunitInformation::UNKNOWN, true);
}

void CSBMLunitInterface::initializeFromSBMLModel(bool unitsFromModel)
{
  if (!this->mpModel) return;

  //initialize global units
  if (unitsFromModel)
    {
      if (this->mpModel->getUnitDefinition("time"))
        (*mpSBMLTimeUnit) = CSBMLunitInformation(this->mpModel->getUnitDefinition("time"), CSBMLunitInformation::GLOBAL);

      if (this->mpModel->getUnitDefinition("substance"))
        (*mpSBMLAmountUnit) = CSBMLunitInformation(this->mpModel->getUnitDefinition("substance"), CSBMLunitInformation::GLOBAL);

      if (this->mpModel->getUnitDefinition("volume"))
        (*mpSBMLVolumeUnit) = CSBMLunitInformation(this->mpModel->getUnitDefinition("volume"), CSBMLunitInformation::GLOBAL);

      if (this->mpModel->getUnitDefinition("area"))
        (*mpSBMLAreaUnit) = CSBMLunitInformation(this->mpModel->getUnitDefinition("area"), CSBMLunitInformation::GLOBAL);

      if (this->mpModel->getUnitDefinition("length"))
        (*mpSBMLLengthUnit) = CSBMLunitInformation(this->mpModel->getUnitDefinition("length"), CSBMLunitInformation::GLOBAL);
    }

  mSBMLObjectsMap.clear();

  //initialize list of species
  unsigned int i;

  for (i = 0; i < this->mpModel->getNumSpecies(); i++)
    {
      Species * s = this->mpModel->getSpecies(i);

      if (unitsFromModel && s->isSetUnits())
        {
          std::map<std::string, CSBMLunitInformation>::iterator pos = this->mSBMLObjectsMap.find(s->getId());

          if (pos != this->mSBMLObjectsMap.end())
            {
              pos->second = CSBMLunitInformation(s->getDerivedUnitDefinition(), CSBMLunitInformation::PROVIDED);
            }
          else
            {
              mSBMLObjectsMap.insert(std::pair<std::string, CSBMLunitInformation>(s->getId() , CSBMLunitInformation(s->getDerivedUnitDefinition(), CSBMLunitInformation::PROVIDED)));
            }
        }
      else //take info from global units
        {
          if (s->getHasOnlySubstanceUnits())
            {
              std::map<std::string, CSBMLunitInformation>::iterator pos = this->mSBMLObjectsMap.find(s->getId());

              if (pos != this->mSBMLObjectsMap.end())
                {
                  pos->second = (*mpSBMLAmountUnit);
                }
              else
                {
                  mSBMLObjectsMap.insert(std::pair<std::string, CSBMLunitInformation>(s->getId(), (*mpSBMLAmountUnit)));
                }
            }
          else //concentration
            {
              CSBMLunit tmp(this->mpModel->getLevel(), this->mpModel->getVersion());
              Compartment* comp = this->mpModel->getCompartment(s->getCompartment());

              if (!comp)
                {
                  std::map<std::string, CSBMLunitInformation>::iterator pos = this->mSBMLObjectsMap.find(s->getId());

                  if (pos != this->mSBMLObjectsMap.end())
                    {
                      pos->second = (*mpSBMLConflictUnit);
                    }
                  else
                    {
                      mSBMLObjectsMap.insert(std::pair<std::string, CSBMLunitInformation>(s->getId(), (*mpSBMLConflictUnit)));
                    }

                  continue;
                }

              switch (comp->getSpatialDimensions())
                {
                  case 0:
                    break;
                  case 1:
                    tmp = (*mpSBMLLengthUnit);
                    break;
                  case 2:
                    tmp = (*mpSBMLAreaUnit);
                    break;
                  case 3:
                    tmp = (*mpSBMLVolumeUnit);
                    break;
                  default:
                    break;
                };

              tmp.invert();

              tmp.multiply(*mpSBMLAmountUnit);

              std::map<std::string, CSBMLunitInformation>::iterator pos = this->mSBMLObjectsMap.find(s->getId());

              if (pos != this->mSBMLObjectsMap.end())
                {
                  pos->second = CSBMLunitInformation(tmp, CSBMLunitInformation::GLOBAL);
                }
              else
                {
                  mSBMLObjectsMap.insert(std::pair<std::string, CSBMLunitInformation>(s->getId(), CSBMLunitInformation(tmp, CSBMLunitInformation::GLOBAL)));
                }

              //TODO: it should be DEFAULT rather than GLOBAL if both amount unit and size unit are DEFAULT.
            }
        }
    }

  //initialize list of compartments
  for (i = 0; i < this->mpModel->getNumCompartments(); i++)
    {
      Compartment *c = this->mpModel->getCompartment(i);

      if (unitsFromModel && c->isSetUnits())
        {

          std::map<std::string, CSBMLunitInformation>::iterator pos = this->mSBMLObjectsMap.find(c->getId());

          if (pos != this->mSBMLObjectsMap.end())
            {
              pos->second = CSBMLunitInformation(c->getDerivedUnitDefinition(), CSBMLunitInformation::PROVIDED);
            }
          else
            {
              mSBMLObjectsMap.insert(std::pair<std::string, CSBMLunitInformation>(c->getId(), CSBMLunitInformation(c->getDerivedUnitDefinition(), CSBMLunitInformation::PROVIDED)));
            }
        }
      else //take info from global units
        {
          CSBMLunitInformation tmp(this->mSBMLLevel, this->mSBMLVersion);

          switch (c->getSpatialDimensions())
            {
              case 0:
                break;
              case 1:
                tmp = (*mpSBMLLengthUnit);
                break;
              case 2:
                tmp = (*mpSBMLAreaUnit);
                break;
              case 3:
                tmp = (*mpSBMLVolumeUnit);
                break;
              default:
                break;
            };

          std::map<std::string, CSBMLunitInformation>::iterator pos = this->mSBMLObjectsMap.find(c->getId());

          if (pos != this->mSBMLObjectsMap.end())
            {
              pos->second = tmp;
            }
          else
            {
              mSBMLObjectsMap.insert(std::pair<std::string, CSBMLunitInformation>(c->getId(), tmp));
            }
        }
    }

  //initialize list of global parameters
  for (i = 0; i < this->mpModel->getNumParameters(); i++)
    {
      Parameter *p = this->mpModel->getParameter(i);

      if (unitsFromModel && p->isSetUnits())
        {
          std::map<std::string, CSBMLunitInformation>::iterator pos = this->mSBMLObjectsMap.find(p->getId());

          if (pos != this->mSBMLObjectsMap.end())
            {
              pos->second = CSBMLunitInformation(p->getDerivedUnitDefinition(), CSBMLunitInformation::PROVIDED);
            }
          else
            {
              mSBMLObjectsMap.insert(std::pair<std::string, CSBMLunitInformation>(p->getId(), CSBMLunitInformation(p->getDerivedUnitDefinition(), CSBMLunitInformation::PROVIDED)));
            }
        }
      else
        {
          std::map<std::string, CSBMLunitInformation>::iterator pos = this->mSBMLObjectsMap.find(p->getId());

          if (pos != this->mSBMLObjectsMap.end())
            {
              pos->second = CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion, CSBMLunitInformation::UNKNOWN);
            }
          else
            {
              mSBMLObjectsMap.insert(std::pair<std::string, CSBMLunitInformation>(p->getId(), CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion, CSBMLunitInformation::UNKNOWN)));
            }
        }
    }

  //initialize list of local parameters
  mSBMLLocalParametersMap.clear();
  unsigned int j;

  for (j = 0; j < this->mpModel->getNumReactions(); j++)
    {
      Reaction * reaction = this->mpModel->getReaction(j);
      std::map<std::string, CSBMLunitInformation> tmpMap;

      if (reaction->getKineticLaw() != NULL)
        {
          for (i = 0; i < reaction->getKineticLaw()->getNumParameters(); i++)
            {
              Parameter *p = reaction->getKineticLaw()->getParameter(i);

              if (unitsFromModel && p->isSetUnits())
                {
                  //tmpMap[p->getId()]=CSBMLunitInformation(p->getDerivedUnitDefinition(), CSBMLunitInformation::PROVIDED);
                  UnitDefinition* tmpUD = this->mpModel->getUnitDefinition(p->getUnits());

                  if (tmpUD)
                    {
                      std::map<std::string, CSBMLunitInformation>::iterator pos = tmpMap.find(p->getId());

                      if (pos != tmpMap.end())
                        {
                          pos->second = CSBMLunitInformation(tmpUD, CSBMLunitInformation::PROVIDED);
                        }
                      else
                        {
                          tmpMap.insert(std::pair<std::string, CSBMLunitInformation>(p->getId(), CSBMLunitInformation(tmpUD, CSBMLunitInformation::PROVIDED)));
                        }
                    }
                  else
                    {
                      //this is just a workaround
                      if (p->getUnits() == "dimensionless")
                        {
                          std::map<std::string, CSBMLunitInformation>::iterator pos = tmpMap.find(p->getId());

                          if (pos != tmpMap.end())
                            {
                              pos->second = CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion, CSBMLunitInformation::PROVIDED);
                            }
                          else
                            {
                              tmpMap.insert(std::pair<std::string, CSBMLunitInformation>(p->getId(), CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion, CSBMLunitInformation::PROVIDED)));
                            }
                        }
                      else
                        {
                          std::map<std::string, CSBMLunitInformation>::iterator pos = tmpMap.find(p->getId());

                          if (pos != tmpMap.end())
                            {
                              pos->second = CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion, CSBMLunitInformation::UNKNOWN);
                            }
                          else
                            {
                              tmpMap.insert(std::pair<std::string, CSBMLunitInformation>(p->getId(), CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion, CSBMLunitInformation::UNKNOWN)));
                            }

                          // "Could not resolve unit ID " << p->getUnits()  << " for " <<  p->getId() << std::endl;
                          //TODO
                        }
                    }
                }
              else //take info from global units
                {
                  std::map<std::string, CSBMLunitInformation>::iterator pos = tmpMap.find(p->getId());

                  if (pos != tmpMap.end())
                    {
                      pos->second = CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion, CSBMLunitInformation::UNKNOWN);
                    }
                  else
                    {
                      tmpMap.insert(std::pair<std::string, CSBMLunitInformation>(p->getId(), CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion, CSBMLunitInformation::UNKNOWN)));
                    }
                }
            }
        }

      mSBMLLocalParametersMap[reaction->getId()] = tmpMap;
    }

  //determine units of stoichiometries

  //**** generate list of all mathematical expressions that need to be considered

  mSBMLExpressions.clear();

  //stoichiometry math TODO

  //kinetic laws
  //construct the units for amount/time (for kinetic laws)
  CSBMLunitInformation amountPerTimeUnit = (*mpSBMLTimeUnit);
  amountPerTimeUnit.invert();
  amountPerTimeUnit.multiply(*mpSBMLAmountUnit);

  if (mpSBMLAmountUnit->getInfo() != CSBMLunitInformation::DEFAULT)
    amountPerTimeUnit.setInfo(CSBMLunitInformation::GLOBAL);

  for (i = 0; i < this->mpModel->getNumReactions(); i++)
    {
      Reaction * reaction = this->mpModel->getReaction(i);

      if (!reaction->getKineticLaw()) continue;

      if (!reaction->getKineticLaw()->isSetMath()) continue;

      CExpressionInformation tmp(this->mSBMLLevel, this->mSBMLVersion);
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
  for (i = 0; i < this->mpModel->getNumRules(); i++)
    {
      Rule* rule = this->mpModel->getRule(i);

      if (!rule->isSetMath()) continue;

      CExpressionInformation tmp(this->mSBMLLevel, this->mSBMLVersion);
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
          //nothing to be done. UNKNOWN is the default for a CSBMLunitInformation
          //tmp.mRootUnit=UNKNOWN;
        }

      mSBMLExpressions.push_back(tmp);
    }

  //Events
  for (i = 0; i < this->mpModel->getNumEvents(); i++)
    {
      Event* event = this->mpModel->getEvent(i);

      //trigger
      if (event->isSetTrigger() && event->getTrigger()->isSetMath())
        {
          CExpressionInformation tmp(this->mSBMLLevel, this->mSBMLVersion);
          tmp.mTypeDescription = "Event trigger";
          tmp.mObjectDisplayString = event->isSetName() ? event->getName() : event->getId();
          tmp.mpExpression = event->getTrigger()->getMath();
          mSBMLExpressions.push_back(tmp);
        }

      //delay
      if (event->isSetDelay() && event->getDelay()->isSetMath())
        {
          CExpressionInformation tmp(this->mSBMLLevel, this->mSBMLVersion);
          tmp.mTypeDescription = "Event delay";
          tmp.mObjectDisplayString = event->isSetName() ? event->getName() : event->getId();
          tmp.mpExpression = event->getDelay()->getMath();
          tmp.mRootUnit = (*mpSBMLTimeUnit);
          mSBMLExpressions.push_back(tmp);
        }

      //event assignments
      for (j = 0; j < event->getNumEventAssignments(); ++j)
        {
          EventAssignment* ea = event->getEventAssignment(j);

          if (ea->isSetMath())
            {
              CExpressionInformation tmp(this->mSBMLLevel, this->mSBMLVersion);
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

void CSBMLunitInterface::writeBackToModel()
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
      CSBMLunitInformation * tmp = getMappedUnitFromIdentifier(p->getId(), CEnvironmentInformation());

      //if the unit could be derived and it does not contain a symbolic exponent
      if (tmp && tmp->getInfo() == CSBMLunitInformation::DERIVED && tmp->getSymbolicExpExp() == 0)
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

      if (reaction->getKineticLaw() != NULL)
        for (i = 0; i < reaction->getKineticLaw()->getNumParameters(); i++)
          {
            Parameter *p = reaction->getKineticLaw()->getParameter(i);

            CSBMLunitInformation * tmp = getMappedUnitFromIdentifier(p->getId(), CEnvironmentInformation(reaction->getId()));
            //TODO this could be easier directly from the map instead of using getMappedUnitFromIdentifier()

            //if the unit could be derived and it does not contain a symbolic exponent
            if (tmp && tmp->getInfo() == CSBMLunitInformation::DERIVED && tmp->getSymbolicExpExp() == 0)
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

void CSBMLunitInterface::calculateStatistics()
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
  std::map<std::string, CSBMLunitInformation>::const_iterator it, itEnd = mSBMLObjectsMap.end();

  for (it = mSBMLObjectsMap.begin(); it != itEnd; ++it)
    {
      if (it->second.isConflict())
        ++mStatistics.global[CONFLICT];
      else
        ++mStatistics.global[it->second.getInfo()];
    }

  //collect statistics from localparameter
  std::map<std::string, std::map<std::string, CSBMLunitInformation> >::const_iterator rit;

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
  std::map<const ASTNode*, CSBMLunitInformation>::const_iterator nit, nitEnd = mSBMLNumbersMap.end();

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

void CSBMLunitInterface::outputStatistics(const Statistics & stat, bool flag)
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
  else if (stat.global[0] + stat.local[0] == 0)
    std::cout << "only some numbers are still unknown" << std::endl;
  else
    std::cout << "some unknown units left..." << std::endl;

  //if (stat.all[5]>0)
  //  debugOutput();
}

std::vector<std::string> CSBMLunitInterface::getListOfObjectsWithGivenUnitStatus(int status) const
{
  std::vector<std::string> ret;

  std::map<std::string, CSBMLunitInformation>::const_iterator it, itEnd = mSBMLObjectsMap.end();

  for (it = mSBMLObjectsMap.begin(); it != itEnd; ++it)
    {
      if (status == 5 && it->second.isConflict())
        ret.push_back(it->first);

      if (status < 5 && (int)it->second.getInfo() == status)
        ret.push_back(it->first);
    }

  return ret;
}

std::vector<std::pair<std::string, std::string> > CSBMLunitInterface::getListOfLocalParametersWithGivenUnitStatus(int status) const
{
  std::vector<std::pair<std::string, std::string> > ret;

  std::map<std::string, CSBMLunitInformation>::const_iterator it;//, itEnd = mSBMLObjectsMap.end();
  std::map<std::string, std::map<std::string, CSBMLunitInformation> >::const_iterator rit;

  for (rit = mSBMLLocalParametersMap.begin(); rit != mSBMLLocalParametersMap.end(); ++rit)
    {
      for (it = rit->second.begin(); it != rit->second.end(); ++it)
        {
          if (status == 5 && it->second.isConflict())
            ret.push_back(std::pair<std::string, std::string>(rit->first, it->first));

          if (status < 5 && (int)it->second.getInfo() == status)
            ret.push_back(std::pair<std::string, std::string>(rit->first, it->first));
        }
    }

  return ret;
}

std::string CSBMLunitInterface::getMessageAboutUnknownUnits() const
{
  std::string ret;

  ret += "Some objects in the SBML file have unknown units. \n";
  ret += "Global objects:\n";

  std::vector<std::string> globalobjects = getListOfObjectsWithGivenUnitStatus(0); //unknown units
  unsigned int i;

  for (i = 0; i < globalobjects.size(); ++i)
    {
      const Compartment* c = mpModel->getCompartment(globalobjects[i]);

      if (c)
        ret += "  Compartment " + c->getId() + " " + c->getName() +  "\n";

      const Species* s = mpModel->getSpecies(globalobjects[i]);

      if (s)
        ret += "  Species " + s->getId() + " " + s->getName() +  "\n";

      const Parameter* p = mpModel->getParameter(globalobjects[i]);

      if (p)
        ret += "  Global parameter " + p->getId() + " " + p->getName() +  "\n";
    }

  ret += "\n";
  ret += "Local parameters:\n";

  std::vector<std::pair<std::string, std::string> > localparameters =
    getListOfLocalParametersWithGivenUnitStatus(0);

  for (i = 0; i < localparameters.size(); ++i)
    {
      const Reaction* r = mpModel->getReaction(localparameters[i].first);

      if (r)
        {
          ret += "  Reaction " + r->getId() + " " + r->getName()
                 + ", parameter " + localparameters[i].second +  "\n";
        }
    }

  //TODO this is not really very nice output. Needs improvement
  return ret;
}

void CSBMLunitInterface::debugOutput() const
{
  std::cout << "global units:" << std::endl;
  std::cout << "Time:        " << mpSBMLTimeUnit->getDisplayString() << std::endl;
  std::cout << "Amount:   " << mpSBMLAmountUnit->getDisplayString() << std::endl;
  std::cout << "Volume:   " << mpSBMLVolumeUnit->getDisplayString() << std::endl;
  std::cout << "Area:        " << mpSBMLAreaUnit->getDisplayString() << std::endl;
  std::cout << "Length:    " << mpSBMLLengthUnit->getDisplayString() << std::endl;

  std::cout << std::endl;

  std::map<std::string, CSBMLunitInformation>::const_iterator it, itEnd = mSBMLObjectsMap.end();

  for (it = mSBMLObjectsMap.begin(); it != itEnd; ++it)
    {
      std::cout << it->first << "  " <<  it->second.getDisplayString() <<  std::endl;
    }

  std::cout << std::endl;

  std::map<std::string, std::map<std::string, CSBMLunitInformation> >::const_iterator rit;

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

const std::set<const ASTNode *> & CSBMLunitInterface::getListOfConflictingNodes() const
{
  return mConflictingNodes;
}

void CSBMLunitInterface::determineUnits()
{
  if (!mpModel) return;

  //clear set of conflicting nodes
  mConflictingNodes.clear();

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

          handleOneExpression(*it);
        }
    }

  calculateStatistics();
}

void CSBMLunitInterface::handleOneExpression(CExpressionInformation & ei)
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
      CSBMLunitInformation * pNodeUnit = getMappedUnitFromIdentifier(ei.mRootObject, environment);

      if (!pNodeUnit) return;

      CSBMLunitInformation sourceUnit = *pNodeUnit;

      if (ei.mPerTime && sourceUnit.getInfo() > CSBMLunitInformation::UNKNOWN)
        {
          //devide unit of rule target by time
          CSBMLunitInformation invTime = (*mpSBMLTimeUnit);
          invTime.invert();
          sourceUnit.multiply(invTime);
        }

      CSBMLunitInformation tmp = recursion(ei.mpExpression, sourceUnit, environment);

      if (ei.mPerTime && tmp.getInfo() > CSBMLunitInformation::UNKNOWN)
        {
          //multiply unit of the rate rule expression by time
          tmp.multiply(*mpSBMLTimeUnit);
        }

      handleTerminalNode(tmp, pNodeUnit, NULL);
    }

  //TODO handle mpRootObject case

  if (mError > ei.mErrorCode) ei.mErrorCode = mError;
}

//*********************************************************************************

//#define UNIT_DEBUG

CSBMLunitInformation CSBMLunitInterface::recursion(const ASTNode* node,
    const CSBMLunitInformation & ui,
    const CEnvironmentInformation & ei)
{

  CSBMLunitInformation ret(this->mSBMLLevel, this->mSBMLVersion);

  if (!node) return ret;

  //handle delay first since it is unclear from the documentation in which class of nodes it is included
  if (node->getType() == AST_FUNCTION_DELAY)
    {
      if (node->getNumChildren() != 2)
        return ret;

      CSBMLunitInformation tmpTimeUnit = (*mpSBMLTimeUnit);
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
          CSBMLunitInformation tmpTimeUnit = (*mpSBMLTimeUnit);
          return handleTerminalNode(ui, &tmpTimeUnit, node);
        }

      //check if it is a reaction ID
      //TODO

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
      CSBMLunitInformation * pNodeUnit = getMappedUnitFromIdentifier(getIdentifier(node), ei);

      if (!pNodeUnit) return (*mpSBMLConflictUnit);

      return handleTerminalNode(ui, pNodeUnit, node);
    }//is object node

  //number node
  else if (isNumber(node))
    {
      CSBMLunitInformation* pNodeUnit = NULL;
      std::map<const ASTNode*, CSBMLunitInformation>::iterator pos = mSBMLNumbersMap.find(node);

      if (pos != mSBMLNumbersMap.end())
        {
          pNodeUnit = &pos->second;
        }
      else
        {
          pNodeUnit = &((mSBMLNumbersMap.insert(
                           std::pair<const ASTNode*, CSBMLunitInformation>
                           (node, CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion))
                         )).first->second);
        }

//       //check if the node is already in the map
//       std::map<const ASTNode*, CSBMLunitInformation>::iterator it = mSBMLNumbersMap.find(node);
//       if (it != mSBMLNumbersMap.end())
//         pNodeUnit=&it->second;
//       else //create new entry in the map
//         {
//           pNodeUnit=&mSBMLNumbersMap[node];
//}

      if (mAssumeDimensionlessOne)
        {
          if (getValueFromNumberNode(node) == 1.0 || getValueFromNumberNode(node) == -1.0)
            pNodeUnit->setInfo(CSBMLunitInformation::DERIVED);
        }

      return handleTerminalNode(ui, pNodeUnit, node);
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
      // function call
      //check if the object is a function call
      FunctionDefinition *fd = resolveFunctionName(getIdentifier(node));

      if (fd)
        {
          // could resolve function call
          unsigned int i, numArgs = fd->getNumArguments();
          assert(numArgs == node->getNumChildren());

          //create mapping from variable ID to the node that should be substituted
          std::map<std::string, ASTNode*> tmpMap;

          for (i = 0; i < numArgs; ++i)
            tmpMap[fd->getArgument(i)->getName()] = node->getChild(i);

          CEnvironmentInformation tmpEI = ei;
          tmpEI.push(tmpMap);
          return recursion(fd->getBody(), ui, tmpEI);
        }
    }

  else if (isBuiltInFunctionCall(node))
    {
      // built in function
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
            recursion(node->getChild(0), CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion, CSBMLunitInformation::DEFAULT), ei);
            return CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion, CSBMLunitInformation::DEFAULT);
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
        return  CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion, CSBMLunitInformation::DEFAULT);
        break;

      case AST_FUNCTION_PIECEWISE:
        return recursionPiecewise(node, ui, ei);

      default:
        break;
    }

  //TODO numbers, functions, calls, variables, choice, delay, time, ...
  //logicals (comparison operators), constants (pi, ...),  ...

  //fallback: just to make sure the whole tree is covered
  unsigned int i, numChildren = node->getNumChildren();

  for (i = 0; i < numChildren; ++i)
    recursion(node->getChild(i), CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion, CSBMLunitInformation::UNKNOWN), ei);

  return ret;
}

CSBMLunitInformation CSBMLunitInterface::handleTerminalNode(const CSBMLunitInformation & ui, CSBMLunitInformation *pNodeUnit, const ASTNode* node)
{
  //TODO handle case where conflict flag is set before

  if (ui.getInfo() == CSBMLunitInformation::UNKNOWN)
    {
      return *pNodeUnit;
    }
  else if (pNodeUnit->getInfo() == CSBMLunitInformation::UNKNOWN)
    {
      *pNodeUnit = ui;
      pNodeUnit->setInfo(CSBMLunitInformation::DERIVED);
      return *pNodeUnit;
    }
  else //both are known
    {
      //check for conflict
      if (CSBMLunit::isEqual(ui, *pNodeUnit))
        return ui;
      else //there is a conflict
        {
          if (ui.getInfo() < pNodeUnit->getInfo())  //the new unit is more reliable
            {
              *pNodeUnit = ui;
              pNodeUnit->setInfo(CSBMLunitInformation::DERIVED);
            }

          if (!pNodeUnit->isConflict())
            {
              //only report the conflict for this expression if it was not known before
              if (1 > mError) mError = 1;

              mConflictingNodes.insert(node);
            }

          pNodeUnit->setConflict(true);
          return *pNodeUnit;
        }
    }
}

CSBMLunitInformation CSBMLunitInterface::recursionEqual(const ASTNode* node,
    const CSBMLunitInformation & ui,
    const CEnvironmentInformation & ei)
{
  CSBMLunitInformation ret(this->mSBMLLevel, this->mSBMLVersion);

  if (!node) return ret;

  ret = ui;

  //TODO deal with conflicts

  unsigned int i, numChildren = node->getNumChildren();
  std::vector<CSBMLunitInformation> childUnits;
  childUnits.resize(numChildren, CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion));

  //first deal with the unit that is passed from above
  if (ui.getInfo() > CSBMLunitInformation::UNKNOWN)
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

          if (childUnits[i].getInfo() > CSBMLunitInformation::UNKNOWN)
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

CSBMLunitInformation CSBMLunitInterface::recursionTimes(const ASTNode* node,
    const CSBMLunitInformation & ui,
    const CEnvironmentInformation & ei)
{
  CSBMLunitInformation ret(this->mSBMLLevel, this->mSBMLVersion);

  if (!node) return ret;

  ret = ui;

  //TODO deal with conflicts

  unsigned int i, numChildren = node->getNumChildren();
  std::vector<CSBMLunitInformation> childUnits;
  childUnits.resize(numChildren, CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion));

  // ask all children for their unit
  std::vector<int> unknown;
  CSBMLunitInformation uu(this->mSBMLLevel, this->mSBMLVersion); //unknown units

  for (i = 0; i < numChildren; ++i) //TODO should stop when we know enough
    {
      childUnits[i] = recursion(node->getChild(i), uu, ei);

      if (childUnits[i].getInfo() == CSBMLunitInformation::UNKNOWN)
        unknown.push_back(i);
    }

  //first the case where the parent unit is unknown
  if (ui.getInfo() == CSBMLunitInformation::UNKNOWN)
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
        ret.setInfo(CSBMLunitInformation::DERIVED);
      else
        ret.setInfo(CSBMLunitInformation::UNKNOWN);
    }
  else //parent units are known
    {
      //if there is more than one child with unknown units we can do nothing
      if (unknown.size() > 1)
        return ret;

      //if no child has unknown units assume the first (and check for conflicts later)
      unsigned int tmp = unknown.size() ? unknown[0] : 0;

      //determine units
      CSBMLunitInformation tmpUnit(this->mSBMLLevel, this->mSBMLVersion);
      bool success = true;

      for (i = 0; i < numChildren; ++i)
        if (i != tmp)
          success &= tmpUnit.multiply(childUnits[i]);

      tmpUnit.invert();
      success &= tmpUnit.multiply(ui);

      if (success)
        tmpUnit.setInfo(CSBMLunitInformation::DERIVED);
      else
        tmpUnit.setInfo(CSBMLunitInformation::UNKNOWN);

      //tell child about derived unit
      childUnits[tmp] = recursion(node->getChild(tmp), tmpUnit, ei);
      //TODO check for conflicts
    }

  return ret;
}

CSBMLunitInformation CSBMLunitInterface::recursionDivide(const ASTNode* node,
    const CSBMLunitInformation & ui,
    const CEnvironmentInformation & ei)
{
  CSBMLunitInformation ret(this->mSBMLLevel, this->mSBMLVersion);

  if (!node) return ret;

  ret = ui;

  //TODO deal with conflicts

  unsigned int i, numChildren = node->getNumChildren();
  assert(numChildren == 2);
  std::vector<CSBMLunitInformation> childUnits;
  childUnits.resize(numChildren, CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion));

  // ask all children for their unit
  std::vector<int> unknown;
  CSBMLunitInformation uu(this->mSBMLLevel, this->mSBMLVersion); //unknown units

  for (i = 0; i < numChildren; ++i)
    {
      childUnits[i] = recursion(node->getChild(i), uu, ei);

      if (childUnits[i].getInfo() == CSBMLunitInformation::UNKNOWN)
        unknown.push_back(i);
    }

  //first the case where the parent unit is unknown
  if (ui.getInfo() == CSBMLunitInformation::UNKNOWN)
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
        ret.setInfo(CSBMLunitInformation::DERIVED);
      else
        ret.setInfo(CSBMLunitInformation::UNKNOWN);
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
          CSBMLunitInformation tmpUnit = childUnits[1];
          bool success = true;
          success &= tmpUnit.multiply(ui);

          if (success)
            tmpUnit.setInfo(CSBMLunitInformation::DERIVED);
          else
            tmpUnit.setInfo(CSBMLunitInformation::UNKNOWN);

          //tell child about derived unit
          childUnits[0] = recursion(node->getChild(0), tmpUnit, ei);
          //TODO check for conflicts
        }
      else //denominator is unknown
        {
          //determine units
          CSBMLunitInformation tmpUnit = ui;
          bool success = true;
          tmpUnit.invert();
          success &= tmpUnit.multiply(childUnits[0]);

          //tmpUnit.multiply(ui);
          if (success)
            tmpUnit.setInfo(CSBMLunitInformation::DERIVED);
          else
            tmpUnit.setInfo(CSBMLunitInformation::UNKNOWN);

          //tell child about derived unit
          childUnits[1] = recursion(node->getChild(1), tmpUnit, ei);
        }
    }

  return ret;
}

CSBMLunitInformation CSBMLunitInterface::recursionPower(const ASTNode* node,
    const CSBMLunitInformation & ui,
    const CEnvironmentInformation & ei)
{
  CSBMLunitInformation ret(this->mSBMLLevel, this->mSBMLVersion);

  if (!node) return ret;

  ret = ui;

  unsigned int numChildren = node->getNumChildren();
  assert(numChildren == 2);
  std::vector<CSBMLunitInformation> childUnits;
  childUnits.resize(numChildren, CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion));

  //the exponent should always be dimensionless
  childUnits[1] = recursion(node->getChild(1), CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion, CSBMLunitInformation::DEFAULT), ei);

  //try to evaluate the exponent
  EvaluationResult res = evaluate(node->getChild(1));

  if (res.known) //the base of the power could be evaluated
    {
      //check if the exponent is integer
      if (fabs(res.result - floor(res.result + 0.5)) < 1e-100)
        {
          int intExp = (int) floor(res.result + 0.5);

          if (ui.getInfo() == CSBMLunitInformation::UNKNOWN)
            {
              childUnits[0] = recursion(node->getChild(0), CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion, CSBMLunitInformation::UNKNOWN), ei);
              ret = childUnits[0];

              if (ret.getInfo() > CSBMLunitInformation::UNKNOWN)
                {//only if the base is known, we can make use of the exponent to calculate the return unit
                  ret.applyExponent(intExp);
                  ret.setInfo(CSBMLunitInformation::DERIVED);
                }
            }
          else
            {
              CSBMLunitInformation tmpUI = ui;
              tmpUI.applyExponent(1 / (double)intExp);
              tmpUI.setInfo(CSBMLunitInformation::DERIVED);
              childUnits[0] = recursion(node->getChild(0), tmpUI, ei);
            }
        }
      else
        {
          //TODO perhaps rather conflict???
          childUnits[0] = recursion(node->getChild(0), CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion, CSBMLunitInformation::UNKNOWN), ei);
        }

      //TODO extend to deal with non integer exponents properly. CSBMLunit needs to support it first.
    }
  else
    {
      //the exponent could not be determined as a number

      //special case: exponent is an identifier
      if (node->getChild(1)->isName())
        {
          if (ui.getInfo() == CSBMLunitInformation::UNKNOWN)
            {
              childUnits[0] = recursion(node->getChild(0), CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion, CSBMLunitInformation::UNKNOWN), ei);
              ret = childUnits[0];

              if (ret.getInfo() > CSBMLunitInformation::UNKNOWN)
                {//only if the base is known, we can make use of the exponent to calculate the return unit
                  ret.applyExponent(node->getChild(1)->getName(), ei.mFrameStack.size());
                  ret.setInfo(CSBMLunitInformation::DERIVED);
                }
            }
          else
            {
              CSBMLunitInformation tmpUI = ui;
              tmpUI.applyInverseExponent(node->getChild(1)->getName(), ei.mFrameStack.size());
              tmpUI.setInfo(CSBMLunitInformation::DERIVED);
              childUnits[0] = recursion(node->getChild(0), tmpUI, ei);
            }
        }
      else //exponent is neither a number nor a simple identifier. Units of the base are unknown
        {
          childUnits[0] = recursion(node->getChild(0), CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion, CSBMLunitInformation::UNKNOWN), ei);
        }
    }

  //heuristics: if the exponent is variable, the base should be dimensionless
  //TODO

  //TODO deal with conflicts

  return ret;
}

CSBMLunitInterface::EvaluationResult CSBMLunitInterface::evaluate(const ASTNode* node)
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

CSBMLunitInformation CSBMLunitInterface::recursionPiecewise(const ASTNode* node,
    const CSBMLunitInformation & ui,
    const CEnvironmentInformation & ei)
{
  CSBMLunitInformation ret(this->mSBMLLevel, this->mSBMLVersion);

  if (!node) return ret;

  ret = ui;

  //TODO deal with conflicts

  unsigned int i, numChildren = node->getNumChildren();
  std::vector<CSBMLunitInformation> childUnits;
  childUnits.resize(numChildren, CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion));

  //first do the recursion for the logical parts (the children with uneven index)
  for (i = 1; i < numChildren; i += 2)
    recursion(node->getChild(i), CSBMLunitInformation(this->mSBMLLevel, this->mSBMLVersion, CSBMLunitInformation::UNKNOWN), ei);

  //first deal with the unit that is passed from above
  if (ui.getInfo() > CSBMLunitInformation::UNKNOWN)
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

          if (childUnits[i].getInfo() > CSBMLunitInformation::UNKNOWN)
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

CSBMLunitInformation* CSBMLunitInterface::getMappedUnitFromIdentifier(const std::string & node,
    const CEnvironmentInformation & ei)
{
  //try local parameters
  if (ei.isReactionScope())
    {
      std::map<std::string, std::map<std::string, CSBMLunitInformation> >::iterator rit;
      rit =  mSBMLLocalParametersMap.find(ei.mReactionID);

      if (rit != mSBMLLocalParametersMap.end())
        {
          std::map<std::string, CSBMLunitInformation>::iterator it;
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
  std::map<std::string, CSBMLunitInformation>::iterator it;
  it = mSBMLObjectsMap.find(node);

  if (it != mSBMLObjectsMap.end())
    return &it->second;

  return NULL;
}

ASTNode* CSBMLunitInterface::resolveVariableName(const std::string & node,
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

FunctionDefinition* CSBMLunitInterface::resolveFunctionName(const std::string & node)
{
  if (!mpModel) return NULL;

  return mpModel->getFunctionDefinition(node);
}

CSBMLunitInformation* CSBMLunitInterface::getMappedUnitFromNumberNode(const ASTNode* node)
{
  //check if the node is in the map
  std::map<const ASTNode*, CSBMLunitInformation>::iterator it = mSBMLNumbersMap.find(node);

  if (it != mSBMLNumbersMap.end())
    return &it->second;
  else
    return NULL;
}

//*************************************************

bool CSBMLunitInterface::isObject(const ASTNode* node)
{
  return (node && node->isName());
}

bool CSBMLunitInterface::isOperator(const ASTNode* node)
{
  //is this a bug in libsbml that power is a function?
  return (node &&
          (node->isOperator() || node->isRelational() || node->getType() == AST_FUNCTION_POWER));
}

bool CSBMLunitInterface::isNumber(const ASTNode* node)
{
  return (node && (node->isNumber() || node->isRational()));
}

bool CSBMLunitInterface::isFunctionCall(const ASTNode* node)
{
  return (node && (node->getType() == AST_FUNCTION));
}

bool CSBMLunitInterface::isBuiltInFunctionCall(const ASTNode* node)
{
  return (node && (node->getType() > AST_FUNCTION) && (node->getType() <= AST_FUNCTION_TANH));
}

double CSBMLunitInterface::getValueFromNumberNode(const ASTNode* node)
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
        return std::numeric_limits< double >::quiet_NaN();
    }
}

std::string CSBMLunitInterface::getIdentifier(const ASTNode* node)
{
  if (node)
    return node->getName();
  else
    return "";
}
