/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/CopasiPlot.cpp,v $
   $Revision: 1.20 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/25 13:42:22 $
   End CVS Header */

#include <qmemarray.h>
#include <qevent.h>
#include <qstring.h>
#include <qcolor.h>   //might need to go to the header file

#include <qpainter.h>
#include <qwt_plot_canvas.h>
#include <qwt_curve.h>
#include <qwt_scale.h>

#include "CopasiPlot.h"
#include "CPlotSpec2Vector.h"
#include "CPlotSpecification.h"
#include "CopasiUI/qtUtilities.h"

//TODO: put all the stuff to locally store the data in a separate class!

void CopasiPlot::createIndices(CPlotSpec2Vector* psv, const CPlotSpecification* pspec)
{
  indexTable.resize(0);

  C_INT32 jj, jjmax;
  C_INT32 index;
  std::vector<C_INT32>::iterator it; // iterator for indexTable
  C_INT32 iterindex;
  CPlotItem::Type tmpType;

  C_INT32 i, imax = pspec->getItems().size();
  dataIndices.resize(imax);
  mItemTypes.resize(imax);
  for (i = 0; i < imax; ++i) //all curves
    {
      jjmax = pspec->getItems()[i]->getNumChannels();
      dataIndices[i].resize(jjmax);
      tmpType = pspec->getItems()[i]->getType();
      mItemTypes[i] = (C_INT32)tmpType;

      switch (tmpType)
        {
        case CPlotItem::curve2d :
          for (jj = 0; jj < jjmax; ++jj) //all Channels
            {
              //get the index in the data vector
              index = psv->getIndexFromCN(pspec->getItems()[i]->getChannels()[jj]);

              for (it = indexTable.begin(), iterindex = 0; it != indexTable.end(); ++it, ++iterindex)
              {if (*it == index) break;};
              if (it == indexTable.end()) //index is not yet in indexTable
                indexTable.push_back(index);
              dataIndices[i][jj] = iterindex;
            }
          break;

        case CPlotItem::histoItem1d :
          for (jj = 0; jj < jjmax; ++jj) //all Channels
            {
              //get the index in the data vector
              index = psv->getIndexFromCN(pspec->getItems()[i]->getChannels()[jj]);
              dataIndices[i][jj] = index;
            }
          break;

        default :
          fatalError();
        }
    }
  //the indexTable now has a list of all the indices of the channels that need to be stored
  //internally in the copasiPlot (the channels that are needed for curves, not histograms).

  //the meaning of the dataIndices[][] differs for curves/histograms:
  //  curves: points to an entry in indexTable (stored channels)
  //  histograms: points to an entry in the data vector
}

CopasiPlot::CopasiPlot(CPlotSpec2Vector* psv, const CPlotSpecification* plotspec, QWidget* parent)
    : ZoomPlot(parent), zoomOn(false)
{
  // set up legend
  enableLegend(TRUE);
  setAutoLegend(TRUE); //curves have to be inserted after this is set
  setLegendPos(Qwt::Bottom);
  //enableLegend(FALSE);
  //setAutoLegend(FALSE); //curves have to be inserted after this is set

  initFromSpec(psv, plotspec);

  // white background better for printing...
  setCanvasBackground(white);

  //  setTitle(FROM_UTF8(plotspec->getTitle()));
  setCanvasLineWidth(0);

  // signal and slot connections
  connect(this, SIGNAL(plotMousePressed(const QMouseEvent &)),
          SLOT(mousePressed(const QMouseEvent&)));
  connect(this, SIGNAL(plotMouseReleased(const QMouseEvent &)),
          SLOT(mouseReleased(const QMouseEvent&)));
  connect(this, SIGNAL(legendClicked(long)),
          SLOT(toggleCurve(long)));
}

bool CopasiPlot::initFromSpec(CPlotSpec2Vector* psv, const CPlotSpecification* plotspec)
{
  createIndices(psv, plotspec);

  setTitle(FROM_UTF8(plotspec->getTitle()));

  removeCurves();
  mHistograms.clear();
  mHistoIndices.resize(plotspec->getItems().size());

  //delete Buffers
  while (data.size() > 0)
    {
      delete data[data.size() - 1];
      data.pop_back();
    }

  //recreate buffers
  for (unsigned int i = 0; i < indexTable.size(); i++)
    {//TODO !!
      QMemArray<double>* v = new QMemArray<double>(500);  // initial size = 500
      data.push_back(v);
    }
  ndata = 0;

  QColor curveColours[5] = {red, blue, green, cyan, magenta}; //TODO
  CPlotItem::Type tmpType;
  CPlotItem* pItem;
  unsigned C_INT32 k;
  for (k = 0; k < plotspec->getItems().size(); k++)
    {
      pItem = plotspec->getItems()[k];

      // set up the curve
      long crv = insertCurve(FROM_UTF8(pItem->getTitle()));

      setCurvePen(crv, QPen(curveColours[k % 5]));
      //      setCurveXAxis(crv, plotspec->getItems()[k].xAxis);
      //      setCurveYAxis(crv, plotspec->getItems()[k].yAxis);

      QwtLegendButton* button = dynamic_cast<QwtLegendButton*>(legend()->findItem(crv));
      if (button)
        {
          button->setToggleButton(true);
          button->setOn(true);
        }

      tmpType = (CPlotItem::Type)mItemTypes[k];

      switch (tmpType)
        {
        case CPlotItem::curve2d :
          break;

        case CPlotItem::histoItem1d :
          C_FLOAT64 tmpIncr;
          const void* tmp;
          if (!(tmp = pItem->getValue("increment")))
            tmpIncr = 0.1; //or error?
          else
            tmpIncr = *(const C_FLOAT64*)tmp;

          mHistograms.push_back(CHistogram(tmpIncr));
          mHistoIndices[k] = mHistograms.size() - 1;

          setCurveStyle(crv, QwtCurve::Steps);
          break;

        default :
          fatalError();
        }
    }

  //setAxisOptions(QwtPlot::yLeft,QwtAutoScale::Logarithmic);
  return true; //TODO really check!
}

void CopasiPlot::takeData(const std::vector<C_FLOAT64> & dataVector)
{
  unsigned C_INT32 i;

  if (data.size() != 0)
    {
      if (ndata >= data[0]->size())
        {
          unsigned C_INT32 newSize = data[0]->size() + 1000;
          for (i = 0; i < data.size(); i++)
            data[i]->resize(newSize);
        }

      //the data that needs to be stored internally:
      for (i = 0; i < indexTable.size(); ++i)
        {
          data[i]->at(ndata) = dataVector[indexTable[i]];
        }
      ++ndata;
    }
  //the data that is used immediately:
  for (i = 0; i < mItemTypes.size(); ++i)
    {
      if ((CPlotItem::Type)mItemTypes[i] == CPlotItem::histoItem1d)
        {
          mHistograms[mHistoIndices[i]].addValue(dataVector[dataIndices[i][0]]);
        }
    }
}

void CopasiPlot::updatePlot()
{
  // TODO: only do this once
  QMemArray<long> crvKeys = curveKeys();
  CPlotItem::Type tmpType;

  unsigned C_INT32 k;
  for (k = 0; k < crvKeys.size(); k++)
    {
      tmpType = (CPlotItem::Type)mItemTypes[k];

      switch (tmpType)
        {
        case CPlotItem::curve2d :
          curve(crvKeys.at(k))->setRawData(data[dataIndices[k][0]]->data(),
                                           data[dataIndices[k][1]]->data(),
                                           ndata);
          break;

        case CPlotItem::histoItem1d :
          curve(crvKeys.at(k))->setRawData(mHistograms[mHistoIndices[k]].getXArray(),
                                           mHistograms[mHistoIndices[k]].getYArray(),
                                           mHistograms[mHistoIndices[k]].size());
          break;

        default :
          fatalError();
        }
      //drawCurveInterval(crvKeys[k], 0, ndata-1);
    }
  replot();
}

//-----------------------------------------------------------------------------

/*void CopasiPlot::drawCurveInterval(long curveId, int from, int to)
{
  // taken from the realtime_plot example from Qwt library...
  QwtPlotCurve *curve = CopasiPlot::curve(curveId);
  if (curve == 0)
    return;
 
  QPainter p(canvas());
 
  p.setClipping(TRUE);
  p.setClipRect(canvas()->rect());
 
  curve->draw(&p,
              canvasMap(curve->xAxis()), canvasMap(curve->yAxis()),
              from, to);
}*/

//-----------------------------------------------------------------------------

void CopasiPlot::enableZoom(bool enabled)
{
  zoomOn = enabled;
}

//-----------------------------------------------------------------------------

void CopasiPlot::mousePressed(const QMouseEvent &e)
{
  if (zoomOn)
    {
      // zooming is now supported, so simply call the method in the base class
      ZoomPlot::mousePressed(e);
    }
  else
    {
      setOutlineStyle(Qwt::Cross);
      enableOutline(TRUE);
    }
}

//-----------------------------------------------------------------------------

void CopasiPlot::mouseReleased(const QMouseEvent &e)
{
  if (!zoomOn)
    return;

  ZoomPlot::mouseReleased(e);

  if (e.button() == RightButton)
    zoomOn = false;
}

//-----------------------------------------------------------------------------

void CopasiPlot::toggleCurve(long curveId)
{
  QwtPlotCurve *c = curve(curveId);
  if (c)
    {
      c->setEnabled(!c->enabled());

      if (c->enabled())
        c->setAxis(QwtPlot::xBottom, QwtPlot::yLeft);
      else
        c->setAxis(QwtPlot::xTop, QwtPlot::yRight);

      replot();
    }
}

//-----------------------------------------------------------------------------

CopasiPlot::~CopasiPlot()
{
  removeCurves();
  //delete pointers sourcefile and plotSpec?

  while (data.size() > 0)
    {
      delete data[data.size() - 1];
      data.pop_back();
    }
}
