/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CopasiPlot.cpp,v $
   $Revision: 1.26 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/28 17:09:14 $
   End CVS Header */

#include <qmemarray.h>
#include <qevent.h>
#include <qstring.h>
#include <qcolor.h>   //might need to go to the header file

#include <qpainter.h>
#include <qwt_plot_canvas.h>
#include <qwt_curve.h>
#include <qwt_scale.h>

#include <float.h>

#include "CopasiPlot.h"
#include "CPlotSpec2Vector.h"
#include "CPlotSpecification.h"
#include "CopasiUI/qtUtilities.h"

MyQwtCPointerData::MyQwtCPointerData(const double *x, const double *y,
                                     size_t size):
    d_x(x), d_y(y), d_size(size)
{}

MyQwtCPointerData& MyQwtCPointerData::operator=(const MyQwtCPointerData &data)
{
  if (this != &data)
    {
      d_x = data.d_x;
      d_y = data.d_y;
      d_size = data.d_size;
    }
  return *this;
}

size_t MyQwtCPointerData::size() const
  {
    return d_size;
  }

double MyQwtCPointerData::x(size_t i) const
  {
    return d_x[int(i)];
  }

double MyQwtCPointerData::y(size_t i) const
  {
    return d_y[int(i)];
  }

QwtData *MyQwtCPointerData::copy() const
  {
    return new MyQwtCPointerData(d_x, d_y, d_size);
  }

QwtDoubleRect MyQwtCPointerData::boundingRect() const
  {
    const size_t sz = size();

    if (sz <= 0)
      return QwtDoubleRect(1.0, -1.0, 1.0, -1.0); // invalid

    double minX, maxX, minY, maxY;
    const double *xIt = d_x;
    const double *yIt = d_y;
    const double *end = d_x + sz;

  while (*xIt != *xIt) {xIt++; yIt++;}
    minX = maxX = *xIt++;
    minY = maxY = *yIt++;

    while (xIt < end)
      {
        const double xv = *xIt++;
        const double yv = *yIt++;

        if (isnan(xv)) //NaN
          continue;

        if (xv < minX)
          minX = xv;
        if (xv > maxX)
          maxX = xv;

        if (yv < minY)
          minY = yv;
        if (yv > maxY)
          maxY = yv;
      }

    //std::cout << minX <<" " <<maxX <<" " << minY<< "  " << maxY<<  std::endl;
    return QwtDoubleRect(minX, maxX, minY, maxY);
  }

//draw the several curves, separated by NaNs.
void MyQwtPlotCurve::myDrawLines(QPainter *painter,
                                 const QwtDiMap &xMap, const QwtDiMap &yMap, int from, int to)
{
  int to2;
  do
    {
      int i;
      for (i = from; i <= to; ++i)
        if (isnan(x(i))) //NaN
          break;

      if (i == from)
        {
          ++from;
          continue;
        }

      to2 = i - 1;

      QPointArray polyline(to2 - from + 1);
      for (i = from; i <= to2; i++)
        {
          int xi = xMap.transform(x(i));
          int yi = yMap.transform(y(i));

          polyline.setPoint(i - from, xi, yi);
        }

      QwtPainter::drawPolyline(painter, polyline);

      if (painter->brush().style() != Qt::NoBrush)
        {
          closePolyline(xMap, yMap, polyline);
          painter->setPen(QPen(Qt::NoPen));
          QwtPainter::drawPolygon(painter, polyline);
        }

      from = to2 + 2;
    }
  while (from < to);
}

//************************************

void CopasiPlot::createIndices(CPlotSpec2Vector* psv, const CPlotSpecification* pspec)
{
  indexTable.clear();
  indexTableNames.clear();

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
                {
                  indexTable.push_back(index);

                  //store object names
                  CCopasiObject* tmpObj =
                    CCopasiContainer::ObjectFromName(pspec->getItems()[i]->getChannels()[jj]);
                  if (tmpObj)
                    indexTableNames.push_back(tmpObj->getObjectDisplayName());
                  else
                    indexTableNames.push_back("?");
                }
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

  /*int j;
  std::cout << "****** create indices **********" << std::endl;  
  std::cout << "       indexTable: " << indexTable.size() <<  std::endl;  
  for (i=0; i<indexTable.size();   ++i)
    std::cout << "         : " << indexTable[i] <<  std::endl;  
  std::cout << "       dataIndices: " << dataIndices.size() <<  std::endl;  
  for (i=0; i<dataIndices.size();   ++i)
    for (j=0; j<dataIndices[i].size();   ++j)
      std::cout << "         : " << i << " : " << dataIndices[i][j] <<  std::endl;  
  */

  //the indexTable now has a list of all the indices of the channels that need to be stored
  //internally in the copasiPlot (the channels that are needed for curves, not histograms).

  //indexTableNames contains the corresponding display names (not yet implemented)

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
      QwtPlotCurve* tmpCurve = new MyQwtPlotCurve(this, FROM_UTF8(pItem->getTitle()));
      long crv = insertCurve(tmpCurve);

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

      const void* tmp;
      switch (tmpType)
        {
        case CPlotItem::curve2d :
          unsigned C_INT32 tmpType;
          if (!(tmp = pItem->getValue("Line type").pVOID))
            tmpType = 0; //or error?
          else
            tmpType = *(const unsigned C_INT32*)tmp;
          switch (tmpType)
            {
            case 0:          //curve
              setCurveStyle(crv, QwtCurve::Lines);
              break;
            case 1:          //points
              setCurveStyle(crv, QwtCurve::Dots);
              break;
            case 2:          //symbols
              setCurveStyle(crv, QwtCurve::NoCurve);
              const QColor &c = curveColours[k % 5];
              setCurveSymbol(crv, QwtSymbol(QwtSymbol::Cross, QBrush(c), QPen(c), QSize(5, 5)));
              break;
            }
          break;

        case CPlotItem::histoItem1d :
          C_FLOAT64 tmpIncr;
          if (!(tmp = pItem->getValue("increment").pVOID))
            tmpIncr = 0.1; //or error?
          else
            tmpIncr = *(const C_FLOAT64*)tmp;

          mHistograms.push_back(CHistogram(tmpIncr));
          mHistoIndices[k] = mHistograms.size() - 1;

          setCurveStyle(crv, QwtCurve::Steps);
          setCurveYAxis(crv, QwtPlot::yRight);
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
          updateCurves(false); //tell the curves that the location of the data has changed
          //otherwise repaint events could crash
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

void CopasiPlot::updateCurves(bool doHisto)
{
  // TODO: only do this once
  QMemArray<long> crvKeys = curveKeys();
  CPlotItem::Type tmpType;

  unsigned C_INT32 k;
  for (k = 0; k < crvKeys.size(); k++)
    {
      tmpType = (CPlotItem::Type)mItemTypes[k];
      QwtData* tmpData;
      switch (tmpType)
        {
        case CPlotItem::curve2d :
          tmpData = new MyQwtCPointerData(data[dataIndices[k][0]]->data(),
                                          data[dataIndices[k][1]]->data(),
                                          ndata);
          curve(crvKeys.at(k))->setData(*tmpData);
          break;

        case CPlotItem::histoItem1d :
          if (doHisto)
            curve(crvKeys.at(k))->setRawData(mHistograms[mHistoIndices[k]].getXArray(),
                                             mHistograms[mHistoIndices[k]].getYArray(),
                                             mHistograms[mHistoIndices[k]].size());
          break;

        default :
          fatalError();
        }
    }
}

void CopasiPlot::updatePlot()
{
  updateCurves(true);

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

      /*
      if (c->enabled())
        c->setAxis(QwtPlot::xBottom, QwtPlot::yLeft);
      else
        c->setAxis(QwtPlot::xTop, QwtPlot::yRight);
      */
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

bool CopasiPlot::saveData(const std::string & filename)
{
  std::ofstream fs(filename.c_str());
  if (!fs.good()) return false;

  if (indexTable.size() && ndata) //we have curves
    {
      //first the names
      fs << "# ";
      unsigned C_INT32 i, imax = indexTable.size();
      for (i = 0; i < imax; ++i)
        fs << indexTableNames[i] << "\t";
      fs << "\n";

      //now the data
      unsigned j, jmax = ndata;
      for (j = 0; j < jmax; ++j)
        {
          if (!isnan(data[0]->at(j))) // not NaN
            {
              for (i = 0; i < imax; ++i)
                fs << data[i]->at(j) << "\t";
            }
          fs << "\n";
        }
    }

  if (mHistograms.size())
    {
      fs << "\n# The histograms: \n";

      C_INT32 i, imax;

      C_INT32 j, jmax = mHistograms.size();
      for (j = 0; j < jmax; ++j)
        {
          fs << "\n";

          imax = mHistograms[j].size();
          const double* x = mHistograms[j].getXArray();
          const double* y = mHistograms[j].getYArray();
          for (i = 0; i < imax; ++i)
            {
              fs << *x++ << "\t" << *y++ << "\n";
            }
        }
    }

  fs.close();
  if (!fs.good()) return false;

  return true;
}
