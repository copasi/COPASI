/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/CPlotSpecification.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/08/10 10:58:56 $
   End CVS Header */

#include "model/CModel.h"

#include "CPlotSpecification.h"

CPlotSpecification::CPlotSpecification(const std::string & name,
                                       const CCopasiContainer * pParent,
                                       const CPlotSpecification::Type & type):
    CPlotItem(name, pParent, type),
    mActive(true)
{}

CPlotSpecification::CPlotSpecification(const CPlotSpecification & src,
                                       const CCopasiContainer * pParent):
    CPlotItem(src, pParent),
    items(src.getItems()),
    mActive(true)
{}

CPlotSpecification::~CPlotSpecification() {}

void CPlotSpecification::cleanup()
{
  items.cleanup();
  this->CPlotItem::cleanup();
}

void CPlotSpecification::initObjects()
{}

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

  /*axes.resize(4);

  axes[QwtPlot::xBottom].active = true;
  axes[QwtPlot::xBottom].autoscale = true;
  axes[QwtPlot::xBottom].title = "X-Achse";

  axes[QwtPlot::yLeft].active = true;
  axes[QwtPlot::yLeft].autoscale = true;
  axes[QwtPlot::yLeft].title = "Y-Achse";

  axes[QwtPlot::xTop].active = false;
  axes[QwtPlot::xTop].autoscale = true;
  axes[QwtPlot::xTop].title = "X2-Achse";

  axes[QwtPlot::yRight].active = false;
  axes[QwtPlot::yRight].autoscale = true;
  axes[QwtPlot::yRight].title = "Y2-Achse";*/

  CPlotItem * plItem;
  std::string itemTitle;
  CPlotDataChannelSpec name2;

  CPlotDataChannelSpec name1 = model->getObject(CCopasiObjectName("Reference=Time"))->getCN();
  std::cout << name1 << std::endl;

  unsigned C_INT32 i, imax = model->getMetabolites().size();
  for (i = 0; i < imax; ++i)
    {
      name2 = model->getMetabolites()[i]->getObject(CCopasiObjectName("Reference=Concentration"))->getCN();
      itemTitle = model->getMetabolites()[i]->getObjectName();
      std::cout << itemTitle << " : " << name2 << std::endl;

      plItem = this->createItem(itemTitle, CPlotItem::curve2d);
      plItem->addChannel(name1);
      plItem->addChannel(name2);
    }
  return true; //TODO: really check;
}
