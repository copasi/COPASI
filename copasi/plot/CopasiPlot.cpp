/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CopasiPlot.cpp,v $
   $Revision: 1.40 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/05/12 13:16:49 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qstring.h>
#include <qcolor.h>   //might need to go to the header file
#include <qcursor.h>

#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_scale_engine.h>

#include <float.h>
#include <limits>

#include "scrollzoomer.h"

#include "CopasiPlot.h"
#include "CPlotSpecification.h"
#include "CopasiUI/qtUtilities.h"

#define ActivitySize 8

C_FLOAT64 DummyValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();

//********************  data  *********************************************
MyQwtCPointerData::MyQwtCPointerData(const double *x, const double *y, size_t size):
    QwtCPointerData(x, y, size)
{}

MyQwtCPointerData & MyQwtCPointerData::operator=(const MyQwtCPointerData & rhs)
{
  *static_cast<QwtCPointerData *>(this) = *static_cast<const QwtCPointerData *>(&rhs);
  return * this;
}

QwtData * MyQwtCPointerData::copy() const
  {return new MyQwtCPointerData(xData(), yData(), size());}

QwtDoubleRect MyQwtCPointerData::boundingRect() const
  {
    const size_t sz = size();

    if (sz <= 0)
      return QwtDoubleRect(1.0, 1.0, -2.0, -2.0); // invalid

    double minX, maxX, minY, maxY;

    const double *xIt = xData();
    const double *yIt = yData();
    const double *end = xIt + sz;

    minX = maxX = *xIt++;
    minY = maxY = *yIt++;

    while (xIt < end)
      {
        const double xv = *xIt++;
        if (!isnan(xv))
          {
            if (xv < minX)
              minX = xv;
            if (xv > maxX)
              maxX = xv;
          }

        const double yv = *yIt++;
        if (!isnan(yv))
          {
            if (yv < minY)
              minY = yv;
            if (yv > maxY)
              maxY = yv;
          }
      }

    if (isnan(minX + maxX + minY + maxY))
      return QwtDoubleRect(1.0, 1.0, -2.0, -2.0); // invalid

    return QwtDoubleRect(minX, minY, maxX - minX, maxY - minY);
  }
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
CopasiPlot::CopasiPlot(QWidget* parent):
    QwtPlot(parent),
    mpPlotSpecification(NULL),
    mpZoomer(NULL)
{}

CopasiPlot::CopasiPlot(const CPlotSpecification* plotspec, QWidget* parent):
    QwtPlot(parent),
    mpPlotSpecification(NULL),
    mpZoomer(NULL)
{
  QwtLegend *legend = new QwtLegend;
  legend->setItemMode(QwtLegend::CheckableItem);
  insertLegend(legend, QwtPlot::BottomLegend);

  // Set up the zoom facility
  mpZoomer = new ScrollZoomer(canvas());
  mpZoomer->setRubberBandPen(QColor(Qt::black));
  mpZoomer->setTrackerPen(QColor(Qt::black));
  mpZoomer->setTrackerMode(QwtPicker::AlwaysOn);
  mpZoomer->setTrackerFont(this->font());

  // white background better for printing...
  setCanvasBackground(white);

  //  setTitle(FROM_UTF8(plotspec->getTitle()));
  setCanvasLineWidth(0);

  canvas()->setPaintAttribute(QwtPlotCanvas::PaintPacked, true);

  connect(this, SIGNAL(legendChecked(QwtPlotItem *, bool)),
          SLOT(showCurve(QwtPlotItem *, bool)));

  // Size the vectors to be able to store information for all activities.
  mData.resize(ActivitySize);
  mObjectValues.resize(ActivitySize);
  mDataSize.resize(ActivitySize);
  mDataIndex.clear();

  //setCursor(Qt::CrossCursor);

  // Initialize from the plot specification
  initFromSpec(plotspec);
}

bool CopasiPlot::initFromSpec(const CPlotSpecification* plotspec)
{
  mpPlotSpecification = plotspec;

  if (mpZoomer) mpZoomer->setEnabled(false);

  //removeCurves();
  detachItems();
  mHistograms.clear();

  // createIndices(plotspec);

  unsigned C_INT32 k, kmax = mpPlotSpecification->getItems().size();

  setTitle(FROM_UTF8(mpPlotSpecification->getTitle()));

  CPlotItem* pItem;
  QColor curveColours[5] = {red, blue, green, cyan, magenta} ; //TODO

  mCurves.resize(kmax);
  mCurveTypes.resize(kmax);
  mCurveActivities.resize(kmax);
  mHistoIndices.resize(kmax);

  for (k = 0; k < kmax; k++)
    {
      pItem = mpPlotSpecification->getItems()[k];

      mCurveTypes[k] = pItem->getType();
      mCurveActivities[k] = pItem->getActivity();

      // set up the curve
      QwtPlotCurve* pCurve = new MyQwtPlotCurve(FROM_UTF8(pItem->getTitle()));
      mCurves[k] = pCurve;

      pCurve->setPen(curveColours[k % 5]);
      pCurve->attach(this);

      // activate the legend button
      QwtLegendItem *li = dynamic_cast<QwtLegendItem*>(legend()->find(pCurve));
      if (li) li->setChecked(true);

      switch (mCurveTypes[k])
        {
        case CPlotItem::curve2d:
          switch (*pItem->getValue("Line type").pUINT)
            {
            case 0:          //curve
              pCurve->setStyle(QwtPlotCurve::Lines);
              break;
            case 1:          //points
              pCurve->setStyle(QwtPlotCurve::Dots);
              break;
            case 2:          //symbols
              pCurve->setStyle(QwtPlotCurve::NoCurve);
              const QColor &c = curveColours[k % 5];
              pCurve->setSymbol(QwtSymbol(QwtSymbol::Cross, QBrush(c), QPen(c), QSize(5, 5)));
              break;
            }
          break;

        case CPlotItem::histoItem1d:
          // Store the index of the histogram to be created
          mHistoIndices[k] = mHistograms.size();
          mHistograms.push_back(CHistogram(*pItem->getValue("increment").pDOUBLE));

          pCurve->setStyle(QwtPlotCurve::Steps);
          pCurve->setYAxis(QwtPlot::yRight);
          break;

        default :
          fatalError();
        }
    }

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

bool CopasiPlot::compile(std::vector< CCopasiContainer * > listOfContainer)
{
  clearBuffers();

  unsigned C_INT32 i, imax;
  unsigned C_INT32 j, jmax;

  std::pair< std::set< CCopasiObject * >::iterator, bool > Inserted;
  std::pair< Activity, unsigned C_INT32 > DataIndex;
  std::vector< std::set < CCopasiObject * > > ActivityObjects;

  ActivityObjects.resize(ActivitySize);

  // Loop over all curves.
  imax = mpPlotSpecification->getItems().size();
  mDataIndex.resize(imax);

  for (i = 0; i < imax; ++i)
    {
      CPlotItem * pItem = mpPlotSpecification->getItems()[i];
      Activity ItemActivity = pItem->getActivity();
      DataIndex.first = ItemActivity;

      // Loop over all channels
      jmax = pItem->getNumChannels();
      mDataIndex[i].resize(jmax);

      for (j = 0; j < jmax; ++j)
        {
          CCopasiObject* pObj =
            CCopasiContainer::ObjectFromName(listOfContainer, pItem->getChannels()[j]);

          if (pObj)
            mObjects.insert(pObj);

          Inserted = ActivityObjects[ItemActivity].insert(pObj);

          if (Inserted.second)
            {
              if (ItemActivity & COutputInterface::BEFORE) mHaveBefore = true;
              if (ItemActivity & COutputInterface::DURING) mHaveDuring = true;
              if (ItemActivity & COutputInterface::AFTER) mHaveAfter = true;

              // The insert was succesful
              DataIndex.second = ActivityObjects[ItemActivity].size() - 1;

              // Allocate the data buffer
              mData[ItemActivity].push_back(new QMemArray<double>(500));

              // Store the pointer to the current object value.
              if (pObj)
                mObjectValues[ItemActivity].push_back((C_FLOAT64 *) pObj->getValuePointer());
              else
                mObjectValues[ItemActivity].push_back(&DummyValue);

              // Store [curve][channel] to data index
              mDataIndex[i][j] = DataIndex;

              // Store the [Activity][object] to data index.
              mObjectIndex[ItemActivity][pObj] = DataIndex.second;
            }
          else
            {
              // The object already existed we only need to
              // store [curve][channel] to data index.
              DataIndex.second = mObjectIndex[ItemActivity][pObj];
              mDataIndex[i][j] = DataIndex;
            }
        }
    }

  updateCurves(C_INVALID_INDEX, false);

  mNextPlotTime = CCopasiTimeVariable::getCurrentWallTime();

  return true;
}

void CopasiPlot::output(const Activity & activity)
{
  unsigned C_INT32 i, imax;
  C_INT32 ItemActivity;

  if (mHaveBefore && (activity == COutputInterface::BEFORE)) mDataBefore++;
  else if (mHaveDuring && (activity == COutputInterface::DURING)) mDataDuring++;
  else if (mHaveAfter && (activity == COutputInterface::AFTER)) mDataAfter++;

  for (ItemActivity = 0; ItemActivity < ActivitySize; ItemActivity++)
    if (ItemActivity & activity && mData[ItemActivity].size())
      {
        std::vector< QMemArray< double > * > & data = mData[ItemActivity];
        unsigned C_INT32 & ndata = mDataSize[ItemActivity];

        if ((imax = data.size()) != 0)
          {
            if (ndata >= data[0]->size())
              {
                unsigned C_INT32 newSize = data[0]->size() + 1000;
                for (i = 0; i < imax; i++)
                  data[i]->resize(newSize); // :TODO: check for allocation problems

                //tell the curves that the location of the data has changed
                //otherwise repaint events could crash
                updateCurves(ItemActivity, false);
              }

            //the data that needs to be stored internally:
            for (i = 0; i < imax; ++i)
              data[i]->at(ndata) = *mObjectValues[ItemActivity][i];

            ++ndata;
          }
      }

  // Deal with the histograms.
  for (i = 0, imax = mCurves.size(); i < imax; ++i)
    if (mCurveTypes[i] == CPlotItem::histoItem1d &&
        mCurveActivities[i] & activity)
      {
        std::pair< Activity, unsigned C_INT32 > * pDataIndex = &mDataIndex[i][0];
        mHistograms[mHistoIndices[i]].addValue(*mObjectValues[pDataIndex->first][pDataIndex->second]);
      }

  updatePlot();
}

void CopasiPlot::separate(const Activity & activity)
{
  unsigned C_INT32 i, imax;
  C_INT32 ItemActivity;

  if (mHaveBefore && (activity == COutputInterface::BEFORE)) mDataBefore++;
  if (mHaveDuring && (activity == COutputInterface::DURING)) mDataDuring++;
  if (mHaveAfter && (activity == COutputInterface::AFTER)) mDataAfter++;

  for (ItemActivity = 0; ItemActivity < ActivitySize; ItemActivity++)
    if (ItemActivity & activity && mData[ItemActivity].size())
      {
        std::vector< QMemArray< double > * > & data = mData[ItemActivity];
        unsigned C_INT32 & ndata = mDataSize[ItemActivity];

        if ((imax = data.size()) != 0)
          {
            if (ndata >= data[0]->size())
              {
                unsigned C_INT32 newSize = data[0]->size() + 1000;
                for (i = 0; i < data.size(); i++)
                  data[i]->resize(newSize); // :TODO: check for allocation problems

                //tell the curves that the location of the data has changed
                //otherwise repaint events could crash
                updateCurves(ItemActivity, false);
              }

            //the data that needs to be stored internally:
            for (i = 0; i < imax; ++i)
              data[i]->at(ndata) = DummyValue;

            ++ndata;
          }
      }

  // Deal with the histograms.
  for (i = 0, imax = mCurves.size(); i < imax; ++i)
    if (mCurveTypes[i] == CPlotItem::histoItem1d &&
        mCurveActivities[i] & activity)
      mHistograms[mHistoIndices[i]].addValue(DummyValue);

  updatePlot();

  return;
}

void CopasiPlot::finish()
{
  updateCurves(C_INVALID_INDEX, true);

  replot();

  if (mpZoomer)
    {
      mpZoomer->setEnabled(true);
      mpZoomer->setZoomBase();
    }
}

void CopasiPlot::updateCurves(const unsigned C_INT32 & activity, const bool & doHisto)
{
  if (activity == C_INVALID_INDEX)
    {
      C_INT32 ItemActivity;

      for (ItemActivity = 0; ItemActivity < ActivitySize; ItemActivity++)
        updateCurves(ItemActivity, doHisto);

      return;
    }

  unsigned C_INT32 k, kmax = mCurves.size();

  for (k = 0; k < kmax; k++)
    if (mCurveActivities[k] == activity)
      {
        std::vector< QMemArray< double > * > & data = mData[activity];
        unsigned C_INT32 & ndata = mDataSize[activity];

        switch (mCurveTypes[k])
          {
          case CPlotItem::curve2d:
            mCurves[k]->setData(MyQwtCPointerData(data[mDataIndex[k][0].second]->data(),
                                                  data[mDataIndex[k][1].second]->data(),
                                                  ndata));
            break;

          case CPlotItem::histoItem1d:
            if (doHisto)
              mCurves[k]->setRawData(mHistograms[mHistoIndices[k]].getXArray(),
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
  if (mNextPlotTime < CCopasiTimeVariable::getCurrentWallTime())
    {
      CCopasiTimeVariable Delta = CCopasiTimeVariable::getCurrentWallTime();

      updateCurves(C_INVALID_INDEX, true);
      replot();

      Delta = CCopasiTimeVariable::getCurrentWallTime() - Delta;
      mNextPlotTime = CCopasiTimeVariable::getCurrentWallTime() + Delta + Delta + Delta;
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
  clearBuffers();
}

bool CopasiPlot::saveData(const std::string & filename)
{
  // No objects.
  if (!mObjects.size()) return true;

  // Find out whether we have any data.
  C_INT32 ItemActivity;

  for (ItemActivity = 0; ItemActivity < ActivitySize; ItemActivity++)
    if (mDataSize[ItemActivity] != 0) break;

  // No data
  if (ItemActivity == ActivitySize) return true;

  std::ofstream fs(filename.c_str());
  if (!fs.good()) return false;

  // Write the table header
  fs << "# ";

  std::set< const CCopasiObject * >::iterator it = mObjects.begin();
  std::set< const CCopasiObject * >::iterator end = mObjects.end();

  for (; it != end; ++it)
    fs << (*it)->getObjectDisplayName() << "\t";

  fs << "\n";

  unsigned C_INT32 i, imax = mObjects.size();
  std::vector< QMemArray< double > * > Data;
  Data.resize(imax);

  std::vector< QMemArray< double > * >::const_iterator itData;
  std::vector< QMemArray< double > * >::const_iterator endData = Data.end();

  std::vector< unsigned C_INT32 > Offset;
  std::vector< unsigned C_INT32 >::const_iterator itOffset;

  Offset.resize(imax);

  std::map< Activity, std::map< const CCopasiObject *, unsigned C_INT32 > >::iterator itActivity;
  std::map< const CCopasiObject *, unsigned C_INT32 >::iterator itObject;

  if (mDataBefore)
    {
      for (i = 0, it = mObjects.begin(); it != end; ++it, i++)
        {
          if ((itActivity = mObjectIndex.find(COutputInterface::BEFORE)) != mObjectIndex.end() &&
              (itObject = itActivity->second.find(*it)) != itActivity->second.end())
            {
              Data[i] = mData[COutputInterface::BEFORE][itObject->second];
              continue;
            }
          if ((itActivity = mObjectIndex.find((COutputInterface::Activity) (COutputInterface::BEFORE | COutputInterface::DURING))) != mObjectIndex.end() &&
              (itObject = itActivity->second.find(*it)) != itActivity->second.end())
            {
              Data[i] = mData[COutputInterface::BEFORE | COutputInterface::DURING][itObject->second];
              continue;
            }
          if ((itActivity = mObjectIndex.find((COutputInterface::Activity) (COutputInterface::BEFORE | COutputInterface::AFTER))) != mObjectIndex.end() &&
              (itObject = itActivity->second.find(*it)) != itActivity->second.end())
            {
              Data[i] = mData[COutputInterface::BEFORE | COutputInterface::AFTER][itObject->second];
              continue;
            }
          if ((itActivity = mObjectIndex.find((COutputInterface::Activity) (COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() &&
              (itObject = itActivity->second.find(*it)) != itActivity->second.end())
            {
              Data[i] = mData[COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER][itObject->second];
              continue;
            }

          Data[i] = NULL;
        }

      for (i = 0; i < mDataBefore; i++)
        {
          for (itData = Data.begin(); itData != endData; ++itData)
            {
              if (*itData) fs << (*itData)->at(i);
              else fs << DummyValue;
              fs << "\t";
            }
          fs << std::endl;
        }
    }

  if (mDataDuring)
    {
      for (i = 0, it = mObjects.begin(); it != end; ++it, i++)
        {
          if ((itActivity = mObjectIndex.find(COutputInterface::DURING)) != mObjectIndex.end() &&
              (itObject = itActivity->second.find(*it)) != itActivity->second.end())
            {
              Data[i] = mData[COutputInterface::DURING][itObject->second];
              Offset[i] = 0;
              continue;
            }
          if ((itActivity = mObjectIndex.find((COutputInterface::Activity) (COutputInterface::BEFORE | COutputInterface::DURING))) != mObjectIndex.end() &&
              (itObject = itActivity->second.find(*it)) != itActivity->second.end())
            {
              Data[i] = mData[COutputInterface::BEFORE | COutputInterface::DURING][itObject->second];
              Offset[i] = mDataBefore;
              continue;
            }
          if ((itActivity = mObjectIndex.find((COutputInterface::Activity) (COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() &&
              (itObject = itActivity->second.find(*it)) != itActivity->second.end())
            {
              Data[i] = mData[COutputInterface::DURING | COutputInterface::AFTER][itObject->second];
              Offset[i] = 0;
              continue;
            }
          if ((itActivity = mObjectIndex.find((COutputInterface::Activity) (COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() &&
              (itObject = itActivity->second.find(*it)) != itActivity->second.end())
            {
              Data[i] = mData[COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER][itObject->second];
              Offset[i] = mDataBefore;
              continue;
            }

          Data[i] = NULL;
        }

      for (i = 0; i < mDataDuring; i++)
        {
          for (itData = Data.begin(), itOffset = Offset.begin(); itData != endData; ++itData)
            {
              if (*itData) fs << (*itData)->at(i + *itOffset);
              else fs << DummyValue;
              fs << "\t";
            }
          fs << std::endl;
        }
    }

  if (mDataAfter)
    {
      for (i = 0, it = mObjects.begin(); it != end; ++it, i++)
        {
          if ((itActivity = mObjectIndex.find(COutputInterface::AFTER)) != mObjectIndex.end() &&
              (itObject = itActivity->second.find(*it)) != itActivity->second.end())
            {
              Data[i] = mData[COutputInterface::AFTER][itObject->second];
              Offset[i] = 0;
              continue;
            }
          if ((itActivity = mObjectIndex.find((COutputInterface::Activity) (COutputInterface::BEFORE | COutputInterface::AFTER))) != mObjectIndex.end() &&
              (itObject = itActivity->second.find(*it)) != itActivity->second.end())
            {
              Data[i] = mData[COutputInterface::BEFORE | COutputInterface::AFTER][itObject->second];
              Offset[i] = mDataBefore;
              continue;
            }
          if ((itActivity = mObjectIndex.find((COutputInterface::Activity) (COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() &&
              (itObject = itActivity->second.find(*it)) != itActivity->second.end())
            {
              Data[i] = mData[COutputInterface::DURING | COutputInterface::AFTER][itObject->second];
              Offset[i] = mDataDuring;
              continue;
            }
          if ((itActivity = mObjectIndex.find((COutputInterface::Activity) (COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() &&
              (itObject = itActivity->second.find(*it)) != itActivity->second.end())
            {
              Data[i] = mData[COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER][itObject->second];
              Offset[i] = mDataBefore + mDataDuring;
              continue;
            }

          Data[i] = NULL;
        }

      for (i = 0; i < mDataAfter; i++)
        {
          for (itData = Data.begin(), itOffset = Offset.begin(); itData != endData; ++itData)
            {
              if (*itData) fs << (*itData)->at(i + *itOffset);
              else fs << DummyValue;
              fs << "\t";
            }
          fs << std::endl;
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

  replot();
}

void CopasiPlot::clearBuffers()
{
  mObjects.clear();

  unsigned C_INT32 Activity;
  unsigned C_INT32 i, imax;

  for (Activity = 0; Activity < ActivitySize; Activity++)
    {
      std::vector< QMemArray< double > * > & data = mData[Activity];

      // Delete each QMemArray
      for (i = 0, imax = data.size(); i < imax; i++)
        if (data[i] != NULL) delete data[i];

      data.clear();

      mObjectValues[Activity].clear();
      mDataSize[Activity] = 0;
    }

  mDataIndex.clear();
  mObjectIndex.clear();

  mDataBefore = 0;
  mDataDuring = 0;
  mDataAfter = 0;

  mHaveBefore = false;
  mHaveDuring = false;
  mHaveAfter = false;
}
