/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CopasiPlot.cpp,v $
   $Revision: 1.26.8.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2006/01/26 16:32:57 $
   End CVS Header */

#include <qstring.h>
#include <qcolor.h>   //might need to go to the header file

#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_scale_engine.h>

#include <float.h>

#include "scrollzoomer.h"

#include "CopasiPlot.h"
#include "CPlotSpec2Vector.h"
#include "CPlotSpecification.h"
#include "CopasiUI/qtUtilities.h"

//********************  curve  ********************************************

//draw the several curves, separated by NaNs.
void MyQwtPlotCurve::myDrawLines(QPainter *painter,
                                 const QwtScaleMap &xMap, const QwtScaleMap &yMap,
                                 int from, int to) const
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

        QwtPlotCurve::drawLines(painter, xMap, yMap, from, to2);

        from = to2 + 2;
      }
    while (from < to);
  }

//virtual
void MyQwtPlotCurve::drawCurve(QPainter *painter, int style,
                               const QwtScaleMap &xMap, const QwtScaleMap &yMap,
                               int from, int to) const
  {
    if (style == Lines)
      myDrawLines(painter, xMap, yMap, from, to);
    else
      QwtPlotCurve::drawCurve(painter, style, xMap, yMap, from, to);
  }

//************************************

CopasiPlot::CopasiPlot(CPlotSpec2Vector* psv, const CPlotSpecification* plotspec, QWidget* parent)
    : QwtPlot(parent),
    mZoomer(NULL)
{
  QwtLegend *legend = new QwtLegend;
  legend->setItemMode(QwtLegend::CheckableItem);
  insertLegend(legend, QwtPlot::BottomLegend);

  mZoomer = new ScrollZoomer(canvas());
  mZoomer->setRubberBandPen(QColor(Qt::black));
  mZoomer->setTrackerPen(QColor(Qt::black));
  mZoomer->setTrackerMode(QwtPicker::AlwaysOn);

  /*QwtPlotPicker * a_picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,
      QwtPicker::PointSelection | QwtPicker::DragSelection, 
      QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn, 
      canvas());
  a_picker->setRubberBandPen(QColor(Qt::green));
  a_picker->setTrackerPen(QColor(Qt::blue));*/

  initFromSpec(psv, plotspec);

  // white background better for printing...
  setCanvasBackground(white);

  //  setTitle(FROM_UTF8(plotspec->getTitle()));
  setCanvasLineWidth(0);

  // signal and slot connections
  //connect(this, SIGNAL(plotMousePressed(const QMouseEvent &)),
  //        SLOT(mousePressed(const QMouseEvent&)));
  //connect(this, SIGNAL(plotMouseReleased(const QMouseEvent &)),
  //        SLOT(mouseReleased(const QMouseEvent&)));
  //connect(this, SIGNAL(legendClicked(long)),
  //        SLOT(toggleCurve(long)));

  canvas()->setPaintAttribute(QwtPlotCanvas::PaintPacked, true);

  const bool cacheMode =
    canvas()->testPaintAttribute(QwtPlotCanvas::PaintCached);

  //canvas()->setPaintAttribute(QwtPlotCanvas::PaintCached, false);
  //d_curve->draw(0, d_curve->dataSize() - 1);
  //canvas()->setPaintAttribute(QwtPlotCanvas::PaintCached, cacheMode);

  //setAxisScaleEngine(xBottom, new QwtLog10ScaleEngine());

  connect(this, SIGNAL(legendChecked(QwtPlotItem *, bool)),
          SLOT(showCurve(QwtPlotItem *, bool)));
}

bool CopasiPlot::initFromSpec(CPlotSpec2Vector* psv, const CPlotSpecification* plotspec)
{
  mZoomer->setEnabled(false);

  if (plotspec->isLogX())
    setAxisScaleEngine(xBottom, new QwtLog10ScaleEngine());
  else
    setAxisScaleEngine(xBottom, new QwtLinearScaleEngine());

  if (plotspec->isLogY())
    setAxisScaleEngine(yLeft, new QwtLog10ScaleEngine());
  else
    setAxisScaleEngine(yLeft, new QwtLinearScaleEngine());

  replot();

  createIndices(psv, plotspec);

  setTitle(FROM_UTF8(plotspec->getTitle()));

  //removeCurves();
  detachItems();
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
      QwtPlotCurve* tmpCurve = new MyQwtPlotCurve(FROM_UTF8(pItem->getTitle()));
      tmpCurve->setPen(curveColours[k % 5]);
      tmpCurve->attach(this);
      mQwtItems[k] = tmpCurve;

      // activate the legend button
      QwtLegendItem *li = dynamic_cast<QwtLegendItem*>(legend()->find(tmpCurve));
      if (li) li->setChecked(true);

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
              tmpCurve->setStyle(QwtPlotCurve::Lines);
              break;
            case 1:          //points
              tmpCurve->setStyle(QwtPlotCurve::Dots);
              break;
            case 2:          //symbols
              tmpCurve->setStyle(QwtPlotCurve::NoCurve);
              const QColor &c = curveColours[k % 5];
              tmpCurve->setSymbol(QwtSymbol(QwtSymbol::Cross, QBrush(c), QPen(c), QSize(5, 5)));
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

          tmpCurve->setStyle(QwtPlotCurve::Steps);
          tmpCurve->setYAxis(QwtPlot::yRight);
          break;

        default :
          fatalError();
        }
    }

  updateCurves(false);

  if (plotspec->isLogX())
    setAxisScaleEngine(xBottom, new QwtLog10ScaleEngine());
  else
    setAxisScaleEngine(xBottom, new QwtLinearScaleEngine());
  setAxisAutoScale(xBottom);

  if (plotspec->isLogY())
    setAxisScaleEngine(yLeft, new QwtLog10ScaleEngine());
  else
    setAxisScaleEngine(yLeft, new QwtLinearScaleEngine());
  setAxisAutoScale(yLeft);

  replot();

  return true; //TODO really check!
}

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
  mQwtItems.resize(imax);
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

  //QMemArray<long> crvKeys = curveKeys();
  CPlotItem::Type tmpType;

  unsigned C_INT32 k;
  for (k = 0; k < mQwtItems.size(); k++)
    {
      tmpType = (CPlotItem::Type)mItemTypes[k];
      QwtData* tmpData;

      QwtPlotCurve * tmpCurve;
      switch (tmpType)
        {
        case CPlotItem::curve2d :
          tmpData = new /*My*/QwtCPointerData(data[dataIndices[k][0]]->data(),
                                              data[dataIndices[k][1]]->data(),
                                              ndata);
          tmpCurve = dynamic_cast<QwtPlotCurve*>(mQwtItems[k]);
          if (!tmpCurve) continue;
          tmpCurve->setData(*tmpData);
          break;

        case CPlotItem::histoItem1d :
          if (doHisto)
            {
              tmpCurve = dynamic_cast<QwtPlotCurve*>(mQwtItems[k]);
              if (!tmpCurve) continue;
              tmpCurve->setRawData(mHistograms[mHistoIndices[k]].getXArray(),
                                   mHistograms[mHistoIndices[k]].getYArray(),
                                   mHistograms[mHistoIndices[k]].size());
            }
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
  //if (mZoomer)
  //mZoomer->setZoomBase();
}

void CopasiPlot::finishPlot()
{
  if (mZoomer)
    {
      mZoomer->setEnabled(true);
      mZoomer->setZoomBase();
    }
}
//-----------------------------------------------------------------------------

/*void CopasiPlot::enableZoom(bool enabled)
{
  zoomOn = enabled;
}*/

//-----------------------------------------------------------------------------

CopasiPlot::~CopasiPlot()
{
  //removeCurves();
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

void CopasiPlot::showCurve(QwtPlotItem *item, bool on)
{
  item->setVisible(on);
  item->setItemAttribute(QwtPlotItem::AutoScale, on);
  QWidget *w = legend()->find(item);
  if (w && w->inherits("QwtLegendItem"))
    ((QwtLegendItem *)w)->setChecked(on);

  //mZoomer->setZoomBase();

  replot();
}
