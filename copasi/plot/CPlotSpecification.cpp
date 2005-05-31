/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/CPlotSpecification.cpp,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/05/31 09:43:16 $
   End CVS Header */

#include "model/CModel.h"

#include "CPlotSpecification.h"
#include "report/CCopasiObjectReference.h"

CPlotSpecification::CPlotSpecification(const std::string & name,
                                       const CCopasiContainer * pParent,
                                       const CPlotSpecification::Type & type):
    CPlotItem(name, pParent, type),
    items("Curves", this),
    mActive(true)
{initObjects();}

CPlotSpecification::CPlotSpecification(const CPlotSpecification & src,
                                       const CCopasiContainer * pParent):
    CPlotItem(src, pParent),
    items(src.getItems(), this),
    mActive(src.mActive)
{initObjects();}

CPlotSpecification::~CPlotSpecification() {}

void CPlotSpecification::cleanup()
{
  items.cleanup();
  this->CPlotItem::cleanup();
}

void CPlotSpecification::initObjects()
{
  CCopasiContainer::addObjectReference("Active", mActive, CCopasiObject::ValueBool);
}

void CPlotSpecification::setActive(bool act)
{
  //std::cout << "plotspec::setActive " << act << std::endl;
  mActive = act;
}

bool CPlotSpecification::isActive() const
  {
    //std::cout << "plotspec::getActive " << mActive << std::endl;
    return mActive;
  }

CPlotItem* CPlotSpecification::createItem(const std::string & name, CPlotItem::Type type)
{
  CPlotItem * itm = new CPlotItem(name, NULL, type);

  if (!items.add(itm, true))
    {
      delete itm;
      return NULL;
    }

  return itm;
}

bool CPlotSpecification::createDefaultPlot(const CModel* model)
{
  mActive = true;

  //TODO cleanup before?
  //title = "Default Data Plot 2D";

  CPlotItem * plItem;
  std::string itemTitle;
  CPlotDataChannelSpec name2;
  const CCopasiObject * tmp;

  CPlotDataChannelSpec name1 = model->getObject(CCopasiObjectName("Reference=Time"))->getCN();
  std::cout << name1 << std::endl;

  unsigned C_INT32 i, imax = model->getMetabolites().size();
  for (i = 0; i < imax; ++i)
    {
      tmp = model->getMetabolites()[i]->getObject(CCopasiObjectName("Reference=Concentration"));
      name2 = tmp->getCN();
      itemTitle = tmp->getObjectDisplayName();
      //std::cout << itemTitle << " : " << name2 << std::endl;

      plItem = this->createItem(itemTitle, CPlotItem::curve2d);
      plItem->addChannel(name1);
      plItem->addChannel(name2);
    }
  return true; //TODO: really check;
}
