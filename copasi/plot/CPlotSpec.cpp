/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CPlotSpec.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/13 13:36:19 $
   End CVS Header */

#include "copasi.h"

#include "report/CKeyFactory.h" 
//#include "CPlotSpec.h"
#include "model/CModel.h"
#include "CPlotSpecVector.h"

bool CDataChannelSpec::compile(CPlotSpecVector * ps)
{
  index = ps->getIndexFromCN(object);
  return true; //TODO really check;
}

//////////////////////////////////////////////////
//
//class CPlotSpec
//
//////////////////////////////////////////////////

CPlotSpec::CPlotSpec(const std::string & name,
                     const CCopasiContainer * pParent):
    CCopasiObject(name, pParent, "CPlotSpec"),
    mKey(GlobalKeys.add("CPlotSpec", this))
{
  //createDebugPlot(); //preliminary
}

CPlotSpec::CPlotSpec(const CPlotSpec & src,
                     const CCopasiContainer * pParent):
    CCopasiObject(src, pParent),
    mKey(GlobalKeys.add("CPlotSpec", this))
{}

CPlotSpec::~CPlotSpec()
{cleanup();}

void CPlotSpec::cleanup()
{
  GlobalKeys.remove(mKey);
}

/*void CPlotSpec::createDebugPlot()
{
  title = "Data Plot 2D";
 
  //curves.push_back(Curve2DSpec("A", 0, 1));
  //curves.push_back(Curve2DSpec("B", 0, 2));
 
  axes.resize(4);
 
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
  axes[QwtPlot::yRight].title = "Y2-Achse";
}*/

bool CPlotSpec::createDefaultPlot(const CModel* model)
{
  title = "Default Data Plot 2D";

  axes.resize(4);

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
  axes[QwtPlot::yRight].title = "Y2-Achse";

  std::string title;
  CCopasiObjectName name2;

  CCopasiObjectName name1 = model->getObject(CCopasiObjectName("Reference=Time"))->getCN();
  std::cout << name1 << std::endl;

  unsigned C_INT32 i, imax = model->getMetabolites().size();
  for (i = 0; i < imax; ++i)
    {
      name2 = model->getMetabolites()[i]->getObject(CCopasiObjectName("Reference=Concentration"))->getCN();
      title = model->getMetabolites()[i]->getObjectName();
      std::cout << title << " : " << name2 << std::endl;

      curves.push_back(Curve2DSpec(title, name1, name2));
    }
  return true; //TODO: really check;
}

bool CPlotSpec::compile(CPlotSpecVector * ps)
{
  std::vector<Curve2DSpec>::iterator it;
  for (it = curves.begin(); it != curves.end(); ++it)
    if (! it->compile(ps)) return false;

  return true;
}
