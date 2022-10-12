// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include <QtCore/QString>
#include <QColor> //might need to go to the header file
#include <QCursor>
#include <QtCore/QMutexLocker>

#include <limits>
#include <algorithm>
#include <cmath>

#include "copasi/copasi.h"
#include "copasi/config.h"

#ifdef COPASI_USE_QTCHARTS

#  include "scrollzoomer.h"
#  include "CQtChartsPlot.h"
#  include "CQPlotColors.h"

#  include "copasi/plot/CPlotSpecification.h"
#  include "copasi/UI/qtUtilities.h"
#  include "copasi/core/CRootContainer.h"
#  include "copasi/model/CModel.h"
#  include "copasi/commandline/CLocaleString.h"
#  include "copasi/CopasiDataModel/CDataModel.h"

#  include <copasi/plotUI/C2DCurveData.h>
#  include <copasi/plotUI/CBandedGraphData.h>
#  include <copasi/plotUI/CHistoCurveData.h>
#  include <copasi/plotUI/CSpectorgramData.h>

#  include <copasi/plotUI/C2DPlotCurve.h>
#  include <copasi/plotUI/CPlotSpectogram.h>

#  include <copasi/plotUI/CLinearColorMap.h>

#  include <QApplication>

#  include <QtCharts/QChartView>
#  include <QtCharts/QLogValueAxis>
#  include <QtCharts/QValueAxis>
#  include <QtCharts/QLegendMarker>

#  include <QtCharts/QScatterSeries>
#  include <QtCharts/QLineSeries>
#  include <QtCharts/QSplineSeries>

QT_USE_NAMESPACE
QT_CHARTS_USE_NAMESPACE

#  if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
#    include <QRegularExpression>
#  endif

#  define ActivitySize 8
C_FLOAT64 CQtChartsPlot::MissingValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

CQtChartsPlot::CQtChartsPlot(QWidget * parent)
  : QChartView(new CopasiChart(), parent)
  , mCurves(0)
  , mCurveMap()
  , mSpectograms(0)
  , mSpectogramMap()
  , mDataBefore(0)
  , mDataDuring(0)
  , mDataAfter(0)
  , mHaveBefore(false)
  , mHaveDuring(false)
  , mHaveAfter(false)
  , mpPlotSpecification(NULL)
  , mNextPlotTime()
  , mIgnoreUpdate(false)
  , mReplotFinished(false)
  , m_isTouching(false)
{
}

CQtChartsPlot::CQtChartsPlot(const CPlotSpecification * plotspec, QWidget * parent)
  : QChartView(new CopasiChart(), parent)
  , mCurves(0)
  , mCurveMap()
  , mSpectograms(0)
  , mSpectogramMap()
  , mDataBefore(0)
  , mDataDuring(0)
  , mDataAfter(0)
  , mHaveBefore(false)
  , mHaveDuring(false)
  , mHaveAfter(false)
  , mpPlotSpecification(NULL)
  , mNextPlotTime()
  , mIgnoreUpdate(false)
  , mReplotFinished(false)
  , m_isTouching(false)
{

  // Size the vectors to be able to store information for all activities.
  mData.resize(ActivitySize);
  mObjectValues.resize(ActivitySize);
  mObjectInteger.resize(ActivitySize);
  mDataSize.resize(ActivitySize);
  mDataIndex.clear();

  chart()->createDefaultAxes();
  // Initialize from the plot specification
  initFromSpec(plotspec);
  connect(this, SIGNAL(replotSignal()), this, SLOT(replot()));
  setRubberBand(RubberBand::RectangleRubberBand);
  setRenderHint(QPainter::Antialiasing);
}

void CQtChartsPlot::setSymbol(QT_CHARTS_NAMESPACE::QAbstractSeries * pCurve, CPlotItem::SymbolType symbol, QColor color, int size, float width)
{
  auto * c = dynamic_cast< QLineSeries * >(pCurve);

  if (c == NULL)
    return;

}

QString CQtChartsPlot::titleText() const
{
  return chart()->title();
}

bool CQtChartsPlot::initFromSpec(const CPlotSpecification * plotspec)
{

  mIgnoreUpdate = true;
  mpPlotSpecification = plotspec;

  chart()->legend()->setAlignment(Qt::AlignBottom);

  chart()->setTitle(FROM_UTF8(mpPlotSpecification->getTitle()));

  mCurves.resize(mpPlotSpecification->getItems().size());

  mSpectograms.resize(mpPlotSpecification->getItems().size());
  mSpectograms = NULL;

  std::map< std::string, QAbstractSeries * >::iterator found;

  CDataVector< CPlotItem >::const_iterator itPlotItem = mpPlotSpecification->getItems().begin();
  CDataVector< CPlotItem >::const_iterator endPlotItem = mpPlotSpecification->getItems().end();

  CVector< bool > Visible(mpPlotSpecification->getItems().size());
  Visible = true;
  bool * pVisible = Visible.array();

  for (; itPlotItem != endPlotItem; ++itPlotItem, ++pVisible)
    {
      if ((found = mCurveMap.find(itPlotItem->CCopasiParameter::getKey())) != mCurveMap.end())
        {
          *pVisible = found->second->isVisible();
        }
    }

  // Remove unused curves if definition has changed
  auto it = mCurveMap.begin();
  auto end = mCurveMap.end();

  for (; it != end; ++it)
    {
      chart()->removeSeries(it->second);
      pdelete(it->second);
    }

  mCurveMap.clear();

  std::map< std::string, CPlotSpectogram * >::iterator it2 = mSpectogramMap.begin();
  std::map< std::string, CPlotSpectogram * >::iterator end2 = mSpectogramMap.end();

  for (; it2 != end2; ++it2)
    pdelete(it2->second);

  mSpectogramMap.clear();

  itPlotItem = mpPlotSpecification->getItems().begin();
  pVisible = Visible.array();
  auto ppCurve = mCurves.begin();
  CPlotSpectogram ** ppSpectogram = mSpectograms.array();
  unsigned long int k = 0;
  bool needLeft = false;
  bool needRight = false;

  for (; itPlotItem != endPlotItem; ++itPlotItem, ++pVisible, ++ppCurve, ++ppSpectogram, ++k)
    {
      // set up the curve
      auto * series = new QLineSeries();
      series->setProperty("curve_type", QVariant((int) itPlotItem->getType()));
      series->setProperty("activity", QVariant((int) itPlotItem->getActivity()));
      series->setProperty("copasi_key", QVariant(FROM_UTF8(itPlotItem->CCopasiParameter::getKey())));
      series->setName(FROM_UTF8(itPlotItem->getTitle()));
      chart()->addSeries(series);

      *ppCurve = series;

      mCurveMap[itPlotItem->CCopasiParameter::getKey()] = series;

      //color handling should be similar for different curve types
      QColor color;

      if (itPlotItem->getType() == CPlotItem::curve2d
          || itPlotItem->getType() == CPlotItem::histoItem1d
          || itPlotItem->getType() == CPlotItem::bandedGraph)
        {
          std::string colorstr = itPlotItem->getValue< std::string >("Color");
          color = CQPlotColors::getColor(colorstr, k);
        }

      series->setPen(color);

      showCurve(series, *pVisible);

      if (itPlotItem->getType() == CPlotItem::curve2d
          || itPlotItem->getType() == CPlotItem::bandedGraph)
        {
          needLeft = true;
          //pCurve->setRenderHint(QwtPlotItem::RenderAntialiased);

          unsigned C_INT32 linetype = itPlotItem->getValue< unsigned C_INT32 >("Line type");
          CPlotItem::LineType lineType = (CPlotItem::LineType) linetype;

          if (lineType == CPlotItem::LineType::Lines || lineType == CPlotItem::LineType::LinesAndSymbols)
            {
              //              //pCurve->setStyle(QwtPlotCurve::Lines);
              //#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
              //              pCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
              //#endif

              unsigned C_INT32 linesubtype = itPlotItem->getValue< unsigned C_INT32 >("Line subtype");
              CPlotItem::LineStyle lineStyle = (CPlotItem::LineStyle) linesubtype;
              C_FLOAT64 width = itPlotItem->getValue< C_FLOAT64 >("Line width");

              switch (lineStyle)
                {
                  case CPlotItem::LineStyle::Dotted:
                    series->setPen(QPen(QBrush(color), width, Qt::DotLine, Qt::FlatCap));
                    break;

                  case CPlotItem::LineStyle::Dashed:
                    series->setPen(QPen(QBrush(color), width, Qt::DashLine));
                    break;

                  case CPlotItem::LineStyle::DotDash:
                    series->setPen(QPen(QBrush(color), width, Qt::DashDotLine));
                    break;

                  case CPlotItem::LineStyle::DotDotDash:
                    series->setPen(QPen(QBrush(color), width, Qt::DashDotDotLine));
                    break;

                  case CPlotItem::LineStyle::None:
                    //pCurve->setStyle(QwtPlotCurve::NoCurve);
                    break;

                  case CPlotItem::LineStyle::Solid:
                  default:
                    series->setPen(QPen(QBrush(color), width, Qt::SolidLine));
                    break;
                }
            }

          if (lineType == CPlotItem::LineType::Points)
            {
              C_FLOAT64 width = itPlotItem->getValue< C_FLOAT64 >("Line width");
              series->setPen(QPen(color, width, Qt::SolidLine, Qt::RoundCap));
              //pCurve->setStyle(QwtPlotCurve::Dots);
            }

          if (lineType == CPlotItem::LineType::Symbols)
            {
              //pCurve->setStyle(QwtPlotCurve::NoCurve);
            }

          if (lineType == CPlotItem::LineType::Symbols || lineType == CPlotItem::LineType::LinesAndSymbols) //line+symbols
            {
              unsigned C_INT32 symbolsubtype = itPlotItem->getValue< unsigned C_INT32 >("Symbol subtype");
              CPlotItem::SymbolType symbolType = (CPlotItem::SymbolType) symbolsubtype;

              //switch (symbolType) //symbol type
              //  {
              //    case CPlotItem::SymbolType::LargeCross:
              //    case CPlotItem::SymbolType::Plus:
              //      setSymbol(pCurve, QwtSymbol::Cross, color, 7, 2);

              //      break;

              //    case CPlotItem::SymbolType::Circle:
              //      setSymbol(pCurve, QwtSymbol::Ellipse, color, 8, 1);
              //      break;

              //    case CPlotItem::SymbolType::Square:
              //      setSymbol(pCurve, QwtSymbol::Rect, color, 7, 2);
              //      break;

              //    case CPlotItem::SymbolType::Diamond:
              //      setSymbol(pCurve, QwtSymbol::Diamond, color, 7, 2);
              //      break;

              //    case CPlotItem::SymbolType::xCross:
              //      setSymbol(pCurve, QwtSymbol::XCross, color, 7, 2);
              //      break;

              //    case CPlotItem::SymbolType::Star:
              //      setSymbol(pCurve, QwtSymbol::Star2, color, 7, 2);
              //      break;

              //    case CPlotItem::SymbolType::TriangleUp:
              //      setSymbol(pCurve, QwtSymbol::UTriangle, color, 7, 2);
              //      break;

              //    case CPlotItem::SymbolType::TriangleDown:
              //      setSymbol(pCurve, QwtSymbol::DTriangle, color, 7, 2);
              //      break;

              //    case CPlotItem::SymbolType::TriangleLeft:
              //      setSymbol(pCurve, QwtSymbol::LTriangle, color, 7, 2);
              //      break;

              //    case CPlotItem::SymbolType::TriangleRight:
              //      setSymbol(pCurve, QwtSymbol::RTriangle, color, 7, 2);
              //      break;

              //    case CPlotItem::SymbolType::hDash:
              //      setSymbol(pCurve, QwtSymbol::HLine, color, 7, 2);
              //      break;

              //    case CPlotItem::SymbolType::vDash:
              //      setSymbol(pCurve, QwtSymbol::VLine, color, 7, 2);
              //      break;

              //    case CPlotItem::SymbolType::SmallCross:
              //    default:
              //      setSymbol(pCurve, QwtSymbol::Cross, color, 5, 1);
              //      break;

              //    case CPlotItem::SymbolType::None:
              //      break;
              //  }
            }
        } //2d curves and banded graphs

      //  if (pCurve->getType() == CPlotItem::bandedGraph)
      //    {
      //      //set fill color
      //      QColor c = color;
      //      int alpha = 64;

      //      if (itPlotItem->getParameter("alpha"))
      //        alpha = itPlotItem->getValue< C_INT32 >("alpha");

      //      c.setAlpha(alpha);
      //      pCurve->setBrush(c);
      //    }

      //  if (pCurve->getType() == CPlotItem::histoItem1d)
      //    {
      //      pCurve->setIncrement(itPlotItem->getValue< C_FLOAT64 >("increment"));

      //      pCurve->setStyle(QwtPlotCurve::Steps);
      //      pCurve->setYAxis(QwtPlot::yRight);
      //      pCurve->setCurveAttribute(QwtPlotCurve::Inverted);

      //      needRight = true;
      //    }
    }

  chart()->createDefaultAxes();
  toggleLogX(plotspec->isLogX());
  toggleLogY(plotspec->isLogY());

  if (needRight)
    {
      //setAxisScaleEngine(yRight, new QwtLinearScaleEngine());
      //    setAxisTitle(yRight, "Percent %");
      //  enableAxis(yRight);
    }

  connectMarkers();

  mIgnoreUpdate = false;

  return true; //TODO really check!
}

const CPlotSpecification *
CQtChartsPlot::getPlotSpecification() const
{
  return mpPlotSpecification;
}

bool CQtChartsPlot::compile(CObjectInterface::ContainerList listOfContainer)
{
  clearBuffers();

  size_t i, imax;
  size_t j, jmax;

  std::pair< std::set< const CObjectInterface * >::iterator, bool > Inserted;
  std::pair< Activity, size_t > DataIndex;
  std::vector< std::set< const CObjectInterface * > > ActivityObjects;

  ActivityObjects.resize(ActivitySize);

  // Loop over all curves.
  imax = mpPlotSpecification->getItems().size();
  mDataIndex.resize(imax);

  std::vector< std::vector< std::string > >::iterator itX;

  for (i = 0; i < imax; ++i)
    {
      const CPlotItem * pItem = &mpPlotSpecification->getItems()[i];
      bool isSpectogram = pItem->getType() == CPlotItem::spectogram;
      Activity ItemActivity = pItem->getActivity();
      DataIndex.first = ItemActivity;

      // Loop over all channels
      jmax = pItem->getNumChannels();
      mDataIndex[i].resize(jmax);

      for (j = 0; j < jmax; ++j)
        {
          std::string objectCN;

          const CObjectInterface * pObj = CObjectInterface::GetObjectFromCN(listOfContainer, pItem->getChannels()[j]);

          if (pObj)
            {
              mObjects.insert(pObj);
              objectCN = pObj->getCN();
              mCnNameMap[objectCN] = pObj->getObjectDisplayName();
            }
          else
            CCopasiMessage(CCopasiMessage::WARNING, MCCopasiTask + 6,
                           pItem->getChannels()[j].c_str());

          // Remember the actual order for saving the data.
          // Note, we are currently only dealing with 2D curves and histograms.
          // In addition the data is not normalized. The same data column may appear
          // multiple times, e.g. as X value and as Y value for another curve.
          if (j == 0)
            {
              // We have an X value
              for (itX = mSaveCurveObjects.begin(); itX != mSaveCurveObjects.end(); ++itX)
                if (*itX->begin() == objectCN)
                  break;

              if (itX == mSaveCurveObjects.end())
                {
                  std::vector< std::string > NewX;
                  NewX.push_back(objectCN);

                  mSaveCurveObjects.push_back(NewX);
                  itX = mSaveCurveObjects.end() - 1;

                  if (!isSpectogram)
                    setAxisUnits(CPlotInterface::Axis::yAxis, pObj);
                }

              if (pItem->getType() == CPlotItem::histoItem1d)
                mSaveHistogramObjects.push_back(objectCN);
            }
          else
            {
              itX->push_back(objectCN);

              if (!isSpectogram)
                setAxisUnits(CPlotInterface::Axis::yAxis, pObj);
            }

          Inserted = ActivityObjects[ItemActivity].insert(pObj);

          if (Inserted.second)
            {
              if (ItemActivity & COutputInterface::BEFORE)
                mHaveBefore = true;

              if (ItemActivity & COutputInterface::DURING)
                mHaveDuring = true;

              if (ItemActivity & COutputInterface::AFTER)
                mHaveAfter = true;

              // The insert was successful
              DataIndex.second = ActivityObjects[ItemActivity].size() - 1;

              // Allocate the data buffer
              mData[ItemActivity].push_back(new CVector< double >(1000));

              // Store the pointer to the current object value. (Only if it has a double or integer value
              // and the value pointer actually exists. If not, use a dummy value.)
              void * tmp;

              const CDataObject * pDataObject = CObjectInterface::DataObject(pObj);

              if (pDataObject != NULL && (tmp = pObj->getValuePointer()) != NULL && (pDataObject->hasFlag(CDataObject::ValueInt) || pDataObject->hasFlag(CDataObject::ValueDbl)))
                {
                  mObjectValues[ItemActivity].push_back((C_FLOAT64 *) tmp); //pObj->getValuePointer());
                  mObjectInteger[ItemActivity].push_back(pDataObject->hasFlag(CDataObject::ValueInt));
                }
              else
                {
                  mObjectValues[ItemActivity].push_back(&MissingValue);
                  mObjectInteger[ItemActivity].push_back(false);
                }

              // Store [curve][channel] to data index
              mDataIndex[i][j] = DataIndex;

              // Store the [Activity][object] to data index.
              mObjectIndex[ItemActivity][objectCN] = DataIndex.second;
            }
          else
            {
              // The object already existed we only need to
              // store [curve][channel] to data index.
              DataIndex.second = mObjectIndex[ItemActivity][objectCN];
              mDataIndex[i][j] = DataIndex;
            }
        }
    }


  mNextPlotTime = CCopasiTimeVariable::getCurrentWallTime();
  mReplotFinished = true;

  return true;
}

void CQtChartsPlot::output(const Activity & activity)
{
  size_t i, imax;
  C_INT32 ItemActivity;

  if (mHaveBefore && (activity == COutputInterface::BEFORE))
    mDataBefore++;
  else if (mHaveDuring && (activity == COutputInterface::DURING))
    mDataDuring++;
  else if (mHaveAfter && (activity == COutputInterface::AFTER))
    mDataAfter++;

  for (ItemActivity = 0; ItemActivity < ActivitySize; ItemActivity++)
    if ((ItemActivity & activity) && mData[ItemActivity].size())
      {
        std::vector< CVector< double > * > & data = mData[ItemActivity];
        size_t & ndata = mDataSize[ItemActivity];

        if ((imax = data.size()) != 0)
          {
            if (ndata >= data[0]->size())
              {
                resizeCurveData(ItemActivity);
              }

            //the data that needs to be stored internally:
            for (i = 0; i < imax; ++i)
              if (mObjectInteger[ItemActivity][i])
                (*data[i])[ndata] = *(C_INT32 *) mObjectValues[ItemActivity][i];
              else
                (*data[i])[ndata] = *mObjectValues[ItemActivity][i];

            ++ndata;
          }
      }

  updatePlot();
}

void CQtChartsPlot::separate(const Activity & activity)
{
  size_t i, imax;
  C_INT32 ItemActivity;

  if (mHaveBefore && (activity == COutputInterface::BEFORE))
    mDataBefore++;

  if (mHaveDuring && (activity == COutputInterface::DURING))
    mDataDuring++;

  if (mHaveAfter && (activity == COutputInterface::AFTER))
    mDataAfter++;

  for (ItemActivity = 0; ItemActivity < ActivitySize; ItemActivity++)
    if ((ItemActivity & activity) && mData[ItemActivity].size())
      {
        std::vector< CVector< double > * > & data = mData[ItemActivity];
        size_t & ndata = mDataSize[ItemActivity];

        if ((imax = data.size()) != 0)
          {
            if (ndata >= data[0]->size())
              {
                resizeCurveData(ItemActivity);
              }

            //the data that needs to be stored internally:
            for (i = 0; i < imax; ++i)
              (*data[i])[ndata] = MissingValue;

            ++ndata;
          }
      }

  updatePlot();

  return;
}

void CQtChartsPlot::finish()
{

  // We need to force a replot, i.e., the next mNextPlotTime should be in the past.
  mNextPlotTime = 0;

  replot();
}

void CQtChartsPlot::updateCurves(const size_t & activity)
{
  if (activity == C_INVALID_INDEX)
    {
      C_INT32 ItemActivity;

      for (ItemActivity = 0; ItemActivity < ActivitySize; ++ItemActivity)
        {
          updateCurves(ItemActivity);
        }

      return;
    }

  size_t k = 0;
  auto itCurves = mCurves.begin();
  auto endCurves = mCurves.end();

  QPointF range = getRange(chart()->axisY());
  double y_min = range.x();
  double y_max = range.y();

  range = getRange(chart()->axisX());
  double x_min = range.x();
  double x_max = range.y();

  bool data_changed = false;

  for (; itCurves != endCurves; ++itCurves, ++k)
    {
      auto * curve = dynamic_cast< QLineSeries * >(*itCurves);
      auto curve_activity = (*itCurves)->property("activity").toInt();

      if (curve_activity != activity)
        continue;

      auto curve_type = (*itCurves)->property("curve_type").toInt();
      std::string curve_key = TO_UTF8((*itCurves)->property("copasi_key").toString());

      if (curve == NULL || curve_activity != activity)
        continue;

      std::vector< CVector< double > * > & data = mData[curve_activity];

      if (data.size() == 0)
        continue;

      switch (curve_type)
        {
          case CPlotItem::curve2d:
          {
            auto & x = *data[mDataIndex[k][0].second];
            auto & y = *data[mDataIndex[k][1].second];
            auto data_size = mDataSize[activity];
            auto current_count = curve->count();

            if ((data_size - current_count) > 2000)
              data_size = current_count + 2000;

            for (int i = current_count; i < data_size; ++i)
              {
                data_changed = true;
                double cur_x = x[i];
                double cur_y = y[i];

                if (!std::isnan(cur_x) && !std::isnan(cur_y))
                  {
                    curve->append(cur_x, cur_y);

                    if (cur_x < x_min)
                      x_min = cur_x;

                    if (cur_x > x_max)
                      x_max = cur_x;

                    if (cur_y < y_min)
                      y_min = cur_y;

                    if (cur_y > y_max)
                      y_max = cur_y;
                  }
              }
          }
        }
    }

  if (data_changed)
    {
      chart()->axisX()->setRange(x_min, x_max);
      chart()->axisY()->setRange(y_min, y_max);
    }

}

void CQtChartsPlot::resizeCurveData(const size_t & activity)
{
  std::vector< CVector< double > * > & data = mData[activity];
  std::vector< CVector< double > * >::iterator it = data.begin();

  std::vector< CVector< double > * > OldData = data;
  std::vector< CVector< double > * >::iterator itOld = OldData.begin();
  std::vector< CVector< double > * >::iterator endOld = OldData.end();

  size_t oldSize = (*it)->size();
  size_t newSize = 2 * (*it)->size();

  // We must not deallocate the old data since this will create a window of time
  // were the GUI thread may access the old location before it is notified.
  for (; itOld != endOld; ++itOld, ++it)
    {
      *it = new CVector< double >(newSize);
      memcpy((*it)->array(), (*itOld)->array(), oldSize * sizeof(double));
    }

  // Tell the curves that the location of the data has changed
  // otherwise repaint events could crash
  size_t k = 0;
  auto itCurves = mCurves.begin();
  auto endCurves = mCurves.end();

  for (; itCurves != endCurves; ++itCurves, ++k)
    {
      if (*itCurves == NULL)
        continue;

      if ((size_t)(*itCurves)->property("activity").toInt() == activity)
        {
          std::vector< CVector< double > * > & data = mData[activity];

          switch ((*itCurves)->property("curve_type").toInt())
            {
                //case CPlotItem::curve2d:
                //  (*itCurves)->reallocatedData(data[mDataIndex[k][0].second],
                //                               data[mDataIndex[k][1].second]);
                //  break;

                //case CPlotItem::bandedGraph:
                //  (*itCurves)->reallocatedData(data[mDataIndex[k][0].second],
                //                               data[mDataIndex[k][1].second],
                //                               data[mDataIndex[k][2].second]);
                //  break;

                //case CPlotItem::histoItem1d:
                //  (*itCurves)->reallocatedData(data[mDataIndex[k][0].second],
                //                               NULL);
                //  break;

              default:
                //fatalError();
                break;
            }
        }
    }

  k = 0;
  CPlotSpectogram ** itSpectograms = mSpectograms.array();
  CPlotSpectogram ** endSpectograms = itSpectograms + mSpectograms.size();

  for (; itSpectograms != endSpectograms; ++itSpectograms, ++k)
    {
      if (*itSpectograms == NULL)
        continue;

      if ((size_t)(*itSpectograms)->getActivity() == activity)
        {
          std::vector< CVector< double > * > & data = mData[activity];

          switch ((*itSpectograms)->getType())
            {
              case CPlotItem::spectogram:
                (*itSpectograms)->reallocatedData(data[mDataIndex[k][0].second], data[mDataIndex[k][1].second], data[mDataIndex[k][2].second]);
                break;

              default:
                fatalError();
                break;
            }
        }
    }

  // It is now save to delete the old data since the GUI thread has been notified.
  for (itOld = OldData.begin(); itOld != endOld; ++itOld)
    {
      // pdelete(*itOld);
    }
}

void CQtChartsPlot::updatePlot()
{
  if (mReplotFinished)
    {
      mReplotFinished = false;
      emit replotSignal();
    }
}

//-----------------------------------------------------------------------------

/*void ChartsPlot::enableZoom(bool enabled)
{
  zoomOn = enabled;
}*/

//-----------------------------------------------------------------------------

CQtChartsPlot::~CQtChartsPlot()
{
  clearBuffers();
}

bool CQtChartsPlot::saveData(const std::string & filename)
{
  // No objects.
  if (!mObjects.size())
    return true;

  // Find out whether we have any data.
  C_INT32 ItemActivity;

  for (ItemActivity = 0; ItemActivity < ActivitySize; ItemActivity++)
    if (mDataSize[ItemActivity] != 0)
      break;

  // No data
  if (ItemActivity == ActivitySize)
    return true;

  std::ofstream fs(CLocaleString::fromUtf8(filename).c_str());

  if (!fs.good())
    return false;

  // Write the table header
  fs << "# ";

  std::vector< std::vector< std::string > >::const_iterator itX;
  std::vector< std::vector< std::string > >::const_iterator endX =
    mSaveCurveObjects.end();

  std::vector< std::string >::const_iterator it;
  std::vector< std::string >::const_iterator end;

  for (itX = mSaveCurveObjects.begin(); itX != endX; ++itX)
    for (it = itX->begin(), end = itX->end(); it != end; ++it)
      fs << mCnNameMap[*it] << "\t";

  fs << "\n";

  size_t i, imax = mObjects.size();
  std::vector< CVector< double > * > Data;
  Data.resize(imax);

  std::vector< CVector< double > * >::const_iterator itData;
  std::vector< CVector< double > * >::const_iterator endData = Data.end();

  std::vector< size_t > Offset;
  std::vector< size_t >::const_iterator itOffset;

  Offset.resize(imax);

  std::map< Activity, std::map< std::string, size_t > >::iterator itActivity;
  std::map< std::string, size_t >::iterator itObject;

  if (mDataBefore)
    {
      for (itX = mSaveCurveObjects.begin(), i = 0; itX != endX; ++itX)
        for (it = itX->begin(), end = itX->end(); it != end; ++it, ++i)
          {
            if ((itActivity = mObjectIndex.find(COutputInterface::BEFORE)) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE][itObject->second];
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING))) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::DURING][itObject->second];
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::AFTER))) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::AFTER][itObject->second];
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
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
              if (*itData)
                fs << (**itData)[i];
              else
                fs << MissingValue;

              fs << "\t";
            }

          fs << std::endl;
        }
    }

  if (mDataDuring)
    {
      for (itX = mSaveCurveObjects.begin(), i = 0; itX != endX; ++itX)
        for (it = itX->begin(), end = itX->end(); it != end; ++it, ++i)
          {
            if ((itActivity = mObjectIndex.find(COutputInterface::DURING)) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::DURING][itObject->second];
                Offset[i] = 0;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING))) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::DURING][itObject->second];
                Offset[i] = mDataBefore;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::DURING | COutputInterface::AFTER][itObject->second];
                Offset[i] = 0;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
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
              if (*itData)
                fs << (**itData)[i + *itOffset];
              else
                fs << MissingValue;

              fs << "\t";
            }

          fs << std::endl;
        }
    }

  if (mDataAfter)
    {
      for (itX = mSaveCurveObjects.begin(), i = 0; itX != endX; ++itX)
        for (it = itX->begin(), end = itX->end(); it != end; ++it, ++i)
          {
            if ((itActivity = mObjectIndex.find(COutputInterface::AFTER)) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::AFTER][itObject->second];
                Offset[i] = 0;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::AFTER))) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::AFTER][itObject->second];
                Offset[i] = mDataBefore;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::DURING | COutputInterface::AFTER][itObject->second];
                Offset[i] = mDataDuring;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
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
              if (*itData)
                fs << (**itData)[i + *itOffset];
              else
                fs << MissingValue;

              fs << "\t";
            }

          fs << std::endl;
        }
    }

  bool FirstHistogram = true;
  size_t HistogramIndex = 0;

  auto itCurves = mCurves.begin();
  auto endCurves = mCurves.end();

  for (; (itCurves != endCurves) && (HistogramIndex < mSaveHistogramObjects.size()); ++itCurves, ++HistogramIndex)
    {
      if (*itCurves == NULL)
        continue;

      if ((*itCurves)->property("curve_type").toInt() == CPlotItem::histoItem1d)
        {
          if (FirstHistogram)
            {
              fs << "\n# The histograms: \n";
              FirstHistogram = false;
            }

          fs << mSaveHistogramObjects[HistogramIndex] << std::endl;

          auto * curve = dynamic_cast< QXYSeries * >(*itCurves);

for (auto p : curve->points())
            {
              fs << p.x() << "\t" << p.y() << "\n";
            }
        }
    }

  fs.close();

  if (!fs.good())
    return false;

  return true;
}

void CQtChartsPlot::showCurve(QAbstractSeries * item, bool on)
{
  item->setVisible(on);

  if (!mIgnoreUpdate)
    replot();
}

void CQtChartsPlot::setCurvesVisibility(const bool & visibility)
{
  const auto markers = chart()->legend()->markers();

for (QLegendMarker * marker : markers)
    {
      // Toggle visibility of series
      marker->series()->setVisible(!marker->series()->isVisible());

      // Turn legend marker back to visible, since hiding series also hides the marker
      // and we don't want it to happen now.
      marker->setVisible(true);
    }

  if (!mIgnoreUpdate)
    replot();
}

void CQtChartsPlot::clearBuffers()
{
  mObjects.clear();

  size_t Activity;
  size_t i, imax;

  for (Activity = 0; Activity < ActivitySize; Activity++)
    {
      std::vector< CVector< double > * > & data = mData[Activity];

      // Delete each QMemArray
      for (i = 0, imax = data.size(); i < imax; i++)
        if (data[i] != NULL)
          delete data[i];

      data.clear();

      mObjectValues[Activity].clear();
      mObjectInteger[Activity].clear();
      mDataSize[Activity] = 0;
    }

  mDataIndex.clear();
  mObjectIndex.clear();

  mSaveCurveObjects.clear();
  mCnNameMap.clear();
  mSaveHistogramObjects.clear();

  mDataBefore = 0;
  mDataDuring = 0;
  mDataAfter = 0;

  mHaveBefore = false;
  mHaveDuring = false;
  mHaveAfter = false;
}

void CQtChartsPlot::setAxisUnits(Axis axis,
                                 const CObjectInterface * pObjectInterface)
{
  if (axis ==  CPlotInterface::Axis::xAxis)
    chart()->axisX()->setTitleText(getAxisText(axis, pObjectInterface));
  else
    chart()->axisY()->setTitleText(getAxisText(axis, pObjectInterface));
}

// virtual
void CQtChartsPlot::replot()
{
  if (mNextPlotTime < CCopasiTimeVariable::getCurrentWallTime())
    {
      // skip rendering when shift is pressed
      Qt::KeyboardModifiers mods = QApplication::keyboardModifiers();

      if (((int) mods & (int) Qt::ShiftModifier) == (int) Qt::ShiftModifier && !mNextPlotTime.isZero())
        {
          mReplotFinished = true;
          return;
        }

      CCopasiTimeVariable Delta = CCopasiTimeVariable::getCurrentWallTime();

      {
        QMutexLocker Locker(&mMutex);
        updateCurves(C_INVALID_INDEX);
      }

      chart()->update();

      Delta = CCopasiTimeVariable::getCurrentWallTime() - Delta;

      if (!mSpectogramMap.empty())
        mNextPlotTime = CCopasiTimeVariable::getCurrentWallTime() + 10 * Delta.getMicroSeconds();
      else
        mNextPlotTime = CCopasiTimeVariable::getCurrentWallTime() + 3 * Delta.getMicroSeconds();
    }

  mReplotFinished = true;
}

void CQtChartsPlot::update()
{
  chart()->update();
}

QPointF CQtChartsPlot::getRange(const QAbstractAxis * axis)
{
  const QValueAxis * val = dynamic_cast< const QValueAxis * >(axis);

  if (val)
    {
      return QPointF(val->min(), val->max());
    }

  const QLogValueAxis * logAxis = dynamic_cast< const QLogValueAxis * >(axis);

  if (logAxis)
    {
      return QPointF(logAxis->min(), logAxis->max());
    }

  return QPointF();
}

void CQtChartsPlot::connectMarkers()
{
  // Connect all markers to handler
  const auto markers = chart()->legend()->markers();

for (QLegendMarker * marker : markers)
    {
      // Disconnect possible existing connection to avoid multiple connections
      QObject::disconnect(marker, &QLegendMarker::clicked,
                          this, &CQtChartsPlot::handleMarkerClicked);
      QObject::connect(marker, &QLegendMarker::clicked, this, &CQtChartsPlot::handleMarkerClicked);
    }
}

void CQtChartsPlot::disconnectMarkers()
{
  const auto markers = chart()->legend()->markers();

for (QLegendMarker * marker : markers)
    {
      QObject::disconnect(marker, &QLegendMarker::clicked,
                          this, &CQtChartsPlot::handleMarkerClicked);
    }
}

void CQtChartsPlot::handleMarkerClicked()
{
  QLegendMarker * marker = qobject_cast< QLegendMarker * >(sender());
  Q_ASSERT(marker);

  switch (marker->type())
    {
      case QLegendMarker::LegendMarkerTypeXY:
      {
        // Toggle visibility of series
        marker->series()->setVisible(!marker->series()->isVisible());

        // Turn legend marker back to visible, since hiding series also hides the marker
        // and we don't want it to happen now.
        marker->setVisible(true);

        break;
      }

      default:
      {
        break;
      }
    }
}

void CQtChartsPlot::toggleLogX(bool logX)
{
  QValueAxis * val = dynamic_cast< QValueAxis * >(chart()->axisX());
  QLogValueAxis * logVal = dynamic_cast< QLogValueAxis * >(chart()->axisX());

  if (logX && val)
    {
for (auto * series : chart()->series())
        series->detachAxis(val);

      QLogValueAxis * axis = new QLogValueAxis();
      axis->setRange(val->min(), val->max());
      axis->setTitleText(val->titleText());
      chart()->setAxisX(axis);

for (auto * series : chart()->series())
        series->attachAxis(axis);
    }

  if (!logX && logVal)
    {
for (auto * series : chart()->series())
        series->detachAxis(logVal);

      QValueAxis * axis = new QValueAxis();
      axis->setRange(logVal->min(), logVal->max());
      axis->setTitleText(logVal->titleText());
      chart()->setAxisX(axis);

for (auto * series : chart()->series())
        series->attachAxis(axis);
    }
}

void CQtChartsPlot::toggleLogY(bool logY)
{
  QValueAxis * val = dynamic_cast< QValueAxis * >(chart()->axisY());
  QLogValueAxis * logVal = dynamic_cast< QLogValueAxis * >(chart()->axisY());

  if (logY && val)
    {
for (auto * series : chart()->series())
        series->detachAxis(val);

      QLogValueAxis * axis = new QLogValueAxis();
      axis->setRange(val->min(), val->max());
      axis->setTitleText(val->titleText());
      chart()->setAxisY(axis);

for (auto * series : chart()->series())
        series->attachAxis(axis);
    }

  if (!logY && logVal)
    {
for (auto * series : chart()->series())
        series->detachAxis(logVal);

      QValueAxis * axis = new QValueAxis();
      axis->setRange(logVal->min(), logVal->max());
      axis->setTitleText(logVal->titleText());
      chart()->setAxisY(axis);

for (auto * series : chart()->series())
        series->attachAxis(axis);
    }
}

void CQtChartsPlot::render(QPainter * painter, QRect rect)
{
  QChartView::render(painter, rect);
}

void CQtChartsPlot::resetZoom()
{
  chart()->zoomReset();
}

bool CQtChartsPlot::viewportEvent(QEvent * event)
{
  if (event->type() == QEvent::TouchBegin)
    {
      m_isTouching = true;

      chart()->setAnimationOptions(QChart::NoAnimation);
    }

  return QChartView::viewportEvent(event);
}

void CQtChartsPlot::mousePressEvent(QMouseEvent * event)
{
  if (m_isTouching)
    return;

  QChartView::mousePressEvent(event);
}

void CQtChartsPlot::mouseMoveEvent(QMouseEvent * event)
{
  if (m_isTouching)
    return;

  QChartView::mouseMoveEvent(event);
}

void CQtChartsPlot::mouseReleaseEvent(QMouseEvent * event)
{
  if (m_isTouching)
    m_isTouching = false;

  // Because we disabled animations when touch event was detected
  // we must put them back on.
  chart()->setAnimationOptions(QChart::SeriesAnimations);

  QChartView::mouseReleaseEvent(event);
}

void CQtChartsPlot::keyPressEvent(QKeyEvent * event)
{
  switch (event->key())
    {
      case Qt::Key_Plus:
        chart()->zoomIn();
        break;

      case Qt::Key_Minus:
        chart()->zoomOut();
        break;

      case Qt::Key_Left:
        chart()->scroll(-10, 0);
        break;

      case Qt::Key_Right:
        chart()->scroll(10, 0);
        break;

      case Qt::Key_Up:
        chart()->scroll(0, 10);
        break;

      case Qt::Key_Down:
        chart()->scroll(0, -10);
        break;

      default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}

#  include <QtWidgets/QGesture>
#  include <QtWidgets/QGraphicsScene>
#  include <QtWidgets/QGraphicsView>

#  include <QtCharts/QChart>

CopasiChart::CopasiChart(QGraphicsItem * parent, Qt::WindowFlags wFlags)
  : QChart(QChart::ChartTypeCartesian, parent, wFlags)
{
  // Seems that QGraphicsView (QChartView) does not grab gestures.
  // They can only be grabbed here in the QGraphicsWidget (QChart).
  grabGesture(Qt::PanGesture);
  grabGesture(Qt::PinchGesture);
}

CopasiChart::~CopasiChart()
{
}

bool CopasiChart::sceneEvent(QEvent * event)
{
  if (event->type() == QEvent::Gesture)
    return gestureEvent(static_cast< QGestureEvent * >(event));

  return QChart::event(event);
}

bool CopasiChart::gestureEvent(QGestureEvent * event)
{
  if (QGesture * gesture = event->gesture(Qt::PanGesture))
    {
      QPanGesture * pan = static_cast< QPanGesture * >(gesture);
      QChart::scroll(-(pan->delta().x()), pan->delta().y());
    }

  if (QGesture * gesture = event->gesture(Qt::PinchGesture))
    {
      QPinchGesture * pinch = static_cast< QPinchGesture * >(gesture);

      if (pinch->changeFlags() & QPinchGesture::ScaleFactorChanged)
        QChart::zoom(pinch->scaleFactor());
    }

  return true;
}

#endif // COPASI_USE_QTCHARTS
