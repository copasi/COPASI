/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CPlotSpec.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/01/14 16:59:28 $
   End CVS Header */

#include "copasi.h"

#include "report/CKeyFactory.h"
#include "CPlotSpec.h"

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
  createDebugPlot(); //preliminary
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

void CPlotSpec::createDebugPlot()
{
  title = "Data Plot 2D";

  curves.push_back(Curve2DSpec("A", 0, 1));
  curves.push_back(Curve2DSpec("B", 0, 2));

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
}
