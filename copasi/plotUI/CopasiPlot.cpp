/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/CopasiPlot.cpp,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/03 20:30:24 $
   End CVS Header */

#include <qarray.h>
#include <qevent.h>
#include <qstring.h>
#include <qcolor.h>   //might need to go to the header file

#include <qpainter.h>
#include <qwt_plot_canvas.h>
#include <qwt_curve.h>
#include <qwt_scale.h>

#include "CopasiPlot.h"
#include "CPlotSpec.h"
#include "CopasiUI/qtUtilities.h"

//TODO: put all the stuff to locally store the data in a separate class!

void CopasiPlot::createIndices()
{
  C_INT32 i, imax = ptspec->getCurves().size();
  C_INT32 index;
  std::vector<C_INT32>::iterator it; // iterator for indexTable
  C_INT32 iterindex;
  dataIndices.resize(imax);

  for (i = 0; i < imax; ++i)
    {
      //TODO generalize to N dims.
      dataIndices[i].resize(2);

      index = ptspec->getCurves()[i].xChannel.index;
      for (it = indexTable.begin(), iterindex = 0; it != indexTable.end(); ++it, ++iterindex)
      {if (*it >= index) break;};
      if (it == indexTable.end()) //index is not yet in indexTable
        indexTable.insert(it, index);
      else if (*it != index)
        indexTable.insert(it, index);
      dataIndices[i][0] = iterindex;

      index = ptspec->getCurves()[i].yChannel.index;
      for (it = indexTable.begin(), iterindex = 0; it != indexTable.end(); ++it, ++iterindex)
      {if (*it >= index) break;};
      if (it == indexTable.end()) //index is not yet in indexTable
        indexTable.insert(it, index);
      else if (*it != index)
        indexTable.insert(it, index);
      dataIndices[i][1] = iterindex;
    }
}

CopasiPlot::CopasiPlot(CPlotSpec* plotspec, QWidget* parent)
    : ZoomPlot(parent), zoomOn(false)
{
  ptspec = plotspec;
  createIndices();

  // white background better for printing...
  setCanvasBackground(white);

  setTitle(FROM_UTF8(ptspec->getTitle()));
  setCanvasLineWidth(0);

  // allocate memory for the plotting data
  for (unsigned int i = 0; i < indexTable.size(); i++)
    {
      QMemArray<double>* v = new QMemArray<double>(500);  // initial size = 500
      data.push_back(v);
    }
  ndata = 0;

  // set up legend
  setAutoLegend(TRUE);
  setLegendPos(Qwt::Right);
  //??enableLegend(TRUE);
  //??setLegendFrameStyle(QFrame::Box|QFrame::Sunken);

  // the colours for different curves to use - should be moved to header file as static member?
  // surely there's a better place for it than here.
  // NB: this should be the same as in redrawCurve() and reloadPlot()
  QColor curveColours[6] = {red, yellow, blue, green, cyan, magenta};

  // insert curves, though without data yet
  unsigned C_INT32 k;
  for (k = 0; k < ptspec->getCurves().size(); k++)
    {
      // set up the curve
      long crv = insertCurve(FROM_UTF8(ptspec->getCurves()[k].title));

      setCurvePen(crv, QPen(curveColours[k]));
      setCurveXAxis(crv, ptspec->getCurves()[k].xAxis);
      setCurveYAxis(crv, ptspec->getCurves()[k].yAxis);
    }

  // signal and slot connections
  connect(this, SIGNAL(plotMousePressed(const QMouseEvent &)),
          SLOT(mousePressed(const QMouseEvent&)));
  connect(this, SIGNAL(plotMouseReleased(const QMouseEvent &)),
          SLOT(mouseReleased(const QMouseEvent&)));
  connect(this, SIGNAL(legendClicked(long)),
          SLOT(redrawCurve(long)));
}

void setupAxes()
{
  /*
  // Set up axes
  // enable the axes just in case
  enableAxis(cspec->xAxis);
  enableAxis(cspec->yAxis);

  // set axes titles
  // might need some tidying up as to whether to use QString and standard string
  QString qs1(_toUtf8(cspec->axisTitles[0]));
  setAxisTitle(cspec->xAxis, qs1);
  QString qs2(_toUtf8(cspec->axisTitles[1]));
  setAxisTitle(cspec->yAxis, qs2);

  //TODO: maybe set axis titles the same colour as the curve?
  // but can't see any methods for doing this...
  */
}

void CopasiPlot::takeData(const std::vector<C_FLOAT64> & dataVector)
{
  unsigned C_INT32 i;
  if (ndata >= data[0]->size())
    {
      unsigned C_INT32 newSize = data[0]->size() + 1000;
      for (i = 0; i < data.size(); i++)
        data[i]->resize(newSize);
    }

  for (i = 0; i < indexTable.size(); ++i)
    {
      data[i]->at(ndata) = dataVector[indexTable[i]];
    }
  ++ndata;
}

void CopasiPlot::updatePlot()
{
  // TODO: only do this once
  QMemArray<long> crvKeys = curveKeys();

  unsigned C_INT32 k;
  for (k = 0; k < crvKeys.size(); k++)
    {
      curve(crvKeys.at(k))->setRawData(data[dataIndices[k][0]]->data(),
                                       data[dataIndices[k][1]]->data(),
                                       ndata);
      //drawCurveInterval(crvKeys[k], 0, ndata-1);
    }
  replot();
}

//-----------------------------------------------------------------------------

void CopasiPlot::drawCurveInterval(long curveId, int from, int to)
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
}

//-----------------------------------------------------------------------------

void CopasiPlot::reload2Plot(CPlotSpec* plotspec, std::vector<int> deletedCurveKeys)
{
  /* // is this necessary? the pointers should actually be the same...
   ptspec = plotspec;

   // make sure we're zoomed out
   zoomOut();
   setAxisAutoScale(QwtPlot::yLeft);
   setAxisAutoScale(QwtPlot::yRight);
   setAxisAutoScale(QwtPlot::xBottom);
   setAxisAutoScale(QwtPlot::xTop);
   enableZoom(false);

   // remove curves as specified
   QArray<long> crvKeys = curveKeys();
   while (deletedCurveKeys.size() > 0)
     {
       removeCurve(crvKeys[deletedCurveKeys[deletedCurveKeys.size() - 1]]);
       deletedCurveKeys.pop_back();
     }

   unsigned int specNum = ptspec->curves.size();
   bool addCurve = (crvKeys.size() < specNum);   // decide whether to add curve before deleting any

   // is this necessary??
   crvKeys = curveKeys();

   // now we need to insert some curves if there are more curve specs than existing curves
   // this is the case if specNum > keyNum before and/or after curves are removed
   unsigned int keyNum = crvKeys.size();
   if ((specNum > keyNum) || addCurve)
     {
       // allocate the extra memory for the plotting data
       int arraySize = data[0]->size();

       for (unsigned int i = keyNum; i < specNum; i++)
         {
           QMemArray<double>* v = new QMemArray<double>(arraySize);  // initial size = 500
           data.push_back(v);
         }

       // get the extra data (from the beginning of the file)
       sourcefile->seekg(0, std::ios::beg);
  */
  /*--------------------------------------------
     hmm, it's a little messy here. the following code will work, but it's equivalent to
     reading in ALL the data, which is surely inefficient. on the other hand, given the characteristics
     specified for ptspec->varIndices, i.e. the elements in the vector should be in ascending order,
     how do we know which is/are the new column/s to pick out???
  */
  /*     unsigned int colNum = 5, index;
       double temp;
       for (int currentRow = 0; currentRow < startRow; currentRow++)
         {
           index = 0;  // the index into the vector varIndices

           for (unsigned int i = 0; i < colNum; i++)
             {
               if (!(*sourcefile >> temp))
                 break;

               if ((index < ptspec->varIndices.size()) && (i == ptspec->varIndices[index]))  // this is in a chosen column
                 {
                   QMemArray<double>* v = data[index++];
                   v->at(currentRow) = temp;
                 }
             }
         }
       //--------------------------------------------

       sourcefile->clear();
       pos = sourcefile->tellg();

       // NB: this should be the same as in redrawCurve() and the constructor
       QColor curveColours[6] = {red, yellow, blue, green, cyan, magenta};

       // set up curves
       for (unsigned int k = keyNum; k < specNum; k++)
         {
           CurveSpec* cspec = ptspec->curves[k];

           // Set up axes
           // enable the axes just in case
           enableAxis(cspec->xAxis);
           enableAxis(cspec->yAxis);

           // set axes titles
           // might need some tidying up as to whether to use QString and standard string
           QString qs1(_toUtf8(cspec->axisTitles[0]));
           setAxisTitle(cspec->xAxis, qs1);
           QString qs2(_toUtf8(cspec->axisTitles[1]));
           setAxisTitle(cspec->yAxis, qs2);

           //TODO: maybe set axis titles the same colour as the curve?
           // but can't see any methods for doing this...

           // set up the curve
           long crv = insertCurve(_toUtf8(cspec->curveTitle));

           setCurvePen(crv, QPen(curveColours[k]));
           setCurveXAxis(crv, cspec->xAxis);
           setCurveYAxis(crv, cspec->yAxis);

           // attach the data - this way might yield better performance when data sets are large
           QwtPlotCurve *curve = CopasiPlot::curve(crv);

           curve->setRawData(data[cspec->coordX]->data(),
                             data[cspec->coordY]->data(),
                             startRow);  // note that startRow now holds the total number of rows read in

           // append each (section of) curve as it's set up
           drawCurveInterval(crv, 0, startRow - 1);
         }
     }

   // otherwise simply display the old plot if there's no change to the specification
   replot();*/
}

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

void CopasiPlot::redrawCurve(long key)
{
  // this is the same as in the constructor
  QColor curveColours[6] = {red, yellow, blue, green, cyan, magenta};

  QPen crvPen = curvePen(key);
  if (crvPen.color() == canvasBackground())
    {
      // the curve is 'hidden', so find its original colour and redraw it
      QMemArray<long> keys = curveKeys();
      for (unsigned int i = 0; i < keys.size(); i++)
        if (keys.at(i) == key)
          {
            setCurvePen(key, QPen(curveColours[i]));
            break;
          }
    }
  else
    {
      // hide the curve by redrawing it using the background colour
      // NB: this could result in incomplete grids on the canvas
      setCurvePen(key, QPen(canvasBackground()));
    }
  replot();
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
