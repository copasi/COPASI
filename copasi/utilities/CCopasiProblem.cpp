/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiProblem.cpp,v $
   $Revision: 1.14 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/07/06 17:14:24 $
   End CVS Header */

/**
 *  CCopasiProblem class.
 *  This class is used to describe a task in COPASI. This class is 
 *  intended to be used as the parent class for all tasks whithin COPASI.
 *  
 *  Created for Copasi by Stefan Hoops 2003
 */

#include "copasi.h"

#include "CCopasiProblem.h"
#include "model/CMetab.h"
#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "CCopasiVector.h"

CCopasiProblem::CCopasiProblem():
    CCopasiParameterGroup("NoName", NULL, "Problem"),
    mType(CCopasiTask::unset),
    mpModel(NULL),
    mpCallBack(NULL),
    mpReport(NULL)
{}

CCopasiProblem::CCopasiProblem(const CCopasiTask::Type & type,
                               const CCopasiContainer * pParent):
    CCopasiParameterGroup(CCopasiTask::TypeName[type], pParent, "Problem"),
    mType(type),
    mpModel(NULL),
    mpCallBack(NULL),
    mpReport(NULL)
{}

CCopasiProblem::CCopasiProblem(const CCopasiProblem & src,
                               const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mType(src.mType),
    mpModel(src.mpModel),
    mpCallBack(src.mpCallBack),
    mpReport(src.mpReport)
{}

CCopasiProblem::~CCopasiProblem() {}

const CCopasiTask::Type & CCopasiProblem::getType() const {return mType;}

bool CCopasiProblem::setModel(CModel * pModel)
{
  mpModel = pModel;
  return true;
}

CModel * CCopasiProblem::getModel() const {return mpModel;}

bool CCopasiProblem::setCallBack(CProcessReport * pCallBack)
{
  mpCallBack = pCallBack;
  return true;
}

//virtual
std::vector<CDefaultPlotDescription> CCopasiProblem::getListOfDefaultPlotDescriptions() const
  {
    std::vector<CDefaultPlotDescription> ret;
    if (!mpModel) return ret;
    CDefaultPlotDescription tmp;

    //concentrations plot
    tmp.id = 0;
    tmp.name = "Concentrations plot";
    tmp.description = "A plot of the variable metabolite concentrations vs. time.\nIt does not contain the concentrations of fixed metabolites.";
    tmp.isPlot = true;
    ret.push_back(tmp);

    //particle numbers plot
    tmp.id = 1;
    tmp.name = "Particle numbers plot";
    tmp.description = "A plot of the variable metabolite particle numbers vs. time.\nIt does not contain the particle numbers of fixed metabolites.";
    tmp.isPlot = true;
    ret.push_back(tmp);

    //offer some plots only if there are fixed metabs
    bool fixedMetab = false;
    const CCopasiVector< CMetab > & metabs = mpModel->getMetabolites();
    C_INT32 i, imax = metabs.size();
    for (i = 0; i < imax; ++i)
      if (metabs[i]->getStatus() == CModelEntity::FIXED)
      {fixedMetab = true; break;}

    if (fixedMetab)
      {
        //complete concentrations plot
        tmp.id = 2;
        tmp.name = "Complete concentrations plot";
        tmp.description = "A plot of all the metabolite concentrations vs. time (including fixed metabolites).";
        tmp.isPlot = true;
        ret.push_back(tmp);

        //complete particle numbers plot
        tmp.id = 3;
        tmp.name = "Complete particle numbers plot";
        tmp.description = "A plot of all the metabolite particle numbers vs. time (including fixed metabolites).";
        tmp.isPlot = true;
        ret.push_back(tmp);
      }

    //concentration rate plot
    /*tmp.id = 4;
    tmp.name = "Concentration rates plot";
    tmp.description = "A plot of the rate of change of all variable metabolite concentrations vs. time.\nIt does not contain the rates of fixed metabolites.";
    tmp.isPlot = true;
    ret.push_back(tmp);*/ //not possible at the moment

    //particle rate plot
    tmp.id = 5;
    tmp.name = "Particle number rates plot";
    tmp.description = "A plot of the rate of change of all variable metabolite particle numbers vs. time.\nIt does not contain the rates of fixed metabolites.";
    tmp.isPlot = true;
    ret.push_back(tmp);

    //reaction particle flux
    tmp.id = 6;
    tmp.name = "Plot of reaction fluxes";
    tmp.description = "A plot of the the fluxes of all the reactions vs. time, in concentration/time unit.";
    tmp.isPlot = true;
    ret.push_back(tmp);

    //reaction particle flux
    tmp.id = 7;
    tmp.name = "Plot of reaction event fluxes";
    tmp.description = "A plot of the the fluxes of all the reactions vs. time, in reaction events/time unit.";
    tmp.isPlot = true;
    ret.push_back(tmp);

    //empty plot
    tmp.id = 999;
    tmp.name = "Empty plot";
    tmp.description = "A plot with nothing in it.";
    tmp.isPlot = true;
    ret.push_back(tmp);

    return ret;
  }

#include "plot/COutputDefinitionVector.h"

//virtual
bool CCopasiProblem::createDefaultPlot(C_INT32 id) const
  {
    //std::cout << id << std::endl;
    if (!mpModel) return false;

    std::string bname;
    switch (id)
      {
      case 0:
        bname = "Concentrations plot";
        break;
      case 1:
        bname = "Particle numbers plot";
        break;
      case 2:
        bname = "Complete concentrations plot";
        break;
      case 3:
        bname = "Complete particle numbers plot";
        break;
      case 4:
        bname = "Concentration rates plot";
        break;
      case 5:
        bname = "Particle number rates plot";
        break;
      case 6:
        bname = "Reaction fluxes";
        break;
      case 7:
        bname = "Reaction events/time";
        break;
      case 999:
        bname = "Plot";
        break;
      default:
        return false;
      }

    //TODO this part of this method is propably the  same for all problems. Could be moved elsewhere
    unsigned C_INT32 i = 0;
    CPlotSpecification* pPl;
    std::ostringstream nname;
    nname << bname;
    while (!(pPl = CCopasiDataModel::Global->getPlotDefinitionList()->createPlotSpec(nname.str(), CPlotItem::plot2d)))
      {
        i++;
        nname.str("");
        nname << bname << "_" << i;
      }

    //empty plot (99)
    if (id == 999) return true;

    CPlotItem * plItem;
    std::string itemTitle;
    CPlotDataChannelSpec name2;
    const CCopasiObject * tmp;

    CPlotDataChannelSpec name1 = mpModel->getObject(CCopasiObjectName("Reference=Time"))->getCN();

    //id 0,1,2,3,4,5
    if ((id >= 0) && (id <= 5))
      {
        bool allMetabs = (id == 2) || (id == 3);

        unsigned C_INT32 imax = mpModel->getMetabolites().size();
        for (i = 0; i < imax; ++i)
          {
            if ((mpModel->getMetabolites()[i]->getStatus() != CModelEntity::FIXED) || allMetabs)
              {
                if ((id == 0) || (id == 2)) //concentrations
                  tmp = mpModel->getMetabolites()[i]->getObject(CCopasiObjectName("Reference=Concentration"));
                else if ((id == 1) || (id == 3)) //particle numbers
                  tmp = mpModel->getMetabolites()[i]->getObject(CCopasiObjectName("Reference=ParticleNumber"));
                else if (id == 4) //conc rate, does not work at the moment
                  tmp = mpModel->getMetabolites()[i]->getObject(CCopasiObjectName("Reference=xxxConcentrationRate"));
                else if (id == 5) //number rate
                  tmp = mpModel->getMetabolites()[i]->getObject(CCopasiObjectName("Reference=Rate"));

                if (!tmp) continue;

                name2 = tmp->getCN();
                itemTitle = tmp->getObjectDisplayName();
                //std::cout << itemTitle << " : " << name2 << std::endl;

                plItem = pPl->createItem(itemTitle, CPlotItem::curve2d);
                plItem->addChannel(name1);
                plItem->addChannel(name2);
              }
          }
      }
    else if ((id >= 6) && (id <= 7))
      {
        unsigned C_INT32 imax = mpModel->getReactions().size();
        for (i = 0; i < imax; ++i)
          {
            if (id == 6) //concentration fluxes
              tmp = mpModel->getReactions()[i]->getObject(CCopasiObjectName("Reference=Flux"));
            else if (id == 7) //particle fluxes
              tmp = mpModel->getReactions()[i]->getObject(CCopasiObjectName("Reference=ParticleFlux"));

            if (!tmp) continue;

            name2 = tmp->getCN();
            itemTitle = tmp->getObjectDisplayName();
            //std::cout << itemTitle << " : " << name2 << std::endl;

            plItem = pPl->createItem(itemTitle, CPlotItem::curve2d);
            plItem->addChannel(name1);
            plItem->addChannel(name2);
          }
      }
    else
      return false;

    return true;
  }

// propably for optimization only

bool CCopasiProblem::initialize() {return true;}

bool CCopasiProblem::calculate() {return true;}

bool CCopasiProblem::checkParametricConstraints() {return true;}

bool CCopasiProblem::checkFunctionalConstraints() {return true;}
