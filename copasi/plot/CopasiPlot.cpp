#include <qarray.h>
#include <qevent.h>
#include <qstring.h>
#include <qcolor.h>   //might need to go to the header file

#include <qpainter.h>
#include <qwt_plot_canvas.h>
#include <qwt_curve.h>
#include <qwt_scale.h>

#include "CopasiPlot.h"
#include "plotspec.h"

CopasiPlot::CopasiPlot(PlotTaskSpec* plotspec, QWidget* parent)
    : ZoomPlot(parent), startRow(0), zoomOn(false)
{
  ptspec = plotspec;

  // white background better for printing...
  setCanvasBackground(white);

  //hideous workaround - TODO: tidy up later!!
  QString qstitle((ptspec->plotTitle).c_str());
  setTitle(qstitle);
  //setTitle(ptspec->plotTitle);

  sourcefile = &(ptspec->sourceStream);
  sourcefile->seekg(0, std::ios::beg);
  pos = sourcefile->tellg();

  // allocate memory for the plotting data
  for (unsigned int i = 0; i < ptspec->varIndices.size(); i++)
    {
      QMemArray<double>* v = new QMemArray<double>(500);  // initial size = 500
      data.push_back(v);
    }

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
  for (unsigned int k = 0; k < (ptspec->curves).size(); k++)
    {
      CurveSpec* cspec = ptspec->curves[k];

      // Set up axes
      // enable the axes just in case
      enableAxis(cspec->xAxis);
      enableAxis(cspec->yAxis);

      // set axes titles
      // might need some tidying up as to whether to use QString and standard string
      QString qs1(cspec->axisTitles[0].c_str());
      setAxisTitle(cspec->xAxis, qs1);
      QString qs2(cspec->axisTitles[1].c_str());
      setAxisTitle(cspec->yAxis, qs2);

      //TODO: maybe set axis titles the same colour as the curve?
      // but can't see any methods for doing this...

      // set up the curve
      long crv = insertCurve(cspec->curveTitle.c_str());

      setCurvePen(crv, QPen(curveColours[k]));
      setCurveXAxis(crv, cspec->xAxis);
      setCurveYAxis(crv, cspec->yAxis);
    }

  // signal and slot connections
  connect(this, SIGNAL(plotMousePressed(const QMouseEvent &)),
          SLOT(mousePressed(const QMouseEvent&)));
  connect(this, SIGNAL(plotMouseReleased(const QMouseEvent &)),
          SLOT(mouseReleased(const QMouseEvent&)));
  connect(this, SIGNAL(legendClicked(long)),
          SLOT(redrawCurve(long)));

  appendPlot();
}

//-----------------------------------------------------------------------------

void CopasiPlot::appendPlot()
{
  // retrieve the data for the plotting task (from all columns)
  // currently we require all curves to draw data from the same rows (across columns)

  // assume we know how many columns there are from somewhere in the simulation
  // for now this is 5
  // same in reloadPlot()
  const unsigned int colNum = 5;

  double temp; // a dummy to take unwanted double from the file

  sourcefile->seekg(pos);

  unsigned int index; // this is the subscript into the vector ptspec->varIndices

  // get the data for the plot up to the end of the file
  int currentRow; // the index of the current row...
  int currentSize = data[0]->size();  // the current size of the arrays holding the plot data

  for (currentRow = startRow; !(sourcefile->eof()); currentRow++)
    {
      index = 0;  // the index into the vector varIndices

      // check the arrays are big enough
      if (currentRow >= currentSize)
        {
          currentSize += 500;

          for (unsigned int i = 0; i < data.size(); i++)
            data[i]->resize(currentSize);
        }

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

  sourcefile->clear();
  currentRow--;  // go back to the proper end of read operation...
  pos = sourcefile->tellg();

  // match data (i.e. columns) with each curve spec and hence produce the plot
  QArray<long> crvKeys = curveKeys();

  for (unsigned int k = 0; k < crvKeys.size(); k++)
    {
      CurveSpec* cspec = ptspec->curves[k];  // the indices of the curve key and its spec should correspond...

      // Attach the data
      //setCurveData(crvKeys[k], data[cspec->coordX]->data(), data[cspec->coordY]->data(), currentRow);

      // attach the data - this way might yield better performance when data sets are large
      QwtPlotCurve *curve = CopasiPlot::curve(crvKeys[k]);

      curve->setRawData(data[cspec->coordX]->data(),
                        data[cspec->coordY]->data(),
                        currentRow);

      // append each (section of) curve as it's set up
      drawCurveInterval(crvKeys[k], startRow, currentRow - 1);
    }

  replot();

  startRow = currentRow;
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

void CopasiPlot::reloadPlot(PlotTaskSpec* plotspec, std::vector<int> deletedCurveKeys)
{
  // is this necessary? the pointers should actually be the same...
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

      /*--------------------------------------------
         hmm, it's a little messy here. the following code will work, but it's equivalent to
         reading in ALL the data, which is surely inefficient. on the other hand, given the characteristics
         specified for ptspec->varIndices, i.e. the elements in the vector should be in ascending order,
         how do we know which is/are the new column/s to pick out???
      */
      unsigned int colNum = 5, index;
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
          QString qs1(cspec->axisTitles[0].c_str());
          setAxisTitle(cspec->xAxis, qs1);
          QString qs2(cspec->axisTitles[1].c_str());
          setAxisTitle(cspec->yAxis, qs2);

          //TODO: maybe set axis titles the same colour as the curve?
          // but can't see any methods for doing this...

          // set up the curve
          long crv = insertCurve(cspec->curveTitle.c_str());

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
  replot();
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
      QArray<long> keys = curveKeys();
      for (unsigned int i = 0; i < keys.size(); i++)
        if (keys[i] == key)
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
